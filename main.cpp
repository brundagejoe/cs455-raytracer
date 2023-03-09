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

Color whittedAlgorithmRayColor(const Ray& ray, const HittableList& world, int depth) {
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
        if (std::dynamic_pointer_cast<PhongMaterial>(hitRecord.material) == nullptr) {
            phongMaterial = std::make_shared<PhongMaterial>(hitRecord.material->getColor());
        }

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
        reflectionColor = whittedAlgorithmRayColor(reflectRay, world, depth - 1) * phongMaterial->getReflectance();

        returnColor = ambientColor + diffuseColor + specularColor + reflectionColor;

        return returnColor;
    }
    return backgroundColor;
}

Color brutePathTracingAlgorithmRayColor(const Ray& ray, const HittableList& world, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0);
    }
    HitRecord hitRecord;
    if (world.hit(ray, hitRecord)) {
        Ray scatteredRay;
        Color attenuation;

        if (hitRecord.material->scatter(ray, hitRecord, attenuation, scatteredRay)) {
            return hitRecord.material->emission() + attenuation * brutePathTracingAlgorithmRayColor(scatteredRay, world, depth - 1);
        }
        return hitRecord.material->emission();
    }
    return world.getAmbientLightColor();
}

int main() {
    srand(time(NULL));

    time_t start = time(0);

    int WIDTH = 500;
    int HEIGHT = 500;

    int SAMPLES_PER_PIXEL;
    int MAX_DEPTH;
    bool USE_WHITTED;

    HittableList world;

    Camera camera;
    Point3D cameraLookFrom(0, 0, 1);
    Point3D cameraLookAt(0, 0, 0);

    switch (1) {
        case 1:
            world = proj6Scene1();
            SAMPLES_PER_PIXEL = 100;
            MAX_DEPTH = 50;
            USE_WHITTED = true;
            break;
        case 2:
            world = proj6Scene2();
            SAMPLES_PER_PIXEL = 100;
            MAX_DEPTH = 50;
            USE_WHITTED = true;
            break;
        case 3:
            // Takes about 10 minutes to render
            world = proj6Scene3();
            SAMPLES_PER_PIXEL = 1000;
            MAX_DEPTH = 100;
            USE_WHITTED = false;
            break;
        case 4:
            world = cornellMetalBalls();
            SAMPLES_PER_PIXEL = 10;
            MAX_DEPTH = 50;
            USE_WHITTED = false;
            cameraLookFrom = Point3D(278, 273, 800);
            cameraLookAt = Point3D(Vector(cameraLookFrom) - Vector(0, 0, 1));
            camera.setVFov(35);
            break;
        case 5:
            world = simpleSpheresForFocusTesting();
            SAMPLES_PER_PIXEL = 200;
            MAX_DEPTH = 50;
            USE_WHITTED = false;
            cameraLookFrom = Point3D(0.5, -0.3, 0.6);
            cameraLookAt = Point3D(0, -.8, 0);
            camera.setAperature(0.2);
            break;
        default:
            world = proj6Scene1();
            SAMPLES_PER_PIXEL = 100;
            MAX_DEPTH = 50;
            USE_WHITTED = true;
            break;
    }

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
                USE_WHITTED ? outputColor += whittedAlgorithmRayColor(camera.getRay(u, v), world, MAX_DEPTH)
                            : outputColor += brutePathTracingAlgorithmRayColor(camera.getRay(u, v), world, MAX_DEPTH);
            }

            outputColor *= 255;
            if (USE_WHITTED) {
                outputColor /= SAMPLES_PER_PIXEL;
            } else {
                // gamma 2 correction (sqrt)
                outputColor = sqrt(outputColor * (256.0 / SAMPLES_PER_PIXEL));
            }
            std::cout << outputColor << '\n';
        }
        std::cerr << "\rScanlines remaining: " << j << ' ';
    }

    time_t end = time(0);

    std::cerr << "\nDone. Time elapsed: " << getTimeInMinutes(start, end) << '\n';

    return 0;
}