#include "levelman.hpp"
#include "../eng/engine2.hpp"
#include "../sys/nodemapsys.hpp"
#include "../sys/soundsystem.hpp"
#include <cmath>
#include "../sys/partsys.hpp"
#include <cstddef>
#include <string>
#include <vector>

/*NUEVO*/ size_t LevelMan::createMap2(GraphicEngine& GE, SoundSystem_t& SouSys) {
    unsigned int const size = 13;

    std::string models [size] {
        "assets/models/mapas/Patio.obj",
        "assets/models/mapas/Sala_1.obj",
        "assets/models/mapas/Sala_2.obj",
        "assets/models/mapas/Sala_3.obj",
        "assets/models/mapas/Sala_4.obj",
        "assets/models/mapas/Sala_5.obj",
        "assets/models/mapas/Pasillo_1.obj",
        "assets/models/mapas/Pasillo_2.obj",
        "assets/models/mapas/Pasillo_3.obj",
        "assets/models/mapas/Pasillo_4.obj",
        "assets/models/mapas/Pasillo_5.obj",
        "assets/models/mapas/Pasillo_6.obj",
        "assets/models/mapas/Pasillo_7.obj"
    };

    Enty& map = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(map);
    EM.addComponent<NodoCmp>    (map, NodoCmp{.salas = NodeMapSys::creaSalas(), .nodos=NodeMapSys::creaNodos()});
    EM.addComponent<SoundCmp>   (map, SoundCmp{.programmerSoundContext = SouSys.createinstance(0), .parametro = 0, .play = true, .loop=true});
    EM.addTag<TMap>(map);

    for(int i = 0; i < size; i++) {
        Enty& room = EM.createEntity();
        EM.addComponent<PhysicsCmp2>(room, PhysicsCmp2 {});
        EM.addComponent<RenderCmp2> (room, RenderCmp2 { .node = GE.createNode(models[i]) });
    }

    return map.getID();
}

/*NUEVO*/ size_t LevelMan::createPlayer2(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys) {
    std::string file_model = "assets/models/armas/pistola.obj";

    Enty& player = EM.createEntity();
    //CMPS
    EM.addComponent<PhysicsCmp2>   (player, PhysicsCmp2 { .x = pos.x, .y = pos.y, .z = pos.z });
    EM.addComponent<RenderCmp2>    (player, RenderCmp2 { .node = GE.createPlayer() });
    EM.addComponent<InputCmp2>     (player, InputCmp2 {});
    EM.addComponent<EstadoCmp>     (player, 1.f, 3.f, 1.f);
    EM.addComponent<EstadisticaCmp>(player, EstadisticaCmp{ .hitpoints=100, .damage=5, .speed=40.f });
    EM.addComponent<InventarioCmp> (player);
    EM.addComponent<SalaCmp>       (player);
    EM.addComponent<SoundCmp>      (player, SouSys.createinstance(9));
    //TAGS
    EM.addTag<TPlayer>  (player);
    EM.addTag<TInteract>(player);

    GE.setCameraPlayer(file_model);

    //viewBB(GE, player);

    return player.getID();
}

/*NUEVO*/ Enty& LevelMan::createEnemy(GraphicEngine &GE, Vec3 pos, SoundSystem_t &SouSys, Type_Enemy type, ExtraStats plus) {
    switch (type) {
        case Type_Enemy::Normal:
            //createNormalEnemy(GE, Vec3{ pos.x, 2.8, pos.z }, SouSys, plus);
            createNormalEnemyAnim(GE, Vec3{ pos.x, 2.5, pos.z }, SouSys, plus);
            break;
        case Type_Enemy::Tank:
            //createTankEnemy2(GE, Vec3{ pos.x, 2.8, pos.z }, SouSys, plus);
            createNormalEnemyAnim(GE, Vec3{ pos.x, 2.5, pos.z }, SouSys, plus);
            break;
        case Type_Enemy::Distance:
            createDistanceEnemy(GE, Vec3{ pos.x, 2.5, pos.z }, SouSys, plus);
            break;
    }
}

