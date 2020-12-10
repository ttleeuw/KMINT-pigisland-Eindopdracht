#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/finitestate/StateMachine.hpp"
#include "kmint/pigisland/algorithms/finitestate/boat/BoatWander.hpp"
#include "kmint/pigisland/algorithms/finitestate/boat/BoatGlobalState.hpp"
#include "kmint/pigisland/algorithms/finitestate/scorecard/ScoreCard.hpp"

namespace kmint {
	namespace pigisland {
		class boat : public play::map_bound_actor {
		public:
			boat(map::map_graph& g, map::map_node& initial_node, finitestate::ScoreCard& _scoreCard);
			// wordt elke game tick aangeroepen
			void act(delta_time dt) override;
			ui::drawable const& drawable() const override { return drawable_; }
			// als incorporeal false is, doet de actor mee aan collision detection
			bool incorporeal() const override { return false; }
			// geeft de lengte van een zijde van de collision box van deze actor terug.
			// Belangrijk voor collision detection
			scalar collision_range() const override { return 16.0; }

			void setTint(kmint::graphics::color tint) { this->drawable_.set_tint(tint); }
			void removeTint() { this->drawable_.remove_tint(); }

			finitestate::StateMachine<boat>& getStateMachine() { return this->stateMachine; }
			map::map_graph& getGraph() { return graph; }
			std::size_t getPaintDamage() { return paintDamge; }
			void repair(int repairValue) { paintDamge -= repairValue; }
			void increasePaintDamage() { paintDamge++; }
		private:
			finitestate::StateMachine<boat> stateMachine;

			map::map_graph& graph;

			finitestate::ScoreCard& scoreCard;
			std::size_t paintDamge = 0;
			// hoeveel tijd is verstreken sinds de laatste beweging
			delta_time t_passed_{};
			// weet hoe de koe getekend moet worden
			play::image_drawable drawable_;
		};
	}
}
#endif /* KMINT_PIGISLAND_BOAT_HPP */
