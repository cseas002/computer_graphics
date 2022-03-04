#include "sphere.h"

#include <cmath>


using namespace std;

Hit Sphere::intersect(Ray const &ray)
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

    float t=0.0;

    Triple oc =  ray.O - position;
    float a = ray.D.dot(ray.D);
    float b = 2.0 * oc.dot(ray.D);
    float c = oc.dot(oc) - r*r;
    float discriminant = (b*b - 4*a*c);

    if (discriminant >= 0.0 && a > 0.0){
        t = a/(2.0*a);
    }else if (discriminant >= 0.0 && b > 0.0){
        t = b/(2.0*a);
    }else return Hit::NO_HIT();

    // Vector originToPosition = (position - ray.O).normalized();
    // if (originToPosition.dot(ray.D) < 0.999)
    //     return Hit::NO_HIT();

    // double t = 1000;

    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, position, r
    * Sought: N
    *
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/

    Vector point = ray.O + ray.D * t;
    Vector N = Vector(point - position);
    N.normalize();
      
    if ((N.dot(-ray.D) > 0.0)) return Hit(t, N);
    else return Hit(t, -N);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}
