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
    
    // source: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution

    // Placeholder for actual intersection calculation.
    float normalDotDir = N.dot(ray.D);
    if (abs(normalDotDir) < 0.0001)
        return Hit::NO_HIT();
    float D = -N.dot(v1);
    float t = -(N.dot(ray.O) + D) / normalDotDir;

    if (t < 0)  return Hit::NO_HIT(); // the triangle is behind 
    
    Vector P = ray.O + t * ray.D;
    Vector C;
    
    // edge 0
    Vector edge0 = v1 - v0; 
    Vector vp0 = P - v0; 
    C = edge0.cross(vp0); 
    
    if (N.dot(C) < 0) return Hit::NO_HIT(); // P is on the right side 
    
    // edge 1
    Vector edge1 = v2 - v1; 
    Vector vp1 = P - v1; 
    C = edge1.cross(vp1); 
    if (N.dot(C) < 0)  return Hit::NO_HIT(); // P is on the right side 
 
    // edge 2
    Vector edge2 = v0 - v2; 
    Vector vp2 = P - v2; 
    C = edge2.cross(vp2); 
    if (N.dot(C) < 0) return Hit::NO_HIT(); // P is on the right side; 
 
    return t > 0 ? Hit(t, N) : Hit(t, -N); // this ray hits the triangle 
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
        
    N = A.cross(B);
        
    N.normalize(); // idk if we should do that
}
