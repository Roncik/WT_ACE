#ifndef DRAWING
#define DRAWING
#include "DirectX.h"

#pragma warning(disable : 4244)

#define ABS(x) ((x<0) ? (-x) : (x))

#define TORAD(x)  ((x)*0.01745329252)

struct VERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	DWORD color;
};
namespace Drawing
{
	void String(int x, int y, char * string, D3DCOLOR color);
	void Rect(int x, int y, int width, int height, D3DCOLOR color);
	void BorderedRect(int x, int y, int width, int height, int fa, int fr, int fg, int fb, D3DCOLOR color);
	void Line(int x, int y, int x1, int y2, D3DCOLOR color, float thickness);
	void FilledRect(int x, int y, int width, int height, D3DCOLOR color);
	void Circle(int x, int y, int radius, D3DCOLOR color);
	void CenteredFilledRect(int x, int y, int width, int height, D3DCOLOR color);
	void FilledCircle(int x, int y, int radius, D3DCOLOR color);
	void LineMultiple(D3DXVECTOR2* vertices, int vertexcount, D3DCOLOR color, float thickness);
	void drawchams(int vertexcount, VERTEX* vertices, int indexcount, WORD* indices);
}





#endif