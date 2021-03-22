#include <iostream>

#include <Heuro.hpp>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    Heuro::Scp solver(3, 5, { 1, 6, 8, 4, 3 }, { { 1, 2, 4 }, { 0, 2 }, { 1, 3, 4 } });
    std::cout << solver.grasp(5, 5) << std::endl;
    std::cout << solver.constructive() << std::endl;

    return 0;
}
