//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_MATH_UTIL_H
#define LD50_CLIENT_MATH_UTIL_H

bool doOBBCollideWithOBB(float r1X, float r1Y, float r1Width, float r1Height, float r1Angle,
						 float r2X, float r2Y, float r2Width, float r2Height, float r2Angle);

bool lineIntersectsLine(float l1StartX, float l1StartY, float l1EndX, float l1EndY,
						float l2StartX, float l2StartY, float l2EndX, float l2EndY);

bool inOBB(float x, float y,
		   float rx, float ry, float width, float height, float angle);

#endif //LD50_CLIENT_MATH_UTIL_H
