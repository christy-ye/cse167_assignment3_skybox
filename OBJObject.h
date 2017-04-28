#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

using namespace std;

class OBJObject
{
private:
std::vector<unsigned int> indices; //face index
    std::vector <unsigned int >normal_indices; //normal index

    //mine
std::vector<glm::vec3> colors; //rgb store
    float angle;
    float size;
  //  float r,g,b;

public:
    glm::mat4 toWorld;
	OBJObject(const char* filepath);
    ~OBJObject();
    std::vector<glm::vec3> vertices; //vert
    std::vector<glm::vec3> normals;  //normals

	void parse(const char* filepath);
    void draw(GLuint shaderProgram);
    //mine
    void draw(GLuint shaderProgram, glm::mat4 M);
    void spin(float);
    void update();
    
    //mine
    void translation(float x, float y , float z );
    void rotate(float d);
    void Drawable(const char * filepath, OBJObject *& object);
    GLuint VBO, VAO, EBO;
    GLuint normalbuffer;
   // glm::vec3 mousePos;
    
    //tracking
    float maxX;
    float minX;
    float maxY;
    float minY;
    float maxZ;
    float minZ;
    
    //lighting
    glm::vec3 position; //for distance 
    glm::vec4 intensities;
    glm::vec4 lightDirection = glm::vec4 (1.0f);
    glm::vec3 direction;
    float sp_control =0.5f;
    glm::vec3 plightDirection; 
    float cutoff = 5.0f;
    float outerCutOff = 35.0f;
    float exponent = -10000.0f;
    
    float quad = 0.01f;
    
    bool directional = false;
    bool point = false;
    bool spotlight = false;
    
    //materials
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLfloat shininess;

    
};

#endif