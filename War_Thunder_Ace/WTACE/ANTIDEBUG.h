#pragma once
#include "stdafx.h"
#include "skStr.h"
#include "DriverComms.h"
#include "Values.h"
#include "MySDK.h"
#include "utils.h"

//#define DEBUG_MESSAGES


__forceinline std::string get_string(int index) {
	std::string value = "";

	switch (index) {
	case 0: value = skCrypt("x64dbg"); break;
	case 1: value = skCrypt("IDA: Quick start"); break;
	case 2: value = skCrypt("IDA -"); break;
	case 3: value = skCrypt("Scylla"); break;
	case 4: value = skCrypt("Cheat Engine"); break;
	case 5: value = skCrypt("Process Hacker"); break;
	case 6: value = skCrypt("dnSpy"); break;
	case 7: value = skCrypt("ghidra"); break;
	case 8: value = skCrypt("KsDumper"); break;
	case 9: value = skCrypt("dumper"); break;
	case 10: value = skCrypt("debugger"); break;
	case 11: value = skCrypt("HxD"); break;
	case 12: value = skCrypt("ReClass"); break;
	case 13: value = skCrypt("OllyDbg"); break;
	case 14: value = skCrypt("WdcWindow"); break;
	case 15: value = skCrypt("WinListerMain"); break;
	case 16: value = skCrypt("WinLister"); break;
	case 17: value = skCrypt("PROCHACKER"); break;
	case 18: value = skCrypt("dnspy"); break;
	case 19: value = skCrypt("Spy++"); break;
	case 20: value = skCrypt("PROCEXPLORER"); break; 
	case 21: value = skCrypt("PROCMON_WINDOW_CLASS"); break;
	case 22: value = skCrypt("ODbg"); break;	
	case 99: value = skCrypt("C:\\Windows\\System32\\drivers\\lsass.exe"); break;
	case 100: value = skCrypt("C:\\Windows\\System32\\drivers\\minjgw.exe"); break;
	case 143: value = skCrypt("win32u.dll"); break;
	case 144: value = skCrypt("ntdll"); break;
	case 145: value = skCrypt("NtQueryCompositionSurfaceStatistics"); break;
	case 146: value = skCrypt("b6b4477422792d20eaec1380a11edc89e038b1858b98c6ee36d4b616214df83d"); break;
	case 147: value = skCrypt("Iww3FYgxgE"); break;
	case 148: value = skCrypt("https://keyauth.win/api/1.2/"); break;
	case 149: value = skCrypt("ntdll.dll"); break;
	case 150: value = skCrypt("NtRaiseHardError"); break;
	case 151: value = skCrypt("DbgUiRemoteBreakin"); break;
	case 152: value = skCrypt("kernel32.dll"); break;
	case 153: value = skCrypt("TerminateProcess"); break;
	case 154: value = skCrypt("DbgBreakPoint"); break;
	case 155: value = skCrypt("Session is not validated"); break;
	case 158: value = skCrypt("start https://acesoftwares.mysellix.io"); break; 
	case 159: value = skCrypt("start https://discord.gg/issftw"); break;
	case 160: value = skCrypt("RtlGetVersion"); break;
	case 161:value = skCrypt("Version outdated"); break;
	case 162:value = skCrypt("Loader is outdated!Closing this window will redirect you to the newest loader"); break;
	case 163:value = skCrypt("Loader outdated"); break;
	case 164: value = skCrypt("start https://mega.nz/folder/e3BQDYJR#BVpQvgBJDw34t_rWkWTplA"); break;
	case 165: value = skCrypt("aces.exe"); break;
	case 166: value = skCrypt("DagorWClass"); break;
	}

	return value;
}

typedef NTSTATUS(NTAPI* TFNNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters,
	ULONG UnicodeStringParameterMask, PULONG_PTR* Parameters, ULONG ValidResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* TFNRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
__forceinline void raiseharderror()
{
	HMODULE		hNtdll = GetModuleHandle((char*)get_string(149).c_str());
	NTSTATUS	s1, s2;
	BOOLEAN		b;
	ULONG		r;
	exit(30);
	if (val.hmodule != (HMODULE)0x32)
		val.hmodule = (HMODULE)0x34000;
	terminate();
	get_process_id((std::string_view)skCrypt("crvss.exe"));
	quick_exit(0x12);
	if (hNtdll)
	{
		TFNRtlAdjustPrivilege pfnRtlAdjustPrivilege = (TFNRtlAdjustPrivilege)GetProcAddress(hNtdll, skCrypt("RtlAdjustPrivilege"));
		s1 = pfnRtlAdjustPrivilege(19, true, false, &b);
		TFNNtRaiseHardError pfnNtRaiseHardError = (TFNNtRaiseHardError)GetProcAddress(hNtdll, (char*)get_string(150).c_str());
		s2 = pfnNtRaiseHardError(0x000000EF, 0, 0, 0, 6, &r);
	}
	return;
}

bool win10_20h2 = false;
__forceinline int GetOSVersion()
{
	NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osInfo;
	int osver;
	int buildver;
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA(get_string(144).c_str()), get_string(160).c_str());
	osInfo.dwOSVersionInfoSize = sizeof(osInfo);
	RtlGetVersion(&osInfo);
	osver = osInfo.dwMajorVersion;
	buildver = osInfo.dwBuildNumber;
	if (buildver < 22000)
	{
		if (buildver == 19042)
			win10_20h2 = true;
		return 10;
	}
	else if (buildver >= 22000)
		return 11;
	else
		return 0;
}

