//
//  Cylinder.cpp
//  assignment_3
//
//  Created by Christy Ye on 5/3/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#include "Cylinder.hpp"


void Cylinder::draw(OBJObject * object, GLuint shaderProgram, glm::mat4 M){

    object->draw(shaderProgram, M);

}