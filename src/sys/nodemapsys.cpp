#include "nodemapsys.hpp"
#include <cfloat>
#include <cstddef>
#include <queue>

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

void NodeMapSys::update3(EntyMan& EM, std::size_t map_ID, double dt){
    Enty& player = EM.getEntityById(EM.getBoard().entyID);
    Enty& map    = EM.getEntityById(map_ID);

    auto& phy_cmp = EM.getComponent<PhysicsCmp2>(player);
    auto& map_cmp = EM.getComponent<NodoCmp>(map);

    int salaplayer = getSala(map_cmp, phy_cmp.x, phy_cmp.z);

    EM.getComponent<SalaCmp>(player).sala = salaplayer;

    EM.foreach<EneCMPs, EneTAGs>(
        [&](Enty& en, PhysicsCmp2& p, AICmp& ai) {
            int salaene = getSala(map_cmp, p.x, p.z);
            if(ai.behaviour != SB::Diying) {
                if(salaene == salaplayer || salaene == -1) {
                    ai.cooldown_ruta = 0;
                    
                    EM.getComponent<SalaCmp>(en).sala = salaene;

                    bool sameSala = 
                        en.hasTAG<TDistEnemy>() && 
                        sqrt((p.x-phy_cmp.x)*(p.x-phy_cmp.x)+(p.z-phy_cmp.z)*(p.z-phy_cmp.z)) < 10 && 
                        salaene != -1;

                    if(sameSala) ai.behaviour = SB::Shoot;
                    else         ai.behaviour = SB::Two_Steps;
                }
                else {
                    ai.behaviour=SB::Patrol;
                    if(ai.cooldown_ruta>0) {
                        ai.cooldown_ruta-=dt;
                    }
                    else{
                        float dist_player = FLT_MAX;
                        float dist_ene = FLT_MAX;
                        nodomap player_nod;
                        nodomap enemy_nod;
                        for(int i=0;i<map_cmp.nodos.size();i++){
                            if(static_cast<float>(sqrt((map_cmp.nodos.at(i).coord.x-phy_cmp.x)*(map_cmp.nodos.at(i).coord.x-phy_cmp.x)+(map_cmp.nodos.at(i).coord.z-phy_cmp.z)*(map_cmp.nodos.at(i).coord.z-phy_cmp.z)))<dist_player){
                                player_nod=map_cmp.nodos.at(i);
                                dist_player=sqrt((map_cmp.nodos.at(i).coord.x-phy_cmp.x)*(map_cmp.nodos.at(i).coord.x-phy_cmp.x)+(map_cmp.nodos.at(i).coord.z-phy_cmp.z)*(map_cmp.nodos.at(i).coord.z-phy_cmp.z));
                            }
                            if(static_cast<float>(sqrt((map_cmp.nodos.at(i).coord.x-p.x)*(map_cmp.nodos.at(i).coord.x-p.x)+(map_cmp.nodos.at(i).coord.z-p.z)*(map_cmp.nodos.at(i).coord.z-p.z)))<dist_ene){
                                enemy_nod=map_cmp.nodos.at(i);
                                dist_ene=sqrt((map_cmp.nodos.at(i).coord.x-p.x)*(map_cmp.nodos.at(i).coord.x-p.x)+(map_cmp.nodos.at(i).coord.z-p.z)*(map_cmp.nodos.at(i).coord.z-p.z));
                                
                            }
                        }
                        std::vector<nodomap> camino=aEstrella(map_cmp.nodos, enemy_nod, player_nod);
                        if(ai.ruta.size()>0)
                            ai.ruta.clear();
                        for(int i=0;i<camino.size();i++){
                            ai.ruta.push_back(camino.at(i));
                        }
                        if(camino.size()>3){
                            ai.cooldown_ruta=3;
                        }
                        vaciaPadres(map_cmp.nodos);
                    }
                }
            }
        }
    );
}
std::vector<sala> NodeMapSys::creaSalas2() {
    float salasx[]={-36.8f, -36.8f, -40.4f, -57.95f, -75.5f, -79.1f, -79.1f, -61.55f, -54.35f, -96.65f, -100.25f, -100.25f, -57.95f, -57.95f, -79.1f, -36.8f, -57.95f};
    float salasz[]={-8.81f, -26.35f, -37.15f, -37.15f, -37.16f, -22.76f, -1.61f, -1.61f, -8.81f, -1.61f, -12.42f, -29.96f, -54.7f, -72.24f, 15.9f, 12.34f, 33.48f};
    float tamx[]=  {20.7/2, 7.2/2, 14.4/2, 20.7/2, 14.57/2, 7.2/2, 20.7/2, 14.4/2, 14.4/2, 14.4/2, 7.2/2, 20.7/2, 7.2/2, 20.7/2, 7.2/2, 7.2/2, 63/2};
    float tamz[]=  {20.7/2, 14.39/2, 7.21/2, 20.7/2, 7.2/2, 21.6/2, 20.7/2, 7.2/2, 7.2/2, 7.2/2, 14.39/2, 20.7/2, 14.39/2, 20.7/2, 14.38/2, 21.58/2, 20.7/2};

    std::vector<sala> sala;

    for(unsigned int i = 0; i < 17; i++)
        sala.push_back({ salasx[i], salasz[i], tamx[i], tamz[i] });

    return sala;
}

