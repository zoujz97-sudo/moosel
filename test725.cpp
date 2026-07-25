#include <iostream>

int main() 
{
    // 变量声明
    int n = 10;              // 整数
    double x = 3.14159;      // 双精度浮点数（力学中最常用）
    float f = 1.0f;          // 单精度（少用，精度不够）
    bool flag = true;        // 布尔值
    char c = 'A';            // 字符
    // 力学常用常量
    const double PI = 3.141592653589793;
    const double YOUNG_MODULUS = 210e9;  // 钢的弹性模量，Pa

    double a = 10.0, b = 3.0;
    double sum = a + b;      // 加法
    double dif = a - b;      // 减法
    double prod = a * b;     // 乘法
    double quot = a / b;     // 除法
    // 整数除法注意：
    int i = 10 / 3;          // = 3（截断，不是3.333）
    double d = 10.0 / 3;     // = 3.33333

    std::cout << "PI: " << PI << std::endl;
    std::cout << "杨氏模量: " << YOUNG_MODULUS << " Pa" << std::endl;
    std::cout << "整数: " << n << std::endl;
    std::cout << "双精度浮点数: " << x << std::endl;
    std::cout << "单精度浮点数: " << f << std::endl;
    std::cout << "布尔值: " << std::boolalpha << flag << std::endl;
    std::cout << "字符: " << c << std::endl;
    std::cout << "加法: a+b=" << sum << std::endl;
    std::cout << "减法: a-b=" << dif << std::endl;
    std::cout << "乘法: a*b=" << prod << std::endl;
    std::cout << "除法: a/b=" << quot << std::endl;
    std::cout << "整数除法: 10/3=" << i << std::endl;
    std::cout << "双精度除法: 10.0/3=" << d << std::endl;
    return 0;
}