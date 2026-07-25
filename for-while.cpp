#include <iostream>

int main() 
{
    int node_count = 50;
    for (int i = 0; i < node_count; i++) 
    {
        std::cout << "节点 " << i << " 已处理" << std::endl;
    }
    // while循环 — 迭代求解
    double tolerance = 1e-10;
    double residual = 1.0;
    int iter = 0;
    while (residual > tolerance && iter < 10000)  // 迭代计算...
    {
        residual *= 0.99;
        iter++;
    }
    std::cout << "收敛于第 " << iter << " 次迭代" << std::endl;
}