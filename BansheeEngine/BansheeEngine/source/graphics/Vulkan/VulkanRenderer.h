#pragma once

#include "VulkanVertexBufferManager.h"
#include <memory>
#include "../MVP.h"

namespace Banshee
{
	class Window;
	class VulkanInstance;
	class VulkanSurface;
	class VulkanDevice;
	class VulkanSwapchain;
	class VulkanDepthBuffer;
	class VulkanRenderPass;
	class VulkanDescriptorSetLayout;
	class VulkanDescriptorPool;
	class VulkanDescriptorSet;
	class VulkanGraphicsPipeline;
	class VulkanCommandPool;
	class VulkanCommandBuffer;
	class VulkanFramebuffer;
	class VulkanSemaphore;
	class VulkanFence;
	class VulkanVertexBufferManager;
	class VulkanUniformBuffer;
	class VulkanTexture;
	class VulkanTextureSampler;

	class VulkanRenderer
	{
	public:
		VulkanRenderer(const Window* _window);
		~VulkanRenderer();

		void DrawFrame();

	private:
		void AllocateDynamicBufferSpace();
		void UpdateDescriptorSet(const uint8 _descriptorSetIndex);
		void RecordRenderCommands(const uint8 _imgIndex);

	private:
		std::unique_ptr<VulkanInstance> m_VkInstance;
		std::unique_ptr<VulkanSurface> m_VkSurface;
		std::unique_ptr<VulkanDevice> m_VkDevice;
		std::unique_ptr<VulkanSwapchain> m_VkSwapchain;
		std::unique_ptr<VulkanDepthBuffer> m_DepthBuffer;
		std::unique_ptr<VulkanRenderPass> m_VkRenderPass;
		std::unique_ptr<VulkanDescriptorSetLayout> m_VkDescriptorSetLayout;
		std::unique_ptr<VulkanDescriptorPool> m_VkDescriptorPool;
		std::unique_ptr<VulkanGraphicsPipeline> m_VkGraphicsPipeline;
		std::unique_ptr<VulkanCommandPool> m_VkCommandPool;
		std::unique_ptr<VulkanCommandBuffer> m_VkCommandBuffers;
		std::unique_ptr<VulkanFramebuffer> m_VkFramebuffers;
		std::unique_ptr<VulkanSemaphore> m_VkSemaphores;
		std::unique_ptr<VulkanFence> m_VkInFlightFences;
		std::unique_ptr<VulkanVertexBufferManager> m_VertexBufferManager;
		std::unique_ptr<VulkanTexture> m_VkTexture;
		std::unique_ptr<VulkanTexture> m_VkTexture2;
		std::unique_ptr<VulkanTextureSampler> m_VkTextureSampler;
		std::vector<std::unique_ptr<VulkanUniformBuffer>> m_VPUniformBuffers;
		std::vector<std::unique_ptr<VulkanUniformBuffer>> m_DynamicUniformBuffers;
		std::vector<std::unique_ptr<VulkanDescriptorSet>> m_DescriptorSets;
		ViewProjMatrix m_ViewProjMatrix;
		uint8 m_CurrentFrameIndex;
		size_t m_DynamicBufferMemoryAlignment;
		glm::vec3* m_DynamicBufferMemorySpace;
	};
} // End of Banshee namespace