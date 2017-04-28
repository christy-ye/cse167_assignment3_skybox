//
//  MatrixTransform.cpp
//  assignment_3
//
//  Created by Christy Ye on 5/2/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#include "MatrixTransform.hpp"


MatrixTransform::MatrixTransform(glm::mat4 M){
    this->M = M;
    this->T = glm::mat4 (1.0f);
    angle = 0; 
}

void MatrixTransform:: spin (){
    
   // angle = 0.005f;
    
  //  M =  M * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}


void MatrixTransform::update(glm::mat4 C){

    glm::mat4 product = C * M;

    std::list< Node * >::iterator i;
    
    for ( i =  children.begin() ; i != children.end(); i ++){
        (*i)->update(product);
    }
}