#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/random.hpp"
#include "kmint/math/matrix.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>

namespace kmint {
    namespace pigisland {
        namespace util {
            namespace math {
                static class Util {
                public:
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

                    static kmint::math::vector2d perpendicular(kmint::math::vector2d target) {

                        return kmint::math::vector2d{ -target.y(), target.x() };
                    }

                    static kmint::math::matrix<float> multiply(kmint::math::matrix<float> m1, kmint::math::matrix<float> m2) {
                        if (m1.n_cols() != m2.n_rows()) throw std::exception("Invalid multiply matrices, columnA != rowB");

                        kmint::math::matrix<float> retMatrix{ m1.n_rows(), m2.n_cols() };

                        for (std::size_t i = 0; i < m1.n_rows(); ++i)
                            for (std::size_t j = 0; j < m2.n_cols(); ++j)
                                for (std::size_t k = 0; k < m2.n_rows(); ++k)
                                    retMatrix(i, j) += m1(i, k) * m1(k, j);

                        return retMatrix;
                    }

                    static kmint::math::vector2d multiply(kmint::math::matrix<float> m1, const kmint::math::vector2d& vector) {
                        float newX = 0;
                        float newY = 0;

                        for (int i = 0; i < m1.n_rows(); ++i) {
                            for (int j = 0; j < m1.n_cols(); ++j) {
                                if (i == 0) newX += m1(i, j) * vector.x();
                                else if (i == 1) newY += m1(i, j) * vector.y();
                            }
                        }
                        return  kmint::math::vector2d{ newX, newY };
                    }

                    static double vectorDistance(const  kmint::math::vector2d& v1, const  kmint::math::vector2d& v2)
                    {

                        double ySeparation = v2.y() - v1.y();
                        double xSeparation = v2.x() - v1.x();

                        return std::sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
                    }
                };
            }
        }
    } // namespace pigisland
} // namespace kmint
