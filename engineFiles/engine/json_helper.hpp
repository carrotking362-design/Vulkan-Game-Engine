#pragma once

#include <string>
#include <vector>

#include <fstream>

class json{
public:
    std::vector<std::string> data;

    void writeTo(std::string filename){
        std::ofstream file(filename);
        file << "{\n";
        for(std::string& item : data){
            file << item + "\n";
        }
        file << "}";
        file.close();
    }


    static std::string field();

    static std::string field(std::string name, std::string value, bool last = false){
        std::string output = "";
        output += '"' + name + '"' + ':' + '"' + value + '"';
        if(!last){
            output += ",";
        }
        return output;
    }

    static std::string field(std::string name, float value, bool last = false){
        std::string output = "";
        output += '"' + name + '"' + ':' + '"' + std::to_string(value) + '"';
        if(!last){
            output += ",";
        }
        return output;
    }
    static std::string field(std::string name, int value, bool last = false){
        std::string output = "";
        output += '"' + name + '"' + ':' + '"' + std::to_string(value) + '"';
        if(!last){
            output += ",";
        }
        return output;
    }
};

