#include <iostream>
#include <string>
#include <future>

#include "engine/global.hpp"
#include "engine/engine.hpp"

#include "engine/components.hpp"
#include "engine/scene.hpp"

#include "include/nlohmann_json.hpp"

#include "ui/pipe_manager.hpp"

// json saving test component
class SaveJson : public Component{
public:
    int number = -1;

    COMPONENT(SaveJson, number)
};

// the engine will automatically handle this all later on..

std::future<void> asyncMethod;

void asyncInput(){
    std::string x;

    while(true){
        std::cin >> x;
        if(x == "p"){
            if(global::running){
                debug::log("pausing");
                Engine::Pause();
            }
            else{
                debug::log("playing");
                Engine::Play();
            }
        }
    }
}

int main() {
    //auto& plr = Engine::Instatiate("Player");
    //plr.transform.localPosition = Vector3(1, 20, 300);
    //auto* comp = plr.addComponent<SaveJson>();
    //comp->number = 1;

    //auto& plr2 = Engine::Instatiate("Player2");
    //plr2.transform.localPosition = Vector3(-123.1f, 20.13f, 350);
    //auto* comp2 = plr2.addComponent<SaveJson>();
    //comp2->number = 2;

    //SceneManager::save("coolScenes");

    pipe::asyncStart();
    //asyncMethod = std::async(std::launch::async, asyncInput);

    Engine::SetTargetFps(999);

    //Engine::WriteSceneData();
    Engine::Start();
    
    
    return 0;
}

