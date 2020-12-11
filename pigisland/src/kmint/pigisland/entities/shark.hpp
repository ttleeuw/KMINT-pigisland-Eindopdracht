#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/entities/base/MapActor.hpp"
#include "kmint/pigisland/algorithms/finitestate/StateMachine.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkWander.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkGlobalState.hpp"

namespace kmint {
	namespace pigisland {
		class shark : public MapActor {
		public:
			shark(map::map_graph& g, map::map_node& initial_node);

			void act(delta_time dt) override;

			// geeft aan dat de haai andere actors kan zien
			bool perceptive() const override { return true; }
			// geeft het bereik aan waarbinnen een haai andere actors kan waarnemen.
			scalar perception_range() const override { return 200.f; }

			finitestate::StateMachine<shark>& getStateMachine() { return this->stateMachine; }
			void setResting(bool _resting) { this->resting = _resting; }
			bool isResting() const { return this->resting; }
			bool shouldFlee();
			void eatPig();
			void reset() override;
		private:
			finitestate::StateMachine<shark> stateMachine;
			bool resting = false;
		};
	} // namespace pigisland
} // namespace kmint
#endif /* KMINT_PIGISLAND_SHARK_HPP */
