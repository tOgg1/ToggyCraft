#pragma once
#include <glm\glm.hpp>

class TerrainGenerator
{
public:
	TerrainGenerator();
	~TerrainGenerator(void);

	double getHeightValue(int x, int y);
	void seedGenerator(double seed);

private:
	int seed;
	int gradSize;
	bool locked;
	
	static int p[];
	static double grad2[][2];

	double interpolate(double a, double b, double t);
	double fade(double t);
	double dot(double vec1[], double x, double y);
	int fastFloor(double t);
};

