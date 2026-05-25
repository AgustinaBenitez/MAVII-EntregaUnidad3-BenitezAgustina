#include "Trampolin.h"

Trampolin::Trampolin(b2World* mundo, b2Vec2 posicionInicial) {

    // Le doy la forma
    anchoTrampolinMov = 250.0f;
    altoTrampolinMov = 35.0f;
    colorTrampolinMov = DARKBLUE;

    // Ancla estática que va a ser el punto fijo en el mundo para el riel
    b2BodyDef defAncla;
    defAncla.type = b2_staticBody;
    defAncla.position = posicionInicial;
    anclaEstatica = mundo->CreateBody(&defAncla);

    // Propiedades
    b2BodyDef defTrampolinMov;
    defTrampolinMov.type = b2_dynamicBody;
    defTrampolinMov.position = posicionInicial;
    defTrampolinMov.fixedRotation = true;

    trampolinMov = mundo->CreateBody(&defTrampolinMov);

    b2PolygonShape formaTrampolinMov;
    formaTrampolinMov.SetAsBox(anchoTrampolinMov / 2.0f, altoTrampolinMov / 2.0f);

    // Fixture
    b2FixtureDef fixTrampolinMov;
    fixTrampolinMov.shape = &formaTrampolinMov;
    fixTrampolinMov.density = 1.0f;
    fixTrampolinMov.friction = 1.0f;

    trampolinMov->CreateFixture(&fixTrampolinMov);

    // Prismatic Joint para el movimiento horizontal restringido
    b2PrismaticJointDef prismaticDef;
    b2Vec2 ejeHorizontal;
    ejeHorizontal.Set(1.0f, 0.0f);

    prismaticDef.Initialize(anclaEstatica, trampolinMov, trampolinMov->GetPosition(), ejeHorizontal);

    // Configuro el motor del Prismatic Joint
    prismaticDef.enableMotor = true;
    prismaticDef.maxMotorForce = 50000.0f;
    prismaticDef.motorSpeed = 300.0f;

    // Activo y configuro los límites 
    prismaticDef.enableLimit = true;
    prismaticDef.lowerTranslation = -350.0f; // Hacia la izquierda
    prismaticDef.upperTranslation = 350.0f;  // Hacia la derecha

    prismaticJoint = (b2PrismaticJoint*)mundo->CreateJoint(&prismaticDef);

}

Trampolin::~Trampolin() {

    // Destruyo los cuerpos para que Box2D destruya automáticamente los joints asociados
    if (trampolinMov != nullptr) trampolinMov->GetWorld()->DestroyBody(trampolinMov);
    if (anclaEstatica != nullptr) anclaEstatica->GetWorld()->DestroyBody(anclaEstatica);

}

void Trampolin::Actualizar() {

    // Obtengo la posición actual relativa al ancla
    float traslacionActual = prismaticJoint->GetJointTranslation();
    float velocidadActual = prismaticJoint->GetMotorSpeed();

    // Si llegó al tope derecho y se está moviendo a la derecha, invierto la velocidad pasándola a negativa
    if (traslacionActual >= prismaticJoint->GetUpperLimit() && velocidadActual > 0) {
        prismaticJoint->SetMotorSpeed(-300.0f);
    }
    // Si llegó al tope izquierdo y se está moviendo a la izquierda, invierto la velocidad a positiva
    else if (traslacionActual <= prismaticJoint->GetLowerLimit() && velocidadActual < 0) {
        prismaticJoint->SetMotorSpeed(300.0f);
    }

}

void Trampolin::Dibujar() {

    b2Vec2 posTrampolinMov = trampolinMov->GetPosition();
    float angTrampolinMov = trampolinMov->GetAngle() * RAD2DEG;
    Rectangle recTrampolinMov = { posTrampolinMov.x, posTrampolinMov.y, anchoTrampolinMov, altoTrampolinMov };
    Vector2 origTrampolinMov = { anchoTrampolinMov / 2.0f, altoTrampolinMov / 2.0f };
    DrawRectanglePro(recTrampolinMov, origTrampolinMov, angTrampolinMov, colorTrampolinMov);

}

void Trampolin::DibujarDebug() {

    // Obtengo el ancla estática del Prismatic Joint
    b2Vec2 anclaP = prismaticJoint->GetAnchorA();

    // Dibujo una línea semitransparente para marcar el eje de desplazamiento
    DrawLineEx({ anclaP.x - 350.0f, anclaP.y }, { anclaP.x + 350.0f, anclaP.y }, 3.0f, Fade(GREEN, 0.4f));

    // Dibujo el punto exacto de conexión (el ancla)
    DrawCircle((int)anclaP.x, (int)anclaP.y, 6, DARKGREEN);

    // Texto de identificación (arriba a la izquierda del mecanismo)
    DrawText("Prismatic Joint", (int)anclaP.x - 350, (int)anclaP.y - 40, 20, DARKGREEN);

    // Descripción basada en el apunte teórico
    DrawText("Restringe el movimiento a una unica direccion", (int)anclaP.x - 350, (int)anclaP.y - 15, 10, DARKGRAY);

}