# C++ 全部符号参考手册

> 按使用频率从高到低排列，冷门符号用 🔍 标注
> 版本标注：C++11/14/17/20

---

## 一、算术运算符 — 最常用

| 符号 | 名称 | 例子 | 说明 |
|------|------|------|------|
| `+` | 加 | `a + b` | 也可用于字符串拼接 |
| `-` | 减 / 负号 | `a - b` / `-x` | 单目负号取相反数 |
| `*` | 乘 | `a * b` | 重点：也用于指针声明和解引用 |
| `/` | 除 | `a / b` | **整数除法截断**：`5/2=2`；`5.0/2=2.5` |
| `%` | 取余（模） | `a % b` | 仅整数可用：`7%3=1`，`-7%3=-1` |
| `++` | 自增 | `i++` / `++i` | 后缀：先用后加；前缀：先加后用 |
| `--` | 自减 | `i--` / `--i` | 同上 |

## 二、赋值运算符

| 符号 | 含义 | 等价于 |
|------|------|--------|
| `=` | 赋值 | `a = b` |
| `+=` | 加后赋值 | `a += b` → `a = a + b` |
| `-=` | 减后赋值 | `a -= b` |
| `*=` | 乘后赋值 | `a *= b` |
| `/=` | 除后赋值 | `a /= b` |
| `%=` | 取余后赋值 | `a %= b` |
| `&=` | 按位与后赋值 | `a &= b` |
| `|=` | 按位或后赋值 | `a |= b` |
| `^=` | 按位异或后赋值 | `a ^= b` |
| `<<=` | 左移后赋值 | `a <<= b` |
| `>>=` | 右移后赋值 | `a >>= b` |

## 三、比较运算符

| 符号 | 含义 | 例子 |
|------|------|------|
| `==` | 等于 | `a == b` |
| `!=` | 不等于 | `a != b` |
| `<` | 小于 | `a < b` |
| `>` | 大于 | `a > b` |
| `<=` | 小于等于 | `a <= b` |
| `>=` | 大于等于 | `a >= b` |
| `<=>` 🔍C++20 | **三路比较（宇宙飞船运算符）** | `(a <=> b) < 0` 表示 a<b，`==0` 表示相等，`>0` 表示 a>b |

## 四、逻辑运算符

| 符号 | 含义 | 例子 |
|------|------|------|
| `&&` | **逻辑与**（且） | `a > 0 && b > 0` — 全真才真 |
| `||` | **逻辑或**（或） | `a > 0 || b > 0` — 一真即真 |
| `!` | **逻辑非**（取反） | `!flag` — true 变 false，false 变 true |
| `&&` 短路 | 左边 false 则不计算右边 | `ptr && ptr->value` 安全写法 |
| `||` 短路 | 左边 true 则不计算右边 | `a > 0 || do_something()` |

## 五、位运算符 — 底层操作

| 符号 | 含义 | 例子 |
|------|------|------|
| `&` | 按位与 | `0b1010 & 0b1100 = 0b1000` |
| `\|` | 按位或 | `0b1010 \| 0b1100 = 0b1110` |
| `^` | 按位异或（XOR） | `0b1010 ^ 0b1100 = 0b0110` |
| `~` | 按位取反 | `~0b1010`（注意类型长度） |
| `<<` | **左移**（× $2^n$） | `3 << 2 = 12`（3×4） |
| `>>` | **右移**（÷ $2^n$） | `8 >> 2 = 2`（8÷4） |

> ⚠️ `<<` `>>` 有两个意思：和 `std::cin`/`std::cout` 一起用是输入输出运算符，和整数一起用是位移

## 六、成员访问与指针运算符