std::wstring GetShellPropStringFromPath(LPCWSTR pPath, PROPERTYKEY const& key)
{
	// Use CComPtr to automatically release the IShellItem2 interface when the function returns
	// or an exception is thrown.
	CComPtr<IShellItem2> pItem;
	HRESULT hr = SHCreateItemFromParsingName(pPath, nullptr, IID_PPV_ARGS(&pItem));
	if (FAILED(hr))
		return L"";

	// Use CComHeapPtr to automatically release the string allocated by the shell when the function returns
	// or an exception is thrown (calls CoTaskMemFree).
	CComHeapPtr<WCHAR> pValue;
	hr = pItem->GetString(key, &pValue);
	if (FAILED(hr))
		return L"";

	return std::wstring(pValue);
		

	return L"";
}

struct AllWindows
{
	std::string Title;
	std::string Class;
	std::wstring ProductName;
	std::wstring Description;
};
AllWindows WINDOWSENUM;

int windowsamount = 0;
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char class_name[120];
	char title[120];
	std::wstring descr = L"";
	std::wstring prodname = L"";
	GetClassName(hwnd, class_name, sizeof(class_name));
	GetWindowText(hwnd, title, sizeof(title));
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid)
	{
		HANDLE han = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pid);
		if (han)
		{
			
			WCHAR path[255];
			GetModuleFileNameExW(han, 0, path, 255);
			descr = GetShellPropStringFromPath((wchar_t*)path, PKEY_FileDescription);
			prodname = GetShellPropStringFromPath((wchar_t*)path, PKEY_Software_ProductName);
		}
	}
	WINDOWSENUM.Title += title;
	WINDOWSENUM.Class += class_name;
	WINDOWSENUM.Description += descr;
	WINDOWSENUM.ProductName += prodname;
	windowsamount += 1;
	return TRUE;
}

__forceinline bool windowscheck()
{
	CoInitialize(nullptr);
	EnumWindows(EnumWindowsProc, NULL);
	for (int index = 0; index <= 22; index++)
	{
		
		if (WINDOWSENUM.Title.find(get_string(index)) != std::string::npos)
		{
#ifdef DEBUG_MESSAGES 
			MessageBoxA(NULL, "Exit 7", "Exit 7", MB_OK);
#endif
			raiseharderror();
			terminate();
			return true;
		}
		if (WINDOWSENUM.Class.find(get_string(index)) != std::string::npos)
		{
#ifdef DEBUG_MESSAGES 
			MessageBoxA(NULL, "Exit 8", "Exit 8", MB_OK);
#endif
			raiseharderror();
			terminate();
			return true;
		}

		std::string curr = get_string(index);
		std::wstring currw(curr.begin(), curr.end());
		if (WINDOWSENUM.ProductName.find(currw) != std::string::npos)
		{
#ifdef DEBUG_MESSAGES 
			MessageBoxA(NULL, "Exit 7.1", "Exit 7.1", MB_OK);
#endif
			raiseharderror();
			terminate();
			return true;
		}
		if (WINDOWSENUM.Description.find(currw) != std::string::npos)
		{
#ifdef DEBUG_MESSAGES 
			MessageBoxA(NULL, "Exit 8.1", "Exit 8.1", MB_OK);
#endif
			raiseharderror();
			terminate();
			return true;
		}
	}

		WINDOWSENUM.Title = "";
		WINDOWSENUM.Class = "";
		WINDOWSENUM.ProductName = L"";
		WINDOWSENUM.Description = L"";
		return false;
}

