#pragma once
#include <array>
#include "kmint/random.hpp"
#include <vector>

namespace kmint
{
	namespace pigisland
	{
		namespace geneticalgorithm
		{
			class Chromosome
			{
				std::vector<float> chromosomes{ 0, 0, 0, 0, 0 };
			public:
				Chromosome()
				{
					chromosomes[0] = random_scalar(-1.0f, 1.0f); // shark
					chromosomes[1] = random_scalar(-1.0f, 1.0f); // boat
					chromosomes[2] = random_scalar(0.0f, 1.0f);  // cohesion
					chromosomes[3] = random_scalar(0.0f, 1.0f);  // seperation
					chromosomes[4] = random_scalar(0.0f, 1.0f);  // alignment
				}

				//[0] = shark
				//[1] = boat
				//[2] = cohesion
				//[3] = separation
				//[4] = alignment
				std::vector<float>& get() { return chromosomes; }
			};
		}
	}
}
