#include "Martillo.h"

Martillo::Martillo(b2World* mundo, b2Vec2 posicionInicial) {

    // Le doy forma alargada para que parezca mango de martillo
    anchoMango = 20.0f;
    altoMango = 100.0f;
    colorMango = ORANGE;

    // Cabeza del martillo
    anchoCabeza = 60.0f;
    altoCabeza = 30.0f;
    colorCabeza = DARKGRAY;

    // Ancla estática
    b2BodyDef defAncla;
    defAncla.type = b2_staticBody;
    defAncla.position = posicionInicial;
    anclaEstatica = mundo->CreateBody(&defAncla);

    // El mango
    b2BodyDef defMango;
    defMango.type = b2_dynamicBody;
    b2Vec2 posMango;
    posMango.Set(posicionInicial.x, posicionInicial.y + (altoMango / 2.0f));
    defMango.position = posMango;
    mango = mundo->CreateBody(&defMango);

    b2PolygonShape formaMango;
    formaMango.SetAsBox(anchoMango / 2.0f, altoMango / 2.0f);

    b2FixtureDef fixMango;
    fixMango.shape = &formaMango;
    fixMango.density = 0.1f;
    fixMango.friction = 0.3f;
    mango->CreateFixture(&fixMango);

    // La cabeza
    b2BodyDef defCabeza;
    defCabeza.type = b2_dynamicBody;
    b2Vec2 posCabeza;
    // La ubico justo debajo de donde termina el mango
    posCabeza.Set(posicionInicial.x, posicionInicial.y + altoMango + (altoCabeza / 2.0f));
    defCabeza.position = posCabeza;
    cabeza = mundo->CreateBody(&defCabeza);

    b2PolygonShape formaCabeza;
    formaCabeza.SetAsBox(anchoCabeza / 2.0f, altoCabeza / 2.0f);

    b2FixtureDef fixCabeza;
    fixCabeza.shape = &formaCabeza;
    fixCabeza.density = 2.0f; // Más pesada para que tenga inercia al golpear
    fixCabeza.friction = 0.3f;
    fixCabeza.restitution = 0.5f;
    cabeza->CreateFixture(&fixCabeza);

    // REVOLUTE JOINT
    b2RevoluteJointDef defRevolute;
    // Inicializamos indicando los cuerpos y el punto de rotación
    defRevolute.Initialize(anclaEstatica, mango, posicionInicial);

    // Activo el motor rotacional para que golpee como martillo
    defRevolute.enableMotor = true;
    defRevolute.motorSpeed = 5.0f;
    defRevolute.maxMotorTorque = 50000000.0f; 

    jointRevolute = (b2RevoluteJoint*)mundo->CreateJoint(&defRevolute);

    // WELD JOINT para hacer la unión rígida entre mango y cabeza
    b2WeldJointDef defWeld;
    b2Vec2 puntoDeUnion;
    puntoDeUnion.Set(posicionInicial.x, posicionInicial.y + altoMango);

    // Inicializo indicando los cuerpos y el punto de unión
    defWeld.Initialize(mango, cabeza, puntoDeUnion);
    jointWeld = (b2WeldJoint*)mundo->CreateJoint(&defWeld);

}

Martillo::~Martillo() {

    // Se destruyen en orden inverso
    if (cabeza != nullptr) cabeza->GetWorld()->DestroyBody(cabeza);
    if (mango != nullptr) mango->GetWorld()->DestroyBody(mango);
    if (anclaEstatica != nullptr) anclaEstatica->GetWorld()->DestroyBody(anclaEstatica);

}

void Martillo::Dibujar() {

    // Dibujo el mango
    b2Vec2 posMango = mango->GetPosition();
    float angMango = mango->GetAngle() * RAD2DEG;
    Rectangle recMango = { posMango.x, posMango.y, anchoMango, altoMango };
    Vector2 origMango = { anchoMango / 2.0f, altoMango / 2.0f };
    DrawRectanglePro(recMango, origMango, angMango, colorMango);

    // Dibujo la cabeza
    b2Vec2 posCabeza = cabeza->GetPosition();
    float angCabeza = cabeza->GetAngle() * RAD2DEG;
    Rectangle recCabeza = { posCabeza.x, posCabeza.y, anchoCabeza, altoCabeza };
    Vector2 origCabeza = { anchoCabeza / 2.0f, altoCabeza / 2.0f };
    DrawRectanglePro(recCabeza, origCabeza, angCabeza, colorCabeza);

}