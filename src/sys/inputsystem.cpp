#include "inputsystem.hpp"

void InputSystem::update(EntityManager<Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>>& EM){
    EM.forall([](Entity<Tags<TPlayer>, PhysicsComponent, RenderComponent, InputComponent>& e) {
        //auto& inp {e.input};
        //auto& phy {e.physics};
    });
}