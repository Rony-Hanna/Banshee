#pragma once

#include "Foundation/Platform.h"
#include <vector>

typedef struct VkPhysicalDevice_T* VkPhysicalDevice;
typedef struct VkDevice_T* VkDevice;
typedef struct VkBuffer_T* VkBuffer;
typedef struct VkCommandPool_T* VkCommandPool;
typedef struct VkQueue_T* VkQueue;
typedef struct VkImage_T* VkImage;
typedef struct VkImageView_T* VkImageView;
typedef struct VkDeviceMemory_T* VkDeviceMemory;
typedef enum VkFormat VkFormat;

namespace Banshee
{
	struct VulkanImage
	{
		VulkanImage(const VkImage& _image, const VkImageView _imageView, const VkDeviceMemory& _imageMemory) noexcept :
			m_Image{ _image },
			m_ImageView{ _imageView },
			m_ImageMemory{ _imageMemory }
		{}

		VkImage m_Image;
		VkImageView m_ImageView;
		VkDeviceMemory m_ImageMemory;
	};

	class VulkanTextureManager
	{
	public:
		VulkanTextureManager(const VkDevice& _device, const VkPhysicalDevice& _gpu, const VkQueue& _graphicsQueue, const VkCommandPool& _commandPool) noexcept;
		~VulkanTextureManager();

		const std::vector<VkImageView>& GetTextureImageViews() const noexcept;
		void UploadTextures();

		VulkanTextureManager(const VulkanTextureManager&) = delete;
		VulkanTextureManager& operator=(const VulkanTextureManager&) = delete;
		VulkanTextureManager(VulkanTextureManager&&) = delete;
		VulkanTextureManager& operator=(VulkanTextureManager&&) = delete;

	private:
		void CreateStagingBuffer(const uint64 _sizeOfBuffer, const unsigned char* _pixels, const uint32 _imgW, const uint32 _imgH);
		void CreateTextureImage(const VkBuffer& _buffer, const uint32 _imgW, const uint32 _imgH);

	private:
		VkDevice m_LogicalDevice;
		VkPhysicalDevice m_PhysicalDevice;
		VkQueue m_GraphicsQueue;
		VkCommandPool m_CommandPool;
		VkFormat m_TextureImageFormat;
		std::vector<VulkanImage> m_TextureImages;
		std::vector<VkImageView> m_TextureImageViews;
	};
} // End of Banshee namespace