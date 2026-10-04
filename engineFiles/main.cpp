#include <iostream>
#include <string>

#include "engine/global.hpp"
#include "engine/engine.hpp"

class CustomCompTest : public Component{
public:
    void Start() override{
        debug::log("start()");
    }
};

// the engine will automatically handle this all later on..

int main() {
    auto& plr = Engine::Instatiate("Player");
    plr.transform.position = Vector3(1, 20, 300);
    plr.addComponent<CustomCompTest>();

    auto& plr2 = Engine::Instatiate("Player2");
    plr2.transform.position = Vector3(1, 20, 300);

    Engine::Start();
    Engine::WriteSceneData();

    std::string x;
    std::cin >> x;
    return 0;
}

