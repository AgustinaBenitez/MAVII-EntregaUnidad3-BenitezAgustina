#pragma once
#include "ObjetoFisico.h"

class Suelo : public ObjetoFisico {

private:

    float ancho, alto;

public:

    Suelo(b2World* mundo, b2Vec2 pos, float ang, float w, float h, b2BodyType tipo, Color col);
    void Dibujar() override;

};