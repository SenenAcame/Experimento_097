#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "typeUsing.hpp"

struct Entity;
struct Mesh;
struct Texture;
struct Shader;



 struct TNodo {

    using vecNodo = std::vector<TNodo *>;

        TNodo() noexcept;
        TNodo(Vec3, Vec3, Vec3) noexcept;

        // inicializa el nodo por defecto
        void initTNode();

        // Borra el nodo
        void remove();
        
        // Añade un nodo hijo a este nodo
        int addSon(TNodo *hijo) noexcept;

        // Elimina un nodo hijo a este nodo
        int deleteSon(TNodo *hijo) noexcept;

        //Manejador de entidad asociada

        TNodo *getFather() noexcept;
        vecNodo *getSons() noexcept;

        //setters
        void setTranslation(Vec3 trans);
        void setRotation(Vec3 rot);
        void setScale(Vec3 sca);
        void setTexture(Texture *tex);
        void setMesh(Mesh *sMesh);
        void setEntity(Entity *nEnt);
        void setFatherNode(TNodo *nFather);
        //transformadores
        // Suma la translacion pasada por parametro a la existente
        void translade(Vec3 trans);
        // Suma la rotacion pasada por parametro a la existente
        void rotate(Vec3 rot);
        // Suma la escala pasada por parametro a la existente
        void scale(Vec3 sca);
        //getters
        Entity *getEntity() noexcept;
        Vec3 getTranslation() const noexcept;
        Vec3 getRotation() const noexcept;
        Vec3 getScale() const noexcept;

        // 1- Se ejecuta la funcion draw de la entidad del nodo y se actualiza los vectores propios.
        // 2- Se hace run de los hijos
        void run(Mat4, bool);

        //matriz
        void setMatrizTransf(Mat4 transf);
        Mat4 getMatrizTransf() noexcept;
    
    // VARIABLES
    //___________________________

        Entity *entity_{nullptr}; 
        Mesh *mesh_{nullptr}; // dentro de Entity si puede ser
        Texture *texture_{nullptr}; // dentro de Entity si puede ser

        bool updateMat_{true};
        

        vecNodo nodeSons_;
        TNodo *fatherNode_{nullptr};

        Mat4 matTransf_;

        Vec3 translation_{0.0f};
        Vec3 rotation_{0.0f};
        Vec3 scale_{1.0f};
        
};