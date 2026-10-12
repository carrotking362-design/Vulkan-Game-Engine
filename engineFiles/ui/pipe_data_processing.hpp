#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <bit>

#include "byte_enums.hpp"

// includes for engine 'injection' and 'communication'

#include "../engine/engine.hpp"

// overall ui transport layer manager for the c# invoke method
class to_ui{
private:

    template <typename T>
    static std::vector<uint8_t> getBytes(const T& value) {
        std::vector<uint8_t> bytes(sizeof(T));
        std::memcpy(bytes.data(), &value, sizeof(T));
        return bytes;
    }

    static std::vector<uint8_t> engineHeader(uint8_t command, std::vector<uint8_t>& args){
        debug::log("in Engine Header..");
        switch(command){
            case ecode::error:
            case ecode::null:
                return {0xFF, 0xFF};
            
            case ecode::getfps:{
                auto payload = getBytes<int>(Engine::FPS());
                std::vector<uint8_t> output = {h::engine, ecode::getfps};
                output.insert(output.end(), payload.begin(), payload.end());
                return output;
            }
            case ecode::setfps:{
                int targetFps = 0;
                std::memcpy(&targetFps, args.data(), sizeof(int));
                Engine::SetTargetFps(targetFps);
                debug::success("Set Engine FPS to: '" + std::to_string(targetFps)  + "' From C# command");

                return {h::engine, ecode::setfps};
            }
            case ecode::pause:{
                debug::success("Pausing engine from C#");
                Engine::Pause();


                auto payload = getBytes<int>(Engine::FPS());
                std::vector<uint8_t> output = {h::engine, ecode::getfps};
                output.insert(output.end(), payload.begin(), payload.end());
                return output;
            }
            case ecode::play:{
                debug::success("Playing engine from C#");
                Engine::Play();

                auto payload = getBytes<int>(Engine::FPS());
                std::vector<uint8_t> output = {h::engine, ecode::getfps};
                output.insert(output.end(), payload.begin(), payload.end());
                return output;
            }
        }
    }

    static std::vector<uint8_t> rendererHeader(uint8_t command, std::vector<uint8_t>& args){
        debug::log("in Renderer Header..");
        switch(command){
            
        }
    }

    static std::vector<uint8_t> sceneHeader(uint8_t command, std::vector<uint8_t>& args){
        debug::log("in Scene Header..");
        switch(command){
            
        }
    }

public:

    // Process Command
    static std::vector<uint8_t> processCommand(uint8_t header, uint8_t command, std::vector<uint8_t> args){
        debug::log("Recieved Command from C#");
        switch(header){
            // Why on earth would C# send an error byte? it shouldnt but its better to be safe than sorry...
            case h::error:
            case h::null:
                return {h::error, error::header};
            case h::engine:
                return engineHeader(command, args);
            case h::renderer:
                return rendererHeader(command, args);
            case h::scene:
                return sceneHeader(command, args);
        }
        return {0xFF, 0xFF};
    }
};