| 符号 | 名称 | 例子 | 说明 |
|------|------|------|------|
| `.` | **点运算符** | `obj.member` | 通过**对象**访问成员 |
| `->` | **箭头运算符** | `ptr->member` | 通过**指针**访问成员，等价于 `(*ptr).member` |
| `::` | **域解析符** | `std::cout`、`MyClass::func` | 访问命名空间/类/全局作用域中的东西 |
| `.*` 🔍 | 成员指针解引用（对象） | `obj.*ptr_to_member` | 通过对象调用成员指针指向的成员 |
| `->*` 🔍 | 成员指针解引用（指针） | `ptr->*ptr_to_member` | 通过指针调用成员指针指向的成员 |
| `&` | **取地址** | `int* p = &a;` | 获得变量内存地址 |
| `*` | **解引用** | `int b = *p;` | 通过地址访问它所指向的值 |

## 七、作用域相关

| 符号 | 含义 | 例子 |
|------|------|------|
| `{}` | 块作用域 / 初始化列表 | `if (...) { ... }`、`vector<int> v{1,2,3}` |
| `()` | 函数调用 / 分组 / 构造 | `func(a,b)`、`(a+b)*c`、`MyClass obj(x)` |
| `[]` | 数组下标 / lambda 捕获 | `arr[0]`、`[=](){}` |
| `;` | **语句结束** | 每行 C++ 语句末尾必须加分号 |
| `:` | **初始化列表 / 继承 / 标签** | `: base_class()`、`case 1:`、`for(int i:vec)` |
| `::` | 全局作用域 | `::global_func()` — 前面不加空间名代表全局 |
| `::`🔍 | 类静态成员访问 | `MyClass::static_member` |

## 八、内存管理

| 符号/关键字 | 含义 | 例子 |
|------------|------|------|
| `new` | 动态分配（堆内存） | `int* p = new int(5);` |
| `new[]` | 动态分配数组 | `int* arr = new int[10];` |
| `delete` | 释放单个对象 | `delete p;` |
| `delete[]` | 释放数组 | `delete[] arr;` |
| `nullptr` C++11 | 空指针（替代 `NULL`） | `int* p = nullptr;` |

## 九、类型转换

| 符号 | 名称 | 说明 |
|------|------|------|
| `(type)expr` | C 风格强制转换 | `(double)a / b` — 不推荐 |
| `type(expr)` | 函数风格转换 | `double(a) / b` — 不推荐 |
| `static_cast<type>(expr)` C++ | **静态转换**（最常用） | 编译时检查的类型转换 |
| `dynamic_cast<type>(expr)` C++ | **动态转换**（运行时检查） | 多态类型的向下转型，失败返回 nullptr |
| `const_cast<type>(expr)` 🔍 | 去除 const/volatile | 去掉 const 限定（慎用） |
| `reinterpret_cast<type>(expr)` 🔍 | **重新解释** | 把某类型的位模式当另一种类型用（极危险） |

```cpp
double x = static_cast<double>(a) / b;   // 安全的整数转浮点
```

## 十、流程控制

| 符号/关键字 | 含义 | 例子 |
|------------|------|------|
| `?:` **三目运算符** | 条件 ? 真值 : 假值 | `max = (a > b) ? a : b;` |
| `,` **逗号运算符** | 依次执行，取最后一个值 | `int x = (a++, b += 2, a + b);` |
| `throw` | 抛出异常 | `throw std::runtime_error("err");` |
| `...` **可变参数** | 任意数量参数 | `void func(...);`（C风格） |
| `...` **折叠表达式** C++17 | 参数包展开 | `(std::cout << ... << args);` |
| `...` 🔍 | 模板参数包 | `template<typename... Args>` |

## 十一、预处理符号

| 符号 | 含义 | 例子 |
|------|------|------|
| `#` | **预处理指令** | `#include`、`#define`、`#ifdef` |
| `##` 🔍 | **预处理粘合** | `#define CONCAT(a,b) a ## b` → `CONCAT(foo,bar)` = `foobar` |
| `#@` 🔍 | **字符化**（非标准） | MSVC 扩展，极少见 |
| `#x` 🔍 | **字符串化** | `#define STR(x) #x` → `STR(hello)` = `"hello"` |
| `#pragma` | 编译器指令 | `#pragma once`、`#pragma omp parallel` |
| `#if` / `#elif` / `#else` / `#endif` | **条件编译** | 选择哪些代码参与编译 |
| `#ifdef` / `#ifndef` | 检查宏是否定义 | `#ifdef DEBUG` |
| `#define` / `#undef` | 定义/取消宏 | `#define PI 3.14159` |
| `#error` | 编译时报错 | `#error "not supported"` |
| `#line` 🔍 | 重置行号 | `#line 100 "file.cpp"` |
| `#include` | 包含头文件 | `#include <iostream>` |
| `defined()` | 检查宏是否存在 | `#if defined(WIN32)` |

