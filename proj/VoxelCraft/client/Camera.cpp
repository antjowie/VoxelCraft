#include "vcpch.hpp"
#include "Camera.hpp"

// This should not be included but we use it for projection matrix for the time being
#include "common/Chunk.hpp"

Camera::Camera(const Window& window)
    : m_window(window)
{
}

FreelookCamera::FreelookCamera(const Window& window)
    : Camera(window)
    , m_oldPos(window.GetMousePos())
{
}

void FreelookCamera::Update(float dt)
{
    if (!m_window.HasFocus())
        return;

    // Rotation
    glm::fvec3 forward(0, 0, -1);
    {
        const auto pos = m_window.GetMousePos();
        const sf::Vector2i center = static_cast<sf::Vector2i>(m_window.GetSize()) / 2;
        sf::Vector2f delta = static_cast<sf::Vector2f>(pos - m_oldPos) * m_sensitivity;
        delta.y = -delta.y;

        m_euler.x = glm::clamp(m_euler.x + delta.y, -89.5f, 89.5f);
        m_euler.y = m_euler.y + delta.x;

        forward.x = cos(glm::radians(m_euler.y)) * cos(glm::radians(m_euler.x));
        forward.y = sin(glm::radians(m_euler.x));
        forward.z = sin(glm::radians(m_euler.y)) * cos(glm::radians(m_euler.x));

        m_window.SetMousePos(center);
        m_oldPos = center;
    }

    // Movement
    {
        glm::fvec3 movement(0,0,0);
        glm::fvec3 right = glm::cross(forward, glm::fvec3(0, 1, 0));
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) movement.y += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) movement.y -= 1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement += forward;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement -= right;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement -= forward;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement += right;
        
        if (glm::length(movement) != 0) movement = glm::normalize(movement);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) movement *= 20.f;

        movement *= (m_speed * dt);
        m_eye = m_eye + movement;
        m_target = m_eye + forward;
    }
}

glm::mat4 Camera::GetProjection() const
{
    return glm::perspective<float>(glm::radians(45.f), (float)m_window.GetSize().x / (float)m_window.GetSize().y, 0.1f, chunkDimension.x * 32.f);
}

glm::mat4 Camera::GetView() const
{
    return glm::lookAt(m_eye, m_target,glm::fvec3(0,1,0));
}

glm::mat4 Camera::GetRotation() const
{
    const glm::vec3 dir = glm::normalize(m_target - m_eye);
    return glm::lookAt(glm::vec3(0), dir, glm::fvec3(0, 1, 0));
}
