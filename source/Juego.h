#pragma once

#include "ObjetoFisico.h"
#include "Trampolin.h"
#include "Martillo.h"

#include <box2d.h>
#include <vector>
#include <memory>

class Juego {

private:

    // Mundo físico (contenedor) + objetos
    std::unique_ptr<b2World> mundo;
    std::vector<std::unique_ptr<ObjetoFisico>> objetos;

    // Objetos
    std::unique_ptr<Trampolin> trampolin;
    std::unique_ptr<Martillo> martillo;

    // Para mostrar la info solicitada en pantalla sin ensuciar la simulación
    bool modoDebug = false;

public:

    Juego();
    ~Juego();

    void Iniciar();
    void Actualizar();
    void Renderizar();
    void Reiniciar();

};