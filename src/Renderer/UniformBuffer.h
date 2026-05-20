#pragma once
#include <GL/glew.h>

class UniformBuffer
{
private:
	unsigned int m_RendererID, slot;
public:
	UniformBuffer(unsigned int size, unsigned int slot);
	~UniformBuffer();

	void SetData(const void* data, unsigned int size, unsigned int offset = 0);

	void Bind() const {
		glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
	};
	void Unbind() const {
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	};
	const unsigned int GetID() const
	{
		return m_RendererID;
	}
};

