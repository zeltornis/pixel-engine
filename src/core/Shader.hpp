#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& vertPath, const std::string& fragPath);
    ~Shader();

    void use() const;
    GLuint getID() const { return id; }

    // Method to set uniforms
    template<typename T>
    void setUniform(const std::string& name, const T& value) const;

private:
    GLuint id;
    std::string loadSource(const std::string& path);
    GLuint compileShader(const std::string& source, GLenum type);
};

// setUniform overload definitions:

template <>
inline void Shader::setUniform<int>(const std::string &name, const int& value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

template <>
inline void Shader::setUniform<float>(const std::string &name, const float& value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

template <>
inline void Shader::setUniform<bool>(const std::string &name, const bool& value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

template <>
inline void Shader::setUniform<glm::vec2>(const std::string &name,
                                          const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

template <>
inline void Shader::setUniform<glm::vec3>(const std::string &name,
                                          const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

template <>
inline void Shader::setUniform<glm::mat4>(const std::string &name,
                                          const glm::mat4& value) const
{
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0][0]);
}