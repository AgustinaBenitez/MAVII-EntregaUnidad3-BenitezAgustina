#pragma once
#include "raylib.h"
#include <box2d.h>

class Trampolin {

private:

    // Cuerpos que conforman el mecanismo
    b2Body* anclaEstatica; // Necesario para enganchar el riel del Prismatic Joint
    b2Body* base;
    b2Body* cama;

    // Restricciones físicas
    b2PrismaticJoint* jointPrismatico;
    b2DistanceJoint* jointDistancia;

    // Propiedades visuales
    float ancho, altoBase, altoCama;
    Color colorBase, colorCama;

public:

    Trampolin(b2World* mundo, b2Vec2 posicionInicial);
    ~Trampolin();

    void Dibujar();

};