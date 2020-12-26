#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/random.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>

namespace kmint {
    namespace pigisland {
        namespace util {
            namespace math {
                static class Util {
                    static kmint::math::vector2d truncate(kmint::math::vector2d vector, float max)
                    {
                        auto length = pigisland::util::math::Util::calcVectorLength(vector);
                        if (length > max)
                        {
                            auto result = pigisland::util::math::Util::normalize(vector);

                            return result *= max;
                        }
                        return vector;
                    }

                    static double calcVectorLength(kmint::math::vector2d target) {
                        return std::sqrt(std::pow(target.x(), 2) + std::pow(target.y(), 2));
                    }

                    static kmint::math::vector2d normalize(kmint::math::vector2d target)
                    {
                        double vector_length = pigisland::util::math::Util::calcVectorLength(target);

                        if (vector_length > std::numeric_limits<double>::epsilon())
                        {
                            target.x(target.x() / vector_length);
                            target.y(target.y() / vector_length);
                        }
                        return target;
                    }
                };
            }
        }
    } // namespace pigisland
} // namespace kmint
