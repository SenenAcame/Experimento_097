#pragma once
#include <vector>
#include <glm/glm.hpp>
struct Entity;
struct Mesh;

class TNodo {
    public:
        //Manejador de Hijos asociados
        int addSon(TNodo *hijo) noexcept;
        int deleteSon(TNodo *hijo) noexcept;

        //Manejador de entidad asociada
        int setEntity(Entity *e);
        Entity *getEntity(){ return entity_; }

        TNodo *getFather(){ return TNfather_; }
        std::vector<TNodo *> *getSons() noexcept;

        //setters
        void setTranslation(glm::vec3 trans){ translation_ = trans; }
        void setRotation(glm::vec3 rot){ rotation_ = rot; }
        void setScale(glm::vec3 sca){ scale_ = sca; }
        void setTexture();
        void setMesh(Mesh *smesh);
        //transformadores
        void translade(glm::vec3 trans);
        void rotate(glm::vec3 rot);
        void scale(glm::vec3 sca);
        //getters
        glm::vec3 getTranslation() const noexcept{ return translation_; }
        glm::vec3 getRotation() const noexcept{ return rotation_; }
        glm::vec3 getScale() const noexcept{ return scale_; }

        //matriz
        void setMatrizTransf(glm::mat4 transf){ matTransf_ = transf; }
        glm::mat4 getMatrizTransf(){ return matTransf_; }

    private:
        Entity *entity_;
        std::vector<TNodo *> TNsons_;
        TNodo *TNfather_{nullptr};
        glm::vec3 translation_{0.0f};
        glm::vec3 rotation_{0.0f};
        glm::vec3 scale_{1.0f};
        glm::mat4 matTransf_;
};