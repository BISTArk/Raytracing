#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
public:
    
    point3 origin;
    point3 lower_left_corner;
    vector3 horizontal;
    vector3 vertical;
    vector3 v,u,w;
    float lens_radius;

    camera(point3 lookFrom,point3 lookAt,vector3 vup, float vfov, float aspect_ratio, float aperture, float focus_dist){
        //vfov in degrees vertical_fov
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio*viewport_height;

        //Distance between secne and camera
        auto focal_length = 1.0; 

        w = unit_vector(lookAt - lookFrom);
        u = unit_vector(cross(w,vup));
        v = cross(u,w);

        origin = lookFrom;
        horizontal = focus_dist*viewport_width*u;
        vertical = focus_dist*viewport_height*v;
        lower_left_corner = origin+(focus_dist*w)-horizontal/2-vertical/2;

        lens_radius = aperture/2;
    }

    ray get_ray(float s,float t) const {
        vector3 rd = lens_radius*random_in_unit_disk();
        vector3 offset = u * rd.x() + v* rd.y();

        return ray(origin+offset,lower_left_corner+s*vertical+t*horizontal-origin-offset);
    }
};

#endif