void NodeMapSys::vaciaPadres(std::vector<nodomap>nodos){
    for(int i=0;i<nodos.size();i++){
        nodos.at(i).padre=nullptr;
        nodos.at(i).estimado=0;
        nodos.at(i).total=0;
    }
}

std::vector<nodomap> NodeMapSys::creaNodos() {
    punto punto0 = { -35.75, -0.88 };
    punto punto1 = { -44.32, -8.73 };
    punto punto2 = { -35.75, -16.67 };
    punto punto3 = { -36.57, -37.3 };
    punto punto4 = { -50.3, -37.3 };
    punto punto5 = { -57.25, -45.13 };
    punto punto6 = { -65.59, -37.3 };
    punto punto7 = { -57.53, -64.37 };
    punto punto8 = { -78.58, -37.24 };
    punto punto9 = { -78.35, -8.98 };
    punto punto10 = { -86.64, -1.7 };
    punto punto11 = { -70.95, -1.7 };
    punto punto12 = { -78.64, 6.06 };
    punto punto13 = { -79.89, 26.01 };
    punto punto14 = { -37.17, 26.01 };
    punto punto15 = { -58.86, -1.87 };
    punto punto16 = { -58.64, -8.83 };
    punto punto17 = { -99.83, -2 };
    punto punto18 = { -100.69, -22.22 };
    punto punto19 = { -37, 3.62 };
    punto punto21 = { -37.12, -21.41 };
    punto punto22 = { -45.42, -38.2 };
    punto punto23 = { -57.48, -54.85 };
    punto punto25 = { -49.81, -9.16 };
    punto punto26 = { -67.19, -1.7 };
    punto punto27 = { -79, 16 };
    punto punto29 = { -70.69, -37.6 };
    punto punto30 = { -79.42, -14.38 };
    punto punto31 = { -91.71, -1.6 };
    punto punto32 = { -101, -17.51 };
    punto punto33 = { -57.48, -37.3 };
    punto punto34 = { -78.64, -1.7 };
    punto punto35 = { -35.75, -8.73 };
    punto punto36 = { -37, 21 };

    std::vector<nodomap> Vnodo0;
    std::vector<nodomap> Vnodo1;
    std::vector<nodomap> Vnodo2;
    std::vector<nodomap> Vnodo3;
    std::vector<nodomap> Vnodo4;
    std::vector<nodomap> Vnodo5;
    std::vector<nodomap> Vnodo6;
    std::vector<nodomap> Vnodo7;
    std::vector<nodomap> Vnodo8;
    std::vector<nodomap> Vnodo9;
    std::vector<nodomap> Vnodo10;
    std::vector<nodomap> Vnodo11;
    std::vector<nodomap> Vnodo12;
    std::vector<nodomap> Vnodo13;
    std::vector<nodomap> Vnodo14;
    std::vector<nodomap> Vnodo15;
    std::vector<nodomap> Vnodo16;
    std::vector<nodomap> Vnodo17;
    std::vector<nodomap> Vnodo18;
    std::vector<nodomap> Vnodo19;
    std::vector<nodomap> Vnodo21;
    std::vector<nodomap> Vnodo22;
    std::vector<nodomap> Vnodo23;
    std::vector<nodomap> Vnodo25;
    std::vector<nodomap> Vnodo26;
    std::vector<nodomap> Vnodo27;
    std::vector<nodomap> Vnodo29;
    std::vector<nodomap> Vnodo30;
    std::vector<nodomap> Vnodo31;
    std::vector<nodomap> Vnodo32;
    std::vector<nodomap> Vnodo33;
    std::vector<nodomap> Vnodo34;
    std::vector<nodomap> Vnodo35;
    std::vector<nodomap> Vnodo36;

    nodomap nodo0 = nodomap{ 0, punto0 };
    nodomap nodo1 = nodomap{ 1, punto1 };
    nodomap nodo2 = nodomap{ 2, punto2 };
    nodomap nodo3 = nodomap{ 3, punto3 };
    nodomap nodo4 = nodomap{ 4, punto4 };
    nodomap nodo5 = nodomap{ 5, punto5 };
    nodomap nodo6 = nodomap{ 6, punto6 };
    nodomap nodo7 = nodomap{ 7, punto7 };
    nodomap nodo8 = nodomap{ 8, punto8 };
    nodomap nodo9 = nodomap{ 9, punto9 };
    nodomap nodo10 = nodomap{ 10, punto0 };
    nodomap nodo11 = nodomap{ 11, punto0 };
    nodomap nodo12 = nodomap{ 12, punto0 };
    nodomap nodo13 = nodomap{ 13, punto13 };
    nodomap nodo14 = nodomap{ 14, punto14 };
    nodomap nodo15 = nodomap{ 15, punto15 };
    nodomap nodo16 = nodomap{ 16, punto16 };
    nodomap nodo17 = nodomap{ 17, punto17 };
    nodomap nodo18 = nodomap{ 18, punto18 };
    nodomap nodo19 = nodomap{ 19, punto19 };
    nodomap nodo21 = nodomap{ 21, punto21 };
    nodomap nodo22 = nodomap{ 22, punto22 };
    nodomap nodo23 = nodomap{ 23, punto23 };
    nodomap nodo25 = nodomap{ 25, punto25 };
    nodomap nodo26 = nodomap{ 26, punto26 };
    nodomap nodo27 = nodomap{ 27, punto27 };
    nodomap nodo29 = nodomap{ 29, punto29 };
    nodomap nodo30 = nodomap{ 30, punto30 };
    nodomap nodo31 = nodomap{ 31, punto31 };
    nodomap nodo32 = nodomap{ 32, punto32 };
    nodomap nodo33 = nodomap{ 33, punto33 };
    nodomap nodo34 = nodomap{ 34, punto34 };
    nodomap nodo35 = nodomap{ 35, punto35 };
    nodomap nodo36 = nodomap{ 36, punto36 };

    Vnodo0.push_back(nodo35);
    Vnodo0.push_back(nodo1);
    Vnodo0.push_back(nodo19);

    Vnodo1.push_back(nodo0);
    Vnodo1.push_back(nodo2);
    Vnodo1.push_back(nodo25);

    Vnodo2.push_back(nodo35);
    Vnodo2.push_back(nodo1);
    Vnodo2.push_back(nodo21);

    Vnodo3.push_back(nodo21);
    Vnodo3.push_back(nodo22);

    Vnodo4.push_back(nodo22);
    Vnodo4.push_back(nodo5);
    Vnodo4.push_back(nodo33);

    Vnodo5.push_back(nodo6);
    Vnodo5.push_back(nodo4);
    Vnodo5.push_back(nodo23);

    Vnodo6.push_back(nodo5);
    Vnodo6.push_back(nodo29);
    Vnodo6.push_back(nodo33);

    Vnodo7.push_back(nodo23);

    Vnodo8.push_back(nodo29);
    Vnodo8.push_back(nodo30);

    Vnodo9.push_back(nodo30);
    Vnodo9.push_back(nodo34);
    Vnodo9.push_back(nodo10);
    Vnodo9.push_back(nodo11);

    Vnodo10.push_back(nodo9);
    Vnodo10.push_back(nodo31);
    Vnodo10.push_back(nodo34);
    Vnodo10.push_back(nodo12);

    Vnodo11.push_back(nodo26);
    Vnodo11.push_back(nodo12);
    Vnodo11.push_back(nodo34);
    Vnodo11.push_back(nodo9);

    Vnodo12.push_back(nodo10);
    Vnodo12.push_back(nodo34);
    Vnodo12.push_back(nodo11);
    Vnodo12.push_back(nodo27);

    Vnodo13.push_back(nodo27);
    Vnodo13.push_back(nodo14);

    Vnodo14.push_back(nodo13);
    Vnodo14.push_back(nodo36);

    Vnodo15.push_back(nodo26);
    Vnodo15.push_back(nodo16);

    Vnodo16.push_back(nodo15);
    Vnodo16.push_back(nodo25);

    Vnodo17.push_back(nodo31);
    Vnodo17.push_back(nodo32);

    Vnodo18.push_back(nodo32);

    Vnodo19.push_back(nodo0);
    Vnodo19.push_back(nodo36);

    Vnodo21.push_back(nodo2);
    Vnodo21.push_back(nodo3);

    Vnodo22.push_back(nodo3);
    Vnodo22.push_back(nodo4);

    Vnodo23.push_back(nodo5);
    Vnodo23.push_back(nodo7);

    Vnodo25.push_back(nodo1);
    Vnodo25.push_back(nodo16);

    Vnodo26.push_back(nodo11);
    Vnodo26.push_back(nodo15);

    Vnodo27.push_back(nodo12);
    Vnodo27.push_back(nodo13);

    Vnodo29.push_back(nodo6);
    Vnodo29.push_back(nodo8);

    Vnodo30.push_back(nodo8);
    Vnodo30.push_back(nodo9);

    Vnodo31.push_back(nodo10);
    Vnodo31.push_back(nodo17);

    Vnodo32.push_back(nodo17);
    Vnodo32.push_back(nodo18);

    Vnodo33.push_back(nodo4);
    Vnodo33.push_back(nodo5);
    Vnodo33.push_back(nodo6);

    Vnodo34.push_back(nodo9);
    Vnodo34.push_back(nodo10);
    Vnodo34.push_back(nodo11);
    Vnodo34.push_back(nodo12);

    Vnodo35.push_back(nodo0);
    Vnodo35.push_back(nodo1);
    Vnodo35.push_back(nodo2);

    Vnodo36.push_back(nodo19);
    Vnodo36.push_back(nodo14);

    nodo0.putnodo(Vnodo0);
    nodo1.putnodo(Vnodo1);
    nodo2.putnodo(Vnodo2);
    nodo3.putnodo(Vnodo3);
    nodo4.putnodo(Vnodo4);
    nodo5.putnodo(Vnodo5);
    nodo6.putnodo(Vnodo6);
    nodo7.putnodo(Vnodo7);
    nodo8.putnodo(Vnodo8);
    nodo9.putnodo(Vnodo9);
    nodo10.putnodo(Vnodo10);
    nodo11.putnodo(Vnodo11);
    nodo12.putnodo(Vnodo12);
    nodo13.putnodo(Vnodo13);
    nodo14.putnodo(Vnodo14);
    nodo15.putnodo(Vnodo15);
    nodo16.putnodo(Vnodo16);
    nodo17.putnodo(Vnodo17);
    nodo18.putnodo(Vnodo18);
    nodo19.putnodo(Vnodo19);
    nodo21.putnodo(Vnodo21);
    nodo22.putnodo(Vnodo22);
    nodo23.putnodo(Vnodo23);
    nodo25.putnodo(Vnodo25);
    nodo26.putnodo(Vnodo26);
    nodo27.putnodo(Vnodo27);
    nodo29.putnodo(Vnodo29);
    nodo30.putnodo(Vnodo30);
    nodo31.putnodo(Vnodo31);
    nodo32.putnodo(Vnodo32);
    nodo33.putnodo(Vnodo33);
    nodo34.putnodo(Vnodo34);
    nodo35.putnodo(Vnodo35);
    nodo36.putnodo(Vnodo36);

    std::vector<nodomap> nodos;
    nodos.push_back(nodo0);
    nodos.push_back(nodo1);
    nodos.push_back(nodo2);
    nodos.push_back(nodo3);
    nodos.push_back(nodo4);
    nodos.push_back(nodo5);
    nodos.push_back(nodo6);
    nodos.push_back(nodo7);
    nodos.push_back(nodo8);
    nodos.push_back(nodo9);
    nodos.push_back(nodo10);
    nodos.push_back(nodo11);
    nodos.push_back(nodo12);
    nodos.push_back(nodo13);
    nodos.push_back(nodo14);
    nodos.push_back(nodo15);
    nodos.push_back(nodo16);
    nodos.push_back(nodo17);
    nodos.push_back(nodo18);
    nodos.push_back(nodo19);
    nodos.push_back(nodo21);
    nodos.push_back(nodo22);
    nodos.push_back(nodo23);
    nodos.push_back(nodo25);
    nodos.push_back(nodo26);
    nodos.push_back(nodo27);
    nodos.push_back(nodo29);
    nodos.push_back(nodo30);
    nodos.push_back(nodo31);
    nodos.push_back(nodo32);
    nodos.push_back(nodo33);
    nodos.push_back(nodo34);
    nodos.push_back(nodo35);
    nodos.push_back(nodo36);

    return nodos;
}

