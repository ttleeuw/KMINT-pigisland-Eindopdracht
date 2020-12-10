#pragma once
#include <map>
#include <vector>

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            struct ScoreData {
                int pigsSaved = 0;
                int receivedDamage = 0;
            };
            class ScoreCard
            {
            private:
                int pigsSaved = 0;
                int receivedDamage = 0;

                int effectiveness() {
                    return pigsSaved + receivedDamage / 4;
                }

                int transitionWeight() {
                    this->effectiveness() / (currentRound / effectiveness());
                }

                int currentRound = 1;

                int dockOneChange = 33;
                int dockTwoChange = 33;
                int dockThreeChange = 33;

                std::unordered_map<int, std::vector<int>> history =
                {
                    {1,{}},
                    {2,{}},
                    {3,{}}
                };
            public:
                void dock(int repair, int dockingStation) {
                    history[dockingStation].push_back(repair);
                }

                void print() const
                {
                    std::cout << "Dock 1 chance: " << dockOneChange << "\n" 
                              << "Dock 2 chance: " << dockTwoChange << "\n" 
                              << "Dock 3 chance: " << dockThreeChange << "\n";
                }

                void newRound()
                {
                    currentRound++;
                    pigsSaved = 0;
                    receivedDamage = 0;
                }
            };
        }
    }
}