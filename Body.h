#pragma once

namespace bd
{
	const float radiusCoef = 0.1;
	const float sunMass = 1000;
	const double PI = 3.1415926536;
	const double coef = 1; // гравитационная постоянная

	struct Body
	{
		float x;
		float y;
		float vx;
		float vy;
		float m;
		float r = m * radiusCoef;
	};
}


//class Body
//{
//
//public:
//
//	const float radiusCoef = 0.1;
//	float x;
//	float y;
//	float vx;
//	float vy;
//	float m;
//	float r;
//	//float r = m * radiusCoef;
//
//public:
//	Body()
//	{
//		x, y, vx, vy, m, r = 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
//	}
//	Body(float _x, float _y, float _vx, float _vy, float _m) : x{ _x }, y{ _y }, vx{ _vx }, vy{ _vy }, m{ _m }
//	{
//		r = m * radiusCoef;
//	}
//
//	Body& operator=(Body& b)
//	{
//		return b;
//	}
//
//	~Body() = default;
//
//};