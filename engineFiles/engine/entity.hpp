#pragma once

#include <string>
#include <unordered_map>

#include "engine.hpp"
#include "components.hpp"

struct entity   {
    
public:
    // entity name (cosmetic)
    std::string name = "Entity";

    // its unique, engine-assigned ID
    int objectId = -1;

    // its transform component
    transform ownTransform();
    // its renderer component
    renderer ownRenderer();

    // pointer to all components in entity
    std::vector<std::unique_ptr<component>> components;

    // constructor for entity ,if your scripting, DO NOT USE THIS
    entity (std::string& _name, int id = -1) {
        name = _name;
        objectId = id;
        if(objectId < 0) debug::error("Invalid ID for instantiated entity. If you tried to instantiate an entity, please use 'engine::instatiate()'");
    }

    // adds a component to the entity
    template <typename T, typename ...Args>
    component* addComponent(Args&& ... args){
        // create component in heap. Make pointer of it.
        std::unique_ptr<T> nComp = std::make_unique<T>(std::forward<Args>(args)...);
        s
        // put pointer in components vector
        components.push_back(std::move(nComp));

        // return base pointer
        return nComp.get();
    }


    
    template <typename T>
    T* getComponent(){
        // for each component, check if it can be casted to T
        for(auto c : components){
            // dyncamic casts component to T
            if(T* found dynamic_cast<T*>(c.get())){
                // returns basic pointer to found component (T*)
                return found;
            }
        }

        // no components can be casted to T! compoennt not found
        debug::warn("getComponent() returning nullptr, component not found");
        // so return null pointer
        return nullptr;
    }

};