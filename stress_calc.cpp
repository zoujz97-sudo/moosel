#include<iostream>

int main()
{
    double stress, force, area;
    std::cout << "Enter the force (in Newtons): ";
    std::cin >> force;
    std::cout << "Enter the area (in square meters): "; 
    std::cin >> area;
    stress = force / area;
    std::cout <<std::endl << "The stress is: " << stress << " Pascals" << std::endl;
    return 0;
}