#include "Simulation.h"

Simulation::Simulation()
    :m_cameraController(16.0f / 9.0f, false)
{
    float positions[] = {
        -0.1f, -0.1f, 0.0f, 0.0f,
         0.1f, -0.1f, 1.0f, 0.0f,
         0.1f,  0.1f, 1.0f, 1.0f,
        -0.1f,  0.1f, 0.0f, 1.0f
    };

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    m_vao = VertexArray();
    m_vbo = VertexBuffer(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout = VertexBufferLayout();
    layout.Push<float>(2);
    layout.Push<float>(2);
    m_vao.AddBuffer(m_vbo, layout);

    m_ibo = IndexBuffer(indicies, 6);

    //m_projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    //m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


    p_shader = new Shader("src/res/shaders/myShader.shader");

    p_texture = new Texture("src/res/textures/circle.png");
    p_texture->Bind(0);
    p_shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    p_shader->SetUniform1i("u_Texture", 0);

    m_vao.Unbind();
    m_vbo.Unbind();
    m_ibo.Unbind();
    p_shader->Unbind();

    m_clearColor = ImVec4(19.0f / 255.0f, 18.0f / 255.0f, 18.0f / 255.0f, 1.0f);
    m_imageColor = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    std::random_device rd;
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (int i = 0; i < 60; i++) {
        m_circles.emplace_back(Circle(rd, dist));
    }
}

Simulation::~Simulation()
{
    p_shader->Delete();
    p_texture->Delete();

    m_vao.Delete();
    m_vbo.Delete();
    m_ibo.Delete();

    delete p_shader;
    delete p_texture;
}

void Simulation::OnEvent(Event& event)
{
    m_cameraController.OnEvent(event);
}

void Simulation::OnRender(Renderer& renderer)
{

    GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));
    renderer.Clear();
    for (const Circle& circle : m_circles) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), circle.m_Position);
        model = glm::scale(model, circle.GetScale());
        glm::mat4 mvp = m_cameraController.GetCamera().GetViewProjectionMatrix() * model;

        p_shader->Bind();
        p_shader->SetUniform4f("u_Color", circle.GetColor().x, circle.GetColor().y, circle.GetColor().z, 1.0f);
        p_shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(m_vao, m_ibo, *p_shader);
    }
}

