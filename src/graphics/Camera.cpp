#include "vcpch.hpp"

Camera::Camera(sf::Window& window)
    : m_window(window)
{
}

FreelookCamera::FreelookCamera(sf::Window& window)
    : Camera(window)
    , m_oldPos(sf::Mouse::getPosition(window))
{
}

void FreelookCamera::Update(float dt)
{
    if (!m_window.hasFocus())
        return;

    // Rotation
    glm::fvec3 forward(0, 0, -1);
    {
        const auto pos = sf::Mouse::getPosition(m_window);
        auto delta = pos - m_oldPos;

        m_euler.x += (float)delta.y * m_sensitivity;
        m_euler.y += (float)delta.x * m_sensitivity;

        //forward.x = cos(glm::radians(m_euler.y)) * cos(glm::radians(m_euler.x));
        //forward.y = sin(glm::radians(m_euler.x));
        //forward.z = sin(glm::radians(m_euler.y)) * cos(glm::radians(m_euler.x));
        m_oldPos = pos;
    }

    // Movement
    {
        std::printf("%.2f %.2f %.2f\n", m_eye.x, m_eye.y, m_eye.z);

        glm::fvec3 movement(0,0,0);
        glm::fvec3 right = glm::cross(forward, glm::fvec3(0, 1, 0));
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) movement.y += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) movement.y -= 1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement += forward;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement -= right;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement -= forward;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement += right;

        movement *= (m_speed * dt);
        m_eye = m_eye + movement;
        m_target = m_eye + forward;
    }
}

glm::mat4 Camera::GetProjection() const
{
    return glm::perspective<float>(glm::radians(45.f), (float)m_window.getSize().x / (float)m_window.getSize().y, 0.1f, 100.f);
}

glm::mat4 Camera::GetView() const
{
    return glm::lookAt(m_eye, m_target,glm::fvec3(0,1,0));
}
