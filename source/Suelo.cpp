#include "Suelo.h"

Suelo::Suelo(b2World* mundo, b2Vec2 pos, float ang, float w, float h, b2BodyType tipo, Color col)
    : ObjetoFisico(mundo, pos, ang, tipo, col) {

    ancho = w;
    alto = h;

    // Defino la forma rectangular
    b2PolygonShape formaSuelo;
    formaSuelo.SetAsBox(w / 2.0f, h / 2.0f); // Porque Box2D usa semi-lados

    // Defino las propiedades físicas mediante una fixture
    b2FixtureDef defFixture;
    defFixture.shape = &formaSuelo;
    defFixture.density = 1.0f;
    defFixture.friction = 0.3f;
    defFixture.restitution = 0.4f;

    // Vinculo la forma al cuerpo
    cuerpo->CreateFixture(&defFixture);

}

void Suelo::Dibujar() {

    // Obtengo el estado calculado por Box2D
    b2Vec2 pos = cuerpo->GetPosition();

    // Convierto para Raylib
    float anguloGrados = cuerpo->GetAngle() * RAD2DEG;

    Rectangle rec = { pos.x, pos.y, ancho, alto };
    Vector2 origen = { ancho / 2.0f, alto / 2.0f };

    // Le paso a Raylib la info de Box2D para representar el objeto
    DrawRectanglePro(rec, origen, anguloGrados, color);

}