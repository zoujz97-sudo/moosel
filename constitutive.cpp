// constitutive.cpp — 材料本构模型
#include <iostream>
#include <cmath>

// 线弹性：σ = E·ε
double linear_elastic(double strain, double E) 
{
    return E * strain;
}

// 理想弹塑性
double elastic_perfect_plastic(double strain, double E, double yield_stress) 
{
    double stress = E * strain;
    if (std::abs(stress) > yield_stress) 
    {
        stress = (stress > 0 ? 1.0 : -1.0) * yield_stress;
    }
    return stress;
}

// 线性硬化弹塑性
double linear_hardening(double strain, double E, double yield_stress, double H) {
    double elastic_strain = yield_stress / E;
    if (std::abs(strain) <= elastic_strain) 
    {
        return E * strain;
    } 
    else 
    {
        double plastic_strain = std::abs(strain) - elastic_strain;
        double sign = (strain > 0) ? 1.0 : -1.0;
        return sign * (yield_stress + H * plastic_strain);
    }
}

int main()
{
    double E = 210000.0;    // MPa
    double ys = 235.0;      // MPa
    double H = 1000.0;      // MPa，硬化模量

    std::cout << "应变\t线弹性\t理想塑性\t硬化塑性" << std::endl;
    for (int i = 0; i <= 20; i++) 
    {
        double eps = i * 0.002;
        std::cout << eps << "\t"
                  << linear_elastic(eps, E) << "\t"
                  << elastic_perfect_plastic(eps, E, ys) << "\t"
                  << linear_hardening(eps, E, ys, H) << std::endl;
    }
    return 0;
}
