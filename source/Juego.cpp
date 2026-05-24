#include "Juego.h"
#include "Suelo.h"

Juego::Juego() {

    // Inicializo gravedad
    b2Vec2 gravedad(0.0f, 9.8f);

    // Inicializo mundo físico
    mundo = std::make_unique<b2World>(gravedad);

}

void Juego::Iniciar() {

    InitWindow(1000, 600, "MAVII - Entrega Guía Unidad 3 - Benitez Agustina");

    SetTargetFPS(60);

    // Cargo todos los objetos
    Reiniciar();

}

void Juego::Actualizar() {

    // Avanzo la simulación física
    mundo->Step(1.0f / 60.0f, 8, 3);

    // Para reiniciar juego
    if (IsKeyPressed(KEY_R)) {
        Reiniciar();
    }

}

void Juego::Renderizar() {

    BeginDrawing();

        ClearBackground(RAYWHITE);

        // Box2D calcula, Raylib dibuja el resultado visual
        for (const auto& obj : objetos) {
            obj->Dibujar();
        }

        // Muestro carteles
        DrawText("zgzgrgdgdds", 25, 21, 30, DARKGRAY);
        DrawText("zggzgzrezrez", 25, 61, 30, DARKGRAY);

        EndDrawing();

}

void Juego::Reiniciar() {

    // Creo el suelo inicial (Cuerpo Estático)
    objetos.emplace_back(std::make_unique<Suelo>(mundo.get(), b2Vec2{ 500, 580 }, 0.0f, 1000.0f, 40.0f, b2_staticBody, DARKGRAY));

    /////// A partir del suelo me armo los límites de la pantalla

    // Pared Izquierda: x=10 (un poquito adentro), y=300 (mitad de alto), ancho=20, alto=600
    objetos.emplace_back(std::make_unique<Suelo>(mundo.get(), b2Vec2{ 10.0f, 300.0f }, 0.0f, 20.0f, 600.0f, b2_staticBody, DARKGRAY));

    // Pared Derecha: x=990, y=300, ancho=20, alto=600
    objetos.emplace_back(std::make_unique<Suelo>(mundo.get(), b2Vec2{ 990.0f, 300.0f }, 0.0f, 20.0f, 600.0f, b2_staticBody, DARKGRAY));



}

Juego::~Juego() {}
