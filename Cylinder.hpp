//
//  Cylinder.hpp
//  assignment_3
//
//  Created by Christy Ye on 5/3/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#ifndef Cylinder_hpp
#define Cylinder_hpp

#include <stdio.h>
#include "OBJObject.h"

class Cylinder
{
public:

    Cylinder ();
    ~Cylinder();
    GLuint shaderProgram; 
    void draw(OBJObject * object, GLuint shaderProgram, glm::mat4 M);
};

#endif /* Cylinder_hpp */
