#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    Window(const std::string& title);
    ~Window();

    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;

    GLFWwindow* getNativeHandle() const { return window; }

    static constexpr int kDefaultWidth = 800;
    static constexpr int kDefaultHeight = 600;

private:
    GLFWwindow* window;
    int width;
    int height;
    std::string title;

    static void framebufferSizeCallback(
        GLFWwindow* window,
        int width,
        int height
    );
};