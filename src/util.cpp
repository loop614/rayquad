#include "util.hpp"
#include <math.h>

Vector2 tiltVec2ByDeg(Vector2 vec, Angle angle) {
    float pi180 = PI / 180;
    return Vector2 {
        vec.x*cos(angle.val * pi180) - vec.y*sin(angle.val * pi180),
        vec.x*sin(angle.val * pi180) + vec.y*cos(angle.val * pi180)
    };
}
