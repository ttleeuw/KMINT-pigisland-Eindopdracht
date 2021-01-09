
#pragma once
#include <vector>
#include <filesystem>
#include "kmint/play/stage.hpp"
#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/algorithms/geneticalgorithm/GeneticScoreCard.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <string>

namespace kmint
{
	namespace pigisland
	{
		namespace geneticalgorithm
		{
			class GeneticAlgorithm
			{
			private:
				std::vector<std::reference_wrapper<pig>> pigs;
				play::stage& stage;
				GeneticScoreCard& scorecard;
			public:
				std::vector<std::reference_wrapper<pig>>& getPigs() { return this->pigs; };
				GeneticAlgorithm(play::stage& s, GeneticScoreCard& sc);

				std::vector<std::reference_wrapper<Chromosome>> getRandomBasedOnFitness(std::map<int, std::vector<std::reference_wrapper<Chromosome>>>& oldgen);
				void create_generation_0(shark& shark, boat& boat);
				void new_generation(shark& shark, boat& boat);
				void crossOver(std::map<int, std::vector<std::reference_wrapper<Chromosome>>> newgen, std::vector<Chromosome>& newGenChromosomes);
				void mutate(std::vector<Chromosome>& newGenChromosomes);
			};
		}
	}
}