class ComparadorNodo {
public:
    bool operator()(const nodomap& nodo1, const nodomap& nodo2) {
        return nodo1.total + nodo1.estimado > nodo2.total + nodo2.estimado;
    }
};

std::vector<nodomap> NodeMapSys::aEstrella(std::vector<nodomap> nodos, nodomap inicio, nodomap objetivo) {
    std::priority_queue<nodomap, std::vector<nodomap>, ComparadorNodo> frontera;
    inicio.total = 0;
    inicio.estimado = calcularDist(inicio, objetivo);
    frontera.push(inicio);

    std::vector<nodomap> visitados;
    

    while (!frontera.empty()) {
        nodomap nodoActual = frontera.top();
        frontera.pop();
        if (nodoActual.num == objetivo.num) {
            std::vector<nodomap> camino;
            while (nodoActual.num != inicio.num) {
                camino.push_back(nodoActual);
                nodoActual = *nodoActual.padre;
            }
            camino.push_back(inicio);
            return camino;
        }
        visitados.push_back(nodoActual);
        std::vector<int> numnodos;
        for(int i=0;i<visitados.size();i++){
            numnodos.push_back(visitados.at(i).num);
        }
        for (int j=0;j<nodoActual.nodos_adya.size();j++) {
            for(int i=0;i<nodos.size();i++){
                if(nodoActual.nodos_adya.at(j).num==nodos.at(i).num){
                    if(std::find(numnodos.begin(), numnodos.end(), nodos.at(i).num) != numnodos.end()){
                        continue;
                    }
                    float costoActual = nodoActual.total + 1;
                    float costoEstimado = costoActual + calcularDist(nodos.at(i), objetivo);
                    if ((nodos.at(i).padre == nullptr || costoEstimado < nodos.at(i).total + nodos.at(i).estimado)) {
                        nodos.at(i).total = costoActual;
                        nodos.at(i).estimado = calcularDist(nodos.at(i), objetivo);
                        for(int k=0;k<nodos.size();k++){
                            if(nodos.at(k).num==nodoActual.num)
                                nodos.at(i).padre = &nodos.at(k);
                        }
                        frontera.push(nodos.at(i));
                    }
                }
            }
        }
    }
    return std::vector<nodomap>();
}

float NodeMapSys::calcularDist(nodomap comienzo, nodomap fin){
    float dx=fin.coord.x-comienzo.coord.x;
    float dz=fin.coord.z-comienzo.coord.z;
    return std::sqrt(dx*dx+dz*dz);
}