#ifndef COLOR_H
#define COLOR_H

#include "vector3.h"
#include <iostream>

using namespace std;

void write_color(ostream &out, color col, int samples)
{

    auto r = col.x();
    auto g = col.y();
    auto b = col.z();

    auto scale = 1.0 / samples;
    r = sqrt(r * scale);
    g = sqrt(g * scale);
    b = sqrt(b * scale);

    out << static_cast<int>(256 * clamp(r, 0, 1)) << ' '
        << static_cast<int>(256 * clamp(g, 0, 1)) << ' '
        << static_cast<int>(256 * clamp(b, 0, 1)) << endl;
}

#endif