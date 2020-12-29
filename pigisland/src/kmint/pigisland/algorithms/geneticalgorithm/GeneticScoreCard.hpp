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
				std::size_t pigsEaten = 0;
				std::size_t pigsSaved = 0;

				std::vector<Chromosome> savedChromosomes;
			public:
				GeneticScoreCard()
				{
				}

				std::size_t pigs_eaten() const { return pigsEaten; }
				std::size_t pigs_saved() const { return pigsSaved; }
				void pig_eaten() { pigsEaten++; }
				void pig_saved() { pigsSaved++; }
				void reset_pigs_eaten() { pigsEaten = 0; }
				void reset_pigs_saved() { pigsSaved = 0; }
				std::vector<Chromosome>& getSavedChromosomes() { return savedChromosomes; }
			};
		}
	}
}
