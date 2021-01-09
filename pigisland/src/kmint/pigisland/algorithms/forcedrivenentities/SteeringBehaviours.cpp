#include "SteeringBehaviours.hpp"
#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/entities/base/MovingEntity.hpp"
#include <cmath>
#include <kmint/pigisland/util/Wall2D.hpp>

namespace kmint {
    namespace pigisland {
        namespace forcedrivenentities {
            kmint::math::vector2d SteeringBehaviours::cohesion(MovingEntity& owner) {
                kmint::math::vector2d centerOfMass, steeringForce;

                auto neighbours = owner.getNeighbours(owner);

                if (neighbours.size() > 0)
                {
                    for (std::size_t i = 0; i < neighbours.size(); i++)
                    {
                        centerOfMass += neighbours[i].get().location();
                    }
                    centerOfMass /= neighbours.size();
                    steeringForce = seek(centerOfMass, owner);
                }
                return steeringForce;
            }

            kmint::math::vector2d SteeringBehaviours::separation(MovingEntity& owner) {
                kmint::math::vector2d steeringForce;

                auto neighbours = owner.getNeighbours(owner);
                for (std::size_t i = 0; i < neighbours.size(); i++)
                {
                    kmint::math::vector2d to = owner.location() - neighbours[i].get().location();
                    steeringForce += kmint::pigisland::util::math::Util::normalize(to) / kmint::pigisland::util::math::Util::calcVectorLength(to);
                }
                return steeringForce;
            }

            kmint::math::vector2d SteeringBehaviours::alignment(MovingEntity& owner) {

                kmint::math::vector2d avarage;
                auto neighbours = owner.getNeighbours(owner);

                if (neighbours.size() > 0)
                {
                    for (std::size_t i = 0; i < neighbours.size(); i++)
                    {
                        avarage += neighbours[i].get().heading();
                    }
                    avarage /= neighbours.size();
                    avarage -= owner.heading();
                }
                return avarage;
            }


            kmint::math::vector2d SteeringBehaviours::seek(kmint::math::vector2d& loc, MovingEntity& owner) {
                kmint::math::vector2d desired = normalize(loc - owner.location()) * owner.maxSpeed();
                return (desired - owner.getVelocity());
            }

            kmint::math::vector2d SteeringBehaviours::flee(kmint::math::vector2d& loc, MovingEntity& owner) {
                for (std::size_t i = 0; i < owner.num_perceived_actors(); ++i)
                {
                    auto& actor = owner.perceived_actor(i);
                    if (typeid(actor) == typeid(owner.fleeTarget())) {
                        kmint::math::vector2d desired = normalize(owner.location() - loc) * owner.maxSpeed();
                        return (desired - owner.getVelocity());
                    }
                }
                return { 0, 0 };
            }

            kmint::math::vector2d SteeringBehaviours::pursuit(kmint::math::vector2d& loc, MovingEntity& owner) {
                for (std::size_t i = 0; i < owner.num_perceived_actors(); ++i)
                {
                    auto& actor = owner.perceived_actor(i);
                    if (typeid(actor) == typeid(owner.pursuitTarget())) {
                        kmint::math::vector2d desired = normalize(loc - owner.location()) * owner.maxSpeed();
                        return (desired - owner.getVelocity());
                    }
                }
                return { 0, 0 };
            }

            kmint::math::vector2d SteeringBehaviours::wander(kmint::math::vector2d& loc, MovingEntity& owner) {
                //first, add a small random vector to the target’s position (RandomClamped returns a value between -1 and 1)
                wanderTarget += kmint::math::vector2d(random_scalar(-1, 1) * owner.wanderJitter(), random_scalar(-1, 1) * owner.wanderJitter());
                //reproject this new vector back onto a unit circle
                auto normalizedTarget = wanderTarget;
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
                return normalize(targetWorld);
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

                auto newV = kmint::pigisland::util::math::Util::multiply(kmint::pigisland::util::math::Util::multiply(kmint::pigisland::util::math::Util::multiply(m1, m2), m3), f);
                auto newM = kmint::pigisland::util::math::Util::multiply(m3, m2);
                auto Mr = kmint::pigisland::util::math::Util::multiply(m3, newM);

                auto r = kmint::pigisland::util::math::Util::multiply(Mr, f);
                return newV;
            }