## 十二、字面量后缀

| 后缀 | 类型 | 例子 |
|------|------|------|
| `f` / `F` | float | `3.14f` |
| `l` / `L` | long double（浮点） | `3.14L` |
| `l` / `L` | long（整数） | `100000L` |
| `ll` / `LL` | long long | `100000LL` |
| `u` / `U` | unsigned | `100u` |
| `ul` / `UL` | unsigned long | `100ul` |
| `z` / `Z` 🔍 | size_t | `42z`（C++23） |
| `""s` 🔍 C++14 | std::string | `auto s = "hello"s;` |
| `""sv` 🔍 C++17 | std::string_view | `auto sv = "hello"sv` |
| `""i` 🔍 | 用户自定义字面量 | `auto val = 3.14_deg;` |

## 十三、声明与定义修饰符

| 符号/关键字 | 含义 | 例子 |
|------------|------|------|
| `*` | 指针 | `int* p;` |
| `* const` | 常量指针 | `int* const p;` — 指针本身不可改 |
| `const *` | 指向常量的指针 | `const int* p;` — 指向的值不可改 |
| `&` | **引用**（C++） | `int& ref = a;` — 别名，必须初始化 |
| `&&` 🔍 C++11 | **右值引用** | `int&& rref = std::move(x);` — 用于移动语义 |
| `[]` | 数组 | `int arr[10];` |
| `auto` C++11 | **自动类型推导** | `auto x = 3.14;` 编译器自己推断类型 |
| `decltype` C++11 | 获取表达式类型 | `decltype(x) y;` — y 和 x 同类型 |
| `using` | 类型别名 / 引入名称 | `using Vec = std::vector<int>;` / `using std::cout;` |
| `typedef` 🔍（旧） | 类型别名（C 风格） | `typedef int MyInt;`（推荐用 using 替代） |
| `constexpr` C++11 | 编译期常量表达式 | `constexpr double PI = 3.14159;` |
| `constinit` 🔍 C++20 | 编译期初始化 | `constinit int g = 42;` |
| `consteval` 🔍 C++20 | 强制编译期求值 | `consteval int sq(int x) { return x*x; }` |
| `volatile` 🔍 | 告知编译器每次从内存读 | 用于硬件寄存器、信号处理（极少用） |
| `mutable` 🔍 | 允许 const 对象修改某些成员 | `mutable int cache;` |
| `explicit` | 禁止隐式转换 | `explicit MyClass(int x);` |
| `extern` | 声明但不定义 | `extern int global_var;` |

## 十四、面向对象符号

| 符号/关键字 | 含义 | 例子 |
|------------|------|------|
| `class` / `struct` | 定义类 / 结构体 | `class MyClass { };` |
| `class` 默认 | 成员默认 private | `class A { int x; };` — x 是 private |
| `struct` 默认 | 成员默认 public | `struct B { int x; };` — x 是 public |
| `public:` | 公有访问权限 | 任何地方都能访问 |
| `protected:` | 保护访问权限 | 类内和派生类可访问 |
| `private:` | 私有访问权限 | 仅类内可访问 |
| `virtual` | 虚函数（多态） | `virtual void draw();` |
| `override` C++11 | 明确覆盖基类虚函数 | `void draw() override;` |
| `final` C++11 | 禁止进一步覆盖/继承 | `class FinalClass final {};` |
| `abstract`（无此关键字） | 纯虚函数 | `virtual void f() = 0;` |
| `friend` | 友元（访问私有成员） | `friend class Other;` |
| `this` | 指向当前对象的指针 | `this->value = x;` |
| `sizeof` | 获取类型/变量字节大小 | `sizeof(int)`、`sizeof(arr) / sizeof(arr[0])` |
| `sizeof...` C++11 | 获取参数包个数 | `sizeof...(Args)` |

