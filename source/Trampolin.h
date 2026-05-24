#pragma once
#include "raylib.h"
#include <box2d.h>

class Trampolin {

private:

    // Cuerpos que conforman el mecanismo
    b2Body* anclaEstatica; // Necesario para enganchar el riel del Prismatic Joint
    b2Body* trampolinMov;

    // Restricción física
    b2PrismaticJoint* prismaticJoint;

    // Propiedades visuales
    float anchoTrampolinMov, altoTrampolinMov;
    Color colorTrampolinMov;

public:

    Trampolin(b2World* mundo, b2Vec2 posicionInicial);
    ~Trampolin();

    void Dibujar();

};