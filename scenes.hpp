#ifndef SCENES_HPP
#define SCENES_HPP

#include "box.hpp"
#include "dielectric.hpp"
#include "emission.hpp"
#include "hit_record.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "phong_material.hpp"
#include "quadrilateral.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

using std::make_shared;

HittableList scene1() {
    HittableList world;
    world.add(make_shared<Sphere>(Point3D(0, 0.3, -1), 0.25, make_shared<PhongMaterial>(0, 0.1, 0.1, Color(0.75, 0.75, 0.75), Color(1, 1, 1), 10, .9)));
    world.add(make_shared<Triangle>(
        Point3D(0, -0.7, -0.5),
        Point3D(1, 0.4, -1),
        Point3D(0, -0.7, -1.5),
        make_shared<PhongMaterial>(0.9, 1, 0.1, Color(0, 0, 1), Color(1, 1, 1), 4, 0)));
    world.add(make_shared<Triangle>(
        Point3D(0, -0.7, -0.5),
        Point3D(0, -0.7, -1.5),
        Point3D(-1, 0.4, -1.0),
        make_shared<PhongMaterial>(0.9, 1, 0.1, Color(1, 1, 0), Color(1, 1, 1), 4, 0)));
    world.addAmbientLight(Color(0.2, 0.2, 0.2));
    world.addDirectionalLight(Color(1, 1, 1), Vector(0, 1, 0));

    return world;
}

HittableList scene2() {
    HittableList world;
    world.add(make_shared<Sphere>(Point3D(0.5, 0, -0.15), 0.05, make_shared<PhongMaterial>(0.8, 0.1, 0.3, Color(1, 1, 1), Color(1, 1, 1), 4, 0)));
    world.add(make_shared<Sphere>(Point3D(0.3, 0, -0.1), 0.08, make_shared<PhongMaterial>(0.8, 0.8, 0.1, Color(1, 0, 0), Color(0.5, 1, 0.5), 32, 0)));
    world.add(make_shared<Sphere>(Point3D(-0.6, 0, 0), 0.3, make_shared<PhongMaterial>(0.7, 0.5, 0.1, Color(0, 1, 0), Color(0.5, 1, 0.5), 64, 0)));
    world.add(make_shared<Sphere>(Point3D(-0.6, 0, 0), 0.3, make_shared<PhongMaterial>(0.7, 0.5, 0.1, Color(0, 1, 0), Color(0.5, 1, 0.5), 64, 0)));
    world.add(make_shared<Sphere>(Point3D(0.1, -0.55, 0.25), 0.3, make_shared<PhongMaterial>(0, 0.1, 0.1, Color(0.75, 0.75, 0.75), Color(1, 1, 1), 10, 0.9)));
    world.add(make_shared<Triangle>(
        Point3D(0.3, -0.3, -0.4),
        Point3D(0, 0.3, -0.1),
        Point3D(-0.3, -0.3, 0.2),
        make_shared<PhongMaterial>(0.9, 0.9, 0.1, Color(0, 0, 1), Color(1, 1, 1), 32, 0)));
    world.add(make_shared<Triangle>(
        Point3D(-0.2, 0.1, 0.1),
        Point3D(-0.2, -0.5, 0.2),
        Point3D(-0.2, 0.1, -0.3),
        make_shared<PhongMaterial>(0.9, 0.5, 0.1, Color(1, 1, 0), Color(1, 1, 1), 4, 0)));
    world.addAmbientLight(Color(0.2, 0.2, 0.2));
    world.addDirectionalLight(Color(1, 1, 1), Vector(1, 0, 0));
    return world;
}

