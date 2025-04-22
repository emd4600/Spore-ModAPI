/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModCreatorKit.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#include "stdafx.h"
#include "ThumbnailCaptureScript.h"
#include <Spore\Cheats.h>
#include <Spore\GameModes.h>
#include <Spore\Editors\Editor.h>
#include <Spore\Graphics\IRenderer.h>
#include <Spore\Graphics\RenderUtils.h>
#include <d3dx9tex.h>

using namespace Editors;

ThumbnailCaptureScript::ThumbnailCaptureScript()
	: mIdentityColor(206 / 255.0f, 212 / 255.0f, 175 / 255.0f)
	, mOldColor()
	, mOldColorSet(false)
	, mItemViewers()
	, mpItemViewer(nullptr)
	, mFolderPath()
	, mIsEnabled(false)
{
}


ThumbnailCaptureScript::~ThumbnailCaptureScript()
{
}

//---------------------------------------------------
// Detours

Palettes::PaletteUI* pLastPalette;

// Editor parts palette loading func, PaletteUI::Load. Used to pull the ingame palettes
member_detour(PaletteUILoad_detour, Palettes::PaletteUI, void(Palettes::PaletteMain*, UTFWin::IWindow*, bool, Palettes::PaletteInfo*)) {
	void detoured(Palettes::PaletteMain* pPalette, UTFWin::IWindow* pWindow, bool bool1, Palettes::PaletteInfo* pInfo) {
		pLastPalette = this;
		original_function(this, pPalette, pWindow, bool1, pInfo);
	}
};

void ThumbnailCaptureScript::AttachDetour() {
	PaletteUILoad_detour::attach(GetAddress(Palettes::PaletteUI, Load));
}

//---------------------------------------------------


int ThumbnailCaptureScript::GetEventFlags() const {
	return UTFWin::kEventRefresh;
}

bool ThumbnailCaptureScript::HandleUIMessage(IWindow* pWindow, const Message& message) {
	if (message.IsType(kMsgMouseEnter)) {
		mpItemViewer = mItemViewers[pWindow];
	}
	else if (message.IsType(kMsgMouseLeave)) {
		// For some reason this might happen in parallel to Render? We don't want them to race
		//mpItemViewer = nullptr;
	}
	return false;
}

void ThumbnailCaptureScript::DrawLayer(int flags, int layerIndex, App::cViewer** arg_8, Graphics::RenderStatistics& stats) {
	if (mpItemViewer && mpItemViewer->mpModel) {

		auto model = mpItemViewer->mpModel.get();
		auto modelWorld = model->GetModelWorld();

		if (!mOldColorSet) {
			auto color = mpItemViewer->mpModel->mColor;
			mOldColor = ColorRGB(color.r, color.g, color.b);
			mOldColorSet = true;
		}

		mpItemViewer->field_16A = false;

		auto viewer = mpItemViewer->mpLayeredObject->GetViewer();
		viewer->SetBackgroundColor(ColorRGBA(0, 0, 0, 0));
		viewer->ClearScene(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);

		model->AddGroup(0x32FAB27);

		modelWorld->StallUntilLoaded(model);
		mpItemViewer->InitializeViewerCamera();
		mpItemViewer->RotateModel();

		model->mColor = ColorRGBA(mIdentityColor, 1.0f);

		modelWorld->SetInWorld(model, true);
		modelWorld->AsLayer()->DrawLayer(flags, layerIndex, &viewer, stats);

		model->RemoveGroup(0x32FAB27);


		// Wait for the maximum zoom
		if (mpItemViewer->mZoom == mpItemViewer->mFinalZoom) {
			CaptureImage();
			// We will only do it once, also restore the rotation
			mpItemViewer->field_16A = true;
			mpItemViewer = nullptr;

			model->mColor = ColorRGBA(mOldColor, 1.0f);
			mOldColorSet = false;
		}
	}
}

