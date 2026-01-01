#pragma once

#include "CmHazel/Layer.h"

#include "CmHazel/Events/ApplicationEvent.h"
#include "CmHazel/Events/KeyEvent.h"
#include "CmHazel/Events/MouseEvent.h"

namespace CmHazel
{

	class CMHAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}