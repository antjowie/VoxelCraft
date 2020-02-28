#include "vcpch.hpp"



Renderer::Renderer(Config config)
    : m_shad("res/shaders/default.vs", "res/shaders/default.fs")
{
    // Create the main window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.majorVersion = 3;
    contextSettings.minorVersion = 3;

    m_window.create(sf::VideoMode(config.x, config.y), config.title.c_str(), sf::Style::Default, contextSettings);
    m_window.setActive();

    // Load OpenGL functions
    if (!gladLoadGL()) {
        throw "Glad couldn't be loaded!";
    }
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    // Configure OpenGL
    glViewport(0, 0, m_window.getSize().x, m_window.getSize().y);
    glClearColor(0.2f, 0.f, 0.2f, 1.f);
    glEnable(GL_DEPTH_TEST);

    // ---
    // Upload data to gpu
    unsigned vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    {
        unsigned vbo;
    }

    m_shad.Use();
    m_shad.SetMatrix("aMVP", glm::value_ptr(glm::mat4(1)));
}

void Renderer::SetMVP(const glm::mat4& mvp)
{
    m_shad.SetMatrix("aMVP", glm::value_ptr(mvp));
}

void Renderer::Render(const Renderable& renderable)
{
    m_renderables.push_back(&renderable);
}

void Renderer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    for (const auto& obj : m_renderables)
        obj->Render();
    m_renderables.clear();

    m_window.display();
}

sf::Vector2u Renderer::GetSize() const
{
    return m_window.getSize();
}

sf::Window& Renderer::GetWindow()
{
    return m_window;
}