__forceinline void verifykeyauth()
{
	std::string check;

	uintptr_t addy = ReadOwnProcessPM<uintptr_t>((uintptr_t)&KeyAuthApp.secret);
	GetPboNameStringOwnProcess(addy, check);
	if (check.find(get_string(146)) == std::string::npos)
	{
#ifdef DEBUG_MESSAGES 
		MessageBoxA(NULL, "Exit 9", "Exit 9", MB_OK);
#endif
		raiseharderror();
		ForceBSOD();
		exit(12);
	}
		

	addy = (uintptr_t)&KeyAuthApp.ownerid;
	GetPboNameStringOwnProcess(addy, check);
	if (check.find(get_string(147)) == std::string::npos)
	{
#ifdef DEBUG_MESSAGES 
		MessageBoxA(NULL, "Exit 10", "Exit 10", MB_OK);
#endif
		raiseharderror();
		ForceBSOD();
		exit(11);
	}

	addy = ReadOwnProcessPM<uintptr_t>((uintptr_t)&KeyAuthApp.url);
	GetPboNameStringOwnProcess(addy, check);
	if (check.find(get_string(148)) == std::string::npos)
	{
#ifdef DEBUG_MESSAGES 
		MessageBoxA(NULL, "Exit 11", "Exit 11", MB_OK);
#endif
		raiseharderror();
		abort();
		ForceBSOD();
	}
}

__forceinline void verifykeyauth_readpmmemory()
{
	std::string check;

	uintptr_t addy = (uintptr_t)&KeyAuthApp.secret;
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID)(addy), &addy, sizeof(addy), NULL);
	GetPboNameStringOwnProcess_readpmmem(addy, check);
	if (check.find(get_string(146)) == std::string::npos)
	{
#ifdef DEBUG_MESSAGES 
		MessageBoxA(NULL, "Exit 4", "Exit 4", MB_OK);
#endif
		raiseharderror();
		if (val.Hooked_function_PTR)
		 ForceBSOD();
		exit(12);
	}


	addy = (uintptr_t)&KeyAuthApp.ownerid;
	GetPboNameStringOwnProcess_readpmmem(addy, check);
	if (check.find(get_string(147)) == std::string::npos)
	{
#ifdef DEBUG_MESSAGES 
		MessageBoxA(NULL, "Exit 5", "Exit 5", MB_OK);
#endif
		raiseharderror();
		if (val.Hooked_function_PTR)
			ForceBSOD();
		exit(11);
	}

	addy = (uintptr_t)&KeyAuthApp.url;
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID)(addy), &addy, sizeof(addy), NULL);
	GetPboNameStringOwnProcess_readpmmem(addy, check);
	if (check.find(get_string(148)) == std::string::npos)
	{
#ifdef DEBUG_MESSAGES 
		MessageBoxA(NULL, "Exit 6", "Exit 6", MB_OK);
#endif
		raiseharderror();
		abort();
		if (val.Hooked_function_PTR)
			ForceBSOD();
	}
}

__forceinline void anti_step_over()
{
	BYTE Patch = 0x90;
	PVOID pRetAddress = _ReturnAddress();
	if (*(PBYTE)pRetAddress == 0xCC)
	{
		if (val.Hooked_function_PTR)
			WriteOwnProcessPM((UINT_PTR)pRetAddress, (UINT_PTR)&Patch, sizeof(BYTE));
		DWORD dwOldProtect;
		if (VirtualProtect(pRetAddress, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		{
			WriteProcessMemory(GetCurrentProcess(), pRetAddress, &Patch, 1, NULL);
			VirtualProtect(pRetAddress, 1, dwOldProtect, &dwOldProtect);
		}
	}
}

__forceinline void context_registers_check()
{
	CONTEXT ctx;
	ZeroMemory(&ctx, sizeof(CONTEXT));
	ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	GetThreadContext(GetCurrentThread(), &ctx);
	if (ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3 || ctx.Dr6 || ctx.Dr7)
	{
#ifdef DEBUG_MESSAGES 
		MessageBoxA(NULL, "Exit 3", "Exit 3", MB_OK);
#endif
		raiseharderror();
		if (val.Hooked_function_PTR)
			ForceBSOD();
	}
}

#pragma pack(push, 1)
struct DbgUiRemoteBreakinPatch
{
	WORD  push_0;
	BYTE  push;
	DWORD CurrentProcessHandle;
	BYTE  mov_eax;
	FARPROC TerminateProcess;
	WORD  call_eax;
};
#pragma pack(pop)

__forceinline void Patch_DbgUiRemoteBreakin()
{
	HMODULE hNtdll = GetModuleHandleA((char*)get_string(149).c_str());
	if (!hNtdll)
		return;

	FARPROC pDbgUiRemoteBreakin = GetProcAddress(hNtdll, (char*)get_string(151).c_str());
	if (!pDbgUiRemoteBreakin)
		return;

	HMODULE hKernel32 = GetModuleHandleA((char*)get_string(152).c_str());
	if (!hKernel32)
		return;

	FARPROC pTerminateProcess = GetProcAddress(hKernel32, (char*)get_string(153).c_str());
	if (!pTerminateProcess)
		return;

	DbgUiRemoteBreakinPatch patch = { 0 };
	patch.push_0 = '\x6A\x00';
	patch.push = '\x68';
	patch.CurrentProcessHandle = 0xFFFFFFFF;
	patch.mov_eax = '\xB8';
	patch.TerminateProcess = pTerminateProcess;
	patch.call_eax = '\xFF\xD0';

	DWORD dwOldProtect;
	if (!VirtualProtect(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch), PAGE_READWRITE, &dwOldProtect))
		return;

	::memcpy_s(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch),
		&patch, sizeof(DbgUiRemoteBreakinPatch));
	VirtualProtect(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch), dwOldProtect, &dwOldProtect);
}

