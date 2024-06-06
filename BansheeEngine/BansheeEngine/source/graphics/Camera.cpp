#include "Camera.h"
#include "Foundation/Input/Input.h"

namespace Banshee
{
	Camera::Camera(float _fov, float _aspect, float _near, float _far) :
		m_Fov(_fov), m_Aspect(_aspect), m_Near(_near), m_Far(_far),
		m_Yaw(-90.0f), m_Pitch(0.0f)
	{
		m_Position = glm::vec3(0.0f, 0.0f, 2.0f);
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		UpdateViewMatrix();
		UpdateProjectionMatrix();

		Input::Instance().LockCursor();
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}

	void Camera::ProcessInput()
	{
		ProcessKeyboardInput();
		ProcessMouseInput();
	}

	void Camera::ProcessKeyboardInput()
	{
		constexpr float speed = 0.005f;

		if (Input::Instance().IsKeyPressed(BE_KEY_W))
		{
			m_Position += speed * m_Front;
		}
		if (Input::Instance().IsKeyPressed(BE_KEY_S))
		{
			m_Position -= speed * m_Front;
		}
		if (Input::Instance().IsKeyPressed(BE_KEY_A))
		{
			m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * speed;
		}
		if (Input::Instance().IsKeyPressed(BE_KEY_D))
		{
			m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * speed;
		}

		UpdateViewMatrix();
	}

	void Camera::MoveForward(float _delta)
	{
		m_Position += m_Front * _delta;
		UpdateViewMatrix();
	}

	void Camera::MoveBackward(float _delta)
	{
		m_Position -= m_Front * _delta;
		UpdateViewMatrix();
	}

	void Camera::MoveRight(float _delta)
	{
		m_Position += m_Right * _delta;
		UpdateViewMatrix();
	}

	void Camera::MoveLeft(float _delta)
	{
		m_Position -= m_Right * _delta;
		UpdateViewMatrix();
	}

	void Camera::ProcessMouseInput()
	{
		float xoffset = Input::Instance().GetMouseXChange();
		float yoffset = Input::Instance().GetMouseYChange();

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_Yaw += xoffset;
		m_Pitch -= yoffset;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		UpdateViewMatrix();
	}

	void Camera::UpdateViewMatrix()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::UpdateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
	}
} // End of Banshee namespace