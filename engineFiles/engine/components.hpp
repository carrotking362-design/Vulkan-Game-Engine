#pragma once

#include <memory>
#include <vector>

#include "data.hpp"
#include "entity.hpp"

#include "serializer.hpp"

// Enum for compoennt tyoe (fast check for premade components)

// Components

struct Entity;

class Component{
public:
    Entity* ownEntity;

    virtual ~Component() = default;

    virtual void Awake() {}
    virtual void Start() {}
    virtual void Update() {}

    virtual void Serialize() {}
};

class Transform : public Component{
public:
    Vector3 position;
    Vector3 scale;
    Quaternion rotation;

    Vector3 localPosition;
    Vector3 localScale;
    Quaternion localRotation;

    std::unique_ptr<Transform> parent;
    std::vector<std::unique_ptr<Transform>> children;

    Transform() {
        position, scale, localPosition, localScale = Vector3();
        rotation, localRotation = Quaternion();
        parent = nullptr;
    }
};

class Renderer : public Component{

};

class CustomComponent : public Component{
public:
    int number = 21;

    void Serialize() override{
        VARIABLE(number);
    }
};

