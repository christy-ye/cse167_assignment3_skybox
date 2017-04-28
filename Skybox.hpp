#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>
#include "shader.h"

using namespace std;

class Skybox
{
public:
    
    Skybox(std::vector<const GLchar*> faces);
    //~Skybox();
    
    glm::mat4 skyboxWorld;
    GLuint VBO, VAO, EBO;
    GLuint skyboxTexture;
    GLuint textureID;
    
    
    //sides
    GLchar* base;
    GLchar * front;
    GLchar *left;
    GLchar * right;
    GLchar *top;
     GLchar * back;
    
    float angle;
    
    void draw(GLuint skyboxShader);
    unsigned char *  loadPPM(const char* filename, int & width, int &height);
    GLuint loadTexture(const char * filename);
     void loadCubemap(std::vector<const GLchar*> faces);
    
};

#endif


