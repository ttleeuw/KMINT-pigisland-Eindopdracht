//#include "SteeringBehaviours.hpp"
//#include "kmint/pigisland/entities/pig.hpp"
//
//namespace kmint {
//    namespace pigisland {
//        // mass -> vast
//        // force -> variabel 
//        // acceleration -> berekenen (vanuit kracht en force)
//        // velocity -> berekenen
//        // position -> berekenen
//
//        // setAcceleration() => force() / mass()
//        // setVelocity() => velocity() + acceleration * dt
//                // Add max velocity
//        // setPosition() => position() + velocity * dt
//
//        // achtervolgen
//            // seek
//                // dom naar huidige plaats
//            // persuit
//                // voorspellen welke plaats
//                // hoe ver vooruit?
//            // wander   
//                // puntje op circel, punt veranderen
//
//        // flocing
//            // seperation
//                // range kijken -> entiteiten die erin liggen
//                // tel vectoren richting neighbours
//                // ga andere kant op van die uitkomst
//            // allignment
//                // range kijken -> entiteiten die erin liggen
//                // tel vectoren richting van de neighbours
//                // normalizeer -> nieuwe richting
//            // cohesion
//                // rangekijken -> middelpunt van alle neighbours
//
//        // wall avoidance
//            // feelers
//        // bstacle avoidance
//        namespace forcedrivenentities {
//            std::vector<kmint::play::actor&> SteeringBehaviours::getNeighbours(pig& owner) {
//                std::vector<pig*> returnVector;
//                for (std::size_t i = 0; i < owner.num_perceived_actors(); ++i)
//                {
//                    auto& actor = owner.perceived_actor(i);
//                    /*if (pig& p = dynamic_cast<pig&>(actor)) {
//                        returnVector.push_back(actor);
//                    }*/
//                }
//            }
//            math::vector2d SteeringBehaviours::cohesion(pig& owner) {
//
//            }
//            math::vector2d SteeringBehaviours::separation(pig& owner) {
//
//            }
//            math::vector2d SteeringBehaviours::alignment(pig& owner) {
//
//            }
//
//
//
//
//            // TODO
//            math::vector2d SteeringBehaviours::seek(math::vector2d& loc) {
//
//            }
//            math::vector2d SteeringBehaviours::flee(math::vector2d& loc) {
//
//            }
//            math::vector2d SteeringBehaviours::persuit(math::vector2d& loc) {
//
//            }
//            math::vector2d SteeringBehaviours::wander(math::vector2d& loc) {
//
//            }
//        }
//    }
//}