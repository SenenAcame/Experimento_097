#pragma once
#include "UIsys.hpp"

void UIsys::renderInterface(EntyMan& EM, GraphicEngine& GE, std::size_t player_ID, double dt) {
    //ImGui::Text("This is some useful text");
    auto* m_window = GE.getWindow();
    auto& player = EM.getEntityById(player_ID);
    auto& invent = EM.getComponent<InventarioCmp>(player);
    auto stats     = EM.getComponent<EstadisticaCmp>(player);
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();
   
    int magazine = 0;
    int ammo = 0;
    double hp = stats.hitpoints/100;
    int wave = 0;
    int kills = 0;
    
    switch (invent.equipada) {
        case 0:
            magazine = invent.gun.magazine;
            ammo = invent.gun.ammo;
            
            break;
        case 1: 
            magazine = invent.shot.magazine;
            ammo = invent.shot.ammo;
            
            break;
        case 2: 
            magazine = invent.rifle.magazine;
            ammo = invent.rifle.ammo;
            
            break;
    }
    renderInterfaceHits(GE, dt);

    ImGui::SetNextWindowPos(ImVec2(10,610));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIHP", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(255,0,0,255));
    //ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0,0,0,0));
    ImGui::ProgressBar(hp,ImVec2(300,40), "");

    //ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(10,545));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIWave", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    
    ImGui::Text("Wave: %d", wave);
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(10,490));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIKills", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    //ImGui::Text("Wave: %d", wave);
    ImGui::Text("Kills: %d", kills);
    //ImGui::Text("HP: %d", hp);
    //ImGui::Text("%d/%d", magazine, ammo );
    
    ImGui::End();
    ImGui::SetNextWindowPos(ImVec2(870,550));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIInventary", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    //ImGui::Text("Wave: %d", wave);
    //ImGui::Text("Kills: %d", kills);
    //ImGui::Text("HP: %d", hp);
    ImGui::Text("%d/%d", magazine, ammo );
    
    ImGui::End();

}

void UIsys::hitInterface(GraphicEngine& GE, Enty& player){

    int random = activateHit;
    while(activateHit==random)
        random = rand()%3+1;

    activateHit = random;
    
    switch (activateHit) {
        case 1: 
            hit1 = true;
        break;
        case 2: 
            hit2 = true;
        break;
        case 3: 
            hit3 = true;
        break;
    }
   
}

void UIsys::renderInterfaceHits(GraphicEngine& GE ,double dt){

    auto* m_window = GE.getWindow();
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();

    int randWidth = rand()%width;
    int randHeight = rand()%height;

    RTexture prueba("assets/Interface/1280x720/zarpazo.png");
    ImGui::SetNextWindowPos(ImVec2(randWidth,randHeight));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit1", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(hit1 == true){
        clockHit1 += dt;
        ImGui::Image((void*)(intptr_t)prueba.ID_, ImVec2(400, 350));
        if(clockHit1 >= cd) {
            hit1 = false;
            clockHit1 = 0;
        }
    }
    ImGui::End();

    randWidth = rand()%width;
    randHeight = rand()%height;
    ImGui::SetNextWindowPos(ImVec2(randWidth,randHeight));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit2", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(hit2 == true){
        clockHit2 += dt;
        ImGui::Image((void*)(intptr_t)prueba.ID_, ImVec2(400, 350));
        if(clockHit2 >= cd) {
            hit2 = false;
            clockHit2 = 0;
        }
    }
    ImGui::End();

    randWidth = rand()%width;
    randHeight = rand()%height;
    ImGui::SetNextWindowPos(ImVec2(randWidth,randHeight));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit3", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(hit3 == true){
        clockHit3 += dt;
        ImGui::Image((void*)(intptr_t)prueba.ID_, ImVec2(400, 350));
        if(clockHit3 >= cd) {
            hit3 = false;
            clockHit3 = 0;
        }
    }
    ImGui::End();
}