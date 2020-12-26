#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include <kmint/play/actor.hpp>
#include "kmint/pigisland/util/math.hpp"

namespace kmint {
    namespace pigisland {
        class pig;

        namespace forcedrivenentities {
            class SteeringBehaviours {
            private:
                // Wander
                math::vector2d wanderTarget;
                double wanderJitter = 1;
                double wanderRadius = 1;
                double wanderDistance = 1;

                double separationWeight = 1;
                double cohesionWeight = 1;
                double alignmentWeight = 1;

                double seekWeight = 1;
                double persuitWeight = 1;
                double wanderWeight = 1;
                double fleeWeight = 1;

                kmint::math::vector2d vTarget;
                kmint::math::vector2d vHeading;
                kmint::math::vector2d vPerp;

                float mass; // const
                float force; // var
                float maxForce = 2;
                float maxTurnRate;
                float maxSpeed;

                kmint::math::vector2d acceleration; // calculated
                kmint::math::vector2d velocity; // calculated
                kmint::math::vector2d maxVelocity; // calculated
                kmint::math::vector2d position; // calculated

                /*math::vector2d side;
                void side(math::vector2d _side) { side = _side; }
                math::vector2d side() const { return side; }*/
            public:
                kmint::math::vector2d truncate(kmint::math::vector2d vector, float max)
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
                void setAcceleration(kmint::math::vector2d steeringForce) { acceleration = steeringForce / mass;  }
                // velocity -> berekenen
                    // Add max velocity
                    // setVelocity() => velocity() + acceleration * dt
                void setVelocity(kmint::math::vector2d v) {
                    auto l = calcVectorLength(v);
                    velocity = truncate(velocity, maxSpeed);
                }
                // position -> berekenen
                    // setPosition() => position() + velocity * dt
                void setPosition(delta_time dt) { position += velocity * dt.count(); }


                std::vector<std::reference_wrapper<pig>> getNeighbours(pig& owner);
                kmint::math::vector2d cohesion(pig& owner);
                kmint::math::vector2d separation(pig& owner);
                kmint::math::vector2d alignment(pig& owner);

                kmint::math::vector2d seek(kmint::math::vector2d& loc, pig& owner);
                kmint::math::vector2d persuit(kmint::math::vector2d& loc, pig& owner);
                kmint::math::vector2d wander(kmint::math::vector2d& loc, pig& owner);
                kmint::math::vector2d flee(kmint::math::vector2d& loc, pig& owner);

                double calcVectorLength(kmint::math::vector2d target);
                kmint::math::vector2d normalize(kmint::math::vector2d target);


                kmint::math::matrix<float> multiply(kmint::math::matrix<float> m1, kmint::math::matrix<float> m2);
                kmint::math::vector2d multiply(kmint::math::matrix<float> m1, const kmint::math::vector2d& vector);
                kmint::math::vector2d pointToWorldSpace(const kmint::math::vector2d& point,
                    const kmint::math::vector2d& agentHeading,
                    const kmint::math::vector2d& agentSide,
                    const kmint::math::vector2d& agentPosition
                );

                // Truncated
                kmint::math::vector2d calculate(pig& owner);

                // Weigthed
                kmint::math::vector2d WTRSwPCalculate() {
                    // vector2d steeringForce
                    // foreach(priorty in priority)
                        // steeringForce += Wander() * wanderAmountWeight;
                        // steeringForce += ObstacleAvoidance() * obstacleAvoidanceAmount
                        // steeringForce += seperation() * seperationAmount;
                    // return steeringForce.truncate(MAX_STEERING_FORCE);
                }
                kmint::math::vector2d prioritizedDithering() {
                    // vector2d steeringForce
                    // random on priority
                    // 1 steeringforce adv random
                    // return steeringForce.truncate(MAX_STEERING_FORCE);
                }
            };
        }
    }
}