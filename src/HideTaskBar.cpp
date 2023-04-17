#include <Windows.h>

void HideTaskBar() {
	HWND taskBar = FindWindow(L"Shell_TrayWnd", NULL);
	ShowWindow(taskBar, SW_HIDE);
}