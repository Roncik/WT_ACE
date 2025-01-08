#pragma once
#include "stdafx.h"
#include "Values.h"
#include "skStr.h"

typedef struct _CALL_STRUCT
{
	void* buff_address;
	ULONGLONG	size;
	UINT_PTR	address;
	int			check;
	BOOLEAN		write, read, req_base, antidebug;
	ULONG		pid;
	void* output;
	const char* module_name;
	ULONG64		base_address;
}CALL_STRUCT;

typedef __int64(__fastcall* function)(int a1, int a2, _CALL_STRUCT* a3);
function func;



struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};
using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

template<typename ... Arg> __forceinline uint64_t call_hook(const Arg ... args)
{
	//void* hooked_func = GetProcAddress(val.hmodule, skCrypt("NtQueryCompositionSurfaceStatistics")); //NtQueryCompositionSurfaceStatistics  NtSetCompositionSurfaceStatistics  NtGdiDdCanCreateSurface

	//auto func = static_cast<uint64_t(_fastcall*)(Arg...)>(val.Hooked_function_PTR);

	return func(args ...);
}

std::uint32_t get_process_id(std::string_view process_name)
{
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return NULL;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
	{
		if (process_name.compare(processentry.szExeFile) == NULL)
		{
			return processentry.th32ProcessID;
		}
	}
	return NULL;
}

static ULONG64 get_module_base_address(const char* module_name)
{
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454;
	instructions.pid = val.Process;
	instructions.req_base = TRUE;
	instructions.read = FALSE;
	instructions.write = FALSE;
	instructions.module_name = module_name;

	//call_hook(1900, &instructions);
	call_hook(40521, 176, &instructions);

	ULONG64 base = NULL;
	base = instructions.base_address;
	return base;

}

static ULONG64 get_module_size(const char* module_name)
{
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454;
	instructions.pid = val.Process;
	instructions.req_base = TRUE;
	instructions.read = FALSE;
	instructions.write = FALSE;
	instructions.module_name = module_name;

	//call_hook(1900, &instructions);
	call_hook(40521, 176, &instructions);

	ULONG64 size = NULL;
	size = instructions.size;
	return size;
}

template <class T> __forceinline T ReadPM(UINT_PTR read_address)
{
	T response{};
	/*CALL_STRUCT instructions = {
	NULL,
	sizeof(T),
	read_address,
	76542454,
	FALSE,
	TRUE,
	FALSE,
	FALSE,
	val.Process,
	&response,
	0,
	0};*/
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454;
	instructions.pid = val.Process;
	instructions.size = sizeof(T);
	instructions.address = read_address;
	instructions.read = TRUE;
	instructions.output = &response;

	call_hook(40521, 176, &instructions);

	return response;
}

template <class T> __forceinline T ReadPM_secure(UINT_PTR read_address, UINT_PTR read_size)
{
	T response{};
	if (read_size <= sizeof(T))
	{

		CALL_STRUCT instructions = {0};
		instructions.check = 76542454;
		instructions.pid = val.Process;
		instructions.size = read_size;
		instructions.address = read_address;
		instructions.read = TRUE;
		instructions.output = &response;

		call_hook(40521, 176, &instructions);
		return response;
	}
	else
		return response;
}

bool write_memory(UINT_PTR write_address, UINT_PTR source_address, SIZE_T write_size)
{
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454;
	instructions.address = write_address;
	instructions.pid = val.Process;
	instructions.write = TRUE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.buff_address = (void*)source_address;
	instructions.size = write_size;

	call_hook(40521, 176, &instructions);

	return true;

}

//template<typename S> bool write(UINT_PTR write_address, const S& value)
//{
//	return write_memory(write_address, (UINT_PTR)&value, sizeof(S));
//}

template<typename S> bool write(UINT_PTR write_address, const S& value)
{
	return NULL;
}


bool being_debugged_kernel()
{
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454;
	instructions.address = 0;
	instructions.pid = GetCurrentProcessId();
	instructions.write = FALSE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.antidebug = TRUE;
	instructions.base_address = 0;
	instructions.size = 0;

	call_hook(40521, 176, &instructions);

	if (instructions.address == 101)
		return true;
	else
		return false;
}

bool being_debugged_kernel_thread()
{
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454;
	instructions.address = 0;
	instructions.pid = GetCurrentThreadId();
	instructions.write = FALSE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.antidebug = TRUE;
	instructions.base_address = 0;
	instructions.size = 0;

	call_hook(40521, 176, &instructions);

	if (instructions.address == 101)
		return true;
	else
		return false;
}

template <class T> T ReadOwnProcessPM(UINT_PTR read_address)
{
	T response{};
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454;
	instructions.pid = GetCurrentProcessId();
	instructions.size = sizeof(T);
	instructions.address = read_address;
	instructions.read = TRUE;
	instructions.write = FALSE;
	instructions.req_base = FALSE;
	instructions.output = &response;

	call_hook(40521, 176, &instructions);

	return response;
}

bool WriteOwnProcessPM(UINT_PTR write_address, UINT_PTR source_address, SIZE_T write_size)
{
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454;
	instructions.address = write_address;
	instructions.pid = GetCurrentProcessId();
	instructions.write = TRUE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.buff_address = (void*)source_address;
	instructions.size = write_size;

	call_hook(40521, 176, &instructions);

	return true;

}

__forceinline void ForceBSOD()
{
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542354; //On Purpose
	instructions.address = 0;
	instructions.pid = 0;
	instructions.write = FALSE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.antidebug = TRUE;
	instructions.base_address = 200;

	call_hook(40521, 176, &instructions);
}

__forceinline void SetProtectedPID(DWORD pid)
{
	CALL_STRUCT instructions = { 0 };
	instructions.check = 76542454; //On Purpose
	instructions.address = 0;
	instructions.pid = pid;
	instructions.write = FALSE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.antidebug = TRUE;
	instructions.base_address = 0;

	call_hook(40521, 176, &instructions);
}