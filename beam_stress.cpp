#include <iostream>
#include <cmath>
int main() 
{
    double  load, stress,length = 2.0; // m
    double moment = 50000.0;     // N·m
    double height = 0.3;         // m
    double width = 0.15;         // m
    double inertia = width * std::pow(height, 3) / 12.0; // I = bh³/12

    int n_layers = 11;
    for (int i = 0; i < n_layers; i++)
    {
        double y = -height/2 + i * height / (n_layers - 1);
        double sigma = moment * y / inertia;
        std::cout << "y = " << y << " m, σ = " << sigma << " Pa" << std::endl;
    }

    std::cout << "Enter the load applied to the beam (in Newtons): ";
    std::cin >> load;

    // Calculate the stress (assuming a simple bending scenario)
    stress = (load * length) / (width * height * height / 6);

    std::cout << "The calculated stress is: " << stress << " Pascals" << std::endl;

    return 0;
}