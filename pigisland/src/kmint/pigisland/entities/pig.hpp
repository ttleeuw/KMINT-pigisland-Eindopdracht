#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include <tuple>
#include <vector>
#include "kmint/pigisland/entities/base/MovingEntity.hpp"
#include <kmint/pigisland/algorithms/geneticalgorithm/Chromosome.hpp>

namespace kmint {
	namespace pigisland {
		class pig : public MovingEntity {
		private:
			geneticalgorithm::Chromosome chromosome;
		public:
			pig::pig(math::vector2d location, boat& boat, shark& shark);
			pig::pig(math::vector2d location, boat& boat, shark& shark, geneticalgorithm::Chromosome chromosome);

			void act(delta_time dt) override;
			geneticalgorithm::Chromosome& getChromosome() { return chromosome; }

			int fitness = 0;
			bool safe = false;
		};
	} 
} 
#endif 
