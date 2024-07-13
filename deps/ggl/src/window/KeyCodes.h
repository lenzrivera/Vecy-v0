#ifndef KEYCODES_H
#define KEYCODES_H

#include <Windows.h>
#include <Winuser.h>

namespace ggl
{
	typedef unsigned int InputCode;

	namespace
	{
		const InputCode FIRST_INPUT_CODE_INDEX = VK_LBUTTON - 1;
		const InputCode LAST_INPUT_CODE_INDEX  = VK_OEM_CLEAR;

		bool getInputHeldState(InputCode keyCode)
		{
			return GetAsyncKeyState(keyCode + 1) & 0x8000;
		}
	}

	enum Key : InputCode
	{
		// Miscellaneous Keys //

		ESCAPE = VK_ESCAPE - 1,
		
		// Space Keys //

		BACKSPACE = VK_BACK - 1,
		TAB       = VK_TAB - 1,
		ENTER     = VK_RETURN - 1,
		SPACE     = VK_SPACE - 1,
#undef DELETE
		DELETE    = VK_DELETE - 1,
#define DELETE 0x00010000L

		// Modifier Keys //

		SHIFT         = VK_SHIFT - 1,
        LEFT_SHIFT    = VK_LSHIFT - 1,
		RIGHT_SHIFT   = VK_RSHIFT - 1,
		CONTROL       = VK_CONTROL - 1,
		LEFT_CONTROL  = VK_LCONTROL - 1,
		RIGHT_CONTROL = VK_RCONTROL - 1,
		ALT           = VK_MENU - 1,
		LEFT_ALT      = VK_LMENU - 1,
		RIGHT_ALT     = VK_RMENU - 1,

		// Arrow Keys //

		LEFT_ARROW  = VK_LEFT - 1,
		UP_ARROW    = VK_UP - 1,
		RIGHT_ARROW = VK_RIGHT - 1,
		DOWN_ARROW  = VK_DOWN - 1,

		// Alphanumeric Keys //
		// Windows does not define any constants for these keys.
		
		ZERO  = 0x30 - 1,
		ONE   = 0x31 - 1,
		TWO   = 0x32 - 1,
		THREE = 0x33 - 1,
		FOUR  = 0x34 - 1,
		FIVE  = 0x35 - 1,
		SIX   = 0x36 - 1,
		SEVEN = 0x37 - 1,
		EIGHT = 0x38 - 1,
		NINE  = 0x39 - 1,

		A = 0X41 - 1,
		B = 0X42 - 1,
		C = 0X43 - 1,
		D = 0X44 - 1,
		E = 0X45 - 1,
		F = 0X46 - 1,
		G = 0X47 - 1,
		H = 0X48 - 1,
		I = 0X49 - 1,
		J = 0X4A - 1,
		K = 0X4B - 1,
		L = 0X4C - 1,
		M = 0X4D - 1,
		N = 0X4E - 1,
		O = 0X4F - 1,
		P = 0X50 - 1,
		Q = 0X51 - 1,
		R = 0X52 - 1,
		S = 0X53 - 1,
		T = 0X54 - 1,
		U = 0X55 - 1,
		V = 0X56 - 1,
		W = 0X57 - 1,
		X = 0X58 - 1,
		Y = 0X59 - 1,
		Z = 0X5A - 1
	};

	enum MouseButton : InputCode
	{
		LEFT   = VK_LBUTTON - 1,
		RIGHT  = VK_RBUTTON - 1,
		MIDDLE = VK_MBUTTON - 1,
	};

}

#endif