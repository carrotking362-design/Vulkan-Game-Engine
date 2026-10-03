#pragma once

#include <iostream>

#include <vector>
#include <memory>

#include "entity.hpp"
#include "debug.hpp"

// Engine has ownership of all entitys.
// Scripts can use Pointers or References?

class engine    {

private:
    static std::vector<std::unique_ptr<entity>> entitys;
    

    static void callRenderApi() {
        for(size_t i = 0; i < entitys.size(); i++){
            
        }
    }

    // run all updates for all entitys
    static void callUpdates(){
        for(auto& e : entitys){
            for(auto& c : e->components){
                c->update();
            }
        }
    }

    static void callAwakes(){
        for(auto& e : entitys){
            for(auto& c : e->components){
                c->awake();
            }
        }
    }
    static void callStarts(){
        for(auto& e : entitys){
            for(auto& c : e->components){
                c->start();
            }
        }
    }

    static void initializeRenderer(){

    }

public:

    // clears all entitys from the scene
    // resets it
    static void clearScene(){
        entitys.clear();
    }

    // starts the engine
    static void start(){
        debug::log("Engine starting..");

        initializeRenderer();

        callAwakes();
        callStarts();


    }


    // set the engines target fps (default 60)
    static void setTargetFps(int fps = 60){
        if(fps < 1){
            fps = 60;
        }

        // Set Renderer Target Fps...
    }

    // run a frame, i guess bro
    static void runFrame() {
        callRenderApi();
        callUpdates();
    }

    // instantiate (spawm) an entity in the engine
    static entity* instatiate(std::string name = "Entity"){ 
        auto e = std::make_unique<entity>(name, entitys.size());
        entitys.push_back(e);
        return e.get();
    }
};

