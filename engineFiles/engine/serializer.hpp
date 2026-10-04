#pragma once

class serializer{
private:
    // write variable data to save it
    template <typename T>
    static void writeData(T& var){

    }

    // read variable data to load it
    template <typename T>
    static void readData(T& var){

    }

public:
    static bool loadingData;

    static void load(){
        loadingData = true;
    }

    static void save(){
        loadingData = false;
    }

    template <typename T>
    static void addvar(const char* name, T& var){
        if(loadingData) {   writeData(var);  }
        else            {   readData(var);   }
    }
};

// Tell the engine to load this variable at runtime. It doesnt save at runtime or during project building

#define VARIABLE(variable) serializer::addvar(#variable, variable)

