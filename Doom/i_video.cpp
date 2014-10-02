using namespace System;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace OpenTK;
using namespace OpenTK::Input;
using namespace DoomSharp;

extern "C"
{
#include "i_video.h"
#include "v_video.h"
#include "d_event.h"
#include "d_main.h"
#include "m_argv.h"
}

#include <vcclr.h>

void I_StartTic2()
{
	MouseState mouse = Mouse::GetState();
	static bool firstmouse = true;
	static int mousex;
	static int mousey;
	if (firstmouse)
	{
		mousex = mouse.X;
		mousey = mouse.Y;
		firstmouse = false;
	}
	if (GameWindow::typeid->IsAssignableFrom(Core::Video->GetType()) && ((GameWindow^)Core::Video)->Focused)
	{
		event_t ev2;
		ev2.type = ev_mouse;
		ev2.data1 = (int)mouse.LeftButton | ((int)mouse.RightButton << 1);
		ev2.data2 = (mouse.X - mousex) * 8;
		ev2.data3 = (mouse.Y - mousey) * -8;
		D_PostEvent(&ev2);
	}
	mousex = mouse.X;
	mousey = mouse.Y;
}

extern "C" void I_StartTic()
{
	I_StartTic2();
}

extern "C" void I_FinishUpdate()
{
	Core::Video->SubmitFrame((IntPtr)screens[0]);
}

extern "C" void I_ForceRender()
{
	Core::Video->ForceRender();
}

extern "C" void I_ReadScreen(byte *scr)
{
	memcpy(scr,screens[0],SCREENWIDTH * SCREENHEIGHT);
}

extern "C" void I_SetPalette(byte *palette)
{
	Core::Video->SubmitPalette((IntPtr)palette);
}

int TranslateKey(Key key)
{
	switch (key)
	{
	case Key::Right:
		return KEY_RIGHTARROW;
	case Key::Left:
		return KEY_LEFTARROW;
	case Key::Up:
		return KEY_UPARROW;
	case Key::Down:
		return KEY_DOWNARROW;
	case Key::Escape:
		return KEY_ESCAPE;
	case Key::Enter:
		return KEY_ENTER;
	case Key::Tab:
		return KEY_TAB;
	case Key::F1:
		return KEY_F1;
	case Key::F2:
		return KEY_F2;
	case Key::F3:
		return KEY_F3;
	case Key::F4:
		return KEY_F4;
	case Key::F5:
		return KEY_F5;
	case Key::F6:
		return KEY_F6;
	case Key::F7:
		return KEY_F7;
	case Key::F8:
		return KEY_F8;
	case Key::F9:
		return KEY_F9;
	case Key::F10:
		return KEY_F10;
	case Key::F11:
		return KEY_F11;
	case Key::F12:
		return KEY_F12;
	case Key::BackSpace:
		return KEY_BACKSPACE;
	case Key::Pause:
		return KEY_PAUSE;
	case Key::Plus:
		return KEY_EQUALS;
	case Key::Minus:
		return KEY_MINUS;
	case Key::ShiftLeft:
	case Key::ShiftRight:
		return KEY_RSHIFT;
	case Key::ControlLeft:
	case Key::ControlRight:
		return KEY_RCTRL;
	case Key::AltLeft:
	case Key::AltRight:
		return KEY_RALT;
	case Key::Space:
		return ' ';
	case Key::Comma:
		return ',';
	case Key::Period:
		return '.';
	}
	if (key >= Key::A && key <= Key::Z)
	{
		return (int)(key - Key::A) + 'a';
	}
	if (key >= Key::Number0 && key <= Key::Number9)
	{
		return (int)(key - Key::Number0) + '0';
	}
	return 0;
}

extern "C" void I_InitGraphics()
{
	if (M_CheckParm("-novideo"))
		return;
	const char *video = "tk10";
	int p = M_CheckParm("-video");
	if (p && p + 1 < myargc)
		video = myargv[p + 1];
	Core::ChangeVideoSystem(gcnew String(video),M_CheckParm("-fullscreen"));
}
