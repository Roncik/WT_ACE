#pragma once
#include "stdafx.h"

#include "portable_executable.hpp"
#include "kdmapper_utils.hpp"
#include "nt.hpp"
#include "intel_driver.hpp"
#include "Encryption.h"

#define PAGE_SIZE 0x1000

namespace kdmapper
{
	typedef bool (*mapCallback)(ULONG64* param1, ULONG64* param2, ULONG64 allocationPtr, ULONG64 allocationSize, ULONG64 mdlptr);

	//Note: if you set PassAllocationAddressAsFirstParam as true, param1 will be ignored
	uint64_t MapDriver(HANDLE iqvw64e_device_handle, BYTE* data, int dataSize, ULONG64 param1, ULONG64 param2, bool free, bool destroyHeader, bool mdlMode, bool PassAllocationAddressAsFirstParam, mapCallback callback, NTSTATUS* exitCode);
	void RelocateImageByDelta(portable_executable::vec_relocs relocs, const uint64_t delta);
	bool ResolveImports(HANDLE iqvw64e_device_handle, portable_executable::vec_imports imports);
	uint64_t AllocMdlMemory(HANDLE iqvw64e_device_handle, uint64_t size, uint64_t* mdlPtr);
}