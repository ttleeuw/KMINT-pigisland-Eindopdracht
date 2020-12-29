#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/entities/base/MapActor.hpp"
#include "kmint/pigisland/algorithms/finitestate/StateMachine.hpp"
#include "kmint/pigisland/algorithms/finitestate/boat/BoatWander.hpp"
#include "kmint/pigisland/algorithms/finitestate/boat/BoatGlobalState.hpp"
#include "kmint/pigisland/algorithms/finitestate/scorecard/BoatDockingScoreCard.hpp"
#include "kmint/pigisland/entities/DockingStation.hpp"
#include "kmint/pigisland/algorithms/geneticalgorithm/GeneticScoreCard.hpp"

namespace kmint {
	namespace pigisland {
		class boat : public MapActor {
		public:
			boat(map::map_graph& g, map::map_node& initial_node, finitestate::BoatDockingScoreCard& _scoreCard);
			boat(map::map_graph& g, map::map_node& initial_node, finitestate::BoatDockingScoreCard& _scoreCard, geneticalgorithm::GeneticScoreCard& _geneticScoreCard);
			
			void act(delta_time dt) override;

			finitestate::StateMachine<boat>& getStateMachine() { return this->stateMachine; }
			finitestate::BoatDockingScoreCard& getScoreCard() { return this->scoreCard; }

			bool perceptive() const override { return false; }
			scalar perception_range() const override { return 0.f; }

			std::size_t getPaintDamage() { return steps; }
			void repair(DockingStation dockingStation, int repairValue);
			void increasePaintDamage() { steps++; }
			void savePig();

			void reset() override;
		private:
			geneticalgorithm::GeneticScoreCard* geneticScoreCard = nullptr;
			finitestate::StateMachine<boat> stateMachine;
			finitestate::BoatDockingScoreCard& scoreCard;
		};
	}
}
#endif /* KMINT_PIGISLAND_BOAT_HPP */
