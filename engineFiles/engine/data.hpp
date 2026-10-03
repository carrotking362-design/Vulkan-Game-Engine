#pragma once

struct vector3{
public:
    float x;
    float y;
    float z;
    
    vector3(float _x, float _y, float _z){
        x = _x; y = _y; z = _z;
    }
};

struct vector2{
public:
    float x;
    float y;
    
    vector2(float _x, float _y){
        x = _x; y = _y;
    }
};

struct quaternion{
public:
    float x;
    float y;
    float z;
    float w;
    
    quaternion(float _x, float _y, float _z, float _w){
        x = _x; y = _y; z = _z; w = _w;
    }
};



