#pragma once

#include "CmHazel/Core/Layer.h"

#include "CmHazel/Events/ApplicationEvent.h"
#include "CmHazel/Events/KeyEvent.h"
#include "CmHazel/Events/MouseEvent.h"

namespace CmHazel
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;

	};

}