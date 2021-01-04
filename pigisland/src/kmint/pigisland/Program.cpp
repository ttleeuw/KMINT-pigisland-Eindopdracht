#include "Program.hpp"

void Program::initDefault() {

}

void Program::initGenetic() {

}

void Program::run() {
    auto map = kmint::pigisland::map();
    auto& graph = map.graph();

    stage.build_actor<kmint::play::background>(kmint::math::size(1024, 768), kmint::graphics::image{ map.background_image() });
    stage.build_actor<kmint::play::map_actor>(kmint::math::vector2d{ 0.f, 0.f }, map.graph());

    kmint::pigisland::finitestate::BoatDockingScoreCard boatScoreCard;
    kmint::pigisland::shark& shark = stage.build_actor<kmint::pigisland::shark>(graph, kmint::pigisland::find_node_of_kind(graph, 'K'));

    bool useGeneticAlgorithm = true;
    kmint::pigisland::geneticalgorithm::GeneticScoreCard geneticScorecard;
    kmint::pigisland::geneticalgorithm::GeneticAlgorithm geneticAlgorithm{ stage, geneticScorecard };

    kmint::pigisland::boat* b;

    std::vector<kmint::pigisland::pig*> pigs;
    if (!useGeneticAlgorithm) {
        b = &stage.build_actor<kmint::pigisland::boat>(graph, kmint::pigisland::find_node_of_kind(graph, '1'), boatScoreCard);
        auto locs = kmint::pigisland::random_pig_locations(100);
        for (auto loc : locs) { pigs.push_back(&stage.build_actor<kmint::pigisland::pig>(loc, *b, shark)); }
    }
    else {
        b = &stage.build_actor<kmint::pigisland::boat>(graph, kmint::pigisland::find_node_of_kind(graph, '1'), boatScoreCard, geneticScorecard);
        geneticAlgorithm.create_generation_0(shark, *b);
    }
    kmint::pigisland::boat& boat = *b;
    // Maak een event_source aan (hieruit kun je alle events halen, zoals toetsaanslagen)
    kmint::ui::events::event_source event_source{};

    bool first = true;
    kmint::main_loop(stage, window, [&](kmint::delta_time dt, kmint::loop_controls& ctl) {
        if (first) {
            ctl.time_scale *= 40.0;
            first = false;
        }

        if (shark.isResting()) {
            boatScoreCard.print();
            boatScoreCard.newRound();
            shark.reset();
            boat.reset();

            if (!useGeneticAlgorithm) {
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
            else {
                geneticAlgorithm.new_generation(shark, boat);
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