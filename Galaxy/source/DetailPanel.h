#pragma once
#include "Log.h"
#include "imgui.h"
namespace Galaxy
{
	class DetailPanel
	{
	private:
		DetailPanel()
		{
			LOG_TRACE("[PANEL] Opening Detail Panel");
		}

		~DetailPanel()
		{
			LOG_TRACE("[PANEL] Closing detail panel");
		}

	public:
		static DetailPanel& Get()
		{
			static DetailPanel instance = DetailPanel();
			return instance;
		}

		void OnGuiRender(const ImGuiIO& io);

	};
}


