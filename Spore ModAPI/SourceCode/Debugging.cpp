#ifndef MODAPI_DLL_EXPORT
#include <Spore/Internal.h>

bool ManualBreakpoint()
{
	// Get System directory, typically c:\windows\system32
	wchar_t systemDir[MAX_PATH + 1];
	UINT nChars = GetSystemDirectoryW(systemDir, MAX_PATH);
	if (nChars == 0) return false; // failed to get system directory
	systemDir[nChars] = 0;

	// Get process ID and create the command line
	DWORD pid = GetCurrentProcessId();

	wchar_t cmdLine[1000];
	wsprintf(cmdLine, L"%ls\\vsjitdebugger.exe -p %d", systemDir, pid);

	// Start debugger process
	STARTUPINFOW si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessW(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) return false;

	// Close debugger process handles to eliminate resource leak
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	// Wait for the debugger to attach
	while (!IsDebuggerPresent()) Sleep(100);

	// Stop execution so the debugger can take over
	DebugBreak();
	return true;
}
#endif
