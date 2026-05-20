#include "Game.h"
#include "Assets.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer/Renderer.h"
#include "Renderer/Vertex.h"
#include "Core/Entity.h"

Game* Game::instance = nullptr;

void Game::Init() {
    Renderer::Get()
        .AddUBO(UBOslot::Camera, sizeof(glm::mat4));

    Assets::Init();

    camera
        .AddComponent(TransformComponent(0, 0, 3))
        .AddComponent(CameraComponent());

    triangle
        .AddComponent(TransformComponent(-0.5, 0.0, 0.0))
        .AddComponent(RenderableComponent(Assets::GetMesh("Triangle"), Assets::GetMaterial("Basic2D")));

    triangle2 = triangle;
    triangle2.GetComponent<TransformComponent>()->pos.z = 1;
    triangle2.GetComponent<TransformComponent>()->rot = { 0.2, 0.5, 0.7 };

    triangle.GetComponent<RenderableComponent>()->material.uniform<glm::vec4>("u_Color") = glm::vec4(1, 0, 1, 0.5);
}

void Game::OnUpdate(float deltaTime) {
    auto camTransform = camera.GetComponent<TransformComponent>();
    float speed = 5.0f * deltaTime;

    if (!ImGui::GetIO().WantCaptureKeyboard) {
        if (ImGui::IsKeyPressed(ImGuiKey_W)) camTransform->pos.z -= speed;
        if (ImGui::IsKeyPressed(ImGuiKey_S)) camTransform->pos.z += speed;
        if (ImGui::IsKeyPressed(ImGuiKey_A)) camTransform->pos.x -= speed;
        if (ImGui::IsKeyPressed(ImGuiKey_D)) camTransform->pos.x += speed;
    }
    if (ImGui::IsMouseDown(1) && !ImGui::GetIO().WantCaptureMouse) {
        ImVec2 delta = ImGui::GetIO().MouseDelta;

        float sensitivity = 0.005f;

        camTransform->rot.y -= delta.x * sensitivity;
        camTransform->rot.x -= delta.y * sensitivity;

        if (camTransform->rot.x > 1.5f)  camTransform->rot.x = 1.5f;
        if (camTransform->rot.x < -1.5f) camTransform->rot.x = -1.5f;
    }

    camera.GetComponent<CameraComponent>()->Submit();
    triangle2.GetComponent<RenderableComponent>()->Submit();
    triangle.GetComponent<RenderableComponent>()->Submit();

    auto tr = triangle.GetComponent<TransformComponent>();
    if (tr->pos.x >= 1.5)
        tr->pos.x = -1.5;
    tr->pos.x += 1 * deltaTime;
    tr->rot += glm::vec3(1) * deltaTime;

    Renderer::Get().Flush();
}

void Game::Close()
{
    Assets::Close();
}
