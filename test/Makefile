CC=g++
CFLAGS=-std=c++11
O_FILES=tests-main.o tests-RGBColor.o tests-PPMImage.o tests-Vector3D.o tests-Scene.o tests-Sphere.o tests-Ray3D.o
CPP_FILES=../RGBColor.cpp ../PPMImage.cpp ../Vector3D.cpp ../Ray3D.cpp ../Scene.cpp ../Camera.cpp ../Light.cpp ../Sphere.cpp ../Plane.cpp ../Surface.cpp ../easylogging++.cc

tests: $(O_FILES) $(CPP_FILES)
	$(CC) $(CFLAGS) -o tests $(O_FILES) $(CPP_FILES)

tests-main.o: tests-main.cpp
	$(CC) $(CFLAGS) -c tests-main.cpp

tests-RGBColor.o: tests-RGBColor.cpp
	$(CC) $(CFLAGS) -c tests-RGBColor.cpp

tests-PPMImage.o: tests-PPMImage.cpp
	$(CC) $(CFLAGS) -c tests-PPMImage.cpp

tests-Vector3D.o: tests-Vector3D.cpp
	$(CC) $(CFLAGS) -c tests-Vector3D.cpp

tests-Scene.o: tests-Scene.cpp
	$(CC) $(CFLAGS) -c tests-Scene.cpp

tests-Sphere.o: tests-Sphere.cpp
	$(CC) $(CFLAGS) -c tests-Sphere.cpp

tests-Ray3D.o: tests-Ray3D.cpp
	$(CC) $(CFLAGS) -c tests-Ray3D.cpp



