#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vector3.h"

class sphere: public hittable{
    public:
        point3 center;
        float radius;
        shared_ptr<material> mat_ptr;

        sphere(){}
        sphere(point3 cen, float r,shared_ptr<material> m): center(cen),radius(r),mat_ptr(m){};

        bool hit(const ray& r,float t_min, float t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec)const {
    vector3 dis = r.origin()-center;

    auto a = r.direction().mag_squared();
    // auto b = 2.0*dot(dis,r.direction());
    auto half_b = dot(dis,r.direction());
    auto c = dis.mag_squared()-(radius*radius);

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    //find roots and check if they are valid

    auto root = (-half_b-sqrtd)/a;
    if(root<t_min || root > t_max){
        root = (-half_b+sqrtd)/a;
        if(root<t_min || root > t_max){
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vector3 outward_normal = (rec.p-center)/radius;
    // std::cerr<<root<<endl;
    rec.set_face_normal(r,outward_normal);
    rec.mat_ptr=mat_ptr;

    return true;
    
}

#endif