#pragma once
#include "Main.h"
#include "stdafx.h"
#include "skStr.h"



using namespace std;

namespace RegistryManager
{
	string replaceAll(string subject, const string& search,
		const string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	string DownloadString(string URL) {
		HINTERNET interwebs = InternetOpenA(skCrypt("Mozilla/5.0"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
		HINTERNET urlFile;
		string rtn;
		if (interwebs) {
			urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
			if (urlFile) {
				char buffer[2000];
				DWORD bytesRead;
				do {
					InternetReadFile(urlFile, buffer, 2000, &bytesRead);
					rtn.append(buffer, bytesRead);
					memset(buffer, 0, 2000);
				} while (bytesRead);
				InternetCloseHandle(interwebs);
				InternetCloseHandle(urlFile);
				string p = replaceAll(rtn, "|n", "\r\n");
				return p;
			}
		}
		InternetCloseHandle(interwebs);
		string p = replaceAll(rtn, "|n", "\r\n");
		return p;
	}
	LONG GetDWORDRegKey(HKEY hKey, const std::string& strValueName, DWORD& nValue, DWORD nDefaultValue)
	{
		nValue = nDefaultValue;
		DWORD dwBufferSize(sizeof(DWORD));
		DWORD nResult(0);
		LONG nError = RegQueryValueExA(hKey,
			strValueName.c_str(),
			0,
			NULL,
			reinterpret_cast<LPBYTE>(&nResult),
			&dwBufferSize);
		if (ERROR_SUCCESS == nError)
		{
			nValue = nResult;
		}
		return nError;
	}


	LONG GetBoolRegKey(HKEY hKey, const std::string& strValueName, bool& bValue, bool bDefaultValue)
	{
		DWORD nDefValue((bDefaultValue) ? 1 : 0);
		DWORD nResult(nDefValue);
		LONG nError = GetDWORDRegKey(hKey, strValueName.c_str(), nResult, nDefValue);
		if (ERROR_SUCCESS == nError)
		{
			bValue = (nResult != 0) ? true : false;
		}
		return nError;
	}


	LONG GetStringRegKey(HKEY hKey, const std::string& strValueName, std::string& strValue, const std::string& strDefaultValue)
	{
		strValue = strDefaultValue;
		CHAR szBuffer[512];
		DWORD dwBufferSize = sizeof(szBuffer);
		ULONG nError;
		nError = RegQueryValueExA(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
		if (ERROR_SUCCESS == nError)
		{
			strValue = szBuffer;
		}
		return nError;
	}


	DWORD get_vulnerabledriverblocklistenable()
	{
		HKEY hkey;
		DWORD VulnerableDriverBlocklistEnable;
		RegOpenKeyExA(HKEY_LOCAL_MACHINE, skCrypt("SYSTEM\\CurrentControlSet\\Control\\CI\\Config"), 0, KEY_READ, &hkey);
		if (GetDWORDRegKey(hkey, (std::string)skCrypt("VulnerableDriverBlocklistEnable"), VulnerableDriverBlocklistEnable, 0) != 0)
			return -1;
		return VulnerableDriverBlocklistEnable;
	}

	DWORD set_disable_vulnerabledriverblocklistenable()
	{
		HKEY hkey;
		DWORD Value = 0;
		RegOpenKeyExA(HKEY_LOCAL_MACHINE, skCrypt("SYSTEM\\CurrentControlSet\\Control\\CI\\Config"), 0, KEY_WRITE, &hkey);
		if (RegSetValueExA(hkey, skCrypt("VulnerableDriverBlocklistEnable"), 0, REG_DWORD, (const BYTE*)&Value, sizeof(Value)) != 0)
			return -1;
		return 0;
	}

	DWORD manager_vulnerabledriverblocklistenable()
	{
		DWORD current = get_vulnerabledriverblocklistenable();
		if (current == -1)
			return 1;
		else if (current == 1)
		{
			set_disable_vulnerabledriverblocklistenable();
			MessageBoxA(NULL, skCrypt("First launch setup complete. Restart your system to apply changes!"), skCrypt("Setup"), MB_OK);
			exit(0);
		}
		return 0;
	}

}