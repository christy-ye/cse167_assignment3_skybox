#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Cube.h"
#include "shader.h"
#include <GLUT/glut.h>
#include "Skybox.hpp"

#include "Node.hpp"
#include "Geode.hpp"
#include "Group.hpp"
#include "MatrixTransform.hpp"

class Window
{
public:
	static int width;
	static int height;
    static double cur_x, cur_y;
    static double prev_x, prev_y;
    static double scrollX, scrollY;
	static glm::mat4 P;
	static glm::mat4 V;
    static glm::mat4 bearV;
    static glm::mat4 bearP; 
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    //mouse controls
    static void cursor_callback(GLFWwindow* window, double x, double y);
    static glm::vec3 mouseMovement(int x, int y);
    static void mouseCompute (int cur_x, int cur_y, int prev_x, int prev_y);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset , double yoffset);

    //glm::vec3 trans, glm::vec3 rot , float angle, glm::vec3 scale
    static  glm::mat4 calcMT(float angle, glm::vec3 rot , glm::vec3 scale, glm::vec3 trans);
    
    static glm::mat4 level ( glm::vec3 trans, glm::vec3 scale);
    static glm::mat4 armCalc (float angle, glm::vec3 rot , glm::vec3 scale, glm::vec3 trans);
    static glm::mat4 podCalc (float angle, glm::vec3 rot , glm::vec3 scale, glm::vec3 trans);
    
    glm::vec3 axis; 
    float dx, dy, dz;
    //static bool mouse_on = false;
};

#endif
