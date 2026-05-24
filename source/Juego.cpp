#include "Juego.h"
#include "Suelo.h"
#include "Pelota.h"

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

    // Lógica del spawner de pelotitas: 2% de probabilidad por frame de que caiga una
    if (GetRandomValue(1, 100) <= 2) {

        // Coordenada X random entre las dos paredes (10 a 990)
        float xRandom = (float)GetRandomValue(30, 970);
        // Coordenada Y arriba de la pantalla, para que caigan desde ahí
        float yInicial = -20.0f;

        // Radio random
        float radioRandom = (float)GetRandomValue(5, 15);

        // Color random (usando un arreglo simple de colores de Raylib)
        Color colores[] = { RED, GREEN, BLUE, ORANGE, PURPLE, YELLOW };
        Color colorRandom = colores[GetRandomValue(0, 5)];

        // Instancio la pelotita y la meto al vector polimórfico
        objetos.emplace_back(std::make_unique<Pelota>(
            mundo.get(),
            b2Vec2{ xRandom, yInicial },
            radioRandom,
            colorRandom
        ));

    }

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

        // Dibujo el trampolín si existe
        if (trampolin) {
            trampolin->Dibujar();
        }

        // Muestro carteles
        DrawText("Mzgzgrgdgdds", 25, 21, 30, DARKGRAY);
        DrawText("R para reiniciar", 25, 61, 30, DARKGRAY);

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

    // Instancio el trampolín en el centro-abajo de la pantalla
    trampolin = std::make_unique<Trampolin>(mundo.get(), b2Vec2{ 500.0f, 500.0f });

}

Juego::~Juego() {}
