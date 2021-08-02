#include <Fjord.h>
#include <Fjord/core/EntryPoint.h>

#include <imgui.h>

namespace Fjord
{
	class Editor : public Application
	{
	public:
		Editor()
		{
			FramebufferSpecification fbSpec;
			fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
			fbSpec.Width = 1280;
			fbSpec.Height = 720;
			m_Framebuffer = CreateRef<Framebuffer>(fbSpec);

			m_Systems.push_back(CreateRef<EditorCameraControllerSystem>(&m_Registry));
			m_RenderSystem  = CreateRef<RenderSystem>(&m_Registry);
			m_Systems.push_back(m_RenderSystem);

			m_RenderSystem->SetFramebuffer(m_Framebuffer);

			//ENTITIES

			//for future camera creation check that there is no active camera
			auto cameraEntt = m_Registry.create();
			m_Registry.emplace<TransformComponent>(cameraEntt);
			m_Registry.emplace<CameraComponent>(cameraEntt, GetWindow()->GetAspectRatio());

			float vertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			};

			auto vBuffer = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float2, "a_TexCoord"},
			};
			vBuffer->SetLayout(layout);

			uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
			auto iBuffer = CreateRef<IndexBuffer>(indices, 6);

			auto vertexArray = CreateRef<VertexArray>();
			vertexArray->AddVertexBuffer(vBuffer);
			vertexArray->SetIndexBuffer(iBuffer);

			auto shader = CreateRef <Shader>("assets/shaders/FlatColorShader.glsl");

			auto cubeEntt = m_Registry.create();
			m_Registry.emplace<TransformComponent>(cubeEntt);

			m_Registry.emplace<RenderComponent>(cubeEntt, vertexArray, shader);
		}

		~Editor()
		{

		}

		void UpdateInternal() override
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
					ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			//VIEWPORT/////////////////////////////////////////////
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
	private:
		Ref<RenderSystem> m_RenderSystem;

		Ref<Framebuffer> m_Framebuffer;
	};

	Application* CreateApplication()
	{
		return new Editor();
	}
}