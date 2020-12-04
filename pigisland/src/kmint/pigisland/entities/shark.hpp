#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/finitestate/StateMachine.hpp"

namespace kmint {
	namespace pigisland {
		class shark : public play::map_bound_actor {
		public:
			shark(map::map_graph &g, map::map_node &initial_node);
			// wordt elke game tick aangeroepen
			void act(delta_time dt) override;
			ui::drawable const &drawable() const override { return drawable_; }
			// als incorporeal false is, doet de actor mee aan collision detection
			bool incorporeal() const override { return false; }
			// geeft de lengte van een zijde van de collision box van deze actor terug. Belangrijk voor collision detection
			scalar collision_range() const override { return 16.0; }
			// geeft aan dat de haai andere actors kan zien
			bool perceptive() const override { return true; }
			// geeft het bereik aan waarbinnen een haai andere actors kan waarnemen.
			scalar perception_range() const override { return 200.f; }

			void setTint(kmint::graphics::color tint) { this->drawable_.set_tint(tint); }
			void removeTint() { this->drawable_.remove_tint(); }

			map::map_graph& getGraph() { return graph; }
			map::map_node& getInitialNode() { return initial; }
			std::size_t getSteps() { return steps; }
			void increaseSteps() { steps++; }

			finitestate::StateMachine<shark>& getStateMachine() { return this->stateMachine; }
		private:
			std::size_t steps = 0;

			finitestate::StateMachine<shark> stateMachine;
			// hoeveel tijd is verstreken sinds de laatste beweging
			delta_time t_passed_{};

			map::map_graph& graph;
			map::map_node& initial;

			// weet hoe de koe getekend moet worden
			play::image_drawable drawable_;
		};
	} // namespace pigisland
} // namespace kmint
#endif /* KMINT_PIGISLAND_SHARK_HPP */
