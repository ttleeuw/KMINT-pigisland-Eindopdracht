#include "kmint/main.hpp" // voor de main loop
#include "kmint/math/intersection.hpp"
#include "kmint/math/rectangle.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>
#include "kmint/pigisland/algorithms/finitestate/scorecard/ScoreCard.hpp"

using namespace kmint;

int main() {
    // een app object is nodig om
    ui::app app{};
    //  maak een venster aan
    ui::window window{app.create_window({1024, 768}, "pigisland", 1.0)};
    // maak een podium aan
    play::stage s{{1024, 768}};

    auto map = pigisland::map();
    auto &graph = map.graph();

    kmint::pigisland::finitestate::ScoreCard boatScoreCard{};

    s.build_actor<play::background>(math::size(1024, 768), graphics::image{map.background_image()});
    s.build_actor<play::map_actor>(math::vector2d{0.f, 0.f}, map.graph());
    s.build_actor<pigisland::boat>(graph, pigisland::find_node_of_kind(graph, '1'), boatScoreCard);
    pigisland::shark& shark = s.build_actor<pigisland::shark>(graph, pigisland::find_node_of_kind(graph, 'K'));

    auto locs = pigisland::random_pig_locations(100);
    for (auto loc : locs) { s.build_actor<pigisland::pig>(loc); }

    // Maak een event_source aan (hieruit kun je alle events halen, zoals toetsaanslagen)
    ui::events::event_source event_source{};

    bool first = true;

    // main_loop stuurt alle actors aan.
    main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
        if (first) {
            ctl.time_scale *= 10.0;
            first = false;
        }

        if (shark.isResting()) {
            // TODO start over
            boatScoreCard.print();
        }

        

        for (ui::events::event &e : event_source) {
            e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
            e.handle_key_up([&](auto ke) {
                switch (ke.key) {
                    case ui::events::key::r:
                        ctl.render = !ctl.render;
                        break;
                    case ui::events::key::opening_bracket:
                        ctl.time_scale /= 2.0;
                        break;
                    case ui::events::key::closing_bracket:
                        ctl.time_scale *= 2.0;
                        break;
                    case ui::events::key::d:
                        ctl.debug_overlay = !ctl.debug_overlay;
                    default:
                        break;
                }
            });
        }
    });
}
