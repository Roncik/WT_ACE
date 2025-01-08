#pragma once
#include "utils.h"
#include "patternsc.h"
#include "Values.h"
#include "AmmoMultipliers.h"


static bool WorldToScreen(const Vector3& in, Vector3& out)
{
	if (in.x <3.f && in.x > -3.f && in.y <3.f && in.y > -3.f && in.z <3.f && in.z > -3.f)
		return false;
	
	matrixx = ReadPM<Matrix>(val.MatrixPtr);



	float width = matrixx.member[3] * in.x + matrixx.member[7] * in.y + matrixx.member[11] * in.z + matrixx.member[15];

	if (width < 0.001f)
		return false;

	width = 1.0 / width;
	float x = in.x * matrixx.member[0] + in.y * matrixx.member[4] + in.z * matrixx.member[8] + matrixx.member[12];
	float y = in.x * matrixx.member[1] + in.y * matrixx.member[5] + in.z * matrixx.member[9] + matrixx.member[13];

	float nx = x * width;
	float ny = y * width;

	const Vector2 size = { (float)Target.width, (float)Target.height };

	out.x = (size.x / 2 * nx) + (nx + size.x / 2);
	out.y = -(size.y / 2 * ny) + (ny + size.y / 2);

	if (out.x > 0 && out.x <= Target.width && out.y > 0 && out.y <= Target.height)
		return true;
	else
		return false;
}

static bool WorldToScreenForBox(Matrix matrix, const Vector3& in, Vector3& out)
{
	matrixx = matrix;



	float width = matrixx.member[3] * in.x + matrixx.member[7] * in.y + matrixx.member[11] * in.z + matrixx.member[15];

	if (width < 0.001f)
		return false;

	width = 1.0 / width;
	float x = in.x * matrixx.member[0] + in.y * matrixx.member[4] + in.z * matrixx.member[8] + matrixx.member[12];
	float y = in.x * matrixx.member[1] + in.y * matrixx.member[5] + in.z * matrixx.member[9] + matrixx.member[13];

	float nx = x * width;
	float ny = y * width;

	Vector2 size = { (float)Target.width, (float)Target.height };

	out.x = (size.x / 2 * nx) + (nx + size.x / 2);
	out.y = -(size.y / 2 * ny) + (ny + size.y / 2);

	if (out.x > 0 && out.x <= Target.width && out.y > 0 && out.y <= Target.height)
		return true;
	else
		return false;
}

static Vector3 WorldToScreenVec3(Vector3 pos)
{
	Vector3 output;
	if (WorldToScreen(pos, output))
		return output;
}

static bool IsConnected(OwnedUnit unit)
{
	if (unit.Playerptr)
		return ReadPM<uint8_t>(unit.Playerptr + 0x208) >= 0;
	return 0;
}

inline bool IsAlive(OwnedUnit unit)  //1090 
{
	uint16_t UnitState = unit.UnitState;
	if (UnitState == 2)
		return 0;

	bool result = 0; // al

	/*if (&unit
		&& ((unit.AliveCheck1 != 0) || unit.UnitState <= 1u)
		&& (!((unit.AliveCheck2) & 0x20000)))
	{
		result = (unit.UnitState) < 2u;
	}
	else
	{
		result = 0;
	}*/

	/*if (&unit
		&& ((unit.AliveCheck1 != 0) || unit.UnitState <= 1u)
		&& (!(unit.AliveCheck2 & 2)
			))
	{
		result = unit.UnitState < 2u;
	}
	else
	{
		result = 0;
	}*/
	return result;
}

inline bool GetCleanMissileNameString(uintptr_t address, std::string& out)
{
	namestruct namech = ReadPM<namestruct>(address);
	std::string string;
	for (int i = 0; i <= 99; i++)
	{
		if (namech.name[i] != '\0')
		{
			if (namech.name[i] == '_' && namech.name[i + 1] == 'r' && namech.name[i + 2] == 'o')
				break;

			namech.name[i] = toupper(namech.name[i]);
			string += namech.name[i];
		}
		else
			break;
	}
	if (string.find("%") != std::string::npos || string.find("$") != std::string::npos 
		|| string.find("FLARE") != std::string::npos || string.find("CHAFF") != std::string::npos 
		|| string.find("SMOKE") != std::string::npos || string.find("TRIGGER") != std::string::npos)
		out == "";
	else
		out = string;

	return true;

}

static struct Dagor_airvelocity
{
	double x, y, z;
	char pad[240];
	double angularaccelerationx, angularaccelerationy, angularaccelerationz;
};

