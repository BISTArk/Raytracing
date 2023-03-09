#include "common.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

hittable_list random_world(){
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5,0.5,0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0),1000,ground_material));

    for(int i=-11;i<11;i++){
        for(int j=-11;j<11;j++){
            auto choose_mat = random_float();
            auto radius = 0.2;
            // auto radius = random_float(0.1,0.3);
            point3 center(i+random_float(),radius,j*random_float());

            if((center-point3(4,radius,0)).mag()>0.9){

                shared_ptr<material> sphere_mat;
                if(choose_mat>0.95){
                    // dielectric / glass material
                    sphere_mat = make_shared<dielectric>(1.5);
                }else if(choose_mat>0.8){
                    // Metal material
                    auto albedo = random_vector3(0.5,1);
                    auto fuzz = random_float(0,0.5);
                    sphere_mat = make_shared<metal>(albedo,fuzz);
                }else{
                    // Diffuse material
                    auto col = random_vector3(0,1);
                    sphere_mat = make_shared<lambertian>(col);
                }
                world.add(make_shared<sphere>(center,radius,sphere_mat));
            }
            
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

color ray_color(const ray& r,const hittable_list& world, int depth){

    if(depth<0)return color(0,0,0);

    hit_record rec;
    if(world.hit(r,0.0001,infinity,rec)){
        ray scattered;
        color attenutaion;
        if(rec.mat_ptr->scatter(r,rec,attenutaion,scattered)) return attenutaion * ray_color(scattered,world,depth-1);
        return color(0,0,0);
    }
    //Background
    vector3 unit_dir = unit_vector(r.direction());
    auto t = 0.5*(unit_dir.y() + 1.0);
    return (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

int main(){

    //Image
    const auto aspect_ratio = 3.0/2.0;
    const int img_width = 1200;
    const int img_height = static_cast<int>(img_width/aspect_ratio);
    const int samples = 500;
    const int depth = 50;

    //World
    hittable_list world = random_world();

    //Camera
    point3 lookFrom(13,2,3);
    point3 lookAt(0,0,0);
    vector3 vup(0,1,0);
    auto aperture = 0.1; // Lesser the aperture lesser the blur
    auto dist_to_focus = 10.0;

    camera cam(lookFrom, lookAt, vup ,20.0,aspect_ratio,aperture,dist_to_focus );

    //Renderer
    cout<< "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for(int i=img_height;i>=0;i--){
        cerr << "\rScanlines remaining: " << i << ' ' << flush;
        for(int j=0;j<img_width;j++){
            color pixel_col(0,0,0);
            for(int s=0;s<samples;s++){
                auto u = float(i+random_float())/img_height;
                auto v = float(j+random_float())/img_width;

                ray r = cam.get_ray(u,v);
                pixel_col += ray_color(r,world,depth);
            }            
            write_color(cout,pixel_col,samples);
        }
    }
    std::cerr << "\nDone.\n";
}