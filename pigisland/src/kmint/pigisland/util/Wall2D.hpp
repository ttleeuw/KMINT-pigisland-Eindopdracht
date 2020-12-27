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

            kmint::math::vector2d m_vA;
            kmint::math::vector2d m_vB;
            kmint::math::vector2d m_vN;

            void calculateNormal()
            {
                kmint::math::vector2d temp = normalize(m_vB - m_vA);

                m_vN = { -temp.y(), temp.x() };
            }

        public:

            Wall2D() {}
            Wall2D(kmint::math::vector2d A, kmint::math::vector2d B) :m_vA(A), m_vB(B)
            {
                calculateNormal();
            }

            Wall2D(kmint::math::vector2d A, kmint::math::vector2d B, kmint::math::vector2d N) :m_vA(A), m_vB(B), m_vN(N)
            {
            }

            kmint::math::vector2d from()const { return m_vA; }
            void setFrom(kmint::math::vector2d v) { m_vA = v; calculateNormal(); }

            kmint::math::vector2d to()const { return m_vB; }
            void setTo(kmint::math::vector2d v) { m_vB = v; calculateNormal(); }

            kmint::math::vector2d normal()const { return m_vN; }
            void setNormal(kmint::math::vector2d n) { m_vN = n; }

            kmint::math::vector2d center() const { return (m_vA + m_vB) / 2.0; }
        };
    }
}
