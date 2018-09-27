CC=g++
CFLAGS=-std=c++11
TEST_FILES=tests-RGBColor.cpp tests-PPMImage.cpp
IMP_FILES=../RGBColor.cpp ../PPMImage.cpp

tests: tests-main.o tests-RGBColor.cpp tests-PPMImage.cpp ../RGBColor.cpp ../PPMImage.cpp
	$(CC) $(CFLAGS) -o tests tests-main.o $(TEST_FILES) $(IMP_FILES)

tests-main.o: tests-main.cpp
	$(CC) $(CFLAGS) -c tests-main.cpp

 
