//
//  Group.hpp
//  assignment_3
//
//  Created by Christy Ye on 5/2/16.
//  Copyright © 2016 christy ye. All rights reserved.
//

#ifndef Group_hpp
#define Group_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Geode.hpp"
#include <list>

class Group : public Node
{
public:
    
    Group();
    ~Group();
    
    std::list < Node * > children;
    void addChild(Node * child);
    void removeChild(Node * oldNode);
    
    virtual void update (glm::mat4 C);
    virtual void draw();
    
};



#endif /* Group_hpp */
