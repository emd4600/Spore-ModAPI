#include "stdafx.h"
#include "UIInspectCheat.h"

UIInspectCheat::UIInspectCheat()
{
}


UIInspectCheat::~UIInspectCheat()
{
}

int UIInspectCheat::AddRef() {
	return ArgScript::ICommand::AddRef();
}
int UIInspectCheat::Release() {
	return ArgScript::ICommand::Release();
}

void* UIInspectCheat::Cast(uint32_t type) const {
	CLASS_CAST(UTFWin::IWinProc);
	CLASS_CAST(UTFWin::UTFWinObject);
	return nullptr;
}

void UIInspectCheat::ParseLine(const ArgScript::Line& line)
{
	line.GetArguments(0);

	useBreakpoint = line.HasFlag("debug");

	auto mainWindow = WindowManager.GetMainWindow();
	for (auto proc : mainWindow->procedures()) {
		if (proc == object_cast<UTFWin::IWinProc>(this)) {
			App::ConsolePrintF("Already inspecting; click on screen to finish cheat.");
			return;
		}
	}

	App::ConsolePrintF("Click outside the console, place the mouse where you want and press any key to inspect.");

	mainWindow->AddWinProc(this);

	wasIgnoringMouse = mainWindow->GetFlags() & UTFWin::kWinFlagIgnoreMouse;
	mainWindow->SetFlag(UTFWin::kWinFlagIgnoreMouse, false);
}

const char* UIInspectCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Gives you information about the UI window where you click. If run with -debug, you can view in Visual Studio.";
}

int UIInspectCheat::GetPriority() const {
	return 100000;
}
int UIInspectCheat::GetEventFlags() const {
	return UTFWin::kEventFlagBasicInput;
}

// Used to find the window that contains the point and has the smallest area
void FindWindow(UTFWin::IWindow* window, float x, float y, float& area, IWindowPtr& dst) 
{
	auto a = window->GetRealArea();
	if (window->ContainsPoint(window->ToLocalCoordinates({ x, y })) && a.GetWidth() * a.GetHeight() < area) {
		area = a.GetWidth() * a.GetHeight();
		dst = window;
	}
	for (auto child : window->children()) {
		FindWindow(child, x, y, area, dst);
	}
}

bool UIInspectCheat::HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) {
	if (message.IsType(UTFWin::kMsgKeyUp)) {
		auto& params = Renderer.GetScreenInfo();
		auto mainWindow = WindowManager.GetMainWindow();

		IWindowPtr window;
		float area = 10000000;
		FindWindow(mainWindow, float(params.mouseX), float(params.mouseY), area, window);

		if (useBreakpoint) {
			ManualBreakpoint();
			// You can inspect window now
		}

		auto a = window->GetRealArea();
		int childCount = 0;
		int procCount = 0;
		for (auto child : window->children()) ++childCount;
		for (auto child : window->procedures()) ++procCount;

		App::ConsolePrintF("ControlID: 0x%x     CommandID: 0x%x     RealArea: (%f, %f, %f, %f)    NumChildren: %d    NumWinProc: %d    Address: 0x%x",
			window->GetControlID(), window->GetCommandID(), a.x1, a.y1, a.x2, a.y2, childCount, procCount, window.get());

		mainWindow->SetFlag(UTFWin::kWinFlagIgnoreMouse, wasIgnoringMouse);
		mainWindow->RemoveWinProc(this);
		return true;
	}
	return false;
}