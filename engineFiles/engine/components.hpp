#pragma once

#include <memory>
#include <vector>

#include "data.hpp"
#include "entity.hpp"

// Enum for compoennt tyoe (fast check for premade components)

// Components

class component{
public:
    entity* ownEntity;

    void awake() {}
    void start() {}
    void update() {}
};

class transform : public component{
public:
    vector3 position;
    vector3 scale;
    quaternion rotation;

    vector3 localPosition;
    vector3 localScale;
    quaternion localRotation;

    std::unique_ptr<transform> parent;
    std::vector<std::unique_ptr<transform>> children;
    
    //transform(){
    //    type = Tpersistant;
    //}
};

class renderer : public component{

};


class playerMovement : public component{

    

};