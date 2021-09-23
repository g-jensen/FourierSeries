#include "Math.h"

float Math::Length(FourierVector v)
{
    return sqrt(
        (v.x * v.x) + (v.y * v.y)
    );
}

float Math::Length(FourierVector v1, FourierVector v2) {
    float xDiff = v1.x - v2.x;
    float yDiff = v1.y - v2.y;
    return sqrt(
        (xDiff * xDiff) + (yDiff * yDiff)
    );
}

FourierVector Math::rotate(FourierVector vec, float angle_deg)
{
    std::cout << vec.length << std::endl;
    vec.angle_deg += angle_deg;
    vec.x = cosf(vec.angle_deg * 180. / M_PI) * vec.length;
    vec.y = sinf(vec.angle_deg * 180. / M_PI) * vec.length;
    return vec;
}
