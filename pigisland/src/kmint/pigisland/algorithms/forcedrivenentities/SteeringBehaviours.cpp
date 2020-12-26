#include "SteeringBehaviours.hpp"
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
                    if (typeid(actor) == typeid(MovingEntity)) {
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
                    // TODO
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
                float x = 0;
                float y = 0;

                auto neighbours = getNeighbours(owner);
                kmint::math::vector2d retVec;
                if (neighbours.size() > 0)
                {
                    for (std::size_t i = 0; i < neighbours.size(); i++)
                    {
                        x = owner.location().x() - neighbours[i].get().location().x();
                        y = owner.location().x() - neighbours[i].get().location().y();
                        retVec += kmint::math::vector2d{ x,y };
                    }
                    steeringForce = retVec * -1;
                }
                return steeringForce;
            }
            // allignment
                // range kijken -> entiteiten die erin liggen
                // tel vectoren richting van de neighbours
                // normalizeer -> nieuwe richting
            kmint::math::vector2d SteeringBehaviours::alignment(MovingEntity& owner) {
                kmint::math::vector2d steeringForce;
                float xTotal = 0;
                float yTotal = 0;

                auto neighbours = getNeighbours(owner);
                std::vector<std::reference_wrapper<kmint::math::vector2d>> vectors;
                if (neighbours.size() > 0)
                {
                    for (std::size_t i = 0; i < neighbours.size(); i++)
                    {
                        xTotal += neighbours[i].get().getTarget().x();
                        yTotal += neighbours[i].get().getTarget().x();
                    }
                    steeringForce = { xTotal / neighbours.size(), yTotal / neighbours.size() };
                }
                return steeringForce;
            }

            // seek
                // dom naar huidige plaats
            kmint::math::vector2d SteeringBehaviours::seek(kmint::math::vector2d& loc, MovingEntity& owner) {
                kmint::math::vector2d desired = normalize(loc - owner.location() * owner.maxSpeed());
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
                throw std::exception("implement");
            }
            // wander   
                // puntje op circel, punt veranderen
            kmint::math::vector2d SteeringBehaviours::wander(kmint::math::vector2d& loc, MovingEntity& owner) {
                float r = ((rand()) / (RAND_MAX + 1.0));
                //first, add a small random vector to the target’s position (RandomClamped returns a value between -1 and 1)
                wanderTarget += kmint::math::vector2d(r * owner.wanderJitter(), r * owner.wanderJitter());
                //reproject this new vector back onto a unit circle
                normalize(wanderTarget);
                //increase the length of the vector to the same as the radius of the wander circle
                wanderTarget *= owner.wanderRadius();
                //move the target into a position WanderDist in front of the agent
                kmint::math::vector2d targetLocal = wanderTarget + kmint::math::vector2d(owner.wanderDistance(), 0);

                //project the target into world space
                kmint::math::vector2d targetWorld = pointToWorldSpace(targetLocal,
                    owner.heading(),
                    owner.side(),
                    owner.location()
                );

                //and steer toward it
                // TODO
                return targetWorld - owner.location();
                //return wanderTarget;
            }

            kmint::math::matrix<float> SteeringBehaviours::multiply(kmint::math::matrix<float> m1, kmint::math::matrix<float> m2) {
                if (m1.n_cols() != m2.n_rows()) throw std::exception("Invalid multiply matrices, columnA != rowB");

                kmint::math::matrix<float> retMatrix{ m1.n_rows(), m2.n_cols() };

                for (std::size_t i = 0; i < m1.n_rows(); ++i)
                    for (std::size_t j = 0; j < m2.n_cols(); ++j)
                        for (std::size_t k = 0; k < m2.n_rows(); ++k)
                            retMatrix(i, j) += m1(i, k) * m1(k, j);

                return retMatrix;
            }

            kmint::math::vector2d SteeringBehaviours::multiply(kmint::math::matrix<float> m1, const kmint::math::vector2d& vector) {
                float newX = 0;
                float newY = 0;

                for (int i = 0; i < m1.n_rows(); ++i) {
                    for (int j = 0; j < m1.n_cols(); ++j) {
                        if (i == 0) newX += m1(i, j) * vector.x();
                        else if (i == 1) newY += m1(i, j) * vector.y();
                    }
                }
                return  kmint::math::vector2d{ newX, newY };
            }

            kmint::math::vector2d SteeringBehaviours::pointToWorldSpace(const kmint::math::vector2d& point,
                    const kmint::math::vector2d& agentHeading,
                    const kmint::math::vector2d& agentSide, 
                    const kmint::math::vector2d& agentPosition
                )
            {
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

                auto newM = multiply(m3, m2);
                auto Mr = multiply(newM, m1);
                
                return multiply(Mr, point);
                // V Heading is je richting
                // V Perp is de vector haaks op de richting
                // V Target is de vector naar je doel
                // A is de hoek tussen V perp en V target!

                // V proj is de projectie van V target op V perp.In dit voorbeeld zit ie aan de andere kant(doe ik expres; -).
                // Als de lengte van V proj positief is, is het target links(aan de kant van V perp) en anders rechts.

                // De lengte van V proj bereken je :

                // Vtarget.length* cos(a)
                kmint::math::vector2d transPoint = point;

                return transPoint;
            }

            double SteeringBehaviours::calcVectorLength(kmint::math::vector2d target) {
                return std::sqrt(std::pow(target.x(), 2) + std::pow(target.y(), 2));
            }

            kmint::math::vector2d SteeringBehaviours::normalize(kmint::math::vector2d target)
            {
                double vector_length = calcVectorLength(target);

                if (vector_length > std::numeric_limits<double>::epsilon())
                {
                    target.x(target.x() / vector_length);
                    target.y(target.y() / vector_length);
                }
                return target;
            }

            // Truncated
            kmint::math::vector2d SteeringBehaviours::calculate(MovingEntity& owner) {
                math::vector2d steeringForce;
                steeringForce += wander(owner.location(), owner) * owner.seekWeight();
                // steeringForce += flee(owner.location(), owner) * fleeWeight;
                // steeringForce += persuit(owner.location(), owner) * persuitWeight;
                //// steeringForce += ObstacleAvoidance() * obstacleAvoidanceAmount
                steeringForce += cohesion(owner) * owner.cohesionWeight();
                steeringForce += separation(owner) * owner.separationWeight();
                steeringForce += alignment(owner) * owner.alignmentWeight();

                return truncate(steeringForce, owner.maxForce());
            }
        }
    }
}