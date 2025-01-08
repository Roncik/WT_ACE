#ifndef DIRECTX
#define DIRECTX
#include "Main.h"
#include "Overlay.h"
#include "stdafx.h"
#include "Drawing.h"


struct directx_t
{
	IDirect3D9Ex * Object;
	IDirect3DDevice9Ex * Device;
	D3DPRESENT_PARAMETERS Param;
	ID3DXFont * Font;
	ID3DXFont * defaultFont;
	ID3DXFont* nearby_warningFont;
	ID3DXFont* missile_warningFont;
	ID3DXFont* LootFont;
	ID3DXFont* creditfont;
	ID3DXFont* MenuFontCenter;
	ID3DXFont * FontWarning;
	ID3DXFont * MissileFont;
	ID3DXLine * Line;
};

extern directx_t DirectX;

namespace DirectxFunctions
{
	void DirectXInit(HWND hwnd);
	void RenderDirectX();
}







#endif