#pragma once
#include "kmint/math/vector2d.hpp"
#include "Wall2D.hpp"

namespace kmint {
    namespace pigisland {
        static class WallFactory {
        public:
            static std::vector<Wall2D> create()
            {
                std::vector<Wall2D> walls;

                // Screen borders
                kmint::math::vector2d A{ 1024, 0 };
                kmint::math::vector2d B{ 1024, 768 };
                walls.emplace_back(A, B);

                A = { 1024, 0 };
                B = { 0, 0 };
                walls.emplace_back(A, B);

                A = { 0, 768 };
                B = { 1024, 768 };
                walls.emplace_back(A, B);

                A = { 0, 0 };
                B = { 768, 0 };
                walls.emplace_back(A, B);

                //Island North-West
                A = { 0, 87 };
                B = { 157, 87 };
                walls.emplace_back(A, B);

                A = { 157, 0 };
                B = { 157, 87 };
                walls.emplace_back(A, B);

                //Island North-East
                A = { 910, 0 };
                B = { 910, 50 };
                walls.emplace_back(A, B);

                A = { 910, 50 };
                B = { 1021, 50 };
                walls.emplace_back(A, B);

                //Island South-East
                A = { 820, 590 };
                B = { 1021, 590 };
                walls.emplace_back(A, B);

                A = { 820, 764 };
                B = { 820, 590 };
                walls.emplace_back(A, B);

                //Island South-west
                A = { 60, 550 };
                B = { 215, 550 };
                walls.emplace_back(A, B);

                A = { 60, 550 };
                B = { 60, 700 };
                walls.emplace_back(A, B);

                A = { 60, 700 };
                B = { 215, 700 };
                walls.emplace_back(A, B);

                A = { 215, 550 };
                B = { 215, 700 };
                walls.emplace_back(A, B);

                return walls;
            }
        };
    }
}
