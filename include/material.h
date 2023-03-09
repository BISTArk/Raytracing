#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"
// #include "hittable.h"

struct hit_record;

class material{
    public:
        virtual bool scatter(const ray& r_in,const hit_record& rec,color& attenuation,ray& scattered) const =0;  
};

class lambertian: public material{
    
    public:
        color albedo;

        lambertian(const color& col):albedo(col){}

        bool scatter(const ray& r_in,const hit_record& rec,color& attenuation,ray& scattered)const override{
            auto scatter_dir = rec.normal + random_unit_vector();
            if(scatter_dir.near_zero())scatter_dir = rec.normal;
            scattered = ray(rec.p, scatter_dir);
            attenuation = albedo;
            return true;
        }
};

class metal :public material{
    public:
        color albedo;
        float fuzz;

        metal(const color& col,float f) :albedo(col),fuzz(f<1?f:1){}

        bool scatter(const ray& r_in,const hit_record& rec,color& attenuation,ray& scattered)const override{
            vector3 unit_dir = unit_vector(r_in.direction());
            auto reflect_dir = reflect(unit_dir,rec.normal);
            // you can use the random_unit_vector as well but using random_in_unit_sphere gives more soft image due to down scaling
            scattered = ray(rec.p,reflect_dir + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return dot(scattered.direction(),rec.normal) > 0;
        }
};

class dielectric: public material{
    public:
        float ir;

        dielectric(float index_of_refraction):ir(index_of_refraction){}

        bool scatter(const ray& r_in,const hit_record& rec,color& attenuation,ray& scattered)const override{
            attenuation = color(1.0,1.0,1.0);
            float refraction_ratio = rec.front_face? (1.0/ir):ir;

            vector3 unit_dir = unit_vector(r_in.direction());
            auto cos_theta = fminf(dot(-unit_dir,rec.normal),1.0);
            auto sin_theta = sqrt(1.0-cos_theta*cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta >1;
            vector3 direction;

            if(cannot_refract && reflactance(cos_theta,refraction_ratio) > random_float()) direction = reflect(unit_dir,rec.normal);
            else direction = refract(unit_dir,rec.normal,refraction_ratio);
            
            scattered = ray(rec.p,direction);
            return true;
                
        }

        private:
            static float reflactance(float cosine,double ref_idx){
                auto r0 = (1-ref_idx)/(1+ref_idx);
                r0 = r0*r0;
                return r0 + (1-r0)*pow((1-cosine),5);
            }
};

#endif