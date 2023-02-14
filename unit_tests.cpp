#include <gtest/gtest.h>

#include "camera.hpp"
#include "color.hpp"
#include "point3d.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "triplet.hpp"
#include "vector.hpp"

TEST(TripletTest, EquivalencyTest) {
    Triplet a(1, 2, 3);
    Triplet b(4, 5, 6);
    Triplet c(1, 2, 3);
    Triplet d(1.0, 2.0, 3.0);

    EXPECT_EQ(a, c);
    EXPECT_EQ(a, d);
    EXPECT_NE(a, b);
}

TEST(TripletTest, StreamTest) {
    Triplet a(1, 2, 3);
    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "1 2 3");
}

TEST(TripletTest, GettersTest) {
    Triplet a(1, 2, 3);
    EXPECT_EQ(a.getX(), 1);
    EXPECT_EQ(a.getY(), 2);
    EXPECT_EQ(a.getZ(), 3);
}

TEST(TripletTest, AdditionTest) {
    Triplet a(1, 2, 3);
    Triplet b(4, 5, 6);

    EXPECT_EQ(a + b, Triplet(5, 7, 9));
    EXPECT_EQ(a + 1, Triplet(2, 3, 4));
    EXPECT_EQ(1.0 + a, Triplet(2, 3, 4));

    a++;
    EXPECT_EQ(a, Triplet(2, 3, 4));
    ++a;
    EXPECT_EQ(a, Triplet(3, 4, 5));
}

TEST(TripletTest, SubtractionTest) {
    Triplet a(1, 2, 3);
    Triplet b(4, 5, 6);

    EXPECT_EQ(a - b, Triplet(-3, -3, -3));
    EXPECT_EQ(a - 1, Triplet(0, 1, 2));
    EXPECT_EQ(1.0 - a, Triplet(0, -1, -2));

    a--;
    EXPECT_EQ(a, Triplet(0, 1, 2));
    --a;
    EXPECT_EQ(a, Triplet(-1, 0, 1));
}

TEST(TripletTest, MultiplicationTest) {
    Triplet a(1, 2, 3);

    EXPECT_EQ(a * 2, Triplet(2, 4, 6));
    EXPECT_EQ(2.0 * a, Triplet(2, 4, 6));
}

TEST(TripletTest, DivisionTest) {
    Triplet a(1, 2, 3);

    EXPECT_EQ(a / 2, Triplet(0.5, 1, 1.5));
    EXPECT_EQ(2.0 / a, Triplet(2, 1, 2.0 / 3));
}

TEST(ColorTest, StreamTest) {
    Color a(-5.5, 2.2, 300.3);
    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "0 2 255");
}

TEST(ColorTest, InterpolateColorTest) {
    Color startingColor = Color(255, 255, 255);
    Color endingColor = Color(130, 150, 255);

    EXPECT_EQ(interpolateColor(startingColor, endingColor, 0), Color(255, 255, 255));
    EXPECT_EQ(interpolateColor(startingColor, endingColor, 0.5), Color(192.5, 202.5, 255));
    EXPECT_EQ(interpolateColor(startingColor, endingColor, 1), Color(130, 150, 255));
}

TEST(ColorTest, ColorDivisionTest) {
    Color a = Color(0, 0, 0);
    a += Color(10.9, 10.9, 10.9);
    a /= 2;

    // EXPECT_EQ(a, Color(5.1, 5.1, 5.1));

    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "5 5 5");
}

TEST(VectorTest, LengthTest) {
    Vector a(1, 2, 3);
    EXPECT_EQ(a.length(), sqrt(14));
}

TEST(VectorTest, NormalizeTest) {
    Vector a(1, 2, 3);
    EXPECT_EQ(a.normalize(), Vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
}

TEST(VectorTest, DotProductTest) {
    Vector a(1, 2, 3);
    Vector b(4, 5, 6);
    EXPECT_EQ(dot(a, b), 32);
}

TEST(VectorTest, CrossProductTest) {
    Vector a(1, 2, 3);
    Vector b(4, 5, 6);
    EXPECT_EQ(cross(a, b), Vector(-3, 6, -3));
}

TEST(Point3DTest, PointSubtractionCreatesVector) {
    Point3D a(1, 2, 3);
    Point3D b(4, 5, 6);
    EXPECT_EQ(a - b, Vector(-3, -3, -3));
    EXPECT_EQ(b - a, Vector(3, 3, 3));

    Vector v = a - b;
    EXPECT_EQ(v, Vector(-3, -3, -3));
}

TEST(Point3DTest, InterpolatePointTest) {
    Point3D a(1, 2, 3);
    Point3D b(4, 5, 6);
    EXPECT_EQ(interpolatePoint(a, b, 0), Point3D(1, 2, 3));
    EXPECT_EQ(interpolatePoint(a, b, 0.5), Point3D(2.5, 3.5, 4.5));
    EXPECT_EQ(interpolatePoint(a, b, 1), Point3D(4, 5, 6));

    EXPECT_THROW(interpolatePoint(a, b, 1.5), std::invalid_argument);
}

TEST(Point3DTest, InterpolatePointsTest) {
    Point3D a(1, 2, 3);
    Point3D b(4, 5, 6);
    Point3D c(7, 8, 9);
    Point3D d(10, 11, 12);

    EXPECT_EQ(interpolatePoints(a, b, c, d, 0, 0), Point3D(1, 2, 3));
    EXPECT_EQ(interpolatePoints(a, b, c, d, 0.5, 0.5), Point3D(5.5, 6.5, 7.5));
    EXPECT_EQ(interpolatePoints(a, b, c, d, 1, 1), Point3D(10, 11, 12));
}

TEST(RayTest, GetTest) {
    Ray a(Point3D(1, 2, 3), Vector(4, 5, 6));
    EXPECT_EQ(a.getOrigin(), Point3D(1, 2, 3));
    EXPECT_EQ(a.getDirection(), Vector(4, 5, 6));
}

TEST(RayTest, AtTest) {
    Ray a(Point3D(1, 2, 3), Vector(4, 5, 6));
    EXPECT_EQ(a.at(0), Point3D(1, 2, 3));
    EXPECT_EQ(a.at(1), Point3D(5, 7, 9));
    EXPECT_EQ(a.at(2), Point3D(9, 12, 15));
}

TEST(SphereTest, GetTest) {
    Sphere a(Point3D(1, 2, 3), 4);
    EXPECT_EQ(a.getCenter(), Point3D(1, 2, 3));
    EXPECT_EQ(a.getRadius(), 4);
}

TEST(SphereTest, HitTest) {
    HitRecord hitRecord;
    Sphere a(Point3D(1, 2, 3), 4);
    Ray b(Point3D(0, 0, 0), Vector(1, 1, 1));
    EXPECT_EQ(a.hit(b, hitRecord), true);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}