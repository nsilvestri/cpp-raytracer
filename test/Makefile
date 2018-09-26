CC=g++
CFLAGS=-std=c++11
TEST_FILES=tests-RGBPixel.cpp tests-PPMImage.cpp
IMP_FILES=../RGBPixel.cpp ../PPMImage.cpp

tests: tests-main.o tests-RGBPixel.cpp ../RGBPixel.cpp
	$(CC) $(CFLAGS) -o tests tests-main.o $(TEST_FILES) $(IMP_FILES)

tests-main.o: tests-main.cpp
	$(CC) $(CFLAGS) -c tests-main.cpp

 
