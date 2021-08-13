#pragma once

#include <Fjord.h>

namespace Fjord
{
	enum class ContentBrowserNodeType
	{
		DIRECTORY,
		FILE
	};

	struct ContentBrowserNode
	{
		std::string Name;
		std::string ID;
		ContentBrowserNodeType Type;
		std::vector<ContentBrowserNode> childs;

		ContentBrowserNode() = default;
		ContentBrowserNode(const std::string& name, const std::string& id, ContentBrowserNodeType type) : Name(name), ID(id), Type(type) {}

		bool operator== (ContentBrowserNode& rhs)
		{
			return ID == rhs.ID;
		}
	};

	class ContentBrowser
	{
	public:
		ContentBrowser();
		~ContentBrowser() = default;

		void SetScene(Ref<Scene> & scene) { m_Scene = scene; }

		void Update();
	private:
		void DisplayTree();
		void DisplayTreeNode(ContentBrowserNode& node);
		void DisplayTable();
	private:
		Ref<Scene> m_Scene;

		std::vector<ContentBrowserNode> m_Nodes;
		std::unordered_set<std::string> m_SelectedNodeIDs;
		ContentBrowserNode* m_LastSelectedDir = nullptr;

		std::unordered_map<ContentBrowserNodeType, Ref<Texture2D>> m_Icons;
	};
}

