#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "light.hpp"
#include "phong_material.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "triplet.hpp"

using namespace std;

void parseCommandLine(int argc, char* argv[], Point3D& at, Point3D& from);

double randomDouble() {
    return static_cast<double>(rand()) / RAND_MAX;
}

double clip(double number, double min, double max) {
    if (number < min) {
        return min;
    } else if (number > max) {
        return max;
    } else {
        return number;
    }
}

int main(int argc, char* argv[]) {
    Point3D cameraLookFrom(0, 0, 1);
    Point3D cameraLookAt(0, 0, 0);

    parseCommandLine(argc, argv, cameraLookAt, cameraLookFrom);

    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    const double ASPECT_RATIO = static_cast<double>(WIDTH) / HEIGHT;

    const int SAMPLES_PER_PIXEL = 1;

    cout << "P3\n";
    cout << WIDTH << " " << HEIGHT << '\n';
    cout << "255\n";

    Camera camera;
    camera.setAspectRatio(ASPECT_RATIO);
    camera.setLookFrom(cameraLookFrom);
    camera.setLookAt(Point3D(0, 0, 0));

    HittableList world;
    world.addLight(Light(Point3D(1, 1, 1), Color(255, 255, 255), 3));

    shared_ptr<PhongMaterial> whiteMaterial = make_shared<PhongMaterial>(Color(255, 255, 255), 0.1, 0.8, 0.3, 4.0);
    shared_ptr<PhongMaterial> redMaterial = make_shared<PhongMaterial>(Color(255, 0, 0), 0.3, 0.6, 0.1, 32.0);
    shared_ptr<PhongMaterial> greenMaterial = make_shared<PhongMaterial>(Color(0, 255, 0), 0.2, 0.7, 0.1, 64.0);
    shared_ptr<PhongMaterial> blueMaterial = make_shared<PhongMaterial>(Color(0, 0, 255), 0.0, 0.9, 0.1, 16.0);

    world.add(make_shared<Sphere>(Point3D(0.45, 0.0, -0.15), 0.15, whiteMaterial));
    world.add(make_shared<Sphere>(Point3D(0.0, 0.0, -0.1), 0.2, redMaterial));
    world.add(make_shared<Sphere>(Point3D(-0.6, 0.0, 0.0), 0.3, greenMaterial));
    world.add(make_shared<Sphere>(Point3D(0.0, -10000.5, 0.0), 10000.0, blueMaterial));

    Color backgroundColor = Color(0.2 * 255, 0.2 * 255, 0.2 * 255);

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
                HitRecord hitRecord;
                if (world.hit(camera.getRay(u, v), hitRecord)) {
                    outputColor += hitRecord.color;
                } else {
                    outputColor += backgroundColor;
                }
            }
            outputColor /= SAMPLES_PER_PIXEL;
            cout << outputColor << '\n';
        }
    }

    return 0;
}

void parseCommandLine(int argc, char* argv[], Point3D& at, Point3D& from) {
    // iterate through the command line arguments
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-at[", 4) == 0 && argv[i][strlen(argv[i]) - 1] == ']') {
            // parse the at point from the argument
            stringstream ss(argv[i] + 4);
            double x, y, z;
            char comma1, comma2;
            ss >> x >> comma1 >> y >> comma2 >> z;
            if (comma1 == ',' && comma2 == ',') {
                at = Point3D(x, y, z);
            } else {
                cerr << "Invalid argument: " << argv[i] << endl;
            }
        } else if (strncmp(argv[i], "-from[", 6) == 0 && argv[i][strlen(argv[i]) - 1] == ']') {
            // parse the from point from the argument
            stringstream ss(argv[i] + 6);
            double x, y, z;
            char comma1, comma2;
            ss >> x >> comma1 >> y >> comma2 >> z;
            if (comma1 == ',' && comma2 == ',') {
                from = Point3D(x, y, z);
            } else {
                cerr << "Invalid argument: " << argv[i] << endl;
            }
        } else {
            cerr << "Invalid argument: " << argv[i] << endl;
        }
    }
}