#include "Window.h"
#include "Foundation/Logging/Logger.h"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <assert.h>

namespace Banshee
{
	Window::Window(const uint16 _width, const uint16 _height, const char* _title) :
		m_Window(nullptr)
	{
		BE_LOG(LogCategory::Trace, "[WINDOW]: Creating window");

		if (!glfwInit())
		{
			throw std::runtime_error("ERROR: Failed to initialize glfw");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
		assert(m_Window != nullptr);
		BE_LOG(LogCategory::Info, "[WINDOW]: Created window");
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;

		glfwTerminate();
	}

	bool Window::ShouldWindowClose() const noexcept
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::Update() noexcept
	{
		glfwPollEvents();
	}

	uint16 Window::GetWidth() const noexcept
	{
		int w = 0;
		glfwGetFramebufferSize(m_Window, &w, nullptr);
		return static_cast<uint16>(w);
	}

	uint16 Window::GetHeight() const noexcept
	{
		int h = 0;
		glfwGetFramebufferSize(m_Window, nullptr, &h);
		return static_cast<uint16>(h);
	}
} // End of Banshee namespace