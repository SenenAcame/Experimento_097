#include "nodemapsys.hpp"
#include <cfloat>
#include <cstddef>

int NodeMapSys::getSala(NodoCmp& map, float x, float z) {
    int devol = -1;
    for(std::size_t i = 0; i < map.salas.size(); i++) {
        bool salaLocation = 
            (map.salas.at(i).x + map.salas.at(i).tamx) >= x && 
            (map.salas.at(i).x - map.salas.at(i).tamx) <= x && 
            (map.salas.at(i).z + map.salas.at(i).tamz) >= z && 
            (map.salas.at(i).z - map.salas.at(i).tamz) <= z;

        if(salaLocation) devol = i;
    }
    return devol;
}

/*VIEJO*/ void NodeMapSys::update(EntyMan& EM){
    //float playerposx, playerposz;
    //Enty player;
    //NodoCmp map;
    //EM.foreach<PlayCMPs, PlayTAGs>(
    //    [&](Enty& p, PhysicsCmp2& phy) {
    //        playerposx = phy.x;
    //        playerposz = phy.z;
    //        player = p;
    //    }
    //);
    //EM.foreach<NodoCMPs, MapTAGs>(
    //    [&](Enty& en, NodoCmp& n) {
    //        map = n;
    //    }
    //);
    //int salaplayer = getSala(map, playerposx, playerposz);
    //EM.foreach<EneCMPs, EneTAGs>(
    //    [&](Enty& en, PhysicsCmp2& p, AICmp& ai) {
    //        int salaene = getSala(map, p.x, p.z);
    //        if(ai.behaviour != SB::Diying) {
    //            if(salaene == salaplayer || salaene == -1) {
    //                if(en.hasTAG<TDistEnemy>()) EM.getComponent<SalaCmp>(player).sala = salaplayer; 
    //
    //                EM.getComponent<SalaCmp>(en).sala = salaene;
    //
    //                bool sameSala = 
    //                    en.hasTAG<TDistEnemy>() && 
    //                    sqrt((p.x-playerposx)*(p.x-playerposx)+(p.z-playerposz)*(p.z-playerposz)) < 40 && 
    //                    salaene != -1;
    //
    //                if(sameSala) ai.behaviour = SB::Shoot;
    //                else         ai.behaviour = SB::Two_Steps;
    //            }
    //            else {
    //                EM.getComponent<SalaCmp>(player).sala = salaplayer;
    //                EM.getComponent<SalaCmp>(en).sala = salaene ;
    //                ai.behaviour = SB::Patrol;
    //                puerta nextcoord = { 0, 0 };
    //                float dist = MAXFLOAT;
    //                for(unsigned int i = 0; i < map.salas.at(salaene).puertas.size(); i++) {
    //                    float distx = playerposx-map.salas.at(salaene).puertas.at(i).x;
    //                    float distz = playerposz-map.salas.at(salaene).puertas.at(i).z;
    //                    float minDist = sqrt((distx*distx)+(distz*distz));
    //                    if(dist > minDist) {
    //                        dist = minDist;
    //                        nextcoord = map.salas.at(salaene).puertas.at(i);
    //                    }
    //                }
    //                ai.ox = nextcoord.x;
    //                ai.oz = nextcoord.z;
    //            }
    //        }
    //    }
    //);
    ////EM.foreach<MapTAGsSpawns>(
    ////    //poner temporizador para que no compruebe todo el rato
    ////    [&](Enty& spawn, PhysicsCmp2& p, SpawnCmp& spawnC) {
    ////        if( spawnC.sala == salaplayer){
    ////            spawnC.active = 1;
    ////        }
    ////    }
    ////);
}

