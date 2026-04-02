#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

Shader::Shader(const std::string &vertPath, const std::string &fragPath)
{
    std::string vertCode = loadSource(vertPath);
    std::string fragCode = loadSource(fragPath);

    GLuint vertex = compileShader(vertCode, GL_VERTEX_SHADER);
    GLuint fragment = compileShader(fragCode, GL_FRAGMENT_SHADER);

    // Linking
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    // Check for linking errors
    int success;
    char infoLogBuf[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, nullptr, infoLogBuf);
        std::cerr << "ERROR: Shader program: Linking failed\n" 
                  << infoLogBuf << std::endl;
        throw std::runtime_error("Shader linking failed");
    }

    // Shaders not needed after linking
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::use() const 
{
    glUseProgram(id);
}

std::string Shader::loadSource(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open shader file: " + path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(const std::string &source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Check for compile errors
    int success;
    char infoLogBuf[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLogBuf);
        std::cerr << "ERROR: Shader: Compilation failed\n" 
                  << infoLogBuf << std::endl;
        throw std::runtime_error("Shader compilation failed");
    }
    return shader;
}

