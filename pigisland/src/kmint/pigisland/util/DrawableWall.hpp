#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/math/vector2d.hpp"

namespace kmint {
    namespace pigisland {
        class DrawableWall : public play::free_roaming_actor
        {
        public:
            DrawableWall(math::vector2d location) : play::free_roaming_actor{ location }, drawable_{ *this,  graphics::image{boat_image()} }
            {
            }

			const ui::drawable& drawable() const override { return drawable_; }

			bool incorporeal() const override { return false; }
			scalar collision_range() const override { return 16.0; }

			bool perceptive() const override { return false; }
			scalar perception_range() const override { return 200.f; }
			virtual void act(delta_time dt) override {}

		protected:
			delta_time t_passed_{};
			play::image_drawable drawable_;
        };
    }
}
