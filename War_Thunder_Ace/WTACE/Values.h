#pragma once
#include "stdafx.h"
#include "Vectors.h"


struct Offsets
{
	uintptr_t Game;
	uintptr_t Localplayer;
	uintptr_t Playerlist;
	uintptr_t hudinfo;
	uintptr_t all_list_data;
	uintptr_t forestall_bool;
}Offset;

struct Signatures
{
	struct Signature
	{
		const char* bytes;
		const char* mask;
	};

	Signature LocalPlayer = { "\x48\x8b\x05\x00\x00\x00\x00\xb1\x00\x48\x85\xc0\x74\x00\x0f\xb6\x48\x00\xeb\x00\x0f\x28\x8c\x24", "xxx????x?xxxx?xxx?x?xxxx" };
	Signature Game = { "\x48\x8b\x0d\x00\x00\x00\x00\x48\x85\xc9\x0f\x84\x00\x00\x00\x00\xc6\x05",  "xxx????xxxxx????xx" };
	Signature HUDINFO = { "\x48\x8b\x05\x00\x00\x00\x00\x83\xb8\x00\x00\x00\x00\x00\x7c\x00\xf3\x0f\x10\x80\x00\x00\x00\x00\xf3\x0f\x10\x8f", "xxx????xx?????x?xxxx????xxxx" };
	Signature AllListData = { "\x48\x8d\x0d\x00\x00\x00\x00\x48\x89\x4c\x24\x00\xc7\x44\x24\x00\x00\x00\x00\x00\x66\xc7\x44\x24\x00\x00\x00\x48\x8d\x84\x24\x00\x00\x00\x00\x48\x89\x44\x24\x00\x4d\x8b\x04\xd0", "xxx????xxxx?xxx?????xxxx???xxxx????xxxx?xxxx"};
	Signature PlayerList = { "\x48\x8b\x0d\x00\x00\x00\x00\x89\xc0\x48\x8b\x34\xc1\x48\x85\xf6\x74", "xxx????xxxxxxxxxx" };
	Signature forestallbool = { "\x80\x3d\x00\x00\x00\x00\x00\x75\x00\x41\xc6\x84\x24\x00\x00\x00\x00\x00\xe9", "xx?????x?xxxx?????x" };
}sigs;

struct Status
{
	bool Init_Complete = false;
	bool CHEATON = true;
	bool MenuOn = false;
	bool NAMEESP = false;

	bool NAMEESP_name = true;
	bool NAMEESP_vehiclename = true;
	bool NAMEESP_distance = true;
	bool NAMEESP_isreloading_cantshoot = true;
	bool NAMEESP_flarecounter = true;
	bool NAMEESP_currenttarget = true;

	bool InfAmmo = false;
	bool ExtraZoom = false;
	bool NoScopeShadow = false;
	bool NoRecoil = false;
	bool Aimbot = true;
	bool espmenu = false;
	bool Mbmenu = false;
	bool showfriendly = false;
	bool BoxESP = false;
	bool SuperStats = false;
	bool aimassist = false;
	bool snaplines = false;
	bool parts_esp = false;
	bool prediction = false;
	bool bomb_indicator = false;
	bool rocket_indicator = false;
	bool nearby_warning = false;
	bool enemymarkers = false;
	bool aimmodeinsim = false;
	bool bomberbot = true;
	bool automaticbomb = false;
	bool SlaveTargetPoint = false;
	bool ChangeCameraPosition = false;
	bool sim3rdperson = false;
	bool MissileESP = false;
	bool Turret_stabilisation = false;
	bool framelimiter = false;

	bool parts_ammo		= false;
	bool parts_crew		= false;
	bool parts_body		= false;
	bool parts_engine	= false;
	bool parts_RenderToPrediction = false;
	bool parts_showmytank = false;

	int indexmenuname = 157;
}Status;

struct Matrix3x4
{
	float member[12];
};

struct PlayerArray
{
	uintptr_t Player[100];
};

struct PtrList
{
	uintptr_t Ptr[50];
};

struct EditColor
{
	float r;
	float g;
	float b;
	float a = 1.f;
};

