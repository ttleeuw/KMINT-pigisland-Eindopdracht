#include "SteeringBehaviours.hpp"
#include "kmint/pigisland/entities/pig.hpp"
#include <cmath>

namespace kmint {
    namespace pigisland {
        // wall avoidance
            // feelers
        // ostacle avoidance
        namespace forcedrivenentities {
            std::vector<std::reference_wrapper<pig>> SteeringBehaviours::getNeighbours(pig& owner) {
                std::vector<std::reference_wrapper<pig>> returnVector;
                for (std::size_t i = 0; i < owner.num_perceived_actors(); ++i)
                {
                    auto& actor = owner.perceived_actor(i);
                    if (typeid(actor) == typeid(pig)) {
                        auto p = dynamic_cast<pig*>(&actor);
                        returnVector.push_back(*p);
                    }
                }
                return returnVector;
            }

            // cohesion
                // rangekijken -> middelpunt van alle neighbours
            math::vector2d SteeringBehaviours::cohesion(pig& owner) {
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
            math::vector2d SteeringBehaviours::separation(pig& owner) {
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
            math::vector2d SteeringBehaviours::alignment(pig& owner) {
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
            math::vector2d SteeringBehaviours::seek(math::vector2d& loc, pig& owner) {
                kmint::math::vector2d desired = normalize(loc - owner.location() * maxSpeed);
                return (desired - velocity);
            }
            // TODO
            // persuit
                // voorspellen welke plaats
                // hoe ver vooruit?
            math::vector2d SteeringBehaviours::persuit(math::vector2d& loc, pig& owner) {
                throw std::exception("implement");
            }
            // wander   
                // puntje op circel, punt veranderen
            math::vector2d SteeringBehaviours::wander(math::vector2d& loc, pig& owner) {
                float r = ((rand()) / (RAND_MAX + 1.0));
                //first, add a small random vector to the target’s position (RandomClamped returns a value between -1 and 1)
                wanderTarget += kmint::math::vector2d(r * wanderJitter, r * wanderJitter);
                //reproject this new vector back onto a unit circle
                normalize(wanderTarget);
                //increase the length of the vector to the same as the radius of the wander circle
                wanderTarget *= wanderRadius;
                //move the target into a position WanderDist in front of the agent
                kmint::math::vector2d targetLocal = wanderTarget + kmint::math::vector2d(wanderDistance, 0);

                //project the target into world space
                /*kmint::math::vector2d targetWorld = pointToWorldSpace(targetLocal,
                    owner.heading(),
                    owner.(),
                    owner.location()
                );*/

                //and steer toward it
                // TODO
                //return targetWorld - owner.location();
                return owner.location();
            }

            kmint::math::vector2d pointToWorldSpace(const kmint::math::vector2d& point, 
                    const kmint::math::vector2d& AgentHeading,
                    const kmint::math::vector2d& AgentSide, 
                    const kmint::math::vector2d& AgentPosition
                )
            {
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
        }
    }
}