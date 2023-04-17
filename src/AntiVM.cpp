#include "SystemInfo.h"
#include <Windows.h>
#include <algorithm>

BOOLEAN IsVirtualMachine() {
	std::wstring _GPU = GetGPUName();
	std::wstring _MANUFACTURER = GetComputerManufacturer();

    std::transform(_GPU.begin(), _GPU.end(), _GPU.begin(), ::tolower);
    std::transform(_MANUFACTURER.begin(), _MANUFACTURER.end(), _MANUFACTURER.begin(), ::tolower);

	std::wstring _VM_NAMES[13] {
        L"vbox",
        L"vmbox",
        L"vmware",
        L"virtualbox",
        L"qemu",
        L"thinapp",
        L"VMXh",
        L"innotek gmbh",
        L"tpvcgateway",
        L"tpautoconnsvc",
        L"kvm",
        L"red hat",
        L"virtual platform"
    };

    for (const auto vm : _VM_NAMES) {
        if ((_GPU.find(vm) != std::string::npos) || (_MANUFACTURER.find(vm) != std::string::npos)) {
            return TRUE;
        }
    }

    return FALSE;
}