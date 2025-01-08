#include "stdafx.h"
#include "Drawing.h"


#define M_PI 3.141f

void Drawing::String(int x, int y, char * string, D3DCOLOR color)
{
	RECT Position;
	Position.left = x + 1;
	Position.top = y + 1;
	DirectX.Font->DrawTextA(0, string, strlen(string), &Position, DT_NOCLIP, color);
	Position.left = x;
	Position.top = y;
	DirectX.Font->DrawTextA(0, string, strlen(string), &Position, DT_NOCLIP, color);
}

void Drawing::Rect(int x, int y, int width, int height, D3DCOLOR color)
{
	D3DXVECTOR2 Rect[5];
	Rect[0] = D3DXVECTOR2(x, y);
	Rect[1] = D3DXVECTOR2(x + width, y);
	Rect[2] = D3DXVECTOR2(x + width, y + height);
	Rect[3] = D3DXVECTOR2(x, y + height);
	Rect[4] = D3DXVECTOR2(x, y);
	DirectX.Line->SetWidth(1);
	DirectX.Line->Draw(Rect, 5, color);
}

void Drawing::BorderedRect(int x, int y, int width, int height, int fa, int fr, int fg, int fb, D3DCOLOR color)
{
	D3DXVECTOR2 Fill[2];
	Fill[0] = D3DXVECTOR2(x + width / 2, y);
	Fill[1] = D3DXVECTOR2(x + width / 2, y + height);
	DirectX.Line->SetWidth(width);
	DirectX.Line->Draw(Fill, 2, D3DCOLOR_ARGB(fa, fr, fg, fb));

	D3DXVECTOR2 Rect[5];
	Rect[0] = D3DXVECTOR2(x, y);
	Rect[1] = D3DXVECTOR2(x + width, y);
	Rect[2] = D3DXVECTOR2(x + width, y + height);
	Rect[3] = D3DXVECTOR2(x, y + height);
	Rect[4] = D3DXVECTOR2(x, y);
	DirectX.Line->SetWidth(1);
	DirectX.Line->Draw(Rect, 5, color);
}

void Drawing::Line(int x, int y, int x1, int y2, D3DCOLOR color, float thickness)
{
	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x, y);
	Line[1] = D3DXVECTOR2(x1, y2);
	DirectX.Line->SetWidth(thickness);
	DirectX.Line->Draw(Line, 2, color);
}

void Drawing::LineMultiple(D3DXVECTOR2* vertices,int vertexcount, D3DCOLOR color, float thickness)
{
	DirectX.Line->SetWidth(thickness);
	DirectX.Line->Draw(vertices, vertexcount, color);
}

void Drawing::FilledRect(int x, int y, int width, int height, D3DCOLOR color)
{
	D3DXVECTOR2 Rect[2];
	Rect[0] = D3DXVECTOR2(x + width / 2, y);
	Rect[1] = D3DXVECTOR2(x + width / 2, y + height);
	DirectX.Line->SetWidth(width);
	DirectX.Line->Draw(Rect, 2, color);
}


void Drawing::CenteredFilledRect(int x, int y, int width, int height, D3DCOLOR color)
{
	D3DXVECTOR2 Rect[2];
	Rect[0] = D3DXVECTOR2(x, y - height/2);
	Rect[1] = D3DXVECTOR2(x, y + height/2);
	DirectX.Line->SetWidth(width);
	DirectX.Line->Draw(Rect, 2, color);
}

void Drawing::Circle(int x, int y, int radius, D3DCOLOR color)
{
	DirectX.Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	DirectX.Device->SetTexture(0, NULL);
	
	D3DXVECTOR2 DotPoints[128];
	D3DXVECTOR2 Line[128];
	int Points = 0;
	for (float i = 0; i < M_PI * 2.0f; i += 0.1f)
	{
		float PointOriginX = x + radius * cos(i);
		float PointOriginY = y + radius * sin(i);
		float PointOriginX2 = radius * cos(i + 0.1) + x;
		float PointOriginY2 = radius * sin(i + 0.1) + y;
		DotPoints[Points] = D3DXVECTOR2(PointOriginX, PointOriginY);
		DotPoints[Points + 1] = D3DXVECTOR2(PointOriginX2, PointOriginY2);
		Points += 2;
	}
	DirectX.Line->Draw(DotPoints, Points, color);
}

struct D3DTLVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	D3DCOLOR Color;
	float fU;
	float fV;
};

D3DTLVERTEX CreateD3DTLVERTEX(float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v =
	{
		X,
		Y,
		Z,
		RHW,
		color,
		U,
		V
	};

	return v;
}

void Drawing::FilledCircle(int x, int y, int radius, D3DCOLOR color)
{
	D3DTLVERTEX Vtex[400];

	float x1 = x;
	float y1 = y;

	for (int i = 0; i <= 363; i += 3)
	{
		float angle = (i / 57.3f);
		float x2 = x + (radius * sin(angle));
		float y2 = y + (radius * cos(angle));
		Vtex[i] = CreateD3DTLVERTEX(x, y, 0, 1, color, 0, 0);
		Vtex[i + 1] = CreateD3DTLVERTEX(x1, y1, 0, 1, color, 0, 0);
		Vtex[i + 2] = CreateD3DTLVERTEX(x2, y2, 0, 1, color, 0, 0);

		y1 = y2;
		x1 = x2;
	}

	DirectX.Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	DirectX.Device->SetTexture(0, NULL);
	DirectX.Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 363, Vtex, sizeof(D3DTLVERTEX));
}

void Drawing::drawchams(int vertexcount, VERTEX* vertices, int indexcount, WORD* indices)
{
	int triangle_count = indexcount / 3;

	DirectX.Device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, vertexcount, triangle_count, indices, D3DFMT_INDEX16, vertices, sizeof(VERTEX));
}

