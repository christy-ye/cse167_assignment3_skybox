//
//  MatrixTransform.hpp
//  assignment_3
//
//  Created by Christy Ye on 5/2/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#ifndef MatrixTransform_hpp
#define MatrixTransform_hpp

#include <stdio.h>
#include "Group.hpp"


class MatrixTransform: public Group
{
public:
    
    MatrixTransform(glm::mat4 M);
    ~MatrixTransform();
    glm::mat4 M;
    float angle;
    bool spinMT;
    
    glm::mat4 T;
    void update(glm::mat4 C);
    void spin ();
    
};

#endif /* MatrixTransform_hpp */
