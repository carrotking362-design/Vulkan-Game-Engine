#include <iostream>
#include <string>

#include "engine/debug.hpp"

#include "engine/engine.hpp"

int main() {

    debug::log("Hi there", debug::green());

    engine::start();

    std::string x;
    std::cin >> x;
    return 0;
}

