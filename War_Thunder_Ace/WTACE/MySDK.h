#pragma once
#include "auth.hpp"
#include "skStr.h"

__forceinline void ChangeTitle()
{
	srand(time(0)); //Helps the rand() function out so it won't produce the same number every time.

	std::string title = ""; //Declare our title string
	for (int i = 0; i <= rand() % 40 + 6; i++)
	{
		title += (char)(rand() % 92);
	}
	SetConsoleTitleA(title.c_str()); //Set our console title to our string, use .c_str() to turn it into a LPCSTR.
}

__forceinline std::string randomstring()
{
	srand(time(0)); //Helps the rand() function out so it won't produce the same number every time.

	std::string title = ""; //Declare our title string
	for (int i = 0; i <= rand() % 40 + 6; i++)
	{
		title += (char)(rand() % 92 + 1);
	}
	return title;
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}

using namespace KeyAuth;

const std::string name = (std::string)skCrypt("");
const std::string ownerid = (std::string)skCrypt("");
const std::string secret = (std::string)skCrypt("");
const std::string version = (std::string)skCrypt("1.0");
const std::string url = "https://keyauth.win/api/1.2/";
std::string key = "";
std::string key2 = "";
bool finished = false;

api KeyAuthApp(name, ownerid, secret, version, url);

bool validation()
{
	AllocConsole();

	freopen(skCrypt("CON"), skCrypt("w"), stdout);
	freopen(skCrypt("CON"), skCrypt("r"), stdin);
	freopen(skCrypt("CON"), skCrypt("w"), stderr);
	std::string consoletitle = randomstring();
	SetConsoleTitleA((char*)consoletitle.c_str());
	while (!val.consolewindow)
		val.consolewindow = FindWindow(NULL, (char*)consoletitle.c_str());

	KeyAuthApp.init();
	Sleep(500);

	if (KeyAuthApp.data.message == "Version outdated")
	{
		int msg = MessageBoxA(NULL, skCrypt("Loader is outdated! Closing this window will redirect you to the newest loader"), skCrypt("Loader outdated"), MB_OK);
		system(skCrypt("start https://mega.nz/folder/e3BQDYJR#BVpQvgBJDw34t_rWkWTplA"));
		exit(1);
	}

	if (key2 == "")
	{
		std::cout << skCrypt("Please Enter Your Key: ");
		std::cin >> key2;
	}
	KeyAuthApp.license(key2);
	//KeyAuthApp.data.success = true;
	if (!KeyAuthApp.data.success)
	{
		key = key2;
		std::cout << skCrypt("\nInvalid key or hardware changed!");
		Sleep(1500);
		exit(0);
	}
	key = key2;
	

	std::string timemsg = tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.expiry)));
	/*std::cout << skCrypt("\nLogin Success");
	std::cout << skCrypt("\nSubscription expires: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.expiry)));
	std::cout << skCrypt("\nThis window will close in ");*/
	system("cls");
	system("Color 02");
	std::cout << skCrypt("Login Success");
	std::cout << skCrypt("\nSubscription expires: ") << timemsg;
	std::cout << skCrypt("\nThis window will close in ");
	for (int t = 5; t > 0; t--)
	{
		std::cout << to_string(t);
		Sleep(250);
		std::cout << ".";
		Sleep(250);
		std::cout << ".";
		Sleep(250);
		std::cout << ".";
		Sleep(250);
	}
	FreeConsole();
	//Sleep(5000);
	finished = true;
	PostMessage(val.consolewindow, WM_CLOSE, 0, 0);
	ChangeTitle();

	return true;
}

