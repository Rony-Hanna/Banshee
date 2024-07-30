#pragma once

typedef struct VkPhysicalDevice_T* VkPhysicalDevice;
typedef struct VkDevice_T* VkDevice;
typedef struct VkSampler_T* VkSampler;

namespace Banshee
{
	class VulkanTextureSampler
	{
	public:
		VulkanTextureSampler(const VkDevice& _device, const VkPhysicalDevice& _gpu);
		~VulkanTextureSampler();

		VkSampler Get() const noexcept { return m_TextureSampler; }

	private:
		VkDevice m_LogicalDevice;
		VkPhysicalDevice m_PhysicalDevice;
		VkSampler m_TextureSampler;
	};
} // End of Banshee namespace