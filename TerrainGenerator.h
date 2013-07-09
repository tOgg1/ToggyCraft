#pragma once

class TerrainGenerator
{
public:
	TerrainGenerator();
	~TerrainGenerator(void);

	double getHeightValue(int x, int y);

	void seedGenerator(int seed);
	void setFrequency(double frequency);
	void setOctaves(double setOctaves);
	void setAmplitude(double amplitude);

	static const int GENERATOR_GRID_SIZE = 128;

private:
	int seed;
	int gradSize;
	bool locked;

	double frequency;
	double octaves;
	double amplitude;
	
	static int p[];
	static double grad2[][2];

	double getValue(double x, double y);
	double interpolate(double a, double b, double t);
	double fade(double t);
	double dot(double vec1[], double x, double y);
	double noise(int x, int y);
	int fastFloor(double t);
};

