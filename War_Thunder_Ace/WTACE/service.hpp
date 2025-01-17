#pragma once
#include "stdafx.h"
#include "intel_driver.hpp"

namespace service
{
	bool RegisterAndStart(const std::wstring& driver_path);
	bool StopAndRemove(const std::wstring& driver_name);
};