//
//  Pod.hpp
//  assignment_3
//
//  Created by Christy Ye on 5/3/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#ifndef Pod_hpp
#define Pod_hpp

#include <stdio.h>
#include "OBJObject.h"

class Pod
{
public:

    Pod();
    ~Pod();
    GLuint shaderProgram;
    void draw(OBJObject * object, GLuint shaderProgram, glm::mat4 M);
};

#endif /* Pod_hpp */
