#pragma once

#include <iostream>

#include <vector>
#include <memory>
#include <thread>
#include <chrono>

#include "entity.hpp"
#include "global.hpp"

#include "debug.hpp"

using namespace std::chrono_literals;

// Engine has ownership of all entitys.
// Scripts can use Pointers or References?

class Engine {

private:
    
    using chronoClock = std::chrono::steady_clock;
    
    inline static std::vector<std::unique_ptr<Entity>> entitys;

    // Is the renderer window open
    inline static bool windowOpen;


    // time thats adds up to 1s, when its 1s+ then it resets to 0 and updated the countedFps
    inline static std::chrono::duration<int64_t, std::nano> addingTime;

    // engines target fps
    inline static float targetFps;

    // the final counted fps by the engine (updates every second). It is 100% accurate. it literally counts each frame
    inline static int countedFps;

    // pending counted fps. Can be from 0-targetFps at runtime
    inline static int countingFps;

    // start updateing frames. (contains a while(windowOpen) loop)
    static void startUpdating() {
        std::chrono::duration<double> targetFrameTime;
        while(windowOpen){
            // +1 Frame
            countingFps++;

            // what time did this frame start
            auto frameStart = chronoClock::now();
            
            // get ms taken per frame (at target fps)
            targetFrameTime = std::chrono::duration<double>(1.0f / targetFps);

            // update the frame and run all Update()
            updateFrame();

            // get the time it took for the engine to update the frame
            auto realFrameTime = chronoClock::now() - frameStart;

            // if the engine took less time that the target frametime, wait the remainder
            if(realFrameTime < targetFrameTime){
                // waiting the remaining time..
                std::this_thread::sleep_for(targetFrameTime - realFrameTime);
            }

            // get the total time it took for the frame to update including waited time
            auto totalFrameTime = chronoClock::now() - frameStart;
            addingTime += totalFrameTime;

            // if the total frame rate was over 1s
            if(addingTime > 1s){
                addingTime = 0s;
                countedFps = countingFps;
                countingFps = 0;
                debug::log("FPS " + std::to_string(countedFps));
            }
        }
    }

    // Update Frame
    static void updateFrame() {
        callRenderApi();
        callUpdates();
    }

    static void callRenderApi() {
        for(size_t i = 0; i < entitys.size(); i++){
            
        }
    }

    // run all updates for all entitys
    static void callUpdates(){
        for(auto& e : entitys){
            for(auto& c : e->components){
                c->Update();
            }
        }
    }

    static void callAwakes(){
        for(auto& e : entitys){
            for(auto& c : e->components){
                c->Awake();
            }
        }
    }
    static void callStarts(){
        for(auto& e : entitys){
            for(auto& c : e->components){
                c->Start();
            }
        }
    }

    static void initializeRenderer(){
        windowOpen = true;
    }

public:

    // clears all entitys from the scene
    // resets it
    static void ClearScene(){
        entitys.clear();
    }

    static int FPS(){
        return countedFps;
    }

    // Writes a file called "scene_data.json"
    // about all the entitys and their data
    static void WriteSceneData(){
        for(auto& e : entitys){
            e->serialize();
        }
    }

    // starts the engine

    static void LoadScene(){
        
    }

    static void Start(){
        if(global::running){
            debug::error("Can't start the engine more than once!");
            return;
        }
        windowOpen = false;
        debug::log("Engine starting..");

        global::running = true;

        initializeRenderer();

        callAwakes();
        callStarts();

        startUpdating();
    }


    // set the engines target fps (default 60)
    static void SetTargetFps(int fps = 60){
        if(fps < 1){
            fps = 60;
        }

        // Set Renderer Target Fps...
    }


    // instantiate (spawm) an entity in the engine
    static Entity& Instatiate(std::string name = "Entity"){ 
        auto e = std::make_unique<Entity>(name, entitys.size());
        Entity& rawPtr = *e.get();
        entitys.push_back(std::move(e));
        return rawPtr;
    }
};

