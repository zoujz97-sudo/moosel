#include<iostream>

double calculate_stress(double force, double area) 
{
    if (area <= 0) 
    {
        throw std::invalid_argument("Area must be greater than zero.");
    }
    return force / area;
}

int main()
{
    double f=5000.0,a=0.01; // Example values for force (N) and area (m²)
    double stress = calculate_stress(f, a);
    std::cout << "Calculated stress: " << stress << " Pa" << std::endl;
    return 0;
}  