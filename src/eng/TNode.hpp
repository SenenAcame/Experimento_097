#pragma once

struct Entity;

class TNodo {
    public:
        //Manejador de Hijos asociados
        int addHijo(TNodo *hijo);
        int deleteHijo(TNodo *hijo);

        //Manejador de entidad asociada
        int setEntity(Entity *e);
        Entity *getEntity(){ return entidad; }

        TNodo *getPadre(){ return *padre; }

        //transformaciones
        void recorrer(mat4);
        //setters
        void setTranslation(vec3 trans){ translation = trans; }
        void setRotation(vec3 rot){ rotation = rot; }
        void setScale(vec3 sca){ scale = sca; }
        //transformadores
        int translade(vec3 trans);
        int rotate(vec3 rot);
        int scale(vec3 sca);
        //getters
        vec3 getTranslation(){ return translation; }
        vec3 getRotation(){ return rotation; }
        vec3 getScale(){ return scale; }

        //matriz
        void setMatrizTransf(mat4 transf){ matTransf = transf; }
        mat4 getMatrizTransf(){ return matTransf; }

    private:
        Entity *entidad;
        vector<TNodo*> hijos;
        TNodo *padre;
        vec3 translation;
        vec3 rotation;
        vec3 scale;
        mat4 matTransf;
};