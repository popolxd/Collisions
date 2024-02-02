#ifndef SAT_H
#define SAT_H

#include "raylib.h"

typedef struct {
    Vector2* points;
    Vector2* edges; // counter clock-wise
    int pointsLen;
} SAT_Polygon;

void SAT_MovePolygon(SAT_Polygon* polygon, Vector2 speed);
void SAT_DrawPolygon(SAT_Polygon* polygon);
void SAT_CreatePolygon(SAT_Polygon* polygon, int pointsLen, Vector2* points);
float SAT_Vec2DotProd(Vector2 vec1, Vector2 vec2);
Vector2 SAT_GetNormal(Vector2* edge);
float SAT_FindSeparationValue(SAT_Polygon* p1, SAT_Polygon* p2, Vector2* chosenCollisionNormal);

#endif