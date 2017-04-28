#include "OBJObject.h"
#include "Window.h"


OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
    parse(filepath);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glGenBuffers(1,&normalbuffer); //mine
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GLfloat),(GLvoid*)0);

    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer); //mine
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW); //mine
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); //mine
    
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]) , &indices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

void OBJObject::parse(const char *filepath) 
{
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
    FILE* fp;     // file pointer
    float x,y,z;  // vertex coordinates
    int c1,c2;    // characters read from file
    
    fp = fopen(filepath,"rb");  // make the file name configurable so you can load other files
    
    if (fp == NULL) { cerr << "error loading file" << endl; exit(-1); }  // just in case the file can't be found or is corrupt

    while(!feof(fp)){
        
        c1 = fgetc(fp);
        
        if (c1 != 'v' && c1!='f')
            continue;
        
        c2 = fgetc(fp);

        if ((c1=='v') && (c2==' '))
        {
            glm::vec3 vertex;
            glm::vec3 temp_color;

           fscanf(fp, "%f %f %f", &x, &y, &z);

            vertex.x = x;
            vertex.y = y;
            vertex.z = z;
            vertices.push_back(vertex);
            
        }
        else if((c1 == 'v') && (c2=='n')) {
            //cerr<<"normal"<<endl;
            glm::vec3 normal;

            fscanf(fp, "%f %f %f ", &x, &y, &z);
            normal.x = x;
            normal.y = y;
            normal.z = z;
          
            normals.push_back(normal);
           // cerr<<"display normal.x "<<&normals[100]<<endl;
            
        }
        else if ((c1 == 'f') && (c2 == ' ')){

            unsigned int vertexIndex[3], normalIndex[3];
         
            fscanf(fp, "%u//%u %u//%u %u//%u", &vertexIndex[0],  &normalIndex[0], &vertexIndex[1],  &normalIndex[1],  &vertexIndex[2],  &normalIndex[2] );

            indices.push_back(vertexIndex[0]-1);
            indices.push_back(vertexIndex[1]-1);
            indices.push_back(vertexIndex[2]-1);
        }
        else{
            
        }
    }
    fclose(fp);   // make sure you don't forget to close the file when done
   printf("Finished parsing %s\n", filepath);
}

//meshing data
void OBJObject::draw(GLuint shaderProgram)
{
    //printf("starting the drawing func.\n");
    // Calculate combination of the model (toWorld), view (camera inverse), and perspective matrices
    glm::mat4 MVP = Window::P * Window::V * toWorld;

    // removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    glm::mat4 camera = Window::V;
    GLuint cameraID = glGetUniformLocation(shaderProgram, "camera");
    glUniformMatrix4fv(cameraID, 1, GL_FALSE, &camera[0][0]);
    
    glm::mat4 model = toWorld;
    GLuint modelID = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
    
    glm::mat4 projection = Window::P;
    GLuint projectionID = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
    
    //TODO: lights
    if(directional){
        glUniform1i(glGetUniformLocation(shaderProgram, "dirLight.dir"), 1);
        glUniform1i(glGetUniformLocation(shaderProgram, "light.point"), false);
        glUniform1i(glGetUniformLocation(shaderProgram, "splight.spot"), false);
    }
    else if (point){
        glUniform1i(glGetUniformLocation(shaderProgram, "light.point"), 1);
        glUniform1i(glGetUniformLocation(shaderProgram, "dirLight.dir"), false);
        glUniform1i(glGetUniformLocation(shaderProgram, "splight.spot"), false);
    }
    else if (spotlight){
        glUniform1i(glGetUniformLocation(shaderProgram, "splight.spot"), 1);
        glUniform1i(glGetUniformLocation(shaderProgram, "light.point"), false);
        glUniform1i(glGetUniformLocation(shaderProgram, "dirLight.dir"), false);
    }
    else{
        glUniform1i(glGetUniformLocation(shaderProgram, "dirLight.dir"), 1);
        glUniform1i(glGetUniformLocation(shaderProgram, "light.point"), false);
        glUniform1i(glGetUniformLocation(shaderProgram, "splight.spot"), false);
    }

    // Directional light
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.direction"), lightDirection.x, lightDirection.y, lightDirection.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.ambient"), 0.7f, 0.7f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
  
    //Point
    glUniform1f(glGetUniformLocation(shaderProgram, "light.quadratic"), quad);
    glUniform3f(glGetUniformLocation(shaderProgram, "light.direction"), lightDirection.x , lightDirection.y , lightDirection.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "light.position"), lightDirection.x , lightDirection.y , lightDirection.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "light.ambient"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "light.diffuse"), 0.9f, 0.9f, 0.9f);
    glUniform3f(glGetUniformLocation(shaderProgram, "light.specular"),0.5f, 0.5f, 0.5f);
    
    //spot
    // glUniform1f(glGetUniformLocation(shaderProgram, "splight.attenuation"), 0.5f);
    glUniform1f(glGetUniformLocation(shaderProgram, "splight.quadratic"), quad);
    glUniform3f(glGetUniformLocation(shaderProgram, "splight.direction"), lightDirection.x , lightDirection.y , lightDirection.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "splight.ambient"), 0.5f , 0.5f , 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "splight.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "splight.specular"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "splight.position"), lightDirection.x, lightDirection.y, lightDirection.z);
    glUniform1f(glGetUniformLocation(shaderProgram, "splight.cutoff"), cutoff);
   // glUniform1f(glGetUniformLocation(shaderProgram, "splight.outerCutOff"), outerCutOff);
    glUniform1f(glGetUniformLocation(shaderProgram, "splight.exponent"), exponent);
    
    //materials
    glUniform3f(glGetUniformLocation(shaderProgram, "materials.amb"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "materials.diff"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shaderProgram, "materials.spec"),specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shaderProgram, "materials.shiny"), shininess);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLint) indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
}

void OBJObject::draw(GLuint shaderProgram, glm::mat4 M)
{
    glUseProgram(shaderProgram);

    glm::mat4 MVP = Window::P * Window::V * toWorld;
    
    // Calculate combination of the model (toWorld), view (camera inverse), and perspective matrices
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    GLuint cameraID = glGetUniformLocation(shaderProgram, "camera");
    glUniformMatrix4fv(cameraID, 1, GL_FALSE, &Window::V[0][0]);
    
    GLuint modelID = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelID, 1, GL_FALSE, &M[0][0]);
    
    GLuint projectionID = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, &Window::P[0][0]);
    
    //dirlight
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.direction"), 5.0f, 5.0f, 5.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
 
    //materials
    glUniform3f(glGetUniformLocation(shaderProgram, "materials.amb"), 0.0215f, 0.1745f, 0.0215f);
    glUniform3f(glGetUniformLocation(shaderProgram, "materials.diff"), 0.07568f, 0.61424f, 0.07568f);
    glUniform3f(glGetUniformLocation(shaderProgram, "materials.spec"),0.633f, 0.727811f,0.633f);
    glUniform1f(glGetUniformLocation(shaderProgram, "materials.shiny"), 0.6f);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLint) indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
}




