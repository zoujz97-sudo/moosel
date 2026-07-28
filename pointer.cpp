#include <iostream>
int main() 
{
double value = 42.0;
double* ptr = &value;         // 取地址
std::cout << *ptr << std::endl; // 解引用，输出42.0

// 指针与数组
double arr[3] = {1.0, 2.0, 3.0};
double* p = arr;              // 数组名即首地址
std::cout << *(p + 1) << std::endl; // 输出2.0
return 0;
}