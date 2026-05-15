#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

struct RenderCall
{
    Mesh* mesh;
    Material* material;
    glm::mat4 model;
};


class Renderer {
private:
    Renderer() {}
    ~Renderer() {}
private:
    unsigned int idMesh = 0, idTex = 0, idShader = 0;
public:
    std::vector<RenderCall> renderQueue;

    static Renderer& Get() {
        static Renderer instance;
        return instance;
    }
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    void Submit(RenderCall& call);
    void Flush();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(RenderCall call);
    void Clear() const;
};