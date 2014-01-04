#pragma once

#include	<cmath>
#include	<cstdlib>

class PerlinNoise
{
public:
	PerlinNoise(int);
	~PerlinNoise();
	float getElevation(float, float, float);

private:
	float	_tempX;
	float	_tempY;
	int		_x0;
	int		_y0;
	int		_ii;
	int		_jj;
	int		_gi0;
	int		_gi1;
	int		_gi2;
	int		_gi3;
	float	_unit;
	float	_tmp, _s, _t, _u, _v, _Cx, _Cy, _Li1, _Li2;
	float	_gradient2[8][2];

	unsigned int _perm[512];
};