struct EditColors
{
	EditColor EnemyName = { .r = 1.f, .g = 0.f,.b = 0.f,.a = 1.f };
	EditColor FriendlyName = { .r = 0.f, .g = 0.f,.b = 1.f,.a = 1.f };
	EditColor VehicleName = { .r = 0.921f, .g = 0.537f,.b = 0.203f,.a = 1.f };
	EditColor Distance = { .r = 0.921f, .g = 0.537f,.b = 0.203f,.a = 1.f };
	EditColor BoxColour = { .r = 1.f, .g = 1.f,.b = 1.f,.a = 1.f };
	EditColor Parts_Crew = { .r = 0.f, .g = 0.2f,.b = 0.8f,.a = 0.7843f };
	EditColor Parts_Body = { .r = 0.2f, .g = 0.6f,.b = 1.f,.a = 0.1960f };
	EditColor Parts_Ammo = { .r = 1.f, .g = 0.f,.b = 0.f,.a = 0.3921f };
	EditColor Parts_Engine = { .r = 1.f, .g = 0.8f,.b = 0.f,.a = 0.3921f };
	EditColor Parts_Barrel = { .r = 1.f, .g = 0.f,.b = 0.f,.a = 0.7843f };
	EditColor PlayerList = { .r = 0.f, .g = 1.f,.b = 0.9215f,.a = 1.f }; 
	EditColor Cantshoot_reloading = { .r = 1.f, .g = 0.f,.b = 0.f,.a = 1.f };
	EditColor SnapLines_Friendly = { .r = 0.f, .g = 0.f,.b = 1.f,.a = 1.f };
	EditColor SnapLines_Enemy = { .r = 1.f, .g = 0.f,.b = 0.f,.a = 1.f };
}clr;

struct DrawingColors
{
	D3DCOLOR enemynamecolor;
	D3DCOLOR friendlynamecolor;
	D3DCOLOR vehiclenamecolor;
	D3DCOLOR distancecolor;
	D3DCOLOR boxcolor;
	D3DCOLOR Parts_Crew;
	D3DCOLOR Parts_Body;
	D3DCOLOR Parts_Ammo;
	D3DCOLOR Parts_Engine;
	D3DCOLOR Parts_Barrel;
	D3DCOLOR PlayerList;
	D3DCOLOR Cantshoot_reloading;
	D3DCOLOR SnapLines_Friendly;
	D3DCOLOR SnapLines_Enemy;

	void parse_colors()
	{
		enemynamecolor = D3DCOLOR_ARGB((int)(clr.EnemyName.a * 255), (int)(clr.EnemyName.r * 255), (int)(clr.EnemyName.g * 255), (int)(clr.EnemyName.b * 255));
		friendlynamecolor = D3DCOLOR_ARGB((int)(clr.FriendlyName.a * 255), (int)(clr.FriendlyName.r * 255), (int)(clr.FriendlyName.g * 255), (int)(clr.FriendlyName.b * 255));
		vehiclenamecolor = D3DCOLOR_ARGB((int)(clr.VehicleName.a * 255), (int)(clr.VehicleName.r * 255), (int)(clr.VehicleName.g * 255), (int)(clr.VehicleName.b * 255));
		distancecolor = D3DCOLOR_ARGB((int)(clr.Distance.a * 255), (int)(clr.Distance.r * 255), (int)(clr.Distance.g * 255), (int)(clr.Distance.b * 255));
		boxcolor = D3DCOLOR_ARGB((int)(clr.BoxColour.a * 255), (int)(clr.BoxColour.r * 255), (int)(clr.BoxColour.g * 255), (int)(clr.BoxColour.b * 255));
		Parts_Crew = D3DCOLOR_ARGB((int)(clr.Parts_Crew.a * 255), (int)(clr.Parts_Crew.r * 255), (int)(clr.Parts_Crew.g * 255), (int)(clr.Parts_Crew.b * 255));
		Parts_Body = D3DCOLOR_ARGB((int)(clr.Parts_Body.a * 255), (int)(clr.Parts_Body.r * 255), (int)(clr.Parts_Body.g * 255), (int)(clr.Parts_Body.b * 255));
		Parts_Ammo = D3DCOLOR_ARGB((int)(clr.Parts_Ammo.a * 255), (int)(clr.Parts_Ammo.r * 255), (int)(clr.Parts_Ammo.g * 255), (int)(clr.Parts_Ammo.b * 255));
		Parts_Engine = D3DCOLOR_ARGB((int)(clr.Parts_Engine.a * 255), (int)(clr.Parts_Engine.r * 255), (int)(clr.Parts_Engine.g * 255), (int)(clr.Parts_Engine.b * 255));
		Parts_Barrel = D3DCOLOR_ARGB((int)(clr.Parts_Barrel.a * 255), (int)(clr.Parts_Barrel.r * 255), (int)(clr.Parts_Barrel.g * 255), (int)(clr.Parts_Barrel.b * 255));
		PlayerList = D3DCOLOR_ARGB((int)(clr.PlayerList.a * 255), (int)(clr.PlayerList.r * 255), (int)(clr.PlayerList.g * 255), (int)(clr.PlayerList.b * 255));
		Cantshoot_reloading = D3DCOLOR_ARGB((int)(clr.Cantshoot_reloading.a * 255), (int)(clr.Cantshoot_reloading.r * 255), (int)(clr.Cantshoot_reloading.g * 255), (int)(clr.Cantshoot_reloading.b * 255));
		SnapLines_Friendly = D3DCOLOR_ARGB((int)(clr.SnapLines_Friendly.a * 255), (int)(clr.SnapLines_Friendly.r * 255), (int)(clr.SnapLines_Friendly.g * 255), (int)(clr.SnapLines_Friendly.b * 255));
		SnapLines_Enemy = D3DCOLOR_ARGB((int)(clr.SnapLines_Enemy.a * 255), (int)(clr.SnapLines_Enemy.r * 255), (int)(clr.SnapLines_Enemy.g * 255), (int)(clr.SnapLines_Enemy.b * 255));
	}
}Color;

