#include <iostream>
#include <cmath>
double dot_product(double a[], double b[], int size) 
{
    double result = 0.0;
    for (int i = 0; i < size; ++i) 
    {
        result += a[i] * b[i];
    }
    return result;
}

double norm(double v[], int size) 
{
    return std::sqrt(dot_product(v, v, size));
}

int main()  
{
    const int size = 3;
    double vector1[size] = {1.0, 2.0, 3.0};
    double vector2[size] = {4.0, 5.0, 6.0};

    double dp = dot_product(vector1, vector2, size);
    double norm1 = norm(vector1, size);
    double norm2 = norm(vector2, size);

    std::cout << "Dot Product: " << dp << std::endl;
    std::cout << "Norm of Vector 1: " << norm1 << std::endl;
    std::cout << "Norm of Vector 2: " << norm2 << std::endl;

    return 0;
}