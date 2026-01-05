#pragma once

namespace CmHazel
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define CM_KEY_SPACE           ::CmHazel::Key::Space
#define CM_KEY_APOSTROPHE      ::CmHazel::Key::Apostrophe    /* ' */
#define CM_KEY_COMMA           ::CmHazel::Key::Comma         /* , */
#define CM_KEY_MINUS           ::CmHazel::Key::Minus         /* - */
#define CM_KEY_PERIOD          ::CmHazel::Key::Period        /* . */
#define CM_KEY_SLASH           ::CmHazel::Key::Slash         /* / */
#define CM_KEY_0               ::CmHazel::Key::D0
#define CM_KEY_1               ::CmHazel::Key::D1
#define CM_KEY_2               ::CmHazel::Key::D2
#define CM_KEY_3               ::CmHazel::Key::D3
#define CM_KEY_4               ::CmHazel::Key::D4
#define CM_KEY_5               ::CmHazel::Key::D5
#define CM_KEY_6               ::CmHazel::Key::D6
#define CM_KEY_7               ::CmHazel::Key::D7
#define CM_KEY_8               ::CmHazel::Key::D8
#define CM_KEY_9               ::CmHazel::Key::D9
#define CM_KEY_SEMICOLON       ::CmHazel::Key::Semicolon     /* ; */
#define CM_KEY_EQUAL           ::CmHazel::Key::Equal         /* = */
#define CM_KEY_A               ::CmHazel::Key::A
#define CM_KEY_B               ::CmHazel::Key::B
#define CM_KEY_C               ::CmHazel::Key::C
#define CM_KEY_D               ::CmHazel::Key::D
#define CM_KEY_E               ::CmHazel::Key::E
#define CM_KEY_F               ::CmHazel::Key::F
#define CM_KEY_G               ::CmHazel::Key::G
#define CM_KEY_H               ::CmHazel::Key::H
#define CM_KEY_I               ::CmHazel::Key::I
#define CM_KEY_J               ::CmHazel::Key::J
#define CM_KEY_K               ::CmHazel::Key::K
#define CM_KEY_L               ::CmHazel::Key::L
#define CM_KEY_M               ::CmHazel::Key::M
#define CM_KEY_N               ::CmHazel::Key::N
#define CM_KEY_O               ::CmHazel::Key::O
#define CM_KEY_P               ::CmHazel::Key::P
#define CM_KEY_Q               ::CmHazel::Key::Q
#define CM_KEY_R               ::CmHazel::Key::R
#define CM_KEY_S               ::CmHazel::Key::S
#define CM_KEY_T               ::CmHazel::Key::T
#define CM_KEY_U               ::CmHazel::Key::U
#define CM_KEY_V               ::CmHazel::Key::V
#define CM_KEY_W               ::CmHazel::Key::W
#define CM_KEY_X               ::CmHazel::Key::X
#define CM_KEY_Y               ::CmHazel::Key::Y
#define CM_KEY_Z               ::CmHazel::Key::Z
#define CM_KEY_LEFT_BRACKET    ::CmHazel::Key::LeftBracket   /* [ */
#define CM_KEY_BACKSLASH       ::CmHazel::Key::Backslash     /* \ */
#define CM_KEY_RIGHT_BRACKET   ::CmHazel::Key::RightBracket  /* ] */
#define CM_KEY_GRAVE_ACCENT    ::CmHazel::Key::GraveAccent   /* ` */
#define CM_KEY_WORLD_1         ::CmHazel::Key::World1        /* non-US #1 */
#define CM_KEY_WORLD_2         ::CmHazel::Key::World2        /* non-US #2 */

