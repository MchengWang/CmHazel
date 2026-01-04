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

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}