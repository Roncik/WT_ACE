#pragma once
#include "DirectX.h"
#include "Vectors.h"
#include "Values.h"
#include "DriverComms.h"
#include "icons.h"
#include "VirtualKeysList.h"
#include "stdafx.h"


 void ReadConfig()
{
	ifstream File;
	File.open("config.txt");
	if (File.is_open())
	{
		std::string line;
		int integer;
		float floatval;

		File >> line; //GETS KEY
		if (line != "key")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		key2 = line;

		File >> line; //NameEsp
		if (line != "NameEsp")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.NAMEESP = true;

		File >> line; //NameEsp_Name
		if (line != "NameEsp_Name")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.NAMEESP_name = true;
		else if (line == "false")
			Status.NAMEESP_name = false;

		File >> line; //NameEsp_VehicleName
		if (line != "NameEsp_VehicleName")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.NAMEESP_vehiclename = true;
		else if (line == "false")
			Status.NAMEESP_vehiclename = false;

		File >> line; //NameEsp_Distance
		if (line != "NameEsp_Distance")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.NAMEESP_distance = true;
		else if (line == "false")
			Status.NAMEESP_distance = false;

		File >> line; //NameEsp_FlareCount
		if (line != "NameEsp_FlareCount")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.NAMEESP_flarecounter = true;
		else if (line == "false")
			Status.NAMEESP_flarecounter = false;

		File >> line; //NameEsp_reloading/cantshoot
		if (line != "NameEsp_reloading/cantshoot")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.NAMEESP_isreloading_cantshoot = true;
		else if (line == "false")
			Status.NAMEESP_isreloading_cantshoot = false;

		File >> line; //ShowFriendlies 
		if (line != "ShowFriendlies")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.showfriendly = true;

		File >> line; //Boxes 
		if (line != "Boxes")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.BoxESP = true;

		File >> line; //Snaplines
		if (line != "Snaplines")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.snaplines = true;

		File >> line; //Prediction 
		if (line != "Prediction")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.prediction = true;

		File >> line; //PlayerList
		if (line != "PlayerList")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.nearby_warning = true;

		File >> line; //PlayerListDistance
		if (line != "PlayerListDistance")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> integer;
		val.nearbydistance = integer;

		File >> line; //PartChams
		if (line != "PartChams")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.parts_esp = true;

		File >> line; //PartChams_body 
		if (line != "PartChams_body")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.parts_body = true;

		File >> line; //PartChams_ammo 
		if (line != "PartChams_ammo")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.parts_ammo = true;

		File >> line; //PartChams_crew 
		if (line != "PartChams_crew")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.parts_crew = true;

		File >> line; //PartChams_engine 
		if (line != "PartChams_engine")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.parts_engine = true;

		File >> line; //PartChams_RenderToPrediction 
		if (line != "PartChams_RenderToPrediction")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.parts_RenderToPrediction = true;

		File >> line; //PartChams_ShowMyTank 
		if (line != "PartChams_ShowMyTank")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.parts_showmytank = true;

		File >> line; //MissileESP 
		if (line != "MissileESP")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.MissileESP = true;

		File >> line; //CCIPs 
		if (line != "CCIPs")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.SuperStats = true;

		File >> line; //AimAssist 
		if (line != "AimAssist")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.aimassist = true;

		File >> line; //EnemyMarkers 
		if (line != "EnemyMarkers")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.enemymarkers = true;

		File >> line; //MouseAiminSim 
		if (line != "MouseAiminSim")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.aimmodeinsim = true;

		File >> line; //BombIndicator  
		if (line != "BombIndicator")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.bomb_indicator = true;

		File >> line; //AutoBomb  
		if (line != "AutoBomb")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.automaticbomb = true;

		File >> line; //ZoomChanger  
		if (line != "ZoomChanger")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.ExtraZoom = true;

		File >> line; //ZoomMultiplier  
		if (line != "ZoomMultiplier")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> floatval;
		val.Zoom_mult = floatval;

		File >> line; //NoScopeShadow   
		if (line != "NoScopeShadow")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.NoScopeShadow = true;

		File >> line; //AutoTargetPoint   
		if (line != "AutoTargetPoint")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.SlaveTargetPoint = true;

		File >> line; //CameraChanger   
		if (line != "CameraChanger")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.ChangeCameraPosition = true;

		File >> line; //CameraChanger_X   
		if (line != "CameraChanger_X")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> floatval;
		val.CameraX = floatval;

		File >> line; //CameraChanger_Y   
		if (line != "CameraChanger_Y")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> floatval;
		val.CameraY = floatval;

		File >> line; //AimbotHotkey 
		if (line != "AimbotHotkey")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> integer;
		val.aimbotkey = integer;

		File >> line; //AutoBombHotkey 
		if (line != "AutoBombHotkey")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> integer;
		val.autobombkey = integer;

		File >> line; //MenuHotkey 
		if (line != "MenuHotkey")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> integer;
		val.menukey = integer;

		File >> line; //ATPHotKey
		if (line != "ATPHotkey")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> integer;
		val.autotargetpointogglekey = integer;

		File >> line; //CloseCheatHotkey 
		if (line != "CloseCheatHotkey")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> integer;
		val.closecheatkey = integer;

		File >> line; //FrameLimiter  
		if (line != "FrameLimiter")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		if (line == "true")
			Status.framelimiter = true;

		File >> line; //EnemyName_COLOR
		if (line != "EnemyName_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.EnemyName.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.EnemyName.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.EnemyName.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.EnemyName.b = floatval / 255.f;
		File >> line;

		File >> line; //FriendlyName_COLOR 
		if (line != "FriendlyName_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.FriendlyName.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.FriendlyName.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.FriendlyName.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.FriendlyName.b = floatval / 255.f;
		File >> line;

		File >> line; //VehicleName_COLOR 
		if (line != "VehicleName_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.VehicleName.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.VehicleName.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.VehicleName.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.VehicleName.b = floatval / 255.f;
		File >> line;

		File >> line; //Distance_COLOR 
		if (line != "Distance_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Distance.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Distance.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Distance.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Distance.b = floatval / 255.f;
		File >> line;

		File >> line; //Box_COLOR 
		if (line != "Box_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.BoxColour.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.BoxColour.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.BoxColour.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.BoxColour.b = floatval / 255.f;
		File >> line;

		File >> line; //Parts_Crew_COLOR 
		if (line != "Parts_Crew_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Crew.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Crew.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Crew.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Crew.b = floatval / 255.f;
		File >> line;

		File >> line; //Parts_Body_COLOR 
		if (line != "Parts_Body_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Body.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Body.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Body.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Body.b = floatval / 255.f;
		File >> line;

		File >> line; //Parts_Ammo_COLOR 
		if (line != "Parts_Ammo_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Ammo.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Ammo.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Ammo.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Ammo.b = floatval / 255.f;
		File >> line;

		File >> line; //Parts_Engine_COLOR 
		if (line != "Parts_Engine_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Engine.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Engine.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Engine.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Engine.b = floatval / 255.f;
		File >> line;

		File >> line; //Parts_Barrel_COLOR 
		if (line != "Parts_Barrel_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Barrel.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Barrel.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Barrel.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Parts_Barrel.b = floatval / 255.f;
		File >> line;

		File >> line; //PlayerList_COLOR 
		if (line != "PlayerList_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.PlayerList.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.PlayerList.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.PlayerList.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.PlayerList.b = floatval / 255.f;
		File >> line;

		File >> line; //Cantshoot/Reloading_COLOR
		if (line != "Cantshoot/Reloading_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Cantshoot_reloading.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Cantshoot_reloading.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Cantshoot_reloading.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.Cantshoot_reloading.b = floatval / 255.f;
		File >> line;

		File >> line; //SnapLines_Friendly_COLOR
		if (line != "SnapLines_Friendly_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.SnapLines_Friendly.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.SnapLines_Friendly.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.SnapLines_Friendly.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.SnapLines_Friendly.b = floatval / 255.f;
		File >> line;

		File >> line; //SnapLines_Enemy_COLOR
		if (line != "SnapLines_Enemy_COLOR")
		{
			MessageBoxA(NULL, "Invalid config format, save a new one", "Invalid config format", MB_OK);
			File.close();
			return;
		}
		File >> line;
		File >> line;
		File >> line;
		File >> floatval;
		clr.SnapLines_Enemy.a = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.SnapLines_Enemy.r = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.SnapLines_Enemy.g = floatval / 255.f;
		File >> line;
		File >> line;
		File >> floatval;
		clr.SnapLines_Enemy.b = floatval / 255.f;
		File >> line;
	}
	File.close();
}

void ExportConfig()
{
	ofstream File("config.txt", std::ofstream::out);

	if (File.is_open())
	{
		std::string line;
		int integer;
		float floatval;

		File << "key"; //GETS KEY
		File << " = ";
		if (key2 != "")
			File << key2;
		else
			File << "ERROR_KEY_NOT_FOUND";
		File << "\n";

		File << "NameEsp";
		File << " = ";
		if (Status.NAMEESP == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "NameEsp_Name";
		File << " = ";
		if (Status.NAMEESP_name == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "NameEsp_VehicleName";
		File << " = ";
		if (Status.NAMEESP_vehiclename == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "NameEsp_Distance";
		File << " = ";
		if (Status.NAMEESP_distance == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "NameEsp_FlareCount";
		File << " = ";
		if (Status.NAMEESP_flarecounter == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "NameEsp_reloading/cantshoot";
		File << " = ";
		if (Status.NAMEESP_isreloading_cantshoot == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "ShowFriendlies";
		File << " = ";
		if (Status.showfriendly == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "Boxes";
		File << " = ";
		if (Status.BoxESP == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "Snaplines";
		File << " = ";
		if (Status.snaplines == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "Prediction";
		File << " = ";
		if (Status.prediction == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "PlayerList";
		File << " = ";
		if (Status.nearby_warning == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "PlayerListDistance";
		File << " = ";
		File << val.nearbydistance;
		File << "\n";

		File << "PartChams";
		File << " = ";
		if (Status.parts_esp == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "PartChams_body";
		File << " = ";
		if (Status.parts_body == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "PartChams_ammo";
		File << " = ";
		if (Status.parts_ammo == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "PartChams_crew";
		File << " = ";
		if (Status.parts_crew == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "PartChams_engine";
		File << " = ";
		if (Status.parts_engine == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "PartChams_RenderToPrediction";
		File << " = ";
		if (Status.parts_RenderToPrediction == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "PartChams_ShowMyTank";
		File << " = ";
		if (Status.parts_showmytank == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "MissileESP";
		File << " = ";
		if (Status.MissileESP == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "CCIPs";
		File << " = ";
		if (Status.SuperStats == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "AimAssist";
		File << " = ";
		if (Status.aimassist == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "EnemyMarkers";
		File << " = ";
		if (Status.enemymarkers == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "MouseAiminSim";
		File << " = ";
		if (Status.aimmodeinsim == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "BombIndicator";
		File << " = ";
		if (Status.bomb_indicator == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "AutoBomb";
		File << " = ";
		if (Status.automaticbomb == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "ZoomChanger";
		File << " = ";
		if (Status.ExtraZoom == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "ZoomMultiplier";
		File << " = ";
		File << val.Zoom_mult;
		File << "\n";

		File << "NoScopeShadow";
		File << " = ";
		if (Status.NoScopeShadow == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "AutoTargetPoint";
		File << " = ";
		if (Status.SlaveTargetPoint == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "CameraChanger";
		File << " = ";
		if (Status.ChangeCameraPosition == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "CameraChanger_X";
		File << " = ";
		File << val.CameraX;
		File << "\n";

		File << "CameraChanger_Y";
		File << " = ";
		File << val.CameraY;
		File << "\n";

		File << "AimbotHotkey";
		File << " = ";
		File << val.aimbotkey;
		File << "\n";

		File << "AutoBombHotkey";
		File << " = ";
		File << val.autobombkey;
		File << "\n";

		File << "MenuHotkey";
		File << " = ";
		File << val.menukey;
		File << "\n";

		File << "ATPHotkey";
		File << " = ";
		File << val.autotargetpointogglekey;
		File << "\n";

		File << "CloseCheatHotkey";
		File << " = ";
		File << val.closecheatkey;
		File << "\n";

		File << "FrameLimiter";
		File << " = ";
		if (Status.framelimiter == true)
			File << "true";
		else
			File << "false";
		File << "\n";

		File << "EnemyName_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.EnemyName.a * 255.f;
		File << " | R: ";
		File << clr.EnemyName.r * 255.f;
		File << " | G: ";
		File << clr.EnemyName.g * 255.f;
		File << " | B: ";
		File << clr.EnemyName.b * 255.f;
		File << " }";
		File << "\n";

		File << "FriendlyName_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.FriendlyName.a * 255.f;
		File << " | R: ";
		File << clr.FriendlyName.r * 255.f;
		File << " | G: ";
		File << clr.FriendlyName.g * 255.f;
		File << " | B: ";
		File << clr.FriendlyName.b * 255.f;
		File << " }";
		File << "\n";

		File << "VehicleName_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.VehicleName.a * 255.f;
		File << " | R: ";
		File << clr.VehicleName.r * 255.f;
		File << " | G: ";
		File << clr.VehicleName.g * 255.f;
		File << " | B: ";
		File << clr.VehicleName.b * 255.f;
		File << " }";
		File << "\n";

		File << "Distance_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.Distance.a * 255.f;
		File << " | R: ";
		File << clr.Distance.r * 255.f;
		File << " | G: ";
		File << clr.Distance.g * 255.f;
		File << " | B: ";
		File << clr.Distance.b * 255.f;
		File << " }";
		File << "\n";

		File << "Box_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.BoxColour.a * 255.f;
		File << " | R: ";
		File << clr.BoxColour.r * 255.f;
		File << " | G: ";
		File << clr.BoxColour.g * 255.f;
		File << " | B: ";
		File << clr.BoxColour.b * 255.f;
		File << " }";
		File << "\n";

		File << "Parts_Crew_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.Parts_Crew.a * 255.f;
		File << " | R: ";
		File << clr.Parts_Crew.r * 255.f;
		File << " | G: ";
		File << clr.Parts_Crew.g * 255.f;
		File << " | B: ";
		File << clr.Parts_Crew.b * 255.f;
		File << " }";
		File << "\n";

		File << "Parts_Body_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.Parts_Body.a * 255.f;
		File << " | R: ";
		File << clr.Parts_Body.r * 255.f;
		File << " | G: ";
		File << clr.Parts_Body.g * 255.f;
		File << " | B: ";
		File << clr.Parts_Body.b * 255.f;
		File << " }";
		File << "\n";

		File << "Parts_Ammo_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.Parts_Ammo.a * 255.f;
		File << " | R: ";
		File << clr.Parts_Ammo.r * 255.f;
		File << " | G: ";
		File << clr.Parts_Ammo.g * 255.f;
		File << " | B: ";
		File << clr.Parts_Ammo.b * 255.f;
		File << " }";
		File << "\n";

		File << "Parts_Engine_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.Parts_Engine.a * 255.f;
		File << " | R: ";
		File << clr.Parts_Engine.r * 255.f;
		File << " | G: ";
		File << clr.Parts_Engine.g * 255.f;
		File << " | B: ";
		File << clr.Parts_Engine.b * 255.f;
		File << " }";
		File << "\n";

		File << "Parts_Barrel_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.Parts_Barrel.a * 255.f;
		File << " | R: ";
		File << clr.Parts_Barrel.r * 255.f;
		File << " | G: ";
		File << clr.Parts_Barrel.g * 255.f;
		File << " | B: ";
		File << clr.Parts_Barrel.b * 255.f;
		File << " }";
		File << "\n";

		File << "PlayerList_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.PlayerList.a * 255.f;
		File << " | R: ";
		File << clr.PlayerList.r * 255.f;
		File << " | G: ";
		File << clr.PlayerList.g * 255.f;
		File << " | B: ";
		File << clr.PlayerList.b * 255.f;
		File << " }";
		File << "\n";

		File << "Cantshoot/Reloading_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.Cantshoot_reloading.a * 255.f;
		File << " | R: ";
		File << clr.Cantshoot_reloading.r * 255.f;
		File << " | G: ";
		File << clr.Cantshoot_reloading.g * 255.f;
		File << " | B: ";
		File << clr.Cantshoot_reloading.b * 255.f;
		File << " }";
		File << "\n";

		File << "SnapLines_Friendly_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.SnapLines_Friendly.a * 255.f;
		File << " | R: ";
		File << clr.SnapLines_Friendly.r * 255.f;
		File << " | G: ";
		File << clr.SnapLines_Friendly.g * 255.f;
		File << " | B: ";
		File << clr.SnapLines_Friendly.b * 255.f;
		File << " }";
		File << "\n";

		File << "SnapLines_Enemy_COLOR";
		File << " = ";
		File << "{ A: ";
		File << clr.SnapLines_Enemy.a * 255.f;
		File << " | R: ";
		File << clr.SnapLines_Enemy.r * 255.f;
		File << " | G: ";
		File << clr.SnapLines_Enemy.g * 255.f;
		File << " | B: ";
		File << clr.SnapLines_Enemy.b * 255.f;
		File << " }";
		File << "\n";

		File << "\n";
		File << "FILE HAS TO BE NAMED config.txt !";
		File << "\n";
		File << "FILE HAS TO BE IN THE SAME FOLDER AS THE .EXE";
		File << "\n";
		File << "DO NOT CHANGE THE FORMAT, ORDER, NAMES OF THE SETTINGS";
		File << "\n";
		File << "true = enabled";
		File << "\n";
		File << "false = disabled";
		File << "\n";
		File << "Hotkey values are Virtual-Key Codes";
		File << "\n";
		File << "This config is exported";
	}
	File.close();
}

__forceinline std::string get_string_v2(int index) {
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
	case 99: value = skCrypt("C:\\Windows\\System32\\drivers\\lsass.exe"); break;
	case 143: value = skCrypt("win32u.dll"); break;
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
	case 156: value = skCrypt("start https://discord.gg/bngWQBy3Hw"); break;
	case 157: value = skCrypt("WarThunder Ace"); break;
	case 158: value = skCrypt("WarThunder"); break;
	
	}

	return value;
}

template <class type>
void write_if_not(uintptr_t address, type value)
{
	if (ReadPM<type>(address) != value)
		write<type>(address, value);
	return;
}

template <class type>
void write_protected_if_not(uintptr_t address, type value)
{
	if (ReadPM<type>(address) != value)
		write_protected<type>(address, value);
	return;
}

void DrawLineVec3(Vector3 one, Vector3 two, D3DCOLOR color, float thickness)
{
	Drawing::Line(one.x, one.y, two.x, two.y, color, thickness);
}

void DrawText(const char* text, float x, float y, D3DCOLOR color, ID3DXFont* font)
{
	RECT rect;

	SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
	font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	SetRect(&rect, x, y, x, y);
	font->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, color);
}

void DrawText_W(const wchar_t* text, float x, float y, D3DCOLOR color, ID3DXFont* font)
{
	RECT rect;

	SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
	font->DrawTextW(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	SetRect(&rect, x, y, x, y);
	font->DrawTextW(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, color);
}

void DrawTextnoncenter(const char* text, float x, float y, D3DCOLOR color, ID3DXFont* font)
{
	RECT rect;

	SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
	font->DrawTextA(NULL, text, -1, &rect, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));

	SetRect(&rect, x, y, x, y);
	font->DrawTextA(NULL, text, -1, &rect, DT_NOCLIP, color);
}

Vector3 Normalizescreenpos(Vector3 Screenpos)
{
	Vector3 output;
	output.x = Screenpos.x - Overlay.OffsetLeft;
	output.y = Screenpos.y - Overlay.OffsetTop;
	return output;
}

template <typename T>
bool inline IsBetween(T value, T min, T max)
{
	return (value < max) && (value > min);
}

template <typename T>
bool inline IsBetweenRange(T value, T range)
{
	return (value < (value + range)) && (value > (value - range));
}

inline bool is_ASCII(char character)
{
	return (IsBetween<uint8_t>(character, 31, 128));
}

int assign_size(int size)
{
	if (size > 0 && size < 1000000)
		return size;
	else
		return 0;
}

struct namestruct
{
	char name[100];
};
inline bool GetPboNameString(uintptr_t address, std::string& out)
{
	namestruct namech = ReadPM<namestruct>(address);
	std::string string;
	for (int i = 0; i <= 99; i++)
	{
		if (namech.name[i] != '\0')
		{
			/*if (namech.name[i] == '\x5F')
				namech.name[i] = '\x2D';
			string += toupper(namech.name[i]);*/
			string += namech.name[i];
		}
		else
			break;
	}
	out = string;
	return true;

}
inline bool GetPboNameStringOwnProcess(uintptr_t address, std::string& out)
{
	namestruct namech = ReadOwnProcessPM<namestruct>(address);
	std::string string;
	for (int i = 0; i <= 99; i++)
	{
		if (namech.name[i] != '\0')
		{
			/*if (namech.name[i] == '\x5F')
				namech.name[i] = '\x2D';
			string += toupper(namech.name[i]);*/
			string += namech.name[i];
		}
		else
			break;
	}
	out = string;
	return true;

}
inline bool GetPboNameStringOwnProcess_readpmmem(uintptr_t address, std::string& out)
{
	namestruct namech;
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID)address, &namech, sizeof(namestruct), NULL);
	std::string string;
	for (int i = 0; i <= 99; i++)
	{
		if (namech.name[i] != '\0')
		{
			string += namech.name[i];
		}
		else
			break;
	}
	out = string;
	return true;
}
inline bool GetPboNameStringASCII(uintptr_t address, std::string& out)
{
	namestruct namech = ReadPM<namestruct>(address);
	std::string string;
	for (int i = 0; i <= 99; i++)
	{
		if (namech.name[i] != '\0')
		{
			if (is_ASCII(namech.name[i]))
			string += namech.name[i];
		}
		else
			break;
	}
	out = string;
	return true;

}

struct wnamestruct
{
	wchar_t name[100];
};
inline bool GetPboNameWString(uintptr_t address, std::wstring& out)
{
	wnamestruct namech = ReadPM<wnamestruct>(address);
	std::wstring string;
	for (int i = 0; i <= 99; i++)
	{
		if (namech.name[i] != '\0')
		{
			/*if (namech.name[i] == '\x5F')
				namech.name[i] = '\x2D';
			string += toupper(namech.name[i]);*/
			string += namech.name[i];
		}
		else
			break;
	}
	out = string;
	return true;
}

inline int GetDistance(Vector3 first, Vector3 second)
{
	return sqrt(pow((first.x - second.x), 2) + pow((first.y - second.y), 2) + pow((first.z - second.z), 2));
}

inline float GetDistance2D(Vector2 first, Vector2 second)
{
	return sqrt(pow((first.x - second.x), 2) + pow((first.y - second.y), 2));
}

Vector2 getScreenCentre()
{
	return Vector2{ (float)(Target.width / 2) - Overlay.OffsetLeft , (float)(Target.height / 2) - Overlay.OffsetTop };
}

void ClickOnScreen(Vector2 ScreenPos)
{
	int x, y;
	x = MulDiv(ScreenPos.x, 65535, Target.width);
	y = MulDiv(ScreenPos.y, 65535, Target.height);

	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x, y, NULL, NULL);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
}

void AimOnScreen(Vector2 ScreenPos)
{
	int x, y;
	x = MulDiv(ScreenPos.x, 65535, Target.width);
	y = MulDiv(ScreenPos.y, 65535, Target.height);

	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x, y, NULL, NULL);
	return;
}

void ClickKey(uint32_t VK, uint32_t ScanCode)
{
	keybd_event(VK, ScanCode, 0, 0);
	Sleep(50);
	keybd_event(VK, ScanCode, KEYEVENTF_KEYUP, 0);
}

void HoldKey(uint32_t VK, uint32_t ScanCode)
{
	keybd_event(VK, ScanCode, 0, 0);
}

void ReleaseKey(uint32_t VK, uint32_t ScanCode)
{
	keybd_event(VK, ScanCode, KEYEVENTF_KEYUP, 0);
}

bool getPixelColor(int &r, int &g, int &b, double xPos, double yPos) {
	// Device Context, Point Struct, and Color Struct
	HDC hDC = GetDC(HWND_DESKTOP);
	POINT pt;
	COLORREF rgb;

	// Values As byte
	BYTE rVal;
	BYTE gVal;
	BYTE bVal;

	// Same Values As Integers
	int red;
	int green;
	int blue;

	// Set This To Your Known Y Coord.
	// Pretty Sure 0,0 Is Top Left
	// Corner Of The Monitor.
	pt.y = yPos;
	pt.x = xPos;
	// Loop To 3000... Adjust For Higher
	// Resolution (Really?)

	rgb = GetPixel(hDC, pt.x, pt.y);
	rVal = GetRValue(rgb);
	gVal = GetGValue(rgb);
	bVal = GetBValue(rgb);

	red = (int)rVal;
	green = (int)gVal;
	blue = (int)bVal;

	r = red;
	g = green;
	b = blue;

	return true;
}

//Vector2 calculate_angle(Vector3 source, Vector3 destination)
//{
//	Vector3 difference = source - destination;
//	float length = difference.Length();
//
//	Vector2 ret{};
//
//	ret.y = asinf(difference.y / length);
//	ret.x = -atan2f(difference.x, -difference.z);
//
//	ret = { ret.x * 57.29578f, ret.y * 57.29578f };
//	ret.x = 90.f - ret.x;
//	/*if (ret.x < -180.f || ret.x > 180.f || ret.y < -180.f || ret.y > 180.f)
//	{
//		ret = { 0.f, 0.f };
//		return ret;
//	}*/
//
//	return ret;
//}

Vector2 calculate_angle(Vector3 source, Vector3 destination)
{
	Vector3 difference = source - destination;
	float length = difference.Length();

	Vector2 ret{};

	ret.y = asinf(difference.y / length);
	ret.x = -atan2f(difference.x, -difference.z);

	ret = { ret.x * 57.29578f, ret.y * 57.29578f };
	if (ret.x < -180.f || ret.x > 180.f || ret.y < -180.f || ret.y > 180.f)
	{
		ret = { 0.f, 0.f };
		return ret;
	}

	return ret;
}

Vector3 calculateRelativeTurretAngles(Vector3 unrelTurretAngles, Matrix3x3 hullRotationMatrix) {
	// Convert turret angles to a homogeneous vector (adding z component as 1)
	Vector3 turretVector = { unrelTurretAngles.x, unrelTurretAngles.y, 1.0f };

	// Apply the hull's rotation matrix to the turret vector
	Vector3 relativeTurretVector = {
		hullRotationMatrix.data[0][0] * turretVector.x + hullRotationMatrix.data[0][1] * turretVector.y + hullRotationMatrix.data[0][2] * turretVector.z,
		hullRotationMatrix.data[1][0] * turretVector.x + hullRotationMatrix.data[1][1] * turretVector.y + hullRotationMatrix.data[1][2] * turretVector.z,
		hullRotationMatrix.data[2][0] * turretVector.x + hullRotationMatrix.data[2][1] * turretVector.y + hullRotationMatrix.data[2][2] * turretVector.z
	};

	// Calculate the relative turret angles
	float relTurretTheta = atan2(relativeTurretVector.y, relativeTurretVector.x);
	float relTurretPhi = atan2(relativeTurretVector.z, sqrt(relativeTurretVector.x * relativeTurretVector.x + relativeTurretVector.y * relativeTurretVector.y));

	return { relTurretTheta, relTurretPhi, 0.0f };
}

std::string msg;
int selectedlistitemindex1 = 0;
int selectedlistitemindex2 = 0;
int selectedlistitemindex3 = 0;
int selectedlistitemindex4 = 0;
int selectedlistitemindex5 = 0;
bool aimbot = false;
bool autobomb = false;
bool menu = false;
//bool close = false;


void DrawMenu()
{
	ImGui::StyleColorsDark();
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos({ 100,100 }, ImGuiCond_Once);
	ImGui::SetNextWindowSize({ 420, 400 });
	ImGui::SetNextWindowBgAlpha(1.0f);

	ImGuiStyle& style = ImGui::GetStyle();
	{
		//Styles
		style.ScrollbarRounding = 5;
		style.FrameRounding = 2;

		style.Colors[ImGuiCol_WindowBg] = ImColor(18, 18, 18);
		style.Colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0);

		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_CheckMark] = ImColor(212, 225, 245);

		style.Colors[ImGuiCol_FrameBg] = ImColor(20, 20, 20);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(23, 23, 23);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(23, 23, 23);

		style.Colors[ImGuiCol_Header] = ImColor(23, 23, 23);
		style.Colors[ImGuiCol_HeaderActive] = ImColor(212, 225, 245);
		style.Colors[ImGuiCol_HeaderHovered] = ImColor(128, 128, 128);

		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(212, 225, 245);
		style.Colors[ImGuiCol_SliderGrab] = ImColor(212, 225, 245);

		style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(100, 100, 100);


		style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 255);
	}

	if (ImGui::Begin("WT", &Status.CHEATON,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::SetCursorPos(ImVec2(10, 10));
		if (ImGui::BeginChild(1, ImVec2(70, 250)))
		{
			ImGui::SetCursorPos(ImVec2(10, 10));
			if (val.tab == 0)
				style.Colors[ImGuiCol_Button] = ImColor(100, 100, 100);
			else
				style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
			if (ImGui::Button("\n" "" ICON_FA_EYE, ImVec2(50, 50)))
			{
				val.tab = 0;
			}
			if (val.tab == 1)
				style.Colors[ImGuiCol_Button] = ImColor(100, 100, 100);
			else
				style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
			ImGui::SetCursorPos(ImVec2(10, 70));
			if (ImGui::Button("\n" "" ICON_FA_BARS, ImVec2(50, 50)))
			{
				val.tab = 1;
			}
			if (val.tab == 3)
				style.Colors[ImGuiCol_Button] = ImColor(100, 100, 100);
			else
				style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
			ImGui::SetCursorPos(ImVec2(10, 130));
			if (ImGui::Button("\n" "" ICON_FA_KEYBOARD, ImVec2(50, 50)))
			{
				val.tab = 3;
			}
			if (val.tab == 2)
				style.Colors[ImGuiCol_Button] = ImColor(100, 100, 100);
			else
				style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
			ImGui::SetCursorPos(ImVec2(10, 190));
			if (ImGui::Button("\n" "" ICON_FA_PAINT_BRUSH, ImVec2(50, 50)))
			{
				val.tab = 2;
			}
			
			/*style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
			style.Colors[ImGuiCol_Text] = ImColor(0, 204, 255);
			style.Colors[ImGuiCol_ButtonActive] = ImColor(0, 102, 204);
			style.Colors[ImGuiCol_ButtonHovered] = ImColor(0, 102, 204);*/
			/*ImGui::SetCursorPos(ImVec2(10, 220));
			if (ImGui::Button("\n" "" ICON_FA_SHOPPING_CART, ImVec2(50, 50)))
			{
				val.tab = 2;
			}
			style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
			style.Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0);
			style.Colors[ImGuiCol_ButtonHovered] = ImColor(100, 100, 100);*/

			ImGui::EndChild();
		}
		ImGui::SetCursorPos(ImVec2(90, 10));
		if (ImGui::BeginChild(2, ImVec2(320, 380)))
		{
			ImGui::SetCursorPos(ImVec2(110, 5));
			ImGui::Text(get_string_v2(Status.indexmenuname).c_str());
			switch (val.tab) {
			case 0:
				ImGui::SetCursorPos(ImVec2(10, 25));
				ImGui::Text(skCrypt("Visuals"));
				ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::Checkbox(skCrypt("Name ESP"), &Status.NAMEESP);

				if (Status.NAMEESP)
				{
					style.Colors[ImGuiCol_ChildBg] = ImColor(30, 30, 30);
					ImGui::SetCursorPos(ImVec2(150, 50));
					ImGui::BeginChild(3, { 160, 67 });
					ImGui::SetWindowFontScale(0.8f);
					ImGui::SetCursorPos(ImVec2(0, 5));
					ImGui::Checkbox(skCrypt("PlayerName"), &Status.NAMEESP_name);
					ImGui::SetCursorPos(ImVec2(85, 5));
					ImGui::Checkbox(skCrypt("Distance"), &Status.NAMEESP_distance);
					ImGui::SetCursorPos(ImVec2(0, 25));
					ImGui::Checkbox(skCrypt("VehicleName"), &Status.NAMEESP_vehiclename);
					ImGui::SetCursorPos(ImVec2(85, 25));
					ImGui::Checkbox(skCrypt("FlareCount"), &Status.NAMEESP_flarecounter);
					ImGui::SetCursorPos(ImVec2(0, 45));
					ImGui::Checkbox(skCrypt("ReloadTimer/CantShoot"), &Status.NAMEESP_isreloading_cantshoot);
					ImGui::EndChild();
				}

				
				

					ImGui::SetCursorPos(ImVec2(10, 75));
					ImGui::Checkbox(skCrypt("Show Friendlies"), &Status.showfriendly);
					

					ImGui::SetCursorPos(ImVec2(10, 100));
					ImGui::Checkbox(skCrypt("Boxes"), &Status.BoxESP);
					

					ImGui::SetCursorPos(ImVec2(10, 125));
					ImGui::Checkbox(skCrypt("Snaplines"), &Status.snaplines);
					ImGui::SetCursorPos(ImVec2(10, 150));
					ImGui::Checkbox(skCrypt("Prediction"), &Status.prediction);

					/*ImGui::SetCursorPos(ImVec2(100, 150));
					ImGui::SliderFloat(" ", &val.predictionmult, 0.f, 30.f);*/

					ImGui::SetCursorPos(ImVec2(10, 175));
					ImGui::Checkbox(skCrypt("Player List"), &Status.nearby_warning);
					if (Status.nearby_warning)
					{
						ImGui::SetCursorPos(ImVec2(110, 175));
						ImGui::PushItemWidth(175.f);
						ImGui::SliderInt(skCrypt(""), &val.nearbydistance, 0, 20000);
					}
					ImGui::SetCursorPos(ImVec2(10, 200));
					ImGui::Checkbox(skCrypt("Missile ESP"), &Status.MissileESP);
					
					ImGui::SetCursorPos(ImVec2(10, 225));
					ImGui::Checkbox(skCrypt("Part Chams"), &Status.parts_esp);
					/*if (Status.parts_esp)
					{
						ImGui::SetCursorPos(ImVec2(150, 225));
						ImGui::Checkbox(skCrypt("Body"), &Status.parts_body);
						ImGui::SetCursorPos(ImVec2(210, 225));
						ImGui::Checkbox(skCrypt("Ammo"), &Status.parts_ammo);
						ImGui::SetCursorPos(ImVec2(150, 250));
						ImGui::Checkbox(skCrypt("Crew"), &Status.parts_crew);
						ImGui::SetCursorPos(ImVec2(210, 250));
						ImGui::Checkbox(skCrypt("Engine"), &Status.parts_engine);
						ImGui::SetCursorPos(ImVec2(150, 275));
						ImGui::Checkbox(skCrypt("RenderToPrediction"), &Status.parts_RenderToPrediction);
						ImGui::SetCursorPos(ImVec2(150, 300));
						ImGui::Checkbox(skCrypt("ShowMyTank"), &Status.parts_showmytank);
					}*/

					if (Status.parts_esp)
					{
						style.Colors[ImGuiCol_ChildBg] = ImColor(30, 30, 30);
						ImGui::SetCursorPos(ImVec2(150, 225));
						ImGui::BeginChild(4, { 160, 87 });
						ImGui::SetWindowFontScale(0.8f);
						ImGui::SetCursorPos(ImVec2(0, 5));
						ImGui::Checkbox(skCrypt("Body"), &Status.parts_body);
						ImGui::SetCursorPos(ImVec2(85, 5));
						ImGui::Checkbox(skCrypt("Ammo"), &Status.parts_ammo);
						ImGui::SetCursorPos(ImVec2(0, 25));
						ImGui::Checkbox(skCrypt("Crew"), &Status.parts_crew);
						ImGui::SetCursorPos(ImVec2(85, 25));
						ImGui::Checkbox(skCrypt("Engine"), &Status.parts_engine);
						ImGui::SetCursorPos(ImVec2(0, 45));
						ImGui::Checkbox(skCrypt("ShowMyTank"), &Status.parts_showmytank);
						ImGui::SetCursorPos(ImVec2(0, 65));
						ImGui::Checkbox(skCrypt("RenderToPrediction"), &Status.parts_RenderToPrediction);
						ImGui::EndChild();
					}
					
				
				break;
			case 1:
				ImGui::SetCursorPos(ImVec2(10, 25));
				ImGui::Text(skCrypt("Misc"));
				/*ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::Checkbox(skCrypt("CCIPs"), &Status.SuperStats);
				ImGui::SetCursorPos(ImVec2(10, 75));
				ImGui::Checkbox(skCrypt("AimAssist"), &Status.aimassist);
				ImGui::SetCursorPos(ImVec2(10, 100));
				style.Colors[ImGuiCol_Text] = ImColor(255, 0, 0);
				ImGui::Checkbox(skCrypt("Enemy Markers(DISABLED)"), &Status.enemymarkers);
				style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
				ImGui::SetCursorPos(ImVec2(10, 125));
				ImGui::Checkbox(skCrypt("Mouse Aim in Sim"), &Status.aimmodeinsim);*/
				ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::Checkbox(skCrypt("Aimbot"), &Status.Aimbot);
				ImGui::SetCursorPos(ImVec2(10, 75));
				ImGui::Checkbox(skCrypt("Bomb Indicator"), &Status.bomb_indicator);
				/*if (Status.bomb_indicator)
				{
					ImGui::SetCursorPos(ImVec2(160, 150));
					ImGui::Checkbox(skCrypt("Auto Bomb(SPACE)"), &Status.automaticbomb);
				}*/
				

				//ImGui::SetCursorPos(ImVec2(10, 175));
				//style.Colors[ImGuiCol_Text] = ImColor(255, 0, 0);
				//ImGui::Checkbox(skCrypt("Auto TargetPoint(DISABLED)"), &Status.SlaveTargetPoint);
				//style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
				//ImGui::SetCursorPos(ImVec2(10, 200));
				//style.Colors[ImGuiCol_Text] = ImColor(255, 0, 0);
				//ImGui::Checkbox(skCrypt("Camera Changer(DISABLED)"), &Status.ChangeCameraPosition);
				//style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
				//if (Status.ChangeCameraPosition)
				//{
				//	ImGui::PushItemWidth(120.f);
				//	ImGui::SetCursorPos(ImVec2(160, 225));
				//	ImGui::SliderFloat(skCrypt("X"), &val.CameraX, -20.f, 20.f);
				//	ImGui::SetCursorPos(ImVec2(160, 250));
				//	ImGui::SliderFloat(skCrypt("Y"), &val.CameraY, -20.f, 200.f);
				//}
				//ImGui::SetCursorPos(ImVec2(10, 225));
				//style.Colors[ImGuiCol_Text] = ImColor(255, 0, 0);
				//ImGui::Checkbox(skCrypt("Sim 3rd person(DISABLED)"), &Status.sim3rdperson);
				//style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
				//ImGui::SetCursorPos(ImVec2(10, 250));
				//style.Colors[ImGuiCol_Text] = ImColor(255, 0, 0);
				//ImGui::Checkbox(skCrypt("No Scope Shadow(DISABLED)"), &Status.NoScopeShadow);
				//style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
				//ImGui::SetCursorPos(ImVec2(10, 275));
				//style.Colors[ImGuiCol_Text] = ImColor(255, 0, 0);
				//ImGui::Checkbox(skCrypt("Zoom Changer(DISABLED)"), &Status.ExtraZoom); // (RISKY! VISIBLE IN REPLAY)
				//style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
				//
				//if (Status.ExtraZoom)
				//{
				//	ImGui::PushItemWidth(120.f);
				//	ImGui::SetCursorPos(ImVec2(10, 300));
				//	ImGui::SliderFloat(skCrypt("Multiplier"), &val.Zoom_mult, 0.1f, 200.f);
				//}
				//ImGui::SetCursorPos(ImVec2(10, 350));
				//style.Colors[ImGuiCol_Text] = ImColor(255, 0, 0);
				//ImGui::Text(skCrypt("WARNING: ALL OF THESE FEATURES ARE RISKY"));
				//style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
				break;
			case 3:
				ImGui::SetCursorPos(ImVec2(10, 25));   //IN MY DEFENCE I WROTE THIS AT 3AM
				ImGui::Text(skCrypt("HOTKEYS(some are disabled)"));
				ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::Text(skCrypt("Aimbot: "));
				ImGui::SetCursorPos(ImVec2(100, 50));
				ImGui::PushItemWidth(50.f);
				selectedlistitemindex1 = getposition(KeyNames, GetNameByVkeyCode(val.aimbotkey).c_str());
				if (ImGui::CollapsingHeader(GetNameByVkeyCode(val.aimbotkey).c_str()))
				{
					ImVec2 winpos = ImGui::GetWindowPos();
					ImVec2 winsize = ImGui::GetWindowSize();
					ImGui::SetNextWindowPos({ winpos.x + winsize.x + 10,winpos.y + 50 }, ImGuiCond_Always);
					
					ImGui::SetNextWindowSize({ 200, 315 });
					ImGui::SetNextWindowBgAlpha(1.0f);
					if (ImGui::Begin(skCrypt("Key selection"), &Status.CHEATON,
						ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoSavedSettings |
						ImGuiWindowFlags_NoCollapse |
						ImGuiWindowFlags_NoScrollbar |
						ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoMove))
					{
						ImGui::SetCursorPos(ImVec2(4, 1));
						style.Colors[ImGuiCol_Text] = ImColor(0, 255, 0);
						ImGui::Text(skCrypt("Select Aimbot key"));
						style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
						ImGui::SetCursorPos(ImVec2(0, 20));
						ImGui::PushItemWidth(200.f);
						ImGui::ListBox(skCrypt("Aimbot key"), &selectedlistitemindex1, KeyNames, IM_ARRAYSIZE(KeyNames), 15);
						ImGui::End();
					}
				}
				if (selectedlistitemindex1 >= 0 && selectedlistitemindex1<=88)
					val.aimbotkey = GetVkeyCodeByName((std::string)KeyNames[selectedlistitemindex1]);

				ImGui::SetCursorPos(ImVec2(10, 75));
				ImGui::Text(skCrypt("BombAuto: "));
				ImGui::SetCursorPos(ImVec2(100, 75));
				ImGui::PushItemWidth(50.f);
				selectedlistitemindex2 = getposition(KeyNames, GetNameByVkeyCode(val.autobombkey).c_str());
				msg = GetNameByVkeyCode(val.autobombkey) + " ";
				if (ImGui::CollapsingHeader(msg.c_str()))
				{
					ImVec2 winpos = ImGui::GetWindowPos();
					ImVec2 winsize = ImGui::GetWindowSize();
					ImGui::SetNextWindowPos({ winpos.x + winsize.x + 10,winpos.y + 75 }, ImGuiCond_Always);

					ImGui::SetNextWindowSize({ 200, 315 });
					ImGui::SetNextWindowBgAlpha(1.0f);
					if (ImGui::Begin(skCrypt("Key selection "), &Status.CHEATON,
						ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoSavedSettings |
						ImGuiWindowFlags_NoCollapse |
						ImGuiWindowFlags_NoScrollbar |
						ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoMove))
					{
						ImGui::SetCursorPos(ImVec2(4, 1));
						style.Colors[ImGuiCol_Text] = ImColor(0, 255, 0);
						ImGui::Text(skCrypt("Select BombAuto key"));
						style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
						ImGui::SetCursorPos(ImVec2(0, 20));
						ImGui::PushItemWidth(200.f);
						ImGui::ListBox("BombAuto key", &selectedlistitemindex2, KeyNames, IM_ARRAYSIZE(KeyNames), 15);
						ImGui::End();
					}
				}
				if (selectedlistitemindex2 >= 0 && selectedlistitemindex2 <= 88)
					val.autobombkey = GetVkeyCodeByName((std::string)KeyNames[selectedlistitemindex2]);

				ImGui::SetCursorPos(ImVec2(10, 100));
				ImGui::Text(skCrypt("Menu: "));
				ImGui::SetCursorPos(ImVec2(100, 100));
				ImGui::PushItemWidth(50.f);
				selectedlistitemindex3 = getposition(KeyNames, GetNameByVkeyCode(val.menukey).c_str());
				msg = GetNameByVkeyCode(val.menukey) + "  ";
				if (ImGui::CollapsingHeader(msg.c_str()))
				{
					ImVec2 winpos = ImGui::GetWindowPos();
					ImVec2 winsize = ImGui::GetWindowSize();
					ImGui::SetNextWindowPos({ winpos.x + winsize.x + 10,winpos.y + 100 }, ImGuiCond_Always);

					ImGui::SetNextWindowSize({ 200, 315 });
					ImGui::SetNextWindowBgAlpha(1.0f);
					if (ImGui::Begin(skCrypt("Key selection  "), &Status.CHEATON,
						ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoSavedSettings |
						ImGuiWindowFlags_NoCollapse |
						ImGuiWindowFlags_NoScrollbar |
						ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoMove))
					{
						ImGui::SetCursorPos(ImVec2(4, 1));
						style.Colors[ImGuiCol_Text] = ImColor(0, 255, 0);
						ImGui::Text(skCrypt("Select Menu key"));
						style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
						ImGui::SetCursorPos(ImVec2(0, 20));
						ImGui::PushItemWidth(200.f);
						ImGui::ListBox(skCrypt("Menu key"), &selectedlistitemindex3, KeyNames, IM_ARRAYSIZE(KeyNames), 15);
						if (selectedlistitemindex3 == 0)
							selectedlistitemindex3 = 1;
						ImGui::End();
					}
				}
				if (selectedlistitemindex3 >= 0 && selectedlistitemindex3 <= 88)
					val.menukey = GetVkeyCodeByName((std::string)KeyNames[selectedlistitemindex3]);

				ImGui::SetCursorPos(ImVec2(10, 125));
				ImGui::Text(skCrypt("ATP toggle: "));
				ImGui::SetCursorPos(ImVec2(100, 125));
				ImGui::PushItemWidth(50.f);
				selectedlistitemindex5 = getposition(KeyNames, GetNameByVkeyCode(val.autotargetpointogglekey).c_str());
				msg = GetNameByVkeyCode(val.autotargetpointogglekey) + "   ";
				if (ImGui::CollapsingHeader(msg.c_str()))
				{
					ImVec2 winpos = ImGui::GetWindowPos();
					ImVec2 winsize = ImGui::GetWindowSize();
					ImGui::SetNextWindowPos({ winpos.x + winsize.x + 10,winpos.y + 125 }, ImGuiCond_Always);

					ImGui::SetNextWindowSize({ 200, 315 });
					ImGui::SetNextWindowBgAlpha(1.0f);
					if (ImGui::Begin(skCrypt("Key selection ATP"), &Status.CHEATON,
						ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoSavedSettings |
						ImGuiWindowFlags_NoCollapse |
						ImGuiWindowFlags_NoScrollbar |
						ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoMove))
					{
						ImGui::SetCursorPos(ImVec2(4, 1));
						style.Colors[ImGuiCol_Text] = ImColor(0, 255, 0);
						ImGui::Text(skCrypt("Select ATP key"));
						style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
						ImGui::SetCursorPos(ImVec2(0, 20));
						ImGui::PushItemWidth(200.f);
						ImGui::ListBox(skCrypt("ATP key"), &selectedlistitemindex5, KeyNames, IM_ARRAYSIZE(KeyNames), 15);
						ImGui::End();
					}
				}
				if (selectedlistitemindex5 >= 0 && selectedlistitemindex5 <= 88)
					val.autotargetpointogglekey = GetVkeyCodeByName((std::string)KeyNames[selectedlistitemindex5]);

				ImGui::SetCursorPos(ImVec2(10, 150));
				ImGui::Text(skCrypt("Exit Cheat: "));
				ImGui::SetCursorPos(ImVec2(100, 150));
				ImGui::PushItemWidth(50.f);
				selectedlistitemindex4 = getposition(KeyNames, GetNameByVkeyCode(val.closecheatkey).c_str());
				msg = GetNameByVkeyCode(val.closecheatkey) + "   ";
				if (ImGui::CollapsingHeader(msg.c_str()))
				{
					ImVec2 winpos = ImGui::GetWindowPos();
					ImVec2 winsize = ImGui::GetWindowSize();
					ImGui::SetNextWindowPos({ winpos.x + winsize.x + 10,winpos.y + 150 }, ImGuiCond_Always);

					ImGui::SetNextWindowSize({ 200, 315 });
					ImGui::SetNextWindowBgAlpha(1.0f);
					if (ImGui::Begin(skCrypt("Key selection   "), &Status.CHEATON,
						ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoSavedSettings |
						ImGuiWindowFlags_NoCollapse |
						ImGuiWindowFlags_NoScrollbar |
						ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoMove))
					{
						ImGui::SetCursorPos(ImVec2(4, 1));
						style.Colors[ImGuiCol_Text] = ImColor(0, 255, 0);
						ImGui::Text(skCrypt("Select Exit key"));
						style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
						ImGui::SetCursorPos(ImVec2(0, 20));
						ImGui::PushItemWidth(200.f);
						ImGui::ListBox(skCrypt("Exit key"), &selectedlistitemindex4, KeyNames, IM_ARRAYSIZE(KeyNames), 15);
						ImGui::End();
						if (selectedlistitemindex4 == 0)
							selectedlistitemindex4 = 1;
					}
				}
				if (selectedlistitemindex4 >= 0 && selectedlistitemindex4 <= 88)
					val.closecheatkey = GetVkeyCodeByName((std::string)KeyNames[selectedlistitemindex4]);

	
				ImGui::SetCursorPos(ImVec2(10, 175));
				ImGui::Text(skCrypt("Press F12 to reset hotkeys"));
				ImGui::SetCursorPos(ImVec2(10, 200));
				ImGui::Checkbox(skCrypt("Frame Limiter (60FPS)"), &Status.framelimiter);
				ImGui::SetCursorPos(ImVec2(10, 225));
				style.Colors[ImGuiCol_Button] = ImColor(50, 50, 50);
				if (ImGui::Button(skCrypt("Save Config")))
					ExportConfig();
				style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
				ImGui::SetCursorPos(ImVec2(120, 225));
				style.Colors[ImGuiCol_Button] = ImColor(50, 50, 50);
				if (ImGui::Button(skCrypt("Load Config")))
					ReadConfig();
				style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
				
				break;
			case 2:
				ImGui::SetCursorPos(ImVec2(10, 25));
				ImGui::Text(skCrypt("Colors"));

				ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::ColorEdit4(skCrypt("EnemyName"), (float*)&clr.EnemyName, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 75));
				ImGui::ColorEdit4(skCrypt("FriendlyName"), (float*)&clr.FriendlyName, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 100));
				ImGui::ColorEdit4(skCrypt("Box"), (float*)&clr.BoxColour, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 125));
				ImGui::ColorEdit4(skCrypt("Distance"), (float*)&clr.Distance, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 150));
				ImGui::ColorEdit4(skCrypt("VehicleName"), (float*)&clr.VehicleName, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 175));
				ImGui::ColorEdit4(skCrypt("Parts_Crew"), (float*)&clr.Parts_Crew, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 200));
				ImGui::ColorEdit4(skCrypt("Parts_Body"), (float*)&clr.Parts_Body, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 225));
				ImGui::ColorEdit4(skCrypt("Parts_Ammo"), (float*)&clr.Parts_Ammo, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 250));
				ImGui::ColorEdit4(skCrypt("Parts_Engine"), (float*)&clr.Parts_Engine, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 275));
				ImGui::ColorEdit4(skCrypt("Parts_Barrel"), (float*)&clr.Parts_Barrel, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 300));
				ImGui::ColorEdit4(skCrypt("PlayerList"), (float*)&clr.PlayerList, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 325));
				ImGui::ColorEdit4(skCrypt("Cantshoot_reloading"), (float*)&clr.Cantshoot_reloading, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 350));
				ImGui::ColorEdit4(skCrypt("SnapLines_Friendly"), (float*)&clr.SnapLines_Friendly, ImGuiColorEditFlags_NoInputs);

				ImGui::SetCursorPos(ImVec2(10, 375));
				ImGui::ColorEdit4(skCrypt("SnapLines_Enemy"), (float*)&clr.SnapLines_Enemy, ImGuiColorEditFlags_NoInputs);
				break;
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

template<std::intmax_t FPS>
class frame_rater {
public:
	frame_rater() :                 // initialize the object keeping the pace
		time_between_frames{ 1 },     // std::ratio<1, FPS> seconds
		tp{ std::chrono::steady_clock::now() }
	{}

	void sleep() {
		// add to time point
		tp += time_between_frames;

		// and sleep until that time point
		std::this_thread::sleep_until(tp);
	}

private:
	// a duration with a length of 1/FPS seconds
	std::chrono::duration<double, std::ratio<1, FPS>> time_between_frames;

	// the time point we'll add to in every loop
	std::chrono::time_point<std::chrono::steady_clock, decltype(time_between_frames)> tp;
};
















