#include "tower_sim.hpp"
#include "geometry.hpp"

void test_generic_points() {
    Point<int, 3> p1;
    Point<int, 3> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3.f; // ou 3.f, ou 3.0 en fonction du type de Point
    std::cout << p3.x() << std::endl;

    Point3D p4 = {1, 2};
    Point2D p5 = {1, 2, 6};
}

int main(int argc, char** argv)
{
    test_generic_points();

    TowerSimulation simulation { argc, argv };
    simulation.launch();

    return 0;
}