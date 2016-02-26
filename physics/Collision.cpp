//
//  Collision.cpp
//  2D_RPG
//
//  Created by John Damits on 2/5/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "Collision.h"

Collision::Collision() {
    
}

bool Collision::isColliding(Polygon& shapeA, Polygon& shapeB) {
    if (shapeA.size() > 1 && shapeB.size() > 1) {
        float minOverlap = oneCollide(shapeA, shapeB).MTV;
        if (minOverlap <= 0)
            return false;
        minOverlap = fminf(minOverlap, oneCollide(shapeB, shapeA).MTV);
        if (minOverlap <= 0)
            return false;
    } else if (shapeA.size() > 1 && shapeB.size() <= 1) {
        if (!isCollidingPoint(shapeB.at(0), shapeA))
            return false;
    } else if (shapeB.size() > 1 && shapeA.size() <= 1) {
        if (!isCollidingPoint(shapeA.at(0), shapeB))
            return false;
    }

    return true;
}

CollData Collision::isCollidingMTV(Polygon& shapeA, Polygon& shapeB) {
    CollData dataA = oneCollide(shapeA, shapeB);
    if (dataA.MTV < 0)
        return {{0, 0}, -1, -1};
    CollData dataB = oneCollide(shapeB, shapeA);
    if (dataB.MTV < 0)
        return {{0, 0}, -1, -1};

    if (dataA.MTV < dataB.MTV) {
        dataA.collisionPoints = findCollidingPoints(shapeA, shapeB);
        return dataA;
    } else {
        dataB.collisionPoints = findCollidingPoints(shapeB, shapeA);
        return dataB;
    }
}

CollData Collision::oneCollide(Polygon& shapeA, Polygon& shapeB) {
    float minOverlap = std::numeric_limits<float>::max();
    Vect collNormal;
    int collisionFace = 0;

    for (int a = 0; a < shapeA.size(); a++) {
        float Vx;
        float Vy;
        
        if (a == shapeA.size() - 1) {
            Vx = -(shapeA.at(a).y - shapeA.at(0).y);
            Vy = shapeA.at(a).x - shapeA.at(0).x;
        } else {
            Vx = -(shapeA.at(a + 1).y - shapeA.at(a).y);
            Vy = shapeA.at(a + 1).x - shapeA.at(a).x;
        }

        float Vmag = sqrtf(Vx * Vx + Vy * Vy);
        Vx = Vx / Vmag;
        Vy = Vy / Vmag;

        float TAmin = std::numeric_limits<float>::max();
        float TAmax = -TAmin;
        
        for (int i = 0; i < shapeA.size(); i++) {
            float TAv = (shapeA.at(i).x * Vx + shapeA.at(i).y * Vy) / (Vx * Vx + Vy * Vy);
            float TAvx = TAv * Vx;
            float TAvy = TAv * Vy;
            
            float TAval = TAvx * Vx + TAvy * Vy;

            TAmin = fminf(TAmin, TAval);
            TAmax = fmaxf(TAmax, TAval);
        }
        
        float TBmin = std::numeric_limits<float>::max();
        float TBmax = -TBmin;
        
        for (int i = 0; i < shapeB.size(); i++) {
            float TBv = (shapeB.at(i).x * Vx + shapeB.at(i).y * Vy) / (Vx * Vx + Vy * Vy);
            float TBvx = TBv * Vx;
            float TBvy = TBv * Vy;
            
            float TBval = TBvx * Vx + TBvy * Vy;

            TBmin = fminf(TBmin, TBval);
            TBmax = fmaxf(TBmax, TBval);
        }

        if (!(TBmin <= TAmax && TBmax >= TAmin))
            return {{0, 0}, -1, -1};

        float overlap = fminf(fabsf(TAmax - TBmin), fabsf(TBmax - TAmin));
        if (minOverlap > overlap) {
            minOverlap = overlap;
            collNormal = {Vx, Vy};
            collisionFace = a;
        }
    }

    return {collNormal, minOverlap, collisionFace};
}

bool Collision::isCollidingPoint(Vect& point, Polygon& shape) {
    for (int a = 0; a < shape.size(); a++) {
        float Vx;
        float Vy;

        if (a == shape.size() - 1) {
            Vx = -(shape.at(a).y - shape.at(0).y);
            Vy = shape.at(a).x - shape.at(0).x;
        } else {
            Vx = -(shape.at(a + 1).y - shape.at(a).y);
            Vy = shape.at(a + 1).x - shape.at(a).x;
        }

        float TAmin = std::numeric_limits<float>::max();
        float TAmax = -TAmin;

        for (int i = 0; i < shape.size(); i++) {
            float TAv = (shape.at(i).x * Vx + shape.at(i).y * Vy) / (Vx * Vx + Vy * Vy);
            float TAvx = TAv * Vx;
            float TAvy = TAv * Vy;

            float TAval = TAvx * Vx + TAvy * Vy;

            TAmin = fminf(TAmin, TAval);
            TAmax = fmaxf(TAmax, TAval);
        }

        float TBv = (point.x * Vx + point.y * Vy) / (Vx * Vx + Vy * Vy);
        float TBvx = TBv * Vx;
        float TBvy = TBv * Vy;

        float TBval = TBvx * Vx + TBvy * Vy;

        if (!(TBval <= TAmax && TBval >= TAmin))
            return false;
    }
    
    return true;
}

bool Collision::isCollidingMouse(Polygon& shape) {
    int mX, mY;
    SDL_GetMouseState(&mX, &mY);
    Vect p = {(float)mX, (float)mY};

    return isCollidingPoint(p, shape);
}

std::vector<Vect> Collision::findCollidingPoints(Polygon& shapeA, Polygon& shapeB) {
    std::vector<Vect> points(0);

    for (int i = 0; i < shapeA.size(); i++) {
        Polygon lineA(2);
        if (i == shapeA.size() - 1 && shapeA.size() > 2) {
            lineA[0] = shapeA[i];
            lineA[1] = shapeA[0];
        } else {
            lineA[0] = shapeA[i];
            lineA[1] = shapeA[i + 1];
        }

        if (isColliding(lineA, shapeB)) {
            for (int j = 0; j < shapeB.size(); j++) {
                Polygon lineB(2);
                if (j == shapeB.size() - 1 && shapeB.size() > 2) {
                    lineB[0] = shapeB[j];
                    lineB[1] = shapeB[0];
                } else {
                    lineB[0] = shapeB[j];
                    lineB[1] = shapeB[j + 1];
                }

                if (isColliding(lineA, lineB)) {
                    float mA = (lineA[0].y - lineA[1].y) / (lineA[0].x - lineA[1].x);
                    float bA = lineA[0].y - (mA * lineA[0].x);

                    float mB = (lineB[0].y - lineB[1].y) / (lineB[0].x - lineB[1].x);
                    float bB = lineB[0].y - (mB * lineB[0].x);

                    float x;
                    if ((lineA[0].x - lineA[1].x) == 0 || (lineB[0].x - lineB[1].x) == 0)
                        x = lineB[0].x;
                    else
                        x = (bB - bA) / (mA - mB);

                    float y = mA * x + bA;

                    points.push_back({x, y});
                }
            }
        }
    }

    return points;
}