## 十五、Lambda 表达式符号 — C++11 起

| 符号 | 含义 | 例子 |
|------|------|------|
| `[]` | **捕获列表** | `[=]` 值捕获、`[&]` 引用捕获、`[x, &y]` 具体捕获 |
| `()` | 参数列表 | `[](int a, int b) { return a + b; }` |
| `->` | 尾置返回类型 | `[](int x) -> double { return x * 1.5; }` |
| `{}` | 函数体 | `[]{ std::cout << "hi"; }` |
| `auto` 参数 🔍 C++14 | 泛型 lambda | `[](auto a, auto b) { return a + b; }` |
| `template` 参数 🔍 C++20 | 模板 lambda | `[]<typename T>(T x) { ... }` |
| `mutable` 🔍 | 允许修改值捕获的副本 | `[x]() mutable { x++; }` |

```cpp
auto add = [](double a, double b) -> double { return a + b; };
auto print_each = [](const auto& v) { for (auto x : v) std::cout << x; };
```

## 十六、模板符号

| 符号/关键字 | 含义 | 例子 |
|------------|------|------|
| `template` | 定义模板 | `template<typename T> T max(T a, T b);` |
| `typename` / `class` | 模板参数类型名 | `template<typename T>` |
| `<>` | 模板特化 / 模板参数列表 | `vector<int>`、`template<> struct hash<MyClass>` |
| `<...>` 非类型参数 | 非类型模板参数 | `template<int N>`、`array<double, 3>` |
| `template<>` 🔍 | 显式特化 | `template<> struct is_void<void> { ... };` |
| `...` 参数包 🔍 C++11 | 可变参数模板 | `template<typename... Args>` |
| `typename...` | 可变类型参数包 | `template<typename... Args>` |
| `auto...` 🔍 C++17 | 可变非类型参数包 | `template<auto... Values>` |
| `requires` 🔍 C++20 | 概念约束 | `template<typename T> requires std::integral<T>` |
| `concept` 🔍 C++20 | 定义概念 | `template<typename T> concept Addable = ...;` |

## 十七、属性符号 — C++11/14/17/20

| 符号 | 含义 | 例子 |
|------|------|------|
| `[[noreturn]]` | 函数不会返回 | `[[noreturn]] void abort();` |
| `[[deprecated]]` C++14 | 标记废弃 | `[[deprecated("use new_func instead")]]` |
| `[[maybe_unused]]` C++17 | 抑制未使用警告 | `[[maybe_unused]] int debug_only;` |
| `[[nodiscard]]` C++17 | 返回值不可忽略 | `[[nodiscard]] int check();` |
| `[[fallthrough]]` C++17 | switch 中明确贯穿 | `case 1: ... [[fallthrough]]; case 2:` |
| `[[likely]]` 🔍 C++20 | 分支优化提示（很可能走） | `if ([[likely]] ...)` |
| `[[unlikely]]` 🔍 C++20 | 分支优化提示（很少走） | `if ([[unlikely]] error)` |
| `[[no_unique_address]]` 🔍 C++20 | 允许空成员不占空间 | `[[no_unique_address]] Empty e;` |
| `__attribute__()` 🔍 GCC | GCC 特有属性 | `__attribute__((packed))` |
| `__declspec()` 🔍 MSVC | MSVC 特有属性 | `__declspec(dllexport)` |

## 十八、异常安全与错误处理

| 符号/关键字 | 含义 |
|------------|------|
| `try` | 尝试运行可能抛异常的代码 |
| `catch(...)` | 捕获所有异常 |
| `catch(const std::exception& e)` | 捕获特定类型异常 |
| `throw` | 抛出异常 |
| `noexcept` 🔍 C++11 | 声明函数不抛异常 |
| `noexcept(false)` 🔍 | 声明函数可能抛异常 |
| `noexcept(expr)` 🔍 | 条件 noexcept |
| `static_assert` C++11 | 编译期断言 | `static_assert(sizeof(int) == 4);` |

