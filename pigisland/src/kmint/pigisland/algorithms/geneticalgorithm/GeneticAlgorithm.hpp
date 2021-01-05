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
				GeneticAlgorithm(play::stage& s, GeneticScoreCard& sc) : stage(s), scorecard(sc) { }

				void create_generation_0(shark& shark, boat& boat)
				{
					std::vector<pig*> m;
					auto locs = pigisland::random_pig_locations(100);
					for (auto loc : locs) { pigs.push_back(stage.build_actor<pigisland::pig>(loc, boat, shark, Chromosome{})); }
				}

				void new_generation(shark& shark, boat& boat) {
					// Fitness
					std::vector<Chromosome> newGenChromosomes;
					for (Chromosome& chromosome : scorecard.getSavedChromosomes()) { newGenChromosomes.push_back(chromosome); }

					// Initialize new population
					std::vector<play::actor*> alivePigs{};
					for (play::actor& actor : stage)
					{
						if (typeid(actor) == typeid(pig)) {
							auto p = dynamic_cast<pig*>(&actor);
							p->fitness += 3;
							alivePigs.push_back(&actor);
						}
					}

					saveChromosomes(alivePigs);
					crossOver(scorecard.getSavedChromosomes(), alivePigs, newGenChromosomes);
					mutate(newGenChromosomes);

					// Repopulate
					for (auto actor : alivePigs) { stage.remove_actor(*actor); }
					alivePigs.clear();
					auto locs = pigisland::random_pig_locations(100);
					for (auto loc : locs) { pigs.push_back(stage.build_actor<pigisland::pig>(loc, boat, shark, newGenChromosomes[rand() % newGenChromosomes.size()])); }

					scorecard.resetChromosomes();
				}

				void saveChromosomes(std::vector<play::actor*>& alivePigs) {
					for (play::actor* actor : alivePigs) {
						auto pig = dynamic_cast<kmint::pigisland::pig*>(actor);
						if (pig->fitness >= 5) {
							scorecard.saveChromosome(pig->getChromosome());
						}
					}
				}

				void crossOver(std::vector<Chromosome>& fittest, std::vector<play::actor*>& alivePigs, std::vector<Chromosome>& newGenChromosomes) {
					const int number_of_pigs_to_generate = 100 - fittest.size();
					// Crossover
					for (int i = 0; i < number_of_pigs_to_generate; ++i)
					{
						Chromosome firstParent;

						if (!fittest.empty())
						{
							firstParent = fittest[random_int(0, fittest.size())];
						}
						else
						{
							firstParent = dynamic_cast<pigisland::pig*>(alivePigs[random_int(0, alivePigs.size())])->getChromosome();
						}

						Chromosome secondParent;
						if (!alivePigs.empty())
						{
							secondParent = dynamic_cast<pigisland::pig*>(alivePigs[random_int(0, alivePigs.size())])->getChromosome();
						}
						else
						{
							secondParent = fittest[random_int(0, fittest.size())];
						}

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

				void mutate(std::vector<Chromosome>& newGenChromosomes) {
					if (random_int(0, 1000) == 190)
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
}
