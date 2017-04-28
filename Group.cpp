//
//  Group.cpp
//  assignment_3
//
//  Created by Christy Ye on 5/2/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#include "Group.hpp"

Group::Group(){

}
Group:: ~Group(){

}
void Group::addChild(Node * child){

    children.push_back(child);
}

void Group:: removeChild(Node * oldNode){
    children.remove(oldNode);
    
}

void Group:: draw(){
    
    std::list< Node * >::iterator i;
    for ( i = children.begin() ; i != children.end(); i ++){
        (*i)->draw();
    }

}

void Group::update(glm::mat4 C){
    
    std::list< Node * >::iterator i;
    for ( i = children.begin() ; i != children.end(); i ++){
        (*i)->update(C);
    }

}