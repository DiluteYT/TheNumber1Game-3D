#pragma once

#include <cstdlib>
#include <cmath>
#include <iostream>

class Perlin {
public:
	Perlin();
	~Perlin();

	// Generates a Perlin (smoothed) noise value between -1 and 1, at the given 3D position.
	float noise(float sample_x, float sample_y, float sample_z);


private:
	int *p; // Permutation table
	// Gradient vectors
	float *Gx;
	float *Gy;
	float *Gz;
};

class PerlinMath
{
	Perlin perlin;

	unsigned int seed;
	unsigned int seed2;
	unsigned int seed3;

	float layer1 = 0.0f;
	float layer2 = 0.0f;
	float layer3 = 0.0f;

public:

	PerlinMath()
		: seed(std::rand()),
		seed2(std::rand()),
		seed3(std::rand())
	{

	}

	int noise(float x, float z)
	{

		layer1 = perlin.noise((x + seed) / 100, 0.0f, (z + seed) / 100) * 20;
		layer2 = perlin.noise((x + seed2) / 100, 0.0f, (z + seed2) / 100) * 50;
		layer3 = perlin.noise((x + seed2) / 50, 0.0f, (z + seed2) / 50) * 60;
		return std::round(layer1 + layer2 + layer3);
	}

};

