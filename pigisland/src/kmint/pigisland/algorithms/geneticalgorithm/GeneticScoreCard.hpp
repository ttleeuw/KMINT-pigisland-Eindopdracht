#pragma once
#include "kmint/play/stage.hpp"
#include "Chromosome.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace geneticalgorithm 
		{
			class GeneticScoreCard
			{
			private:
				std::size_t round = 0;
				std::vector<Chromosome> savedChromosomes;
			public:
				GeneticScoreCard() { }

				void saveChromosome(Chromosome& s) { this->savedChromosomes.push_back(s); }
				void resetChromosomes() { savedChromosomes.clear(); round++; }
				std::vector<Chromosome>& getSavedChromosomes() { return savedChromosomes; }
			};
		}
	}
}
