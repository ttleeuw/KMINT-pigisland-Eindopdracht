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
                kmint::math::vector2d A{ 0, 548 };
                kmint::math::vector2d B{ 0, 220 };
                walls.emplace_back(A, B);

                A = { 1024, 220 };
                B = { 1024, 548 };
                walls.emplace_back(A, B);

                A = { 768, 768 };
                B = { 256, 768 };
                walls.emplace_back(A, B);

                A = { 256, 0 };
                B = { 768, 0 };
                walls.emplace_back(A, B);

                //Island North-West
                A = { 255, 549 };
                B = { 0, 514 };
                walls.emplace_back(A, B);

                A = { 255, 768 };
                B = { 255, 549 };
                walls.emplace_back(A, B);

                //Island North-East
                A = { 1024, 549 };
                B = { 769, 549 };
                walls.emplace_back(A, B);

                A = { 769, 549 };
                B = { 769, 768 };
                walls.emplace_back(A, B);

                //Island South-East
                A = kmint::math::vector2d(769, 219);
                B = kmint::math::vector2d(1024, 219);
                walls.emplace_back(A, B);

                A = { 769, 0 };
                B = { 769, 219 };
                walls.emplace_back(A, B);

                //Island South-west
                A = { 0, 219 };
                B = { 305, 219 };
                walls.emplace_back(A, B);

                A = { 305, 219 };
                B = { 305, 0 };
                walls.emplace_back(A, B);

                return walls;
            }
        };
    }
}
