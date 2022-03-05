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

    if (ray.O.distance(position) <= r) // if the ray source is inside the sphere
        return Hit::NO_HIT();
        


    float t=0.0, t1 = 0, t2 = 0;

    Triple oc =  ray.O - position;
    float a = ray.D.dot(ray.D);
    float b = 2.0 * oc.dot(ray.D);
    float c = oc.dot(oc) - r*r;
    float discriminant = (b*b - 4*a*c);

    if (discriminant < 0)
        return Hit::NO_HIT();
    // else if (discriminant == 0)
    //     t = (-b) / (2 * a);
    else {
        t1 = (-b + sqrt(discriminant)) / (2 * a);
        t2 = (-b - sqrt(discriminant)) / (2 * a);
        if (t1 < t2) // find the smallest distance between ray source and hit points
            t = t1;
        else   
            t = t2;
    }
    if (t < 0)
        return Hit::NO_HIT();

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