            kmint::math::vector2d SteeringBehaviours::wallAvoidance(MovingEntity& owner) {
                createFeelers(owner);

                double distToThisIP = 0.0;
                double distToClosestIP = DBL_MAX;

                //this will hold an index into the vector of walls
                int closestWall = -1;
                kmint::math::vector2d steeringForce, point, closestPoint;  

                //examine each feeler in turn
                std::vector<Wall2D> walls = owner.getWalls();
                for (std::size_t flr = 0; flr < m_Feelers.size(); ++flr)
                {
                    for (std::size_t w = 0; w < walls.size(); ++w)
                    {
                        // Check wheter feeleter insects
                        if (kmint::pigisland::util::math::Util::lineIntersection2D(owner.location(), m_Feelers[flr],  walls[w].from(), walls[w].to(), distToThisIP, point))
                        {
                            // 
                            if (distToThisIP < distToClosestIP)
                            {
                                distToClosestIP = distToThisIP;
                                closestWall = w;
                                closestPoint = point;
                            }
                        }
                    }

                    //if an intersection point has been detected, calculate a force that will direct the agent away
                    if (closestWall >= 0)
                    {
                        // calculate by what distance the projected position of the agent will overshoot the wall
                        kmint::math::vector2d overShoot = m_Feelers[flr] - closestPoint;
                        // create a force in the direction of the wall normal, with a magnitude of the overshoot
                        steeringForce = walls[closestWall].normal() * kmint::pigisland::util::math::Util::calcVectorLength(overShoot);
                    }
                }

                return steeringForce;
            }

            void SteeringBehaviours::createFeelers(MovingEntity& owner)
            {
                //feeler pointing straight in front
                m_Feelers[0] = owner.location() + owner.wallDetectionFeelerLength() * owner.heading();

                //feeler to left
                kmint::math::vector2d temp = owner.heading();

                kmint::math::matrix<float> r1 = kmint::pigisland::util::math::Util::createRotationMatrix(HALF_PI * 3.5f);
                kmint::math::matrix<float> t1 = kmint::pigisland::util::math::Util::createTransformMatrix(temp.x(), temp.y());
                kmint::math::matrix<float> t2 = kmint::pigisland::util::math::Util::createTransformMatrix(-temp.x(), -temp.y());

                temp = kmint::pigisland::util::math::Util::multiply(t1, temp);
                temp = kmint::pigisland::util::math::Util::multiply(r1, temp);
                temp = kmint::pigisland::util::math::Util::multiply(t2, temp);

                m_Feelers[1] = owner.location() + owner.wallDetectionFeelerLength() / 2.0f * temp;

                //feeler to right
                temp = owner.heading();

                r1 = kmint::pigisland::util::math::Util::createRotationMatrix(HALF_PI * 0.5f);
                t1 = kmint::pigisland::util::math::Util::createTransformMatrix(temp.x(), temp.y());
                t2 = kmint::pigisland::util::math::Util::createTransformMatrix(-temp.x(), -temp.y());

                temp = kmint::pigisland::util::math::Util::multiply(t1, temp);
                temp = kmint::pigisland::util::math::Util::multiply(r1, temp);
                temp = kmint::pigisland::util::math::Util::multiply(t2, temp);

                m_Feelers[2] = owner.location() + owner.wallDetectionFeelerLength() / 2.0f * temp;
            }

            bool accumulateForece(MovingEntity& owner, kmint::math::vector2d& runningTot, const kmint::math::vector2d forceToAdd) {
                double magSoFar = kmint::pigisland::util::math::Util::calcVectorLength(runningTot);

                double magRemaining = owner.maxForce() - magSoFar;

                if (magRemaining <= 0) return false;

                double magToAdd = kmint::pigisland::util::math::Util::calcVectorLength(forceToAdd);

                if (magToAdd < magRemaining) {
                    runningTot += forceToAdd;
                }
                else {
                    runningTot  += normalize(forceToAdd) * magRemaining;
                }
                return true;
            }

            // Truncated
            kmint::math::vector2d SteeringBehaviours::calculate(MovingEntity& owner) {
                math::vector2d steeringForce;
                steeringForce += wallAvoidance(owner) * owner.obstacleAvoidanceWeight();
                steeringForce += wander(owner.location(), owner) * owner.wanderWeight();
                steeringForce += flee(owner.fleeTarget().location(), owner) * owner.fleeWeight();
                steeringForce += pursuit(owner.pursuitTarget().location(), owner) * owner.seekWeight();
                steeringForce += separation(owner) * owner.separationWeight();
                steeringForce += cohesion(owner) * owner.cohesionWeight();
                steeringForce += alignment(owner) * owner.alignmentWeight();

                return kmint::pigisland::util::math::Util::truncate(steeringForce, owner.maxForce());
            }
        }
    }
}