struct VehicleConfig
{
	char pad_0000[1030]; //0x0000
	int8_t haveCCIPForRocket; //0x0406
	int8_t haveCCIPForGun; //0x0407
	int8_t haveCCIPForTurret; //0x0408
	int8_t haveCCIPForBombs; //0x0409
	int8_t haveCCRPForRocket; //0x040A
	int8_t haveCCRPForGun; //0x040B
	int8_t haveCCRPForTurret; //0x040C
	int8_t haveCCRPForBombs; //0x040D
	int8_t radarCScope; //0x040E
	int8_t haveOpticTurret; //0x040F
	int8_t havePointOfInterestDesignator; //0x0410
	int8_t hasPointOfInterestMemory; //0x0411
	int8_t hasMissileCommandLine; //0x0412
	int8_t laserDesignator; //0x0413
	int8_t hasHelmetDesignator; //0x0414

}; 

struct CGame
{
	char pad_0000[744]; //0x0000
	int64_t UnitList_1; //0x02E8
	char pad_02F0[8]; //0x02F0
	int32_t UnitCount_1; //0x02F8
	char pad_02FC[4]; //0x02FC
	int64_t UnitList_2; //0x0300
	char pad_0308[8]; //0x0308
	int32_t UnitCount_2; //0x0310
	char pad_0314[4]; //0x0314
	int64_t UnitList_3; //0x0318
	char pad_0320[8]; //0x0320
	int32_t UnitCount_3; //0x0328
	char pad_032C[204]; //0x032C
	int64_t BallisticComputer; //0x03F8
	char pad_0400[472]; //0x0400
	int64_t matrixptr; //0x05D8
};

struct Player
{
	char pad_0000[528]; //0x0000
	int8_t PlayerTeam; //0x0210
	char pad_0211[751]; //0x0211
	int8_t GuiState; //0x0500
	char pad_0501[511]; //0x0501
	int64_t ownedunitptr; //0x0700
};

