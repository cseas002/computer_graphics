#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

pair<ObjectPtr, Hit> Scene::castRay(Ray const &ray) const
{
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }

    return pair<ObjectPtr, Hit>(obj, min_hit);
}

Color Scene::trace(Ray const &ray, unsigned depth)
{
    pair<ObjectPtr, Hit> mainhit = castRay(ray);
    ObjectPtr obj = mainhit.first;
    Hit min_hit = mainhit.second;

    // No hit? Return background color.
    if (!obj)
        return Color(0.0, 0.0, 0.0);

    Material const &material = obj->material;
    Point hit = ray.at(min_hit.t);
    Vector V = -ray.D;

    // Pre-condition: For closed objects, N points outwards.
    Vector N = min_hit.N;

    // The shading normal always points in the direction of the view,
    // as required by the Phong illumination model.
    Vector shadingN;
    if (N.dot(V) >= 0.0)
        shadingN = N;
    else
        shadingN = -N;

    Color matColor = material.color;
    if (material.hasTexture){
        Vector uv = obj->toUV(hit);
        double u = uv.x;
        double v = uv.y;
        matColor = material.texture.colorAt(u, 1 - v);
    }
        

    // Add ambient once, regardless of the number of lights.
    Color color = material.ka * matColor;

    // Add diffuse and specular components.
    for (LightPtr light : lights)
    {
        Vector L = (light->position - hit).normalized();

        if (renderShadows)
        {
            std::pair<ObjectPtr, Hit> res = castRay(Ray(hit + L * epsilon, L));
            if (res.first != nullptr)
            {
                continue;
            }
        }

        // Add diffuse.
        double dotNormal = shadingN.dot(L);
        double diffuse = std::max(dotNormal, 0.0);
        color += diffuse * material.kd * light->color * matColor;

        // Add specular.
        if (dotNormal > 0)
        {
            Vector reflectDir = reflect(-L, shadingN); // Note: reflect(..) is not given in the framework.
            double specAngle = std::max(reflectDir.dot(V), 0.0);
            double specular = std::pow(specAngle, material.n);

            color += specular * material.ks * light->color;
        }
    }

    if (depth > 0)
    {
        Vector reflectDir = reflect(ray.D, shadingN);
        Color reflectedColor = trace(Ray(hit + reflectDir * epsilon, reflectDir), depth - 1);
        if (material.isTransparent)
        {
            double ni = 1;
            double nt = material.nt;
            // printf("swap=%d depth=%d\n", N.dot(V) >= 0.0, depth);

            if (N.dot(V) <= 0.0)
                std::swap(ni, nt);

            double kr0 = pow((ni - nt) / (ni + nt), 2);
            double cos = -ray.D.normalized().dot(shadingN.normalized());
            double kr = kr0 + (ni - kr0) * pow((ni - cos), 5);
            color += reflectedColor * kr;

            Vector T = (ni * (ray.D - ray.D.dot(shadingN) * shadingN)) / nt -
                       shadingN * sqrt(1 - ni * ni * (1 - pow(ray.D.dot(shadingN), 2)) / pow(nt, 2));
            Color refractedColor = trace(Ray(hit + T * epsilon, T), depth - 1);
            color += refractedColor * (1 - kr);
        }
        else if (material.ks > 0.0)
        {
            color += reflectedColor * material.ks;
        }
    }

    return color;
}

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();

    double ss0 = (double) (supersamplingFactor);

    for (unsigned y = 0; y < h; ++y)
        for (unsigned x = 0; x < w; ++x)
        {
            Color avgColor;
            for (int i = 0; i < supersamplingFactor; i++) 
                for (int j = 0; j < supersamplingFactor; j++) {
                    Point pixel;
                    pixel = Point(x + i/ss0 + 1/(ss0*2), h - y - j/ss0 - 1/(ss0*2));
                     
                    Ray ray(eye, (pixel - eye).normalized());
                    Color col = trace(ray, recursionDepth);
                    avgColor += col;
            }
            avgColor /= (pow(ss0, 2));
            avgColor.clamp();
            img(x, y) = avgColor;
        }
}

// --- Misc functions ----------------------------------------------------------

// Defaults
Scene::Scene()
    : objects(),
      lights(),
      eye(),
      renderShadows(true),
      recursionDepth(0),
      supersamplingFactor(1)
{
}

void Scene::addObject(ObjectPtr obj)
{
    objects.push_back(obj);
}

void Scene::addLight(Light const &light)
{
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position)
{
    eye = position;
}

unsigned Scene::getNumObject()
{
    return objects.size();
}

unsigned Scene::getNumLights()
{
    return lights.size();
}

void Scene::setRenderShadows(bool shadows)
{
    renderShadows = shadows;
}

void Scene::setRecursionDepth(unsigned depth)
{
    recursionDepth = depth;
}

void Scene::setSuperSample(unsigned factor)
{
    supersamplingFactor = factor;
}
