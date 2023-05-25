#include "UIsys.hpp"
#include "soundsystem.hpp"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <string>

void UIsys::iniText(GraphicEngine& GE){

    zarpazo.setImage("assets/Interface/UI/zarpazo.png");
    zarpazo1.setImage("assets/Interface/UI/zarpazo_dir.png");
    golpe.setImage("assets/Interface/UI/degradado.png");

    inicio.setImage("assets/Interface/1280x720/pantalla_inicio_fondo.png");
    muerte.setImage("assets/Interface/1280x720/pantalla_muerto.png");
    controles.setImage("assets/Interface/1280x720/pantalla_controles.png");
    pausa.setImage("assets/Interface/1280x720/pantalla_pausa.png");
    cargando.setImage("assets/Interface/1280x720/pantalla_cargando.png");
    
    //ICONS
    iconoEscopeta.setImage("assets/Interface/UI/capsula escopeta pequeño.png");
    iconoPistola.setImage("assets/Interface/UI/capsula pistola pequeño.png");
    iconoSubfusil.setImage("assets/Interface/UI/capsula fusil.png");
    iconoRonda.setImage("assets/Interface/UI/rondas.png");
    iconoBajas.setImage("assets/Interface/UI/bajas.png");
    iconoMira.setImage("assets/Interface/1280x720/mira_borde.png");
    iconoVida.setImage("assets/Interface/UI/vida.png");
    iconoPower.setImage("assets/Interface/UI/icono_powerup.png");
    iconoSpeed.setImage("assets/Interface/UI/icono_ala.png");

    moveX=GE.getWidth()/2;
    moveY=GE.getHeight()/2.5;
}

void UIsys::renderInterface(EntyMan& EM, GraphicEngine& GE, double dt) {
    //ImGui::Text("This is some useful text");
    auto board      = EM.getBoard();
    auto& player  = EM.getEntityById(board.entyID);
    auto& invent  = EM.getComponent<InventarioCmp>(player);
    auto stats      = EM.getComponent<EstadisticaCmp>(player);
    auto width  = GE.getWidth();
    auto height = GE.getHeight();
    auto inRound    = board.progres.inRound;

    if(inRound == false){
        moveY = moveY-1.4;
    }
    else if(moveY!=GE.getHeight()/2.5){
        moveY = GE.getHeight()/2.5;
    }

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

    if(inRound == false){
        
        ImGui::SetNextWindowPos(ImVec2(moveX,moveY));
        ImGui::SetNextWindowSize(ImVec2(width,height));
        ImGui::Begin(
            "UIPRUEBANEXTROUND", NULL,
            ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
            | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
        );
        ImGui::Text("%d", wave+1);

        //ImGui::PopStyleColor();
        ImGui::End();
    }

    ImGui::SetNextWindowPos(ImVec2(0,height/10*8.3-75));
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

    ImGui::SetNextWindowPos(ImVec2(0+25,height/10*5-25));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIPowerIcon", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconoPower.ID_, ImVec2(50,50));
    

    //ImGui::PopStyleColor();
    ImGui::End();
    
    ImGui::SetNextWindowPos(ImVec2(width/10*0.5,height/10*5-40));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIPowerText", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Text(" : %d", board.progres.powerDamage);

    //ImGui::PopStyleColor();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(0+25,height/10*4-25));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UISpeedIcon", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconoSpeed.ID_, ImVec2(50,50));

    //ImGui::PopStyleColor();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(width/10*0.5,height/10*4-40));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UISpeedText", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Text(" : %d", board.progres.powerSpeed);

    //ImGui::PopStyleColor();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(width/10*2-95,height/10*8.3-20));
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

    ImGui::SetNextWindowPos(ImVec2(width/2-90,0));
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

    ImGui::SetNextWindowPos(ImVec2(0,height/10*6.5-75));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIiconKills", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconoBajas.ID_, ImVec2(250,150));
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(width/10-20,height/10*5.9));
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
    
    ImGui::SetNextWindowPos(ImVec2(width/10*8.2-250,height/10*7.5-125));
    ImGui::SetNextWindowSize(ImVec2(width,height));
    ImGui::Begin(
        "UIiconWeapon", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    ImGui::Image((void*)(intptr_t)iconWeaponID, ImVec2(500,300));
    ImGui::End();

    ImGui::End();
    ImGui::SetNextWindowPos(ImVec2(width/10*7.7,height/10*7.9));
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
    float defaultFont = ImGui::GetFont()->Scale;
    ImGui::GetFont()->Scale *=0.9;
    ImGui::PushFont(ImGui::GetFont());
    ImGui::Text("%d/%d", magazine, ammo );
    ImGui::GetFont()->Scale =defaultFont;
    ImGui::PopFont();
    
    ImGui::End();
}