struct OwnedUnit // 31F4 ACCELERATION?d
{
	char pad_0000[8]; //0x0000
	int16_t UnitIndex; //0x0008
	char pad_000A[774]; //0x000A
	int64_t TransformsPtr; //0x0310
	Vector3 boundsmin; //0x0318
	Vector3 boundsmax; //0x0324
	char pad_0330[1640]; //0x0330
	int8_t visualReloadProgress; //0x0998
	char pad_0999[555]; //0x0999
	Vector3 Rotation_Matrix[3]; //0x0BC4
	Vector3 PlayerPosition; //0x0BE8
	char pad_0BF4[4]; //0x0BF4
	int64_t AirVelocityPTR; //0x0BF8
	int64_t MCLOSPtr; //0x0C00
	char pad_0C08[1584]; //0x0C08
	int8_t isInvulnerable; //0x1238
	char pad_1239[143]; //0x1239
	int32_t UnitFlags; //0x12C8
	char pad_12CC[76]; //0x12CC
	int32_t UnitState; //0x1318
	char pad_131C[12]; //0x131C
	int64_t Playerptr; //0x1328
	char pad_1330[152]; //0x1330
	int64_t vehicleinfoptr; //0x13C8
	char pad_13D0[120]; //0x13D0
	int64_t damagemodelinfo; //0x1448
	char pad_1450[40]; //0x1450
	int64_t weaponsinfo; //0x1478
	char pad_1480[80]; //0x1480
	int64_t SensorsListPtr; //0x14D0
	char pad_14D8[3280]; //0x14D8
	int64_t VelocityGroundPTR; //0x21A8

}; 
OwnedUnit ownedunit;

struct DamageModelContainer //[damagemodelinfo + 0x58]
{
	char pad_0000[160]; //0x0000
	int64_t DamageModelArrayPtr; //0x00A0
	char pad_0001[8]; //0x00A8
	int32_t DamageModelArraySize; //0x00B0
}; 

struct DamageModel_part 
{
	char pad_0000[4]; //0x0000
	int16_t TransformIndex;
	char pad_0100[2]; //0x0000
	int64_t NextDamageModelPtr; //0x0008
	Vector3 Forward; //0x0010
	Vector3 Up; //0x001C
	Vector3 Left; //0x0028
	Vector3 Position; //0x0034
	Vector3 BbMin; //0x0040
	Vector3 BbMax; //0x004C
	char pad_0058[40]; //0x0058
	int64_t VerticesPtr; //0x0080
	int32_t VertexCount; //0x0088
	char pad_vercount[4]; //0x0058
	int64_t IndicesPtr; //0x0090
	int32_t IndexCount; //0x0098
	char pad_indcount[4]; //0x0058
	char pad_00A0[28]; //0x00A0
	int8_t Index; //0x00BC
	char pad_00BD[3]; //0x00BD
	int64_t NamePtr; //0x00C0
	char pad_0001[8]; //0x00C8
}; 

struct DamageModel_Array
{
	DamageModel_part Part[1000];
};
DamageModel_Array DM_Array;

struct DamageModelTransformInfo
{
	//char pad_0000[64]; //0x0000
	Matrix Transform; //0x0040
};

struct TransformsArray
{
	DamageModelTransformInfo TransformMatrix[1000];
};
TransformsArray transformsarray;

struct Vector3List
{
	Vector3 member[100];
};

struct Vector4List
{
	Vector4 member[800];
};
Vector4List Vertices_list;

struct IndicesList
{
	WORD Index[10000];
};
IndicesList indices_list;

//struct hudinfo1
//{
//	int64_t N00000069 = 72340172838076673; //0x0018
//	int64_t N0000006A = 282574488404225; //0x22 CAUSES DESYNC ! 282574488338689
//	int64_t N000004FE = 4294967296;
//};
//hudinfo1 hudvalues1;
//hudinfo1 hudcheck1;
//struct hudinfo2
//{
//	int64_t N000000B6 = 72340173965164544; //0x0280
//	int64_t N000002F0 = 72340172838076673;
//	int64_t N0000031C = 72057594037993729;
//	int64_t N000000B5 = 282578800148736;
//	int64_t N000002F1 = 1181376512;
//};
//hudinfo2 hudvalues2;
//hudinfo2 hudcheck2;
//
//struct hudinfo_all
//{
//	char pad_0000[24]; //0x0000
//	hudinfo1 info1; //0x0018
//	char pad_0030[592]; //0x0030
//	char pad_0031[8]; //0x0030
//	hudinfo2 info2; //0x0288
//};
//hudinfo_all hudcheck;

