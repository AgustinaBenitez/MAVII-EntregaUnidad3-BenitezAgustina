#include "Trampolin.h"

Trampolin::Trampolin(b2World* mundo, b2Vec2 posicionInicial) {

    ancho = 100.0f;
    altoBase = 20.0f;
    altoCama = 10.0f;
    colorBase = BLUE;
    colorCama = RED;

    // ANCLA ESTÁTICA (Punto fijo en el mundo para el riel)
    b2BodyDef defAncla;
    defAncla.type = b2_staticBody;
    defAncla.position = posicionInicial;
    anclaEstatica = mundo->CreateBody(&defAncla);

    // BASE DEL TRAMPOLÍN (Cuerpo dinámico pesado)
    b2BodyDef defBase;
    defBase.type = b2_dynamicBody;
    defBase.position = posicionInicial;
    defBase.fixedRotation = true; // Para que no vuelque
    base = mundo->CreateBody(&defBase);

    b2PolygonShape formaBase;
    formaBase.SetAsBox(ancho / 2.0f, altoBase / 2.0f);

    b2FixtureDef fixBase;
    fixBase.shape = &formaBase;
    fixBase.density = 5.0f;
    fixBase.friction = 0.3f;
    base->CreateFixture(&fixBase);

    // CAMA ELÁSTICA (Cuerpo dinámico más liviano)
    b2BodyDef defCama;
    defCama.type = b2_dynamicBody;
    // La posiciono un poco más arriba de la base
    b2Vec2 posCama;
    posCama.Set(posicionInicial.x, posicionInicial.y - 30.0f);
    defCama.position = posCama;
    defCama.fixedRotation = true;
    cama = mundo->CreateBody(&defCama);

    b2PolygonShape formaCama;
    formaCama.SetAsBox(ancho / 2.0f, altoCama / 2.0f);

    b2FixtureDef fixCama;
    fixCama.shape = &formaCama;
    fixCama.density = 1.0f;
    fixCama.restitution = 0.8f; // Rebote alto para los impactos
    cama->CreateFixture(&fixCama);

    // PRISMATIC JOINT (Movimiento horizontal de la base)
    b2PrismaticJointDef defPrismatico;
    b2Vec2 ejeHorizontal;
    ejeHorizontal.Set(1.0f, 0.0f);

    defPrismatico.Initialize(anclaEstatica, base, base->GetPosition(), ejeHorizontal);

    // Configuro el motor del Prismatic Joint
    defPrismatico.enableMotor = true;
    defPrismatico.maxMotorForce = 2000.0f;
    defPrismatico.motorSpeed = 3.0f;

    jointPrismatico = (b2PrismaticJoint*)mundo->CreateJoint(&defPrismatico);

    // DISTANCE JOINT (Efecto resorte entre la base y la cama)
    b2DistanceJointDef defDistancia;
    defDistancia.Initialize(base, cama, base->GetPosition(), cama->GetPosition());

    // Parámetros elásticos de Box2D
    defDistancia.stiffness = 4.0f;   // Velocidad de oscilación
    defDistancia.damping = 0.2f;  // Amortiguación baja para que siga rebotando

    jointDistancia = (b2DistanceJoint*)mundo->CreateJoint(&defDistancia);

}

Trampolin::~Trampolin() {

    // Destruyo los cuerpos para que Box2D destruya automáticamente los joints asociados
    if (base != nullptr) base->GetWorld()->DestroyBody(base);
    if (cama != nullptr) cama->GetWorld()->DestroyBody(cama);
    if (anclaEstatica != nullptr) anclaEstatica->GetWorld()->DestroyBody(anclaEstatica);

}

void Trampolin::Dibujar() {

    // Dibujo la base
    b2Vec2 posBase = base->GetPosition();
    float angBase = base->GetAngle() * RAD2DEG;
    Rectangle recBase = { posBase.x, posBase.y, ancho, altoBase };
    Vector2 origBase = { ancho / 2.0f, altoBase / 2.0f };
    DrawRectanglePro(recBase, origBase, angBase, colorBase);

    // Dibujo la cama elástica
    b2Vec2 posCama = cama->GetPosition();
    float angCama = cama->GetAngle() * RAD2DEG;
    Rectangle recCama = { posCama.x, posCama.y, ancho, altoCama };
    Vector2 origCama = { ancho / 2.0f, altoCama / 2.0f };
    DrawRectanglePro(recCama, origCama, angCama, colorCama);

}