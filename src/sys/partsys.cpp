#include "partsys.hpp"

#include "../cmp/particlecmp.hpp"
#include "../cmp/physicscmp2.hpp"

#include "../eng/GLgEngine.hpp"

bool PartSys::update(EntyMan &EM, const float dt) const {

    EM.foreach<SYSCMPs, SYSTAGs>(
        [&](Enty& ent, PhysicsCmp2& phy, ParticleCMP& particle) {
            
            particle.ellapsedTime_ += dt;
    
            if(particle.ellapsedTime_ >= particle.spawnTime_) {
        
                particle.generator_->addParticle(particle.particlesForSpawn_);
                particle.ellapsedTime_ = 0.f;
        
                //gen new part
                particle.generator_->genParticles(Vec3(phy.x, phy.y, phy.z), Vec3(0.f), Vec3(particle.velocityDirection_[0], particle.velocityDirection_[1], particle.velocityDirection_[2]), particle.dotVelocity_, particle.rotation_, particle.scale_, particle.life_, particle.gravity_);
            }
        }
    );

    //for(auto &particle : ) {
    //    auto &ent = EM.getEntityById(particle.getEntityID());
    //    auto *phy = EM.getComponent<PhysicsCmp2>(ent);
    //
    //    
    //}

    engine_->updateAllParticles(dt);

    return true;
}

    void PartSys::setParticle(ParticleCMP& parcmp, std::string textureName, uint8_t maxParticles, uint8_t particlesForSpawn, float spawnTime, float life, std::vector<float> velocityDirection, float dotVelocity, float rotation, float scale, float gravity){

        parcmp.textureName_ = textureName;
        parcmp.maxParticles_ = maxParticles;
        parcmp.particlesForSpawn_ = particlesForSpawn;
        parcmp.spawnTime_ = spawnTime;
        parcmp.life_ = life;

        parcmp.velocityDirection_ = velocityDirection;
        parcmp.dotVelocity_ = dotVelocity;
        parcmp.rotation_ = rotation;
        parcmp.scale_ = scale;

        parcmp.gravity_ = gravity;

        parcmp.generator_ = &(engine_->createGenParticle(parcmp.textureName_, parcmp.maxParticles_));
    }
