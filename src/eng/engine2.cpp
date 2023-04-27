#include "engine2.hpp"
#include "../man/levelman.hpp"
#include "../util/types.hpp"
#include "resources/RTexture.hpp"
#include <vector>

void GraphicEngine::createEnemy(LevelMan& LM) {
    auto& EM = LM.getEM();
    Enty& player = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(player, PhysicsCmp2{ });
    auto& rend = EM.addComponent<RenderCmp2> (player, 
        RenderCmp2{ .node = glEng.createModel(
            NULL,
            {-0, -2, -2},
            Vec3(0.f),
            Vec3(0.5f),
            "assets/models/personajes/monstruo2/monstruo2_prueba_verde267.obj"
            //"assets/models/personajes/monstruo2/monstruo2.obj"
            //"assets/Caja_roja.obj"
        )}
    );
    
    RTexture* texture = nullptr;
    texture = glEng.getRG()->getResource<RTexture>("assets/models/personajes/monstruo2/monstruo_dos_verde.png");
    rend.node->setTexture(texture);
}