## 十九、C++17/20 新特性符号

| 符号 | 含义 | 例子 |
|------|------|------|
| `auto [a, b] = ...` C++17 | **结构化绑定** | `auto [x, y] = point;` |
| `if (init; cond)` C++17 | if 内嵌初始化 | `if (auto it = map.find(k); it != map.end())` |
| `switch (init; cond)` C++17 | switch 内嵌初始化 | 同上 |
| `if constexpr` C++17 | **编译期条件分支** | `if constexpr (std::is_pointer_v<T>)` |
| `inline` 变量 C++17 | 头文件内定义全局变量 | `inline int g_counter = 0;` |
| `using enum` 🔍 C++20 | 引入枚举成员到作用域 | `using enum Color::Red;` |
| `@` | **不是 C++ 符号！** | C++ 没有 @ 符号（C# 有） |
| `$` | **不是标准 C++ 符号** | 某些编译器允许标识符含 $，不标准 |

## 二十、其他冷门符号

| 符号 | 含义 | 例子 |
|------|------|------|
| `->` | 尾置返回类型（auto 搭配） | `auto func() -> int;` |
| `.*` / `->*` 🔍 | **成员指针** | `int (MyClass::*ptr) = &MyClass::value;` |
| `::*` 🔍 | 指向成员的指针声明 | `int MyClass::*p = &MyClass::x;` |
| `##` 🔍 | 预处理记号粘合 | `#define VAR(n) x_##n` → `VAR(1)` = `x_1` |
| `#` 🔍 | 预处理字符串化 | `#define STR(x) #x` → `STR(abc)` = `"abc"` |
| `?#` 🔍 | 三字符序列（已移除） | `??=` 曾表示 `#`（C++17 已删除） |
| `compl` 🔍 | 替代 `~`（位取反） | `compl x` 等价于 `~x` |
| `not` 🔍 | 替代 `!`（逻辑非） | `not flag` 等价于 `!flag` |
| `and` 🔍 | 替代 `&&` | `a and b` 等价于 `a && b` |
| `or` 🔍 | 替代 `||` | `a or b` 等价于 `a || b` |
| `xor` 🔍 | 替代 `^` | `a xor b` 等价于 `a ^ b` |
| `bitand` 🔍 | 替代 `&`（按位与） | `a bitand b` 等价于 `a & b` |
| `bitor` 🔍 | 替代 `|` | `a bitor b` 等价于 `a | b` |
| `not_eq` 🔍 | 替代 `!=` | `a not_eq b` 等价于 `a != b` |
| `and_eq` 🔍 | 替代 `&=` | 同上模式 |
| `or_eq` 🔍 | 替代 `|=` | 同上 |
| `xor_eq` 🔍 | 替代 `^=` | 同上 |
| `compl` 系列 | 字母替代运算符 | 需要 `#include <ciso646>`（但主流编译器自动支持） |
| `::` 空前置 | 全局作用域 | `::main`、`::std::cout` — 避免重名冲突 |

## 二十一、优先级速查（从高到低）

```
1.  ::        域解析
2.  () [] . -> ++(后缀) --(后缀)   typeid const_cast dynamic_cast static_cast reinterpret_cast
3.  ++(前缀) --(前缀) + - ! ~ * & sizeof new delete delete[]
4.  .* ->*     成员指针
5.  * / %      乘除取余
6.  + -        加减
7.  << >>      位移 / 输入输出
8.  < <= > >=  比较
9.  == !=      等于不等于
10. &          位与
11. ^          位异或
12. |          位或
13. &&         逻辑与
14. ||         逻辑或
15. ?:         三目
16. = += -= ...  赋值
17. ,          逗号
```

> 记不住优先级就加 `()`，代码可读性比炫技重要。

---

**参考说明：** 🔍 标记的为冷门或高级用法，初学者了解即可，不用死记。优先掌握一至十一节的内容。
