#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

using namespace std;

class hittable_list: public hittable{
    public:
        vector<shared_ptr<hittable>> objects;
        
        hittable_list(){}
        hittable_list(shared_ptr<hittable> obj){add(obj);}

        void clear(){objects.clear();}
        void add(shared_ptr<hittable> obj){objects.push_back(obj);}

        bool hit(const ray& r, float t_min, float t_max, hit_record& rec)const override;

};

bool hittable_list:: hit(const ray& r, float t_min, float t_max, hit_record& rec)const{
    hit_record temp;
    bool hit_anything = false;
    auto closest = t_max;

    for(const auto& obj:objects){
        if(obj->hit(r,t_min,closest,temp)){
            hit_anything = true;
            closest = temp.t;
            rec=temp;
        }
    }
    return hit_anything;
}

#endif