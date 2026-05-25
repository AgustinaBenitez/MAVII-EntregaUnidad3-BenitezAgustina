#pragma once

#include "raylib.h"

#include <box2d.h>

class Martillo {

private:

    b2Body* anclaEstatica;
    b2Body* mango;
    b2Body* cabeza;

    b2RevoluteJoint* jointRevolute;
    b2WeldJoint* jointWeld;

    float anchoMango, altoMango;
    float anchoCabeza, altoCabeza;
    Color colorMango, colorCabeza;

public:

    Martillo(b2World* mundo, b2Vec2 posicionInicial);
    ~Martillo();

    void Dibujar();
    void DibujarDebug();

};