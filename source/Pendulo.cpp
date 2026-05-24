#include "Pendulo.h"

Pendulo::Pendulo(b2World* mundo, b2Vec2 posicionInicial) {

    // Le damos forma alargada tipo pendulo
    anchoPendulo = 20.0f;
    altoPendulo = 100.0f;
    colorPendulo = ORANGE;

    // 1. ANCLA ESTÁTICA (La plataforma fija en el aire)
    b2BodyDef defAncla;
    defAncla.type = b2_staticBody;
    defAncla.position = posicionInicial;
    anclaEstatica = mundo->CreateBody(&defAncla);

    // 2. EL BATE (Cuerpo dinámico)
    b2BodyDef defPendulo;
    defPendulo.type = b2_dynamicBody;

    // Lo posicionamos desfasado hacia abajo para que el eje de rotación 
    // quede en la punta superior del pendulo (como si lo agarraran del mango)
    b2Vec2 posPendulo;
    posPendulo.Set(posicionInicial.x, posicionInicial.y + (altoPendulo / 2.0f));
    defPendulo.position = posPendulo;
    pendulo = mundo->CreateBody(&defPendulo);

    b2PolygonShape formaPendulo;
    formaPendulo.SetAsBox(anchoPendulo / 2.0f, altoPendulo / 2.0f);

    b2FixtureDef fixPendulo;
    fixPendulo.shape = &formaPendulo;
    fixPendulo.density = 0.1f;
    fixPendulo.friction = 3.0f;
    fixPendulo.restitution = 0.5f; // Para que las pelotitas salgan rebotando
    pendulo->CreateFixture(&fixPendulo);

    // 3. REVOLUTE JOINT (La articulación)
    b2RevoluteJointDef defRevolute;
    // Inicializamos indicando los cuerpos y el punto de rotación [cite: 485, 486]
    defRevolute.Initialize(anclaEstatica, pendulo, posicionInicial);

    // Activamos el motor rotacional para que golpee como pendulo [cite: 524, 526]
    defRevolute.enableMotor = true;
    defRevolute.motorSpeed = 5.0f; // Velocidad de giro [cite: 527]
    defRevolute.maxMotorTorque = 50000.0f; // Fuerza de rotación (Torque) 

    jointRevolute = (b2RevoluteJoint*)mundo->CreateJoint(&defRevolute);

}

Pendulo::~Pendulo() {
    if (pendulo != nullptr) pendulo->GetWorld()->DestroyBody(pendulo);
    if (anclaEstatica != nullptr) anclaEstatica->GetWorld()->DestroyBody(anclaEstatica);
}

void Pendulo::Dibujar() {
    b2Vec2 pos = pendulo->GetPosition();
    float ang = pendulo->GetAngle() * RAD2DEG;
    Rectangle rec = { pos.x, pos.y, anchoPendulo, altoPendulo };
    Vector2 orig = { anchoPendulo / 2.0f, altoPendulo / 2.0f };
    DrawRectanglePro(rec, orig, ang, colorPendulo);
}