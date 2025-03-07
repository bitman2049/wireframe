#include <eigen3/Eigen/Dense>
#include <vector>
#include "poly.h"

// Ship models extracted from Elite (1984)
namespace Ship
{
    const Poly Sidewinder(
            PointList({
                Eigen::Vector4d({-32, 0, 36, 1}),
                Eigen::Vector4d({32, 0, 36, 1}),
                Eigen::Vector4d({64, 0, -28, 1}),
                Eigen::Vector4d({-64, 0, -28, 1}),
                Eigen::Vector4d({0, 16, -28, 1}),
                Eigen::Vector4d({0, -16, -28, 1}),
                Eigen::Vector4d({-12, 6, -28, 1}),
                Eigen::Vector4d({12, 6, -28, 1}),
                Eigen::Vector4d({12, -6, -28, 1}),
                Eigen::Vector4d({-12, -6, -28, 1})
                }),
            std::vector<std::vector<int>>({
                std::vector<int>({0, 4, 1}),
                std::vector<int>({0, 3, 4}),
                std::vector<int>({1, 4, 2}),
                std::vector<int>({5, 2, 4, 3}),
                std::vector<int>({6, 9, 8, 7}),
                std::vector<int>({0, 5, 3}),
                std::vector<int>({0, 1, 5}),
                std::vector<int>({1, 2, 5})
                })
    );
    const Poly Viper(
            PointList({
                Eigen::Vector4d({0, 0, 72, 1}),
                Eigen::Vector4d({0, 16, 24, 1}),
                Eigen::Vector4d({0, -16, 24, 1}),
                Eigen::Vector4d({48, 0, -24, 1}),
                Eigen::Vector4d({-48, 0, -24, 1}),
                Eigen::Vector4d({24, -16, -24, 1}),
                Eigen::Vector4d({-24, -16, -24, 1}),
                Eigen::Vector4d({24, 16, -24, 1}),
                Eigen::Vector4d({-24, 16, -24, 1}),
                Eigen::Vector4d({-32, 0, -24, 1}),
                Eigen::Vector4d({32, 0, -24, 1}),
                Eigen::Vector4d({8, 8, -24, 1}),
                Eigen::Vector4d({-8, 8, -24, 1}),
                Eigen::Vector4d({-8, -8, -24, 1}),
                Eigen::Vector4d({8, -8, -24, 1}),
                }),
            std::vector<std::vector<int>>({
                std::vector<int>({1, 8, 7}),
                std::vector<int>({4, 8, 1, 0}),
                std::vector<int>({0, 1, 7, 3}),
                std::vector<int>({0, 2, 6, 4}),
                std::vector<int>({3, 5, 2, 0}),
                std::vector<int>({2, 5, 6}),
                std::vector<int>({7, 8, 4, 6, 5, 3}),
                std::vector<int>({13, 12, 9}),
                std::vector<int>({10, 11, 14}),
                })
    );
    const Poly Mamba(
            PointList({
                Eigen::Vector4d({0, 0, 64, 1}),
                Eigen::Vector4d({-64, -8, -32, 1}),
                Eigen::Vector4d({-32, 8, -32, 1}),
                Eigen::Vector4d({32, 8, -32, 1}),
                Eigen::Vector4d({64, -8, -32, 1}),
                Eigen::Vector4d({-4, 4, 16, 1}),
                Eigen::Vector4d({4, 4, 16, 1}),
                Eigen::Vector4d({8, 3, 28, 1}),
                Eigen::Vector4d({-8, 3, 28, 1}),
                Eigen::Vector4d({-20, -4, 16, 1}),
                Eigen::Vector4d({20, -4, 16, 1}),
                Eigen::Vector4d({-24, -7, -20, 1}),
                Eigen::Vector4d({-16, -7, -20, 1}),
                Eigen::Vector4d({16, -7, -20, 1}),
                Eigen::Vector4d({24, -7, -20, 1}),
                Eigen::Vector4d({-8, 4, -32, 1}),
                Eigen::Vector4d({8, 4, -32, 1}),
                Eigen::Vector4d({8, -4, -32, 1}),
                Eigen::Vector4d({-8, -4, -32, 1}),
                Eigen::Vector4d({-32, 4, -32, 1}),
                Eigen::Vector4d({32, 4, -32, 1}),
                Eigen::Vector4d({36, -4, -32, 1}),
                Eigen::Vector4d({-36, -4, -32, 1}),
                Eigen::Vector4d({-38, 0, -32, 1}),
                Eigen::Vector4d({38, 0, -32, 1}),
            }),
        std::vector<std::vector<int>>({
                std::vector<int>({4, 1, 0}),
                std::vector<int>({12, 11, 9}),
                std::vector<int>({14, 13, 10}),
                std::vector<int>({2, 3, 0}),
                std::vector<int>({5, 6, 7, 8}),
                std::vector<int>({0, 1, 2}),
                std::vector<int>({0, 3, 4}),
                std::vector<int>({1, 4, 3, 2}),
                std::vector<int>({18, 17, 16, 15}),
                std::vector<int>({23, 22, 19}),
                std::vector<int>({20, 21, 24}),
                })
    );
    const Poly CobraMk3(
            PointList({
                Eigen::Vector4d({32, 0, 76, 1}),
                Eigen::Vector4d({-32, 0, 76, 1}),
                Eigen::Vector4d({0, 26, 24, 1}),
                Eigen::Vector4d({-120, -3, -8, 1}),
                Eigen::Vector4d({120, -3, -8, 1}),
                Eigen::Vector4d({-88, 16, -40, 1}),
                Eigen::Vector4d({88, 16, -40, 1}),
                Eigen::Vector4d({128, -8, -40, 1}),
                Eigen::Vector4d({-128, -8, -40, 1}),
                Eigen::Vector4d({0, 26, -40, 1}),
                Eigen::Vector4d({-32, -24, -40, 1}),
                Eigen::Vector4d({32, -24, -40, 1}),
                Eigen::Vector4d({-36, 8, -40, 1}),
                Eigen::Vector4d({-8, 12, -40, 1}),
                Eigen::Vector4d({8, 12, -40, 1}),
                Eigen::Vector4d({36, 8, -40, 1}),
                Eigen::Vector4d({36, -12, -40, 1}),
                Eigen::Vector4d({8, -16, -40, 1}),
                Eigen::Vector4d({-8, -16, -40, 1}),
                Eigen::Vector4d({-36, -12, -40, 1}),
                Eigen::Vector4d({0, 0, 76, 1}),
                Eigen::Vector4d({0, 0, 90, 1}),
                Eigen::Vector4d({-80, -6, -40, 1}),
                Eigen::Vector4d({-80, 6, -40, 1}),
                Eigen::Vector4d({-88, 0, -40, 1}),
                Eigen::Vector4d({80, 6, -40, 1}),
                Eigen::Vector4d({88, 0, -40, 1}),
                Eigen::Vector4d({80, -6, -40, 1}),
            }),
        std::vector<std::vector<int>>({
                std::vector<int>({0, 1, 2}),
                std::vector<int>({1, 5, 2}),
                std::vector<int>({2, 6, 0}),
                std::vector<int>({1, 3, 5}),
                std::vector<int>({6, 4, 0}),
                std::vector<int>({5, 9, 2}),
                std::vector<int>({2, 9, 6}),
                std::vector<int>({3, 8, 5}),
                std::vector<int>({6, 7, 4}),
                std::vector<int>({9, 5, 8, 10, 11, 7, 6}),
                std::vector<int>({19, 18, 13, 12}),
                std::vector<int>({17, 16, 15, 14}),
                std::vector<int>({23, 24, 22}),
                std::vector<int>({27, 26, 25}),
                std::vector<int>({10, 8, 3, 1}),
                std::vector<int>({11, 10, 1, 0}),
                std::vector<int>({0, 4, 7, 11}),
                })
    );
    const Poly Thargoid(
            PointList({
                Eigen::Vector4d({32, -48, 48, 1}),
                Eigen::Vector4d({32, -68, 0, 1}),
                Eigen::Vector4d({32, -48, -48, 1}),
                Eigen::Vector4d({32, 0, -68, 1}),
                Eigen::Vector4d({32, 48, -48, 1}),
                Eigen::Vector4d({32, 68, 0, 1}),
                Eigen::Vector4d({32, 48, 48, 1}),
                Eigen::Vector4d({32, 0, 68, 1}),
                Eigen::Vector4d({-24, -116, 116, 1}),
                Eigen::Vector4d({-24, -164, 0, 1}),
                Eigen::Vector4d({-24, -116, -116, 1}),
                Eigen::Vector4d({-24, 0, -164, 1}),
                Eigen::Vector4d({-24, 116, -116, 1}),
                Eigen::Vector4d({-24, 164, 0, 1}),
                Eigen::Vector4d({-24, 116, 116, 1}),
                Eigen::Vector4d({-24, 0, 164, 1}),
                Eigen::Vector4d({-24, 64, 80, 1}),
                Eigen::Vector4d({-24, 64, -80, 1}),
                Eigen::Vector4d({-24, -64, -80, 1}),
                Eigen::Vector4d({-24, -64, 80, 1}),
            }),
        std::vector<std::vector<int>>({
                std::vector<int>({0, 1, 9, 8}),
                std::vector<int>({1, 2, 10, 9}),
                std::vector<int>({2, 3, 11, 10}),
                std::vector<int>({3, 4, 12, 11}),
                std::vector<int>({0, 7, 6, 5, 4, 3, 2, 1}),
                std::vector<int>({4, 5, 13, 12}),
                std::vector<int>({5, 6, 14, 13}),
                std::vector<int>({6, 7, 15, 14}),
                std::vector<int>({8, 15, 7, 0}),
                std::vector<int>({9, 10, 11, 12, 13, 14, 15, 8}),
                })
    );
    const Poly Coriolis(
            PointList({
                Eigen::Vector4d({160, 0, 160, 1}),
                Eigen::Vector4d({0, 160, 160, 1}),
                Eigen::Vector4d({-160, 0, 160, 1}),
                Eigen::Vector4d({0, -160, 160, 1}),
                Eigen::Vector4d({160, -160, 0, 1}),
                Eigen::Vector4d({160, 160, 0, 1}),
                Eigen::Vector4d({-160, 160, 0, 1}),
                Eigen::Vector4d({-160, -160, 0, 1}),
                Eigen::Vector4d({160, 0, -160, 1}),
                Eigen::Vector4d({0, 160, -160, 1}),
                Eigen::Vector4d({-160, 0, -160, 1}),
                Eigen::Vector4d({0, -160, -160, 1}),
                Eigen::Vector4d({10, -30, 160, 1}),
                Eigen::Vector4d({10, 30, 160, 1}),
                Eigen::Vector4d({-10, 30, 160, 1}),
                Eigen::Vector4d({-10, -30, 160, 1}),
                }),
            std::vector<std::vector<int>>({
                std::vector<int>({3, 2, 1, 0}),
                std::vector<int>({15, 14, 13, 12}),
                std::vector<int>({4, 3, 0}),
                std::vector<int>({0, 1, 5}),
                std::vector<int>({1, 2, 6}),
                std::vector<int>({2, 3, 7}),
                std::vector<int>({3, 4, 11, 7}),
                std::vector<int>({5, 8, 4, 0}),
                std::vector<int>({7, 10, 6, 2}),
                std::vector<int>({5, 1, 6, 9}),
                std::vector<int>({7, 11, 10}),
                std::vector<int>({8, 11, 4}),
                std::vector<int>({5, 9, 8}),
                std::vector<int>({6, 10, 9}),
                std::vector<int>({9, 10, 11, 8}),
                })
    );
    const Poly Python(
            PointList({
                Eigen::Vector4d({0, 0, 224, 1}),
                Eigen::Vector4d({0, 48, 48, 1}),
                Eigen::Vector4d({96, 0, -16, 1}),
                Eigen::Vector4d({-96, 0, -16, 1}),
                Eigen::Vector4d({0, 48, -32, 1}),
                Eigen::Vector4d({0, 24, -112, 1}),
                Eigen::Vector4d({-48, 0, -112, 1}),
                Eigen::Vector4d({48, 0, -112, 1}),
                Eigen::Vector4d({0, -48, 48, 1}),
                Eigen::Vector4d({0, -48, -32, 1}),
                Eigen::Vector4d({0, -24, -112, 1}),
                }),
            std::vector<std::vector<int>>({
                std::vector<int>({0, 3, 1}),
                std::vector<int>({1, 2, 0}),
                std::vector<int>({0, 8, 3}),
                std::vector<int>({2, 8, 0}),
                std::vector<int>({1, 3, 4}),
                std::vector<int>({1, 4, 2}),
                std::vector<int>({3, 8, 9}),
                std::vector<int>({9, 8, 2}),
                std::vector<int>({5, 4, 3}),
                std::vector<int>({6, 5, 3}),
                std::vector<int>({2, 4, 5}),
                std::vector<int>({2, 5, 7}),
                std::vector<int>({10, 9, 2}),
                std::vector<int>({2, 7, 10}),
                std::vector<int>({3, 9, 10}),
                std::vector<int>({10, 6, 3}),
                std::vector<int>({5, 6, 10, 7}),
                })
    );
}
