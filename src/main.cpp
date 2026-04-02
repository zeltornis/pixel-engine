#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "core/Window.hpp"
#include "core/Shader.hpp"
#include "core/Mesh.hpp"

int main() {
    Window wnd("Showroom");

    Shader shader("shaders/basic.vert", "shaders/basic.frag");
    shader.use();
    shader.setUniform(
        "uResolution",
        glm::vec2(Window::kDefaultWidth, Window::kDefaultHeight)
    );

    std::vector<float> vertices = {
        // positions       // colors
        -0.8f, 0.9f, 0.0f, 1.0f, 0.0f, 0.0f, // top left (red)
         0.8f, 0.9f, 0.0f, 0.0f, 1.0f, 0.0f, // top right (green)
        -0.8f,-0.9f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left (blue)
         0.8f,-0.9f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom left (yellow)
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, // triangle 0
        2, 3, 1  // triangle 1
    };

    Mesh quad(vertices, indices);

    while (!wnd.shouldClose())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime(); // seconds since GLFW init
        shader.setUniform("uTime", time);

        quad.render();

        wnd.swapBuffers();
        wnd.pollEvents();
    }
    
    return 0;
}