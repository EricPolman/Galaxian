#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "SDL.h"
#include "sdl_mixer.h"
#include <random>
#include <map>
#include <sstream>
#include "Stats.h"
#include "SoundManager.h"

class Vector2{
public: 
	Vector2(){x = 0; y = 0;}
	Vector2(const Vector2& a_vec){x = a_vec.x; y = a_vec.y;}
	Vector2(float a_fX, float a_fY){x = a_fX; y = a_fY;}
	float x; 
	float y;
	void Normalize(){float mag = sqrt(x*x + y*y);x /= mag; y/= mag;}
	float Distance(Vector2 a_vec){float distX = x - a_vec.x; float distY = y - a_vec.y;return sqrt(distX*distX + distY*distY);}
	Vector2 operator+(Vector2 a_vec){return Vector2(x + a_vec.x, y + a_vec.y);}
	Vector2 operator-(Vector2 a_vec){return Vector2(x - a_vec.x, y - a_vec.y);}
	Vector2 operator*(float a_scalar){return Vector2(x * a_scalar, y * a_scalar);}
	Vector2 operator-(){return Vector2(-x, -y);}
};