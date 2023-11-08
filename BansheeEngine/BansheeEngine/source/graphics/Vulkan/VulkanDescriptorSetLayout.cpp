#include "VulkanDescriptorSetLayout.h"
#include "Foundation/Logging/Logger.h"
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <array>

namespace Banshee
{
	VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(const VkDevice& _logicalDevice, const uint32_t _shaderStage) :
		m_LogicalDevice(_logicalDevice),
		m_DescriptorSetLayout(VK_NULL_HANDLE)
	{
		BE_LOG(LogCategory::Trace, "[DESCRIPTOR SET LAYOUT]: Creating descriptor set layout");

		// View-projection binding
		std::array<VkDescriptorSetLayoutBinding, 3> layoutBindings{};
		layoutBindings[0].binding = 0;
		layoutBindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		layoutBindings[0].descriptorCount = 1;
		layoutBindings[0].stageFlags = _shaderStage;
		layoutBindings[0].pImmutableSamplers = nullptr;
		BE_LOG(LogCategory::Trace, "[DESCRIPTOR SET LAYOUT]: Added descriptor of type VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER at binding 0");

		// Color dynamic buffer
		layoutBindings[1].binding = 1;
		layoutBindings[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
		layoutBindings[1].descriptorCount = 1;
		layoutBindings[1].stageFlags = _shaderStage;
		layoutBindings[1].pImmutableSamplers = nullptr;
		BE_LOG(LogCategory::Trace, "[DESCRIPTOR SET LAYOUT]: Added descriptor of type VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC at binding 1");

		// Sampler
		layoutBindings[2].binding = 2;
		layoutBindings[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		layoutBindings[2].descriptorCount = 1;
		layoutBindings[2].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		layoutBindings[2].pImmutableSamplers = nullptr;
		BE_LOG(LogCategory::Trace, "[DESCRIPTOR SET LAYOUT]: Added descriptor of type VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER at binding 2");

		VkDescriptorSetLayoutCreateInfo layoutCreateInfo{};
		layoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutCreateInfo.bindingCount = static_cast<uint32_t>(layoutBindings.size());
		layoutCreateInfo.pBindings = layoutBindings.data();

		if (vkCreateDescriptorSetLayout(_logicalDevice, &layoutCreateInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS)
		{
			throw std::runtime_error("ERROR: Failed to create descriptor set layout");
		}

		BE_LOG(LogCategory::Info, "[DESCRIPTOR SET LAYOUT]: Created descriptor set layout");
	}

	VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
	{
		if (m_DescriptorSetLayout == VK_NULL_HANDLE)
			return;

		vkDestroyDescriptorSetLayout(m_LogicalDevice, m_DescriptorSetLayout, nullptr);
		m_DescriptorSetLayout = VK_NULL_HANDLE;
	}
}