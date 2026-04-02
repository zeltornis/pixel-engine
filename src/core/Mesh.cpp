#include "Mesh.hpp"

Mesh::Mesh(const std::vector<float> &vertices,
           const std::vector<unsigned int> &indices)
    : vbo(0), vao(0), ebo(0), indexCount(0), hasIndices(!indices.empty())
{
    // generating VBO and VAO handles (no memory allocation yet)
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    // binding objects (no data tranfer yet)
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    if (hasIndices)
    {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(unsigned int),
                     indices.data(), GL_STATIC_DRAW);
        indexCount = static_cast<GLsizei>(indices.size());
    }

    // Position attribute (location = 0)
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    // unbind vao
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    if (hasIndices)
        glDeleteBuffers(1, &ebo);
}

void Mesh::render() const
{
    glBindVertexArray(vao);
    if (hasIndices)
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, 3); // default to 3 vertices
    glBindVertexArray(0);
}
