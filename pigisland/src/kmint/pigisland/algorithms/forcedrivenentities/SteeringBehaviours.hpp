#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include <kmint/play/actor.hpp>
#include "kmint/pigisland/util/math.hpp"

namespace kmint {
    namespace pigisland {
        class MovingEntity;

        namespace forcedrivenentities {
            class SteeringBehaviours {
            private:
                // Wander
                math::vector2d wanderTarget;

                kmint::math::vector2d vTarget;
                kmint::math::vector2d vHeading;
                kmint::math::vector2d vPerp;


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


                std::vector<std::reference_wrapper<MovingEntity>> getNeighbours(MovingEntity& owner);
                kmint::math::vector2d cohesion(MovingEntity& owner);
                kmint::math::vector2d separation(MovingEntity& owner);
                kmint::math::vector2d alignment(MovingEntity& owner);

                kmint::math::vector2d seek(kmint::math::vector2d& loc, MovingEntity& owner);
                kmint::math::vector2d persuit(kmint::math::vector2d& loc, MovingEntity& owner);
                kmint::math::vector2d wander(kmint::math::vector2d& loc, MovingEntity& owner);
                kmint::math::vector2d flee(kmint::math::vector2d& loc, MovingEntity& owner);

                double calcVectorLength(kmint::math::vector2d target);
                kmint::math::vector2d normalize(kmint::math::vector2d target);


                kmint::math::matrix<float> multiply(kmint::math::matrix<float> m1, kmint::math::matrix<float> m2);
                kmint::math::vector2d multiply(kmint::math::matrix<float> m1, const kmint::math::vector2d& vector);
                kmint::math::vector2d pointToWorldSpace(
                    const kmint::math::vector2d& point,
                    const kmint::math::vector2d& agentHeading,
                    const kmint::math::vector2d& agentSide,
                    const kmint::math::vector2d& agentPosition
                );

                // Truncated
                kmint::math::vector2d calculate(MovingEntity& owner);

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