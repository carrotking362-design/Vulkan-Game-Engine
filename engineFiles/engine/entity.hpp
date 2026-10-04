#pragma once

#include <string>
#include <unordered_map>

#include "engine.hpp"
#include "components.hpp"
#include "global.hpp"
#include "json_helper.hpp"

#include "debug.hpp"

struct Entity  {
private:
    // its unique, engine-assigned ID
    int objectId = -1;
public:
    // entity name (cosmetic)
    std::string name = "Entity";

    // its transform component
    Transform transform;

    // its renderer component
    Renderer renderer;

    // pointer to all components in entity
    std::vector<std::unique_ptr<Component>> components;

    // constructor for entity ,if your scripting, DO NOT USE THIS
    Entity (std::string& _name, int id = -1) {
        transform = Transform();
        renderer = Renderer();

        name = _name;
        objectId = id;
        if(objectId < 0) debug::error("Invalid ID for instantiated entity. If you tried to instantiate an entity, please use 'engine::instatiate()'");
    }

    // serialize entity data to json
    void serialize(){
        json output;
        output.data = {
            json::field("name", name),
            json::field("id", objectId),

            json::field("px", transform.position.x),
            json::field("py", transform.position.y),
            json::field("pz", transform.position.z, true)
        };
        output.writeTo(std::to_string(objectId) + ".json");
    }

    // adds a component to the entity
    template <typename T, typename ...Args>
    Component* addComponent(Args&& ... args){
        // create component in heap. Make pointer of it.
        std::unique_ptr<T> nComp = std::make_unique<T>(std::forward<Args>(args)...);
        
        // run components Start() if engine isnt running
        if(global::running) nComp->Start();

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
            if(T* found = dynamic_cast<T*>(c.get())){
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
