#ifndef VECTOR3_H
#define VECTOR3_H

#include<bits/stdc++.h>
#include "common.h"
using namespace std;

class vector3{
    public:

    float vec[3];
    vector3():vec{0,0,0}{}
    vector3(float x,float y,float z):vec{x,y,z}{}

    float x() const {return vec[0];}
    float y() const {return vec[1];}
    float z() const {return vec[2];}

    vector3 operator-() const{return vector3(-vec[0],-vec[1],-vec[2]);}
    float operator[](int i) const{return vec[i];}
    float& operator[](int i) {return vec[i];}

    vector3& operator+=(const vector3 &v){
        vec[0]+=v[0];
        vec[1]+=v[1];
        vec[2]+=v[2];
        return *this;
    }

    vector3& operator*=(const float t){
        vec[0]*=t;
        vec[1]*=t;
        vec[2]*=t;
        return *this;
    }

    vector3& operator/=(const float t){
        return *this*=(1/t);
    }

    float mag_squared() const{
        return vec[0]*vec[0] +vec[1]*vec[1] +vec[2]*vec[2];
    }

    float mag() const{
        return sqrt(mag_squared());
    }

    bool near_zero() const{
        const auto s = 1e-8;
        return (fabsf(vec[0])<s && fabsf(vec[1]) && fabsf(vec[2]));
    }
};

using point3 = vector3;
using color = vector3;


//vector3 utility finctions

inline ostream& operator<<(ostream &out, const vector3 &v){
    return out<<v.vec[0]<<' '<<v.vec[1]<<' '<<v.vec[2];
}

inline vector3 operator+(const vector3 &u, const vector3 &v){
    return vector3(u.vec[0]+v.vec[0],u.vec[1]+v.vec[1],u.vec[2]+v.vec[2]);
}

inline vector3 operator-(const vector3 &u, const vector3 &v){
    return vector3(u.vec[0]-v.vec[0],u.vec[1]-v.vec[1],u.vec[2]-v.vec[2]);
}

inline vector3 operator*(const vector3 &u, const vector3 &v){
    return vector3(u.vec[0]*v.vec[0],u.vec[1]*v.vec[1],u.vec[2]*v.vec[2]);
}

inline vector3 operator*(float t, const vector3 &v){
    return vector3(t*v.vec[0],t*v.vec[1],t*v.vec[2]);
}

inline vector3 operator*(const vector3 &v, float t){
    return t*v;
}

inline vector3 operator/(const vector3 &v, float t){
    return (1/t)*v;
}

inline vector3 unit_vector(vector3 v){
    return v/v.mag();
}

inline float dot(const vector3 &u, const vector3 &v){
    return u.vec[0]*v.vec[0]
            + u.vec[1]*v.vec[1]
            + u.vec[2]*v.vec[2];
}

inline vector3 cross(const vector3 &u, const vector3 &v){
    return vector3(u.vec[1]*v.vec[2] - u.vec[2]*v.vec[1],
                    u.vec[2]*v.vec[0] - u.vec[0]*v.vec[2],
                    u.vec[0]*v.vec[1] - u.vec[1]*v.vec[0]);
}

inline vector3 random_vector3(){
    return vector3(random_float(),random_float(),random_float());
}

inline vector3 random_vector3(float minn,float maxx){
    return vector3(random_float(minn,maxx),random_float(minn,maxx),random_float(minn,maxx));
}

inline vector3 random_in_unit_sphere(){
    while(true){
        auto t = random_vector3(-1,1);
        if(t.mag_squared()>=1) continue;
        return t;
    }
}

inline vector3 random_in_unit_disk(){
    while(true){
        auto t = vector3(random_float(-1,1),random_float(-1,1),0);
        if(t.mag_squared()>=1) continue;
        return t;
    }
}

inline vector3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

vector3 reflect(const vector3& v,const vector3& n){
    //minus because v.n is negetaive
    return v-((2*dot(v,n))*n);
}

vector3 refract(const vector3& v, const vector3& n, float etai_over_etat){
    // refaction formula with derivations here.. https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/reflection_refraction.pdf pg - 15

    auto cos_theta = fminf(dot(-v,n),1.0);
    vector3 r_out_perp = etai_over_etat * (v+cos_theta*n);
    vector3 r_out_parallel = -sqrt(fabsf(1-r_out_perp.mag_squared()))*n;

    return r_out_perp + r_out_parallel;
}
#endif