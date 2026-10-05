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
        using namespace std::chrono_literals;

        // track the time we last reset our 1-second FPS counter
        auto fpsTimer = chronoClock::now();

        while (windowOpen) {
            // +1 Frame
            countingFps++;

            // get the time it took to run this frame
            auto frameStart = chronoClock::now();

            // get ms taken per frame (at target fps)
            auto targetFrameTime = std::chrono::duration<double>(1.0 / targetFps);

            // update the frame and run all Update()
            updateFrame();

            // calculate the exact time this frame ought to finish
            auto targetEnd = frameStart + targetFrameTime;

            // sleep when high remaining time
            //while (targetEnd - chronoClock::now() > 2ms) {
            //    std::this_thread::sleep_for(1ms);
            //}

            // preciser delay
            while (chronoClock::now() < targetEnd) {}

            // get current time after frame processing and waiting
            auto now = chronoClock::now();

            // if 1 second has elapsed since last FPS log
            if (now - fpsTimer >= 1s) {
                countedFps = countingFps;
                countingFps = 0;

                // advance timer by exactly 1s to retain leftover fractional seconds and prevent time drift
                fpsTimer += 1s;

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
        std::vector<njson> json_entitys;
        for(auto& e : entitys){
            json_entitys.push_back(e->serialize());
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

        if(targetFps < 1){
            targetFps = 60;
        }

        global::running = true;

        initializeRenderer();

        callAwakes();
        callStarts();

        startUpdating();
    }


    // set the engines target fps (default 60)
    // targetFps(0) means the Fps in unbound
    static void SetTargetFps(int64_t fps = 60){
        if(fps < 1){
            fps = 1000000000000;
        }

        // Set Renderer Target Fps...
        targetFps = fps;
    }


    // instantiate (spawm) an entity in the engine
    static Entity& Instatiate(std::string name = "Entity"){ 
        auto e = std::make_unique<Entity>(name, entitys.size());
        Entity& rawPtr = *e.get();
        entitys.push_back(std::move(e));
        return rawPtr;
    }
};

