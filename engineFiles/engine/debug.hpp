#pragma once

#include <string>
#include <iostream>
#include <cstdint>

class debug {
public:
    // colors

    static std::string green(){
        return "\033[32m";
    }
    static std::string yellow(){
        return "\033[33m";
    }
    static std::string red() {
        return "\033[31m";
    }
    static std::string blue() {
        return "\033[31m";
    }
    static std::string white() {
        return "\033[0m";
    }

    static std::string color(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255){
        return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }

    // methods

    static void success(std::string text){
        std::cout << green() << text << white();
    }

    // Logs a message on the console
    // color_code can be any colors or color() from the debug class. or any other ASCII color code thingys
    static void log(std::string text, std::string color_code = white()){
        std::cout << color_code << text << white();
    }

    static void warn(std::string text){
        std::cout << yellow() << text << white();
    }

    static void error(std::string text){
        std::cout << red() << text << white();
    }

    
};