struct HUDINFO
{
	char pad_0000[32]; //0x0000
	int8_t selectable_air; //0x0020 !!!
	char pad_0021[36]; //0x0021
	int8_t ReticleView; //0x0045 !!!
	char pad_0046[594]; //0x0046
	char pad_0047[16]; //0x0046
	int8_t penetration_cross; //0x02A8
	char pad_0299[59]; //0x0299
	int8_t mouseaim1; //0x02E4
	char pad_02D5[8]; //0x02D5
	int8_t mouseaim2; //0x02ED
	char pad_02DE[291]; //0x02DE
	int8_t selectable_air2; //0x0411
};

struct ProjectileInfoBallisticComputer
{
	char pad_0000[7544]; //0x0000
	float ProjSpeed; //0x1D78
	char pad_1D7C[8]; //0x1D7C
	float ProjMass; //0x1D84
	float Caliber; //0x1D88
	float ShellLenght; //0x1D8C
};

struct ProjectileInfo
{
	int64_t NamePtr;
	float Caliber;
	float ProjSpeed;
	float ShellLenght;
	float ProjMass;
};

struct WeaponPositionInfo
{
	char pad_0000[632]; //0x0000
	Vector3 FireportPos; //0x0278
};

struct GunAnglesInfo //OwnedUnit + 0x3398] + 0x2A74
{
	char pad_0000[56]; //0x0000
	float CurrentX; //0x0038
	float CurrentY; //0x003C
	float CurrentX2; //0x0040
	float CurrentY2; //0x0044
	char pad_0048[13]; //0x0048
	int8_t IsTurretRotating; //0x0055
	char pad_0056[2]; //0x0056
	float CurrentX3; //0x0058
	float CurrentY3; //0x005C
	float CurrentX4; //0x0060
	float CurrentY4; //0x0064
	char pad_0068[12]; //0x0068
	float RotationSpeedX; //0x0074
	float RotationSpeedY; //0x0078
	float TargetX; //0x007C
	float TargetY; //0x0080
};

struct Base
{
	char pad_0000[112]; //0x0000
	int8_t side; //0x0070
	char pad_0071[55]; //0x0071
	int64_t PositionPTR; //0x00A8 + 0xE0 = Vec3 Position
	char pad_00B0[64]; //0x00B0
	float health; //0x00F0
};

struct weapon
{
	char pad_0000[832]; //0x0000
	int64_t NamePTR; //0x0340
	char pad_0348[1051]; //0x0348
	int8_t CanFire; //0x0763
};

struct weapon_extra_info
{
	int64_t Weapon_Name_Ptr; //0x0000
	char pad_0008[272]; //0x0008
	int32_t Max_ammo_count; //0x0118
	int32_t Remaining_ammo_count; //0x011C
};

struct ballisticcomputer
{
	char pad_0000[1640]; //0x0000
	int64_t pred_unit; //0x0668
	char pad_0670[6940]; //0x0670
	int8_t pred_is_drawn; //0x218C
	char pad_218D[3]; //0x218D
	Vector3 pred; //0x2190
};

enum GuiState : std::uint8_t
{
	NONE	=		0,
	MENU	=		1,
	ALIVE	=		2,
	DEAD	=		3,
	SPEC	=		6,
	SPAWN_MENU	=	8,
	LOADING =		10
};

struct vehicleslots
{
	Vector2 slot1 = { 278 + (155 * 0), 959 }; Vector2 slot1_check = { 278 + (155 * 0) ,936 };
	Vector2 slot2 = { 278 + (155 * 1), 959 }; Vector2 slot2_check = { 278 + (155 * 1) ,936 };
	Vector2 slot3 = { 278 + (155 * 2), 959 }; Vector2 slot3_check = { 278 + (155 * 2) ,936 };
	Vector2 slot4 = { 278 + (155 * 3), 959 }; Vector2 slot4_check = { 278 + (155 * 3) ,936 };
	Vector2 slot5 = { 278 + (155 * 4), 959 }; Vector2 slot5_check = { 278 + (155 * 4) ,936 };
}vehicleslot;

