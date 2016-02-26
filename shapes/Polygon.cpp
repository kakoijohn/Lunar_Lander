//
//  Polygon.cpp
//  2D_RPG
//
//  Created by John Damits on 2/6/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "Polygon.h"

Polygon::Polygon(int vertecies) : std::vector<Vect>(vertecies){

}

Polygon::Polygon() : std::vector<Vect>(0) {
    
}

void Polygon::addVert(Vect vert) {
    this->push_back(vert);
}

void Polygon::rotate(float rad, Vect point) {
    for (int i = 0; i < this->size(); i++) {
        float distance = sqrtf(powf((point.x - this->at(i).x), 2) + powf((point.y - this->at(i).y), 2));
        float theta = atan2f((this->at(i).y - point.y), (this->at(i).x - point.x));

        theta += rad;
        
        this->at(i).x = point.x + distance * cosf(theta);
        this->at(i).y = point.y + distance * sinf(theta);
    }

    rotation += rad;
}

void Polygon::setRot(float rad, Vect point) {
    for (int i = 0; i < this->size(); i++) {
        float distance = sqrtf(powf((point.x - this->at(i).x), 2) + powf((point.y - this->at(i).y), 2));

        this->at(i).x = point.x + distance * cosf(rad);
        this->at(i).y = point.y + distance * sinf(rad);
    }

    rotation = rad;
}

void Polygon::move(Vect delta) {
    for (int i = 0; i < this->size(); i++) {
        this->at(i).x += delta.x;
        this->at(i).y += delta.y;
    }
}

void Polygon::set(Vect location) {
    Vect original = this->at(0);
    if (this->size() > 1)
        for (int i = 1; i < this->size(); i++) {
            this->at(i).x = (this->at(i).x - original.x) + location.x;
            this->at(i).y = (this->at(i).y - original.y) + location.y;
        }
    this->at(0) = location;
}

void Polygon::resize(float percent) {
    for (int i = 0; i < this->size(); i++) {
        this->at(i).x *= percent;
        this->at(i).y *= percent;
    }
}

Vect Polygon::centroid() {
    float Cx;
    float Cy;

    for (int i = 0; i < this->size(); i++) {
        Cx += this->at(i).x;
        Cy += this->at(i).y;
    }

    Cx = Cx / this->size();
    Cy = Cy / this->size();

    printf("%f, %f\n", Cx, Cy);

    return {Cx, Cy};
}

void Polygon::pollEvents() {
    std::vector<eventData> &events = InputEvent::events;
    for (int i  = 0; i < events.size(); i++) {
        if (events.at(i).active == true) {
            if (events.at(i).identifier == polygon_drag_start) {
                oMousePos = {events.at(i).x, events.at(i).y};
                oPolyPos = this->at(0);
                return;
            } else if (events.at(i).identifier == polygon_move) {
                set({(events.at(i).x - oMousePos.x) + oPolyPos.x, (events.at(i).y - oMousePos.y) + oPolyPos.y});
                return;
            } else if (events.at(i).identifier == polygon_rotate_right) {
                rotate(.1, centroid());
                return;
            } else if (events.at(i).identifier == polygon_rotate_left) {
                rotate(-.1, centroid());
                return;
            }
        }
    }
}

void Polygon::render(SDL_Renderer *SDLRender) {
    for (int i = 0; i < this->size(); i++)
        if (i == this->size() - 1)
            SDL_RenderDrawLine(SDLRender, this->at(i).x, this->at(i).y, this->at(0).x, this->at(0).y);
        else
            SDL_RenderDrawLine(SDLRender, this->at(i).x, this->at(i).y, this->at(i + 1).x, this->at(i + 1).y);
}
