//
// Created by Alexander Winter🤤 on 2022-04-02.
//

#include "util/math_util.h"
#include "SFML/System/Vector2.hpp"

bool doOBBCollideWithOBB(float r1X, float r1Y, float r1Width, float r1Height, float r1Angle,
						 float r2X, float r2Y, float r2Width, float r2Height, float r2Angle)
{
	sf::Vector2 vec(r1Width, r1Height);
	vec.x *= -0.5f;
	vec.y *= -0.5f;
	vec.rotatedBy(sf::degrees(r1Angle));
	vec += { r1X, r1Y };
	float r1X1 = vec.x;
	float r1Y1 = vec.y;

	sf::Vector2 vec2(r1Width, r1Height);
	vec2.x *= -0.5f;
	vec2.y *= 0.5f;
	vec2.rotatedBy(sf::degrees(r1Angle));
	vec2 += { r1X, r1Y };
	float r1X2 = vec2.x;
	float r1Y2 = vec2.y;

	sf::Vector2 vec3(r1Width, r1Height);
	vec3.x *= 0.5f;
	vec3.y *= 0.5f;
	vec3.rotatedBy(sf::degrees(r1Angle));
	vec3 += { r1X, r1Y };
	float r1X3 = vec3.x;
	float r1Y3 = vec3.y;

	sf::Vector2 vec4(r1Width, r1Height);
	vec4.x *= 0.5f;
	vec4.y *= -0.5f;
	vec4.rotatedBy(sf::degrees(r1Angle));
	vec4 += { r1X, r1Y };
	float r1X4 = vec4.x;
	float r1Y4 = vec4.y;

	sf::Vector2 vec5(r2Width, r2Height);
	vec5.x *= -0.5f;
	vec5.y *= -0.5f;
	vec5.rotatedBy(sf::degrees(r2Angle));
	vec5 += { r2X, r2Y };
	float r2X1 = vec5.x;
	float r2Y1 = vec5.y;

	sf::Vector2 vec6(r2Width, r2Height);
	vec6.x *= -0.5f;
	vec6.y *= 0.5f;
	vec6.rotatedBy(sf::degrees(r2Angle));
	vec6 += { r2X, r2Y };
	float r2X2 = vec6.x;
	float r2Y2 = vec6.y;

	sf::Vector2 vec7(r2Width, r2Height);
	vec7.x *= 0.5f;
	vec7.y *= 0.5f;
	vec7.rotatedBy(sf::degrees(r2Angle));
	vec7 += { r2X, r2Y };
	float r2X3 = vec7.x;
	float r2Y3 = vec7.y;

	sf::Vector2 vec8(r2Width, r2Height);
	vec8.x *= 0.5f;
	vec8.y *= -0.5f;
	vec8.rotatedBy(sf::degrees(r2Angle));
	vec8 += { r2X, r2Y };
	float r2X4 = vec8.x;
	float r2Y4 = vec8.y;

	if(lineIntersectsLine(r1X1, r1Y1, r1X2, r1Y2, r2X1, r2Y1, r2X2, r2Y2)
	   || lineIntersectsLine(r1X1, r1Y1, r1X2, r1Y2, r2X2, r2Y2, r2X3, r2Y3)
	   || lineIntersectsLine(r1X1, r1Y1, r1X2, r1Y2, r2X3, r2Y3, r2X4, r2Y4)
	   || lineIntersectsLine(r1X1, r1Y1, r1X2, r1Y2, r2X4, r2Y4, r2X1, r2Y1)
	   || lineIntersectsLine(r1X2, r1Y2, r1X3, r1Y3, r2X1, r2Y1, r2X2, r2Y2)
	   || lineIntersectsLine(r1X2, r1Y2, r1X3, r1Y3, r2X2, r2Y2, r2X3, r2Y3)
	   || lineIntersectsLine(r1X2, r1Y2, r1X3, r1Y3, r2X3, r2Y3, r2X4, r2Y4)
	   || lineIntersectsLine(r1X2, r1Y2, r1X3, r1Y3, r2X4, r2Y4, r2X1, r2Y1)
	   || lineIntersectsLine(r1X3, r1Y3, r1X4, r1Y4, r2X1, r2Y1, r2X2, r2Y2)
	   || lineIntersectsLine(r1X3, r1Y3, r1X4, r1Y4, r2X2, r2Y2, r2X3, r2Y3)
	   || lineIntersectsLine(r1X3, r1Y3, r1X4, r1Y4, r2X3, r2Y3, r2X4, r2Y4)
	   || lineIntersectsLine(r1X3, r1Y3, r1X4, r1Y4, r2X4, r2Y4, r2X1, r2Y1)
	   || lineIntersectsLine(r1X4, r1Y4, r1X1, r1Y1, r2X1, r2Y1, r2X2, r2Y2)
	   || lineIntersectsLine(r1X4, r1Y4, r1X1, r1Y1, r2X2, r2Y2, r2X3, r2Y3)
	   || lineIntersectsLine(r1X4, r1Y4, r1X1, r1Y1, r2X3, r2Y3, r2X4, r2Y4)
	   || lineIntersectsLine(r1X4, r1Y4, r1X1, r1Y1, r2X4, r2Y4, r2X1, r2Y1))
		return true;

	return inOBB(r2X, r2Y, r1X, r1Y, r1Width, r1Height, r1Angle)
		   || inOBB(r1X, r1Y, r2X, r2Y, r2Width, r2Height, r2Angle);
}

bool inOBB(float x, float y,
		   float rx, float ry, float width, float height, float angle)
{
	sf::Vector2 vec(x - rx, y - ry);

	vec = vec.rotatedBy(sf::degrees(-angle));

	return vec.x <= width / 2.0f
		   && vec.x >= -width / 2.0f
		   && vec.y <= height / 2.0f
		   && vec.y >= -height / 2.0f;
}

bool lineIntersectsLine(float l1StartX, float l1StartY, float l1EndX, float l1EndY,
						float l2StartX, float l2StartY, float l2EndX, float l2EndY)
{
	sf::Vector2 vec(l1StartX - l1EndX, l1StartY - l1EndY);

	vec = vec.rotatedBy(sf::degrees(90));

	float dot1 = vec.dot({l1StartX - l2StartX, l1StartY - l2StartY});
	float dot2 = vec.dot({l1StartX - l2EndX, l1StartY - l2EndY});

	if(dot1 > 0 == dot2 > 0)
		return false;

	sf::Vector2 vec2(l2StartX - l2EndX, l2StartY - l2EndY);
	vec2 = vec2.rotatedBy(sf::degrees(90));

	dot1 = vec2.dot({l2StartX - l1StartX, l2StartY - l1StartY});
	dot2 = vec2.dot({l2StartX - l1EndX, l2StartY - l1EndY});

	return dot1 > 0 != dot2 > 0;
}