#include "engine2.hpp"
#include "../man/levelman.hpp"
#include "../util/types.hpp"
#include "resources/RTexture.hpp"
#include <vector>

void GraphicEngine::createEnemy(LevelMan& LM) {
    auto& EM = LM.getEM();
    Enty& player = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(player, PhysicsCmp2{ });
    auto& r_en = EM.addComponent<RenderCmp2> (player, 
        RenderCmp2{ .node = glEng.createModel(
            NULL,
            {-0, -2, -2},
            Vec3(0.f),
            Vec3(0.5f),
            "assets/models/personajes/monstruo2/monstruo2_prueba_verde267.obj"
        )}
    );
    
    RTexture* texture = nullptr;
    texture = glEng.getRG()->getResource<RTexture>("assets/models/personajes/monstruo2/monstruo_dos_verde.png");
    r_en.node->setTexture(texture);
}

void GraphicEngine::createMap(LevelMan& LM) {
    auto& EM = LM.getEM();

    Enty& sala1 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(sala1, PhysicsCmp2{ });
    auto& r_s1 = EM.addComponent<RenderCmp2> (sala1, 
        RenderCmp2{ .node = glEng.createModel(
            NULL,
            {-10, 0, -10},
            Vec3(0.f),
            Vec3(0.2f),
            "assets/models/mapas/salas_independientes/Sala_1.obj"
        )}
    );

    Enty& sala2 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(sala2, PhysicsCmp2{ });
    auto& r_s2 = EM.addComponent<RenderCmp2> (sala2, 
        RenderCmp2{ .node = glEng.createModel(
            NULL,
            {-10, 0, -10},
            Vec3(0.f),
            Vec3(0.2f),
            "assets/models/mapas/salas_independientes/Sala_2.obj"
        )}
    );

    Enty& sala3 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(sala3, PhysicsCmp2{ });
    auto& r_s3 = EM.addComponent<RenderCmp2> (sala3, 
        RenderCmp2{ .node = glEng.createModel(
            NULL,
            {-10, 0, -10},
            Vec3(0.f),
            Vec3(0.2f),
            "assets/models/mapas/salas_independientes/Sala_3.obj"
        )}
    );

    Enty& pasillo1 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(pasillo1, PhysicsCmp2{ });
    auto& r_p1 = EM.addComponent<RenderCmp2> (pasillo1, 
        RenderCmp2{ .node = glEng.createModel(
            NULL,
            {-10, 0, -10},
            Vec3(0.f),
            Vec3(0.2f),
            "assets/models/mapas/salas_independientes/Pasillo_1.obj"
        )}
    );

    Enty& pasillo2 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(pasillo2, PhysicsCmp2{ });
    auto& r_p2 = EM.addComponent<RenderCmp2> (pasillo2, 
        RenderCmp2{ .node = glEng.createModel(
            NULL,
            {-10, 0, -10},
            Vec3(0.f),
            Vec3(0.2f),
            "assets/models/mapas/salas_independientes/Pasillo_2.obj"
        )}
    );

    Enty& pasillo3 = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(pasillo3, PhysicsCmp2{ });
    auto& r_p3 = EM.addComponent<RenderCmp2> (pasillo3, 
        RenderCmp2{ .node = glEng.createModel(
            NULL,
            {-10, 0, -10},
            Vec3(0.f),
            Vec3(0.2f),
            "assets/models/mapas/salas_independientes/Pasillo_3.obj"
        )}
    );

    //RTexture* texture = nullptr;
    //texture = glEng.getRG()->getResource<RTexture>("assets/textures/mapa/textura_Sala1.png");
    //rend.node->setTexture(texture);
}