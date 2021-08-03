#include "EditorApp.h"

#include <Fjord/core/EntryPoint.h>
#include <imgui.h>

namespace Fjord
{
	Application* CreateApplication()
	{
		return new Editor();
	}

	Editor::Editor()
	{
		m_Scene = CreateRef<Scene>();
		auto registry = m_Scene->GetRegistry();

		m_HierarchyPanel.SetScene(m_Scene);
		m_InspectorPanel.SetScene(m_Scene);

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = CreateRef<Framebuffer>(fbSpec);

		m_Systems.push_back(CreateRef<EditorCameraControllerSystem>(registry));
		m_RenderSystem = CreateRef<RenderSystem>(registry);
		m_Systems.push_back(m_RenderSystem);

		m_RenderSystem->SetFramebuffer(m_Framebuffer);

		//ENTITIES

		//for future camera creation check that there is no active camera
		auto cameraEntt = registry->create();
		registry->emplace<TransformComponent>(cameraEntt);
		registry->emplace<CameraComponent>(cameraEntt, GetWindow()->GetAspectRatio());
	}

	Editor::~Editor()
	{

	}

	void Editor::SaveScene(const std::string& path)
	{
		std::string filepath = path;
		if (filepath.empty()) filepath = FileDialogs::SaveFile("Fjord Scene (*.fscene)\0*.fscene\0");

		if (!filepath.empty())
		{
			SceneLoader(m_Scene).Save(filepath);
		}
	}

	bool Editor::LoadScene()
	{
		std::string filepath = FileDialogs::OpenFile("Fjord Scene (*.fscene)\0*.fscene\0");
		if (!filepath.empty())
		{
			SceneLoader(m_Scene).Load(filepath);
			return true;
		}
		return false;
	}

	void Editor::UpdateInternal()
	{
		static bool dockOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (!m_Scene->GetPath().empty())
				{
					if (ImGui::MenuItem("Save Scene", "Ctrl+S")) SaveScene(m_Scene->GetPath());
				}

				if (ImGui::MenuItem("Save Scene As", "Ctrl+Shift+S")) SaveScene();
				if (ImGui::MenuItem("Open Scene", "Ctrl+O")) LoadScene();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		//LAYOUT
		m_HierarchyPanel.Update();
		m_InspectorPanel.Update(m_HierarchyPanel.GetSelectedEntity());
		
		//DEMO TEST
		/*bool showDemo = true;
		ImGui::ShowDemoWindow(&showDemo);*/

		//VIEWPORT/////////////////////////////////////////////
		//TODO: move to separated unit 
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
			
		//Resize
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		if (m_Framebuffer->GetSpecification().Width != viewportSize.x || m_Framebuffer->GetSpecification().Height != viewportSize.y)
		{
			m_Framebuffer->Resize(viewportSize.x, viewportSize.y);
		}
		m_RenderSystem->HandleOnWindowResize(viewportSize.x, viewportSize.y);

		//Framebuffer to texture
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ viewportSize.x, viewportSize.y });

		ImGui::End();
		ImGui::PopStyleVar();
		/////////////////////////////////////////////////////

		ImGui::End();
	}
}