///*NUEVO*/ Enty& LevelMan::createNormalEnemy(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, /*PartSys& PartSys,*/ ExtraStats plus) {
//    std::string file_model = "assets/models/personajes/monstruo2/enemigo2.obj";
//    Vec3 base_stats = { 20, 20, 4 };
//    
//    Enty& enemy = EM.createEntity();
//    //CMPS 
//    defineAI(enemy, SB::Two_Steps, 0.1);
//    auto& stats = EM.addComponent<EstadisticaCmp>(
//        enemy, 
//        EstadisticaCmp { 
//            .hitpoints = static_cast<int>(base_stats.x * plus.life.extra), 
//            .damage    = static_cast<int>(base_stats.y * plus.damg.extra), 
//            .speed     = base_stats.z * plus.sped.extra 
//        }
//    );
//
//    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2 { .x = pos.x, .y = pos.y, .z = pos.z, .kMxVLin = stats.speed });
//    EM.addComponent<RenderCmp2> (enemy, RenderCmp2 { .node = GE.createNode(file_model) });
//    EM.addComponent<EstadoCmp>  (enemy, 0.7f, 1.5f, 0.7f);
//    EM.addComponent<SoundCmp>   (enemy, SouSys.createinstance(7));
//    EM.addComponent<SalaCmp>    (enemy);
//
//    //auto &part = EM.addComponent<ParticleCMP> (enemy);
//    //PartSys.setParticle(part, "assets/textures/partExplosion.png", 100, 0, 0.f, 1.0f, {.5f, 1.f, .5f}, 3.f, 0.f, 0.1f, -8.f);
//
//    //TAGS
//    EM.addTag<TInteract>(enemy);
//    EM.addTag<TEnemy>   (enemy);
//
//    //viewBB(GE, enemy);
//
//    return enemy;
//}

/*NUEVO*/ Enty& LevelMan::createNormalEnemyAnim(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus) {
    std::string file_model        = "assets/models/personajes/monstruo2/enemigo2.obj";
    std::vector<std::string> anim = { "monstruo2/caminar/monstruo2_caminar", "monstruo2/caminar/monstruo2_caminar" };
    std::vector<int> framesAnim   = { 111, 111 };
    Vec3 base_stats = { 20, 20, 4 };

    Enty& enemy = EM.createEntity();
    //CMPS
    defineAI(enemy, SB::Two_Steps, 0.1);

    auto& stats = EM.addComponent<EstadisticaCmp>(
        enemy, 
        EstadisticaCmp { 
            .hitpoints = static_cast<int>(base_stats.x * plus.life.extra), 
            .damage    = static_cast<int>(base_stats.y * plus.damg.extra), 
            .speed     = base_stats.z * plus.sped.extra 
        }
    );
    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2 { .x = pos.x, .y = pos.y, .z = pos.z, .kMxVLin = stats.speed });

    auto& rend = EM.addComponent<RenderCmp2>(enemy, RenderCmp2 { .node = GE.createNodeAnim(file_model, anim, framesAnim) });
    rend.node->getEntity<EModel>()->currentAnim = 0;

    EM.addComponent<EstadoCmp>(enemy, 0.7f, 1.5f, 0.7f);
    EM.addComponent<SoundCmp> (enemy, SouSys.createinstance(7));
    EM.addComponent<SalaCmp>  (enemy);
    //TAGS
    EM.addTag<TInteract>(enemy);
    EM.addTag<TEnemy>(enemy);

    //viewBB(GE, enemy);

    return enemy;
}

/*NUEVO*/ Enty& LevelMan::createTankEnemy2(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus) {
    std::string file_model = "assets/models/personajes/monstruo3/monstruo_3_grande_caminar.fbx";
    Vec3 base_stats = { 20, 20, 4 };
    
    Enty& enemy = EM.createEntity();
    //CMPS 
    defineAI(enemy, SB::Two_Steps, 0.1);
    auto& stats = EM.addComponent<EstadisticaCmp>(
        enemy, 
        EstadisticaCmp { 
            .hitpoints = static_cast<int>(base_stats.x * plus.life.extra), 
            .damage    = static_cast<int>(base_stats.y * plus.damg.extra), 
            .speed     = base_stats.z * plus.sped.extra 
        }
    );

    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2 { .x = pos.x, .y = pos.y, .z = pos.z, .kMxVLin = stats.speed });
    EM.addComponent<RenderCmp2> (enemy, RenderCmp2 { .node = GE.createNode(file_model) });
    EM.addComponent<EstadoCmp>  (enemy, 1.f, 1.5f, 1.f);
    EM.addComponent<SoundCmp>   (enemy, SouSys.createinstance(7));
    EM.addComponent<SalaCmp>    (enemy);
    //TAGS
    EM.addTag<TInteract>(enemy);
    EM.addTag<TEnemy>   (enemy);

    //viewBB(GE, enemy);

    return enemy;
}

