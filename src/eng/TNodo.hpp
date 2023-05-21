#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "resources/RAnimation.hpp"
#include "utils/typeUsing.hpp"

struct Entity;
struct TNodo;
struct RMesh;
struct RTexture;
struct RShader;

struct TNodo {
    using vecNodo = std::vector<TNodo *>;

    TNodo();
    TNodo(Vec3, Vec3, Vec3);

    // inicializa el nodo por defecto
    void initTNode();

    // Borra el nodo
    void remove();

    template<typename T>
    T *getEntity() const noexcept {
        return ((T *)entity_);
    }
    
    // Añade un nodo hijo a este nodo
    int addSon(TNodo *hijo) noexcept;

    // Elimina un nodo hijo a este nodo
    int deleteSon(TNodo *hijo) noexcept;

    //Manejador de entidad asociada

    TNodo *getFather() const noexcept;
    vecNodo *getSons() noexcept;
    Vec3 getPosition() { return Vec3{matTransf_[3][0], matTransf_[3][1], matTransf_[3][2]}; }

    //setters
    void setTranslation(Vec3 trans);
    void setRotation(Vec3 rot);
    void setScale(Vec3 sca);
    void setTexture(RTexture *tex);
    void setMesh(RMesh *sMesh);
    void setEntity(Entity *nEnt);
    void setFatherNode(TNodo *nFather);
    void setAnimation(RAnimation *ranni);
    //transformadores
    // Suma la translacion pasada por parametro a la existente
    void translade(Vec3 trans);
    // Suma la rotacion pasada por parametro a la existente
    void rotate(Vec3 rot);
    // Suma la escala pasada por parametro a la existente
    void scale(Vec3 sca);
    //getters

    Vec3 getTranslation() const noexcept;
    Vec3 getRotation() const noexcept;
    Vec3 getScale() const noexcept;

    // 1- Se ejecuta la funcion draw de la entidad del nodo y se actualiza los vectores propios.
    // 2- Se hace run de los hijos
    void run(Mat4, bool fatherChange, bool border = false);

    //matriz
    void setMatrizTransf(Mat4 transf);
    Mat4 getMatrizTransf() noexcept;

// VARIABLES
//___________________________

    Entity *entity_{nullptr}; 
    //RMesh *mesh_{nullptr}; // dentro de Entity si puede ser
    //RTexture *texture_{nullptr}; // dentro de Entity si puede ser

    bool updateMat_{true};
    bool floor_{false};
    bool UI_{false};
    
    float xRad{0.0f};
    float yRad{0.0f};
    float zRad{0.0f};

    vecNodo nodeSons_;
    TNodo *fatherNode_{nullptr};

    Mat4 matTransf_;

    Vec3 translation_{0.0f};
    Vec3 rotation_{0.0f};
    Vec3 scale_{1.0f};
    
};