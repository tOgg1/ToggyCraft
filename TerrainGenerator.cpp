#include "TerrainGenerator.h"
#include <algorithm>

// Permutation table
int TerrainGenerator::p[] = {151,160,137,91,90,15,
 131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
 190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
 88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
 77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
 102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
 135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
 5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
 223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
 129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
 251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
 49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
 138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

// 10 unit vectors
double TerrainGenerator::grad2[10][2] = {
	{1.0, 0.0},
	{0.81, 0.59},
	{0.31, 0.95},
	{-0.31, 0.95},
	{-0.81, 0.59},
	{-1.0, 0.0},
	{-0.81, -0.59},
	{-0.31, -0.95},
	{0.31, -0.95},
	{0.81, -0.59},
};


TerrainGenerator::TerrainGenerator()
{

}


TerrainGenerator::~TerrainGenerator(void)
{

}

// Defining grid of 32 units
double TerrainGenerator::getHeightValue(int x, int y)
{
	double tx, ty;
	
	tx = float(x)/64;
	ty = float(y)/64;

	double total = 0.0;
	double frequency = this->frequency;
	double amplitude = this->amplitude;

	return getValue(tx, ty);
}

double TerrainGenerator::getValue(double x, double y)
{
	double rx, ry;
	// integer
	int ix, iy;

	ix = fastFloor(x);
	iy = fastFloor(y);

	rx = x - ix;
	ry = y - iy;

	// gradient indices
	int i00, i10, i01, i11;

	// Get some random numbers in the range 0-10 for our gradients
	i00 = p[(ix + p[iy]) % 255] % 10;
	i01 = p[(ix + p[iy+1]) % 255] % 10;
	i10 = p[(ix+1 +p[iy]) % 255] % 10;
	i11 = p[(ix+1 +p[iy+1]) % 255] % 10;

	/*double n01 = noise(ix-1, iy-1);
	double n02 = noise(ix+1, iy-1);
	double n03 = noise(ix-1, iy+1);
	double n04 = noise(ix+1, iy+1);
	double n05 = noise(ix-1, iy);
	double n06 = noise(ix+1, iy);
	double n07 = noise(ix, iy-1);
	double n08 = noise(ix, iy+1);
	double n09 = noise(ix, iy);

	double n12 = noise(ix+2, iy-1);
	double n14 = noise(ix+2, iy+1);
	double n16 = noise(ix+2, iy);

	double n23 = noise(ix-1, iy+2);
	double n24 = noise(ix+1, iy+2);
	double n28 = noise(ix, iy+2);

	double n34 = noise(ix+2, iy+2);

	//find the noise values of the four corners
	double c00 = 0.0625*(n01+n02+n03+n04) + 0.125*(n05+n06+n07+n08) + 0.25*(n09);  
	double c10 = 0.0625*(n07+n12+n08+n14) + 0.125*(n09+n16+n02+n04) + 0.25*(n06);  
	double c01 = 0.0625*(n05+n06+n23+n24) + 0.125*(n03+n04+n09+n28) + 0.25*(n08);  
	double c11 = 0.0625*(n09+n16+n28+n34) + 0.125*(n08+n14+n06+n24) + 0.25*(n04);  
	*/
	
	double c00 = dot(grad2[i00], rx, ry); 
	double c10 = dot(grad2[i10], rx-1, ry);
	double c01 = dot(grad2[i01], rx, ry-1);
	double c11 = dot(grad2[i11], rx-1, ry-1);

	// get faded x and y values
	double x_fade, y_fade;
	x_fade = fade(rx);
	y_fade = fade(ry);

	//interpolate 
	double final_x0, final_x1, final_xy;

	// along x
	final_x0 = interpolate(c00, c10, x_fade);
	final_x1 = interpolate(c01, c11, x_fade);

	final_xy = interpolate(final_x0, final_x1, y_fade);

	//Skew from [-1, 1] to [0, 1]
	final_xy = (final_xy + 1)*0.5f;

	//is there another fix?
	return final_xy > 1 ? 1 : final_xy;
}

// Generate some random numbers
double TerrainGenerator::noise(int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
	int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - double(t) * 0.931322574615478515625e-9; /// 1073741824.0);
}

void TerrainGenerator::seedGenerator(int seed)
{
	if(!locked)
		this->seed = seed;
	locked = true;
}

void TerrainGenerator::setFrequency(double frequency)
{
	this->frequency = frequency;
}

void TerrainGenerator::setOcatves(double octaves)
{
	this->octaves = octaves;
}

void TerrainGenerator::setAmplitude(double amplitude)
{
	this->amplitude = amplitude;
}

double TerrainGenerator::interpolate(double a, double b, double t)
{
	return (1-t)*a + (t*b);
}

// Fade with the formula 3t^2 - 2t^3
double TerrainGenerator::fade(double t)
{ 
	return t*t*(3 - 2*t);
}

double TerrainGenerator::dot(double vec[], double x, double y)
{
	return vec[0]*x + vec[1]*y;
}

int TerrainGenerator::fastFloor(double t)
{ 
	return t == 0 ? t : t > 0 ? (int) t : (int) t-1;
}