#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>       & vertices,
         const std::vector<unsigned int>& indices = {});
    ~Mesh();

    void render() const;

private:
    GLuint vbo, vao, ebo;
    GLsizei indexCount;
    bool hasIndices;
};