#include "Pelota.h"

Pelota::Pelota(b2World* mundo, b2Vec2 posicion, float r, Color col)
    : ObjetoFisico(mundo, posicion, 0.0f, b2_dynamicBody, col) {

    radio = r;

    // Defino la forma circular
    b2CircleShape formaPelota;
    formaPelota.m_radius = radio;

    // Propiedades físicas
    b2FixtureDef fixPelota;
    fixPelota.shape = &formaPelota;
    fixPelota.density = 0.5f;
    fixPelota.friction = 1.0f;
    fixPelota.restitution = 0.6f;

    cuerpo->CreateFixture(&fixPelota);

}

void Pelota::Dibujar() {

    b2Vec2 pos = cuerpo->GetPosition();

    DrawCircle((int)pos.x, (int)pos.y, radio, color);

}