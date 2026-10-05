#pragma once

#include <string>
#include <unordered_map>

#include "engine.hpp"
#include "components.hpp"
#include "global.hpp"
#include "json_helper.hpp"

#include "debug.hpp"

#include "../include/nlohmann_json.hpp"

using njson = nlohmann::json;

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

    // pointer to all components in entity (Serializable so even scripts without engine callbacks eg, Update() can be supported)
    std::vector<std::unique_ptr<Component>> components;

    // constructor for entity ,if your scripting, DO NOT USE THIS
    Entity (std::string& _name, int id = -1) {
        transform = Transform();
        renderer = Renderer();

        name = _name;
        objectId = id;
        if(objectId < 0) debug::error("Invalid ID for instantiated entity. If you tried to instantiate an entity, please use 'engine::instatiate()'");
    }
    ~Entity() = default;

    njson serialize(){
        njson out;

        out["name"] = name;
        out["id"]   = objectId;
        out["transform"] = {
            {"lposition", transform.localPosition},
            {"lscale",    transform.localScale},
            {"lrotation", transform.localRotation}
        };

        out["components"] = njson::array();
        for (auto& c : components) {
            njson cj;
            c->toJson(cj);             
            cj["type"] = c->typeName();
            out["components"].push_back(cj);
        }

        return out;
    }



    //// saves data as json on a file
    //void saveData() {
    //    debug::log("serializing entity: " + std::to_string(objectId));

    //    njson out;

    //    out["name"] = name;
    //    out["id"]   = objectId;
    //    out["transform"] = {
    //        {"lposition", transform.localPosition},
    //        {"lscale",    transform.localScale},
    //        {"lrotation", transform.localRotation}
    //    };

    //    out["components"] = njson::array();
    //    for (auto& c : components) {
    //        njson cj;
    //        c->toJson(cj);             
    //        cj["type"] = c->typeName();
    //        out["components"].push_back(cj);
    //    }

    //    std::ofstream file(std::to_string(objectId) + ".json");
    //    file << out.dump(4);
    //}

    // loads data
    void loadData(njson& j){
        name = j["name"];
        objectId = j["id"];
        transform.localPosition = j["transform"]["lposition"];
        transform.localScale = j["transform"]["lscale"];
        transform.localRotation = j["transform"]["lrotation"];

        components.clear();
        for (const auto& newComp : j["components"]) {
            std::string type = newComp["type"];
            auto component = componentReg::create(type);
            if (component) {
                component->fromJson(newComp);
                components.push_back(std::move(component));
            }
        }
    }

    // adds a component to the entity
    template <typename T, typename ...Args>
    T* addComponent(Args&& ... args){
        // create component in heap. Make pointer of it.
        std::unique_ptr<T> nComp = std::make_unique<T>(std::forward<Args>(args)...);
        
        // run components Start() if engine isnt running
        if(global::running) nComp->Start();

        // set the components entity reference to me
        nComp->entity = this;

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