struct Values
{
	uintptr_t Process;
	uintptr_t gameModule;
	uintptr_t gameModule_Size;
	HWND currentwindow;
	HWND consolewindow;
	uintptr_t Game;
	CGame cgame;
	uintptr_t MatrixPtr;
	uintptr_t PlayerList;
	uint8_t LocalPlayerTeam;
	uint8_t LocalPlayerUnitIndex;
	OwnedUnit LocalOwnedUnit;
	VehicleConfig vehicleconfig;
	Vector3 LocalPlayerPosition;
	float LocalHeight;
	int PlayerList_size;
	uintptr_t LocalPlayerptr;
	Player LocalPlayer;
	HMODULE hmodule;
	void* Hooked_function_PTR;
	int aimfov = 150;
	ProjectileInfo first_bullet;
	std::string current_bullet_name;
	uintptr_t BallisticComputer;
	Vector3 localgroundvelocity;
	Vector3 localairvelocity;
	uintptr_t MissileListptr;
	uint32_t MissileListSize;
	uintptr_t selected_targetunit_ptr;
	uintptr_t internal_target_unit;
	OwnedUnit selected_targetunit;
	bool radar_pred_being_drawn;
	bool in_air = false;
	bool on_ground = false;
	int predictiondistance = 5000;
	int nearbydistance = 2000;

	double PI = 3.14159265359;
	bool antidebug = false;

	float predictionmult = 14.08f;
	float Zoom_mult = 0.1f;
	float Zoom_focusedmult = 0.f;

	float CameraX = -10.f;
	float CameraY = 5.f;

	bool drop_bomb = false;
	Vector3 FlyTargetPoint;
	Vector3 FlyTargetPointScreen;

	int tab;

	std::string nameee;
	Vector3 playerpositions[100];
	Vector3 aimbotpositions[100];
	Vector3 targetpointpositions[100];

	Base basesbuffer[8];
	Vector3 basespositionsbuffer[8];
	uint32_t basecount;

	int aimbotkey = 0x52;
	int autobombkey = 0x52;
	int menukey = VK_INSERT;
	int closecheatkey = VK_F11;
	int autotargetpointogglekey = 0x52;

	VERTEX vertexlist_screenpos[600];
	DamageModel_Array DM_Array_buff[100];
	TransformsArray transformsarray_buff[100];

	D3DCOLOR DM_colors_buff[100][1000];
}val;

struct ListIndexData
{
	char pad_0000[4]; //0x0000
	int16_t ListPtrOffset; //0x0004
	char pad_0006[18]; //0x0006
	int16_t ExtraInfoOffset; //0x0018
}; 

struct ListData
{
	int64_t ListPtr; //0x0000
	int32_t Count; //0x0008
	int8_t ExtraInfoOffset; //0x000C
};

struct AllListData
{
	char pad_0000[376]; //0x0000
	int64_t ListDataPtr; //0x0178
	char pad_0180[1144]; //0x0180
	int64_t ListIndexDataPtr; //0x05F8
};

struct Missile
{
	char pad_0000[508]; //0x0000
	Vector3 Position; //0x01FC
	char pad_0208[16]; //0x0208
	Vector3 Velocity; //0x0218
	char pad_0224[476]; //0x0224
	int64_t OwnerUnitPtr; //0x0400
	int64_t OwnerPlayerPtr; //0x0408
	char pad_0410[328]; //0x0410
	int64_t GuidancePtr; //0x0558
	char pad_0560[104]; //0x0560
	int64_t cleannameptr; //0x05C8

}; 

struct Missile_Kinematics
{
	char pad_0000[192]; //0x0000
	double Writable_PosX; //0x00C0
	double Writable_PosY; //0x00C8
	double Writable_PosZ; //0x00D0
	char pad_00D8[32]; //0x00D8
	double Writable_VelX; //0x00F8
	double Writable_VelY; //0x0100
	double Writable_VelZ; //0x0108
};

struct Missile_Guidance
{
	char pad_0000[64]; //0x0000
	int8_t IsLocked; //0x0040
	char pad_0041[31]; //0x0041
	int32_t IsTracking; //0x0060
	int16_t TargetUnitId; //0x0064
};

struct List_with_Size
{
	int64_t ListPtr; //0x0000
	int32_t Size_08; //0x0008
	char pad_000C[4]; //0x000C
	int32_t Size_10; //0x0010
};

struct UnitSensor
{
	char pad_0000[10112]; //0x0000
	int8_t IsTracking; //0x2780
	char pad_2781[39]; //0x2781
	int16_t TargetUnitID; //0x27A8
};




