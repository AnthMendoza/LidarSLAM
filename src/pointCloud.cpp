
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "../include/VLPAPI.h"
#include <thread>
#include <iostream>
#include <algorithm>
#include <queue>


void drawPointCloud(const std::array<Point,5000>setOfPoints) {
    glBegin(GL_POINTS);
    for(const auto point : setOfPoints ){
        if(point.x <= 1 && point.y <= 1 ){
            continue;
        }
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
}




void filterPoints(std::array<Point,5000> &points){

    std::vector<Point> Xsorted;
    std::vector<Point> Ysorted;
    std::vector<Point> Zsorted;
    Xsorted.reserve(points.size());
    Ysorted.reserve(points.size());
    Zsorted.reserve(points.size());


    std::sort(Xsorted.begin(), Xsorted.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });

    std::sort(Ysorted.begin(), Ysorted.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

    std::sort(Zsorted.begin(), Zsorted.end(), [](const Point& a, const Point& b) {
        return a.z < b.z;
    });
    //check neighbors
    // x x x x x
    // x x C x x
    // x C o C x
    // x x C x x
    // x x x x x
    for(int i = 0 ; i < Xsorted.size() ; i++ ){


    }
        for(int i = 0 ; i < Xsorted.size() ; i++ ){
        

    }
        for(int i = 0 ; i < Xsorted.size() ; i++ ){
        

    }

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

    std::queue<Point> points;


    while (!glfwWindowShouldClose(window)) {
        getPoints(points);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(4.0f, 4.0f, 4.0f);
        glm::vec3 cameraPos(4.0f, 4.0f, 4.0f); 
        glm::vec3 target(0.0f, 0.0f, 0.0f);
        glm::vec3 up(0.0f, 0.0f, -1.0f);
        glm::mat4 view = glm::lookAt(cameraPos, target, up);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(view)); // Apply the view matrix

        drawPointCloud(points);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();

    UDPThread.join();
    return 0;
}