void UIsys::hitInterface(GraphicEngine& GE){

    auto* m_window = GE.getWindow();
    auto width = GE.getWidth();
    auto height = GE.getHeight();
    int random = activateHit;
    while(activateHit == random)
        random = rand()%3+1;

    activateHit = random;
    
    switch (activateHit) {
        case 1: 
            if(hit1==false){
                hit1 = true;
                randWidth1 = rand()%width;
                randHeight2 = rand()%height;
                if(redHit == false){
                    redHit = true;
                }
            }
        break;
        case 2: 
            if(hit2==false){
                hit2 = true;
                randWidth2 = rand()%width;
                randHeight2 = rand()%height;
                if(redHit == false){
                        redHit = true;
                }
            }
        break;
        case 3: 
            if(hit3==false){
                hit3 = true;
                randWidth3 = rand()%width;
                randHeight3 = rand()%height;
                if(redHit == false){
                        redHit = true;
                }
            }
        break;
    }
}

void UIsys::renderInterfaceHits(GraphicEngine& GE ,double dt){
    auto* m_window = GE.getWindow();
    auto width  = GE.getWidth();
    auto height = GE.getHeight();
    

    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit1", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(redHit == true) {
        clockGolpe += dt;
        ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)golpe.ID_, ImVec2(0, 0), ImVec2(width, height));
        if(clockGolpe >= cdG) {
            redHit = false;
            clockGolpe = 0;
        }
        
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2((randWidth1-300)/2,(randHeight2-225)/2));
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

    ImGui::SetNextWindowPos(ImVec2((randWidth1-300)/2,(randHeight2-225)/2));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit2", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(hit2 == true) {
        clockHit2 += dt;
        ImGui::Image((void*)(intptr_t)zarpazo1.ID_, ImVec2(700, 600));
        if(clockHit2 >= cd) {
            hit2 = false;
            clockHit2 = 0;
        }
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2((randWidth1-300)/2,(randHeight2-225)/2));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "Hit3", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus
    );
    if(hit3 == true) {
        clockHit3 += dt;
        ImGui::Image((void*)(intptr_t)zarpazo.ID_, ImVec2(650, 500));
        if(clockHit3 >= cd) {
            hit3 = false;
            clockHit3 = 0;
        }
    }
    ImGui::End();
}

size_t UIsys::menuIni (GraphicEngine& GE, size_t next){

    auto* m_window = GE.getWindow();
    auto width = GE.getWidth();
    auto height = GE.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)inicio.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuIni", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
    ImGui::SetCursorPos(ImVec2(width/10*1.1,height/10*3));
    if(ImGui::Button("Jugar", ImVec2(300,100))) {
        next = 1;
    }
    

    ImGui::SetCursorPos(ImVec2(width/10*1.1,height/10*4.5));
    
    if(ImGui::Button("Sonido", ImVec2(300,100))) {
        next = 5;
    }

    ImGui::SetCursorPos(ImVec2(width/10*1.1,height/10*6));
    if(ImGui::Button("Controles", ImVec2(300,100))) {
        next = 4;
    }

    ImGui::SetCursorPos(ImVec2(width/10*1.1,height/10*7.5));
    if(ImGui::Button("Salir", ImVec2(300,100))) {
        GE.setWindowClose();
        next = 0;
    }
    
    ImGui::PopStyleVar();
    ImGui::End();
   
    //ImGui::PopStyleVar();
    return next;
}

size_t UIsys::menuMuerto (GraphicEngine& GE, size_t next){
    
    
    auto* m_window = GE.getWindow();
    auto width = GE.getWidth();
    auto height = GE.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)muerte.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuMuerto", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SetCursorPos(ImVec2(width/10*7,height/10*4));
    if(ImGui::Button("Jugar", ImVec2(300,100))){
        next = 1;
    }
    ImGui::SetCursorPos(ImVec2(width/10*7,height/10*6));
    if(ImGui::Button("Inicio", ImVec2(300,100))){
        next = 0;
    }
    ImGui::PopStyleVar();
    ImGui::End();

    return next;
}

