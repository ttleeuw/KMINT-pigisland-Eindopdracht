#include "SteeringBehaviours.hpp"
#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/entities/base/MovingEntity.hpp"
#include <cmath>
#include <kmint/pigisland/util/Wall2D.hpp>

namespace kmint {
    namespace pigisland {
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


            kmint::math::vector2d SteeringBehaviours::seek(kmint::math::vector2d& loc, MovingEntity& owner) {
                kmint::math::vector2d desired = normalize(loc - owner.location()) * owner.maxSpeed();
                return (desired - owner.getVelocity());
            }

            kmint::math::vector2d SteeringBehaviours::flee(kmint::math::vector2d& loc, MovingEntity& owner) {
                for (std::size_t i = 0; i < owner.num_perceived_actors(); ++i)
                {
                    auto& actor = owner.perceived_actor(i);
                    if (typeid(actor) == typeid(shark)) {
                        auto p = dynamic_cast<shark*>(&actor);

                        kmint::math::vector2d desired = normalize(owner.location() - loc) * owner.maxSpeed();
                        return (desired - owner.getVelocity());
                    }
                }
                return { 0, 0 };
            }

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

            bool SteeringBehaviours::lineIntersection2D(kmint::math::vector2d A,
                kmint::math::vector2d B, kmint::math::vector2d C,
                kmint::math::vector2d D, double& dist, kmint::math::vector2d& point)
            {

                double rTop = (A.y() - C.y()) * (D.x() - C.x()) - (A.x() - C.x()) * (D.y() - C.y());
                double rBot = (B.x() - A.x()) * (D.y() - C.y()) - (B.y() - A.y()) * (D.x() - C.x());

                double sTop = (A.y() - C.y()) * (B.x() - A.x()) - (A.x() - C.x()) * (B.y() - A.y());
                double sBot = (B.x() - A.x()) * (D.y() - C.y()) - (B.y() - A.y()) * (D.x() - C.x());

                if ((rBot == 0) || (sBot == 0))
                {
                    //lines are parallel
                    return false;
                }
                double r = rTop / rBot;
                double s = sTop / sBot;

                if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
                {
                    dist = kmint::pigisland::util::math::Util::vectorDistance(A, B) * r;
                    point = A + r * (B - A);
                    return true;
                }
                else
                {
                    dist = 0;
                    return false;
                }
            }

            kmint::math::vector2d SteeringBehaviours::wallAvoidance(MovingEntity& owner) {
                createFeelers(owner);

                double distToThisIP = 0.0;
                double distToClosestIP = DBL_MAX;

                //this will hold an index into the vector of walls
                int closestWall = -1;

                kmint::math::vector2d steeringForce,
                    point,         //used for storing temporary info
                    closestPoint;  //holds the closest intersection point

                //examine each feeler in turn
                std::vector<Wall2D> walls = owner.getWalls();
                for (unsigned int flr = 0; flr < m_Feelers.size(); ++flr)
                {
                    //run through each wall checking for any intersection points
                    for (unsigned int w = 0; w < walls.size(); ++w)
                    {
                        if (lineIntersection2D(owner.location(),
                            m_Feelers[flr],
                            walls[w].from(),
                            walls[w].to(),
                            distToThisIP,
                            point))
                        {
                            //is this the closest found so far? If so keep a record
                            if (distToThisIP < distToClosestIP)
                            {
                                distToClosestIP = distToThisIP;

                                closestWall = w;

                                closestPoint = point;
                            }
                        }
                    }//next wall


                    //if an intersection point has been detected, calculate a force  
                    //that will direct the agent away
                    if (closestWall >= 0)
                    {
                        //calculate by what distance the projected position of the agent
                        //will overshoot the wall
                        kmint::math::vector2d OverShoot = m_Feelers[flr] - closestPoint;

                        //create a force in the direction of the wall normal, with a 
                        //magnitude of the overshoot
                        steeringForce = walls[closestWall].normal() * kmint::pigisland::util::math::Util::calcVectorLength(OverShoot);
                    }

                }//next feeler

                return steeringForce;
            }

