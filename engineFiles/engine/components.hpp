#pragma once

#include <memory>
#include <vector>

#include "data.hpp"
#include "entity.hpp"
#include "debug.hpp"

#include "../include/nlohmann_json.hpp"
using nloh_json = nlohmann::json;

// Enum for compoennt tyoe (fast check for premade components)

// Components

struct Entity;

// Links with serializer.hpp

class Component{
public:
    Entity* entity;

    virtual ~Component() = default;

    virtual void Awake()    {}
    virtual void Start()    {}
    virtual void Update()   {}

    virtual const char* typeName() const         {return "";}          
    virtual void toJson(nloh_json& j) const      {return   ;}            
    virtual void fromJson(const nloh_json& j)    {return   ;}    
};

// Updated Version

#include "../include/nlohmann_json.hpp"
using nloh_json = nlohmann::json;

//#define REGISTER_COMPONENT(...) register_component(this, #__VA_ARGS__, __VA_ARGS__); 
// Instead of REGISTER_COMPONENT, you can use this for each variable
//#define REGISTER_FIELD(variable) register_field(this, #variable, variable);


// keeps track and has all serializable components
class componentReg{
    using fPtr = std::function<std::unique_ptr<Component>()>;
public:
        static auto& map() {
            static std::unordered_map<std::string, fPtr> output;
            return output;
        }
        template <typename T>
        static void addComp(const char* name){
            // lambda function
            // Makes a function that is just:
            // unique_ptr<T> makeT() {returns make_unique<T>();}
            // pointer is then turned into a <Serializable>
            map()[name] = [] {return std::make_unique<T>(); };
        }

        static std::unique_ptr<Component> create(const std::string& name) {
            auto& m = map();
            auto comp = m.find(name);

            // if component is in the map
            if(comp != m.end()){
                return comp->second();
            }
            else{
                debug::warn("nullptr returned when ran 'create' for component: " + name);
                return nullptr;
            }
        }
};

// runs on start ups
template <typename T>
class _registerer{
public:
    _registerer(const char* name){
        componentReg::addComp<T>(name);
    }
};


#define COMPONENT(type, ...)                                                \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(type, __VA_ARGS__)                       \
    const char* typeName() const override { return #type; }                 \
    void toJson(nloh_json& j) const override { to_json(j, *this); }         \
    void fromJson(const nloh_json& j) override { from_json(j, *this); }     \
    static inline _registerer<type> registrar_{#type};




class Transform : public Component{
public:
    Vector3 position;
    Vector3 scale;
    Quaternion rotation;

    Vector3 localPosition;
    Vector3 localScale;
    Quaternion localRotation;

    Transform* parent;
    std::vector<Transform*> children;

    unsigned int parentId;

    Transform() {
        position, scale, localPosition, localScale = Vector3();
        rotation, localRotation = Quaternion();
        parent = nullptr;
    }

    COMPONENT(Transform, position, scale, rotation, localPosition, localScale, localRotation, parentId)
};


class Renderer : public Component{

};

