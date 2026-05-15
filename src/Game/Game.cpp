#include "Game.h"
#include "Assets.h"

#include "Renderer/Renderer.h"
#include "Renderer/Vertex.h"
#include "Core/Entity.h"

Game* Game::instance = nullptr;

void Game::Init() {
    Assets::Init();

    triangle
        .AddComponent(TransformComponent(-0.5, 0.0, 0.0))
        .AddComponent(RenderableComponent(Assets::GetMesh("Triangle"), Assets::GetMaterial("Basic2D")));

    triangle2 = triangle;
    triangle2.GetComponent<TransformComponent>()->pos.z = 1;
    triangle2.GetComponent<TransformComponent>()->rot = { 0.2, 0.5, 0.7 };

    triangle.GetComponent<RenderableComponent>()->material.uniform<glm::vec4>("u_Color") = glm::vec4(1, 0, 1, 0.5);
}

void Game::OnUpdate(float deltaTime) {
    triangle2.GetComponent<RenderableComponent>()->Submit();
    triangle.GetComponent<RenderableComponent>()->Submit();

    auto tr = triangle.GetComponent<TransformComponent>();
    if (tr->pos.x >= 1.5)
        tr->pos.x = -1.5;
    tr->pos.x += 1*deltaTime;
    tr->rot += glm::vec3(1) * deltaTime;

    Renderer::Get().Flush();
}

void Game::Close()
{
    Assets::Close();
}
