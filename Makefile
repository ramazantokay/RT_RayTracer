all:
	g++ *.cpp ext/*.cpp -Wall -o raytracer -lpthread -std=c++11 -O3 -g
clean:
	rm raytracer