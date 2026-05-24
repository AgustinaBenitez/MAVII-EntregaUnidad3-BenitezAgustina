#include "Trampolin.h"

Trampolin::Trampolin(b2World* mundo, b2Vec2 posicionInicial) {

    anchoTrampolinMov = 250.0f;
    altoTrampolinMov = 35.0f;
    colorTrampolinMov = DARKBLUE;

    // Ancla estática que va a ser el punto fijo en el mundo para el riel
    b2BodyDef defAncla;
    defAncla.type = b2_staticBody;
    defAncla.position = posicionInicial;
    anclaEstatica = mundo->CreateBody(&defAncla);

    // Armo trampolín movible
    b2BodyDef defTrampolinMov;
    defTrampolinMov.type = b2_dynamicBody;
    defTrampolinMov.position = posicionInicial;
    defTrampolinMov.fixedRotation = true;
    trampolinMov = mundo->CreateBody(&defTrampolinMov);

    b2PolygonShape formaTrampolinMov;
    formaTrampolinMov.SetAsBox(anchoTrampolinMov / 2.0f, altoTrampolinMov / 2.0f);

    b2FixtureDef fixTrampolinMov;
    fixTrampolinMov.shape = &formaTrampolinMov;
    fixTrampolinMov.density = 1.0f;
    fixTrampolinMov.friction = 1.0f;
    trampolinMov->CreateFixture(&fixTrampolinMov);

    // PRISMATIC JOINT (Movimiento horizontal)
    b2PrismaticJointDef prismaticDef;
    b2Vec2 ejeHorizontal;
    ejeHorizontal.Set(1.0f, 0.0f);

    prismaticDef.Initialize(anclaEstatica, trampolinMov, trampolinMov->GetPosition(), ejeHorizontal);

    // Configuro el motor del Prismatic Joint
    prismaticDef.enableMotor = true;
    prismaticDef.maxMotorForce = 500000.0f;
    prismaticDef.motorSpeed = 12.0f;

    prismaticJoint = (b2PrismaticJoint*)mundo->CreateJoint(&prismaticDef);

}

Trampolin::~Trampolin() {

    // Destruyo los cuerpos para que Box2D destruya automáticamente los joints asociados
    if (trampolinMov != nullptr) trampolinMov->GetWorld()->DestroyBody(trampolinMov);
    if (anclaEstatica != nullptr) anclaEstatica->GetWorld()->DestroyBody(anclaEstatica);

}

void Trampolin::Dibujar() {

    b2Vec2 posTrampolinMov = trampolinMov->GetPosition();
    float angTrampolinMov = trampolinMov->GetAngle() * RAD2DEG;
    Rectangle recTrampolinMov = { posTrampolinMov.x, posTrampolinMov.y, anchoTrampolinMov, altoTrampolinMov };
    Vector2 origTrampolinMov = { anchoTrampolinMov / 2.0f, altoTrampolinMov / 2.0f };
    DrawRectanglePro(recTrampolinMov, origTrampolinMov, angTrampolinMov, colorTrampolinMov);

}