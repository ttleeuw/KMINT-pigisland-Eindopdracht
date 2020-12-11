#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/entities/base/MapActor.hpp"
#include "kmint/pigisland/algorithms/finitestate/StateMachine.hpp"
#include "kmint/pigisland/algorithms/finitestate/boat/BoatWander.hpp"
#include "kmint/pigisland/algorithms/finitestate/boat/BoatGlobalState.hpp"
#include "kmint/pigisland/algorithms/finitestate/scorecard/ScoreCard.hpp"
#include "kmint/pigisland/entities/DockingStation.hpp"

namespace kmint {
	namespace pigisland {
		class boat : public MapActor {
		public:
			boat(map::map_graph& g, map::map_node& initial_node, finitestate::ScoreCard& _scoreCard);
			// wordt elke game tick aangeroepen
			void act(delta_time dt) override;

			// geeft de lengte van een zijde van de collision box van deze actor terug.
			// Belangrijk voor collision detection
			scalar collision_range() const override { return 16.0; }


			finitestate::StateMachine<boat>& getStateMachine() { return this->stateMachine; }

			std::size_t getPaintDamage() { return steps; }
			void repair(DockingStation dockingStation, int repairValue) { 
				scoreCard.dock(dockingStation, repairValue);
				steps -= repairValue; 
			}
			void increasePaintDamage() { steps++; }
			void savePig();
		private:
			finitestate::StateMachine<boat> stateMachine;
			finitestate::ScoreCard& scoreCard;
		};
	}
}
#endif /* KMINT_PIGISLAND_BOAT_HPP */
