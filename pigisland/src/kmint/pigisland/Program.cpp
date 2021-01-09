#include "Program.hpp"
#include <kmint/pigisland/util/DrawableWall.hpp>

int scale = 2;

void drawWalls(kmint::pigisland::pig& pig, kmint::play::stage& stage) {
    std::vector<std::reference_wrapper<kmint::pigisland::DrawableWall>> drawables;
    auto walls = pig.getWalls();

    for (auto w : walls) {
        if (w.from().x() == w.to().x()) {
            // Draw over y-axis
            auto dist = w.from().y() - w.to().y();

            if (w.from().y() < w.to().y()) {
                for (size_t i = 0; i < dist; i++)
                {
                    kmint::math::vector2d loc = { w.from().x(), w.from().y() + i };
                    drawables.push_back(stage.build_actor<kmint::pigisland::DrawableWall>(loc));
                }
            }
            else {
                for (size_t i = 0; i < dist; i++)
                {
                    kmint::math::vector2d loc = { w.from().x(), w.from().y() + i };
                    drawables.push_back(stage.build_actor<kmint::pigisland::DrawableWall>(loc));
                }
            }
        }
        else {
            // Draw over x-axis
            auto dist = w.from().x() - w.to().x();
            if (w.from().x() < w.to().x()) {
                for (size_t i = 0; i < dist; i++)
                {
                    kmint::math::vector2d loc = { w.from().x() - i , w.from().y() };
                    drawables.push_back(stage.build_actor<kmint::pigisland::DrawableWall>(loc));
                }
            }
            else {
                for (size_t i = 0; i < dist; i++)
                {
                    kmint::math::vector2d loc = { w.from().x() + i , w.from().y() };
                    drawables.push_back(stage.build_actor<kmint::pigisland::DrawableWall>(loc));
                }
            }
        }
    }
}

void Program::runDefault() {
    auto map = kmint::pigisland::map();
    auto& graph = map.graph();

    stage.build_actor<kmint::play::background>(kmint::math::size(1024, 768), kmint::graphics::image{ map.background_image() });
    stage.build_actor<kmint::play::map_actor>(kmint::math::vector2d{ 0.f, 0.f }, map.graph());

    kmint::pigisland::finitestate::BoatDockingScoreCard boatScoreCard;
    kmint::pigisland::shark& shark = stage.build_actor<kmint::pigisland::shark>(graph, kmint::pigisland::find_node_of_kind(graph, 'K'));

    bool useGeneticAlgorithm = true;
    kmint::pigisland::geneticalgorithm::GeneticScoreCard geneticScorecard;
    kmint::pigisland::geneticalgorithm::GeneticAlgorithm geneticAlgorithm{ stage, geneticScorecard };

    kmint::pigisland::boat& boat = stage.build_actor<kmint::pigisland::boat>(graph, kmint::pigisland::find_node_of_kind(graph, '1'), boatScoreCard);

    std::vector<kmint::pigisland::pig*> pigs;
    auto locs = kmint::pigisland::random_pig_locations(100);
    for (auto loc : locs) { pigs.push_back(&stage.build_actor<kmint::pigisland::pig>(loc, boat, shark)); }

    // Maak een event_source aan (hieruit kun je alle events halen, zoals toetsaanslagen)
    kmint::ui::events::event_source event_source{};

    bool first = true;
    kmint::main_loop(stage, window, [&](kmint::delta_time dt, kmint::loop_controls& ctl) {
        if (first) {
            ctl.time_scale *= scale;
            first = false;
        }

        if (shark.isResting()) {
            boatScoreCard.print();
            boatScoreCard.newRound();
            shark.reset();
            boat.reset();

            for (auto actor : pigs)
            {
                stage.remove_actor(*actor);
            }
            pigs.clear();

            auto locs = kmint::pigisland::random_pig_locations(100);
            for (auto loc : locs) {
                pigs.push_back(&stage.build_actor<kmint::pigisland::pig>(loc, boat, shark));
            }
        }

        for (kmint::ui::events::event& e : event_source) {
            e.handle_quit([&ctl](kmint::ui::events::quit_event qe) { ctl.quit = true; });
            e.handle_key_up([&](auto ke) {
                switch (ke.key) {
                case kmint::ui::events::key::r:
                    ctl.render = !ctl.render;
                    break;
                case kmint::ui::events::key::opening_bracket:
                    ctl.time_scale /= 2.0;
                    break;
                case kmint::ui::events::key::closing_bracket:
                    ctl.time_scale *= 2.0;
                    break;
                case kmint::ui::events::key::d:
                    ctl.debug_overlay = !ctl.debug_overlay;
                default:
                    break;
                }
                });
        }
        });
}

void Program::runGenetic() {
    auto map = kmint::pigisland::map();
    auto& graph = map.graph();

    stage.build_actor<kmint::play::background>(kmint::math::size(1024, 768), kmint::graphics::image{ map.background_image() });
    stage.build_actor<kmint::play::map_actor>(kmint::math::vector2d{ 0.f, 0.f }, map.graph());


    kmint::pigisland::geneticalgorithm::GeneticScoreCard geneticScorecard;
    kmint::pigisland::geneticalgorithm::GeneticAlgorithm geneticAlgorithm{ stage, geneticScorecard };

    kmint::pigisland::finitestate::BoatDockingScoreCard boatScoreCard;
    kmint::pigisland::boat& boat = stage.build_actor<kmint::pigisland::boat>(graph, kmint::pigisland::find_node_of_kind(graph, '1'), boatScoreCard, geneticScorecard);
    kmint::pigisland::shark& shark = stage.build_actor<kmint::pigisland::shark>(graph, kmint::pigisland::find_node_of_kind(graph, 'K'), geneticScorecard);

    std::vector<kmint::pigisland::pig*> pigs;

    geneticAlgorithm.create_generation_0(shark, boat);
    // Maak een event_source aan (hieruit kun je alle events halen, zoals toetsaanslagen)
    kmint::ui::events::event_source event_source{};

    //drawWalls(geneticAlgorithm.getPigs()[0], stage);
    bool first = false;
    kmint::main_loop(stage, window, [&](kmint::delta_time dt, kmint::loop_controls& ctl) {
        if (first) {
            ctl.time_scale *= scale;
            first = false;
        }

        if (shark.isResting()) {
            boatScoreCard.print();
            boatScoreCard.newRound();
            shark.reset();
            boat.reset();

            geneticAlgorithm.new_generation(shark, boat);
        }

        for (kmint::ui::events::event& e : event_source) {
            e.handle_quit([&ctl](kmint::ui::events::quit_event qe) { ctl.quit = true; });
            e.handle_key_up([&](auto ke) {
                switch (ke.key) {
                case kmint::ui::events::key::r:
                    ctl.render = !ctl.render;
                    break;
                case kmint::ui::events::key::opening_bracket:
                    ctl.time_scale /= 2.0;
                    break;
                case kmint::ui::events::key::closing_bracket:
                    ctl.time_scale *= 2.0;
                    break;
                case kmint::ui::events::key::d:
                    ctl.debug_overlay = !ctl.debug_overlay;
                default:
                    break;
                }
                });
        }
        });
}

void Program::run() {
    bool useGenetic = true;
    if (useGenetic) {
        this->runGenetic();
    }
    else {
        this->runDefault();
    }
}