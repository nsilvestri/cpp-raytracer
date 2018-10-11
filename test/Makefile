CC=g++
CFLAGS=-std=c++11
O_FILES=tests-main.o tests-RGBColor.o tests-PPMImage.o tests-Vector3D.o tests-Scene.o
CPP_FILES=../RGBColor.cpp ../PPMImage.cpp ../Vector3D.cpp ../Scene.cpp ../Camera.cpp

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