/*NUEVO*/ Enty& LevelMan::createDistanceEnemy(GraphicEngine& GE, Vec3 pos, SoundSystem_t& SouSys, ExtraStats plus) {
    std::string file_model = "assets/models/personajes/monstruo1/enemigo1.obj";
    Vec3 base_stats = { 10, 30, 5 };
    
    Enty& enemy = EM.createEntity();
    //CMPS
    defineAI(enemy, SB::Shoot, 1.);
    auto& stats = EM.addComponent<EstadisticaCmp>(
        enemy, 
        EstadisticaCmp{ 
            .hitpoints = static_cast<int>(base_stats.x * plus.life.extra), 
            .damage    = static_cast<int>(base_stats.y * plus.damg.extra), 
            .speed     = base_stats.z * plus.sped.extra 
        }
    );

    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2 { .x = pos.x, .y = pos.y, .z = pos.z, .kMxVLin = stats.speed });
    EM.addComponent<RenderCmp2> (enemy, RenderCmp2  { .node = GE.createNode(file_model) });
    EM.addComponent<EstadoCmp>  (enemy, .7f, 1.2f, .7f);
    EM.addComponent<SoundCmp>   (enemy, SouSys.createinstance(7));
    EM.addComponent<SalaCmp>    (enemy);
    //TAGS
    EM.addTag<TInteract> (enemy);
    EM.addTag<TEnemy>    (enemy);
    EM.addTag<TDistEnemy>(enemy);

    //viewBB(GE, enemy);

    return enemy;
}

TNodo* LevelMan::createModelHitbox(GraphicEngine& GE, Vec3 pos, Vec3 scale, TNodo* padre) {
    std::string file_model = "assets/models/otros/untitled.obj";
    return GE.glEng.createModel(padre, pos, Vec3(0.f), scale, file_model);
}

void LevelMan::viewBB(GraphicEngine& GE, Enty& ent){
    auto& bb = EM.getComponent<EstadoCmp>(ent);
    auto& pos_ent = EM.getComponent<PhysicsCmp2>(ent);
    auto& node_ent = EM.getComponent<RenderCmp2>(ent);
                        //pos = 0,0,0   //tamaño collider               //nodoPadre
    createModelHitbox(GE, Vec3(0), Vec3{bb.width, bb.height, bb.depth}, node_ent.node);
}


/*NUEVO*/ void LevelMan::createBullet2(GraphicEngine& GE, PhysicsCmp2& pos, EstadisticaCmp&& stats, 
Vec3 dir, SoundSystem_t& SouSys, double const slfD, double const pbx, double const pby) {
    std::string file_model = "assets/models/armas/bala.obj";

    auto* model = GE.playerModel;
    auto mat  = model->matTransf_;

    Vec3 pos_b = { mat[3][0], mat[3][1], mat[3][2]
        ///*X*/ tras.x * cos(pos.orieny) + tras.y * 0 + tras.z * (-sin(pos.orieny)),
        ///*Y*/ tras.x * 0               + tras.y * 0 + tras.z * 0,
        ///*Z*/ tras.x * sin(pos.orieny) + tras.y * 0 + tras.z * cos(pos.orieny)

        ///*X*/ tras.x * cos(pos.orieny) * cos(pos.orienx) + tras.y * sin(pos.orienx) + tras.z * (-sin(pos.orieny)),
        ///*Y*/ tras.x * (-sin(pos.orienx))                + tras.y * cos(pos.orienx) + tras.z * (-sin(pos.orienx)),
        ///*Z*/ tras.x * sin(pos.orieny)                   + tras.y * 0               + tras.z * cos(pos.orieny) * cos(pos.orienx)
    };

    Enty& bullet = EM.createEntity();
    //CMPS
    EM.addComponent<EstadisticaCmp>(bullet, stats);
    EM.addComponent<PhysicsCmp2>(bullet, PhysicsCmp2 { 
        .x = pos_b.x, .y = pos_b.y, .z = pos_b.z,
        .vx = stats.speed * cos(pos.orienx + pbx) * cos(pos.orieny + pby),
        .vy = stats.speed * sin(pos.orienx + pbx), 
        .vz = stats.speed * cos(pos.orienx + pbx) * sin(pos.orieny + pby) 
    });
    EM.addComponent<RenderCmp2> (bullet, RenderCmp2 { .node = GE.createNode(file_model) });
    EM.addComponent<EstadoCmp>  (bullet);
    EM.addComponent<SelfDestCmp>(bullet, slfD);
    EM.addComponent<SoundCmp>   (bullet, SoundCmp{ .programmerSoundContext=SouSys.createinstance(1), .parametro=2, .play=true, .cambia=true });
    //TAGS
    EM.addTag<TBullet>  (bullet);
    EM.addTag<TInteract>(bullet);
}


