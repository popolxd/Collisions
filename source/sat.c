#include "sat.h"
#include "math.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

void SAT_MovePolygon(SAT_Polygon* polygon, Vector2 speed)
{
    for (int i = 0; i < polygon->pointsLen; i++) {
        polygon->points[i].x += speed.x;
        polygon->points[i].y += speed.y;
    }
}

void SAT_DrawPolygon(SAT_Polygon* polygon)
{
    for (int i = 0; i < polygon->pointsLen - 1; i++) {
        DrawLineV(polygon->points[i], polygon->points[i + 1], WHITE);
    }
    DrawLineV(polygon->points[polygon->pointsLen - 1], polygon->points[0], WHITE);
}

void SAT_CreatePolygon(SAT_Polygon* polygon, int pointsLen, Vector2* points)
{ 
    polygon->pointsLen = pointsLen;
    polygon->points = (Vector2*)malloc(sizeof(Vector2)*polygon->pointsLen);

    for (int i = 0; i < pointsLen; i++) {
        polygon->points[i] = (Vector2){points[i].x, points[i].y};
    }

    polygon->edges = (Vector2*)malloc(sizeof(Vector2)*polygon->pointsLen);
    
    for (int i = 0; i < pointsLen - 1; i++) {
        polygon->edges[i] = (Vector2){points[i + 1].x - points[i].x, points[i + 1].y - points[i].y};
    }
    polygon->edges[pointsLen - 1] = (Vector2){points[0].x - points[pointsLen - 1].x, points[0].y - points[pointsLen - 1].y};
}

float SAT_Vec2DotProd(Vector2 vec1, Vector2 vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

Vector2 SAT_GetNormal(Vector2* edge)
{
    Vector2 rotatedEdge = (Vector2){-edge->y, edge->x};
    float divisor = sqrt(pow(rotatedEdge.x, 2) + pow(rotatedEdge.y, 2));

    rotatedEdge.x /= divisor;
    rotatedEdge.y /= divisor;
    return rotatedEdge;
}

float SAT_FindSeparationValue(SAT_Polygon* p1, SAT_Polygon* p2, Vector2* chosenCollisionNormal)
{
    float maxSep = -INFINITY;
    float minSepForThisEdge;

    // prvy polygon
    for (int i = 0; i < p1->pointsLen; i++) {
        Vector2 normal = SAT_GetNormal(&p1->edges[i]);
        minSepForThisEdge = INFINITY;
        
        for (int j = 0; j < p2->pointsLen; j++) {
            float projection = SAT_Vec2DotProd((Vector2){p2->points[j].x - p1->points[i].x, p2->points[j].y - p1->points[i].y}, normal);
            if (projection < minSepForThisEdge) {
                minSepForThisEdge = projection;
            }
        }

        if (minSepForThisEdge > maxSep) {
            maxSep = minSepForThisEdge;
            chosenCollisionNormal->x = normal.x;
            chosenCollisionNormal->y = normal.y;
        }
    }

    // druhy polygon
    for (int i = 0; i < p2->pointsLen; i++) {
        Vector2 normal = SAT_GetNormal(&p2->edges[i]);
        minSepForThisEdge = INFINITY;
        
        for (int j = 0; j < p1->pointsLen; j++) {
            float projection = SAT_Vec2DotProd((Vector2){p1->points[j].x - p2->points[i].x, p1->points[j].y - p2->points[i].y}, normal);
            if (projection < minSepForThisEdge) {
                minSepForThisEdge = projection;
            }
        }

        if (minSepForThisEdge > maxSep) {
            maxSep = minSepForThisEdge;
            chosenCollisionNormal->x = -normal.x;
            chosenCollisionNormal->y = -normal.y;
        }
    }

    return maxSep;
}