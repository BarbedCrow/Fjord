#pragma once

#include <Fjord.h>

#include "HierarchyPanel.h"
#include "InspectorPanel.h"
#include "ContentBrowser.h"

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
		bool LoadScene(bool fromFile = true);
		
		void ProcessInputs();
	private:
		Ref<Scene> m_scene;

		HierarchyPanel m_HierarchyPanel;
		InspectorPanel m_InspectorPanel;
		ContentBrowser m_ContentBrowser;

		//TEMP
		Ref<RenderSystemLegacy> m_renderSys;
		Ref<Framebuffer> m_frameBuffer;
	};
}