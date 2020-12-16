#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include <kmint/play/actor.hpp>

namespace kmint {
    namespace pigisland {
        class pig;
        class boat;
        class shark;

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
            class SteeringBehaviours {
            public:
                std::vector<std::reference_wrapper<pig>> getNeighbours(pig& owner);
                math::vector2d cohesion(pig& owner);
                math::vector2d separation(pig& owner);
                math::vector2d alignment(pig& owner);

                math::vector2d seek(math::vector2d& loc); // Boat?
                math::vector2d flee(math::vector2d& loc); // Shark?
                math::vector2d persuit(math::vector2d& loc);
                math::vector2d wander(math::vector2d& loc);

                // Truncated
                math::vector2d truncatedCalculate() {
                    // vector2d steeringForce
                    // steeringForce += Wander() * wanderAmountWeight;
                    // steeringForce += ObstacleAvoidance() * obstacleAvoidanceAmount
                    // steeringForce += seperation() * seperationAmount;

                    // return steeringForce.truncate(MAX_STEERING_FORCE);
                }

                // Weigthed
                math::vector2d WTRSwPCalculate() {
                    // vector2d steeringForce

                    // foreach(priorty in priority)
                        // steeringForce += Wander() * wanderAmountWeight;
                        // steeringForce += ObstacleAvoidance() * obstacleAvoidanceAmount
                        // steeringForce += seperation() * seperationAmount;

                    // return steeringForce.truncate(MAX_STEERING_FORCE);
                }

                math::vector2d prioritizedDithering() {
                    // vector2d steeringForce

                    // random on priority
                    // 1 steeringforce adv random

                    // return steeringForce.truncate(MAX_STEERING_FORCE);
                }
            private:
                //the current target
                math::vector2d target;
                //the current position on the wander circle the agent is attempting to steer towards
                math::vector2d wanderTarget;
                double wanderJitter;
                double wanderRadius;
                double wanderDistance;

                double separationWeight;
                double cohesionWeight;
                double alignmentWeight;

                double seekWeight;
                double fleeWeight;
                double persuitWeight;
                double wanderWeight;

                double viewDistance;
            };
        }
    }
}