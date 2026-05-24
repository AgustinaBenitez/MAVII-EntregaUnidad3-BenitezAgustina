#pragma once

#include "raylib.h"

#include <box2d.h>

class Pendulo {

private:

    b2Body* anclaEstatica;
    b2Body* pendulo;
    b2RevoluteJoint* jointRevolute;

    float anchoPendulo, altoPendulo;
    Color colorPendulo;

public:

    Pendulo(b2World* mundo, b2Vec2 posicionInicial);
    ~Pendulo();

    void Dibujar();

};