#pragma once
#include "ObjetoFisico.h"

class Pelota : public ObjetoFisico {

private:

    float radio;

public:

    Pelota(b2World* mundo, b2Vec2 posicion, float r, Color col);
    void Dibujar() override;

};