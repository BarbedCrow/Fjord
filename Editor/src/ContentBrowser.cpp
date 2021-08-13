#include "ContentBrowser.h"

#include <imgui.h>
#include <filesystem>

#include <iostream>
#include <queue>

namespace fs = std::filesystem;

namespace Fjord
{
	/// HELPER FUNCTIONS
	
	static ContentBrowserNodeType GetNodeType(const fs::directory_entry& file)
	{
		if (file.is_directory())
		{
			return ContentBrowserNodeType::DIRECTORY;
		}

		auto ext = file.path().extension().string();
		//TO DO: switch by file extensions
		return ContentBrowserNodeType::FILE;
	}

	static void CollectNodes(std::vector<ContentBrowserNode>& nodes)
	{
		std::queue<ContentBrowserNode*> queue;
		for (auto& file : fs::recursive_directory_iterator("assets")) // TO DO: move strings and other constants to Engine's config file
		{
			auto path = file.path();
			auto parent = path.parent_path().filename();

			ContentBrowserNode node(path.filename().string(), path.string(), GetNodeType(file));

			ContentBrowserNode* currNode = queue.empty() ? nullptr : queue.front();
			while (currNode && currNode->Name != parent)
			{
				queue.pop();
				currNode = queue.empty() ? nullptr : queue.front();
			}

			if (!currNode)
			{
				nodes.push_back(node);
				queue.push(&nodes[nodes.size() - 1]);
				continue;
			}

			currNode->childs.push_back(node);
			if (file.is_directory()) queue.push(&currNode->childs[currNode->childs.size() - 1]);
		}
	}

	/// HELPER FUNCTIONS


	/// CONTENT BROWSER
	ContentBrowser::ContentBrowser()
	{
		m_Icons[ContentBrowserNodeType::DIRECTORY] = CreateRef<Texture2D>("resources\\icons\\DirIcon.png", 0);
		m_Icons[ContentBrowserNodeType::FILE] = CreateRef<Texture2D>("resources\\icons\\FileIcon.png", 0);
		//Currently Content browser doesn't support hot reload
		//It means, if you added some files from outside of the editor
		//you should reload whole engine
		//TO DO: support hot reload
		CollectNodes(m_Nodes);
	}

	void ContentBrowser::Update()
	{
		ImGui::Begin("Content Browser");
		DisplayTree();
		DisplayTable();
		ImGui::End();
	}

	void ContentBrowser::DisplayTree()
	{
		ImGui::Begin("Assets", nullptr, ImGuiWindowFlags_NoTitleBar);

		for (auto& node : m_Nodes)
		{
			DisplayTreeNode(node);
		}
		
		ImGui::End();
	}

	void ContentBrowser::DisplayTreeNode(ContentBrowserNode& node)
	{
		ImGuiTreeNodeFlags flags = node.childs.empty() ?
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen
			:
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

		bool open = m_SelectedNodeIDs.find(node.ID) != m_SelectedNodeIDs.end();
		ImGui::SetNextTreeNodeOpen(open);

		bool isOpen = ImGui::TreeNodeEx((void*)(&node), flags, node.Name.c_str()) && !node.childs.empty();

		if (ImGui::IsItemClicked())
		{
			m_SelectedNodeIDs.insert(node.ID);
			if (node.Type == ContentBrowserNodeType::DIRECTORY) m_LastSelectedDir = &node;
		}

		if (isOpen)
		{
			for (auto& childNode : node.childs)
			{
				DisplayTreeNode(childNode);
			}
			ImGui::TreePop();
		}
		else
		{
			m_SelectedNodeIDs.erase(node.ID);
		}
	}

	void ContentBrowser::DisplayTable()
	{
		if (m_Nodes.empty()) return;
		std::vector<ContentBrowserNode>& nodesToDisplay = m_LastSelectedDir ? m_LastSelectedDir->childs : m_Nodes;
		if (nodesToDisplay.empty()) return;
		
		ImGuiTableFlags tableFlags = ImGuiTableFlags_SizingFixedFit;
		static int columnCount = 7; // TO DO: change this value accordingly to available space

		ImGui::BeginTable("Content", columnCount, tableFlags);
		int rowCount = nodesToDisplay.size() / columnCount + 1;

		for (int row = 0; row < rowCount; row++)
		{
			ImGui::TableNextRow();
			for (int column = 0; column < columnCount; column++)
			{
				int idx = columnCount * row + column;
				if(idx >= nodesToDisplay.size()) break;
				ContentBrowserNode& nodeToDisplay = nodesToDisplay[idx];
				ImGui::TableSetColumnIndex(column);

				auto icon = m_Icons.find(nodeToDisplay.Type);
				if(icon != m_Icons.end()) ImGui::Image((void*)icon->second->GetRendererID(), ImVec2{ 128.f, 128.f });
				
				//Input handle. TO DO: move to separated function
				if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
				{
					switch (nodeToDisplay.Type)
					{
					case DIRECTORY:
						m_LastSelectedDir = &nodeToDisplay;
						break;
					case FILE:
						break;
					default:
						break;
					}
				}

				ImGui::Text(nodeToDisplay.Name.c_str(), row, column);
			}
		}

		ImGui::EndTable();
	}

}