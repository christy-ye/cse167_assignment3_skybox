//
//  Geode.cpp
//  assignment_3
//
//  Created by Christy Ye on 5/2/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#include "Geode.hpp"

Geode:: Geode(OBJObject * object, GLuint shaderProgram){
    
    M = glm::mat4(1.0f);
    

    toDraw = object;
    shader = shaderProgram;
    
    angle = 0;
    //draw();

}

void Geode:: update (glm::mat4 C){
    M = C ;
}

void Geode:: spin (){
    
 //   angle += 0.05f;
    
 //   M =  M * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Geode:: draw(){
    toDraw -> draw(shader , M);
}
