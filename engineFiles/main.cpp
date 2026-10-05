#include <iostream>
#include <string>

#include "engine/global.hpp"
#include "engine/engine.hpp"

#include "engine/components.hpp"

#include "include/nlohmann_json.hpp"

// json saving test component
class SaveJson : public Component{
public:
    int number = 12;

    COMPONENT(SaveJson, number)
};

// the engine will automatically handle this all later on..

int main() {
    auto& plr = Engine::Instatiate("Player");
    plr.transform.position = Vector3(1, 20, 300);
    auto* comp = plr.addComponent<SaveJson>();
    //comp->number = 1;
    plr.addComponent<SaveJson>();

    auto& plr2 = Engine::Instatiate("Player2");
    plr2.transform.position = Vector3(-123.1f, 20.13f, 350);
    comp = plr.addComponent<SaveJson>();
    //comp->number = 2;

    //Engine::SetTargetFps(100);

    Engine::WriteSceneData();
    Engine::Start();
    
    std::string x;
    std::cin >> x;
    return 0;
}

