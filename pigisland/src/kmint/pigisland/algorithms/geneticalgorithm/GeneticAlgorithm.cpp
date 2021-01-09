#include "GeneticAlgorithm.hpp"
#include "kmint/pigisland/resources/resources.hpp"

#define MAX_FITNESS 8
#define MED_FITNESS	3
#define LOW_FITNESS	1
#define MUTATION_CHANCE 1000

#define OLD_GEN_POPULATION 20

namespace kmint
{
	namespace pigisland
	{
		namespace geneticalgorithm
		{
			GeneticAlgorithm::GeneticAlgorithm(play::stage& s, GeneticScoreCard& sc) : stage(s), scorecard(sc) { }

			void GeneticAlgorithm::create_generation_0(shark& shark, boat& boat)
			{
				std::vector<pig*> m;
				auto locs = pigisland::random_pig_locations(100);
				for (auto loc : locs) { pigs.push_back(stage.build_actor<pigisland::pig>(loc, boat, shark, Chromosome{})); }
			}

			void GeneticAlgorithm::new_generation(shark& shark, boat& boat) {
				// Fitness
				std::vector<Chromosome> newGenChromosomes;

				std::map<int, std::vector<std::reference_wrapper<Chromosome>>> oldgen;
				for (Chromosome& chromosome : scorecard.getSavedFittestChromosomes()) {
					oldgen[MAX_FITNESS].push_back(chromosome);
				}
				for (Chromosome& chromosome : scorecard.getSavedLeastFittestChromosomes()) {
					oldgen[LOW_FITNESS].push_back(chromosome);
				}
				std::vector<pig*> alivePigs;
				for (play::actor& actor : stage)
				{
					if (typeid(actor) == typeid(pig)) {
						auto p = dynamic_cast<pig*>(&actor);
						oldgen[MED_FITNESS].push_back(p->getChromosome());
						alivePigs.push_back(p);
					}
				}

				crossOver(oldgen, newGenChromosomes);
				mutate(newGenChromosomes);

				for (size_t i = 0; i < OLD_GEN_POPULATION; i++)
				{
					auto randomParentList = getRandomBasedOnFitness(oldgen);
					newGenChromosomes.push_back(randomParentList[random_int(0, randomParentList.size())]);
				}
				// Repopulate
				for (auto actor : alivePigs) { stage.remove_actor(*actor); }
				alivePigs.clear();
				auto locs = pigisland::random_pig_locations(100);
				for (size_t i = 0; i < locs.size(); i++)
				{
					if (i == 79) {
						int x = 9;
					}
					pigs.push_back(stage.build_actor<pigisland::pig>(locs[i], boat, shark, newGenChromosomes[i]));
				}
				scorecard.resetChromosomes();
			}

			std::vector<std::reference_wrapper<Chromosome>> GeneticAlgorithm::getRandomBasedOnFitness(std::map<int, std::vector<std::reference_wrapper<Chromosome>>>& oldgen) {
				auto randomInt = random_int(1, MAX_FITNESS + MED_FITNESS + LOW_FITNESS);
				if (randomInt <= MAX_FITNESS) {
					if (oldgen[MAX_FITNESS].size()) {
						return oldgen[MAX_FITNESS];
					}
					else {
						return oldgen[MED_FITNESS];
					}
				}
				else if(randomInt <= MAX_FITNESS + MED_FITNESS) {
					if (oldgen[MED_FITNESS].size() > 0) {
						return oldgen[MED_FITNESS];
					}
					else {
						return oldgen[MAX_FITNESS];
					}
				}
				else {
					if (oldgen[LOW_FITNESS].size() > 0) {
						return oldgen[LOW_FITNESS];
					}
					else {
						return oldgen[MED_FITNESS];
					}
				}
			}

			void GeneticAlgorithm::crossOver(std::map<int, std::vector<std::reference_wrapper<Chromosome>>> oldgen, std::vector<Chromosome>& newGenChromosomes) {
				// Crossover
				for (int i = 0; i < 100 - OLD_GEN_POPULATION; ++i)
				{
					Chromosome firstParent;

					auto randomV = getRandomBasedOnFitness(oldgen);
					firstParent = randomV[random_int(0, randomV.size())];

					Chromosome secondParent;
					randomV = getRandomBasedOnFitness(oldgen);
					secondParent = randomV[random_int(0, randomV.size())];

					const int splicePoint = random_int(1, 4);
					Chromosome child;
					for (int a = 0; a < splicePoint; ++a)
					{
						child.get()[a] = firstParent.get()[a];
					}
					for (int b = splicePoint; b < secondParent.get().size(); ++b)
					{
						child.get()[b] = secondParent.get()[b];
					}

					newGenChromosomes.push_back(child);
				}
			}

			void GeneticAlgorithm::mutate(std::vector<Chromosome>& newGenChromosomes) {
				if (random_int(0, MUTATION_CHANCE) == 190)
				{
					const int randomGene = random_int(0, 5);
					// Check wheter scalar can be < 0 
					randomGene <= 1 ? newGenChromosomes.at(random_int(0, 100)).get().at(randomGene) = random_scalar(-1.0f, 1.0f) :
						newGenChromosomes.at(random_int(0, 100)).get().at(randomGene) = random_scalar(0.0f, 1.0f);
				}
			}
		};
	}
}