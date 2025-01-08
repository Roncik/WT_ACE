#include "stdafx.h"
#include "kdmapper.hpp"
#include "1stdriver.h"
#include "Encryption.h"
#include "skStr.h"
#define DISABLE_OUTPUT 
#define NO_CONSOLE

static bool Mapping_Complete = false;
static HANDLE iqvw64e_device_handle;


static int paramExists(const int argc, wchar_t** argv, const wchar_t* param) {
	size_t plen = wcslen(param);
	for (int i = 1; i < argc; i++) {
		if (wcslen(argv[i]) == plen + 1ull && _wcsicmp(&argv[i][1], param) == 0 && argv[i][0] == '/') { // with slash
			return i;
		}
		else if (wcslen(argv[i]) == plen + 2ull && _wcsicmp(&argv[i][2], param) == 0 && argv[i][0] == '-' && argv[i][1] == '-') { // with double dash
			return i;
		}
	}
	return -1;
}



static bool callbackExample(ULONG64* param1, ULONG64* param2, ULONG64 allocationPtr, ULONG64 allocationSize, ULONG64 mdlptr) {
	UNREFERENCED_PARAMETER(param1);
	UNREFERENCED_PARAMETER(param2);
	UNREFERENCED_PARAMETER(allocationPtr);
	UNREFERENCED_PARAMETER(allocationSize);
	UNREFERENCED_PARAMETER(mdlptr);
	
	
	/*
	This callback occurs before call driver entry and
	can be usefull to pass more customized params in 
	the last step of the mapping procedure since you 
	know now the mapping address and other things
	*/
	return true;
}

static INT Run_kdmapper()
{
	iqvw64e_device_handle = intel_driver::Load();

	if (iqvw64e_device_handle == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, skCrypt("FATAL ERROR 001"), skCrypt("ERROR 001"), NULL);
		exit(1);
		return -1;
	}



	NTSTATUS exitCode = 0;
	if (!kdmapper::MapDriver(iqvw64e_device_handle, (BYTE*)mydriver, sizeof(mydriver), 0, 0, false, true, false, false, callbackExample, &exitCode)) {
		RtlZeroMemory(&mydriver, sizeof(mydriver));
		intel_driver::Unload(iqvw64e_device_handle);

		MessageBoxA(NULL, skCrypt("FATAL ERROR 002"), skCrypt("ERROR 002"), NULL);
		exit(1);
		return -1;
	}
	RtlZeroMemory(&mydriver, sizeof(mydriver));
	intel_driver::Unload(iqvw64e_device_handle);


	return 0;
	//MessageBoxA(NULL, "Driver Loaded Successfully", "SUCCESS", NULL);
}

static DWORD WINAPI MapProc(LPVOID lpParam)
{
	int status = Run_kdmapper();
	if (status != 0)
	{
		MessageBoxA(NULL, skCrypt("FATAL ERROR 003"), skCrypt("ERROR 003"), NULL);
		exit(1);
	}
	Mapping_Complete = true;
	return status;
}

static void MapDriver()
{
	CreateThread(0, NULL, MapProc, (LPVOID)L"I", NULL, NULL);
}