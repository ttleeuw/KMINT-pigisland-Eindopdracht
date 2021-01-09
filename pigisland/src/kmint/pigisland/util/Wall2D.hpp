#pragma once
#include "kmint/math/vector2d.hpp"

namespace kmint {
    namespace pigisland {
        class Wall2D
        {
        protected:

            double calcVectorLength(kmint::math::vector2d target) {
                return std::sqrt(std::pow(target.x(), 2) + std::pow(target.y(), 2));
            }

            kmint::math::vector2d normalize(kmint::math::vector2d target)
            {
                double vector_length = calcVectorLength(target);

                if (vector_length > std::numeric_limits<double>::epsilon())
                {
                    target.x(target.x() / vector_length);
                    target.y(target.y() / vector_length);
                }
                return target;
            }

            kmint::math::vector2d _from;
            kmint::math::vector2d _to;
            kmint::math::vector2d _normal;

            void calculateNormal()
            {
                kmint::math::vector2d temp = normalize(_to - _from);
                _normal = { -temp.y(), temp.x() };
            }

        public:

            Wall2D(kmint::math::vector2d from, kmint::math::vector2d to) :_from(from), _to(to)
            {
                calculateNormal();
            }

            kmint::math::vector2d from()const { return _from; }
            kmint::math::vector2d to()const { return _to; }

            kmint::math::vector2d normal()const { return _normal; }
        };
    }
}