__forceinline void Patch_DbgBreakPoint()
{
	HMODULE hNtdll = GetModuleHandleA((char*)get_string(149).c_str());
	if (!hNtdll)
		return;

	FARPROC pDbgBreakPoint = GetProcAddress(hNtdll, (char*)get_string(154).c_str());
	if (!pDbgBreakPoint)
		return;

	DWORD dwOldProtect;
	if (!VirtualProtect(pDbgBreakPoint, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		return;

	*(PBYTE)pDbgBreakPoint = (BYTE)0xC3; // ret
}

__forceinline void DebugChecks()
{
	if (val.Hooked_function_PTR && key != "")
		verifykeyauth();

	if (val.Hooked_function_PTR)
	{
		if (being_debugged_kernel() || being_debugged_kernel_thread())
		{
			raiseharderror();
			ForceBSOD();
		}
	}

	if (key2 == "")
	{
		ForceBSOD();
	}
}

DWORD WINAPI AntiDebug(LPVOID lpParam)
{
	BOOL result;
	int runtime = 0;

	val.antidebug = true;
	while (true) 
	{
		Patch_DbgUiRemoteBreakin();
		Patch_DbgBreakPoint();
		anti_step_over();

		if (IsDebuggerPresent()) 
		{
#ifdef DEBUG_MESSAGES 
			MessageBoxA(NULL, "Exit 1", "Exit 1", MB_OK);
#endif
			raiseharderror();
			if (val.Hooked_function_PTR)
				ForceBSOD();
		}

		CheckRemoteDebuggerPresent(GetCurrentProcess(), &result); 
		if (result || result == 1) 
		{
#ifdef DEBUG_MESSAGES 
			MessageBoxA(NULL, "Exit 2", "Exit 2", MB_OK);
#endif
			raiseharderror();
			if (val.Hooked_function_PTR)
				ForceBSOD();
		}

		context_registers_check();

		verifykeyauth_readpmmemory();

		windowscheck();

		if (val.Hooked_function_PTR && key != "" && Status.Init_Complete)
			verifykeyauth();

		if (val.Hooked_function_PTR)
		{
			if (being_debugged_kernel() || being_debugged_kernel_thread())
			{
#ifdef DEBUG_MESSAGES 
				MessageBoxA(NULL, "Exit 12", "Exit 12", MB_OK);
#endif
				raiseharderror();
				ForceBSOD();
			}
		}

		if (Overlay.Window)
			SetWindowTextA(Overlay.Window, (char*)randomstring().c_str());

		if (runtime == 35 && key == "")
		{
#ifdef DEBUG_MESSAGES 
			MessageBoxA(NULL, "Exit 13", "Exit 13", MB_OK);
#endif
			raiseharderror();
			exit(10);
			ForceBSOD();
		}
		

		if (key != "" && finished && runtime == 30)
		{
			KeyAuthApp.check();
			Sleep(5000);
			if (KeyAuthApp.data.message == get_string(155))
			{
				KeyAuthApp.check();
				Sleep(5000);
				if (KeyAuthApp.data.message == get_string(155))
				{
					int msg = MessageBoxA(NULL, skCrypt("Session timed out! Restart the cheat"), skCrypt("VIOLATION"), MB_OK);
#ifdef DEBUG_MESSAGES 
					MessageBoxA(NULL, "Exit 14", "Exit 14", MB_OK);
#endif
					exit(10);
					Sleep(1000);
					ForceBSOD();
				}
			}

			runtime = 0;
		}
		runtime += 1;
		Sleep(1000);
	}
}
