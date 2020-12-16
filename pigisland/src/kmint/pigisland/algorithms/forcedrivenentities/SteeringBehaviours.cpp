#include "SteeringBehaviours.hpp"
#include "kmint/pigisland/entities/pig.hpp"

namespace kmint {
    namespace pigisland {
        // mass -> vast
        // force -> variabel 
        // acceleration -> berekenen (vanuit kracht en force)
        // velocity -> berekenen
        // position -> berekenen

        // setAcceleration() => force() / mass()
        // setVelocity() => velocity() + acceleration * dt
                // Add max velocity
        // setPosition() => position() + velocity * dt

        // achtervolgen
            // seek
                // dom naar huidige plaats
            // persuit
                // voorspellen welke plaats
                // hoe ver vooruit?
            // wander   
                // puntje op circel, punt veranderen

        // flocing
            // seperation
                // range kijken -> entiteiten die erin liggen
                // tel vectoren richting neighbours
                // ga andere kant op van die uitkomst
            // allignment
                // range kijken -> entiteiten die erin liggen
                // tel vectoren richting van de neighbours
                // normalizeer -> nieuwe richting
            // cohesion
                // rangekijken -> middelpunt van alle neighbours

        // wall avoidance
            // feelers
        // bstacle avoidance
        namespace forcedrivenentities {
            std::vector<std::reference_wrapper<pig>> SteeringBehaviours::getNeighbours(pig& owner) {
                std::vector<std::reference_wrapper<pig>> returnVector;
                for (std::size_t i = 0; i < owner.num_perceived_actors(); ++i)
                {
                    auto& actor = owner.perceived_actor(i);
                    if (typeid(actor) == typeid(pig)) {
                        auto p = dynamic_cast<pig*>(&actor);
                        returnVector.push_back(*p);
                    }
                }
                return returnVector;
            }
            // cohesion
                // rangekijken -> middelpunt van alle neighbours
            math::vector2d SteeringBehaviours::cohesion(pig& owner) {
                kmint::math::vector2d centerOfMass, steeringForce;
                float xTotal = 0;
                float yTotal = 0;

                auto neighbours = getNeighbours(owner);

                if (neighbours.size() > 0)
                {
                    for (std::size_t i = 0; i < neighbours.size(); i++)
                    {
                        xTotal += neighbours[i].get().location().x();
                        yTotal += neighbours[i].get().location().y();
                    }
                    centerOfMass = { xTotal / neighbours.size(), yTotal / neighbours.size() };
                    // now seek toward that position
                    //steeringForce = seek(centerOfMass, owner);
                }
                return steeringForce;
            }
            // seperation
                // range kijken -> entiteiten die erin liggen
                // tel vectoren richting neighbours
                // ga andere kant op van die uitkomst
            math::vector2d SteeringBehaviours::separation(pig& owner) {
                throw std::exception("implement");
            }
            // allignment
                // range kijken -> entiteiten die erin liggen
                // tel vectoren richting van de neighbours
                // normalizeer -> nieuwe richting
            math::vector2d SteeringBehaviours::alignment(pig& owner) {
                auto neighbours = getNeighbours(owner);
               
                throw std::exception("implement");
            }




            // TODO
            math::vector2d SteeringBehaviours::seek(math::vector2d& loc) {
                throw std::exception("implement");
            }
            math::vector2d SteeringBehaviours::flee(math::vector2d& loc) {
                throw std::exception("implement");
            }
            math::vector2d SteeringBehaviours::persuit(math::vector2d& loc) {
                throw std::exception("implement");
            }
            math::vector2d SteeringBehaviours::wander(math::vector2d& loc) {
                throw std::exception("implement");
            }
        }
    }
}