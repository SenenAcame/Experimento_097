#pragma once
#include "UIsys.hpp"
#include "soundsystem.hpp"
#include <cstddef>

void UIsys::iniText(){

    zarpazo.setImage("assets/Interface/1280x720/zarpazo.png");
    inicio.setImage("assets/Interface/1280x720/pantalla_inicio_fondo.png");
    muerte.setImage("assets/Interface/1280x720/pantalla_muerto.png");
    controles.setImage("assets/Interface/1280x720/pantalla_controles.png");
    pausa.setImage("assets/Interface/1280x720/pantalla_pausa.png");
    
    //ICONS
    iconoEscopeta.setImage("assets/Interface/UI/arma escopeta.png");
    iconoPistola.setImage("assets/Interface/UI/arma pistola.png");
    iconoSubfusil.setImage("assets/Interface/UI/arma fusil.png");
    iconoRonda.setImage("assets/Interface/UI/rondas.png");
    iconoBajas.setImage("assets/Interface/UI/bajas.png");
    iconoMira.setImage("assets/Interface/1280x720/mira_borde.png");
    iconoVida.setImage("assets/Interface/UI/vida.png");
}

void UIsys::renderInterface(EntyMan& EM, GraphicEngine& GE, double dt) {
    //ImGui::Text("This is some useful text");
    auto* m_window = GE.getWindow();
    auto board = EM.getBoard();
    auto& player = EM.getEntityById(board.entyID);
    auto& invent = EM.getComponent<InventarioCmp>(player);
    auto stats     = EM.getComponent<EstadisticaCmp>(player);
    auto width     = GE.glEng.getWidth();
    auto height    = GE.glEng.getHeight();
   
    int magazine = 0;
    int ammo     = 0;
    double hp    = (double)stats.hitpoints/100;
    int wave     = board.progres.actualWave;
    int kills    = board.wave.kills;
    unsigned int iconWeaponID = 0;
    
    switch (invent.equipada) {
        case 0:
            magazine = invent.gun.magazine;
            ammo = invent.gun.ammo;
            iconWeaponID = iconoPistola.ID_;
            break;
        case 1: 
            magazine = invent.shot.magazine;
            ammo = invent.shot.ammo;
            iconWeaponID = iconoEscopeta.ID_;
            break;
        case 2: 
            magazine = invent.rifle.magazine;
            ammo = invent.rifle.ammo;
            iconWeaponID = iconoSubfusil.ID_;
            break;
    }

    renderInterfaceHits(GE, dt);

    ImGui::SetNextWindowPos(ImVec2(width/10*1-75,height/10*8.3-75));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIHPIcon", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconoVida.ID_, ImVec2(150,150));

    //ImGui::PopStyleColor();
    ImGui::End();


    ImGui::SetNextWindowPos(ImVec2(width/10*1.6,height/10*8.3));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIHP", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(255,0,0,255));
    //ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0,0,0,0));
    ImGui::ProgressBar(hp,ImVec2(250,40),"");

    //ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(width/2-150,height/2-100));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIMira", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconoMira.ID_, ImVec2(300,200));
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(width/2.38,0));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIiconWave", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconoRonda.ID_, ImVec2(200,100));
    ImGui::End();
    

    ImGui::SetNextWindowPos(ImVec2(width/2,10));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIWave", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Text("%d", wave);
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0,height/1.5));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIiconKills", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconoBajas.ID_, ImVec2(200,100));
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(width/10,height/1.5));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIKills", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    //ImGui::Text("Wave: %d", wave);
    ImGui::Text("%d", kills);
    //ImGui::Text("HP: %d", hp);
    //ImGui::Text("%d/%d", magazine, ammo );
    
    ImGui::SetNextWindowPos(ImVec2(width/1.4,height/1.4));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIiconWeapon", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconWeaponID, ImVec2(240,130));
    ImGui::End();

    ImGui::End();
    ImGui::SetNextWindowPos(ImVec2(width/1.2,height/1.3));
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
    ImGui::SetCursorPos(ImVec2(width/10*1.1,height/10*3));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Jugar", ImVec2(200,100))){
        
        next = 1;
    }
    ImGui::PopStyleColor();

    ImGui::SetCursorPos(ImVec2(width/10*1.1,height/10*4.5));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Sonido", ImVec2(200,100))){
        
        next = 5;
    }
    ImGui::PopStyleColor();

    ImGui::SetCursorPos(ImVec2(width/10*1.1,height/10*6));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Controles", ImVec2(200,100))){
        
        next = 4;
    }
    ImGui::PopStyleColor();

    ImGui::SetCursorPos(ImVec2(width/10*1.1,height/10*7.5));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Salir", ImVec2(200,100))){
        
        glfwSetWindowShouldClose(GE.getWindow(), GL_TRUE);
        next = 0;
    }
    ImGui::PopStyleColor();
 
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
            
            next = 3;
        }
        else{
            next = 0;
        }
        
    }
    ImGui::PopStyleColor();
    ImGui::End();

    return next;
}

size_t UIsys::menuSonido (GraphicEngine& GE, size_t next, SoundSystem_t& Sou){

    auto* m_window = GE.getWindow();
    auto width = GE.glEng.getWidth();
    auto height = GE.glEng.getHeight();
    auto masterPrevi = SoundMaster;
    
    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)inicio.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuSonido", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SliderFloat("Master", &SoundMaster, 0.0f, 1.0f); 
    ImGui::SliderFloat("Ambiente", &SoundAmbient, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("Musica", &SoundMusic, 0.0f, 1.0f);
    ImGui::SliderFloat("SFX", &SoundSFX, 0.0f, 1.0f);
    ImGui::SliderFloat("Voces", &SoundVoices, 0.0f, 1.0f);

    ImGui::SetCursorPos(ImVec2(height/2,width/3));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 0, 0,0)));
    if(ImGui::Button("Volver", ImVec2(200,100))){
        if(inGame == true){
            
            next = 3;
        }
        else{
            next = 0;
        }
        
    }
    ImGui::PopStyleColor();
    ImGui::End();

    if(masterPrevi != SoundMaster){
        Sou.changeMasterVCA(SoundMaster);
        SoundAmbient = SoundMaster;
        SoundMusic = SoundMaster;
        SoundSFX = SoundMaster;
        SoundVoices = SoundMaster;
    }
    
    Sou.changeVCA(0,SoundAmbient);
    Sou.changeVCA(1,SoundMusic);
    Sou.changeVCA(2,SoundSFX);
    Sou.changeVCA(3,SoundVoices);
    

    return next;
}

size_t UIsys::menuPausa (GraphicEngine& GE, size_t next, EntyMan& EM, SoundSystem_t& SouSys){
    EM.foreach<SoundCMPs, MAPTAGs>(
        [&](Enty& entity, SoundCmp& sound) {
            sound.play=true;
            sound.loop=true;
        }
    );
   
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