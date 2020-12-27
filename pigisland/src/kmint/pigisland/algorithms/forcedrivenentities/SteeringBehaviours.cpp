#include "SteeringBehaviours.hpp"
#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/entities/base/MovingEntity.hpp"
#include <cmath>

namespace kmint {
    namespace pigisland {
        // wall avoidance
            // feelers
        // ostacle avoidance
        namespace forcedrivenentities {
            std::vector<std::reference_wrapper<MovingEntity>> SteeringBehaviours::getNeighbours(MovingEntity& owner) {
                std::vector<std::reference_wrapper<MovingEntity>> returnVector;
                for (std::size_t i = 0; i < owner.num_perceived_actors(); ++i)
                {
                    auto& actor = owner.perceived_actor(i);
                    if (typeid(actor) == typeid(pig)) {
                        auto p = dynamic_cast<MovingEntity*>(&actor);
                        returnVector.push_back(*p);
                    }
                }
                return returnVector;
            }

            // cohesion
                // rangekijken -> middelpunt van alle neighbours
            kmint::math::vector2d SteeringBehaviours::cohesion(MovingEntity& owner) {
                kmint::math::vector2d centerOfMass, steeringForce;

                auto neighbours = getNeighbours(owner);

                for (std::size_t i = 0; i < neighbours.size(); i++)
                {
                    centerOfMass += neighbours[i].get().location();
                }

                if (neighbours.size() > 0)
                {
                    centerOfMass /= neighbours.size();
                    steeringForce = seek(centerOfMass, owner);
                }
                return steeringForce;
            }

            // seperation
                // range kijken -> entiteiten die erin liggen
                // tel vectoren richting neighbours
                // ga andere kant op van die uitkomst
            kmint::math::vector2d SteeringBehaviours::separation(MovingEntity& owner) {
                kmint::math::vector2d steeringForce;

                auto neighbours = getNeighbours(owner);
                for (std::size_t i = 0; i < neighbours.size(); i++)
                {
                    kmint::math::vector2d to = owner.location() - neighbours[i].get().location();
                    steeringForce += kmint::pigisland::util::math::Util::normalize(to) / kmint::pigisland::util::math::Util::calcVectorLength(to);
                }
                return steeringForce;
            }
            // allignment
                // range kijken -> entiteiten die erin liggen
                // tel vectoren richting van de neighbours
                // normalizeer -> nieuwe richting
            kmint::math::vector2d SteeringBehaviours::alignment(MovingEntity& owner) {

                kmint::math::vector2d avarage;
                auto neighbours = getNeighbours(owner);

                for (std::size_t i = 0; i < neighbours.size(); i++)
                {
                    avarage += neighbours[i].get().heading();
                }

                if (neighbours.size() > 0)
                {
                    avarage /= neighbours.size();
                    avarage -= owner.heading();
                }
                return avarage;
            }

            // seek
                // dom naar huidige plaats
            kmint::math::vector2d SteeringBehaviours::seek(kmint::math::vector2d& loc, MovingEntity& owner) {
                kmint::math::vector2d desired = normalize(loc - owner.location()) * owner.maxSpeed();
                return (desired - owner.getVelocity());
            }
            // TODO
            // persuit
                // voorspellen welke plaats
                // hoe ver vooruit?
            kmint::math::vector2d SteeringBehaviours::persuit(kmint::math::vector2d& loc, MovingEntity& owner) {
                throw std::exception("implement");
            }
            // persuit
               // opposite vector of target
            kmint::math::vector2d SteeringBehaviours::flee(kmint::math::vector2d& loc, MovingEntity& owner) {
                for (std::size_t i = 0; i < owner.num_perceived_actors(); ++i)
                {
                    auto& actor = owner.perceived_actor(i);
                    if (typeid(actor) == typeid(shark)) {
                        auto p = dynamic_cast<shark*>(&actor);

                        kmint::math::vector2d desired = normalize(owner.location() - owner.fleeTarget().location()) * owner.maxSpeed();
                        return (desired - owner.getVelocity());
                    }
                }
                return { 0, 0 };
            }
            // wander   
                // puntje op circel, punt veranderen
            kmint::math::vector2d SteeringBehaviours::wander(kmint::math::vector2d& loc, MovingEntity& owner) {
                //first, add a small random vector to the target’s position (RandomClamped returns a value between -1 and 1)
                wanderTarget += kmint::math::vector2d(random_scalar(-1, 1) * owner.wanderJitter(), random_scalar(-1, 1) * owner.wanderJitter());
                //reproject this new vector back onto a unit circle
                auto normalizedTarget = normalize(wanderTarget);
                //increase the length of the vector to the same as the radius of the wander circle
                normalizedTarget *= owner.wanderRadius();
                //move the target into a position WanderDist in front of the agent
                kmint::math::vector2d targetLocal = normalizedTarget + kmint::math::vector2d(owner.wanderDistance(), 0);

                //project the target into world space
                kmint::math::vector2d targetWorld = pointToWorldSpace(targetLocal,
                    owner.heading(),
                    owner.side(),
                    owner.location()
                );

                //and steer toward it
                // TODO
                return targetWorld - owner.location();
            }

            kmint::math::vector2d SteeringBehaviours::pointToWorldSpace(const kmint::math::vector2d& point,
                    const kmint::math::vector2d& agentHeading,
                    const kmint::math::vector2d& agentSide, 
                    const kmint::math::vector2d& agentPosition
                )
            {
                kmint::math::vector2d f = point;

                kmint::math::matrix<float> m1{ 3, 3 };
                m1(0, 0) = 1;                   m1(0, 1) = 0;                   m1(0, 2) = 0;
                m1(1, 0) = 0;                   m1(1, 1) = 1;                   m1(1, 2) = 0;
                m1(2, 0) = agentPosition.x();   m1(2, 1) = agentPosition.y();   m1(2, 2) = 1;

                kmint::math::matrix<float> m2{ 3, 3 };
                m2(0, 0) = agentHeading.x();    m2(0, 1) = agentHeading.y();    m2(0, 2) = 0;
                m2(1, 0) = agentSide.x();       m2(1, 1) = agentSide.y();       m2(1, 2) = 0;
                m2(2, 0) = 0;                   m2(2, 1) = 0;                   m2(2, 2) = 1;

                kmint::math::matrix<float> m3{ 3, 3 };
                m3(0, 0) = 1;                   m3(0, 1) = 0;                   m3(0, 2) = 0;
                m3(1, 0) = 0;                   m3(1, 1) = 1;                   m3(1, 2) = 0;
                m3(2, 0) = 0;                   m3(2, 1) = 0;                   m3(2, 2) = 1;

                auto newM = kmint::pigisland::util::math::Util::multiply(m3, m2);
                auto Mr = kmint::pigisland::util::math::Util::multiply(newM, m1);
                
                auto r = kmint::pigisland::util::math::Util::multiply(Mr, f);
                return r;
            }

            // Truncated
            kmint::math::vector2d SteeringBehaviours::calculate(MovingEntity& owner) {
                math::vector2d steeringForce;
                //steeringForce += wander(owner.location(), owner) * owner.wanderWeight();
                 steeringForce += flee(owner.location(), owner) * owner.fleeWeight();
                // steeringForce += persuit(owner.location(), owner) * persuitWeight;
                //// steeringForce += ObstacleAvoidance() * obstacleAvoidanceAmount
                //steeringForce += cohesion(owner) * owner.cohesionWeight();
                //steeringForce += separation(owner) * owner.separationWeight();
                //steeringForce += alignment(owner) * owner.alignmentWeight();

                return steeringForce;
            }
        }
    }
}