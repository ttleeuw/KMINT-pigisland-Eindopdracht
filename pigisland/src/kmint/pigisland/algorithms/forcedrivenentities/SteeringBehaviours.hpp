#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include <kmint/play/actor.hpp>
#include <cmath>

#define PI 3.14159
#define HALF_PI PI / 2

namespace kmint {
    namespace pigisland {
        class MovingEntity;

        namespace forcedrivenentities {
            class SteeringBehaviours {
            private:
                math::vector2d wanderTarget;

                std::vector<kmint::math::vector2d> m_Feelers{ 3 };
            public:
                std::vector<std::reference_wrapper<MovingEntity>> getNeighbours(MovingEntity& owner);
                kmint::math::vector2d cohesion(MovingEntity& owner);
                kmint::math::vector2d separation(MovingEntity& owner);
                kmint::math::vector2d alignment(MovingEntity& owner);

                kmint::math::vector2d seek(kmint::math::vector2d& loc, MovingEntity& owner);
                kmint::math::vector2d wander(kmint::math::vector2d& loc, MovingEntity& owner);
                kmint::math::vector2d flee(kmint::math::vector2d& loc, MovingEntity& owner);

                kmint::math::vector2d pointToWorldSpace(const kmint::math::vector2d& point, const kmint::math::vector2d& agentHeading, const kmint::math::vector2d& agentSide, const kmint::math::vector2d& agentPosition);


                void createFeelers(MovingEntity& owner);
                kmint::math::vector2d wallAvoidance(MovingEntity& owner);
                bool lineIntersection2D(kmint::math::vector2d A, kmint::math::vector2d B, kmint::math::vector2d C, kmint::math::vector2d D, double& dist, kmint::math::vector2d& point);


                // Truncated
                kmint::math::vector2d calculate(MovingEntity& owner);

                // TODO
                kmint::math::vector2d WTRSwPCalculate() { }
                    // vector2d steeringForce
                    // foreach(priorty in priority)
                        // steeringForce += Wander() * wanderAmountWeight;
                        // steeringForce += ObstacleAvoidance() * obstacleAvoidanceAmount
                        // steeringForce += seperation() * seperationAmount;
                    // return steeringForce.truncate(MAX_STEERING_FORCE);
                kmint::math::vector2d prioritizedDithering() {}
                    // vector2d steeringForce
                    // random on priority
                    // 1 steeringforce adv random
                    // return steeringForce.truncate(MAX_STEERING_FORCE);
            };
        }
    }
}