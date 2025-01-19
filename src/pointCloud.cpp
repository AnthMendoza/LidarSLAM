
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../include/VLPAPI.h"
#include <thread>
#include <iostream>


void drawPointCloud(const std::array<std::vector<Point>, 20> &setOfPoints) {
    glBegin(GL_POINTS);
    for(const auto cluster : setOfPoints ){
        for (const auto& point : cluster) {
            glVertex3f(point.x, point.y, point.z);
        }
    }
    glEnd();
}




int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Point Cloud Viewer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        return -1;
    }
    std::thread UDPThread(UDP);



    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10000.0f);
    std::vector<Point> points;
    std::array<std::vector<Point>, 20> setOfPoints = {};
    int count = 0;
    while (!glfwWindowShouldClose(window)) {
        getPoints(points);

        setOfPoints[static_cast<int>(count%20)] = points;

        count++;

        for(auto point : points ){
            std::cout<< "("<<point.x << " , " << point.y << " , " <<point.z << ")";
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -3.0f);

        drawPointCloud(setOfPoints);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();

    UDPThread.join();
    return 0;
}

