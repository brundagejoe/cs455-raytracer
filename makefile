make:
	g++ -std=c++17 -Wall -Wextra -Wpedantic -O3 -o raytracer/raytracer main.cpp color.cpp point3d.cpp triplet.cpp
test:
	cd build && make
	./build/unit_tests
image:
	make && ./raytracer/raytracer > raytracer/image.ppm && open raytracer/image.ppm