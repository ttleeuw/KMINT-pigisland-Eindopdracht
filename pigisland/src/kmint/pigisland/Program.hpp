#pragma once
#include "kmint/main.hpp" // voor de main loop
#include "kmint/math/intersection.hpp"
#include "kmint/math/rectangle.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/finitestate/scorecard/BoatDockingScoreCard.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>
#include <kmint/pigisland/algorithms/geneticalgorithm/GeneticScoreCard.hpp>
#include <kmint/pigisland/algorithms/geneticalgorithm/GeneticAlgorithm.hpp>

class Program {
private:
    // een app object is nodig om
    kmint::ui::app app{};
    //  maak een venster aan
    kmint::ui::window window{ app.create_window({1024, 768}, "pigisland", 1.0) };
    // maak een podium aan
    kmint::play::stage stage{ {1024, 768} };
public:
	void initGenetic();
	void initDefault();

	void run();
};