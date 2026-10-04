#pragma once

struct Vector3{
public:
    float x;
    float y;
    float z;
    
    Vector3(float _x=0, float _y=0, float _z=0){
        x = _x; y = _y; z = _z;
    }
};

struct Vector2{
public:
    float x;
    float y;
    
    Vector2(float _x = 0, float _y=0){
        x = _x; y = _y;
    }
};

struct Quaternion{
public:
    float x;
    float y;
    float z;
    float w;
    
    Quaternion(float _x=0, float _y=0, float _z=0, float _w=0){
        x = _x; y = _y; z = _z; w = _w;
    }
};