/* Function keys */
#define CM_KEY_ESCAPE          ::CmHazel::Key::Escape
#define CM_KEY_ENTER           ::CmHazel::Key::Enter
#define CM_KEY_TAB             ::CmHazel::Key::Tab
#define CM_KEY_BACKSPACE       ::CmHazel::Key::Backspace
#define CM_KEY_INSERT          ::CmHazel::Key::Insert
#define CM_KEY_DELETE          ::CmHazel::Key::Delete
#define CM_KEY_RIGHT           ::CmHazel::Key::Right
#define CM_KEY_LEFT            ::CmHazel::Key::Left
#define CM_KEY_DOWN            ::CmHazel::Key::Down
#define CM_KEY_UP              ::CmHazel::Key::Up
#define CM_KEY_PAGE_UP         ::CmHazel::Key::PageUp
#define CM_KEY_PAGE_DOWN       ::CmHazel::Key::PageDown
#define CM_KEY_HOME            ::CmHazel::Key::Home
#define CM_KEY_END             ::CmHazel::Key::End
#define CM_KEY_CAPS_LOCK       ::CmHazel::Key::CapsLock
#define CM_KEY_SCROLL_LOCK     ::CmHazel::Key::ScrollLock
#define CM_KEY_NUM_LOCK        ::CmHazel::Key::NumLock
#define CM_KEY_PRINT_SCREEN    ::CmHazel::Key::PrintScreen
#define CM_KEY_PAUSE           ::CmHazel::Key::Pause
#define CM_KEY_F1              ::CmHazel::Key::F1
#define CM_KEY_F2              ::CmHazel::Key::F2
#define CM_KEY_F3              ::CmHazel::Key::F3
#define CM_KEY_F4              ::CmHazel::Key::F4
#define CM_KEY_F5              ::CmHazel::Key::F5
#define CM_KEY_F6              ::CmHazel::Key::F6
#define CM_KEY_F7              ::CmHazel::Key::F7
#define CM_KEY_F8              ::CmHazel::Key::F8
#define CM_KEY_F9              ::CmHazel::Key::F9
#define CM_KEY_F10             ::CmHazel::Key::F10
#define CM_KEY_F11             ::CmHazel::Key::F11
#define CM_KEY_F12             ::CmHazel::Key::F12
#define CM_KEY_F13             ::CmHazel::Key::F13
#define CM_KEY_F14             ::CmHazel::Key::F14
#define CM_KEY_F15             ::CmHazel::Key::F15
#define CM_KEY_F16             ::CmHazel::Key::F16
#define CM_KEY_F17             ::CmHazel::Key::F17
#define CM_KEY_F18             ::CmHazel::Key::F18
#define CM_KEY_F19             ::CmHazel::Key::F19
#define CM_KEY_F20             ::CmHazel::Key::F20
#define CM_KEY_F21             ::CmHazel::Key::F21
#define CM_KEY_F22             ::CmHazel::Key::F22
#define CM_KEY_F23             ::CmHazel::Key::F23
#define CM_KEY_F24             ::CmHazel::Key::F24
#define CM_KEY_F25             ::CmHazel::Key::F25

/* Keypad */
#define CM_KEY_KP_0            ::CmHazel::Key::KP0
#define CM_KEY_KP_1            ::CmHazel::Key::KP1
#define CM_KEY_KP_2            ::CmHazel::Key::KP2
#define CM_KEY_KP_3            ::CmHazel::Key::KP3
#define CM_KEY_KP_4            ::CmHazel::Key::KP4
#define CM_KEY_KP_5            ::CmHazel::Key::KP5
#define CM_KEY_KP_6            ::CmHazel::Key::KP6
#define CM_KEY_KP_7            ::CmHazel::Key::KP7
#define CM_KEY_KP_8            ::CmHazel::Key::KP8
#define CM_KEY_KP_9            ::CmHazel::Key::KP9
#define CM_KEY_KP_DECIMAL      ::CmHazel::Key::KPDecimal
#define CM_KEY_KP_DIVIDE       ::CmHazel::Key::KPDivide
#define CM_KEY_KP_MULTIPLY     ::CmHazel::Key::KPMultiply
#define CM_KEY_KP_SUBTRACT     ::CmHazel::Key::KPSubtract
#define CM_KEY_KP_ADD          ::CmHazel::Key::KPAdd
#define CM_KEY_KP_ENTER        ::CmHazel::Key::KPEnter
#define CM_KEY_KP_EQUAL        ::CmHazel::Key::KPEqual

#define CM_KEY_LEFT_SHIFT      ::CmHazel::Key::LeftShift
#define CM_KEY_LEFT_CONTROL    ::CmHazel::Key::LeftControl
#define CM_KEY_LEFT_ALT        ::CmHazel::Key::LeftAlt
#define CM_KEY_LEFT_SUPER      ::CmHazel::Key::LeftSuper
#define CM_KEY_RIGHT_SHIFT     ::CmHazel::Key::RightShift
#define CM_KEY_RIGHT_CONTROL   ::CmHazel::Key::RightControl
#define CM_KEY_RIGHT_ALT       ::CmHazel::Key::RightAlt
#define CM_KEY_RIGHT_SUPER     ::CmHazel::Key::RightSuper
#define CM_KEY_MENU            ::CmHazel::Key::Menu