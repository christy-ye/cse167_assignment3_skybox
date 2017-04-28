//
//  Node.hpp
//  assignment_3
//
//  Created by Christy Ye on 5/2/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

class Node
{
public:
    
    virtual void draw() =0;
    virtual void update(glm::mat4 M) =0;
    
};



#endif /* Node_hpp */
