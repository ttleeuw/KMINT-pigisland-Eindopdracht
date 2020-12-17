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
            private:
                // Wander
                math::vector2d wanderTarget;
                double wanderJitter;
                double wanderRadius;
                double wanderDistance;

                double separationWeight;
                double cohesionWeight;
                double alignmentWeight;

                double seekWeight;
                double persuitWeight;
                double wanderWeight;

                math::vector2d vTarget;
                math::vector2d vHeading;
                math::vector2d vPerp;

                float mass; // const
                float force; // var
                float maxForce;
                float maxTurnRate;
                float maxSpeed;

                math::vector2d acceleration; // calculated
                math::vector2d velocity; // calculated
                math::vector2d maxVelocity; // calculated
                math::vector2d position; // calculated

                /*math::vector2d side;
                void side(math::vector2d _side) { side = _side; }
                math::vector2d side() const { return side; }*/
            public:
                math::vector2d truncate(math::vector2d vector, float max)
                {
                    auto length = calcVectorLength(vector);
                    if (length > max)
                    {
                        auto result = normalize(vector);

                        return result *= max;
                    }
                    return vector;
                }

                // acceleration -> berekenen (vanuit kracht en force)
                    // setAcceleration() => force() / mass()
                void setAcceleration(math::vector2d steeringForce) {
                    acceleration = steeringForce / mass;
                }
                // velocity -> berekenen
                    // Add max velocity
                    // setVelocity() => velocity() + acceleration * dt
                void setVelocity(math::vector2d v) {
                    auto l = calcVectorLength(v);
                    velocity = truncate(velocity, maxSpeed);
                }
                // position -> berekenen
                    // setPosition() => position() + velocity * dt
                void setPosition(delta_time dt) {
                    position += velocity * dt.count();
                }


                std::vector<std::reference_wrapper<pig>> getNeighbours(pig& owner);
                math::vector2d cohesion(pig& owner);
                math::vector2d separation(pig& owner);
                math::vector2d alignment(pig& owner);

                math::vector2d seek(math::vector2d& loc, pig& owner);
                math::vector2d persuit(math::vector2d& loc, pig& owner);
                math::vector2d wander(math::vector2d& loc, pig& owner);

                double calcVectorLength(kmint::math::vector2d target);
                kmint::math::vector2d normalize(kmint::math::vector2d target);

                // Truncated
                math::vector2d calculate(pig& owner) {
                    //math::vector2d steeringForce;
                    //steeringForce += wander(owner.location(), owner) * seekWeight;
                    //// steeringForce += ObstacleAvoidance() * obstacleAvoidanceAmount
                    //steeringForce += cohesion(owner) * cohesionWeight;
                    //steeringForce += separation(owner) * separationWeight;
                    //steeringForce += alignment(owner) * alignmentWeight;

                    //return truncate(steeringForce, 10);
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
            };
        }
    }
}