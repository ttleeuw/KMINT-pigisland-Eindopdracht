#pragma once
#include <map>
#include <vector>
#include "kmint/pigisland/entities/DockingStation.hpp"
#include "kmint/random.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            class BoatDockingScoreCard
            {
            private:
                std::unordered_map<DockingStation, std::vector<int>> history =
                {
                    {DockingStation::DOCK_ONE,{}},
                    {DockingStation::DOCK_TWO,{}},
                    {DockingStation::DOCK_THREE,{}}
                };

                int currentRound = 1;

                int dockOneChance;
                int dockTwoChance;
                int dockThreeChance;
            public:
                BoatDockingScoreCard() {
                    dockOneChance = 100 / 3;
                    dockTwoChance = 100 / 3;
                    dockThreeChance = 100 / 3;
                }

                void dock(DockingStation dockingStation, int repair) {
                    history[dockingStation].emplace_back(repair); 
                }

                void print() const
                {
                    std::cout << "Dock 1 chance: " << dockOneChance << "\n" 
                              << "Dock 2 chance: " << dockTwoChance << "\n"
                              << "Dock 3 chance: " << dockThreeChance << "\n";
                }

                DockingStation getRandomDock() {
                    int result = random_int(0, dockOneChance + dockTwoChance + dockThreeChance);

                    if (result < dockOneChance) return DockingStation::DOCK_ONE;
                    else if(result < dockOneChance + dockTwoChance) return DockingStation::DOCK_TWO;
                    else return DockingStation::DOCK_THREE;
                }

                void newRound() { currentRound++; this->adjustChances(); }

                void adjustChances() {

                    int counter = 0;
                    for (size_t i = 0; i < history.size(); i++) {
                        if (history[(DockingStation)(i + 1)].size() != 0) counter++;
                    };

                    if (counter == 2) {
                        adjustChangesHistoryTwo();
                    }
                    else if (counter == 3) {
                        adjustChangesHistoryThree();
                    }
                }


                void adjustChangesHistoryTwo() {
                    float totalChance = (100 / 3) * 2;
                    std::unordered_map<DockingStation, int> avarageMap;
                    int totalRepaird = 0;

                    for (size_t i = 0; i < history.size(); i++) {
                        if (history[(DockingStation)(i + 1)].size() == 0) {
                            switch ((DockingStation)(i + 1))
                            {
                            case DockingStation::DOCK_ONE:
                                dockOneChance = 100 / 3;
                                break;
                            case DockingStation::DOCK_TWO:
                                dockTwoChance = 100 / 3;
                                break;
                            case DockingStation::DOCK_THREE:
                                dockThreeChance = 100 / 3;
                                break;
                            default:
                                break;
                            }
                            continue;
                        }
                        else {
                            int total = 0;
                            int amount = 0;
                            for (size_t j = 0; j < history[(DockingStation)(i + 1)].size(); j++)
                            {
                                total += history[(DockingStation)(i + 1)][j];
                                amount++;
                            }
                            totalRepaird += total / amount;
                            avarageMap.insert(std::make_pair((DockingStation)(i + 1), total / amount));
                        }
                    }
                    this->setChanges(avarageMap, totalChance, totalRepaird);
                }

                void setChanges(std::unordered_map<DockingStation, int> avarageMap, float totalChance, float totalRepaird) {
                    for (auto& it : avarageMap) {
                        switch (it.first)
                        {
                        case DockingStation::DOCK_ONE:
                            dockOneChance = totalChance / totalRepaird * it.second;
                            break;
                        case DockingStation::DOCK_TWO:
                            dockTwoChance = totalChance / totalRepaird * it.second;
                            break;
                        case DockingStation::DOCK_THREE:
                            dockThreeChance = totalChance / totalRepaird * it.second;
                            break;
                        default:
                            break;
                        }
                    }
                }

                void adjustChangesHistoryThree() {
                    float totalChance = 100;
                    std::unordered_map<DockingStation, int> avarageMap;
                    int totalRepaird = 0;

                    for (size_t i = 0; i < history.size(); i++) {
                        int total = 0;
                        int amount = 0;
                        for (size_t j = 0; j < history[(DockingStation)(i + 1)].size(); j++)
                        {
                            total += history[(DockingStation)(i + 1)][j];
                            amount++;
                        }
                        totalRepaird += total / amount;
                        avarageMap.insert(std::make_pair((DockingStation)(i + 1), total / amount));
                    }
                    this->setChanges(avarageMap, totalChance, totalRepaird);
                }
            };
        }
    }
}