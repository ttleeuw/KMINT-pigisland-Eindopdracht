#pragma once
#include <queue>
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

namespace kmint {
	namespace pigisland {
		class MapActor : public play::map_bound_actor {
		public:
			MapActor(map::map_graph& g, map::map_node& initial_node, play::actor const& owner, graphics::image image);

			virtual void act(delta_time dt) override = 0;

			// als incorporeal false is, doet de actor mee aan collision detection
			bool incorporeal() const override { return false; }
			// geeft de lengte van een zijde van de collision box van deze actor terug.
			// Belangrijk voor collision detection
			scalar collision_range() const override { return 16.0; }

			ui::drawable const& drawable() const override { return drawable_; }
			void setTint(kmint::graphics::color tint) { this->drawable_.set_tint(tint); }
			void removeTint() { this->drawable_.remove_tint(); }

			map::map_graph& getGraph() { return graph; }
			map::map_node& getInitialNode() { return initial; }
			std::size_t getSteps() const { return steps; }
			void increaseSteps() { steps++; }
			bool getCanMove() { return canMove; };

			void moveRandomly();
			void moveWithPath(std::queue<int>& path);
			bool waitIfNecessary();
		protected:
			std::size_t steps = 0;

			map::map_graph& graph;
			map::map_node& initial;
			int waitTimer = 0;
			bool canMove = true;

			delta_time t_passed_{};
			play::image_drawable drawable_;
		};
	} // namespace pigisland
} // namespace kmint
