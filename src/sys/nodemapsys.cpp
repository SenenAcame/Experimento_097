#include "nodemapsys.hpp"
#include <cfloat>
#include <cstddef>

int NodeMapSys::getSala(NodoCmp& map, float x, float z) {
    int devol = -1;
    for(size_t i = 0; i < map.salas.size(); i++) {
        bool salaLocation = 
            (map.salas.at(i).x + map.salas.at(i).tamx) >= x && 
            (map.salas.at(i).x - map.salas.at(i).tamx) <= x && 
            (map.salas.at(i).z + map.salas.at(i).tamz) >= z && 
            (map.salas.at(i).z - map.salas.at(i).tamz) <= z;

        if(salaLocation) devol = i;
    }
    return devol;
}

///*VIEJO*/ void NodeMapSys::update(EntyMan& EM){
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
//}

/*NUEVO*/ void NodeMapSys::update2(EntyMan& EM, size_t player_ID, size_t map_ID){
    Enty& player = EM.getEntityById(player_ID);
    Enty& map    = EM.getEntityById(map_ID);

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
                    if((salaplayer == 10 || salaplayer == 11) && salaene == 6) {
                        nextcoord = { -89.95, -0.6 };
                    }
                    else if(salaene == 10 && salaplayer != 11) {
                        nextcoord = { -100.74, -4.22 };
                    }
                    else if(salaene == 9 && salaplayer != 11 && salaplayer != 10) {
                        nextcoord = { -88.95, -1.61 };
                    }
                    else {
                        float dist = FLT_MAX;

                        EM.getComponent<SalaCmp>(player).sala = salaplayer;
                        EM.getComponent<SalaCmp>(en).sala = salaene ;

                        ai.behaviour = SB::Patrol;

                        //std::cout << salaplayer << std::endl;
                        //std::cout << salaene << std::endl;

                        for(unsigned int i = 0; i < map_cmp.salas.at(salaene).puertas.size(); i++) {
                            float distx = phy_cmp.x - map_cmp.salas.at(salaene).puertas.at(i).x;
                            float distz = phy_cmp.z - map_cmp.salas.at(salaene).puertas.at(i).z;
                            float minDist = sqrt((distx*distx) + (distz*distz));
                            if(dist > minDist) {
                                dist = minDist;
                                nextcoord = map_cmp.salas.at(salaene).puertas.at(i);
                            }
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
    float salasz[]={-8.81f, -26.35f, -37.15f, -37.15f, -37.16f, -22.76f, -1.61f, -1.61f, -8.81f, -1.61f, -12.42f, -29.96f, -54.7f, -72.24f};
    float tamx[]=  {20.7/2, 7.2/2, 14.4/2, 20.7/2, 14.57/2, 7.2/2, 20.7/2, 14.4/2, 14.4/2, 14.4/2, 7.2/2, 20.7/2, 7.2/2, 20.7/2};
    float tamz[]=  {20.7/2, 14.39/2, 7.21/2, 20.7/2, 7.2/2, 21.6/2, 20.7/2, 7.2/2, 7.2/2, 7.2/2, 14.39/2, 20.7/2, 14.39/2, 20.7/2};

    std::vector<sala> sala;
    std::vector<std::vector<puerta>> todaspuertas;
    std::vector<puerta> puertass1;
    puertass1.push_back({-36.8, -19.66});
    puertass1.push_back({-47.65, -8.81});

    std::vector<puerta> puertass2;
    puertass2.push_back({-36.8, -18.66});
    puertass2.push_back({-36.8, -34.05});

    std::vector<puerta> puertass3;
    puertass3.push_back({-35.8, -33.05});
    puertass3.push_back({-48.1, -37.15});

    std::vector<puerta> puertass4;
    puertass4.push_back({-47.1, -37.15});
    puertass4.push_back({-69.3, -38.15});
    puertass4.push_back({-57.97, -48});

    std::vector<puerta> puertass5;
    puertass5.push_back({-68.3, -37.15});
    puertass5.push_back({-79.1, -33.06});

    std::vector<puerta> puertass6;
    puertass6.push_back({-79.1, -34.06});
    puertass6.push_back({-79.1, -11.46});

    std::vector<puerta> puertass7;
    puertass7.push_back({-79.1, -12.46});
    puertass7.push_back({-68.25, -1.6});
    puertass7.push_back({-89.95, -0.6});

    std::vector<puerta> puertass8;
    puertass8.push_back({-69.25, -1.6});
    puertass8.push_back({-56.95, -5.71});

    std::vector<puerta> puertass9;
    puertass9.push_back({-46.65, -8.81});
    puertass9.push_back({-58.95, -4.71});

    std::vector<puerta> puertass10;
    puertass10.push_back({-88.95, -1.61});
    puertass10.push_back({-101.74, -5.72});

    std::vector<puerta> puertass11;
    puertass11.push_back({-99.74, -4.22});
    puertass11.push_back({-100.24, -20.61});

    std::vector<puerta> puertass12;
    puertass12.push_back({-100.24, -18.61});

    std::vector<puerta> puertass13;
    puertass13.push_back({-57.97, -47});
    puertass13.push_back({-57.97, -62.89});

    std::vector<puerta> puertass14;
    puertass14.push_back({-57.97, -60.89});


    todaspuertas.push_back(puertass1);
    todaspuertas.push_back(puertass2);
    todaspuertas.push_back(puertass3);
    todaspuertas.push_back(puertass4);
    todaspuertas.push_back(puertass5);
    todaspuertas.push_back(puertass6);
    todaspuertas.push_back(puertass7);
    todaspuertas.push_back(puertass8);
    todaspuertas.push_back(puertass9);
    todaspuertas.push_back(puertass10);
    todaspuertas.push_back(puertass11);
    todaspuertas.push_back(puertass12);
    todaspuertas.push_back(puertass13);
    todaspuertas.push_back(puertass14);

    for(unsigned int i = 0; i < todaspuertas.size(); i++)
        sala.push_back({ salasx[i], salasz[i], tamx[i], tamz[i], todaspuertas.at(i) });

    return sala;
};