HittableList cornellBox() {
    HittableList world;
    Point3D lowerLeftFront(-1, -1, 0);
    Point3D lowerLeftBack(-1, -1, -2);
    Point3D upperLeftFront(-1, 0.75, 0);
    Point3D upperLeftBack(-1, 0.75, -2);
    Point3D lowerRightFront(1, -1, 0);
    Point3D lowerRightBack(1, -1, -2);
    Point3D upperRightFront(1, 0.75, 0);
    Point3D upperRightBack(1, 0.75, -2);

    Point3D lightLeftFront(-0.3, 0.74, -0.6);
    Point3D lightLeftBack(-0.3, 0.74, -1.2);
    Point3D lightRightFront(0.3, 0.74, -0.6);
    Point3D lightRightBack(0.3, 0.74, -1.2);

    auto red = make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
    auto white = make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
    auto green = make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
    auto light = make_shared<Emission>(Color(10, 10, 10));
    auto metal = make_shared<Metal>(Color(0.8, 0.8, 0.9), 0.1);
    auto glass = make_shared<Dielectric>(1.5);

    world.add(make_shared<Quadrilateral>(lowerLeftBack, upperLeftBack, upperLeftFront, lowerLeftFront, red));
    world.add(make_shared<Quadrilateral>(lowerRightBack, upperRightBack, upperLeftBack, lowerLeftBack, white));
    world.add(make_shared<Quadrilateral>(lowerRightFront, upperRightFront, upperRightBack, lowerRightBack, green));
    world.add(make_shared<Quadrilateral>(lowerRightFront, lowerRightBack, lowerLeftBack, lowerLeftFront, white));
    world.add(make_shared<Quadrilateral>(upperLeftFront, upperLeftBack, upperRightBack, upperRightFront, white));
    world.add(make_shared<Quadrilateral>(lightLeftFront, lightLeftBack, lightRightBack, lightRightFront, light));

    world.add(make_shared<Box>(Point3D(-.7, -1, -1.8), 0.5, 0.9, 0.4, 0, 0, 0, metal));
    world.add(make_shared<Sphere>(Point3D(-0.1, -0.75, -0.9), 0.25, white));
    world.add(make_shared<Sphere>(Point3D(0.45, -0.65, -1.3), 0.35, glass));

    world.addAmbientLight(Color(0, 0, 0));

    return world;
}

HittableList phongCornellBox() {
    HittableList world;
    Point3D lowerLeftFront(-1, -1, 0);
    Point3D lowerLeftBack(-1, -1, -2);
    Point3D upperLeftFront(-1, 0.75, 0);
    Point3D upperLeftBack(-1, 0.75, -2);
    Point3D lowerRightFront(1, -1, 0);
    Point3D lowerRightBack(1, -1, -2);
    Point3D upperRightFront(1, 0.75, 0);
    Point3D upperRightBack(1, 0.75, -2);

    auto red = make_shared<PhongMaterial>(Color(0.65, 0.05, 0.05));
    auto white = make_shared<PhongMaterial>(Color(0.73, 0.73, 0.73));
    auto green = make_shared<PhongMaterial>(Color(0.12, 0.45, 0.15));
    auto metal = make_shared<PhongMaterial>(0, 0.1, 0.1, Color(0.75, 0.75, 0.75), Color(1, 1, 1), 10, 0.9);

    world.add(make_shared<Quadrilateral>(lowerLeftBack, upperLeftBack, upperLeftFront, lowerLeftFront, red));
    world.add(make_shared<Quadrilateral>(lowerRightBack, upperRightBack, upperLeftBack, lowerLeftBack, white));
    world.add(make_shared<Quadrilateral>(lowerRightFront, upperRightFront, upperRightBack, lowerRightBack, green));
    world.add(make_shared<Quadrilateral>(lowerRightFront, lowerRightBack, lowerLeftBack, lowerLeftFront, white));
    world.add(make_shared<Quadrilateral>(upperLeftFront, upperLeftBack, upperRightBack, upperRightFront, white));

    world.add(make_shared<Box>(Point3D(-.7, -1, -1.8), 0.5, 0.9, 0.4, 0, 0, 0, metal));
    world.add(make_shared<Sphere>(Point3D(-0.1, -0.75, -0.9), 0.25, white));
    world.add(make_shared<Sphere>(Point3D(0.45, -0.65, -1.3), 0.35, white));

    world.addAmbientLight(Color(2, 2, 2));
    world.addDirectionalLight(Color(1, 1, 1), Vector(.3, .3, 1));

    return world;
}

#endif  // !SCENES_HPP