#include "triangle.h"
#include <math.h>

Hit Triangle::intersect(Ray const &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r
    * Sought: intersects? if true: *t
    *
    * Insert calculation of ray/sphere intersection here.
    *
    * You have the sphere's center (position) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    ****************************************************/

    // Placeholder for actual intersection calculation.
    float D = N.dot(v0);

    float t = - (N.dot(ray.O) + D) / N.dot(ray.D); 
    
    if (t < 0) return Hit::NO_HIT();
    else       return Hit(t, N);
}

Triangle::Triangle(Point const &v0,
                   Point const &v1,
                   Point const &v2)
:
    v0(v0),
    v1(v1),
    v2(v2),
    N()

{
    // Calculate the surface normal here and store it in the N,
    // which is declared in the header. It can then be used in the intersect function.
    Vector A = v1 - v0;
    Vector B = v2 - v0;

    N.x = (A.x * B.z) - (A.z * B.y);
    N.y = (A.z * B.x) - (A.z * B.x);
    N.z = (A.y * B.x) - (A.y * B.x);
}
