#include "MeshComponent.h"
#include "Foundation/ResourceManager/ResourceManager.h"

namespace Banshee
{
	MeshComponent::MeshComponent(const std::string& _modelPath, const ShaderType _shaderType) :
		m_MeshId(0),
		m_TexId(0),
		m_ShaderType(_shaderType),
		m_Meshes(),
		m_ModelName(ResourceManager::Instance().GetAssetName(_modelPath)),
		m_HasModel(true),
		m_HasTexture(false),
		m_Color(glm::vec3(1.0f))
	{}

	MeshComponent::MeshComponent(const PrimitiveShape _basicShape, const ShaderType _shaderType, const glm::vec3& _color) :
		m_MeshId(0),
		m_TexId(0),
		m_ShaderType(_shaderType),
		m_Meshes(),
		m_ModelName(""),
		m_HasModel(false),
		m_HasTexture(false),
		m_Color(_color)
	{
		SetMeshId(static_cast<uint32>(_basicShape));
	}

	void MeshComponent::SetTexture(const char* _pathToTexture) noexcept
	{
		m_TexId = ResourceManager::Instance().LoadImageResource(_pathToTexture);
		m_HasTexture = true;
	}

	const std::string MeshComponent::GetModelPath() const
	{
		const std::string modelsFolder = "Models/";
		return ResourceManager::Instance().GetEngineResDirPath() + modelsFolder + m_ModelName;
	}
} // End of Banshee namespace
