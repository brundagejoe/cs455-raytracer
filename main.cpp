#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

#include "camera.hpp"
#include "color.hpp"
#include "dielectric.hpp"
#include "hit_record.hpp"
#include "hittable_list.hpp"
#include "ray.hpp"
#include "scenes.hpp"
#include "triplet.hpp"
#include "utilities.hpp"

Color phongRayColor(const Ray& ray, const HittableList& world, int depth) {
    Vector directionToLight = world.getDirectionalLightDirection();
    Color directionLightColor = world.getDirectionalLightColor();
    Color ambientLightColor = world.getAmbientLightColor();

    if (depth <= 0) {
        return Color(0, 0, 0);
    }
    Color backgroundColor = Color(0.2, 0.2, 0.2);
    HitRecord hitRecord;
    if (world.hit(ray, hitRecord)) {
        Color returnColor;
        std::shared_ptr<PhongMaterial> phongMaterial = std::dynamic_pointer_cast<PhongMaterial>(hitRecord.material);

        Color ambientColor = phongMaterial->getColor() * phongMaterial->getAmbientCoefficient() * ambientLightColor;

        Color diffuseColor = phongMaterial->getColor() * phongMaterial->getDiffuseCoefficient() * std::max(0.0, dot(hitRecord.normal, directionToLight)) * directionLightColor;

        Vector reflectRayDirection = reflect(ray.getDirection(), hitRecord.normal);
        Color specularColor = phongMaterial->getSpecularColor() * phongMaterial->getSpecularCoefficient() * pow(std::max(0.0, dot(reflectRayDirection, directionToLight)), phongMaterial->getShininess()) * directionLightColor;
        Color reflectionColor = Color(0, 0, 0);

        Ray shadowRay = Ray(hitRecord.point, directionToLight);
        HitRecord shadowHitRecord;
        if (world.hit(shadowRay, shadowHitRecord)) {
            diffuseColor *= 0;
            specularColor *= 0;
        }

        Ray reflectRay(hitRecord.point, reflectRayDirection);
        reflectionColor = phongRayColor(reflectRay, world, depth - 1) * phongMaterial->getReflectance();

        returnColor = ambientColor + diffuseColor + specularColor + reflectionColor;

        return returnColor;
    }
    return backgroundColor;
}

Color rayColor(const Ray& ray, const HittableList& world, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0);
    }
    HitRecord hitRecord;
    if (world.hit(ray, hitRecord)) {
        Ray scatteredRay;
        Color attenuation;

        if (hitRecord.material->scatter(ray, hitRecord, attenuation, scatteredRay)) {
            return hitRecord.material->emission() + attenuation * rayColor(scatteredRay, world, depth - 1);
        }
        return hitRecord.material->emission();
    }
    return world.getAmbientLightColor();
}

int main() {
    srand(0);

    int WIDTH = 500;
    int HEIGHT = 500;

    int SAMPLES_PER_PIXEL;
    int MAX_DEPTH;
    bool USE_PHONG;

    HittableList world;

    switch (0) {
        case 1:
            world = scene1();
            SAMPLES_PER_PIXEL = 100;
            MAX_DEPTH = 50;
            USE_PHONG = true;
            break;
        case 2:
            world = scene2();
            SAMPLES_PER_PIXEL = 100;
            MAX_DEPTH = 50;
            USE_PHONG = true;
            break;
        case 3:
            // Takes about 10 minutes to render
            world = cornellBox();
            SAMPLES_PER_PIXEL = 1000;
            MAX_DEPTH = 100;
            USE_PHONG = false;
            break;
        case 4:
            world = phongCornellBox();
            SAMPLES_PER_PIXEL = 10;
            MAX_DEPTH = 5;
            USE_PHONG = true;
            break;
        default:
            world = scene1();
            SAMPLES_PER_PIXEL = 100;
            MAX_DEPTH = 50;
            USE_PHONG = true;
            break;
    }

    Camera camera;

    Point3D cameraLookFrom(0, 0, 1);
    Point3D cameraLookAt(0, 0, 0);

    const double ASPECT_RATIO = static_cast<double>(WIDTH) / HEIGHT;
    camera.setAspectRatio(ASPECT_RATIO);
    camera.setLookFrom(cameraLookFrom);
    camera.setLookAt(cameraLookAt);

    std::cout << "P3\n";
    std::cout << WIDTH << " " << HEIGHT << '\n';
    std::cout << "255\n";

    std::cerr << "Rendering...\n";

    for (int j = HEIGHT - 1; j >= 0; --j) {
        for (int i = 0; i < WIDTH; ++i) {
            double u = static_cast<double>(i) / (WIDTH - 1);
            double v = static_cast<double>(j) / (HEIGHT - 1);

            Color outputColor = Color(0, 0, 0);
            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
                if (SAMPLES_PER_PIXEL > 1) {
                    u = clip((i + randomDouble()) / (WIDTH - 1), 0.0, 1.0);
                    v = clip((j + randomDouble()) / (HEIGHT - 1), 0.0, 1.0);
                }
                USE_PHONG ? outputColor += phongRayColor(camera.getRay(u, v), world, MAX_DEPTH)
                          : outputColor += rayColor(camera.getRay(u, v), world, MAX_DEPTH);
            }

            outputColor *= 255;
            if (USE_PHONG) {
                outputColor /= SAMPLES_PER_PIXEL;
            } else {
                // gamma 2 correction (sqrt)
                outputColor = sqrt(outputColor * (256.0 / SAMPLES_PER_PIXEL));
            }
            std::cout << outputColor << '\n';
        }
        std::cerr << "\rScanlines remaining: " << j << ' ';
    }

    std::cerr << "\nDone.\n";

    return 0;
}
