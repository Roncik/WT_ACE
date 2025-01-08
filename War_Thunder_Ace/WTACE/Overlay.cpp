#include "stdafx.h"
#include "Overlay.h"
#include "DirectX.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "skStr.h"

HINSTANCE hInstance;
HANDLE pHandle;
DWORD pid;
DWORD Module;
inline POINTS position = { };
inline D3DPRESENT_PARAMETERS presentParameters = { };
overlay_t Overlay;
target_t Target;

void OverlayFunctions::CreateClass(WNDPROC winproc, char * windowname)
{
	sprintf(Overlay.Name, "%s", windowname);
	Overlay.Class.cbClsExtra = 0;
	Overlay.Class.cbSize = sizeof(WNDCLASSEX);
	Overlay.Class.cbWndExtra = 0;
	Overlay.Class.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	Overlay.Class.hCursor = LoadCursor(0, IDC_ARROW);
	Overlay.Class.hIcon = LoadIcon(0, IDI_APPLICATION);
	Overlay.Class.hIconSm = LoadIcon(0, IDI_APPLICATION);
	Overlay.Class.hInstance = hInstance;
	Overlay.Class.lpfnWndProc = winproc;
	Overlay.Class.lpszClassName = (LPCSTR)Overlay.Name;
	Overlay.Class.lpszMenuName = (LPCSTR)Overlay.Name;
	Overlay.Class.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&Overlay.Class))
		exit(1);
}

void OverlayFunctions::GetTargetWindow()
{
	Target.Window = FindWindow(skCrypt("DagorWClass"), 0);

	if (Target.Window != NULL)
	{  
		GetWindowThreadProcessId(Target.Window, &pid);
		HANDLE pHandle;
		Target.Checked = true;
		GetWindowRect(Target.Window, &Target.Size);
		Target.width = Target.Size.right - Target.Size.left;
		Target.height = Target.Size.bottom - Target.Size.top;
		Overlay.Width = Target.Size.right - Target.Size.left - 56;
		Overlay.Height = Target.Size.bottom - Target.Size.top - 68;
		Overlay.OverlayLeft = Target.Size.left + Overlay.OffsetLeft;
		Overlay.OverlayTop= Target.Size.top + Overlay.OffsetTop;
		Target.Style = GetWindowLong(Target.Window, GWL_STYLE);

		if (Target.Style & WS_BORDER)
		{
			Target.Size.top += 23;
			Overlay.Height -= 23;
		}

		HWND setover = FindWindow(skCrypt("PNIHiddenWnd"), NULL);
		SetWindowPos(Overlay.Window, setover, Overlay.OverlayLeft, Overlay.OverlayTop, Overlay.Width, Overlay.Height, SWP_SHOWWINDOW);
		//MoveWindow(Overlay.Window, Target.Size.left, Target.Size.top, Overlay.Width, Overlay.Height, true);
		Overlay.Margin = { 0, 0, Overlay.Width, Overlay.Height };

	}
	
}

void OverlayFunctions::CreateWindowOverlay()
{
	
	Overlay.Window = CreateWindowEx( WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW, (LPCSTR)Overlay.Name, (LPCSTR)Overlay.Name, WS_POPUP, 1, 1, Overlay.Width, Overlay.Height, 0, 0, hInstance, 0);	
	SetLayeredWindowAttributes(Overlay.Window, RGB(0, 0, 0), 255,  LWA_ALPHA);

	ShowWindow(Overlay.Window, SW_SHOWDEFAULT);
	DwmExtendFrameIntoClientArea(Overlay.Window, &Overlay.Margin);
	
}

void OverlayFunctions::UpdateOverlayState(bool MenuOpen, HWND ownd)
{
	//We call this function only when we open or close the menu
	long style = GetWindowLong(ownd, GWL_EXSTYLE);
	if (MenuOpen)
	{
		style &= ~WS_EX_LAYERED;
		SetWindowLong(ownd,
			GWL_EXSTYLE, style);
		EnableWindow(Target.Window, false);
		EnableWindow(Overlay.Window, true);
	}
	else
	{
		style |= WS_EX_LAYERED;
		SetWindowLong(ownd,
			GWL_EXSTYLE, style);
		EnableWindow(Target.Window, true);
		EnableWindow(Overlay.Window, false);
	}
	
}





