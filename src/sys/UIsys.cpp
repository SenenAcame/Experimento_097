#pragma once
#include "UIsys.hpp"
#include <cstddef>

void UIsys::iniText(){

    zarpazo.setImage("assets/Interface/1280x720/zarpazo.png");
    inicio.setImage("assets/Interface/1280x720/pantalla_inicio_fondo.png");
    muerte.setImage("assets/Interface/1280x720/pantalla_muerto.png");
    controles.setImage("assets/Interface/1280x720/pantalla_controles.png");
    pausa.setImage("assets/Interface/1280x720/pantalla_pausa.png");
}

void UIsys::renderInterface(EntyMan& EM, GraphicEngine& GE, std::size_t player_ID, double dt) {
    //ImGui::Text("This is some useful text");
    auto* m_window = GE.getWindow();
    auto& player = EM.getEntityById(player_ID);
    auto& invent = EM.getComponent<InventarioCmp>(player);
    auto stats     = EM.getComponent<EstadisticaCmp>(player);
    auto width     = GE.glEng.getWidth();
    auto height    = GE.glEng.getHeight();
   
    int magazine = 0;
    int ammo     = 0;
    double hp    = stats.hitpoints/100;
    int wave     = 0;
    int kills    = 0;
    
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

void UIsys::hitInterface(GraphicEngine& GE){

    auto* m_window = GE.getWindow();
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();
    int random = activateHit;
    while(activateHit == random)
        random = rand()%3+1;

    activateHit = random;
    
    switch (activateHit) {
        case 1: 
            hit1 = true;
            randWidth1 = rand()%width;
            randHeight2 = rand()%height;
        break;
        case 2: 
            hit2 = true;
            randWidth2 = rand()%width;
            randHeight2 = rand()%height;
        break;
        case 3: 
            hit3 = true;
            randWidth3 = rand()%width;
            randHeight3 = rand()%height;
        break;
    }
}

void UIsys::renderInterfaceHits(GraphicEngine& GE ,double dt){
    auto* m_window = GE.getWindow();
    auto width  = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();

    
    ImGui::SetNextWindowPos(ImVec2(randWidth1,randHeight2));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit1", NULL,
         ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(hit1 == true) {
        clockHit1 += dt;
        ImGui::Image((void*)(intptr_t)zarpazo.ID_, ImVec2(600, 450));
        if(clockHit1 >= cd) {
            hit1 = false;
            clockHit1 = 0;
        }
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(randWidth2,randHeight2));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit2", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(hit2 == true) {
        clockHit2 += dt;
        ImGui::Image((void*)(intptr_t)zarpazo.ID_, ImVec2(800, 750));
        if(clockHit2 >= cd) {
            hit2 = false;
            clockHit2 = 0;
        }
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(randWidth3,randHeight3));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit3", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(hit3 == true) {
        clockHit3 += dt;
        ImGui::Image((void*)(intptr_t)zarpazo.ID_, ImVec2(850, 800));
        if(clockHit3 >= cd) {
            hit3 = false;
            clockHit3 = 0;
        }
    }
    ImGui::End();
}

size_t UIsys::menuIni (GraphicEngine& GE, size_t next){

    
    auto* m_window = GE.getWindow();
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)inicio.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuIni", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SetCursorPos(ImVec2(height/2,width/3));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    //ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0,0,0,0)));
    if(ImGui::Button("Jugar", ImVec2(200,100))){
        next = 1;
    }
    ImGui::PopStyleColor();

    ImGui::SetCursorPos(ImVec2(height/2,width/4));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    //ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0,0,0,0)));
    if(ImGui::Button("Controles", ImVec2(200,100))){
        next = 4;
    }
    ImGui::PopStyleColor();
    //ImGui::PopStyleColor();
    //ImGui::Text("Hola");
    //ImGui::Image((void*)(intptr_t)inicio.ID_, ImVec2(width, height));
 
    ImGui::End();
    //ImGui::PopStyleVar();
    return next;
}

size_t UIsys::menuMuerto (GraphicEngine& GE, size_t next){
    
    auto* m_window = GE.getWindow();
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)muerte.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuMuerto", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SetCursorPos(ImVec2(height/2,width/3));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Jugar", ImVec2(200,100))){
        next = 0;
    }
    ImGui::PopStyleColor();
 
    ImGui::End();

    return next;
}

size_t UIsys::menuControles (GraphicEngine& GE, size_t next){

    auto* m_window = GE.getWindow();
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)controles.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuIni", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SetCursorPos(ImVec2(height/2,width/3));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Volver", ImVec2(200,100))){
        if(inGame == true){
            next = 1;
        }
        else{
            next = 0;
        }
        
    }
    ImGui::PopStyleColor();
    ImGui::End();

    return next;
}

size_t UIsys::menuSonido (GraphicEngine& GE, size_t next){

    auto* m_window = GE.getWindow();
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)controles.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuSonido", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SetCursorPos(ImVec2(height/2,width/3));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Volver", ImVec2(200,100))){
        if(inGame == true){
            next = 1;
        }
        else{
            next = 0;
        }
        
    }
    ImGui::PopStyleColor();
    ImGui::End();

    return next;
}

size_t UIsys::menuPausa (GraphicEngine& GE, size_t next){
    
    //0 Ini 1 game 2 dead 3 pause 4 controls 5 sound
    auto* m_window = GE.getWindow();
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)pausa.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuIni", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SetCursorPos(ImVec2(height/1.7,width/6.4));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Reanudar", ImVec2(200,100))){
        
        next = 1;
    }
    ImGui::PopStyleColor();

    ImGui::SetCursorPos(ImVec2(height/1.7,width/4.4));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Sonido", ImVec2(200,100))){
        
        next = 5;
    }
    ImGui::PopStyleColor();

    ImGui::SetCursorPos(ImVec2(height/1.7,width/3.4));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Controles", ImVec2(200,100))){
        
        next = 4;
    }
    ImGui::PopStyleColor();

    ImGui::SetCursorPos(ImVec2(height/1.7,width/2.4));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Salir", ImVec2(200,100))){
        
        next = 0;
    }
    ImGui::PopStyleColor();
 
 
    ImGui::End();

    return next;
}