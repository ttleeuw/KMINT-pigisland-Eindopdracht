# Author: Jeroen de Haas <jah.dehaas@avans.nl>
cmake_minimum_required(VERSION 3.1.3)
project(pigisland)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wpedantic)#  -Werror)
    add_compile_options("$<$<CONFIG:DEBUG>:-g>")
endif()

  
add_executable(pigisland
  src/kmint/pigisland/main.cpp
    "src/kmint/pigisland/algorithms/node_algorithm.cpp"
    "src/kmint/pigisland/resources/resources.cpp"
    "src/kmint/pigisland/entities/shark.cpp"
    "src/kmint/pigisland/entities/boat.cpp"
    "src/kmint/pigisland/entities/pig.cpp" 

    "src/kmint/pigisland/datastructures/PriorityQueue.hpp"  
    "src/kmint/pigisland/algorithms/pathfinder/AStarSearchStrategy.cpp" 
    "src/kmint/pigisland/algorithms/pathfinder/AStarSearchStrategy.hpp" 
    "src/kmint/pigisland/algorithms/pathfinder/ISearchStrategy.hpp" 
    "src/kmint/pigisland/algorithms/pathfinder/PathFinder.hpp" 
  
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkWander.hpp"
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkChase.hpp" 
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkChase.cpp" 
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkWander.cpp" 
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkTired.hpp" 
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkTired.cpp" 
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkFlee.hpp" 
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkFlee.cpp" 
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkGlobalState.hpp" 
    "src/kmint/pigisland/algorithms/finitestate/shark/SharkGlobalState.cpp" 

    "src/kmint/pigisland/algorithms/finitestate/boat/BoatWander.hpp" 
    "src/kmint/pigisland/algorithms/finitestate/boat/BoatRepair.hpp" 
    "src/kmint/pigisland/algorithms/finitestate/boat/BoatGlobalState.hpp" 
    "src/kmint/pigisland/algorithms/finitestate/boat/BoatWander.cpp" 
    "src/kmint/pigisland/algorithms/finitestate/boat/BoatRepair.cpp" 
    "src/kmint/pigisland/algorithms/finitestate/boat/BoatGlobalState.cpp" 

    "src/kmint/pigisland/algorithms/finitestate/IState.hpp" 
     
    "src/kmint/pigisland/algorithms/finitestate/StateMachine.hpp"  

    "src/kmint/pigisland/algorithms/finitestate/scorecard/BoatDockingScoreCard.hpp"
     "src/kmint/pigisland/entities/base/MapActor.hpp" "src/kmint/pigisland/entities/base/MapActor.cpp" "src/kmint/pigisland/entities/DockingStation.hpp"    "src/kmint/pigisland/algorithms/forcedrivenentities/SteeringBehaviours.hpp" "src/kmint/pigisland/algorithms/forcedrivenentities/SteeringBehaviours.cpp" "src/kmint/pigisland/entities/base/MovingEntity.hpp" "src/kmint/pigisland/entities/base/MovingEntity.cpp" "src/kmint/pigisland/util/math.hpp" "src/kmint/pigisland/util/Wall2D.hpp" "src/kmint/pigisland/util/WallFactory.hpp"  "src/kmint/pigisland/entities/properties/PigPropertiesDefault.hpp" "src/kmint/pigisland/entities/properties/IProperties.hpp" "src/kmint/pigisland/entities/properties/PigPropertiesGenetic.hpp" "src/kmint/pigisland/algorithms/geneticalgorithm/GeneticAlgorithm.hpp" "src/kmint/pigisland/algorithms/geneticalgorithm/GeneticAlgorithm.cpp" "src/kmint/pigisland/algorithms/geneticalgorithm/Chromosome.hpp" "src/kmint/pigisland/algorithms/geneticalgorithm/GeneticScoreCard.hpp" "src/kmint/pigisland/Program.hpp" "src/kmint/pigisland/Program.cpp" "src/kmint/pigisland/util/DrawableWall.hpp")

target_compile_features(pigisland PUBLIC cxx_std_17)
target_link_libraries(pigisland PRIVATE kmint)
target_include_directories(pigisland PRIVATE 
  src
  include)

add_custom_target(pigisland-resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")