/*NUEVO*/ void LevelMan::createShotgunBullets2(GraphicEngine& GE, PhysicsCmp2& pos, EstadisticaCmp&& stats, 
Vec3 dir, SoundSystem_t& SouSys, double const slfD, uint8_t dispersion) {
    for(uint8_t i = 0; i < 10; i++) {
        //TwoAngles disp_angs = disperShotgun(dispersion);
        //std::cout<<"Normalizado: "<<disp_angs.alfa<<" "<<disp_angs.beta<<"\n";
        //createBullet2(GE, pos, EstadisticaCmp{stats}, dir, SouSys, slfD, disp_angs.alfa, disp_angs.beta);

        double ang_alp = randAng(dispersion);
        double ang_bet = randAng(dispersion);
        //std::cout<<"Sin normalizar: "<<ang_alp<<" "<<ang_bet<<"\n";
        createBullet2(GE, pos, EstadisticaCmp{stats}, dir, SouSys, slfD, ang_alp, ang_bet);
    }
    //std::cout<<"\n";
}

/*NUEVO*/ void LevelMan::createEneBullet(GraphicEngine& GE, PhysicsCmp2&& phy, int dmg) {
    std::string file_model = "assets/models/personajes/monstruo1/bala_ene.obj";

    Enty& bullet = EM.createEntity();
    auto& stats = EM.addComponent<EstadisticaCmp>(
        bullet, EstadisticaCmp{ .damage = dmg, .speed = 0.2f }
    ); 
    EM.addComponent<PhysicsCmp2>(
        bullet, PhysicsCmp2{
            .x  = phy.x, .y = phy.y, .z = phy.z,
            .vx = phy.vx * stats.speed,
            .vz = phy.vz * stats.speed
        }
    );
    EM.addComponent<RenderCmp2> (bullet, RenderCmp2 { .node = GE.createNode(file_model) });
    EM.addComponent<EstadoCmp>  (bullet);
    EM.addComponent<SelfDestCmp>(bullet, SelfDestCmp{ .cooldown = 5. });
    EM.addTag<TEneBullet>(bullet);
    EM.addTag<TInteract> (bullet);
}


/*NUEVO*/ Enty& LevelMan::createWeapon2(GraphicEngine& GE, Vec3 pos, W_Type tipo, SoundSystem_t& SouSys) {
    TNodo* model = nullptr;

    Enty& weapon = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(weapon, PhysicsCmp2{ .x = pos.x, .y = pos.y, .z = pos.z });
    switch (tipo) {
        case W_Type::Pistol:
            model = GE.createNode("assets/models/armas/pistola.obj");
            EM.addComponent<WeaponCmp> (weapon, 0);
            break;
        case W_Type::Shotgun:
            model = GE.createNode("assets/models/armas/escopeta.obj");
            EM.addComponent<WeaponCmp> (weapon, 1);
            break;
        case W_Type::Fusil:
            model = GE.createNode("assets/models/armas/subfusil.obj");
            EM.addComponent<WeaponCmp> (weapon, 2);
            break;
    }
    EM.addComponent<RenderCmp2>(weapon, RenderCmp2 { .node = model });
    EM.addComponent<SoundCmp>  (weapon, SouSys.createinstance(1));
    EM.addComponent<EstadoCmp> (weapon, 1.f, 1.f, 1.f); 
    EM.addTag      <TWeapon>   (weapon);
    EM.addTag      <TInteract> (weapon);
    return weapon;
}

void LevelMan::createHitBox(double const pos_x, double const pos_y, double const pos_z, float const width, float const height, float const depth) {
    Enty& wall = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(wall, pos_x, pos_y,  pos_z);
    EM.addComponent<EstadoCmp>  (wall, width, height, depth);
    EM.addTag<TInteract>(wall);
    EM.addTag<TWall>    (wall);
    
}

