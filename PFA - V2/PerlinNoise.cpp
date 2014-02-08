#include				"PerlinNoise.h"

PerlinNoise::PerlinNoise(int seed)
{
	_unit = static_cast<float>(1.0f / sqrt(2));
	_gradient2[0][0] = _unit;
	_gradient2[0][1] = _unit;

	_gradient2[1][0] = -_unit;
	_gradient2[1][1] = _unit;

	_gradient2[2][0] = _unit;
	_gradient2[2][1] = -_unit;

	_gradient2[3][0] = -_unit;
	_gradient2[3][1] = -_unit;

	_gradient2[4][0] = 1;
	_gradient2[4][1] = 0;

	_gradient2[5][0] = -1;
	_gradient2[5][1] = 0;

	_gradient2[6][0] = 0;
	_gradient2[6][1] = 1;

	_gradient2[7][0] = 0;
	_gradient2[7][1] = -1;

	srand(seed);
	for (int i = 0 ; i < 512 ; ++i)
		_perm[i] = rand() % 255;

}

PerlinNoise::~PerlinNoise()
{
}

#include <iostream>

float			PerlinNoise::getElevation(float x, float y, float res)
{
	//Adapter pour la résolution
	x /= res;
	y /= res;

	
	//On récupère les positions de la grille associée à (x,y)
	_x0 = (int)(x);
	_y0 = (int)(y);

	//Masquage
	_ii = _x0 & 255;
	_jj = _y0 & 255;


	//Pour récupérer les vecteurs
	_gi0 = _perm[_ii + _perm[_jj]] % 8;
	_gi1 = _perm[_ii + 1 + _perm[_jj]] % 8;
	_gi2 = _perm[_ii + _perm[_jj + 1]] % 8;
	_gi3 = _perm[_ii + 1 + _perm[_jj + 1]] % 8;


	//on récupère les vecteurs et on pondère
	_tempX = x - _x0;
	_tempY = y - _y0;
	_s = _gradient2[_gi0][0] * _tempX + _gradient2[_gi0][1] * _tempY;

	_tempX = x - (_x0 + 1);
	_tempY = y - _y0;
	_t = _gradient2[_gi1][0] * _tempX + _gradient2[_gi1][1] * _tempY;

	_tempX = x - _x0;
	_tempY = y - (_y0 + 1);
	_u = _gradient2[_gi2][0] * _tempX + _gradient2[_gi2][1] * _tempY;

	_tempX = x - (_x0 + 1);
	_tempY = y - (_y0 + 1);
	_v = _gradient2[_gi3][0] * _tempX + _gradient2[_gi3][1] * _tempY;


	//Lissage
	_tmp = x - _x0;
	_Cx = 3 * _tmp * _tmp - 2 * _tmp * _tmp * _tmp;

	_Li1 = _s + _Cx * (_t - _s);
	_Li2 = _u + _Cx * (_v - _u);

	_tmp = y - _y0;
	_Cy = 3 * _tmp * _tmp - 2 * _tmp * _tmp * _tmp;

	return (_Li1 + _Cy * (_Li2 - _Li1));
}