/*NUEVO*/ void NodeMapSys::update2(EntyMan& EM, std::size_t player_ID, std::size_t map_ID){
    Enty& player = EM.getEntityById(player_ID);
    Enty& map    = EM.getEntityById(map_ID);

    std::cout << "Player: " << player_ID << std::endl;
    std::cout << "Mapa: " << map_ID << std::endl;

    auto& phy_cmp = EM.getComponent<PhysicsCmp2>(player);
    auto& map_cmp = EM.getComponent<NodoCmp>(map);

    int salaplayer = getSala(map_cmp, phy_cmp.x, phy_cmp.z);

    EM.foreach<EneCMPs, EneTAGs>(
        [&](Enty& en, PhysicsCmp2& p, AICmp& ai) {
            int salaene = getSala(map_cmp, p.x, p.z);
            if(ai.behaviour != SB::Diying) {
                if(salaene == salaplayer || salaene == -1) {
                    if(en.hasTAG<TDistEnemy>()) EM.getComponent<SalaCmp>(player).sala = salaplayer; 

                    EM.getComponent<SalaCmp>(en).sala = salaene;

                    bool sameSala = 
                        en.hasTAG<TDistEnemy>() && 
                        sqrt((p.x-phy_cmp.x)*(p.x-phy_cmp.x)+(p.z-phy_cmp.z)*(p.z-phy_cmp.z)) < 40 && 
                        salaene != -1;

                    if(sameSala) ai.behaviour = SB::Shoot;
                    else         ai.behaviour = SB::Two_Steps;
                }
                else {
                    puerta nextcoord = { 0, 0 };
                    float dist = FLT_MAX;

                    EM.getComponent<SalaCmp>(player).sala = salaplayer;
                    EM.getComponent<SalaCmp>(en).sala = salaene ;
                    ai.behaviour = SB::Patrol;

                    for(unsigned int i = 0; i < map_cmp.salas.at(salaene).puertas.size(); i++) {
                        float distx = phy_cmp.x - map_cmp.salas.at(salaene).puertas.at(i).x;
                        float distz = phy_cmp.z - map_cmp.salas.at(salaene).puertas.at(i).z;
                        float minDist = sqrt((distx*distx) + (distz*distz));
                        if(dist > minDist) {
                            dist = minDist;
                            nextcoord = map_cmp.salas.at(salaene).puertas.at(i);
                        }
                    }
                    ai.ox = nextcoord.x;
                    ai.oz = nextcoord.z;
                }
            }
        }
    );
}

std::vector<sala> NodeMapSys::creaSalas() {

    float salasx[]={-36.8f, -36.8f, -40.4f, -57.95f, -75.5f, -79.1f, -79.1f, -61.55f, -54.35f, -96.65f, -100.25f, -100.25f, -57.95f, -57.95f};
    float salasz[]={8.81f, 26.35f, 37.15f, 37.15f, 37.16f, 22.76f, 1.61f, 1.61f, 8.81f, 1.61f, 12.42f, 29.96f, 54.7f, 72.24f};
    float tamx[]=  {20.7/2, 7.2/2, 14.4/2, 20.7/2, 14.57/2, 7.2/2, 20.7/2, 14.4/2, 14.4/2, 14.4/2, 7.2/2, 20.7/2, 7.2/2, 20.7/2};
    float tamz[]=  {20.7/2, 14.39/2, 7.21/2, 20.7/2, 7.2/2, 21.6/2, 20.7/2, 7.2/2, 7.2/2, 7.2/2, 14.39/2, 20.7/2, 14.39/2, 20.7/2};

    std::vector<sala> sala;
    std::vector<puerta> puertass1;
    puertass1.push_back({-36.8, 20.16});
    puertass1.push_back({-48.15, 8.81});

    std::vector<puerta> puertass2;
    puertass2.push_back({-36.8, 18.16});
    puertass2.push_back({-36.8, 34.55});

    std::vector<puerta> puertass3;
    puertass3.push_back({-36.8, 32.55});
    puertass3.push_back({-48.6, 37.15});

    std::vector<puerta> puertass4;
    puertass4.push_back({-46.6, 37.15});
    puertass4.push_back({-69.3, 37.15});
    puertass4.push_back({-57.97, 48.5});

    std::vector<puerta> puertass5;
    puertass5.push_back({-67.3, 37.15});
    puertass5.push_back({-79.1, 32.56});

    std::vector<puerta> puertass6;
    puertass6.push_back({-79.1, 34.56});
    puertass6.push_back({-79.1, 10.96});

    std::vector<puerta> puertass7;
    puertass7.push_back({-79.1, 12.96});
    puertass7.push_back({-67.75, 1.6});
    puertass7.push_back({-90.45, 1.6});

    std::vector<puerta> puertass8;
    puertass8.push_back({-69.75, 1.6});
    puertass8.push_back({-57.95, 6.21});

    std::vector<puerta> puertass9;
    puertass9.push_back({-46.15, 8.81});
    puertass9.push_back({-57.95, 4.21});

    std::vector<puerta> puertass10;
    puertass10.push_back({-88.45, 1.61});
    puertass10.push_back({-100.24, 6.22});

    std::vector<puerta> puertass11;
    puertass11.push_back({-100.24, 4.22});
    puertass11.push_back({-100.24, 20.61});

    std::vector<puerta> puertass12;
    puertass12.push_back({-100.24, 18.61});

    std::vector<puerta> puertass13;
    puertass13.push_back({-57.97, 46.5});
    puertass13.push_back({-57.97, 62.89});

    std::vector<puerta> puertass14;
    puertass14.push_back({-57.97, 60.89});

    std::vector<puerta> todaspuertas[] = { 
        puertass1, puertass2, puertass3, puertass4, puertass5, 
        puertass6, puertass7, puertass8, puertass9, puertass10,
        puertass11, puertass12, puertass13, puertass14
    };

    for(unsigned int i = 0; i < std::size(todaspuertas); i++)
        sala.push_back({ salasx[i], salasz[i], tamx[i], tamz[i], todaspuertas[i] });

    return sala;
};