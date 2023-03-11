#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "typeUsing.hpp"

struct Entity;
struct Mesh;
struct Texture;




 struct TNodo {

    using vecNodo = std::vector<TNodo *>;

        TNodo() noexcept;
        TNodo(Vec3, Vec3, Vec3) noexcept;

        void initTNode();
        void remove();
        
        int addSon(TNodo *hijo) noexcept;
        int deleteSon(TNodo *hijo) noexcept;

        //Manejador de entidad asociada
        Entity *getEntity() noexcept;

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
        void translade(Vec3 trans);
        void rotate(Vec3 rot);
        void scale(Vec3 sca);
        //getters
        Vec3 getTranslation() const noexcept;
        Vec3 getRotation() const noexcept;
        Vec3 getScale() const noexcept;

        //matriz
        void setMatrizTransf(Mat4 transf);
        Mat4 getMatrizTransf() noexcept;
    
        Entity *entity_{nullptr};
        Mesh *mesh_{nullptr};
        //Texture *texture_{nullptr};
        
        vecNodo nodeSons_;
        TNodo *fatherNode_{nullptr};

        Mat4 matTransf_;

        Vec3 translation_{0.0f};
        Vec3 rotation_{0.0f};
        Vec3 scale_{1.0f};
        
};