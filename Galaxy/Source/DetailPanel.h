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
			
		}

		~DetailPanel()
		{
			
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


