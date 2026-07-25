#include <iostream>
int main() 
{
// 固定大小数组（不推荐力学中使用，用vector代替）
double stress[5] = {100, 200, 150, 300, 250};

// 二维数组 — 3×3 应力张量
double sigma[3][3] = {
    {100, 50, 0},
    {50, -30, 0},
    {0,   0,  0}
};
for (int i = 0; i < 3; ++i) 
{
    for (int j = 0; j < 3; ++j) 
    {
        std::cout << "σ[" << i << "][" << j << "] = " << sigma[i][j] << std::endl;
    }
}
for (int i = 0; i < 5; ++i) 
{
    std::cout << "stress[" << i << "] = " << stress[i] << std::endl;
}
return 0;
}