size_t UIsys::menuControles (GraphicEngine& GE, size_t next){

    auto* m_window = GE.getWindow();
    auto width = GE.getWidth();
    auto height = GE.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)controles.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuIni", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SetCursorPos(ImVec2(width/10*8-100,height/10*8));
    if(ImGui::Button("Volver", ImVec2(300,100))){
        if(inGame == true){

            next = 3;
        }
        else{

            next = 0;
        }
        
    }
    ImGui::PopStyleVar();
    ImGui::End();

    return next;
}

size_t UIsys::menuSonido (GraphicEngine& GE, size_t next, SoundSystem_t& Sou){

    auto* m_window = GE.getWindow();
    auto width = GE.getWidth();
    auto height = GE.getHeight();
    auto masterPrevi = SoundMaster;
    
    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)inicio.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(width/10,height/10*3));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuSonido", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
    ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.55f);
    float defaultFont = ImGui::GetFont()->Scale;
    ImGui::GetFont()->Scale *=0.5;
    ImGui::PushFont(ImGui::GetFont());

    ImGui::SliderFloat("Master", &SoundMaster, 0.0f, 1.0f); 
    ImGui::SliderFloat("Ambiente", &SoundAmbient, 0.0f, 1.0f);      
    ImGui::SliderFloat("Musica", &SoundMusic, 0.0f, 1.0f);
    ImGui::SliderFloat("SFX", &SoundSFX, 0.0f, 1.0f);
    ImGui::SliderFloat("Voces", &SoundVoices, 0.0f, 1.0f);

    ImGui::Checkbox("Pantalla completa", &pantallaCompleta);
    
    ImGui::GetFont()->Scale =defaultFont;
    ImGui::PopFont();
    ImGui::PopItemWidth();



    ImGui::SetCursorPos(ImVec2(width/10*3,height/10*5));
    if(ImGui::Button("Volver", ImVec2(300,100))){
        if(inGame == true){
            
            next = 3;
        }
        else{
            next = 0;
        }
        
    }
    ImGui::PopStyleVar();
    ImGui::End();

    if(masterPrevi != SoundMaster){
        Sou.changeMasterVCA(SoundMaster);
        SoundAmbient = SoundMaster;
        SoundMusic = SoundMaster;
        SoundSFX = SoundMaster;
        SoundVoices = SoundMaster;
    }
    if(pantallaCompleta == true){
        glfwMaximizeWindow(m_window);
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        GE.glEng.setResolution(mode->width, mode->height);
        moveX=GE.getWidth()/2;
        moveY=GE.getHeight()/2.5;
        //glfwSetWindowSize(m_window,mode->width, mode->height);
    }
    else{
        glfwRestoreWindow(m_window);
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
    auto width = GE.getWidth();
    auto height = GE.getHeight();

    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)pausa.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(
        "MenuPausa", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    ImGui::SetCursorPos(ImVec2(width/10*4,height/10*2.5));
    if(ImGui::Button("Reanudar", ImVec2(300,100))){
        
        next = 1;
    }

    ImGui::SetCursorPos(ImVec2(width/10*4,height/10*4));
    if(ImGui::Button("Sonido", ImVec2(300,100))){
        
        next = 5;
    }


    ImGui::SetCursorPos(ImVec2(width/10*4,height/10*5.5));
    if(ImGui::Button("Controles", ImVec2(300,100))){
        next = 4;
    }


    ImGui::SetCursorPos(ImVec2(width/10*4,height/10*7));
    if(ImGui::Button("Salir", ImVec2(300,100))){
        
        next = 0;
    }
 
    ImGui::PopStyleVar();
    ImGui::End();
    
    return next;
}

void UIsys::pantallaCarga(GraphicEngine& GE, double progress ){

    auto* m_window = GE.getWindow();
    auto width = GE.getWidth();
    auto height = GE.getHeight();
    
    ImGui::GetBackgroundDrawList()->AddImage((void*)(intptr_t)cargando.ID_, ImVec2(0, 0), ImVec2(width, height));
    
    //ImGui::PushStyleVar(ImGuiCol_WindowBg);
    ImGui::SetNextWindowPos(ImVec2(0,height/10*7));
    
    ImGui::SetNextWindowSize(ImVec2(width, height));
    
    ImGui::Begin(
        "Cargand", NULL,
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar 
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse 
    );
    
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, IM_COL32(255,0,0,255));
    float defaultFont = ImGui::GetFont()->Scale;
    ImGui::GetFont()->Scale /=1.5;
    ImGui::PushFont(ImGui::GetFont());
    //ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0,0,0,0));
    ImGui::ProgressBar(progress,ImVec2(width,60));

    ImGui::GetFont()->Scale =defaultFont;
    ImGui::PopFont();
    //ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    
    
    ImGui::End();
}  
    