//Enty& LevelMan::createSmallEnemy(float x_pos, float z_pos, TheEngine& dev, SoundSystem_t& SouSys) {
//    Enty& enemy = createEnemy(SouSys);
//    auto& stats = EM.addComponent<EstadisticaCmp>(enemy, EstadisticaCmp{.hitpoints=100, .damage=20, .speed=3.f});
//    
//    EM.addComponent<PhysicsCmp2>(enemy, PhysicsCmp2{.x=x_pos, .y=2.33, .z=z_pos, .kMxVLin = stats.speed});
//    EM.addComponent<RenderCmp2> (enemy, dev.createModel("assets/models/monstruo1.obj","assets/textures/faerie2.bmp"));
//    EM.addComponent<EstadoCmp>  (enemy, 0.875f, 2.33f, 0.85f);
//    EM.addTag      <TSmallEnemy>(enemy);
//    return enemy;
//}

Enty& LevelMan::createEneSpawn(Vec3 pos, GraphicEngine& GE, int room, double timer){
    Enty& spawn = createSpawn2(pos, GE, room, timer);
    EM.addTag<TSpwEnemy>(spawn);
    return spawn;
}

Enty& LevelMan::createWpnSpawn(Vec3 pos, GraphicEngine& GE, int room, double timer){
    Enty& spawn = createSpawn2(pos, GE, room, timer);
    EM.addTag<TSpwWeapon>(spawn);
    return spawn;
}

Enty& LevelMan::createSpawn2(Vec3 pos, GraphicEngine& GE, int room, double timer){
    Enty& spawn = EM.createEntity();
    EM.addComponent<SalaCmp>    (spawn, SalaCmp { .sala = room });
    EM.addComponent<PhysicsCmp2>(spawn, PhysicsCmp2 { .x = pos.x, .z = pos.z });
    EM.addComponent<SpawnCmp>   (spawn, SpawnCmp { .timer = timer });
    EM.addTag      <TSpawn>     (spawn);
    return spawn;
}

Enty& LevelMan::createPowerUp(GraphicEngine& GE, PhysicsCmp2& phy) {
    std::string file_model = "assets/models/powerup/powerup.obj";

    Enty& power = EM.createEntity();
    EM.addComponent<PhysicsCmp2>(power, PhysicsCmp2 { .x = phy.x, .y = 2., .z = phy.z   });
    EM.addComponent<RenderCmp2> (power, RenderCmp2  { .node = GE.createNode(file_model) });
    EM.addComponent<EstadoCmp>  (power);
    EM.addComponent<SelfDestCmp>(power, 5.);
    EM.addTag      <TInteract>  (power);
    EM.addTag      <TPowerUp>   (power);
    return power;
}

void LevelMan::resetLevel() {
    EM.forall(
        [](Enty& ent) {
            bool is_enemy_bullet_or_player = 
                ent.hasTAG<TEnemy>()  ||
                ent.hasTAG<TBullet>() ||
                ent.hasTAG<TWeapon>() ||
                ent.hasTAG<TSpawn>();

            if(is_enemy_bullet_or_player) ent.setDestroy();
           
        }
    );

    EM.callDestroy();
}

TwoAngles LevelMan::disperShotgun(uint8_t disp) {
    double mod = (rand() % 2 - 1) / 10;
    std::cout<<mod<<"\n";

    TwoAngles angs {};

    angs.alfa = randAng(disp);
    angs.beta = randAng(disp);

    angs = normalize(angs);

    angs.alfa *= mod;
    angs.beta *= mod;

    return angs;
}

TwoAngles LevelMan::normalize(TwoAngles angs) {
    double module = std::sqrt(angs.alfa*angs.alfa + angs.beta*angs.beta);
    angs.alfa /= module;
    angs.beta /= module;
    return angs;
}

void LevelMan::defineAI(Enty& enemy, SB patron, double cd) {
    int    num    = rand() % 360;
    double angle  = num * PI / 180;
    double radius = 5.;

    EM.addComponent<AICmp>(
        enemy, 
        AICmp {
            .rad           = radius,
            .ang           = angle,
            .flock_x       = cos(angle) * radius, 
            .flock_z       = sin(angle) * radius, 
            .arrivalRadius = 0.5, 
            .timeArrive    = 0.1, 
            .cooldown      = cd, 
            .enable        = true, 
            .behaviour     = patron
        }
    );
}

double LevelMan::randAng(uint8_t ang) {
    float  alpha = rand() % ang - (ang / 2);
    return alpha * PI / 180;
}