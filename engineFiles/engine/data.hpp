#pragma once
#include "../include/nlohmann_json.hpp"

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3(float _x = 0, float _y = 0, float _z = 0){
        x=_x;
        y=_y;
        z=_z;
    }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector3, x, y, z)

struct Vector2 {
    float x;
    float y;

    Vector2(float _x = 0, float _y = 0){
        x=_x;
        y=_y;
    }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2, x, y)

struct Quaternion {
    float x;
    float y;
    float z;
    float w;

    Quaternion(float _x = 0, float _y = 0, float _z = 0, float _w = 1){
        x=_x;
        y=_y;
        z=_z;
        w=_w;
    }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Quaternion, x, y, z, w)

