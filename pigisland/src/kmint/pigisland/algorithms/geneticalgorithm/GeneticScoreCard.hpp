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
				std::vector<Chromosome> savedFittestChromosomes;
				std::vector<Chromosome> savedLeastFittestChromosomes;
			public:
				GeneticScoreCard() { }

				void saveFittestChromosome(Chromosome& s) { 
					this->savedFittestChromosomes.push_back(s); 
				}				
				void saveLeastFittestChromosome(Chromosome& s) {
					this->savedLeastFittestChromosomes.push_back(s);
				}
				void resetChromosomes() { 
					savedFittestChromosomes.clear();
					savedLeastFittestChromosomes.clear();
					round++; 
				}
				std::vector<Chromosome>& getSavedFittestChromosomes() { return savedFittestChromosomes; }
				std::vector<Chromosome>& getSavedLeastFittestChromosomes() { return savedLeastFittestChromosomes; }
			};
		}
	}
}