static void draw3DBox(vec3 position, vec3 boundsmin, vec3 boundsmax, float* rotationMatrix, D3DCOLOR color, float thickness)
{
	matrixx = ReadPM<Matrix>(val.MatrixPtr);

	///
	/// bottom
	/// 
	vec3 forwardDotLeftBottomForward = vec3{ boundsmax.x, boundsmin.y, boundsmax.z };
	vec3 forwardDotRightBottomForward = vec3{ boundsmax.x, boundsmin.y, boundsmin.z };
	vec3 forwardDotLeftBottomBackward = vec3{ boundsmin.x, boundsmin.y, boundsmax.z };
	vec3 forwardDotRightBottomBackward = vec3{ boundsmin.x, boundsmin.y, boundsmin.z };

	///
	/// top
	/// 
	vec3 forwardDotLeftTopForward = vec3{ boundsmax.x, boundsmax.y, boundsmax.z };
	vec3 forwardDotRightTopForward = vec3{ boundsmax.x, boundsmax.y, boundsmin.z };
	vec3 forwardDotLeftTopBackward = vec3{ boundsmin.x, boundsmax.y, boundsmax.z };
	vec3 forwardDotRightTopBackward = vec3{ boundsmin.x, boundsmax.y, boundsmin.z };

	Vector3 forwardDotLeftBottomForwardRotated, forwardDotRightBottomForwardRotated, forwardDotLeftBottomBackwardRotated, forwardDotRightBottomBackwardRotated;
	RotateDot(rotationMatrix, forwardDotLeftBottomForward, forwardDotLeftBottomForwardRotated);
	RotateDot(rotationMatrix, forwardDotRightBottomForward, forwardDotRightBottomForwardRotated);
	RotateDot(rotationMatrix, forwardDotLeftBottomBackward, forwardDotLeftBottomBackwardRotated);
	RotateDot(rotationMatrix, forwardDotRightBottomBackward, forwardDotRightBottomBackwardRotated);

	forwardDotLeftBottomForwardRotated += position;
	forwardDotRightBottomForwardRotated += position;
	forwardDotLeftBottomBackwardRotated += position;
	forwardDotRightBottomBackwardRotated += position;

	Vector3 forwardDotLeftBottomForwardRotatedScreenPos, forwardDotRightBottomForwardRotatedScreenPos, forwardDotLeftBottomBackwardRotatedScreenPos, forwardDotRightBottomBackwardRotatedScreenPos;
	if (!WorldToScreenForBox(matrixx, forwardDotLeftBottomForwardRotated, forwardDotLeftBottomForwardRotatedScreenPos))
		return;
	else if (!WorldToScreenForBox(matrixx, forwardDotRightBottomForwardRotated, forwardDotRightBottomForwardRotatedScreenPos))
		return;
	else if (!WorldToScreenForBox(matrixx, forwardDotLeftBottomBackwardRotated, forwardDotLeftBottomBackwardRotatedScreenPos))
		return;
	else if (!WorldToScreenForBox(matrixx, forwardDotRightBottomBackwardRotated, forwardDotRightBottomBackwardRotatedScreenPos))
		return;

	Vector3 forwardDotLeftTopForwardRotated, forwardDotRightTopForwardRotated, forwardDotLeftTopBackwardRotated, forwardDotRightTopBackwardRotated;
	RotateDot(rotationMatrix, forwardDotLeftTopForward, forwardDotLeftTopForwardRotated);
	RotateDot(rotationMatrix, forwardDotRightTopForward, forwardDotRightTopForwardRotated);
	RotateDot(rotationMatrix, forwardDotLeftTopBackward, forwardDotLeftTopBackwardRotated);
	RotateDot(rotationMatrix, forwardDotRightTopBackward, forwardDotRightTopBackwardRotated);

	forwardDotLeftTopForwardRotated += position;
	forwardDotRightTopForwardRotated += position;
	forwardDotLeftTopBackwardRotated += position;
	forwardDotRightTopBackwardRotated += position;

	Vector3 forwardDotLeftTopForwardRotatedScreenPos, forwardDotRightTopForwardRotatedScreenPos, forwardDotLeftTopBackwardRotatedScreenPos, forwardDotRightTopBackwardRotatedScreenPos;
	if (!WorldToScreenForBox(matrixx, forwardDotLeftTopForwardRotated, forwardDotLeftTopForwardRotatedScreenPos))
		return;
	else if (!WorldToScreenForBox(matrixx, forwardDotRightTopForwardRotated, forwardDotRightTopForwardRotatedScreenPos))
		return;
	else if (!WorldToScreenForBox(matrixx, forwardDotLeftTopBackwardRotated, forwardDotLeftTopBackwardRotatedScreenPos))
		return;
	else if (!WorldToScreenForBox(matrixx, forwardDotRightTopBackwardRotated, forwardDotRightTopBackwardRotatedScreenPos))
		return;

	forwardDotLeftBottomForwardRotatedScreenPos = Normalizescreenpos(forwardDotLeftBottomForwardRotatedScreenPos);
	forwardDotRightBottomForwardRotatedScreenPos = Normalizescreenpos(forwardDotRightBottomForwardRotatedScreenPos);
	forwardDotRightBottomBackwardRotatedScreenPos = Normalizescreenpos(forwardDotRightBottomBackwardRotatedScreenPos);
	forwardDotLeftBottomBackwardRotatedScreenPos = Normalizescreenpos(forwardDotLeftBottomBackwardRotatedScreenPos);

	forwardDotLeftTopForwardRotatedScreenPos = Normalizescreenpos(forwardDotLeftTopForwardRotatedScreenPos);
	forwardDotRightTopForwardRotatedScreenPos = Normalizescreenpos(forwardDotRightTopForwardRotatedScreenPos);
	forwardDotRightTopBackwardRotatedScreenPos = Normalizescreenpos(forwardDotRightTopBackwardRotatedScreenPos);
	forwardDotLeftTopBackwardRotatedScreenPos = Normalizescreenpos(forwardDotLeftTopBackwardRotatedScreenPos);

	VERTEX vertices[8];
	vertices[0] = { forwardDotLeftBottomForwardRotatedScreenPos.x,forwardDotLeftBottomForwardRotatedScreenPos.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
	vertices[1] = { forwardDotRightBottomForwardRotatedScreenPos.x,forwardDotRightBottomForwardRotatedScreenPos.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
	vertices[2] = { forwardDotRightBottomBackwardRotatedScreenPos.x,forwardDotRightBottomBackwardRotatedScreenPos.y,0.f,1.f,color };
	vertices[3] = { forwardDotLeftBottomBackwardRotatedScreenPos.x,forwardDotLeftBottomBackwardRotatedScreenPos.y,0.f,1.f,color };
	vertices[4] = { forwardDotLeftTopForwardRotatedScreenPos.x,forwardDotLeftTopForwardRotatedScreenPos.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
	vertices[5] = { forwardDotRightTopForwardRotatedScreenPos.x,forwardDotRightTopForwardRotatedScreenPos.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
	vertices[6] = { forwardDotRightTopBackwardRotatedScreenPos.x,forwardDotRightTopBackwardRotatedScreenPos.y,0.f,1.f,color };
	vertices[7] = { forwardDotLeftTopBackwardRotatedScreenPos.x,forwardDotLeftTopBackwardRotatedScreenPos.y,0.f,1.f,color };

	WORD indices[24] = { 0, 1, 1, 2,2,3 ,3,0,4,5,5,6,6,7,7,4,0,4,1,5,2,6,3,7 };
	DirectX.Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 8, 12, indices, D3DFMT_INDEX16, vertices, sizeof(VERTEX));
	////bottom base
	//DrawLineVec3(forwardDotLeftBottomForwardRotatedScreenPos, forwardDotRightBottomForwardRotatedScreenPos, D3DCOLOR_ARGB(255, 255, 0, 0), thickness);
	//DrawLineVec3(forwardDotRightBottomForwardRotatedScreenPos, forwardDotRightBottomBackwardRotatedScreenPos, color, thickness);
	//DrawLineVec3(forwardDotRightBottomBackwardRotatedScreenPos, forwardDotLeftBottomBackwardRotatedScreenPos, color, thickness);
	//DrawLineVec3(forwardDotLeftBottomBackwardRotatedScreenPos, forwardDotLeftBottomForwardRotatedScreenPos, color, thickness);

	////top base
	//DrawLineVec3(forwardDotLeftTopForwardRotatedScreenPos, forwardDotRightTopForwardRotatedScreenPos, D3DCOLOR_ARGB(255, 255, 0, 0), thickness);
	//DrawLineVec3(forwardDotRightTopForwardRotatedScreenPos, forwardDotRightTopBackwardRotatedScreenPos, color, thickness);
	//DrawLineVec3(forwardDotRightTopBackwardRotatedScreenPos, forwardDotLeftTopBackwardRotatedScreenPos, color, thickness);
	//DrawLineVec3(forwardDotLeftTopBackwardRotatedScreenPos, forwardDotLeftTopForwardRotatedScreenPos, color, thickness);

	////collumns
	//DrawLineVec3(forwardDotLeftBottomForwardRotatedScreenPos, forwardDotLeftTopForwardRotatedScreenPos, D3DCOLOR_ARGB(255, 255, 0, 0), thickness);
	//DrawLineVec3(forwardDotRightBottomForwardRotatedScreenPos, forwardDotRightTopForwardRotatedScreenPos, D3DCOLOR_ARGB(255, 255, 0, 0), thickness);
	//DrawLineVec3(forwardDotRightBottomBackwardRotatedScreenPos, forwardDotRightTopBackwardRotatedScreenPos, color, thickness);
	//DrawLineVec3(forwardDotLeftBottomBackwardRotatedScreenPos, forwardDotLeftTopBackwardRotatedScreenPos, color, thickness);
}

static ProjectileInfo get_first_bullet()
{
	uintptr_t weaponslist = ReadPM<uintptr_t>(val.LocalOwnedUnit.weaponsinfo + 0x2D0);
	uintptr_t first_weapon = ReadPM<uintptr_t>(weaponslist + 0x0);
	uintptr_t weaponsinfo = ReadPM<uintptr_t>(first_weapon + 0x2A8);
	uintptr_t roundlist = ReadPM<uintptr_t>(weaponsinfo + 0x98);
	uintptr_t first_round = ReadPM<uintptr_t>(roundlist + 0x0);
	return ReadPM<ProjectileInfo>(first_round);
}

static ProjectileInfo get_current_bullet()
{
	ProjectileInfo currentbulletinfo;
	uintptr_t weaponslist = ReadPM<uintptr_t>(val.LocalOwnedUnit.weaponsinfo + 0x320); //48 8b 8e ? ? ? ? 48 89 8c 24 ? ? ? ? 48 89 84 24 ? ? ? ? 48 85 c0
	uintptr_t first_weapon = ReadPM<uintptr_t>(weaponslist + 0x0); //41 08 85 ? ? ? ? 41 0f b6 85 CanFire
	uint8_t loadedammo_index = ReadPM<uint8_t>(first_weapon + 0x4F4); 
	uintptr_t weaponsinfo = ReadPM<uintptr_t>(first_weapon + 0x340); 
	uintptr_t round = ReadPM<uintptr_t>(weaponsinfo + 0xA0 *loadedammo_index); //round + 0xA0 = numofshells, round + 0x14C = CanShoot
	//uintptr_t round_ptr = ReadPM<uintptr_t>(round + 0x0);
	currentbulletinfo.NamePtr = ReadPM<uintptr_t>(round + 0x10);
	ProjectileInfoBallisticComputer bulletinfo = ReadPM<ProjectileInfoBallisticComputer>(val.BallisticComputer);
	currentbulletinfo.Caliber = bulletinfo.Caliber;
	currentbulletinfo.ProjMass = bulletinfo.ProjMass;
	currentbulletinfo.ProjSpeed = bulletinfo.ProjSpeed;
	currentbulletinfo.ShellLenght = bulletinfo.ShellLenght;
	return currentbulletinfo;
}

static WeaponPositionInfo get_turret()
{
	uintptr_t weaponspositions = ReadPM<uintptr_t>(val.LocalOwnedUnit.weaponsinfo + 0xD0);
	return ReadPM<WeaponPositionInfo>(weaponspositions);
}

static Vector2 get_turret_rotation()
{
	uintptr_t turretrotationptr = ReadPM<uintptr_t>(val.LocalOwnedUnit.weaponsinfo + 0x190);
	return ReadPM<Vector2>(turretrotationptr+0x38);
}

static Vector3 predict_bullet_drop(Vector3 localposition, Vector3 localvelocity, Vector3 targetposition, Vector3 target_velocity, float bullet_speed)
{
	float distance = GetDistance(localposition, targetposition);
	float localspeed = hypot(localvelocity.x, localvelocity.y, localvelocity.z);

	/*float a0 = 173.958;
	float a1 = -0.0190192;*/
	float currentbulletspeed = bullet_speed + localspeed; //calculate rocketspeed based on current distance

	float travel_time = distance / currentbulletspeed;
	Vector3 pred_destination = targetposition + (target_velocity)*travel_time; //predict position of impact
	if (bullet_speed)
		pred_destination.y += 0.5f * 9.81f * travel_time * travel_time;

	float predictdistance = GetDistance(localposition, pred_destination); //get distance of the predicted impact

	return pred_destination;
}

static bool ccip_release_hint(Vector3 x1, Vector3 x2, Vector3 z1, Vector3 z2, Vector3* playerpositions)
{
	for (int i = 0; i <= 99; i++)
	{
		Vector3 playerpos = playerpositions[i];
		if (playerpos.x < x1.x && playerpos.x > x2.x &&
			playerpos.z < z1.z && playerpos.z > z2.z)
			return true;
		else
			continue;
	}
	return false;
}

static void getbombdroppermission()
{
	uintptr_t BallisticComputer = ReadPM<uintptr_t>(val.Game + 0x440);
	Vector3 Bomb_predicted_impactpoint = ReadPM<Vector3>(BallisticComputer + 0x19AC);
	Vector3 x1, x2, z1, z2;
	float radius = 5.f;
	x1 = Bomb_predicted_impactpoint; x1.x += radius;
	x2 = Bomb_predicted_impactpoint; x2.x -= radius;
	z1 = Bomb_predicted_impactpoint; z1.z += radius;
	z2 = Bomb_predicted_impactpoint; z2.z -= radius;
	bool release = ccip_release_hint(x1, x2, z1, z2, val.playerpositions);
	if (release)
		val.drop_bomb = true;
	else
		val.drop_bomb = false;
}

static float GetDragConstant(float LocalPosY)
{
	float max_alt = 18300.0f;
	float alt_mult = 1.225f;
	float clamped_alt = fmin(LocalPosY, max_alt);
	float unk_1 = 2.2871901e-19f, unk_2 = 5.8355603e-14f,
		unk_3 = 0.00000000353118f, unk_4 = 0.000095938703f;


	return alt_mult *
		((max_alt / std::fmax(LocalPosY, max_alt)) *
			((((((unk_1 * clamped_alt) - unk_2) * clamped_alt) + unk_3) *
				clamped_alt) -
				unk_4) *
			clamped_alt +
			1.0f);
}

static float GetBallisticCoeff(float BulletLength, float BulletMass, float BulletCaliber, float DragConstant)
{
	return -1.0f *
		(DragConstant * static_cast<float>(M_PI) * 0.5f *
			std::pow(BulletCaliber * 0.5f, 2.0f) *
			BulletLength) /
		BulletMass;
}

static float getDensity(float alt)
{
	float v1; // xmm0_4
	float v3; // [esp+0h] [ebp-4h]

	v1 = alt;
	if (alt >= 18300.f)
		alt = 18300.f;
	if (18300.f <= v1)
		v3 = v1;
	else
		v3 = 18300.f;

	float densityCoeffs[] = { 1.0, -9.59387e-05, 3.53118e-09, -5.83556e-14, 2.28719e-19 };
	//float density = evalPolynom(densityCoeffs, alt) * 1.225
	float density = (alt * (((densityCoeffs[4] * alt + densityCoeffs[3]) * alt + densityCoeffs[2]) * alt + densityCoeffs[1]) + densityCoeffs[0])
		* 1.225f
		* (18300.f
			/ v3);
	return density;
}

static Vector3 calc_forestall(Vector3 localposition, Vector3 localvelocity, Vector3 targetposition, Vector3 target_velocity, float bullet_speed)
{
	float v6; // xmm3_4
	float v7; // xmm5_4
	float v8; // xmm0_4
	Vector3 v9; // [esp+0h] [ebp-Ch]

	float bulletspeed = bullet_speed;



	if (bulletspeed < 0.0001)
		return { 0,0,0 };
	v6 = targetposition.y - localposition.y;
	v7 = targetposition.z - localposition.z;
	//v8 = GetTimeToTargetRGivenInitialSpeedS(-GetDragConstant(localposition.y), bullet_speed, targetposition, bullet_speed, false);
	v8 = sqrtf((((targetposition.x - localposition.x) * (targetposition.x - localposition.x)) + (v6 * v6)) + (v7 * v7)) / bulletspeed;
	v9.x = targetposition.x + (target_velocity.x * v8);
	v9.y = targetposition.y + (target_velocity.y * v8);
	v9.z = targetposition.z + (target_velocity.z * v8);
	v9.y = (((v8 * v8) * 9.81f) * 0.5) + v9.y;

	return v9;
}

static double GetTimeToTargetRGivenInitialSpeedS(double k, double vInfinity, double rX, double rY, double s, bool highArc) {
	double kRX = k * rX, kRY = k * rY, kRXSq = kRX * kRX, sS = s * s;
	double twoKVInfinityRY = vInfinity * (kRY + kRY), kVInfinity = k * vInfinity;
	double a0 = rX * rX + rY * rY, a1 = (k + k) * a0;
	double a2 = kRXSq + kRY * kRY + twoKVInfinityRY - sS;
	double a3 = twoKVInfinityRY * k, a4 = kVInfinity * kVInfinity;
	double maxInvRelError = 10.0;
	double maxV0YSq = sS - kRXSq;
	double e, de, u, uDelta = 0;

	if (highArc) {
		double minusB = std::sqrt(maxV0YSq) - kRY;
		double determ = minusB * minusB - (twoKVInfinityRY + twoKVInfinityRY);
		u = (kVInfinity + kVInfinity) / (minusB + std::sqrt(determ));
		maxInvRelError = -maxInvRelError;
	}
	else if (rY < 0) {
		double minusB = -std::sqrt(maxV0YSq) - kRY;
		double determ = minusB * minusB - (twoKVInfinityRY + twoKVInfinityRY);
		u = (minusB - std::sqrt(determ)) / (rY + rY);

		u = min(s / rX - k, u);
	}
	else u = s / std::sqrt(a0) - k;

	int it = 0;
	for (; it < 12; ++it, uDelta = e / de, u -= 1.9 * uDelta) {
		de = a0 * u;
		e = de + a1;
		de = de + e;
		e = e * u + a2;
		de = de * u + e;
		e = e * u + a3;
		e = (e * u + a4) * u;
		de = de * u * u - a4;
		if (!(u > 0 && de * maxInvRelError > 0 && e > 0)) break;
	}
	u += 0.9 * uDelta;

	for (; u > 0 && it < 12; ++it) {
		de = a0 * u;
		e = de + a1;
		de = de + e;
		e = e * u + a2;
		de = de * u + e;
		e = e * u + a3;
		e = (e * u + a4) * u;
		de = de * u * u - a4;
		uDelta = e / de;
		u -= uDelta;
		if (!(de * maxInvRelError > 0)) break;
		if (uDelta * maxInvRelError < u && u > 0) return 1 / u;
	}
	return 0;
}

static float time_to_target(float initial_velocity, Vector3 target_position, Vector3 target_velocity, Vector3 local_position, Vector3 local_velocity)
{
	if (initial_velocity < 1.f) return 0.f;
	float distance = GetDistance(local_position, target_position);
	float basic_time = distance / initial_velocity;
	float dt = 1.f / 96.f;
	//s(t) = −0.5f* g*t2 + v0*t + h0,

	float start_height = local_position.y;
	float target_height = target_position.y + basic_time * target_velocity.y;

	float current_bullet_height = start_height;
	float current_travel_time = 0.f;
	float current_velocity = initial_velocity;
	float height_precision = 0.f;

	while (current_travel_time < basic_time)
	{
		if (current_bullet_height < target_height && current_travel_time > basic_time)
			return current_travel_time;
		current_travel_time += dt;
		current_bullet_height = -0.5f * 9.81f * dt * dt + current_velocity * dt + current_bullet_height;
	}
}

static Vector3 calc_forestall_2(Vector3 localposition, Vector3 localvelocity, Vector3 targetposition, Vector3 target_velocity, ProjectileInfo bullet)
{
	float time_to_target;
	Vector3 v9;
	Vector3 deltavelocity = target_velocity;
	if (val.on_ground)
		deltavelocity -= localvelocity;

	float bulletspeed = bullet.ProjSpeed;
	if (bulletspeed < 0.0001)
		return { 0,0,0 };
	float Bullet_cross_section = M_PI * pow(bullet.Caliber * 0.5f, 2);
	float BC = GetBallisticCoeff(bullet.ShellLenght, bullet.ProjMass, bullet.Caliber, GetDragConstant(localposition.y));
	float airdensity = getDensity(localposition.y);
	float Drag_force = 0.5f * BC * airdensity * Bullet_cross_section;

	float k = Drag_force / bullet.ProjMass;
	float distance = GetDistance(localposition, targetposition);
	float range_X = GetDistance2D(Vector2{ localposition.x, localposition.z }, Vector2{ targetposition.x, targetposition.z });
	float range_Y = targetposition.y - localposition.y;
	time_to_target = GetTimeToTargetRGivenInitialSpeedS(k, bulletspeed, range_X, range_Y, bulletspeed, false);


	float multiplier = distance / (val.predictionmult * 1000.f);
	//float multiplier = distance / (mult * 1000.f);

	time_to_target *= (1.f + multiplier);

	v9.x = targetposition.x + (deltavelocity.x * time_to_target) + (0.5f * k * time_to_target * time_to_target);
	v9.y = targetposition.y + (deltavelocity.y * time_to_target) + (0.5f * k * time_to_target * time_to_target);
	v9.z = targetposition.z + (deltavelocity.z * time_to_target) + (0.5f * k * time_to_target * time_to_target);

	v9.y = (((time_to_target * time_to_target) * 9.81f) * 0.5) + v9.y;

	return v9;
}



static double magnitude(const Vector3& vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Vector3 scale(const Vector3& vec, float scalar) {
	return { (float)(vec.x * scalar), (float)(vec.y * scalar), (float)(vec.z * scalar) };
}

static float calculateInterceptionTime(Vector3 missile_pos, Vector3 missile_velocity, Vector3 target_pos, Vector3 target_velocity)
{
	Vector3 r_rel = target_pos - missile_pos;
	Vector3 v_rel = target_velocity - missile_velocity;

	float relativeSpeed = magnitude(v_rel);
	float time = magnitude(r_rel) / relativeSpeed;

	return time;
}

static Vector3 calculateInterceptionPoint(Vector3 target_pos, Vector3 target_velocity, Vector3 missile_pos, Vector3 missile_velocity)
{
	float time = calculateInterceptionTime(missile_pos, missile_velocity, target_pos, target_velocity);
	Vector3 Interception_Point = target_pos + scale(target_velocity, time);
	return Interception_Point;
}

struct Line //y = ax + b
{
	float slope;  // współczynnik kierunkowy	a
	float intercept;  // wyraz wolny			b
};

Line findLineEquation(Vector2 p1, Vector2 p2)
{
	Line line;
	// Obliczenie współczynnika kierunkowego
	if (p1.x == p2.x) {
		// Równoległa do osi y
		//line.slope = std::numeric_limits<double>::infinity(); // wartość nieskończona
		line.slope = 0;
		line.intercept = p1.x; // x-intercept
	}
	else {
		line.slope = (p2.y - p1.y) / (p2.x - p1.x);
		// Obliczenie wyrazu wolnego
		line.intercept = p1.y - line.slope * p1.x;
	}
	return line;
}

float distanceFromPointToLine(Vector2 p, Line line)
{
	// Obliczenie odległości punktu od prostej za pomocą wzoru
	if (line.slope == std::numeric_limits<float>::infinity()) {
		// Prosta równoległa do osi y
		return (p.x - line.intercept);
	}
	else {
		return (line.slope * p.x - p.y + line.intercept) / sqrt(pow(line.slope, 2) + 1);
	}
}

static float crossProduct(Vector2 missile_pos, Vector2 missile_stepforward, Vector2 target_pos) //line a--b point c
{
	float formula = (missile_stepforward.x - missile_pos.x) * (target_pos.y - missile_pos.y) - (missile_stepforward.y - missile_pos.y) * (target_pos.x - missile_pos.x);
	//if (formula == 0)
	return formula;
}

//static Vector2 calcGuidanceValues(Vector3 missile_pos, Vector3 missile_vel, Vector3 target_pos, bool ground_unit)
//{
//	Vector2 output;
//
//	if (missile_pos == Vector3{ 0,0,0 } || target_pos == Vector3{ 0,0,0 } || missile_vel == Vector3{ 0,0,0 })
//		return output;
//	float mult = 2.f;
//	//float distance = GetDistance(missile_pos, target_pos);
//	float distancexz = GetDistance2D({ missile_pos.x,missile_pos.z }, { target_pos.x,target_pos.z });
//	if (ground_unit)
//	{
//		if (distancexz > 3000.f)
//		{
//			target_pos.y += 1000.f;
//		}
//	}
//
//	Vector3 RelativeTargetPos = target_pos - missile_pos;
//	Vector3 zeromissilepos = { 0,0,0 };
//	Vector3 minimalmissilevel = missile_vel / 1000.f;
//	Vector3 forwardstep = zeromissilepos + minimalmissilevel;
//
//	//x
//	float xzcross = crossProduct(Vector2{ zeromissilepos.x,zeromissilepos.z }, Vector2{ forwardstep.x,forwardstep.z }, Vector2{ RelativeTargetPos.x,RelativeTargetPos.z });
//
//
//	if (abs(xzcross) < 10.f)
//	{
//		if (ground_unit)
//		{
//			float base = 0.2f;
//			float perc = (abs(xzcross) / 10.f);
//			float extra = perc * 1.8f;
//			mult = base + extra;
//		}
//		else
//		{
//			float base = 1.5f;
//			float perc = (abs(xzcross) / 10.f);
//			float extra = perc * 0.5f;
//			mult = base + extra;
//		}
//	}
//	else
//	{
//		mult = 2.f;
//	}
//
//	if (xzcross > 0)
//	{
//		output.x = -1.f * mult;
//	}
//	else if (xzcross < 0)
//	{
//		output.x = 1.f * mult;
//	}
//	else
//	{
//		output.x = 0.f;
//	}
//
//	//y
//	float v1 = GetDistance2D({ forwardstep.x,forwardstep.z }, { zeromissilepos.x,zeromissilepos.z });
//	float v2 = GetDistance2D({ RelativeTargetPos.x,RelativeTargetPos.z }, { zeromissilepos.x,zeromissilepos.z });
//	float ycross = crossProduct(Vector2{ zeromissilepos.x,zeromissilepos.y }, Vector2{ v1,forwardstep.y }, Vector2{ v2,RelativeTargetPos.y });
//
//	if (abs(ycross) < 10.f)
//	{
//		if (ground_unit)
//		{
//			float base = 0.2f;
//			float perc = (abs(ycross) / 10.f);
//			float extra = perc * 1.8f;
//			mult = base + extra;
//		}
//		else
//		{
//			float base = 1.5f;
//			float perc = (abs(ycross) / 10.f);
//			float extra = perc * 0.5f;
//			mult = base + extra;
//		}
//	}
//	else
//	{
//		mult = 2.f;
//	}
//
//	if (ycross > 0)
//	{
//		output.y = -1.f * mult;
//	}
//	else if (ycross < 0)
//	{
//		output.y = 1.f * mult;
//	}
//	else
//	{
//		output.y = 0.f;
//	}
//
//
//	return output;
//}

static Vector2 calcGuidanceValues(Vector3 missile_pos, Vector3 missile_vel, Vector3 target_pos, bool ground_unit)
{
	Vector2 output;
	if (missile_pos == Vector3{ 0,0,0 } || target_pos == Vector3{ 0,0,0 } || missile_vel == Vector3{ 0,0,0 })
		return output;

	float mult = 1.f;

	float distance = GetDistance(missile_pos, target_pos);
	float vellength = missile_vel.Length();
	if (ground_unit)
	{
		float distancexz = GetDistance2D({ missile_pos.x,missile_pos.z }, { target_pos.x,target_pos.z });
		if (distancexz > 3000.f)
		{
			target_pos.y += 1000.f;
		}
	}

	
	Vector3 RelativeTargetPos = target_pos - missile_pos;
	Vector3 zeromissilepos = { 0,0,0 };
	Vector3 minimalmissilevel = missile_vel / 1000.f;
	Vector3 forwardstep = zeromissilepos + minimalmissilevel;


	float xzcross = crossProduct(Vector2{ zeromissilepos.x,zeromissilepos.z }, Vector2{ forwardstep.x,forwardstep.z }, Vector2{ RelativeTargetPos.x,RelativeTargetPos.z });
	float v1 = GetDistance2D({ forwardstep.x,forwardstep.z }, { zeromissilepos.x,zeromissilepos.z });
	float v2 = GetDistance2D({ RelativeTargetPos.x,RelativeTargetPos.z }, { zeromissilepos.x,zeromissilepos.z });
	float ycross = crossProduct(Vector2{ zeromissilepos.x,zeromissilepos.y }, Vector2{ v1,forwardstep.y }, Vector2{ v2,RelativeTargetPos.y });

	
	

	if (ground_unit)
	{
		if (abs(xzcross) < 10.f)
		{
			float base = 0.2f;
			float perc = (abs(xzcross) / 10.f);
			float extra = perc * 1.8f;
			mult = base + extra;
		}
		else
		{
			mult = 2.f;
		}

		if (xzcross > 0)
		{
			output.x = -1.f * mult;
		}
		else if (xzcross < 0)
		{
			output.x = 1.f * mult;
		}
		else
		{
			output.x = 0.f;
		}

		if (abs(ycross) < 10.f)
		{
			float base = 0.2f;
			float perc = (abs(ycross) / 10.f);
			float extra = perc * 1.8f;
			mult = base + extra;
		}
		else
		{
			mult = 2.f;
		}

		if (ycross > 0)
		{
			output.y = -1.f * mult;
		}
		else if (ycross < 0)
		{
			output.y = 1.f * mult;
		}
		else
		{
			output.y = 0.f;
		}
	}
	else
	{
		if (vellength > 700.f)
			mult = 3.f;
		else if (vellength > 500.f)
			mult = 2.f;
		else if (vellength > 300.f)
			mult = 1.5f;
		else
			mult = 1.f;
			/*if (abs(xzcross) < 10.f)
			{
				float base = 1.5f;
				float perc = (abs(xzcross) / 10.f);
				float extra = perc * 0.5f;
				mult = base + extra;
			}
			else if (abs(xzcross) < 50.f)
			{
				float base = 2.f;
				float perc = ((abs(xzcross) - 10.f) / 40.f);
				float extra = perc * 1.f;
				mult = base + extra;
			}
			else
			{
				mult = 3.f;
			}*/
		

		if (xzcross > 0)
		{
			output.x = -1.f * mult;
		}
		else if (xzcross < 0)
		{
			output.x = 1.f * mult;
		}
		else
		{
			output.x = 0.f;
		}

		
			/*if (abs(ycross) < 10.f)
			{
				float base = 1.5f;
				float perc = (abs(ycross) / 10.f);
				float extra = perc * 0.5f;
				mult = base + extra;
			}
			else if (abs(ycross) < 50.f)
			{
				float base = 2.f;
				float perc = ((abs(ycross) - 10.f) / 40.f);
				float extra = perc * 1.f;
				mult = base + extra;
			}
			else
			{
				mult = 3.f;
			}*/
		

		if (ycross > 0)
		{
			output.y = -1.f * mult;
		}
		else if (ycross < 0)
		{
			output.y = 1.f * mult;
		}
		else
		{
			output.y = 0.f;
		}
	}

	return output;
}

float get_multiplier()
{
	WeaponPositionInfo turret = get_turret();
	float BC = GetBallisticCoeff(val.first_bullet.ShellLenght, val.first_bullet.ProjMass, val.first_bullet.Caliber, GetDragConstant(turret.FireportPos.y));
	float mult = 0.f;
	BC *= 100000.f;
	if (BC < -110.F)
		mult = BC * -0.015F;
	else if (BC >= -110.F && BC < -100.F)
		mult = BC * -0.018F;
	else if (BC >= -100.F && BC < -90.F)
		mult = BC * -0.021F;
	else if (BC >= -90.F && BC < -85.F)
		mult = BC * -0.028F;
	else if (BC >= -85.F && BC < -70.F)
		mult = BC * -0.049F;
	else if (BC >= -70.F && BC < -60.F)
		mult = BC * -0.052F;
	else if (BC >= -60.F && BC < -50.F)
		mult = BC * -0.075F;
	else if (BC >= -50.F && BC < -45.F)
		mult = BC * -0.115F;
	else if (BC >= -45.F && BC < -40.F)
		mult = BC * -0.15F;
	else if (BC >= -40.F && BC < -30.F)
		mult = BC * -0.22F;
	else if (BC >= -30.F && BC < -25.F)
		mult = BC * -0.27F;
	else if (BC >= -25.F && BC < -20.F)
		mult = BC * -0.47F;
	else if (BC >= -20.F && BC < -17.5F)
		mult = BC * -0.65F;
	else if (BC >= -17.5F && BC < -15.F)
		mult = BC * -1.F;
	else if (BC >= -15.F && BC < -10.F)
		mult = BC * -1.F;
	else if (BC >= -10.F && BC < -7.5F)
		mult = BC * -2.5F;
	else if (BC >= -7.5F && BC < -5.F)
		mult = BC * -4.F;
	else if (BC >= -5.F)
		mult = BC * -8.F;
	else mult = 14.f;

	float constantmult = GetMultByName(val.current_bullet_name);
	if (constantmult != 0.f)
		mult = constantmult;

	return mult;
}

static void drawpart(int index, Vector3 PlayerPosition, Vector3 groundvelocity, Vector3 pred, D3DCOLOR selected_color, OwnedUnit unit)
{
	DamageModel_part Part = DM_Array.Part[index];

	if (Part.TransformIndex >= 0 && Part.TransformIndex < 600)
	{
		Matrix Transform = transformsarray.TransformMatrix[Part.TransformIndex].Transform;

		Vector3 rotatedpartpos;
		Vector3 partpos;

		int indices_read_size = Part.IndexCount * sizeof(WORD);
		indices_list = ReadPM_secure<IndicesList>(Part.IndicesPtr, indices_read_size);

		int vertices_read_size = Part.VertexCount * sizeof(Vector4);
		Vertices_list = ReadPM_secure<Vector4List>(Part.VerticesPtr, vertices_read_size);

		if (Part.VertexCount >= 0 && Part.VertexCount <= 399)
		{
			RtlZeroMemory(&val.vertexlist_screenpos, sizeof(val.vertexlist_screenpos));
			for (int index = 0; index < Part.VertexCount; index++)
			{
				Vector4 partpos4 = Vertices_list.member[index];
				Vector4 partpos4rot;
				RotateDotvec4(Transform.member, partpos4, partpos4rot);
				partpos = { partpos4rot.x,partpos4rot.y,partpos4rot.z };
				RotateDot((float*)unit.Rotation_Matrix, partpos, rotatedpartpos);
				Vector3 final_vertice_pos = PlayerPosition + rotatedpartpos;
				if (Status.parts_RenderToPrediction)
				{
					final_vertice_pos = pred + rotatedpartpos;
				}
				WorldToScreenForBox(matrixx, final_vertice_pos, final_vertice_pos);
				final_vertice_pos = Normalizescreenpos(final_vertice_pos);
				val.vertexlist_screenpos[index] = { final_vertice_pos.x, final_vertice_pos.y, 0.f, 1.f, selected_color };

				/*std::string indexstr = to_string(index);
				char* indexmsg = (char*)indexstr.c_str();
				DrawText(indexmsg, final_vertice_pos.x, final_vertice_pos.y, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.defaultFont);*/

				/*std::string partname;
				GetPboNameString(Part.NamePtr, partname);
				char* namemsg = (char*)partname.c_str();
				DrawText(namemsg, final_vertice_pos.x, final_vertice_pos.y, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.defaultFont);*/
			}
			Drawing::drawchams(Part.VertexCount, val.vertexlist_screenpos, Part.IndexCount, indices_list.Index);
		}
	}
}

static void read_locals()
{
	val.Game = ReadPM<uintptr_t>(val.gameModule + Offset.Game);
	val.cgame = ReadPM<CGame>(val.Game);
	val.BallisticComputer = val.cgame.BallisticComputer;
	//val.MatrixPtr = val.gameModule + Offset.matrix;
	val.MatrixPtr = val.cgame.matrixptr + 0x1D0;
	val.LocalPlayerptr = ReadPM<uintptr_t>(val.gameModule + Offset.Localplayer);
	val.LocalPlayer = ReadPM<Player>(val.LocalPlayerptr);
	val.PlayerList = ReadPM<uintptr_t>(val.gameModule + Offset.Playerlist);
	val.PlayerList_size = ReadPM<uint32_t>(val.gameModule + Offset.Playerlist + 0x10);
	val.LocalPlayerTeam = val.LocalPlayer.PlayerTeam;
	val.LocalOwnedUnit = ReadPM<OwnedUnit>(val.LocalPlayer.ownedunitptr);
	val.LocalPlayerUnitIndex = val.LocalOwnedUnit.UnitIndex;
	val.LocalPlayerPosition = val.LocalOwnedUnit.PlayerPosition;
	val.LocalHeight = val.LocalOwnedUnit.boundsmax.y - val.LocalOwnedUnit.boundsmin.y;
	val.vehicleconfig = ReadPM<VehicleConfig>(val.LocalOwnedUnit.vehicleinfoptr);
	val.first_bullet = get_current_bullet();
	GetPboNameString(val.first_bullet.NamePtr, val.current_bullet_name);
	val.localgroundvelocity = ReadPM<Vector3>(val.LocalOwnedUnit.VelocityGroundPTR + 0x54);
	Dagor_airvelocity localairvelocitydagor = ReadPM<Dagor_airvelocity>(val.LocalOwnedUnit.AirVelocityPTR + 0x988);
	val.localairvelocity = { (float)localairvelocitydagor.x, (float)localairvelocitydagor.y,(float)localairvelocitydagor.z };
	/*if (val.localairvelocity.x != NULL || val.localairvelocity.y != NULL || val.localairvelocity.z != NULL)
	{
		val.in_air = true;
		val.on_ground = false;
	}
	else
	{
		val.on_ground = true;
		val.in_air = false;
	}*/
	if (val.LocalOwnedUnit.AirVelocityPTR)
	{
		val.in_air = true;
		val.on_ground = false;
	}
	else
	{
		val.on_ground = true;
		val.in_air = false;
	}

	//48 8b a9 ? ? ? ? 49 c1 e2 <- AllListData.ListIndexDataPtr
	//48 8d 0d ? ? ? ? 4c 8d 44 24 ? 45 31 c9 e8 ? ? ? ? 48 8b 44 24 ? 48 85 c0 74 ? 48 8d 4c 24 ? 31 d2 45 31 c0 ff d0 80 7c 24 ? ? 74 ? 49 8d bf <- AllListDataPtr
	uintptr_t AllListDataPtr = val.gameModule + Offset.all_list_data; 
	AllListData allListData = ReadPM<AllListData>(AllListDataPtr);
	int dataIndex = (0x23 & 0xFFFFFF) << 6; //missiles -> 0x23
	ListIndexData indexData = ReadPM<ListIndexData>(allListData.ListIndexDataPtr + dataIndex);
	if (indexData.ListPtrOffset && indexData.ExtraInfoOffset)
	{
		ListData listData = ReadPM<ListData>(allListData.ListDataPtr + indexData.ListPtrOffset * 0x20);
		uint32_t listsize = listData.Count;
		uintptr_t finalListPtr = listData.ListPtr + (indexData.ExtraInfoOffset << listData.ExtraInfoOffset);
		val.MissileListSize = listsize;
		val.MissileListptr = finalListPtr;
	}
	else
	{
		val.MissileListSize = 0;
		val.MissileListptr = 0;
	}


	//uintptr_t AllListDataPtr = val.gameModule + 0x4DDB018;
	//AllListData allListData = ReadPM<AllListData>(AllListDataPtr);
	//int dataIndex = (0x23 & 0xFFFFFF) << 6; //missiles -> 0x23
	//ListIndexData indexData = ReadPM<ListIndexData>(allListData.ListIndexDataPtr + dataIndex);
	//ListData listData = ReadPM<ListData>(ReadPM<uint16_t>(allListData.ListDataPtr + allListData.ListIndexDataPtr + 0xA)* 0x20);
	//uint32_t listsize = listData.Count;
	//uintptr_t finalListPtr = listData.ListPtr + (indexData.ExtraInfoOffset << listData.ExtraInfoOffset);
	//val.MissileListSize = listsize;
	//val.MissileListptr = finalListPtr;

	CGame cgame = ReadPM<CGame>(val.Game);
	ballisticcomputer computer = ReadPM<ballisticcomputer>(val.BallisticComputer);
	val.selected_targetunit_ptr = computer.pred_unit;
	val.selected_targetunit = ReadPM<OwnedUnit>(val.selected_targetunit_ptr);
	val.radar_pred_being_drawn = computer.pred_is_drawn;
	
}

static void get_bases()
{
	uintptr_t v1 = ReadPM<uintptr_t>(val.Game + 0x420);
	uintptr_t list = ReadPM<uintptr_t>(v1 + 0x110);
	uint32_t size = ReadPM<uintptr_t>(v1 + 0x120);
	for (int i = 0; i <= 7; i++)
	{
		uintptr_t baseptr = ReadPM<uintptr_t>(list + 0x8 * i);
		Base base = ReadPM<Base>(baseptr);
		Vector3 pos = ReadPM<Vector3>(base.PositionPTR + 0xE0);
		val.basesbuffer[i] = base;
		val.basespositionsbuffer[i] = pos;
	}
	val.basecount = size;
}

static int get_countermeasures(OwnedUnit Unit)
{
	int countermeasure_count = 0;
	
	uintptr_t weapons = Unit.weaponsinfo;
	List_with_Size list = ReadPM<List_with_Size>(weapons + 0x308); //48 8b 89 ? ? ? ? 48 89 08 48 89 50 ? c3 0f 57 c0
	uintptr_t WeaponListPTR = list.ListPtr;
	uint32_t WeaponListSize = list.Size_10;
	PtrList WeaponList = ReadPM<PtrList>(WeaponListPTR);
	if (WeaponListSize < 50)
	{
		for (int index = 0; index <= WeaponListSize; index++)
		{
			weapon currentweapon = ReadPM<weapon>(WeaponList.Ptr[index]);
			std::string weaponname;
			weapon_extra_info weaponinfo = ReadPM<weapon_extra_info>(currentweapon.NamePTR);
			uintptr_t weaponnameptr2 = weaponinfo.Weapon_Name_Ptr;
			GetPboNameString(weaponnameptr2, weaponname);

			if (weaponname.find("countermeasure") != std::string::npos)
			{
				int ammocount = weaponinfo.Remaining_ammo_count;
				countermeasure_count += ammocount;
			}
		}
	}
	return countermeasure_count;
}

static void get_offsets()
{
	uint64_t start = val.gameModule;
	uint64_t end = val.gameModule + val.gameModule_Size;

	Offset.Localplayer = get_offset_wrapper(sigs.LocalPlayer, start, end);
	Offset.Game = get_offset_wrapper(sigs.Game, start, end);
	Offset.Playerlist = get_offset_wrapper(sigs.PlayerList, start, end);
	Offset.hudinfo = get_offset_wrapper(sigs.HUDINFO, start, end);
	Offset.all_list_data = get_offset_wrapper(sigs.AllListData, start, end);

	Offset.forestall_bool = get_offset_wrapper_2(sigs.forestallbool, start, end);

	RtlZeroMemory(&sigs, sizeof(sigs));
}

static void get_target_unit()
{
	if (val.PlayerList_size <= 0 || val.PlayerList_size > 100 || val.LocalPlayer.GuiState != GuiState::ALIVE)
	{
		val.internal_target_unit = 0;
		return;
	}
	Vector2 screenmiddle = getScreenCentre();
	Matrix vmatrix = ReadPM<Matrix>(val.MatrixPtr);
	//Vector3* screenplayerpositions = (Vector3*)malloc(sizeof(Vector3)*100);
	float closest_distance = 10000.f;
	int index = -1;
	

	for (int i = 0; i < val.PlayerList_size; i++)
	{
		Vector3 AimPosition = val.playerpositions[i];
		if (AimPosition == Vector3{ 0.f, 0.f, 0.f })
		{
			continue;
		}
		Vector3 ScreenPosition;
		if (WorldToScreenForBox(vmatrix, AimPosition, ScreenPosition))
		{
			ScreenPosition = Normalizescreenpos(ScreenPosition);
			float distance = GetDistance2D(screenmiddle, { ScreenPosition.x, ScreenPosition.y });
			if (distance < closest_distance)
			{
				closest_distance = distance;
				index = i;
			}
			else
			{
				continue;
			}
		}
	}

	if (index >= 0 || index <= val.PlayerList_size)
	{
		int Playerarray_sizeread = sizeof(uintptr_t) * val.PlayerList_size;
		if (Playerarray_sizeread < 0 || Playerarray_sizeread > 1000000)Playerarray_sizeread = 0;
		PlayerArray Playerarray = ReadPM_secure<PlayerArray>(val.PlayerList, Playerarray_sizeread);
		Player targetplayer = ReadPM<Player>(Playerarray.Player[index]);

		if (Playerarray.Player[index] != val.LocalPlayerptr)
		{
			val.internal_target_unit = targetplayer.ownedunitptr;
			return;
		}
	}

	val.internal_target_unit = 0;
}

namespace features
{
	static void aimassist();
	static void enemymarkers();
	static void MouseAimInSim();
	static void noscopeshadow();
	static void extrazoom();
	static void superstats();
	static void AIMBOT(Vector3* aimpositions);
	static void SlaveTargetPoint(Vector3* slavepositions);
	static void AutoBombDrop();
	static void CameraChanger();
	static void sim_3rd_person();
	static void autoguide_mclos();
	/*static void patch_ArcadePenetrationIndicator(bool enable);*/
}

static void features::aimassist()
{
	if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	{
		uintptr_t hudinfoptr = ReadPM<uintptr_t>(val.gameModule + Offset.hudinfo);
		HUDINFO hudinfo = ReadPM<HUDINFO>(hudinfoptr);

		if (hudinfo.penetration_cross != 1)
			write<uint8_t>(hudinfoptr + 0x2A8, 1); // ("80 b8 ? ? ? ? ? 74 ? 0f 57 c0 0f 2e f8")
		if (hudinfo.selectable_air2 != 1)
			write<uint8_t>(hudinfoptr + 0x411, 1); // ("80 b9 ? ? ? ? ? 0f 85 ? ? ? ? e9 ? ? ? ? 48 8b 88")

		//if (ReadPM<uintptr_t>(hudinfoptr + 0x18) != hudvalues1.N00000069 ||
		//	ReadPM<uintptr_t>(hudinfoptr + 0x18 + 0x8) != hudvalues1.N0000006A ||
		//	ReadPM<uintptr_t>(hudinfoptr + 0x18 + 0x8 + 0x8) != hudvalues1.N000004FE ||
		//	ReadPM<uintptr_t>(hudinfoptr + 0x288) != hudvalues2.N000000B6 ||
		//	ReadPM<uintptr_t>(hudinfoptr + 0x288 + 0x8) != hudvalues2.N000002F0 ||
		//	ReadPM<uintptr_t>(hudinfoptr + 0x288 + 0x8 + 0x8) != hudvalues2.N0000031C ||
		//	ReadPM<uintptr_t>(hudinfoptr + 0x288 + 0x8 + 0x8 + 0x8) != hudvalues2.N000000B5 ||
		//	ReadPM<uintptr_t>(hudinfoptr + 0x288 + 0x8 + 0x8 + 0x8 + 0x8) != hudvalues2.N000002F1 ||
		//	ReadPM<uintptr_t>(hudinfoptr + 0x288 + 0x8 + 0x8 + 0x8 + 0x8 + 0x8) != hudvalues2.N000000B6)
		//{
		//	write<hudinfo1>(hudinfoptr + 0x18, hudvalues1); //!!!
		//	write<hudinfo2>(hudinfoptr + 0x288, hudvalues2); //!!!
		//	write<uint8_t>(hudinfoptr + 0x22, 0); //!!!
		//}

		//CGame Game = ReadPM<CGame>(val.Game); 
		uintptr_t GameOptics = ReadPM<uintptr_t>(val.gameModule + 0x4F6B298);

		if (ReadPM<float>(GameOptics + 0x17c) != 3000.f) // ("f3 0f 10 9d ? ? ? ? 66 41 83 bd")
			write<float>(GameOptics + 0x17c, 3000.f); //!
		if (ReadPM<float>(GameOptics + 0x180) != 2000.f)
			write<float>(GameOptics + 0x180, 2000.f); //! ("f3 45 0f 10 90 ? ? ? ? 84 db")
	}
}

static void features::enemymarkers()
{
	if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	{
		uintptr_t hudinfoptr2 = ReadPM<uintptr_t>(val.gameModule + Offset.hudinfo);
		if (Status.enemymarkers)
		{

			//write_if_not<uint8_t>(hudinfoptr2 + 0x1CC, 2);
		}
		else
		{

			//write_if_not<uint8_t>(hudinfoptr2 + 0x1CC, 1);
		}
	}
}

static void features::MouseAimInSim()
{
	//if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	//{
	//	uintptr_t hudinfoptr = ReadPM<uintptr_t>(val.gameModule + Offset.hudinfo);
	//	HUDINFO hudinfo = ReadPM<HUDINFO>(hudinfoptr);
	//	if (Status.aimmodeinsim)
	//	{
	//		if (hudinfo.mouseaim1 != 1)
	//			write<uint8_t>(hudinfoptr + 0x2E4, 1); //("80 b8 ? ? ? ? ? 0f 84 ? ? ? ? 80 3d ? ? ? ? ? 0f 85 ? ? ? ? 48 8b 4c 24")
	//		if (hudinfo.mouseaim2 != 1)
	//			write<uint8_t>(hudinfoptr + 0x2ED, 1); //("0f b6 80 ? ? ? ? 0a 05 ? ? ? ? 75 ? 48 8b 05")
	//		
	//		//write_if_not<uint8_t>(hudinfoptr + 0x2D9 + 0x4, 1); //Mouse_Aim
	//		//write_if_not<uint8_t>(hudinfoptr + 0x2D0 + 0x4, 1); //Mouse_Aim
	//		//write_if_not<uint8_t>(hudinfoptr + 0x2D4, 0); //HOVER
	//		//write_if_not<uint8_t>(hudinfoptr + 0x1DC + 0x4, 0); //Mouse_Aim
	//		//write_if_not<uint8_t>(hudinfoptr2 + 0x44, 1); //Third_Person_View DETECTED
	//		//write_if_not<uint8_t>(hudinfoptr + 0x45, 1); //Reticle_View ! 
	//	}
	//}
}

static void features::noscopeshadow()
{
	//if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	//{
	//	if (val.vehicleconfig.Zoom_ShadowMultiplier != (val.vehicleconfig.Zoom_FocusedMultiplier * 3))
	//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x204, (val.vehicleconfig.Zoom_FocusedMultiplier * 3)); //!!
	//}
}

static void features::extrazoom()
{
	//if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	//{
	//	float Zoom_Ratio = 5.f;

	//	if (val.Zoom_mult != 0.f && val.Zoom_mult != val.vehicleconfig.Zoom_Multiplier
	//		|| val.Zoom_mult != val.vehicleconfig.Zoom_Multiplier_Air
	//		)
	//	{
	//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x1F0, val.Zoom_mult); //!!
	//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x1FC, val.Zoom_mult); //!!
	//	}
	//	if (val.vehicleconfig.Zoom_FocusedMultiplier != 0.f && val.vehicleconfig.Zoom_FocusedMultiplier != (val.Zoom_mult / Zoom_Ratio)
	//		|| val.vehicleconfig.Zoom_FocusedMultiplier_Air != (val.Zoom_mult / Zoom_Ratio)
	//		)
	//	{
	//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x1EC, val.Zoom_mult / Zoom_Ratio); //!!
	//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x1F8, val.Zoom_mult / Zoom_Ratio); //!!
	//	}
	//}
}

static void features::superstats()
{
	if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	{
		uint8_t CCIPForRockets = val.vehicleconfig.haveCCIPForRocket;
		uint8_t CCIPForGun = val.vehicleconfig.haveCCIPForGun;
		uint8_t CCIPForBombs = val.vehicleconfig.haveCCIPForBombs;
		uint8_t CCRPForRockets = val.vehicleconfig.haveCCRPForRocket;
		uint8_t CCRPForGun = val.vehicleconfig.haveCCRPForGun;
		uint8_t CCRPForTurret = val.vehicleconfig.haveCCRPForTurret;
		uint8_t CCRPForBombs = val.vehicleconfig.haveCCRPForBombs;
		uint8_t RadarCScope = val.vehicleconfig.radarCScope;
		uint8_t havePointOfInterestDesignator = val.vehicleconfig.havePointOfInterestDesignator;
		uint8_t hasPointOfInterestMemory = val.vehicleconfig.hasPointOfInterestMemory;
		uint8_t hasMissileCommandLine = val.vehicleconfig.hasMissileCommandLine;
		uint8_t hasHelmetDesignator = val.vehicleconfig.hasHelmetDesignator;
		uint8_t haveOpticTurret = val.vehicleconfig.haveOpticTurret;
		uint8_t laserDesignator = val.vehicleconfig.laserDesignator;

		/*float airframeInfraRedBrightnessMult = val.vehicleconfig.airframeInfraRedBrightnessMult;
		float engineInfraRedBrightnessAspectMultRear = val.vehicleconfig.engineInfraRedBrightnessAspectMultRear;
		float engineInfraRedBrightnessAspectMultSide = val.vehicleconfig.engineInfraRedBrightnessAspectMultSide;
		float engineInfraRedBrightnessAspectMultFront = val.vehicleconfig.engineInfraRedBrightnessAspectMultFront;
		float radarCrossSectionAspectMultFront = val.vehicleconfig.radarCrossSectionAspectMultFront;
		float radarCrossSectionAspectMultSide = val.vehicleconfig.radarCrossSectionAspectMultSide;
		float radarCrossSectionAspectMultRear = val.vehicleconfig.radarCrossSectionAspectMultRear;
		float activeSonarReflectionMult = val.vehicleconfig.activeSonarReflectionMult;*/



		//if (CCIPForBombs != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03F1, 1); //!
		//if (CCRPForBombs != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03F5, 1); //!
		//if (CCIPForRockets != 1)
			write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x0406, 1); //!
		//if (CCIPForGun != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03EF, 1); //!
		//if (haveOpticTurret != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03F7, 1); //!
		//if (hasHelmetDesignator != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03FC, 1); //!
		//if (CCRPForRockets != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03EA, 1); //!
		//if (CCRPForGun != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03EB, 1); //!
		//if (CCRPForTurret != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03EC, 1); //!
		//if (RadarCScope != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03F6, 1); //!
		//if (havePointOfInterestDesignator != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03F8, 1); //!
		//if (hasPointOfInterestMemory != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03F9, 1); //!
		//if (hasMissileCommandLine != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03FA, 1); //!


		//if (laserDesignator != 1)
		//	write<uint8_t>(val.LocalOwnedUnit.vehicleinfoptr + 0x03FB, 1); //!
		//if (val.in_air)
		//{
		//	if (airframeInfraRedBrightnessMult != 0.01f)
		//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x0498, 0.01f);
		//	if (engineInfraRedBrightnessAspectMultRear != 0.01f)
		//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x049C, 0.01f);
		//	if (engineInfraRedBrightnessAspectMultSide != 0.01f)
		//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x04A0, 0.01f);
		//	if (engineInfraRedBrightnessAspectMultFront != 0.01f)
		//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x04A4, 0.01f);
		//	if (radarCrossSectionAspectMultFront != 0.01f)
		//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x04B4, 0.01f);
		//	if (radarCrossSectionAspectMultSide != 0.01f)
		//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x04B8, 0.01f);
		//	if (radarCrossSectionAspectMultRear != 0.01f)
		//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x04BC, 0.01f);
		//	//if (activeSonarReflectionMult != 0.01f)
		//	//	write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0x04C0, 0.01f);
		//}

	}
}

static void features::AIMBOT(Vector3* aimpositions)
{
	float closest_distance = 10000.f;
	int index = -1;
	Vector2 aim_reticle_screen;
	//matrixx = ReadPM<Matrix>(val.MatrixPtr);
	//WorldToScreenForBox(matrixx,aim_reticle, aim_reticle_screen);
	aim_reticle_screen = getScreenCentre();

	for (int i = 0; i <= 99; i++)
	{
		Vector3 AimPosition = aimpositions[i];
		if (AimPosition == Vector3{ 0.f, 0.f, 0.f })
			continue;
		Vector3 ScreenPosition;
		if (WorldToScreen(AimPosition, ScreenPosition))
		{
			ScreenPosition = Normalizescreenpos(ScreenPosition);
			float distance = GetDistance2D(aim_reticle_screen, { ScreenPosition.x, ScreenPosition.y });
			if (distance < closest_distance)
			{
				closest_distance = distance;
				index = i;
			}
			else
			{
				continue;
			}
		}
	}

	if (index < 0)
		return;
	Vector3 TargetAimPosition = aimpositions[index];
	matrixx = ReadPM<Matrix>(val.MatrixPtr);
	Vector3 TargetScreenPosition;
	if (WorldToScreenForBox(matrixx,TargetAimPosition, TargetScreenPosition))
	{
		TargetScreenPosition = Normalizescreenpos(TargetScreenPosition);
		float SmoothX = 1.1f;
		float SmoothY = 1.1f;
		int Fov = val.aimfov;
		int sleep = 10;
		

		if ((GetAsyncKeyState(val.aimbotkey)) && GetForegroundWindow() == Target.Window && GetDistance2D(aim_reticle_screen, { TargetScreenPosition.x, TargetScreenPosition.y }) <= Fov)
		{
			int x = (TargetScreenPosition.x - aim_reticle_screen.x) / SmoothX;
			int y = (TargetScreenPosition.y - aim_reticle_screen.y) / SmoothY;
			if (x <= Fov && y <= Fov)
				mouse_event(1U, x, y, NULL, NULL);
			Sleep(sleep);
		}
	}

}

static void features::SlaveTargetPoint(Vector3* aimpositions)
{
	if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	{
		float closest_distance = 5000.f;
		int index = -1;
		uintptr_t ballistic_computer = val.BallisticComputer;
		uintptr_t TargetPoint_Address = ReadPM<uintptr_t>(ballistic_computer+0x990);
		TargetPoint_Address = TargetPoint_Address + 0x38;

		for (int i = 0; i <= 99; i++)
		{
			Vector3 AimPosition = aimpositions[i];
			Vector3 TargetPointPosition = ReadPM<Vector3>(TargetPoint_Address);
			if (AimPosition == Vector3{ 0.f, 0.f, 0.f })
				continue;
			float distance = GetDistance(TargetPointPosition, AimPosition);
			if (distance < closest_distance)
			{
				closest_distance = distance;
				index = i;
			}
			else
			{
				continue;
			}
		}

		if (index < 0)
			return;
		Vector3 TargetAimPosition = aimpositions[index];
		if (TargetAimPosition != Vector3{ 0.f, 0.f, 0.f })
			write_if_not<Vector3>(TargetPoint_Address, TargetAimPosition);
	}
}

static void features::AutoBombDrop()
{
	if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	{
		if (val.drop_bomb && GetAsyncKeyState(val.autobombkey))
		{
			HoldKey(VK_SPACE, 57);
			Sleep(10);
			ReleaseKey(VK_SPACE, 57);
			while (val.drop_bomb == true) {}
		}
	}
}

static void features::CameraChanger() //0XBC = float VirtualCockpitCameraX
{
	//if (val.LocalPlayer.GuiState == GuiState::ALIVE)
	//{
	//	float CameraX = val.vehicleconfig.CameraX;
	//	float CameraY = val.vehicleconfig.CameraY;

	//	if (CameraX != val.CameraX)
	//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0xCC, val.CameraX); //!!
	//	if (CameraY != val.CameraY)
	//		write<float>(val.LocalOwnedUnit.vehicleinfoptr + 0xC8, val.CameraY); //!!
	//}
}

static void features::sim_3rd_person()
{
	//Vector2 current_camera_offsets = ReadPM<Vector2>(val.LocalOwnedUnit.vehicleinfoptr + 0xC4);

	//if (val.LocalPlayer.GuiState == GuiState::ALIVE && val.in_air && (current_camera_offsets.x != -25.f || current_camera_offsets.y != 3.5f))
	//	write<Vector2>(val.LocalOwnedUnit.vehicleinfoptr + 0xC4, {-25.f, 3.5f}); //!!
}

static void features::autoguide_mclos()
{
	if (val.MissileListSize < 1000 && val.MissileListSize>0 && val.LocalPlayer.GuiState == GuiState::ALIVE)
	{
		for (int i = 0; i <= val.MissileListSize; i++)
		{
			uintptr_t missileptr = ReadPM<uintptr_t>(val.MissileListptr + i * 0x8);
			Missile missile = ReadPM<Missile>(missileptr);
			/*std::string missilename = "";
			GetCleanMissileNameString(ReadPM<uintptr_t>(missile.cleannameptr + 0x10), missilename);
			if (missilename == "")
			{
				GetCleanMissileNameString(ReadPM<uintptr_t>(missile.cleannameptr + 0x30), missilename);
				if (missilename == "")
					continue;
			}*/
			if (missile.OwnerUnitPtr == val.LocalPlayer.ownedunitptr)
			{
				Vector3 missile_pos = missile.Position;
				Vector3 missile_vel = missile.Velocity;
				ballisticcomputer balcmp = ReadPM<ballisticcomputer>(val.cgame.BallisticComputer);
				OwnedUnit targetunit = ReadPM<OwnedUnit>(balcmp.pred_unit);
				//OwnedUnit targetunit = ReadPM<OwnedUnit>(val.internal_target_unit);
				Vector3 targetvelocity;
				bool ground_unit = false;
				if (targetunit.AirVelocityPTR)
				{
					Dagor_airvelocity airvelocitydagor = ReadPM<Dagor_airvelocity>(targetunit.AirVelocityPTR + 0xB20);
					targetvelocity = { (float)airvelocitydagor.x, (float)airvelocitydagor.y,(float)airvelocitydagor.z };
				}
				else
				{
					targetvelocity = ReadPM<Vector3>(targetunit.VelocityGroundPTR + 0x54);
					ground_unit = true;
				}
				Vector3 targetpos = targetunit.PlayerPosition;
				if (ground_unit)
				{
					vec3 max, min;
					vec3 forwardDotRightBottomBackward = vec3{ targetunit.boundsmin.x, targetunit.boundsmin.y, targetunit.boundsmin.z };
					vec3 forwardDotLeftTopForward = vec3{ targetunit.boundsmax.x, targetunit.boundsmax.y, targetunit.boundsmax.z };
					RotateDot((float*)targetunit.Rotation_Matrix, forwardDotRightBottomBackward, min);
					RotateDot((float*)targetunit.Rotation_Matrix, forwardDotLeftTopForward, max);
					max += targetunit.PlayerPosition;
					min += targetunit.PlayerPosition;
					targetpos = { (max.x + min.x) / 2, (max.y + min.y) / 2,(max.z + min.z) / 2 };
				}
				Vector3 intercept_point = calculateInterceptionPoint(targetpos, targetvelocity, missile_pos, missile_vel);
				//Vector2 guidance = calcGuidanceValues(missile_pos, missile_vel, intercept_point, ground_unit);
				/*if (ground_unit)
				{
					float distancexz = GetDistance2D({ missile_pos.x,missile_pos.z }, { intercept_point.x,intercept_point.z });
					if (distancexz > 3000.f)
					{
						intercept_point.y += 100.f;
					}
					else if (distancexz > 1000.f)
					{
						float perc = ((distancexz-1000.f) / 2000.f) * 100.f;
						intercept_point.y += perc;
					}
				}*/
				uintptr_t guidptr = ReadPM<uintptr_t>(val.BallisticComputer + 0x990);

				write<Vector3>(guidptr + 0x38, intercept_point);
				write<Vector3>(guidptr + 0x88, intercept_point);
				write<Vector3>(guidptr + 0xC0, intercept_point);
				write<Vector3>(guidptr + 0x100, intercept_point);
			}

		}
	}
}

static void renderChams(int index, Vector3 PlayerPosition, Vector3 groundvelocity, OwnedUnit unit)
{
	DirectX.Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);

	DamageModelContainer container = ReadPM<DamageModelContainer>(ReadPM<uintptr_t>(unit.damagemodelinfo + 0x58));
	//DM_Array = ReadPM<DamageModel_Array>(container.DamageModelArrayPtr);
	//transformsarray = ReadPM<TransformsArray>(ReadPM<uintptr_t>(ownedunit.TransformsPtr + 0x0));
	DM_Array = val.DM_Array_buff[index];
	transformsarray = val.transformsarray_buff[index];

	Vector3 pred;
	if (Status.parts_RenderToPrediction)
	{
		WeaponPositionInfo turret = get_turret();
		Vector3 aimpos = unit.PlayerPosition;
		pred = calc_forestall_2(turret.FireportPos, val.localgroundvelocity, aimpos, groundvelocity, val.first_bullet);
	}
	D3DCOLOR selected_color;
	matrixx = ReadPM<Matrix>(val.MatrixPtr);
	for (int z = 0; z <= container.DamageModelArraySize; z++)
	{
		if (z > 999)
			break;
		selected_color = val.DM_colors_buff[index][z];
		if (selected_color == Color.Parts_Body)
			drawpart(z, PlayerPosition, groundvelocity, pred, selected_color, unit);
	}
	for (int z = 0; z <= container.DamageModelArraySize; z++)
	{
		if (z > 999)
			break;
		selected_color = val.DM_colors_buff[index][z];
		if (selected_color != Color.Parts_Body && selected_color != D3DCOLOR_ARGB(0, 0, 0, 0))
			drawpart(z, PlayerPosition, groundvelocity, pred, selected_color, unit);
	}

	DirectX.Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

static void renderNameESP(uint8_t PlayerTeam, Vector3 ScreenPosition, char* namemsg, char* vehiclenamemsg, char* distmsg,
	uint8_t ReloadTime, char* reloadtimemsg, uint8_t isInvulnerable, std::string countermeasuresstr, char* countermeasuresmsg,
	bool in_air, bool cannotshoot, bool is_selected_target, int8_t visibility)
{
	if (PlayerTeam == val.LocalPlayerTeam && Status.showfriendly)
	{
		int drawindex = 0;
		if (Status.NAMEESP_name)
		{
			DrawText(namemsg, ScreenPosition.x, ScreenPosition.y, Color.friendlynamecolor, DirectX.defaultFont);
			drawindex += 10;
		}

		if (Status.NAMEESP_vehiclename)
		{
			DrawText(vehiclenamemsg, ScreenPosition.x, ScreenPosition.y + drawindex, Color.vehiclenamecolor, DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_distance)
		{
			DrawText(distmsg, ScreenPosition.x, ScreenPosition.y + drawindex, Color.distancecolor, DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_isreloading_cantshoot && ReloadTime != 100)
		{
			DrawText(reloadtimemsg, ScreenPosition.x, ScreenPosition.y + drawindex, Color.Cantshoot_reloading, DirectX.defaultFont);
			drawindex += 10;
		}

		if (isInvulnerable == 1)
		{
			DrawText(skCrypt("Invincible"), ScreenPosition.x, ScreenPosition.y + drawindex, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_flarecounter && countermeasuresstr != "")
		{
			DrawText(countermeasuresmsg, ScreenPosition.x, ScreenPosition.y + drawindex, Color.distancecolor, DirectX.defaultFont);
			drawindex += 10;
		}

		if (Status.NAMEESP_isreloading_cantshoot && !in_air && cannotshoot == true)
		{
			DrawText(skCrypt("Can't shoot"), ScreenPosition.x, ScreenPosition.y + drawindex, Color.Cantshoot_reloading, DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_currenttarget && is_selected_target)
		{
			DrawText(skCrypt("TARGET"), ScreenPosition.x, ScreenPosition.y + drawindex, D3DCOLOR_ARGB(255, 255, 0, 0), DirectX.defaultFont);
			drawindex += 10;
		}

	}
	else if (PlayerTeam != val.LocalPlayerTeam)
	{
		int drawindex = 0;
		if (Status.NAMEESP_name)
		{
			DrawText(namemsg, ScreenPosition.x, ScreenPosition.y, Color.enemynamecolor, DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_vehiclename)
		{
			DrawText(vehiclenamemsg, ScreenPosition.x, ScreenPosition.y + drawindex, Color.vehiclenamecolor, DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_distance)
		{
			DrawText(distmsg, ScreenPosition.x, ScreenPosition.y + drawindex, Color.distancecolor, DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_isreloading_cantshoot && ReloadTime != 100)
		{
			DrawText(reloadtimemsg, ScreenPosition.x, ScreenPosition.y + drawindex, Color.Cantshoot_reloading, DirectX.defaultFont);
			drawindex += 10;
		}

		if (isInvulnerable == 1)
		{
			DrawText(skCrypt("Invincible"), ScreenPosition.x, ScreenPosition.y + drawindex, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_flarecounter && countermeasuresstr != "")
		{
			DrawText(countermeasuresmsg, ScreenPosition.x, ScreenPosition.y + drawindex, Color.distancecolor, DirectX.defaultFont);
			drawindex += 10;
		}

		if (Status.NAMEESP_isreloading_cantshoot && !in_air && cannotshoot == true)
		{
			DrawText(skCrypt("Can't shoot"), ScreenPosition.x, ScreenPosition.y + drawindex, Color.Cantshoot_reloading, DirectX.defaultFont);
			drawindex += 10;
		}
		if (Status.NAMEESP_currenttarget && is_selected_target)
		{
			DrawText(skCrypt("TARGET"), ScreenPosition.x, ScreenPosition.y + drawindex, D3DCOLOR_ARGB(255, 255, 0, 0), DirectX.defaultFont);
			drawindex += 10;
		}
		if (visibility >= 1)
		{
			DrawText(skCrypt("VISIBLE"), ScreenPosition.x, ScreenPosition.y + drawindex, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.defaultFont);
			drawindex += 10;
		}
	}
}

static void renderPrediction(int index, OwnedUnit unit, Player player, Vector3 airvelocity, Vector3 groundvelocity, uint8_t PlayerTeam)
{
	vec3 forwardDotRightBottomBackward = vec3{ unit.boundsmin.x, unit.boundsmin.y, unit.boundsmin.z };
	vec3 forwardDotLeftTopForward = vec3{ unit.boundsmax.x, unit.boundsmax.y, unit.boundsmax.z };
	vec3 max, min;
	RotateDot((float*)unit.Rotation_Matrix, forwardDotRightBottomBackward, min);
	RotateDot((float*)unit.Rotation_Matrix, forwardDotLeftTopForward, max);
	max += unit.PlayerPosition;
	min += unit.PlayerPosition;

	Vector3 aimpos = { (max.x + min.x) / 2, (max.y + min.y) / 2,(max.z + min.z) / 2 };

	WeaponPositionInfo turret = get_turret();


	bool radar_pred = false;
	Vector3 pred;
	if (val.on_ground)
	{
		if (airvelocity.x != NULL || airvelocity.y != NULL || airvelocity.z != NULL)
		{
			ballisticcomputer ballcmp = ReadPM<ballisticcomputer>(val.BallisticComputer);
			if (ballcmp.pred_is_drawn && ballcmp.pred_unit == player.ownedunitptr)
			{
				pred = ballcmp.pred;
				radar_pred = true;
			}
			else
				pred = calc_forestall_2(turret.FireportPos, val.localgroundvelocity, aimpos, airvelocity, val.first_bullet);
		}
		else
		{
			pred = calc_forestall_2(turret.FireportPos, val.localgroundvelocity, aimpos, groundvelocity, val.first_bullet);
			//pred = prediction::calc_forestall_3(turret.FireportPos, val.localgroundvelocity, aimpos, groundvelocity, val.first_bullet);
		}
	}
	else if (val.in_air)
	{
		if (airvelocity.x != NULL || airvelocity.y != NULL || airvelocity.z != NULL)
		{
			if (Status.prediction && val.LocalPlayer.GuiState == GuiState::ALIVE)
			{

				ballisticcomputer ballcmp = ReadPM<ballisticcomputer>(val.BallisticComputer);
				if (ballcmp.pred_is_drawn && ballcmp.pred_unit == player.ownedunitptr)
				{
					pred = ballcmp.pred;
					radar_pred = true;
				}
				else
					pred = calc_forestall_2(turret.FireportPos, val.localairvelocity, aimpos, airvelocity, val.first_bullet);
			}
			//pred = prediction::calc_forestall_3(turret.FireportPos, val.localairvelocity, aimpos, airvelocity, val.first_bullet);
		}
		else
		{
			pred = calc_forestall_2(turret.FireportPos, val.localairvelocity, aimpos, groundvelocity, val.first_bullet);
			//pred = prediction::calc_forestall_3(turret.FireportPos, val.localairvelocity, aimpos, groundvelocity, val.first_bullet);
		}
	}
	if (pred.x != NULL && PlayerTeam != val.LocalPlayerTeam)
		val.aimbotpositions[index] = pred;

	Vector3 aimscreenpos, aimtargetscreenpos;
	if (WorldToScreen(pred, aimscreenpos))
	{
		aimscreenpos = Normalizescreenpos(aimscreenpos);
		if (WorldToScreen(aimpos, aimtargetscreenpos))
		{
			aimtargetscreenpos = Normalizescreenpos(aimtargetscreenpos);
			Drawing::Line(aimtargetscreenpos.x, aimtargetscreenpos.y, aimscreenpos.x, aimscreenpos.y, D3DCOLOR_ARGB(255, 255, 255, 255), 1.f);
		}
		Drawing::FilledCircle(aimscreenpos.x, aimscreenpos.y, 3, D3DCOLOR_ARGB(255, 255, 0, 0));
		if (radar_pred)
			Drawing::Circle(aimscreenpos.x, aimscreenpos.y, 15, D3DCOLOR_ARGB(255, 0, 255, 0));
	}
}

static void renderPlayerList(int distance, int &nearby_counter, std::string name, std::string vehiclename, std::string dist2)
{
	if (distance <= val.nearbydistance)
	{
		nearby_counter += 1;
		std::string msg = "";
		msg += name + " | ";
		msg += vehiclename + " | ";
		msg += dist2;
		char* nearbymsg = (char*)msg.c_str();
		DrawTextnoncenter(nearbymsg, 20, (Target.height / 2 - 200) + (25 * nearby_counter), Color.PlayerList, DirectX.nearby_warningFont);
	}
}

static void renderSnaplines(uint8_t PlayerTeam, Vector3 ScreenPosition)
{
	if (PlayerTeam == val.LocalPlayerTeam && Status.showfriendly)
	{
		Drawing::Line((Target.width / 2) - Overlay.OffsetLeft, Target.height - 100, ScreenPosition.x, ScreenPosition.y, Color.SnapLines_Friendly, 1.f);
	}
	else if (PlayerTeam != val.LocalPlayerTeam)
	{
		Drawing::Line((Target.width / 2) - Overlay.OffsetLeft, Target.height - 100, ScreenPosition.x, ScreenPosition.y, Color.SnapLines_Enemy, 1.f);
	}
}

static void renderMissileESP()
{
	if (val.MissileListSize < 1000 && val.MissileListSize>0 && val.LocalPlayer.GuiState == GuiState::ALIVE)
	{
		bool missile_warning = false;
		for (int i = 0; i <= val.MissileListSize; i++)
		{
			Missile missile = ReadPM<Missile>(ReadPM<uintptr_t>(val.MissileListptr + i * 0x8));
			Vector3 missile_pos = missile.Position;
			Vector3 missile_vel = missile.Velocity;
			//OwnedUnit missile_owner = ReadPM<OwnedUnit>(missile.OwnerUnitPtr);
			
			if (missile.GuidancePtr && missile.OwnerUnitPtr != val.LocalPlayer.ownedunitptr)
			{
				Missile_Guidance missileguidance = ReadPM<Missile_Guidance>(missile.GuidancePtr);
				
				if (missileguidance.TargetUnitId == val.LocalPlayerUnitIndex && missileguidance.IsLocked)
					missile_warning = true;
			}
			

			//if (missile.OwnerUnitPtr == val.LocalPlayer.ownedunitptr)
			//{
			//	/*ballisticcomputer balcmp = ReadPM<ballisticcomputer>(val.cgame.BallisticComputer);
			//	OwnedUnit targetunit = ReadPM<OwnedUnit>(balcmp.pred_unit);*/
			//	OwnedUnit targetunit = ReadPM<OwnedUnit>(val.internal_target_unit);
			//	Vector3 targetpos = targetunit.PlayerPosition;
			//	Vector3 targetvelocity;
			//	bool ground_unit = false;
			//	if (targetunit.AirVelocityPTR)
			//	{
			//		Dagor_airvelocity airvelocitydagor = ReadPM<Dagor_airvelocity>(targetunit.AirVelocityPTR + 0x988);
			//		targetvelocity = { (float)airvelocitydagor.x, (float)airvelocitydagor.y,(float)airvelocitydagor.z };
			//	}
			//	else
			//	{
			//		targetvelocity = ReadPM<Vector3>(targetunit.VelocityGroundPTR + 0x54);
			//		ground_unit = true;
			//	}
			//	Vector3 intercept_point = calculateInterceptionPoint(targetpos, targetvelocity, missile_pos, missile_vel);
			//	//Vector2 guidance = calcGuidanceValues(missile_pos, missile_vel, intercept_point, ground_unit);
			//	//uintptr_t guidptr = ReadPM<uintptr_t>(val.LocalPlayer.ownedunitptr + 0xBA8);
			//	//if (GetDistance(missile_pos, intercept_point))
			//	//write<Vector2>(guidptr + 0x2384, guidance); //

			//	float distance = GetDistance(missile_pos, intercept_point);
			//	float missile_velmag = missile_vel.Length();
			//	std::string distmsgstr = to_string(int(distance));
			//	char* distmsg = (char*)distmsgstr.c_str();
			//	std::string velmsgstr = to_string(int(missile_velmag));
			//	char* velmsg = (char*)velmsgstr.c_str();
			//	Vector3 scrpos;
			//	if (WorldToScreen(intercept_point, scrpos))
			//	{
			//		scrpos = Normalizescreenpos(scrpos);
			//		Drawing::FilledCircle(scrpos.x, scrpos.y, 2.f, D3DCOLOR_ARGB(255, 255, 0, 0));
			//		DrawText(distmsg, scrpos.x, scrpos.y + 2, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.defaultFont);
			//		DrawText(velmsg, scrpos.x, scrpos.y + 12, D3DCOLOR_ARGB(255, 255, 255, 255), DirectX.defaultFont);
			//	}
			//}

			int distance = GetDistance(val.LocalPlayerPosition, missile_pos);
			if (distance <= 0 || distance > 200000) continue;
			std::string dist2 = "Distance " + to_string(distance);
			char* distmsg = (char*)dist2.c_str();

			std::string missilename = "";
			GetCleanMissileNameString(ReadPM<uintptr_t>(missile.cleannameptr + 0x10), missilename);
			if (missilename == "")
			{
				GetCleanMissileNameString(ReadPM<uintptr_t>(missile.cleannameptr + 0x30), missilename);
				if (missilename == "")
					continue;
			}
			char* missilenamemsg = (char*)missilename.c_str();

			uint8_t missileteam = ReadPM<Player>(missile.OwnerPlayerPtr).PlayerTeam;

			if (missile_warning)
				DrawText("MISSILE TRACK", Target.width / 2, Target.height / 2 - 100, D3DCOLOR_ARGB(255, 255, 0, 0), DirectX.missile_warningFont);

			if (WorldToScreen(missile_pos, missile_pos))
			{
				missile_pos = Normalizescreenpos(missile_pos);

				if (missileteam == val.LocalPlayerTeam && Status.showfriendly && missile.OwnerPlayerPtr != val.LocalPlayerptr)
				{
					int drawindex = 0;
					DrawText("MISSILE", missile_pos.x, missile_pos.y + drawindex, Color.friendlynamecolor, DirectX.MissileFont);
					drawindex += 12;
					DrawText(missilenamemsg, missile_pos.x, missile_pos.y + drawindex, Color.friendlynamecolor, DirectX.defaultFont);
					drawindex += 12;
					DrawText(distmsg, missile_pos.x, missile_pos.y + drawindex, Color.distancecolor, DirectX.defaultFont);
					drawindex += 12;

					Drawing::Circle(missile_pos.x, missile_pos.y, 5, Color.friendlynamecolor);
				}
				else if (missileteam != val.LocalPlayerTeam)
				{
					int drawindex = 0;
					DrawText("MISSILE", missile_pos.x, missile_pos.y + drawindex, Color.enemynamecolor, DirectX.MissileFont);
					drawindex += 12;
					DrawText(missilenamemsg, missile_pos.x, missile_pos.y + drawindex, Color.enemynamecolor, DirectX.defaultFont);
					drawindex += 12;
					DrawText(distmsg, missile_pos.x, missile_pos.y + drawindex, Color.distancecolor, DirectX.defaultFont);
					drawindex += 12;

					Drawing::Circle(missile_pos.x, missile_pos.y, 5, Color.enemynamecolor);
				}
				else if (missile.OwnerPlayerPtr == val.LocalPlayerptr)
				{
					Drawing::Circle(missile_pos.x, missile_pos.y, 5, Color.friendlynamecolor);
				}
				else
					continue;
			}

		}
	}
}

static void renderBombRocketIndicator()
{
	uintptr_t BallisticComputer = val.BallisticComputer;
	Vector3 Bomb_predicted_impactpoint = ReadPM<Vector3>(BallisticComputer + 0x1974); //48 8b 88 ? ? ? ? 48 89 8c 24 ? ? ? ? 48 8b 8d

	Vector3 x1, x2, z1, z2;
	float radius = 12.f;
	x1 = Bomb_predicted_impactpoint; x1.x += radius;
	x2 = Bomb_predicted_impactpoint; x2.x -= radius;
	z1 = Bomb_predicted_impactpoint; z1.z += radius;
	z2 = Bomb_predicted_impactpoint; z2.z -= radius;
	bool release_hint = ccip_release_hint(x1, x2, z1, z2, val.playerpositions);
	Vector3 screenposbomb;

	VERTEX vertices[4];
	WORD indices[12] = { 0, 1, 2, 3, 0, 2, 0, 3, 1, 2, 1, 3 };

	if (WorldToScreen(Bomb_predicted_impactpoint, screenposbomb))
	{
		screenposbomb = Normalizescreenpos(screenposbomb);
		Matrix matrix = ReadPM<Matrix>(val.MatrixPtr);
		WorldToScreenForBox(matrix, x1, x1);
		WorldToScreenForBox(matrix, x2, x2);
		WorldToScreenForBox(matrix, z1, z1);
		WorldToScreenForBox(matrix, z2, z2);
		x1 = Normalizescreenpos(x1);
		x2 = Normalizescreenpos(x2);
		z1 = Normalizescreenpos(z1);
		z2 = Normalizescreenpos(z2);

		if (release_hint)
		{
			Drawing::Circle(screenposbomb.x, screenposbomb.y, 20, D3DCOLOR_ARGB(255, 0, 255, 0));

			vertices[0] = { x1.x,x1.y,0.f,1.f,D3DCOLOR_ARGB(255, 0, 255, 0) };
			vertices[1] = { x2.x,x2.y,0.f,1.f,D3DCOLOR_ARGB(255, 0, 255, 0) };
			vertices[2] = { z1.x,z1.y,0.f,1.f,D3DCOLOR_ARGB(255, 0, 255, 0) };
			vertices[3] = { z2.x,z2.y,0.f,1.f,D3DCOLOR_ARGB(255, 0, 255, 0) };
			DirectX.Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 4, 6, indices, D3DFMT_INDEX16, vertices, sizeof(VERTEX));
		}
		else
		{
			Drawing::Circle(screenposbomb.x, screenposbomb.y, 20, D3DCOLOR_ARGB(255, 255, 0, 0));

			vertices[0] = { x1.x,x1.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
			vertices[1] = { x2.x,x2.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
			vertices[2] = { z1.x,z1.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
			vertices[3] = { z2.x,z2.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
			DirectX.Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 4, 6, indices, D3DFMT_INDEX16, vertices, sizeof(VERTEX));
		}

	}

	Vector3 Rocket_predicted_impactpoint = ReadPM<Vector3>(BallisticComputer + 0x1CE8); //48 8b 80 ? ? ? ? 48 89 84 24 ? ? ? ? 48 8b 0d ? ? ? ? 83 b9 ? ? ? ? ? 0f 85
	radius = 3.f;
	x1 = Rocket_predicted_impactpoint; x1.x += radius;
	x2 = Rocket_predicted_impactpoint; x2.x -= radius;
	z1 = Rocket_predicted_impactpoint; z1.z += radius;
	z2 = Rocket_predicted_impactpoint; z2.z -= radius;
	release_hint = ccip_release_hint(x1, x2, z1, z2, val.playerpositions);

	if (WorldToScreen(Rocket_predicted_impactpoint, screenposbomb))
	{
		screenposbomb = Normalizescreenpos(screenposbomb);
		Matrix matrix = ReadPM<Matrix>(val.MatrixPtr);
		WorldToScreenForBox(matrix, x1, x1);
		WorldToScreenForBox(matrix, x2, x2);
		WorldToScreenForBox(matrix, z1, z1);
		WorldToScreenForBox(matrix, z2, z2);
		x1 = Normalizescreenpos(x1);
		x2 = Normalizescreenpos(x2);
		z1 = Normalizescreenpos(z1);
		z2 = Normalizescreenpos(z2);

		if (release_hint)
		{
			Drawing::Circle(screenposbomb.x, screenposbomb.y, 20, D3DCOLOR_ARGB(255, 0, 255, 0));

			vertices[0] = { x1.x,x1.y,0.f,1.f,D3DCOLOR_ARGB(255, 0, 255, 0) };
			vertices[1] = { x2.x,x2.y,0.f,1.f,D3DCOLOR_ARGB(255, 0, 255, 0) };
			vertices[2] = { z1.x,z1.y,0.f,1.f,D3DCOLOR_ARGB(255, 0, 255, 0) };
			vertices[3] = { z2.x,z2.y,0.f,1.f,D3DCOLOR_ARGB(255, 0, 255, 0) };
			DirectX.Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 4, 6, indices, D3DFMT_INDEX16, vertices, sizeof(VERTEX));
		}
		else
		{
			Drawing::Circle(screenposbomb.x, screenposbomb.y, 20, D3DCOLOR_ARGB(255, 255, 0, 0));

			vertices[0] = { x1.x,x1.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
			vertices[1] = { x2.x,x2.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
			vertices[2] = { z1.x,z1.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
			vertices[3] = { z2.x,z2.y,0.f,1.f,D3DCOLOR_ARGB(255, 255, 0, 0) };
			DirectX.Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 4, 6, indices, D3DFMT_INDEX16, vertices, sizeof(VERTEX));
		}

	}
}

static Vector3 calculate_projectile_3D_Velocity(float bullet_speed, Vector2 turret_rotation)
{
	Vector3 velocity;
	velocity.x = bullet_speed * cos(turret_rotation.y * M_PI / 180.F);
	velocity.y = bullet_speed * sin(turret_rotation.y * M_PI / 180.F);

	velocity.z = velocity.x * sin(turret_rotation.x * M_PI / 180.F) * -1.f;
	velocity.x = velocity.x * cos(turret_rotation.x * M_PI / 180.F);

	return velocity;
}

void wait_if_guistate(int &timer, int64_t wait_time_sec, int8_t GuiState)
{
	int8_t GUISTATE;
	timer = 0;
	while (timer < wait_time_sec)
	{
		timer += 1;
		GUISTATE = val.LocalPlayer.GuiState;
		if (GUISTATE != GuiState)
		{
			break;
		}
		Sleep(1000);
	}
	timer = 0;
}

//void bomberbot()
//{
//	int width = 1920;
//	int height = 1080;
//	int timer = 0;
//
//	int match_search_timeout = 10; //MENU (seconds)
//
//	int sleep_beggining_of_a_match = 500; //ALIVE (ms)
//	float height_offset = 500.f; //ALIVE
//	int after_bombing_timer = 1; //ALIVE (seconds)
//	int base_radius = 200; //ALIVE
//	int distance_to_open_bombbay = 3000; //ALIVE
//	int distance_to_level_flight = 500; //ALIVE
//	bool dive = false; //ALIVE
//	bool relative_to_base = true; //ALIVE
//
//
//	while (true)
//	{
//		if (Status.bomberbot)
//		{
//			uint8_t GUISTATE;
//			GUISTATE = val.LocalPlayer.GuiState;
//			if (GUISTATE == GuiState::MENU)
//			{
//				Sleep(2000);
//				while (GUISTATE == GuiState::MENU)
//				{
//					int red_slot1, red_slot2, red_slot3, temp;
//					GUISTATE = val.LocalPlayer.GuiState;
//					if (GUISTATE != GuiState::MENU)
//						break;
//					SetForegroundWindow(Target.Window);
//					ClickKey(0x0D, 28); //ENTER
//					Sleep(500);
//					ClickKey(0x0D, 28); //ENTER
//					Sleep(500);
//					ClickOnScreen(Vector2{ (float)(width * 0.4167f), (float)(height * 0.6944f) }); //Spend
//					Sleep(500);
//					ClickOnScreen(Vector2{ (float)(width * 0.7573f), (float)(height * 0.6453f) }); //Finish
//					//Sleep(500);
//					//ClickOnScreen(Vector2{ (float)(width * 0.8973f), (float)(height * 0.3564f) }); //Close
//					GUISTATE = val.LocalPlayer.GuiState;
//					if (GUISTATE != GuiState::MENU)
//						break;
//					ClickKey(VK_ESCAPE, 1); //ESCAPE
//					Sleep(2000);
//
//					getPixelColor(red_slot1, temp, temp, vehicleslot.slot2_check.x, vehicleslot.slot2_check.y);
//					getPixelColor(red_slot2, temp, temp, vehicleslot.slot1_check.x, vehicleslot.slot1_check.y);
//					getPixelColor(red_slot3, temp, temp, vehicleslot.slot4_check.x, vehicleslot.slot4_check.y);
//
//					if (red_slot3 < 100)
//					{
//						ClickOnScreen(vehicleslot.slot4);
//					}
//					else if (red_slot1 < 100)
//					{
//						ClickOnScreen(vehicleslot.slot2);
//					}
//					else if (red_slot2 < 100)
//					{
//						ClickOnScreen(vehicleslot.slot1);
//					}
//
//					Sleep(1000);
//
//					ClickOnScreen(Vector2{ (float)(width / 2), (float)(height * 0.034f) }); //To Battle!
//					GUISTATE = val.LocalPlayer.GuiState;
//					if (GUISTATE != GuiState::MENU)
//						break;
//					//Sleep(20000);
//					while (timer < match_search_timeout)
//					{
//						timer += 1;
//						GUISTATE = val.LocalPlayer.GuiState;
//						if (GUISTATE != GuiState::MENU)
//						{
//							break;
//						}
//						Sleep(1000);
//					}
//					timer = 0;
//				}
//			}
//			//else if (GUISTATE == GuiState::SPAWN_MENU) //DOESNT HAPPEN IN AIR RB!
//			//{
//			//	Sleep(10000);
//			//	SetForegroundWindow(Target.Window);
//			//	ClickKey(0x0D, 28); //ENTER
//			//	Sleep(10000);
//			//	while (GUISTATE == GuiState::SPAWN_MENU)
//			//	{
//			//		GUISTATE = val.LocalPlayer.GuiState;
//			//		if (GUISTATE != GuiState::SPAWN_MENU)
//			//			break;
//			//		SetForegroundWindow(Target.Window);
//			//		ClickKey(0x0D, 28); //ENTER
//			//		Sleep(5000);
//			//	}
//			//}
//			else if (GUISTATE == GuiState::ALIVE)
//			{
//				Vector3 Target1, Target2, Target3, Target4, temp, target_point_location, closest_target, second_closest_target;
//				Base currentbase;
//				int currentbaseindex;
//				Vector3 Targetsarray[4];
//				float distancearray[4];
//				float smallest_distance, second_smallest_distance, final_distance;
//				uintptr_t BallisticComputer = ReadPM<uintptr_t>(val.Game + 0x440);
//				Status.aimassist = true;
//				Status.SuperStats = true;
//				HoldKey(VK_LSHIFT, 42); //LSHIFT
//				Sleep(sleep_beggining_of_a_match);
//				SetForegroundWindow(Target.Window);
//				ClickKey(VK_F4, 62); //F4
//				Sleep(1000);
//				SetForegroundWindow(Target.Window);
//				//while (Target1 == Target2) //CHECKS FOR WHEN BASES SPAWN
//				//{
//				//	ClickKey(0x37, 8); //7
//				//	Sleep(200);
//				//	Target1 = ReadPM<Vector3>(BallisticComputer + 0x97C);
//				//	Sleep(200);
//				//	ClickKey(0x37, 8); //7
//				//	Sleep(200);
//				//	Target2 = ReadPM<Vector3>(BallisticComputer + 0x97C);
//				//	GUISTATE = val.LocalPlayer.GuiState;
//				//	if (GUISTATE != GuiState::ALIVE || !IsAlive(val.LocalOwnedUnit))
//				//		break;
//				//}
//				//RtlZeroMemory(&Target1, sizeof(Vector3));
//				//RtlZeroMemory(&Target2, sizeof(Vector3));
//				//RtlZeroMemory(&Target3, sizeof(Vector3));
//				//RtlZeroMemory(&Target4, sizeof(Vector3));
//
//				//while (Target1 == Target2 //|| Target1 == Target3 || Target1 == Target4 ||
//				//	//Target2 == Target1 || Target2 == Target3 || Target2 == Target4 ||
//				//	//Target3 == Target2 || Target3 == Target1 || Target3 == Target4 ||
//				//	//Target4 == Target2 || Target4 == Target3 || Target4 == Target1
//				//	) //GETS BASES
//				//{
//				//	ClickKey(0x37, 8); //7
//				//	Sleep(200);
//				//	Target1 = ReadPM<Vector3>(BallisticComputer + 0x97C);
//				//	Sleep(200);
//				//	ClickKey(0x37, 8); //7
//				//	Sleep(200);
//				//	Target2 = ReadPM<Vector3>(BallisticComputer + 0x97C);
//				//	Sleep(200);
//				//	ClickKey(0x37, 8); //7
//				//	Sleep(200);
//				//	Target3 = ReadPM<Vector3>(BallisticComputer + 0x97C);
//				//	Sleep(200);
//				//	ClickKey(0x37, 8); //7
//				//	Sleep(200);
//				//	Target4 = ReadPM<Vector3>(BallisticComputer + 0x97C);
//				//	Sleep(200);
//				//}
//				//distancearray[0] = GetDistance(val.LocalOwnedUnit.PlayerPosition, Target1);
//				//distancearray[1] = GetDistance(val.LocalOwnedUnit.PlayerPosition, Target2);
//				//distancearray[2] = GetDistance(val.LocalOwnedUnit.PlayerPosition, Target3);
//				//distancearray[3] = GetDistance(val.LocalOwnedUnit.PlayerPosition, Target4);
//				//smallest_distance = distancearray[0];
//				//second_smallest_distance = distancearray[0];
//				//for (int i = 0; i <= 3; i++) 
//				//{
//				//	smallest_distance = max(smallest_distance, distancearray[i]);
//				//}
//				//if (smallest_distance == distancearray[0])
//				//{
//				//	closest_target = Target1;
//				//	distancearray[0] = NULL;
//				//}
//				//else if (smallest_distance == distancearray[1])
//				//{
//				//	closest_target = Target2;
//				//	distancearray[1] = NULL;
//				//}
//				//else if (smallest_distance == distancearray[2])
//				//{
//				//	closest_target = Target3;
//				//	distancearray[2] = NULL;
//				//}
//				//else if (smallest_distance == distancearray[3])
//				//{
//				//	closest_target = Target4;
//				//	distancearray[3] = NULL;
//				//}
//
//				//for (int i = 0; i <= 3; i++)
//				//{
//				//	second_smallest_distance = max(second_smallest_distance, distancearray[i]);
//				//}
//				//if (smallest_distance == distancearray[0])
//				//{
//				//	second_closest_target = Target1;
//				//	distancearray[0] = NULL;
//				//}
//				//else if (smallest_distance == distancearray[1])
//				//{
//				//	second_closest_target = Target2;
//				//	distancearray[1] = NULL;
//				//}
//				//else if (smallest_distance == distancearray[2])
//				//{
//				//	second_closest_target = Target3;
//				//	distancearray[2] = NULL;
//				//}
//				//else if (smallest_distance == distancearray[3])
//				//{
//				//	second_closest_target = Target4;
//				//	distancearray[3] = NULL;
//				//}
//
//				//Targetsarray[0] = Target1;
//				//Targetsarray[1] = Target2;
//				//Targetsarray[2] = Target3;
//				//Targetsarray[3] = Target4;
//
//				//int random = rand() % 4;
//
//				//if (WorldToScreen(Target2, temp))
//				//{
//				//	target_point_location = Target2;
//				//}
//				//else if (WorldToScreen(second_closest_target, temp))
//				//{
//				//	target_point_location = second_closest_target;
//				//}
//				//else if (WorldToScreen(closest_target, temp))
//				//{
//				//	target_point_location = closest_target;
//				//}
//				//else if (WorldToScreen(Target4, temp))
//				//{
//				//	target_point_location = Target4;
//				//}
//				//else if (WorldToScreen(Target3, temp))
//				//{
//				//	target_point_location = Target3;
//				//}
//				//else if (WorldToScreen(Targetsarray[random], temp))
//				//{
//				//	target_point_location = Targetsarray[random];
//				//}
//				//else if (WorldToScreen(Target1, temp))
//				//{
//				//	target_point_location = Target1;
//				//}
//				RtlZeroMemory(&target_point_location, sizeof(Vector3));
//				RtlZeroMemory(&val.basesbuffer, sizeof(val.basesbuffer));
//				while (target_point_location == Vector3{ 0.f, 0.f, 0.f })
//				{
//					for (int i = 0; i <= 7; i++)
//					{
//						currentbase = val.basesbuffer[i];
//						if (currentbase.side != val.LocalPlayerTeam &&
//							currentbase.health != 0.f)
//						{
//							Vector3 pos = ReadPM<Vector3>(currentbase.PositionPTR + 0xE0);
//							if (pos != Vector3{ 0.f, 0.f, 0.f })
//							{
//								target_point_location = pos;
//								currentbaseindex = i;
//								break;
//							}
//						}
//					}
//				}
//
//				write<Vector3>(BallisticComputer + 0x97C, target_point_location);
//				Vector3 fly_point_location = target_point_location;
//				Vector3 Bomb_predicted_impactpoint;
//				final_distance = GetDistance2D(Vector2{ val.LocalOwnedUnit.PlayerPosition.x, val.LocalOwnedUnit.PlayerPosition.z }, Vector2{ target_point_location.x,target_point_location.z });
//				Vector3 starting_position = val.LocalOwnedUnit.PlayerPosition;
//				if (relative_to_base == false)
//				{
//					fly_point_location.y = val.LocalOwnedUnit.PlayerPosition.y + height_offset;
//				}
//				else
//				{
//					fly_point_location.y = target_point_location.y + height_offset;
//				}
//				//fly_point_location.y += 500.f;
//				Vector3 target_pos_screen;
//				WorldToScreen(fly_point_location, target_pos_screen);
//				target_pos_screen.y = height / 2;
//				int x, y;
//				float smooth = 2.f;
//				SetForegroundWindow(Target.Window);
//				ClickKey(0x36, 7); //6
//				while (GetDistance(fly_point_location, val.LocalOwnedUnit.PlayerPosition) >= 500)
//				{
//					if (!WorldToScreen(fly_point_location, target_pos_screen))
//						break;
//					Bomb_predicted_impactpoint = ReadPM<Vector3>(BallisticComputer + 0x19AC);
//					if (GetDistance2D(Vector2{ Bomb_predicted_impactpoint.x, Bomb_predicted_impactpoint.z }, Vector2{ target_point_location.x,target_point_location.z }) < base_radius)
//					{
//						SetForegroundWindow(Target.Window);
//						HoldKey(VK_SPACE, 57); //SPACE
//					}
//					if (GetDistance2D(Vector2{ Bomb_predicted_impactpoint.x, Bomb_predicted_impactpoint.z }, Vector2{ target_point_location.x,target_point_location.z }) < distance_to_open_bombbay)
//					{
//						SetForegroundWindow(Target.Window);
//						HoldKey(0x4E, 49); //N
//					}
//					if (GetDistance2D(Vector2{ val.LocalOwnedUnit.PlayerPosition.x, val.LocalOwnedUnit.PlayerPosition.z }, Vector2{ target_point_location.x,target_point_location.z }) < distance_to_level_flight)
//					{
//						fly_point_location.y = val.LocalOwnedUnit.PlayerPosition.y;
//					}
//					if (dive)
//					{
//						//-6000.f - 1000.f
//						float currentdistance = GetDistance2D(Vector2{ val.LocalOwnedUnit.PlayerPosition.x, val.LocalOwnedUnit.PlayerPosition.z }, Vector2{ target_point_location.x,target_point_location.z });
//						float percentage = ((((currentdistance / final_distance) * 100.f) - 100.f) * -1.f) / 100.f;
//						float offset = (percentage * 7000.f) - 5000.f;
//						fly_point_location.y = target_point_location.y + offset;
//					}
//
//					HoldKey(VK_LSHIFT, 42); //LSHIFT
//					x = (target_pos_screen.x - (width / 2)) / smooth;
//					y = (target_pos_screen.y - (height / 2)) / smooth;
//					mouse_event(1U, x, y, NULL, NULL);
//					GUISTATE = val.LocalPlayer.GuiState;
//					if (GUISTATE != GuiState::ALIVE || !IsAlive(val.LocalOwnedUnit))
//						break;
//
//					Sleep(10);
//				}
//				//Sleep(20000);
//				while (timer < 20)
//				{
//					timer += 1;
//					GUISTATE = val.LocalPlayer.GuiState;
//					if (GUISTATE != GuiState::ALIVE || !IsAlive(val.LocalOwnedUnit))
//					{
//						break;
//					}
//					Sleep(1000);
//				}
//				timer = 0;
//				SetForegroundWindow(Target.Window);
//				ReleaseKey(0x4E, 49); //N
//				Sleep(300);
//				ReleaseKey(VK_SPACE, 57); //SPACE
//				Sleep(300);
//				ReleaseKey(VK_LSHIFT, 42); //LSHIFT
//				GUISTATE = val.LocalPlayer.GuiState;
//				if (GUISTATE == GuiState::ALIVE && IsAlive(val.LocalOwnedUnit))
//				{
//					while (timer < after_bombing_timer)
//					{
//						timer += 1;
//						GUISTATE = val.LocalPlayer.GuiState;
//						if (GUISTATE != GuiState::ALIVE || !IsAlive(val.LocalOwnedUnit))
//						{
//							break;
//						}
//						Sleep(1000);
//					}
//					timer = 0;
//				}
//				SetForegroundWindow(Target.Window);
//				HoldKey(0x4A, 36); //J
//				Sleep(5000);
//				SetForegroundWindow(Target.Window);
//				ReleaseKey(0x4A, 36); //J
//				while (GUISTATE == GuiState::ALIVE)
//				{
//					GUISTATE = val.LocalPlayer.GuiState;
//					Sleep(100);
//				}
//			}
//			else if (GUISTATE == GuiState::SPEC || GUISTATE == GuiState::DEAD)
//			{
//				Sleep(2000);
//				SetForegroundWindow(Target.Window);
//				ClickOnScreen(Vector2{ (float)width * 0.776f, (float)height * 0.945f }); //width*0.776f -> NO SQUADRON
//				Sleep(700);
//				ClickOnScreen(Vector2{ (float)width * 0.687f, (float)height * 0.968f }); //width*0.687f -> SQUADRON
//
//				while (GUISTATE == GuiState::SPEC || GUISTATE == GuiState::DEAD)
//				{
//					GUISTATE = val.LocalPlayer.GuiState;
//					if (GUISTATE != SPEC)
//						break;
//					Sleep(2000);
//					GUISTATE = val.LocalPlayer.GuiState;
//					if (GUISTATE != SPEC)
//						break;
//					ClickOnScreen(Vector2{ (float)width * 0.776f, (float)height * 0.945f }); //width*0.776f -> NO SQUADRON
//					Sleep(700);
//					ClickOnScreen(Vector2{ (float)width * 0.687f, (float)height * 0.968f }); //width*0.687f -> SQUADRON
//				}
//
//			}
//
//		}
//	}
//}