Vector3 ThumbnailCaptureScript::CalculateOffset(Graphics::Model* model)
{
	BoundingBox bbox;
	auto propList = model->GetPropList();
	if (propList && propList->HasProperty(0x1CBB2F62)) {
		App::Property* p;
		propList->GetProperty(0x1CBB2F62, p);
		bbox = *p->GetValueBBox();
	}
	else {
		bbox = model->mpWorld->GetBoundingBox(model);
	}

	return -(bbox.upper + bbox.lower) / 2;
}

void ThumbnailCaptureScript::CaptureImage() {
	auto device = Graphics::RenderUtils::GetDevice();
	HRESULT hr;
	IDirect3DSurface9* surface;
	hr = device->GetRenderTarget(0, &surface);
	if (hr == D3D_OK) {
		RECT rect;

		auto viewer = mpItemViewer->mpLayeredObject->GetViewer();
		auto viewport = viewer->GetViewport();
		rect.left = viewport.X;
		rect.top = viewport.Y;
		rect.right = viewport.X + viewport.Width;
		rect.bottom = viewport.Y + viewport.Height;

		string16 path = mFolderPath;
		path.append_sprintf(u"0x%x.png", mpItemViewer->mFileName.instanceID);

		hr = D3DXSaveSurfaceToFile((LPCWSTR)path.c_str(), D3DXIMAGE_FILEFORMAT::D3DXIFF_PNG,
			surface, NULL, &rect);

		if (hr != D3D_OK) {
			App::ConsolePrintF("Could not save surface to file: %d", hr);
		}
		else {
			App::ConsolePrintF("Thumbnail successfully saved to: %ls", path.c_str());
		}
	}
	else {
		App::ConsolePrintF("Could not get render surface: %d", hr);
	}

	device->SetRenderTarget(0, surface);
}


PaletteUIPtr ThumbnailCaptureScript::GetCurrentPalette() const {
	// Editor is valid, get the parts palette
	if (GetEditor() && GetEditor()->IsActive()) { return GetEditor()->mpPartsPaletteUI; }
	// Editor is invalid, try the last loaded palette
	else { return pLastPalette; }

}

void ThumbnailCaptureScript::InjectListeners() {

	PaletteUIPtr palette = GetCurrentPalette();
	if (!palette) { return; }

	RemoveListeners();
	for (PaletteCategoryUIPtr catUI : palette->mCategories) {
		PaletteSubcategoriesUIPtr subCatUIs = catUI->mpSubcategoriesUI;

		// subcategories present
		if (subCatUIs) {
			for (PaletteCategoryUIPtr subCatUI : subCatUIs->mCategoryUIs) {
				for (auto pageUI : subCatUI->mPageUIs) {
					// standard editor/planner
					if (pageUI.page->mStandardItems.size() > 0) {
						for (StandardItemUIPtr itemUI : pageUI.page->mStandardItems) {
							itemUI->mpWindow->AddWinProc(this);
							mItemViewers[itemUI->mpWindow.get()] = itemUI->mpViewer.get();
						}
					}
					// adventure editor
					/*
					else {
						for (eastl::intrusive_ptr<Palettes::IAdvancedItemUI> itemUI : pageUI.page->mAdvancedItems) {
							itemUI->mpWindow
							mItemViewers[itemUI->mpWindow.get()] = itemUI->mpViewer.get();
						}
					}*/
					
				}
			}
		}
		// simple category
		else {
			for (auto pageUI : catUI->mPageUIs) {
				for (StandardItemUIPtr itemUI : pageUI.page->mStandardItems) {
					itemUI->mpWindow->AddWinProc(this);
					mItemViewers[itemUI->mpWindow.get()] = itemUI->mpViewer.get();
				}
			}
		}
		
	}

	Renderer.RegisterLayer(this, 40);
}



