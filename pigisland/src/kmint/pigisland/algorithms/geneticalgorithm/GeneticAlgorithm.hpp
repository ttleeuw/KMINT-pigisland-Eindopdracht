#pragma once
#include <vector>
#include "kmint/play/stage.hpp"
#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/algorithms/geneticalgorithm/GeneticScoreCard.hpp"

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
				GeneticScoreCard& scoreCard;
			public:
				GeneticAlgorithm(play::stage& s, GeneticScoreCard& sc) : stage(s), scoreCard(sc) { }

				void create_generation_0(shark& shark, boat& boat)
				{
					std::vector<pig*> m;
					auto locs = pigisland::random_pig_locations(100);
					for (auto loc : locs) {
						pig& p = stage.build_actor<pigisland::pig>(loc, boat, shark, Chromosome{});
						pigs.push_back(p);
					}
				}

				void new_generation(shark& shark, boat& boat, GeneticScoreCard& scorecard) {
					std::vector<Chromosome> new_generation_chromosomes;

					//Pigs that got saved are automatically added to new generation because of elitism
					for (Chromosome& ch : scorecard.getSavedChromosomes())
					{
						new_generation_chromosomes.push_back(ch);
					}

					const int number_of_pigs_to_generate = 100 - scorecard.getSavedChromosomes().size();

					//Get left over pigs
					std::vector<play::actor*> left_over_pigs{};
					for (play::actor& a : stage)
					{
						if (typeid(a) == typeid(pig))
							left_over_pigs.push_back(&a);
					}

					//If the shark ate all the pigs -> restart
					if (left_over_pigs.empty() && scorecard.getSavedChromosomes().empty())
					{
						create_generation_0(shark, boat);
						return;
					}

					//Fitness = boat reached is good
					//Get a parent from the boat and pair it with a left over pig(left over pig survived too so should have something good(or luck))
					for (int i = 0; i < number_of_pigs_to_generate; ++i)
					{
						Chromosome random_parent_a;
						Chromosome random_parent_b;

						if (!scorecard.getSavedChromosomes().empty())
							random_parent_a = scorecard.getSavedChromosomes().at(random_int(0, scorecard.getSavedChromosomes().size()));
						else
							random_parent_a = dynamic_cast<pigisland::pig*>(left_over_pigs.at(random_int(0, left_over_pigs.size())))->getChromosome();

						if (!left_over_pigs.empty())
							random_parent_b = dynamic_cast<pigisland::pig*>(left_over_pigs.at(random_int(0, left_over_pigs.size())))->getChromosome();
						else
							random_parent_b = scorecard.getSavedChromosomes().at(random_int(0, scorecard.getSavedChromosomes().size()));

						const int splice_point = random_int(1, 5);
						Chromosome child{};

						for (int j = 0; j < splice_point; ++j)
						{
							child.get().at(j) = random_parent_a.get().at(j);
						}
						for (int k = splice_point; k < 5; ++k)
						{
							child.get().at(k) = random_parent_b.get().at(k);
						}

						new_generation_chromosomes.push_back(child);
					}

					//Mutate one child with a chance of 1/100.
					if (random_int(0, 100) == 67)
					{
						const int random_child = random_int(0, 100);
						const int random_gene = random_int(0, 5);

						if (random_gene > 1)
							new_generation_chromosomes.at(random_child).get().at(random_gene) = random_scalar(0.0f, 1.0f);
						else
							new_generation_chromosomes.at(random_child).get().at(random_gene) = random_scalar(-1.0f, 1.0f);
					}

					//Remove old still living pigs
					for (auto actor : left_over_pigs)
					{
						stage.remove_actor(*actor);
					}
					left_over_pigs.clear();

					//Build new generation
					auto locs = pigisland::random_pig_locations(100);
					for (auto loc : locs) {
						pigs.push_back(stage.build_actor<pigisland::pig>(loc, boat, shark, Chromosome{}));
					}

					// TODO reset saved chromosomes
				}
			};
		}
	}
}
