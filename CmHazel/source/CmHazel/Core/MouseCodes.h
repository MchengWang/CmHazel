#pragma once

namespace CmHazel
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define CM_MOUSE_BUTTON_0      ::CmHazel::Mouse::Button0
#define CM_MOUSE_BUTTON_1      ::CmHazel::Mouse::Button1
#define CM_MOUSE_BUTTON_2      ::CmHazel::Mouse::Button2
#define CM_MOUSE_BUTTON_3      ::CmHazel::Mouse::Button3
#define CM_MOUSE_BUTTON_4      ::CmHazel::Mouse::Button4
#define CM_MOUSE_BUTTON_5      ::CmHazel::Mouse::Button5
#define CM_MOUSE_BUTTON_6      ::CmHazel::Mouse::Button6
#define CM_MOUSE_BUTTON_7      ::CmHazel::Mouse::Button7
#define CM_MOUSE_BUTTON_LAST   ::CmHazel::Mouse::ButtonLast
#define CM_MOUSE_BUTTON_LEFT   ::CmHazel::Mouse::ButtonLeft
#define CM_MOUSE_BUTTON_RIGHT  ::CmHazel::Mouse::ButtonRight
#define CM_MOUSE_BUTTON_MIDDLE ::CmHazel::Mouse::ButtonMiddle