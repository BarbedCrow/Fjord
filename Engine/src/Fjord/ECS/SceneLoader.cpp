#include "fjordpch.h"
#include "SceneLoader.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

#include "Fjord/ECS/Components/Components.h"

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}

namespace Fjord
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	static void SaveEntity(entt::entity& entt, YAML::Emitter& out, entt::registry* registry)
	{
		auto uid = registry->try_get<UIDComponent>(entt);
		if (!uid) return; // DON'T process entities without ID
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << uid->UID;

		auto tr = registry->try_get<TransformComponent>(entt);
		if (tr)
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap;
			out << YAML::Key << "Translation" << YAML::Value << tr->Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tr->Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tr->Scale;
			out << YAML::EndMap;
		}

		auto rc = registry->try_get<RenderComponent>(entt);
		if (rc)
		{
			out << YAML::Key << "RenderComponent";
			out << YAML::BeginMap;
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	bool SceneLoader::Load(const std::string& path)
	{
		YAML::Node data = YAML::LoadFile(path);
		if (!data["Scene"]) return false;

		auto entities = data["Entities"];
		if (entities)
		{
			auto registry = m_Scene->GetRegistry();
			for (auto entity : entities)
			{
				auto uid = entity["Entity"].as<std::string>();
				auto entt = registry->create();
				registry->emplace<UIDComponent>(entt, uid);

				auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					auto& tc = registry->emplace<TransformComponent>(entt);
					tc.Translation = transformComponent["Translation"].as<glm::vec3>();
					tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponent["Scale"].as<glm::vec3>();
				}

				auto renderComponent = entity["RenderComponent"];
				if (renderComponent)
				{
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

					registry->emplace<RenderComponent>(entt, vertexArray, shader);
				}
			}
		}

		return true;
	}

	bool SceneLoader::LoadRuntime(const std::string& path)
	{
		//NOT IMPLEMENTED
		FJORD_CORE_ASSERT(false);
		return false;
	}

	void SceneLoader::Save(const std::string& path)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value;

		out << YAML::BeginSeq;
		m_Scene->GetRegistry()->each([&](auto entt) 
		{
			SaveEntity(entt, out, m_Scene->GetRegistry());
		});
		out << YAML::EndSeq;

		out << YAML::EndMap;

		std::ofstream fout(path);
		fout << out.c_str();
	}

	void SceneLoader::SaveRuntime(const std::string& path)
	{
		//NOT IMPLEMENTED
		FJORD_CORE_ASSERT(false);
	}
	
}