#include "stdafx.h"
#include "DirectX.h"
#include "main.h"
#include "Vectors.h"
#include "gui.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "REGISTRY_MANAGER.h"
#include "DriverComms.h"
#include "Values.h"
#include "skStr.h"
#include "MySDK.h"
#include "utils.h"
#include "SDK.h"
#include "JunkCode.h"
#include "AmmoMultipliers.h"
#include "kdmapper_main.hpp"

#define RELEASE

//#define DEBUG

//#define BOMBERBOT

//#define UNBRANDED



directx_t DirectX;
void DirectxFunctions::DirectXInit(HWND hwnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX.Object)))
		exit(1);

	ZeroMemory(&DirectX.Param, sizeof(DirectX.Param));
	DirectX.Param.Windowed = true;
	DirectX.Param.BackBufferFormat = D3DFMT_A8R8G8B8;
	DirectX.Param.BackBufferHeight = Overlay.Height;
	DirectX.Param.BackBufferWidth = Overlay.Width;
	DirectX.Param.EnableAutoDepthStencil = true;
	DirectX.Param.AutoDepthStencilFormat = D3DFMT_D16;
	DirectX.Param.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	DirectX.Param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	DirectX.Param.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	DirectX.Param.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	if (FAILED(DirectX.Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &DirectX.Param, 0, &DirectX.Device)))
		exit(1);
	


	D3DXCreateFontA(DirectX.Device, 20, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &DirectX.Font);
	D3DXCreateFontA(DirectX.Device, 13, 0, 0, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tahoma", &DirectX.defaultFont); 
	D3DXCreateFontA(DirectX.Device, 40, 0, 0, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Fixedsys", &DirectX.nearby_warningFont);
	D3DXCreateFontA(DirectX.Device, 13, 0, 2, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial", &DirectX.creditfont); 
	D3DXCreateFontA(DirectX.Device, 15, 10, 0, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Impact", &DirectX.MissileFont); 
	D3DXCreateFontA(DirectX.Device, 50, 30, 0, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Fixedsys", &DirectX.missile_warningFont);
	D3DXCreateLine(DirectX.Device, &DirectX.Line);


	DirectX.Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DirectX.Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DirectX.Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	/*DirectX.Device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_SRCALPHA);
	DirectX.Device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_DESTALPHA);*/
	//DirectX.Device->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	DirectX.Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
	DirectX.Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE); //DIFFUSE!!

	



	if (!DirectX.Line)
		D3DXCreateLine(DirectX.Device, &DirectX.Line);

}

DWORD WINAPI MiscProc(LPVOID lpParam)
{
	while (true)
	{
		if (Status.automaticbomb)
		{
			features::AutoBombDrop();
		}
		if (GetAsyncKeyState(VK_MBUTTON))
		{
			get_target_unit();
		}
		features::autoguide_mclos();

		//uintptr_t v1 = ReadPM<uintptr_t>(val.LocalPlayer.ownedunitptr + 0x3380); //OwnedUnit + 0x3380] + 0x2A74
		//Vector3 nonrelangle = ReadPM<Vector3>(v1 + 0x2A74);
		//Vector3 v2 = ReadPM<Vector3>(v1 + 0x2AC0);
		//v2 = val.LocalPlayerPosition;
		//Vector2 angle = calculate_angle(Vector3{ v2.z, v2.y, v2.x }, Vector3{ 1784.35999, 217.251678, 1949.83997 }); //{x = 1949.83997 y = 217.251678 z = 1784.35999 }

		/*uintptr_t v1 = ReadPM<uintptr_t>(val.LocalPlayer.ownedunitptr + 0x33C0);
		int v8 = ReadPM<int>(v1 + 0x3100);
		int v52 = 0x360 * v8;
		uintptr_t v9 = ReadPM<uintptr_t>(v1 + 0x30F0);
		uintptr_t v53 = v9 + v52 - 0x360;
		Vector2 angle = ReadPM<Vector2>(v53 + 0x44);
		Vector3 bulletspawn = ReadPM<Vector3>(v53 + 0x90);*/

		//write<Vector2>(ReadPM<uintptr_t>(val.LocalOwnedUnit.weaponsinfo + 0x1E0) + 0x38, Vector2{ 0,0 });

		Sleep(1);
	}
}

DWORD WINAPI AimbotProc(LPVOID lpParam)
{
	while (true)
	{
		if (Status.prediction&& val.on_ground)
			features::AIMBOT(val.aimbotpositions);

		/*if (Status.automaticbomb)
		{
			getbombdroppermission();
		}*/
#ifdef BOMBERBOT
		int timer = 0;
		uint8_t GUISTATE;
		while (timer < 600) //10min
		{
			GUISTATE = val.LocalPlayer.GuiState;
			if (GUISTATE != GuiState::ALIVE)
			{
				timer += 1;
				Sleep(1000);
			}
			else
			{
				timer = 0;
			}
		}
		if (timer >= 600)
		{
			while (get_process_id((std::string_view)skCrypt("aces.exe")) != NULL)
			{
				system("taskkill /f /im aces.exe");
				Sleep(1000);
			}
			exit(1);
		}
#endif

		Sleep(1);
	}

}

//DWORD WINAPI BomberBotProc(LPVOID lpParam)
//{
//	bomberbot();
//	return 0;
//}

DWORD WINAPI BuffProc(LPVOID lpParam)
{
	while (true)
	{
		int Playerarray_sizeread = sizeof(uintptr_t) * val.PlayerList_size;
		if (Playerarray_sizeread < 0 || Playerarray_sizeread > 1000000)Playerarray_sizeread = 0;
		PlayerArray Playerarray = ReadPM_secure<PlayerArray>(val.PlayerList, Playerarray_sizeread);
		int nearby_counter = 0;
#ifdef DEBUG
		CGame game = ReadPM<CGame>(val.Game);
		Playerarray = ReadPM<PlayerArray>(game.UnitList_3);
#endif
#ifndef DEBUG
		for (int i = 0; i <= val.PlayerList_size; i++)
#endif
#ifdef DEBUG
			for (int i = 0; i <= game.UnitCount_3; i++)
#endif
			{
				if (i > 99)
					break;
				Player player = ReadPM<Player>(Playerarray.Player[i]);
				uint8_t PlayerTeam = player.PlayerTeam;
#ifdef DEBUG
				PlayerTeam = ReadPM<uint8_t>(Playerarray.Player[i] + 0x10E0);
#endif


				if (Playerarray.Player[i] != NULL)
				{
					uintptr_t ownedunitptr = player.ownedunitptr;
					OwnedUnit ownedunit = ReadPM<OwnedUnit>(ownedunitptr);
#ifdef DEBUG
					ownedunit = ReadPM<OwnedUnit>(Playerarray.Player[i]);
#endif

					DamageModelContainer container = ReadPM<DamageModelContainer>(ReadPM<uintptr_t>(ownedunit.damagemodelinfo + 0x58));
					uintptr_t arrayptr = container.DamageModelArrayPtr;
					int DM_Array_readsize = container.DamageModelArraySize * sizeof(DamageModel_part);
					//if (DM_Array_readsize < 0 || DM_Array_readsize > 1000000)DM_Array_readsize = 0;
					DamageModel_Array DM_ArrayZ = ReadPM_secure<DamageModel_Array>(container.DamageModelArrayPtr, DM_Array_readsize);
					int transformsarray_readsize = ReadPM<uint32_t>(ownedunit.TransformsPtr + 0x8) * sizeof(DamageModelTransformInfo);
					//if (transformsarray_readsize < 0 || transformsarray_readsize > 1000000)transformsarray_readsize = 0;
					TransformsArray transformsarrayZ = ReadPM_secure<TransformsArray>(ReadPM<uintptr_t>(ownedunit.TransformsPtr + 0x0), transformsarray_readsize);

					for (int z = 0; z <= container.DamageModelArraySize; z++)
					{
						if (z > 999)
							break;
						DamageModel_part Part = DM_ArrayZ.Part[z];
						//DamageModel_part Part = ReadPM<DamageModel_part>(container.DamageModelArrayPtr);

						std::string partname;
						GetPboNameString(Part.NamePtr, partname);

						D3DCOLOR barrel_color, crewman_color, ammo_color, body_color, engine_color, selected_color;

						selected_color = D3DCOLOR_ARGB(100, 255, 255, 255);

						barrel_color = Color.Parts_Barrel;
						crewman_color = Color.Parts_Crew;
						ammo_color = Color.Parts_Ammo;
						body_color = Color.Parts_Body;
						engine_color = Color.Parts_Engine;

						if ((partname.find("ammo") != std::string::npos) && Status.parts_ammo)
							selected_color = ammo_color;
						else if ((partname == "driver_dm" || partname == "gunner_dm" || partname == "commander_dm" || partname == "loader_01_dm" || partname == "loader_02_dm"
							|| partname == "loader_dm" || partname == "machine_gunner_dm") && Status.parts_crew)
							selected_color = crewman_color;
						else if ((partname.find("cls_body") != std::string::npos || partname.find("turret") != std::string::npos || partname == "track_l_dm" || partname == "track_r_dm" ||
							partname.find("wheel_") != std::string::npos
							) && Status.parts_body)
							selected_color = body_color;
						else if ((partname == "engine_dm" || partname == "transmission_dm") && Status.parts_engine)
							selected_color = engine_color;
						else if ((partname == "gun_barrel_dm" || partname.find("cls_gun") != std::string::npos) && Status.parts_body)
							selected_color = barrel_color;
						else
							selected_color = D3DCOLOR_ARGB(0, 0, 0, 0);

						val.DM_colors_buff[i][z] = selected_color;
					}

					val.DM_Array_buff[i] = DM_ArrayZ;
					val.transformsarray_buff[i] = transformsarrayZ;
				}
			}
		Sleep(1);
	}
}

DWORD WINAPI MainProc(LPVOID lpParam)
{
	while (true)
	{
		read_locals();


#ifdef BOMBERBOT
		get_bases();
#endif BOMBERBOT

#ifndef DEBUG
		if (Status.prediction)
			val.predictionmult = get_multiplier();
#endif
		/*if (Status.prediction)
			val.predictionmult = get_multiplier();*/


#ifdef RELEASE
		DebugChecks();
#endif
		Status.SuperStats = true;
		Status.aimassist = true;
		Status.SlaveTargetPoint = true;
		if (Status.SuperStats && val.LocalPlayerptr)
		{
			features::superstats();
		}

		//if (Status.ExtraZoom && val.LocalPlayerptr)
		//{
		//	//features::extrazoom();
		//}

		//if (Status.NoScopeShadow && val.LocalPlayerptr)
		//{
		//	//features::noscopeshadow();
		//}

		if (Status.aimassist && val.LocalPlayerptr)
		{
			features::aimassist();
		}

		/*if (Status.SlaveTargetPoint)
		{
			features::SlaveTargetPoint(val.targetpointpositions);
		}*/

		//if (val.LocalPlayerptr)
		//{
		//	//features::enemymarkers();
		//}

		if (val.LocalPlayerptr)
		{
			features::MouseAimInSim();
		}

		//if (Status.ChangeCameraPosition && val.LocalPlayerptr)
		// {
			//features::CameraChanger();
		// }

		//if (Status.sim3rdperson)
		// {
			//features::sim_3rd_person();
		// }

		if (Status.prediction && val.LocalPlayer.GuiState == GuiState::ALIVE)
		{
			write_if_not<uint8_t>((val.gameModule + Offset.forestall_bool), 1);
		}


		Color.parse_colors();

		Sleep(1);
	}
}

void DirectxFunctions::RenderDirectX()
{
	frame_rater<70> fr;
	DirectX.Device->BeginScene();                  
	
	if (val.currentwindow == Target.Window || val.currentwindow == Overlay.Window)
	{
		if (Status.Init_Complete)
		{
			
				int Playerarray_sizeread = sizeof(uintptr_t) * val.PlayerList_size;
				if (Playerarray_sizeread < 0 || Playerarray_sizeread > 1000000)Playerarray_sizeread = 0;
				PlayerArray Playerarray = ReadPM_secure<PlayerArray>(val.PlayerList, Playerarray_sizeread);
				int nearby_counter = 0;
#ifdef DEBUG
				CGame game = ReadPM<CGame>(val.Game);
				Playerarray = ReadPM<PlayerArray>(game.UnitList_3);

				
#endif
#ifndef DEBUG
				for (int i = 0; i <= 99; i++)
#endif
#ifdef DEBUG
				if (game.UnitCount_3 < 100)
					for (int i = 0; i <= game.UnitCount_3; i++)
#endif
				{
					Player player = ReadPM<Player>(Playerarray.Player[i]);
					uint8_t PlayerTeam = player.PlayerTeam;
					

					if (Playerarray.Player[i] > 0)
					{
						uintptr_t ownedunitptr = player.ownedunitptr;
						ownedunit = ReadPM<OwnedUnit>(ownedunitptr);
#ifdef DEBUG
						ownedunit = ReadPM<OwnedUnit>(Playerarray.Player[i]);
						PlayerTeam = ReadPM<Player>(ownedunit.Playerptr).PlayerTeam;
						player.ownedunitptr = Playerarray.Player[i];
						ownedunitptr = Playerarray.Player[i];
#endif

#ifndef DEBUG
						bool isDead = ((ownedunit.UnitState == 2) || (player.GuiState != GuiState::ALIVE));
						/*if (!IsAlive(ownedunit) || player.GuiState != GuiState::ALIVE)*/
						if (isDead)
						{
							val.aimbotpositions[i] = { 0.f,0.f,0.f };
							val.targetpointpositions[i] = { 0.f,0.f,0.f };
							val.playerpositions[i] = { 0.f,0.f,0.f };
							continue;
						}
#endif 
#ifdef DEBUG
						/*if (!IsAlive(ownedunit))
						{
							val.aimbotpositions[i] = { 0.f,0.f,0.f };
							continue;
						}*/
#endif

						Vector3 PlayerPosition = ownedunit.PlayerPosition;
						val.playerpositions[i] = PlayerPosition;
						Vector3 aimpos;

						if (PlayerTeam != val.LocalPlayerTeam)
						{
							vec3 max, min;
							vec3 forwardDotRightBottomBackward = vec3{ ownedunit.boundsmin.x, ownedunit.boundsmin.y, ownedunit.boundsmin.z };
							vec3 forwardDotLeftTopForward = vec3{ ownedunit.boundsmax.x, ownedunit.boundsmax.y, ownedunit.boundsmax.z };
							RotateDot((float*)ownedunit.Rotation_Matrix, forwardDotRightBottomBackward, min);
							RotateDot((float*)ownedunit.Rotation_Matrix, forwardDotLeftTopForward, max);
							max += ownedunit.PlayerPosition;
							min += ownedunit.PlayerPosition;
							aimpos = { (max.x + min.x) / 2, (max.y + min.y) / 2,(max.z + min.z) / 2 };
							val.targetpointpositions[i] = aimpos;
						}



						if (PlayerPosition.x < 1.f && PlayerPosition.z < 1.f && PlayerPosition.x > -1.f && PlayerPosition.z > -1.f)
						{
							val.aimbotpositions[i] = { 0.f,0.f,0.f };
							val.targetpointpositions[i] = { 0.f,0.f,0.f };
							val.playerpositions[i] = { 0.f,0.f,0.f };
							continue;
						}

						if (Status.showfriendly == false && PlayerTeam == val.LocalPlayerTeam && Playerarray.Player[i] != val.LocalPlayerptr)
							continue;

#ifndef DEBUG
						uintptr_t nameptr1 = Playerarray.Player[i] + 0xB8;
						std::string name;
						GetPboNameString(nameptr1, name);
						if (name.length() == NULL)
							continue;
						char* namemsg = (char*)name.c_str();
#endif 
#ifdef DEBUG
						char* namemsg = (char*)"Vehicle";
#endif
						uintptr_t vehicleinfoptr = ownedunit.vehicleinfoptr;
						uintptr_t FullVehicleName = ReadPM<uintptr_t>(vehicleinfoptr + 0x20);
						std::string vehiclename;
						GetPboNameStringASCII(FullVehicleName, vehiclename);
						if (vehiclename == "" || vehiclename == "...")
							continue;
						char* vehiclenamemsg = (char*)vehiclename.c_str();

						int distance = GetDistance(PlayerPosition, val.LocalPlayerPosition);
						std::string dist2 = "Distance " + to_string(distance);
						char* distmsg = (char*)dist2.c_str();

						float airspeed;
						bool in_air = false;
						Dagor_airvelocity airvelocitydagor = ReadPM<Dagor_airvelocity>(ownedunit.AirVelocityPTR + 0xB20); //f2 0f 10 80 ? ? ? ? f2 0f 10 88 ? ? ? ? f2 0f 59 c0 f2 0f 59 c9 f2 0f 58 c8 f2 0f 10 80 ? ? ? ? f2 0f 59 c0 f2 0f 58 c1 f2 0f 51 c0 f2 0f 5a c0 f3 0f 11 82
						Vector3 airvelocity = { (float)airvelocitydagor.x, (float)airvelocitydagor.y,(float)airvelocitydagor.z };
						//Vector3 angularacceleration = { (float)airvelocitydagor.angularaccelerationx, (float)airvelocitydagor.angularaccelerationy,(float)airvelocitydagor.angularaccelerationz };
						Vector3 groundvelocity;
						if (!ownedunit.AirVelocityPTR)
						{
							groundvelocity = ReadPM<Vector3>(ownedunit.VelocityGroundPTR + 0x54);
						}
						else
							in_air = true;

						uint8_t isInvulnerable = ownedunit.isInvulnerable;


						int Countermeasures_count;
						std::string countermeasuresstr = "";
						char* countermeasuresmsg;

						if (airvelocity.x != NULL || airvelocity.y != NULL || airvelocity.z != NULL)
						{
							Countermeasures_count = get_countermeasures(ownedunit);
							if (Countermeasures_count > 0)
							{
								countermeasuresstr = "Flares: " + to_string(Countermeasures_count);
								countermeasuresmsg = (char*)countermeasuresstr.c_str();
							}
						}

						//uintptr_t weapons = ownedunit.weaponsinfo;
						//uintptr_t WeaponListPTR = ReadPM<uintptr_t>(weapons + 0x308); //48 8b 89 ? ? ? ? 48 89 08 48 89 50 ? c3 0f 57 c0
						//weapon first_weapon = ReadPM<weapon>(ReadPM<uintptr_t>(WeaponListPTR));
						bool cannotshoot = false;
						/*if (!first_weapon.CanFire)
							cannotshoot = true;*/

						uint8_t ReloadTime = 100 - (uint8_t)(((float)ownedunit.visualReloadProgress / 16.f) * 100.f);
						std::string reloadtimestr = "Reloading " + to_string(ReloadTime) + "%";
						char* reloadtimemsg = (char*)reloadtimestr.c_str();

						bool is_selected_target = false;
						if (ownedunitptr == val.internal_target_unit && val.in_air)
						{
							is_selected_target = true;
						}

						int8_t visible = 0;
						if (ownedunit.UnitFlags & 0x800 && ownedunit.UnitFlags & 0x40000000)
							visible = 2;
						else if (ownedunit.UnitFlags & 0x800)
							visible = 1;


						Vector3 ScreenPosition;
						bool is_on_screen = WorldToScreen(PlayerPosition, ScreenPosition);
						ScreenPosition = Normalizescreenpos(ScreenPosition);





						if (Status.parts_esp && ownedunit.TransformsPtr != NULL && !in_air && !val.in_air && is_on_screen
							&& (PlayerTeam != val.LocalPlayerTeam || (Playerarray.Player[i] == val.LocalPlayerptr && Status.parts_showmytank)))
						{
							renderChams(i, PlayerPosition, groundvelocity, ownedunit);
						}

						if (Status.BoxESP && is_on_screen && Playerarray.Player[i] != val.LocalPlayerptr)
						{
							draw3DBox(PlayerPosition, ownedunit.boundsmin, ownedunit.boundsmax, (float*)ownedunit.Rotation_Matrix, Color.boxcolor, 2.f);
						}

						if (Status.snaplines && Playerarray.Player[i] != val.LocalPlayerptr && is_on_screen)
						{
							renderSnaplines(PlayerTeam, ScreenPosition);
						}

						if (is_on_screen && Status.NAMEESP)
						{
							renderNameESP(PlayerTeam, ScreenPosition, namemsg, vehiclenamemsg, distmsg, ReloadTime, reloadtimemsg, isInvulnerable,
								countermeasuresstr, countermeasuresmsg, in_air, cannotshoot, is_selected_target, visible);
						}

						if (Status.nearby_warning && PlayerTeam != val.LocalPlayerTeam)
						{
							renderPlayerList(distance, nearby_counter, name, vehiclename, dist2);
						}

						if (Status.prediction && distance <= val.predictiondistance && Playerarray.Player[i] != val.LocalPlayerptr)
						{
							renderPrediction(i, ownedunit, player, airvelocity, groundvelocity, PlayerTeam);
						}
					}
				}
			

			if (Status.bomb_indicator && val.in_air)
			{
				renderBombRocketIndicator();
			}

			if (Status.MissileESP)
			{
				renderMissileESP();
			}
		}
		if (!Mapping_Complete)
			DrawTextnoncenter(skCrypt("Initializing..."), 10, 19 - Overlay.OffsetTop, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.creditfont);
		else
			DrawTextnoncenter(skCrypt("MENU - INSERT"), 10, 19 - Overlay.OffsetTop, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.creditfont);
		if (Status.MenuOn)
		{
			DrawMenu();
		}
	}
	else
	{
		Status.MenuOn = false;
	}


	DirectX.Device->EndScene();
	DirectX.Device->PresentEx(0, 0, 0, 0, 0);
	DirectX.Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	if (Status.framelimiter)
		fr.sleep();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM wideParameter, LPARAM longParameter);
POINTS poswnd = { };
LRESULT CALLBACK WinProcedure(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Status.MenuOn)
		if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
			return true;

	switch (Message)
	{
	case WM_PAINT:
		DirectxFunctions::RenderDirectX();

		break;

	case WM_DESTROY:
		PostQuitMessage(1);
		break;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;


	case WM_SIZE: {
		if (DirectX.Device && wParam != SIZE_MINIMIZED)
		{
			DirectX.Param.BackBufferWidth = LOWORD(lParam);
			DirectX.Param.BackBufferHeight = HIWORD(lParam);
		}
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	}break;


	case WM_LBUTTONDOWN: {
		poswnd = MAKEPOINTS(lParam); // set click points
	}return 0;

	case WM_MOUSEMOVE: {
		if (wParam == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(lParam);
			auto rect = ::RECT{ };

			GetWindowRect(hWnd, &rect);

			rect.left += points.x - poswnd.x;
			rect.top += points.y - poswnd.y;

			/*if (poswnd.x >= 0 &&
				poswnd.x <= 300 &&
				poswnd.y >= 0 && poswnd.y <= 19)
			{
				HWND setover = FindWindow(skCrypt("PNIHiddenWnd"), NULL);
				SetWindowPos(
					hWnd,
					setover,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
			}*/
		}

	}


	}
	return 0;
}

int ThreadProc()
{
	zigzag6(); //JUNK
	ReadConfig();
	int osver = GetOSVersion();
	if (osver == 0)
	{
		MessageBoxA(NULL, skCrypt("OS not supported"), skCrypt("FATAL ERROR"), MB_OK);
		exit(1);
	}

#ifdef RELEASE
	zigzag();//JUNK

	CreateThread(0, NULL, AntiDebug, (LPVOID)L"Z", NULL, NULL);
	if (!validation())
	{
		abort();
		val.hmodule = (HMODULE)0x1000;
		val.LocalPlayer = { 0 };
		ZeroMemory(&val.Game, sizeof(val.Game));
		get_process_id((std::string_view)skCrypt("lsass.exe"));
		quick_exit(0x16);
		terminate();
		ZeroMemory(&val.Hooked_function_PTR, sizeof(val.Hooked_function_PTR));
		ZeroMemory(&val.nameee, sizeof(val.nameee));
		ZeroMemory(&val.LocalPlayerTeam, sizeof(val.LocalPlayerTeam));
		get_process_id((std::string_view)skCrypt("cbm.exe"));
		exit(12);
		return 11;
	}

	xdoxozy::xdoxozy(); //JUNK
	RegistryManager::manager_vulnerabledriverblocklistenable();

	
		val.Process = get_process_id((std::string_view)(char*)get_string(165).c_str());
		if (!val.hmodule)while (!val.hmodule)val.hmodule = LoadLibraryA((char*)get_string(143).c_str());
		zigzag8(); //JUNK
		if (!val.Hooked_function_PTR)while (!val.Hooked_function_PTR)val.Hooked_function_PTR = GetProcAddress(val.hmodule, (char*)get_string(145).c_str());
		zigzag7(); //JUNK
		func = static_cast<function>(val.Hooked_function_PTR);
		
		int checked = 0;
		int check = 5;
		checked = ReadOwnProcessPM<int>((uintptr_t)&check);
		if (checked == 5 && val.Process)
		{
			Mapping_Complete = true;
		}
		else if (checked != 5 && val.Process)
		{
			MessageBoxA(0, "Close the game first", "Violation", MB_OK);
			exit(1);
		}
		else if (!val.Process)
		{
			MapDriver();
		}
	
	
		



#endif
#ifndef RELEASE
		Mapping_Complete = true;
#endif

	if (!val.hmodule)while (!val.hmodule)val.hmodule = LoadLibraryA((char*)get_string(143).c_str());
	zigzag7(); //JUNK
	if (!val.Hooked_function_PTR)while (!val.Hooked_function_PTR)val.Hooked_function_PTR = GetProcAddress(val.hmodule, (char*)get_string(145).c_str());
	zigzag8(); //JUNK
	func = static_cast<function>(val.Hooked_function_PTR);
	

#ifdef RELEASE
	INPUT inputs[2] = {};
	ZeroMemory(inputs, sizeof(inputs));
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_LWIN;
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_LWIN;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	Sleep(100);
	uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
#endif

	HWND Check = NULL;
	Check = FindWindow(((char*)get_string(166).c_str()), 0);
	if (Check == NULL)
		while (Check == NULL)
		{
			if (GetAsyncKeyState(VK_F11) & 1)
			{
				if (iqvw64e_device_handle)
					intel_driver::Unload(iqvw64e_device_handle);
				exit(1);
			}
			Check = FindWindow((char*)get_string(166).c_str(), 0);
		}

#ifdef RELEASE
	Sleep(1000);
#endif 

#ifdef UNBRANDED
	Status.indexmenuname += 1;
#endif

	val.Process = get_process_id((std::string_view)(char*)get_string(165).c_str()); 
	if (val.Process == NULL)while (val.Process == NULL)val.Process = get_process_id((std::string_view)(char*)get_string(165).c_str());


#ifdef DEBUG
	Status.NAMEESP = true;
	Status.ExtraZoom = true;
	Status.NoScopeShadow = true;
	Status.showfriendly = true;
	Status.BoxESP = true;
	Status.SuperStats = true;
	Status.aimassist = true;
	Status.prediction = true;
	val.Zoom_mult = 20.f;
#endif
	OverlayFunctions::GetTargetWindow(); //width-56 height-68
#ifndef BOMBERBOT
	OverlayFunctions::CreateClass(WinProcedure, (char*)skCrypt(" "));
	OverlayFunctions::CreateWindowOverlay();
	DirectxFunctions::DirectXInit(Overlay.Window);
	gui::CreateImGui(Overlay.Window, DirectX.Device);
	HWND setover = FindWindow(skCrypt("PNIHiddenWnd"), NULL);
if (win10_20h2)
	setover = FindWindow(skCrypt("Windows.UI.Core.CoreWindow"), NULL);

	SetWindowPos(Overlay.Window, setover, Overlay.OverlayLeft, Overlay.OverlayTop, Overlay.Width, Overlay.Height, SWP_SHOWWINDOW);
	ShowWindow(Overlay.Window, SW_SHOWNORMAL);
#endif


#ifdef BOMBERBOT
	CreateThread(0, NULL, BomberBotProc, (LPVOID)L"H", NULL, NULL);
#endif


#ifdef RELEASE
	zigzag2();			//JUNK
#endif
	

	while (true)
	{
		if (Mapping_Complete && !val.gameModule && !val.gameModule_Size)
		{
			val.gameModule = get_module_base_address((char*)get_string(165).c_str());
			val.gameModule_Size = get_module_size(skCrypt("aces.exe"));
			if (val.gameModule && val.gameModule_Size)
			{
				SetProtectedPID(GetCurrentProcessId());
				get_offsets();
				CreateThread(0, NULL, MainProc, (LPVOID)L"X", NULL, NULL);
				CreateThread(0, NULL, BuffProc, (LPVOID)L"G", NULL, NULL);
				CreateThread(0, NULL, MiscProc, (LPVOID)L"N", NULL, NULL);
				CreateThread(0, NULL, AimbotProc, (LPVOID)L"J", NULL, NULL);

				Status.Init_Complete = true;
			}
			
		}
		
		OverlayFunctions::UpdateOverlayState(Status.MenuOn, Overlay.Window);
		
		if (FindWindow(skCrypt("DagorWClass"), 0) == NULL)
		{
			Sleep(1000);
			if (FindWindow(skCrypt("DagorWClass"), 0) == NULL)
			{
				if (iqvw64e_device_handle)
					intel_driver::Unload(iqvw64e_device_handle);
				exit(1);
			}
		}
#ifndef BOMBERBOT
		if (PeekMessage(&Overlay.Message, Overlay.Window, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&Overlay.Message);
			TranslateMessage(&Overlay.Message);
		}

		if (!Target.Window)
			OverlayFunctions::GetTargetWindow();

		HWND setover = FindWindow(skCrypt("PNIHiddenWnd"), NULL);
		if (win10_20h2)
			setover = FindWindow(skCrypt("Windows.UI.Core.CoreWindow"), NULL);

		SetWindowPos(Overlay.Window, setover, Overlay.OverlayLeft, Overlay.OverlayTop, Overlay.Width, Overlay.Height, SWP_SHOWWINDOW);
#endif
		SetProtectedPID(GetCurrentProcessId());
		val.currentwindow = GetForegroundWindow();

		if (GetAsyncKeyState(val.menukey) & 1)
		{
			Status.MenuOn = !Status.MenuOn;
			if (Status.MenuOn == true)
				SetForegroundWindow(Overlay.Window);
			else
				SetForegroundWindow(Target.Window);
		}
		else if (GetAsyncKeyState(val.closecheatkey) & 1)
		{
			if (iqvw64e_device_handle)
				intel_driver::Unload(iqvw64e_device_handle);
			exit(1);
		}
		else if (GetAsyncKeyState(VK_F12) & 1)
		{
			val.aimbotkey = 0x52;
			val.autobombkey = 0x52;
			val.menukey = VK_INSERT;
			val.closecheatkey = VK_F11;
		}
		else if (GetAsyncKeyState(val.autotargetpointogglekey) & 1)
		{
			Status.SlaveTargetPoint = !Status.SlaveTargetPoint;
		}
#ifdef RELEASE
		else if (!val.antidebug)
		{
			if (iqvw64e_device_handle)
				intel_driver::Unload(iqvw64e_device_handle);
			exit(1);
		}
#endif

		Sleep(1);
	}
	return 0;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	xdoxozy::xdoxozy(); //JUNK
	zigzag();			//JUNK

	ThreadProc();

	zigzag2();			//JUNK
	return TRUE;
}








