#include <Windows.h>

void HideDesktop() {
    HWND hProgman = FindWindowW(L"Progman", L"Program Manager");
    HWND hChild = GetWindow(hProgman, GW_CHILD);
    ShowWindow(hChild, SW_HIDE);
}