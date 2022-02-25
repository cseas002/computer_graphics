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
    // Vector originToPosition = (position - ray.O).normalized();
    // if (originToPosition.dot(ray.D) < 0.999)
    //     return Hit::NO_HIT();

    Vector temp = ray.O - position; // O-C
    double a = ray.D.dot(ray.D); // D * D     
    double b = 2 * ray.D.dot(ray.O - position); // 2 * (D, temp)
    double c = temp.dot(temp) - (r * r); // temp * temp - r^2

    double discriminant = b * b - 4 * a * c;
    if (discriminant <= 0)
        return Hit::NO_HIT(); 
    // else if (discriminant == 0) {
    //     *t = ray.at((-b + sqrt(discriminant)) / (2 * a));
    //     return 0;
    // }
    else
    {
        double t1, t2;
        double distanceOfHit;
        t1 = (-b + sqrt(discriminant)) / (2 * a);
        t2 = (-b - sqrt(discriminant)) / (2 * a);
        // both must be positive, otherwise it's behind the camera
        distanceOfHit = min(t1, t2);
        return Hit(distanceOfHit, distanceOfHit - ray.O);
    }
        

    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, position, r
    * Sought: N
    *
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}