            void SteeringBehaviours::createFeelers(MovingEntity& owner)
            {
                // TODO get from owner
                int m_dWallDetectionFeelerLength = 12;

                //feeler pointing straight in front
                m_Feelers[0] = owner.location() + m_dWallDetectionFeelerLength * owner.heading();


                //feeler to left
                kmint::math::vector2d temp = owner.heading();

                float a = HALF_PI * 3.5f;

                kmint::math::matrix<float> r1{ 3, 3 };
                r1(0, 0) = std::cosf(a * (PI / 180));   r1(0, 1) = std::sinf(a * (PI / 180));   r1(0, 2) = 0;
                r1(1, 0) = -std::sinf(a * (PI / 180));  r1(1, 1) = std::cosf(a * (PI / 180));   r1(1, 2) = 0;
                r1(2, 0) = 0;                           r1(2, 1) = 0;                           r1(2, 2) = 1;

                kmint::math::matrix<float> t1{ 3, 3 };
                t1(0, 0) = 1;  t1(0, 1) = 0;    t1(0, 2) = temp.x();
                t1(1, 0) = 0;  t1(1, 1) = 1;    t1(1, 2) = temp.y();
                t1(2, 0) = 0;  t1(2, 1) = 0;    t1(2, 2) = 1;

                kmint::math::matrix<float> t2{ 3, 3 };
                t2(0, 0) = 1;  t2(0, 1) = 0;    t2(0, 2) = -temp.x();
                t2(1, 0) = 0;  t2(1, 1) = 1;    t2(1, 2) = -temp.y();
                t2(2, 0) = 0;  t2(2, 1) = 0;    t2(2, 2) = 1;


                temp = kmint::pigisland::util::math::Util::multiply(t1, temp);
                temp = kmint::pigisland::util::math::Util::multiply(r1, temp);
                temp = kmint::pigisland::util::math::Util::multiply(t2, temp);


                m_Feelers[1] = owner.location() + m_dWallDetectionFeelerLength / 2.0f * temp;

                //feeler to right
                temp = owner.heading();

                a = HALF_PI * 0.5f;

                r1 = { 3, 3 };
                r1(0, 0) = std::cosf(a * (PI / 180));   r1(0, 1) = std::sinf(a * (PI / 180));   r1(0, 2) = 0;
                r1(1, 0) = -std::sinf(a * (PI / 180));  r1(1, 1) = std::cosf(a * (PI / 180));   r1(1, 2) = 0;
                r1(2, 0) = 0;                           r1(2, 1) = 0;                           r1(2, 2) = 1;

                t1 = { 3, 3 };
                t1(0, 0) = 1;  t1(0, 1) = 0;    t1(0, 2) = temp.x();
                t1(1, 0) = 0;  t1(1, 1) = 1;    t1(1, 2) = temp.y();
                t1(2, 0) = 0;  t1(2, 1) = 0;    t1(2, 2) = 1;

                t2 = { 3, 3 };
                t2(0, 0) = 1;  t2(0, 1) = 0;    t2(0, 2) = -temp.x();
                t2(1, 0) = 0;  t2(1, 1) = 1;    t2(1, 2) = -temp.y();
                t2(2, 0) = 0;  t2(2, 1) = 0;    t2(2, 2) = 1;


                temp = kmint::pigisland::util::math::Util::multiply(t1, temp);
                temp = kmint::pigisland::util::math::Util::multiply(r1, temp);
                temp = kmint::pigisland::util::math::Util::multiply(t2, temp);


                m_Feelers[2] = owner.location() + m_dWallDetectionFeelerLength / 2.0f * temp;
            }

            // Truncated
            kmint::math::vector2d SteeringBehaviours::calculate(MovingEntity& owner) {
                math::vector2d steeringForce;
                //steeringForce += wander(owner.location(), owner) * owner.wanderWeight();
                steeringForce += flee(owner.fleeTarget().location(), owner) * owner.fleeWeight();
                //steeringForce += seek(owner.persuitTarget().location(), owner) * owner.persuitWeight();
                steeringForce += wallAvoidance(owner) * owner.obstacleAvoidance();
                //steeringForce += cohesion(owner) * owner.cohesionWeight();
                steeringForce += separation(owner) * owner.separationWeight();
                steeringForce += alignment(owner) * owner.alignmentWeight();

                return steeringForce;
            }
        }
    }
}