void ThumbnailCaptureScript::RemoveListeners() {

	PaletteUIPtr palette = GetCurrentPalette();
	if (!palette) { return; }

	for (auto catUI : palette->mCategories) {
		auto subCatUIs = catUI->mpSubcategoriesUI;

		// subcategories present
		if (subCatUIs) {
			for (PaletteCategoryUIPtr subCatUI : subCatUIs->mCategoryUIs) {
				for (auto pageUI : subCatUI->mPageUIs) {
					// standard editor/planner
					if (pageUI.page->mStandardItems.size() > 0) {
						for (StandardItemUIPtr itemUI : pageUI.page->mStandardItems) {
							itemUI->mpWindow->RemoveWinProc(this);
						}
					}
					/*
					// adventure editor
					else {
						for (StandardItemUIPtr itemUI : pageUI.page->mpPage->mItems) {
							itemUI->mpWindow->RemoveWinProc(this);
						}
					}
					*/
				}
			}
		}
		// simple category
		else {
			for (auto pageUI : catUI->mPageUIs) {
				for (StandardItemUIPtr itemUI : pageUI.page->mStandardItems) {
					if (itemUI && itemUI->mpWindow) {
						itemUI->mpWindow->RemoveWinProc(this);
					}
				}
			}
		}
	}

	mItemViewers.clear();

	Renderer.UnregisterLayer(40);
}

void ThumbnailCaptureScript::ParseLine(const ArgScript::Line& line) {
	if (mIsEnabled) {
		RemoveListeners();
		App::ConsolePrintF("Icon capture disabled.");
		mIsEnabled = false;
		return;
	}

	//auto editor = GetEditor();

	if (!Editor.IsActive()) {

		if (Simulator::GetGameModeID() == kEditorMode) {
			App::ConsolePrintF("Must be in editor or a community planner to use this cheat.");
			return;
		}
		// TODO: make this work in the adventure editor.
		else if (Simulator::IsTribeGame() || Simulator::IsCivGame() || Simulator::IsSpaceGame()) { // || Simulator::IsScenarioMode()
			// found a palette that's been loaded anyway
			if (!pLastPalette) {
				App::ConsolePrintF("Must be in editor or a community planner to use this cheat.");
			}
		}
		
		//return;
	}
	else if (!Editor.IsMode(Mode::BuildMode)) {
		App::ConsolePrintF("Must be in editor build mode to use this cheat.");
		return;
	}

	if (line.GetArgumentsCount() == 1) {
		App::ConsolePrintF("Please, specify the output folder path.");
		return;
	}

	mFolderPath = string16(string16::CtorConvert(), line.GetArguments(1)[0]);
	if (mFolderPath[mFolderPath.size() - 1] != char16_t('\\') && mFolderPath[mFolderPath.size() - 1] != char16_t('/')) {
		mFolderPath.append(1, char16_t('\\'));
	}

	auto args = line.GetOption("color", 1);
	if (args) {
		mIdentityColor = this->mpFormatParser->ParseColorRGB(args[0]);
	}

	InjectListeners();

	App::ConsolePrintF("Icon capture enabled: hover a palette item and wait until it starts rotating to generate the icon.");
	mIsEnabled = true;
}

const char* ThumbnailCaptureScript::GetDescription(ArgScript::DescriptionMode mode) const {
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Generates a thumbnail icon for all the parts you hover. Usage: captureIcon \"destination/path\"";
	}
	else {
		return "Generates a thumbnail icon for all the parts you hover. Usage:\n\tcaptureIcon \"destination/path\"\n  (Optional) -color <identityColor>, allows you to change the identity color used in the part thumbnail.";
	}
}

int ThumbnailCaptureScript::AddRef() {
	return DefaultObject::AddRef();
}
int ThumbnailCaptureScript::Release() {
	return DefaultObject::Release();
}
void* ThumbnailCaptureScript::Cast(uint32_t type) const {
	if (type == IWinProc::TYPE) return (IWinProc*)this;
	else return DefaultObject::Cast(type);
}

void ThumbnailCaptureScript::AddCheat() {
	CheatManager.AddCheat("captureIcon", new ThumbnailCaptureScript());
}

bool ThumbnailCaptureScript::HandleMessage(uint32_t messageID, void* message) {
	if (messageID == App::kMsgOnModeExit) {
		auto data = (App::OnModeExitMessage*)message;
		if (data->GetPreviousModeID() == GameModeIDs::kEditorMode) {
			RemoveListeners();
		}
	}
	return false;
}