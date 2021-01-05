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
                kmint::math::vector2d pursuit(kmint::math::vector2d& loc, MovingEntity& owner);

                kmint::math::vector2d pointToWorldSpace(const kmint::math::vector2d& point, const kmint::math::vector2d& agentHeading, const kmint::math::vector2d& agentSide, const kmint::math::vector2d& agentPosition);

                void createFeelers(MovingEntity& owner);
                kmint::math::vector2d wallAvoidance(MovingEntity& owner);

                // Truncated
                kmint::math::vector2d calculate(MovingEntity& owner);
            };
        }
    }
}