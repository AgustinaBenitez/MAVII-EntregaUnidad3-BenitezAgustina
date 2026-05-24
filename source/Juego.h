#pragma once

#include <vector>
#include <memory>

class Juego {

private:

    // Mundo físico (contenedor) + objetos
    std::unique_ptr<b2World> mundo;
    std::vector<std::unique_ptr<ObjetoFisico>> objetos;

    // Objetos
    

public:

    Juego();
    ~Juego();

    void Iniciar();
    void Actualizar();
    void Renderizar();
    void Reiniciar();

};