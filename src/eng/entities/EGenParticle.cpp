#include "EGenParticle.hpp"
#include <GL/gl.h>
#include <GL/glext.h>

EGenParticle::EGenParticle(RShader *shader, RTexture *texture, unsigned int amount) 
    : amount(amount), shader(shader), texture(texture) {

        this->init();
        particles.reserve(amount + 1);
}

void EGenParticle::update(float dt) {
    //update all particles
    for(unsigned int i = 0; i < this->amount; i++) {
        Particle &p = this->particles[i];
        p.Life -= dt;
        if(p.Life >0.0f) {
            p.Velocity.y += p.Gravity * dt;
            p.Position += p.Velocity * dt;
            p.Color.a -= dt * 1.0f;
        }
    }
}

void EGenParticle::genParticles(Vec3 objPos, Vec3 offset , Vec3 velocityDirection, float offsetVelocity, float rotation, float scale, float life, float gravity) {
    //add new particles
    for(unsigned int i = 0; i < newParticles; ++i) {
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], objPos, offset , velocityDirection, offsetVelocity, rotation, scale, life, gravity);
    }
    newParticles = 0;
}

void EGenParticle::addParticle(unsigned int add) {
    newParticles += add;
}

//draw all particles
void EGenParticle::draw(Mat4 &view) {

    this->shader->use();
    Mat4 mIdent(1.0f);
    for (Particle particle : this->particles) {
        if(particle.Life > 0.0f) {
            Mat4 tmpIdt = mIdent;
            tmpIdt = glm::translate(tmpIdt, particle.Position);

            tmpIdt[0].x = view[0].x;
            tmpIdt[0].y = view[1].y;
            tmpIdt[0].z = view[2].z;

            tmpIdt[1].x = view[0].x;
            tmpIdt[1].y = view[1].y;
            tmpIdt[1].z = view[2].z;

            tmpIdt[2].x = view[0].x;
            tmpIdt[2].y = view[1].y;
            tmpIdt[2].z = view[2].z;

            tmpIdt = glm::rotate(tmpIdt, glm::radians(180.0f + particle.Rotation), {0,0,1});
            tmpIdt = glm::scale(tmpIdt, Vec3(particle.Scale));

            tmpIdt = view * tmpIdt;

            this->shader->setMat4("model", tmpIdt);
            this->shader->setVec4("color", particle.Color);
            glBindTexture(GL_TEXTURE_2D, texture->ID_);
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
}

void EGenParticle::init() {
    //init quad and arrays
    unsigned int VBO;
    float particle_quad[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 

        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 
        0.0f, 1.0f, 0.0f, 1.0f 
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    //fill the buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindVertexArray(0);

    for (unsigned int i = 0; i < this->amount; ++i) {
        this->particles.push_back(Particle());
    }
}

unsigned int lastUsedParticle = 0;
unsigned int EGenParticle::firstUnusedParticle() {
    //search the next non-used
    for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
        if (this->particles[i].Life <= 0.0f ) {
            lastUsedParticle = i;
            return i;
        }
    }
    //if didn't match, search linear
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if(this->particles[i].Life <= 0.0) {
            lastUsedParticle = i;
            return i;
        }
    }
    //if all particles are occupied, rewrite the firs
    lastUsedParticle = 0;
    return 0;
}

void EGenParticle::respawnParticle(Particle &particle, Vec3 objPos, Vec3 offset, Vec3 velocityDirection, float offsetVelocity, float rotation, float scale, float life, float gravity) {
    float random = ((rand() % 100) -49) / 50.0f;
    float random2 = ((rand() % 50)) / 50.0f;
    float random3 = ((rand() % 100) -49) / 50.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    particle.Position = Vec3(objPos.x + random / 2.0f, objPos.y + random2 / 2.0f, objPos.z + random3 / 2.0f) + offset;
    particle.Color = Vec4(rColor, rColor, rColor, 1.0f);
    particle.Life = life;
    particle.Velocity = Vec3(random, random2, random3) * velocityDirection * offsetVelocity;

    particle.Rotation = rotation;
    particle.Scale = scale;
    particle.Gravity = gravity;
}