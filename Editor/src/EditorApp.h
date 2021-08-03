#pragma once

#include <Fjord.h>

#include "HierarchyPanel.h"

namespace Fjord
{
	class Editor : public Application
	{
	public:
		Editor();
		~Editor();
	protected:
		virtual void UpdateInternal() override;
	private:
		void SaveScene(const std::string& path = "");
		bool LoadScene();
	private:
		Ref<Scene> m_Scene;

		HierarchyPanel m_HierarchyPanel;

		//TEMP
		Ref<RenderSystem> m_RenderSystem;
		Ref<Framebuffer> m_Framebuffer;
	};
}