#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(unsigned int size, unsigned int slot) : slot(slot)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);

    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_UNIFORM_BUFFER, slot, m_RendererID);
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void UniformBuffer::SetData(const void* data, unsigned int size, unsigned int offset)
{
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}