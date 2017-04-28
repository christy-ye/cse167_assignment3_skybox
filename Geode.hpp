//
//  Geode.hpp
//  assignment_3
//
//  Created by Christy Ye on 5/2/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#ifndef Geode_hpp
#define Geode_hpp
#include "Node.hpp"
#include "OBJObject.h"

using namespace std;

class Geode: public Node
{
public:
    
    Geode(OBJObject * object, GLuint shaderProgram);
    ~Geode();
    
    float angle;
    
    //TODO: Modify OBJ to take in matrix
    glm::mat4 M;
    OBJObject * toDraw;
    GLuint shader; 
      void update (glm::mat4 M);
      void draw();
    void spin (); 
};

#endif /* Geode_hpp */
