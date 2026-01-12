#pragma once

#include "CmHazel/Events/Event.h"
#include "CmHazel/Core/KeyCodes.h"

namespace CmHazel 
{

	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }
        //int GetNativeKeyCode() const { return GK_TO_IK(m_KeyCode); }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {
		}

		KeyCode m_KeyCode;

		//protected:
  //          int GK_TO_IK(int keycode) const
  //          {
  //              switch (keycode)
  //              {
  //              case 512:                      return CM_KEY_TAB;                  //512
  //              case 513:                      return CM_KEY_LEFT;
  //              case 514:                      return CM_KEY_RIGHT;
  //              case 515:                      return CM_KEY_UP;
  //              case 516:                      return CM_KEY_DOWN;
  //              case 517:                      return CM_KEY_PAGE_UP;
  //              case 518:                      return CM_KEY_PAGE_DOWN;
  //              case 519:                      return CM_KEY_HOME;
  //              case 520:                      return CM_KEY_END;
  //              case 521:                      return CM_KEY_INSERT;
  //              case 522:                      return CM_KEY_DELETE;
  //              case 523:                      return CM_KEY_BACKSPACE;
  //              case 524:                      return CM_KEY_SPACE;
  //              case 525:                      return CM_KEY_ENTER;
  //              case 526:                      return CM_KEY_ESCAPE;               // 526
  //              case 596:                      return CM_KEY_APOSTROPHE;         //596
  //              case 597:                      return CM_KEY_COMMA;
  //              case 598:                      return CM_KEY_MINUS;
  //              case 599:                      return CM_KEY_PERIOD;
  //              case 600:                      return CM_KEY_SLASH;
  //              case 601:                      return CM_KEY_SEMICOLON;
  //              case 602:                      return CM_KEY_EQUAL;
  //              case 603:                      return CM_KEY_LEFT_BRACKET;
  //              case 604:                      return CM_KEY_BACKSLASH;           //604
  //              case 631:                      return CM_KEY_WORLD_1;              //631
  //              case 632:                      return CM_KEY_WORLD_2;
  //              case 605:                      return CM_KEY_RIGHT_BRACKET;        //605
  //              case 606:                      return CM_KEY_GRAVE_ACCENT;
  //              case 607:                      return CM_KEY_CAPS_LOCK;
  //              case 608:                      return CM_KEY_SCROLL_LOCK;
  //              case 609:                      return CM_KEY_NUM_LOCK;
  //              case 610:                      return CM_KEY_PRINT_SCREEN;
  //              case 611:                      return CM_KEY_PAUSE;
  //              case 612:                      return CM_KEY_KP_0;
  //              case 613:                      return CM_KEY_KP_1;
  //              case 614:                      return CM_KEY_KP_2;
  //              case 615:                      return CM_KEY_KP_3;
  //              case 616:                      return CM_KEY_KP_4;
  //              case 617:                      return CM_KEY_KP_5;
  //              case 618:                      return CM_KEY_KP_6;
  //              case 619:                      return CM_KEY_KP_7;
  //              case 620:                      return CM_KEY_KP_8;
  //              case 621:                      return CM_KEY_KP_9;
  //              case 622:                      return CM_KEY_KP_DECIMAL;
  //              case 623:                      return CM_KEY_KP_DIVIDE;
  //              case 624:                      return CM_KEY_KP_MULTIPLY;
  //              case 625:                      return CM_KEY_KP_SUBTRACT;
  //              case 626:                      return CM_KEY_KP_ADD;
  //              case 627:                      return CM_KEY_KP_ENTER;
  //              case 628:                      return CM_KEY_KP_EQUAL;            //628
  //              case 528:                      return CM_KEY_LEFT_SHIFT;          //528
  //              case 527:                      return CM_KEY_LEFT_CONTROL;
  //              case 529:                      return CM_KEY_LEFT_ALT;            //529
  //              case 530:                      return CM_KEY_LEFT_SUPER;         //530
  //              case 532:                      return CM_KEY_RIGHT_SHIFT;          //532
  //              case 531:                      return CM_KEY_RIGHT_CONTROL;       //531
  //              case 533:                      return CM_KEY_RIGHT_ALT;            //533
  //              case 534:                      return CM_KEY_RIGHT_SUPER;
  //              case 535:                      return CM_KEY_MENU;
  //              case 536:                      return CM_KEY_0;
  //              case 537:                      return CM_KEY_1;
  //              case 538:                      return CM_KEY_2;
  //              case 539:                      return CM_KEY_3;
  //              case 540:                      return CM_KEY_4;
  //              case 541:                      return CM_KEY_5;
  //              case 542:                      return CM_KEY_6;
  //              case 543:                      return CM_KEY_7;
  //              case 544:                      return CM_KEY_8;
  //              case 545:                      return CM_KEY_9;
  //              case 546:                      return CM_KEY_A;
  //              case 547:                      return CM_KEY_B;
  //              case 548:                      return CM_KEY_C;
  //              case 549:                      return CM_KEY_D;
  //              case 550:                      return CM_KEY_E;
  //              case 551:                      return CM_KEY_F;
  //              case 552:                      return CM_KEY_G;
  //              case 553:                      return CM_KEY_H;
  //              case 554:                      return CM_KEY_I;
  //              case 555:                      return CM_KEY_J;
  //              case 556:                      return CM_KEY_K;
  //              case 557:                      return CM_KEY_L;
  //              case 558:                      return CM_KEY_M;
  //              case 559:                      return CM_KEY_N;
  //              case 560:                      return CM_KEY_O;
  //              case 561:                      return CM_KEY_P;
  //              case 562:                      return CM_KEY_Q;
  //              case 563:                      return CM_KEY_R;
  //              case 564:                      return CM_KEY_S;
  //              case 565:                      return CM_KEY_T;
  //              case 566:                      return CM_KEY_U;
  //              case 567:                      return CM_KEY_V;
  //              case 568:                      return CM_KEY_W;
  //              case 569:                      return CM_KEY_X;
  //              case 570:                      return CM_KEY_Y;
  //              case 571:                      return CM_KEY_Z;                   //571
  //              case 572:                      return CM_KEY_F1;
  //              case 573:                      return CM_KEY_F2;
  //              case 574:                      return CM_KEY_F3;
  //              case 575:                      return CM_KEY_F4;
  //              case 576:                      return CM_KEY_F5;
  //              case 577:                      return CM_KEY_F6;
  //              case 578:                      return CM_KEY_F7;
  //              case 579:                      return CM_KEY_F8;
  //              case 580:                      return CM_KEY_F9;
  //              case 581:                      return CM_KEY_F10;
  //              case 582:                      return CM_KEY_F11;
  //              case 583:                      return CM_KEY_F12;
  //              case 584:                      return CM_KEY_F13;
  //              case 585:                      return CM_KEY_F14;
  //              case 586:                      return CM_KEY_F15;
  //              case 587:                      return CM_KEY_F16;
  //              case 588:                      return CM_KEY_F17;
  //              case 589:                      return CM_KEY_F18;
  //              case 590:                      return CM_KEY_F19;
  //              case 591:                      return CM_KEY_F20;
  //              case 592:                      return CM_KEY_F21;
  //              case 593:                      return CM_KEY_F22;
  //              case 594:                      return CM_KEY_F23;
  //              case 595:                      return CM_KEY_F24;
  //              }
  //              return 0;
  //          }
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), m_IsRepeat(isRepeat) {
		}

		bool IsRepeat() const { return m_IsRepeat; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat   << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		bool m_IsRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode)
		{ }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}