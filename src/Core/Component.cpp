#include "Component.h"
#include "Entity.h"

void RenderableComponent::Submit()
{
    if (TransformComponent* tc = parent->GetComponent<TransformComponent>()) {
        RenderCall call = { mesh, &material, tc->GetModelMatrix() };
        Renderer::Get().Submit(call);
    }
}

std::unique_ptr<Component> RenderableComponent::Clone() const
{
	return std::make_unique<RenderableComponent>(*this);
}

glm::mat4 TransformComponent::GetModelMatrix() const
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
    transform = glm::rotate(transform, rot.x, { 1, 0, 0 });
    transform = glm::rotate(transform, rot.y, { 0, 1, 0 });
    transform = glm::rotate(transform, rot.z, { 0, 0, 1 });
    transform = glm::scale(transform, scale);
    return transform;
}

std::unique_ptr<Component> TransformComponent::Clone() const
{
	return std::make_unique<TransformComponent>(*this);
}

void CameraComponent::Submit() {
    glm::mat4 view, proj, VP;
    proj = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
    if (TransformComponent* tc = parent->GetComponent<TransformComponent>())
        view = glm::inverse(tc->GetModelMatrix());
    else
        view = glm::mat4(1.0f);
    VP = proj * view;
    Renderer::Get().SetUBO(UBOslot::Camera, VP);
}

std::unique_ptr<Component> CameraComponent::Clone() const
{
    return std::make_unique<CameraComponent>(*this);
}