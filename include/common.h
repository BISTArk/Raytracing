#ifndef COMMON_H
#define COMMON_H

#include<bits/stdc++.h>
using namespace std;

//constants
const float infinity = numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

// Utility Functions

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}

inline float random_float(){
    return rand()/(RAND_MAX+1.0);
}

inline float random_float(float min,float max){
    return min+(max-min)*random_float();
}

inline float clamp(float x,float minn,float maxx){
    return x<minn?minn:(x>maxx)?maxx:x;
}

// Common Headers

#include "ray.h"
#include "vector3.h"

#endif