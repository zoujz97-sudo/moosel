# C++ 力学求解器开发学习指南

> 面向对象：零基础 → 独立开发有限元/多物理场求解程序
> 方向：计算固体力学 + 多物理场耦合
> 风格：知识体系驱动（语法系统 → 力学案例串联）
> 预估周期：16周（每周 8–10 小时投入）

---

## 目录总览

| 阶段 | 内容 | 时间 | 产出 |
|------|------|------|------|
| 一 | C++语言基石 | 第1–2周 | 能写数值计算基本程序 |
| 二 | 面向对象编程 | 第3–4周 | 能设计材料/单元类体系 |
| 三 | C++核心进阶 | 第5–6周 | 能使用STL和模板写通用数值代码 |
| 四 | 数值方法与Eigen库 | 第7–8周 | 能求解线性方程组，做矩阵运算 |
| 五 | 有限元求解器实现 | 第9–12周 | 手写2D线弹性FEM程序 |
| 六 | 多物理场耦合 | 第13–16周 | 实现热-力/相场耦合求解器 |

---

# 第一阶段：C++语言基石（第1–2周）

## 目标
搭建开发环境，掌握C++基本语法，能写数值计算程序。

## 第1章 开发环境搭建

### 1.1 推荐方案：WSL + g++ (与MOOSE同一环境)

```bash
# 你已经有了 WSL Ubuntu，确认 g++
g++ --version
# 如果未安装
sudo apt update && sudo apt install g++ cmake gdb
```

### 1.2 第一个程序

```cpp
// hello.cpp
#include <iostream>  // 输入输出库

int main() {
    std::cout << "Hello, Mechanics!" << std::endl;
    return 0;
}
```

```bash
g++ hello.cpp -o hello && ./hello
```

### 1.3 力学应用：编译运行第一个物理计算

```cpp
// stress_calc.cpp — 计算杆件应力
#include <iostream>

int main() {
    double force = 1000.0;        // N
    double area = 0.005;          // m²
    double stress = force / area; // σ = F/A

    std::cout << "力: " << force << " N" << std::endl;
    std::cout << "截面积: " << area << " m²" << std::endl;
    std::cout << "应力: " << stress << " Pa" << std::endl;
    return 0;
}
```

**知识点总结：**
- `#include` 预处理指令
- `main()` 函数 — 程序入口
- `std::cout <<` — 控制台输出
- `std::endl` — 换行
- 变量声明与初始化
- 基本算术运算

---

## 第2章 变量、类型与运算符

### 2.1 基本数据类型

```cpp
int n = 10;              // 整数
double x = 3.14159;      // 双精度浮点数（力学中最常用）
float f = 1.0f;          // 单精度（少用，精度不够）
bool flag = true;        // 布尔值
char c = 'A';            // 字符

// 力学常用常量
const double PI = 3.141592653589793;
const double YOUNG_MODULUS = 210e9;  // 钢的弹性模量，Pa
```

### 2.2 算术运算符

```cpp
double a = 10.0, b = 3.0;
double sum = a + b;      // 加法
double dif = a - b;      // 减法
double prod = a * b;     // 乘法
double quot = a / b;     // 除法
// 整数除法注意：
int i = 10 / 3;          // = 3（截断，不是3.333）
double d = 10.0 / 3;     // = 3.33333
```

### 2.3 力学案例：应变与应力计算

```cpp
// strain_stress.cpp
#include <iostream>

int main() {
    // 输入：试件原始长度和伸长量
    double original_length = 100.0;  // mm
    double elongation = 0.15;        // mm
    double young_modulus = 210000.0; // MPa

    // 计算应变 ε = ΔL / L₀
    double strain = elongation / original_length;

    // 计算应力 σ = E · ε
    double stress = young_modulus * strain;

    std::cout << "原始长度: " << original_length << " mm" << std::endl;
    std::cout << "伸长量: " << elongation << " mm" << std::endl;
    std::cout << "应变 ε: " << strain << std::endl;
    std::cout << "弹性模量 E: " << young_modulus << " MPa" << std::endl;
    std::cout << "应力 σ: " << stress << " MPa" << std::endl;

    return 0;
}
```

---

## 第3章 控制流

### 3.1 条件判断

```cpp
double stress = 350.0;
double yield = 235.0;  // Q235钢屈服强度

if (stress > yield) {
    std::cout << "进入塑性！" << std::endl;
} else if (stress > yield * 0.8) {
    std::cout << "接近屈服" << std::endl;
} else {
    std::cout << "弹性状态" << std::endl;
}
```

### 3.2 循环

```cpp
// for循环 — 遍历节点等
int node_count = 5;
for (int i = 0; i < node_count; i++) {
    std::cout << "节点 " << i << " 已处理" << std::endl;
}

// while循环 — 迭代求解
double tolerance = 1e-6;
double residual = 1.0;
int iter = 0;
while (residual > tolerance && iter < 100) {
    // 迭代计算...
    residual *= 0.1;
    iter++;
}
std::cout << "收敛于第 " << iter << " 次迭代" << std::endl;
```

### 3.3 力学案例：应力沿梁高度分布

```cpp
// beam_stress.cpp — 纯弯梁应力分布 σ = M·y / I
#include <iostream>
#include <cmath>

int main() {
    double moment = 50000.0;     // N·m
    double height = 0.3;         // m
    double width = 0.15;         // m
    double inertia = width * std::pow(height, 3) / 12.0; // I = bh³/12

    int n_layers = 11;
    for (int i = 0; i < n_layers; i++) {
        double y = -height/2 + i * height / (n_layers - 1);
        double sigma = moment * y / inertia;
        std::cout << "y = " << y << " m, σ = " << sigma << " Pa" << std::endl;
    }
    return 0;
}
```

**新知识点：** `#include <cmath>`、`std::pow()`、循环内计算

---

## 第4章 函数与作用域

### 4.1 函数定义

```cpp
// 函数声明/定义
double calculate_stress(double force, double area) {
    return force / area;
}

// 主函数调用
int main() {
    double f = 5000.0, a = 0.01;
    double sigma = calculate_stress(f, a);
    std::cout << sigma << std::endl;
    return 0;
}
```

### 4.2 函数重载

```cpp
// 同名函数，不同参数
double norm(double x, double y) {
    return std::sqrt(x*x + y*y);
}

double norm(double x, double y, double z) {
    return std::sqrt(x*x + y*y + z*z);
}
```

### 4.3 力学案例：材料本构函数族

```cpp
// constitutive.cpp — 材料本构模型
#include <iostream>
#include <cmath>

// 线弹性：σ = E·ε
double linear_elastic(double strain, double E) {
    return E * strain;
}

// 理想弹塑性
double elastic_perfect_plastic(double strain, double E, double yield_stress) {
    double stress = E * strain;
    if (std::abs(stress) > yield_stress) {
        stress = (stress > 0 ? 1.0 : -1.0) * yield_stress;
    }
    return stress;
}

// 线性硬化弹塑性
double linear_hardening(double strain, double E, double yield_stress, double H) {
    double elastic_strain = yield_stress / E;
    if (std::abs(strain) <= elastic_strain) {
        return E * strain;
    } else {
        double plastic_strain = std::abs(strain) - elastic_strain;
        double sign = (strain > 0) ? 1.0 : -1.0;
        return sign * (yield_stress + H * plastic_strain);
    }
}

int main() {
    double E = 210000.0;    // MPa
    double ys = 235.0;      // MPa
    double H = 1000.0;      // MPa，硬化模量

    std::cout << "应变\t线弹性\t理想塑性\t硬化塑性" << std::endl;
    for (int i = 0; i <= 20; i++) {
        double eps = i * 0.002;
        std::cout << eps << "\t"
                  << linear_elastic(eps, E) << "\t"
                  << elastic_perfect_plastic(eps, E, ys) << "\t"
                  << linear_hardening(eps, E, ys, H) << std::endl;
    }
    return 0;
}
```

---

## 第5章 数组与指针

### 5.1 数组

```cpp
// 固定大小数组（不推荐力学中使用，用vector代替）
double stress[5] = {100, 200, 150, 300, 250};

// 二维数组 — 3×3 应力张量
double sigma[3][3] = {
    {100, 50, 0},
    {50, -30, 0},
    {0,   0,  0}
};

// 访问元素
std::cout << "σxx = " << sigma[0][0] << std::endl;
```

### 5.2 指针基础

```cpp
double value = 42.0;
double* ptr = &value;         // 取地址
std::cout << *ptr << std::endl; // 解引用，输出42.0

// 指针与数组
double arr[3] = {1.0, 2.0, 3.0};
double* p = arr;              // 数组名即首地址
std::cout << *(p + 1) << std::endl; // 输出2.0
```

### 5.3 new/delete 动态分配

```cpp
// 动态分配数组
int n = 100;
double* data = new double[n];  // 堆上分配
// ... 使用 data ...
delete[] data;                 // 必须释放！
```

> ⚠️ **在力学编程中：尽量不要直接使用 new/delete**
> 用 `std::vector` 代替动态数组，用智能指针代替裸指针。
> 但**理解指针**是看懂MOOSE源码的前提——MOOSE大量使用指针和引用。

### 5.4 力学案例：向量和矩阵的基本操作

```cpp
// vector_ops.cpp — 向量运算
#include <iostream>

// 向量点积
double dot_product(double a[], double b[], int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }
    return result;
}

// 向量范数（模长）
double norm(double v[], int n) {
    return std::sqrt(dot_product(v, v, n));
}

int main() {
    double force[3] = {100.0, 50.0, 0.0};     // N
    double direction[3] = {1.0, 0.0, 0.0};     // 单位方向

    double f_mag = norm(force, 3);
    double work = dot_product(force, direction, 3);

    std::cout << "力的大小: " << f_mag << " N" << std::endl;
    std::cout << "x方向分力: " << work << " N" << std::endl;

    return 0;
}
```

---

## 第6章 引用与const

### 6.1 引用

```cpp
double a = 10.0;
double& ref = a;   // ref是a的引用（别名）
ref = 20.0;        // a也变成20.0

// 函数传引用 — 避免拷贝大对象
void update_stress(double& stress, double increment) {
    stress += increment;
}
```

### 6.2 const 关键字

```cpp
const double PI = 3.14159;         // 常量，不可修改
const int NODES = 8;               // 编译期常量

// const 引用 — 只读，不拷贝
void print_tensor(const double t[3][3]) {
    // t[i][j] 可读不可写
    std::cout << t[0][0] << std::endl;
}
```

### 6.3 阶段力学集成案例：平面桁架节点力计算

```cpp
// truss_forces.cpp — 简单平面桁架
#include <iostream>
#include <cmath>

const double DEG2RAD = M_PI / 180.0;

// 计算杆件内力（基于节点位移）
double element_force(double displacement, double E, double A, double L) {
    return (E * A / L) * displacement;
}

int main() {
    // 三杆桁架参数
    double E  = 200e9;  // Pa
    double A1 = 0.005;   // m²
    double L1 = 2.0;     // m

    // 荷载
    double P = 50000.0;  // N

    // 假设节点位移（简化演示，实际应由全局求解得到）
    double u_x = 0.0012;  // m

    // 各杆轴力
    double F1 = element_force(u_x, E, A1, L1);

    std::cout << "=== 平面桁架内力计算 ===" << std::endl;
    std::cout << "外荷载 P = " << P << " N" << std::endl;
    std::cout << "节点位移 u_x = " << u_x << " m" << std::endl;
    std::cout << "杆件1轴力: " << F1 / 1000 << " kN" << std::endl;

    // 校核：F1 应接近 P
    std::cout << "校核: F1 / P = " << (F1 / P) << std::endl;

    return 0;
}
```

---

# 第二阶段：面向对象编程（第3–4周）

## 目标
掌握类与对象、继承与多态，能用OOP思想设计力学计算类体系。

## 第7章 类与对象

### 7.1 类的定义

```cpp
class Material {
public:                    // 公开接口
    // 构造函数
    Material(double E, double nu)
        : young_modulus_(E), poisson_ratio_(nu) {}

    // 成员函数
    double get_E() const { return young_modulus_; }
    double get_nu() const { return poisson_ratio_; }
    double get_G() const {  // 剪切模量 G = E / 2(1+ν)
        return young_modulus_ / (2.0 * (1.0 + poisson_ratio_));
    }

private:                   // 私有数据
    double young_modulus_;
    double poisson_ratio_;
};

// 使用
Material steel(210e9, 0.3);
std::cout << "G = " << steel.get_G() << " Pa" << std::endl;
```

### 7.2 力学案例：材料类体系

```cpp
// material_demo.cpp
#include <iostream>
#include <string>

class Material {
public:
    Material(const std::string& name, double E, double nu, double rho)
        : name_(name), E_(E), nu_(nu), rho_(rho) {}

    // 弹性常数
    double E()  const { return E_; }
    double nu() const { return nu_; }
    double G()  const { return E_ / (2.0 * (1.0 + nu_)); }
    double K()  const { return E_ / (3.0 * (1.0 - 2.0 * nu_)); } // 体积模量
    double lambda() const { return nu_ * E_ / ((1.0+nu_)*(1.0-2.0*nu_)); } // Lame常数

    double density() const { return rho_; }
    std::string name() const { return name_; }

    void print_info() const {
        std::cout << name_ << ": E=" << E_/1e9 << " GPa, ν=" << nu_
                  << ", ρ=" << rho_ << " kg/m³" << std::endl;
    }

private:
    std::string name_;
    double E_, nu_, rho_;
};

int main() {
    Material steel("Q235钢", 210e9, 0.3, 7850);
    Material aluminum("铝合金6061", 69e9, 0.33, 2700);
    Material concrete("C30混凝土", 30e9, 0.2, 2400);

    steel.print_info();
    aluminum.print_info();
    concrete.print_info();

    std::cout << "\nQ235钢的剪切模量 G = " << steel.G() / 1e9 << " GPa" << std::endl;
    std::cout << "体积模量 K = " << steel.K() / 1e9 << " GPa" << std::endl;

    return 0;
}
```

---

## 第8章 继承与多态

### 8.1 继承 — 建立材料/单元分类体系

```cpp
// 基类：材料
class Material {
public:
    Material(double E, double nu) : E_(E), nu_(nu) {}
    virtual double compute_stress(double strain) const {
        return E_ * strain;  // 默认线弹性
    }
    virtual ~Material() = default;  // 虚析构（重要！）

protected:
    double E_, nu_;
};

// 派生类：弹塑性材料
class PlasticMaterial : public Material {
public:
    PlasticMaterial(double E, double nu, double yield_stress, double H)
        : Material(E, nu), yield_(yield_stress), H_(H) {}

    // 重写（override）基类虚函数
    double compute_stress(double strain) const override {
        double elastic_strain = yield_ / E_;
        if (std::abs(strain) <= elastic_strain) {
            return E_ * strain;
        } else {
            double plastic_strain = std::abs(strain) - elastic_strain;
            double sign = (strain > 0) ? 1.0 : -1.0;
            return sign * (yield_ + H_ * plastic_strain);
        }
    }

private:
    double yield_, H_;
};
```

### 8.2 多态 — 统一接口，不同行为

```cpp
// 多态核心：通过基类指针调用派生类方法
Material* mat = new PlasticMaterial(210e9, 0.3, 235e6, 1e9);
double sigma = mat->compute_stress(0.005);  // 调用PlasticMaterial版本
delete mat;
```

### 8.3 纯虚函数与抽象类

```cpp
// 抽象基类：所有单元类型的接口
class Element {
public:
    virtual ~Element() = default;
    virtual int num_nodes() const = 0;          // 纯虚函数
    virtual double compute_area() const = 0;
    virtual void print_info() const = 0;
};
// 不能直接创建Element对象，必须派生
```

### 8.4 力学案例：面向对象的FEM材料-单元体系

```cpp
// oop_fem.cpp — 面向对象有限元基础
#include <iostream>
#include <vector>
#include <cmath>

// === 抽象基类：材料 ===
class Material {
public:
    Material(double E, double nu) : E_(E), nu_(nu) {}
    virtual ~Material() = default;

    double E() const { return E_; }
    double nu() const { return nu_; }

    virtual std::string type() const = 0;
    virtual void print() const {
        std::cout << type() << ": E=" << E_/1e9 << " GPa, ν=" << nu_;
    }

protected:
    double E_, nu_;
};

// === 派生：线弹性材料 ===
class ElasticMaterial : public Material {
public:
    ElasticMaterial(double E, double nu) : Material(E, nu) {}
    std::string type() const override { return "线弹性材料"; }
};

// === 派生：热弹性材料 ===
class ThermalMaterial : public ElasticMaterial {
public:
    ThermalMaterial(double E, double nu, double alpha)
        : ElasticMaterial(E, nu), alpha_(alpha) {}

    double alpha() const { return alpha_; }

    std::string type() const override { return "热弹性材料"; }

    void print() const override {
        ElasticMaterial::print();
        std::cout << ", α=" << alpha_ << " /K";
    }

private:
    double alpha_;
};

// === 抽象基类：单元 ===
class Element {
public:
    Element(const std::vector<double>& coords, Material* mat)
        : coords_(coords), material_(mat) {}

    virtual ~Element() = default;

    virtual int dim() const = 0;
    virtual int num_nodes() const = 0;
    virtual double compute_stiffness_entry(int i, int j) const = 0;

    void set_material(Material* mat) { material_ = mat; }

    virtual void print() const {
        std::cout << "  单元: " << num_nodes() << "节点, "
                  << dim() << "维" << std::endl;
    }

protected:
    std::vector<double> coords_;
    Material* material_;
};

// === 派生：杆单元 ===
class TrussElement : public Element {
public:
    TrussElement(const std::vector<double>& coords, Material* mat, double area)
        : Element(coords, mat), area_(area) {}

    int dim() const override { return 2; }
    int num_nodes() const override { return 2; }

    // 杆单元刚度系数 k = EA/L
    double compute_stiffness_entry(int i, int j) const override {
        if (i == j) return 1.0;  // 简化
        return -1.0;
    }

    double length() const {
        double dx = coords_[2] - coords_[0];
        double dy = coords_[3] - coords_[1];
        return std::sqrt(dx*dx + dy*dy);
    }

    void print() const override {
        Element::print();
        std::cout << "  长度L=" << length() << " m, 面积A=" << area_ << " m²" << std::endl;
    }

private:
    double area_;
};

// === 主函数演示 ===
int main() {
    // 创建材料
    ElasticMaterial steel(210e9, 0.3);
    ThermalMaterial alloy(110e9, 0.32, 23e-6);

    // 创建单元
    std::vector<double> coords = {0.0, 0.0, 2.0, 0.0};
    TrussElement truss(coords, &steel, 0.01);

    // 多态演示
    std::vector<Material*> materials = {&steel, &alloy};
    for (auto mat : materials) {
        mat->print();
        std::cout << std::endl;
    }

    truss.print();

    return 0;
}
```

---

## 第9章 运算符重载

### 9.1 力学向量类

```cpp
// 2D向量类，支持运算符重载
class Vec2D {
public:
    double x, y;

    Vec2D(double x = 0, double y = 0) : x(x), y(y) {}

    // + 运算符
    Vec2D operator+(const Vec2D& rhs) const {
        return Vec2D(x + rhs.x, y + rhs.y);
    }

    // - 运算符
    Vec2D operator-(const Vec2D& rhs) const {
        return Vec2D(x - rhs.x, y - rhs.y);
    }

    // 标量乘法（向量 × 标量）
    Vec2D operator*(double s) const {
        return Vec2D(x * s, y * s);
    }

    // 点积
    double dot(const Vec2D& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    // 输出运算符重载（友元函数）
    friend std::ostream& operator<<(std::ostream& os, const Vec2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

// 标量 × 向量（左侧乘法）
Vec2D operator*(double s, const Vec2D& v) {
    return Vec2D(s * v.x, s * v.y);
}
```

> **力学意义：** 运算符重载让代码更接近数学表达式。
> `f = k * u` 在代码中写成 `force = stiffness * displacement;`
> Eigen库全面运用了这一技术。

---

## 🌟 第二阶段集成案例：2D线弹性材料点应力计算

```cpp
// stage2_final.cpp — 综合运用类、继承、多态、运算符重载
// 计算给定应变状态下的应力响应，支持不同材料模型
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

// ========== 2D 张量类（运算符重载） ==========
class Tensor2D {
public:
    double xx, yy, xy;
    Tensor2D(double xx=0, double yy=0, double xy=0)
        : xx(xx), yy(yy), xy(xy) {}

    Tensor2D operator+(const Tensor2D& rhs) const {
        return {xx+rhs.xx, yy+rhs.yy, xy+rhs.xy};
    }
    Tensor2D operator-(const Tensor2D& rhs) const {
        return {xx-rhs.xx, yy-rhs.yy, xy-rhs.xy};
    }
    Tensor2D operator*(double s) const {
        return {xx*s, yy*s, xy*s};
    }

    friend std::ostream& operator<<(std::ostream& os, const Tensor2D& t) {
        os << "[" << t.xx << ", " << t.yy << ", " << t.xy << "]ᵀ";
        return os;
    }
};

// ========== 材料基类 ==========
class Material {
public:
    Material(double E, double nu) : E_(E), nu_(nu) {}
    virtual ~Material() = default;

    // 给定应变张量，返回应力张量
    virtual Tensor2D compute_stress(const Tensor2D& strain) const = 0;

    double E() const { return E_; }
    double nu() const { return nu_; }

protected:
    double E_, nu_;
};

// ========== 平面应力线弹性 ==========
class PlaneStressElastic : public Material {
public:
    PlaneStressElastic(double E, double nu) : Material(E, nu) {
        // 弹性矩阵系数
        double c = E / (1.0 - nu*nu);
        D11_ = D22_ = c;
        D12_ = D21_ = c * nu;
        D33_ = c * (1.0 - nu) / 2.0;
    }

    Tensor2D compute_stress(const Tensor2D& eps) const override {
        double sx = D11_*eps.xx + D12_*eps.yy;
        double sy = D21_*eps.xx + D22_*eps.yy;
        double sxy = D33_*eps.xy;
        return {sx, sy, sxy};
    }

private:
    double D11_, D12_, D21_, D22_, D33_;
};

// ========== 平面应变线弹性 ==========
class PlaneStrainElastic : public Material {
public:
    PlaneStrainElastic(double E, double nu) : Material(E, nu) {
        double c = E / ((1.0+nu)*(1.0-2.0*nu));
        D11_ = D22_ = c * (1.0 - nu);
        D12_ = D21_ = c * nu;
        D33_ = c * (1.0 - 2.0*nu) / 2.0;
    }

    Tensor2D compute_stress(const Tensor2D& eps) const override {
        double sx = D11_*eps.xx + D12_*eps.yy;
        double sy = D21_*eps.xx + D22_*eps.yy;
        double sxy = D33_*eps.xy;
        return {sx, sy, sxy};
    }

private:
    double D11_, D12_, D21_, D22_, D33_;
};

// ========== 主函数 ==========
int main() {
    // 创建材料
    PlaneStressElastic steel(210e9, 0.3);
    PlaneStrainElastic steel_ps(210e9, 0.3);

    // 给定应变状态
    Tensor2D strain(0.001, -0.0003, 0.0005);

    std::cout << "=== 2D线弹性材料应力计算 ===" << std::endl;
    std::cout << "应变: " << strain << std::endl;
    std::cout << "\n--- 平面应力 ---" << std::endl;
    Tensor2D s1 = steel.compute_stress(strain);
    std::cout << "应力: " << s1 << " Pa" << std::endl;

    std::cout << "\n--- 平面应变 ---" << std::endl;
    Tensor2D s2 = steel_ps.compute_stress(strain);
    std::cout << "应力: " << s2 << " Pa" << std::endl;

    return 0;
}
```

---

# 第三阶段：C++核心进阶（第5–6周）

## 目标
掌握模板、STL容器和算法、智能指针，能写通用高效的数值代码。

## 第10章 模板编程

### 10.1 函数模板

```cpp
// 通用向量范数函数
template<typename T>
T norm(const std::vector<T>& v) {
    T sum = T(0);
    for (const T& val : v) {
        sum += val * val;
    }
    return std::sqrt(sum);
}

// 使用
std::vector<double> forces = {100, 200, 150};
double n = norm(forces);  // T = double
```

### 10.2 类模板 — 通用矩阵类

```cpp
template<typename T, int N, int M>
class Matrix {
public:
    T data[N][M]{};

    T& operator()(int i, int j) { return data[i][j]; }
    const T& operator()(int i, int j) const { return data[i][j]; }

    // 矩阵乘法 C = A * B （仅当M匹配时可用）
    template<int P>
    Matrix<T, N, P> multiply(const Matrix<T, M, P>& rhs) const {
        Matrix<T, N, P> result;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < P; j++)
                for (int k = 0; k < M; k++)
                    result(i, j) += data[i][k] * rhs(k, j);
        return result;
    }
};

// 使用
Matrix<double, 3, 3> D;   // 3×3 弹性矩阵
Matrix<double, 3, 1> eps; // 应变向量
// D(i,j) = ... 填入数值
```

> ⚠️ **注意：** 实际力学计算中**不要手写模板矩阵类**。
> 理解模板是为了看懂MOOSE源码和Eigen库。实际开发用 **Eigen** 库。

---

## 第11章 STL容器

### 11.1 std::vector — 动态数组（最常用）

```cpp
#include <vector>

// 节点坐标列表
std::vector<double> x_coords = {0.0, 1.0, 2.0, 3.0};

x_coords.push_back(4.0);         // 末尾添加
size_t n = x_coords.size();      // 大小
double first = x_coords[0];      // 访问（不检查边界）
double safe = x_coords.at(0);    // 访问（越界抛异常）

// 范围for循环
for (double x : x_coords) {
    std::cout << x << std::endl;
}

// 二维向量（存储网格节点）
std::vector<std::vector<double>> nodes = {
    {0.0, 0.0},
    {1.0, 0.0},
    {0.0, 1.0}
};

// 预分配提高性能
std::vector<double> forces;
forces.reserve(10000);  // 预分配10000个元素的空间
```

### 11.2 其他容器

```cpp
#include <map>     // 键值对，如节点编号→自由度映射
#include <set>     // 有序集合，如边界节点集合
#include <array>   // 固定大小数组（优于C风格数组）

// map示例：约束边界条件
std::map<int, double> boundary_conditions;
boundary_conditions[0] = 0.0;   // 节点0位移=0
boundary_conditions[5] = 0.0;   // 节点5位移=0

// set示例：固定节点集
std::set<int> fixed_nodes = {0, 5, 10, 15};

// array示例：3×3 矩阵
std::array<std::array<double, 3>, 3> identity = {{
    {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
}};
```

### 11.3 力学案例：使用STL管理网格数据

```cpp
// mesh_stl.cpp — STL容器管理有限元网格
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>

// 节点结构
struct Node {
    int id;
    double x, y;
};

// 单元结构
struct Element {
    int id;
    std::vector<int> node_ids;  // 构成单元的节点编号
};

int main() {
    // 创建网格：4个节点，2个三角形单元
    std::vector<Node> nodes = {
        {0, 0.0, 0.0},
        {1, 1.0, 0.0},
        {2, 0.0, 1.0},
        {3, 1.0, 1.0}
    };

    std::vector<Element> elements = {
        {0, {0, 1, 2}},
        {1, {1, 3, 2}}
    };

    // 边界条件：固定节点0和节点2
    std::set<int> fixed_nodes = {0, 2};
    std::map<int, double> loads;
    loads[1] = -1000.0;  // 节点1 y方向荷载
    loads[3] = -500.0;   // 节点3 y方向荷载

    // 输出网格信息
    std::cout << "=== 网格信息 ===" << std::endl;
    std::cout << "节点数: " << nodes.size() << std::endl;
    std::cout << "单元数: " << elements.size() << std::endl;

    std::cout << "\n固定节点: ";
    for (int id : fixed_nodes) std::cout << id << " ";
    std::cout << std::endl;

    std::cout << "\n荷载: " << std::endl;
    for (const auto& [node_id, force] : loads) {
        std::cout << "  节点" << node_id << ": " << force << " N" << std::endl;
    }

    // 计算单元面积
    for (const auto& elem : elements) {
        const Node& n0 = nodes[elem.node_ids[0]];
        const Node& n1 = nodes[elem.node_ids[1]];
        const Node& n2 = nodes[elem.node_ids[2]];

        double area = 0.5 * std::abs(
            (n1.x - n0.x)*(n2.y - n0.y) - (n2.x - n0.x)*(n1.y - n0.y)
        );
        std::cout << "单元" << elem.id << " 面积: " << area << std::endl;
    }

    return 0;
}
```

---

## 第12章 智能指针与RAII

### 12.1 为什么需要智能指针

```cpp
// 裸指针的问题
Material* mat = new ElasticMaterial(210e9, 0.3);
// ... 如果中途抛出异常 ...
delete mat;  // 可能执行不到！内存泄漏
```

### 12.2 std::unique_ptr（独占所有权）

```cpp
#include <memory>

auto mat = std::make_unique<ElasticMaterial>(210e9, 0.3);
// mat 超出作用域时自动释放
// 不能拷贝，只能移动
```

### 12.3 std::shared_ptr（共享所有权）

```cpp
// 多个对象共享同一个材料
auto mat = std::make_shared<ElasticMaterial>(210e9, 0.3);

Element elem1(..., mat);
Element elem2(..., mat);
// 引用计数归零时自动释放
```

### 12.4 力学案例：智能指针管理材料

```cpp
// smart_ptr_demo.cpp
#include <iostream>
#include <memory>
#include <vector>

class Material { /* 同前... */ };
class ElasticMaterial : public Material { /* ... */ };

int main() {
    // 用 unique_ptr 管理材料（推荐）
    auto steel = std::make_unique<ElasticMaterial>(210e9, 0.3);

    // 多个单元共享材料用 shared_ptr
    std::vector<std::shared_ptr<Material>> materials;
    materials.push_back(std::make_shared<ElasticMaterial>(210e9, 0.3));
    materials.push_back(std::make_shared<ElasticMaterial>(69e9, 0.33));

    for (const auto& mat : materials) {
        std::cout << "E = " << mat->E() / 1e9 << " GPa" << std::endl;
    }
    // 自动释放，不用delete

    return 0;
}
```

---

## 第13章 文件读写与后处理基础

### 13.1 写VTK文件（可视化用ParaView）

```cpp
// 写出最简单的VTK格式，可在ParaView中查看
#include <fstream>

void write_vtk_points(const std::string& filename,
                      const std::vector<Node>& nodes) {
    std::ofstream file(filename);
    file << "# vtk DataFile Version 3.0\n";
    file << "2D mesh\nASCII\nDATASET POLYDATA\n";
    file << "POINTS " << nodes.size() << " double\n";
    for (const auto& n : nodes) {
        file << n.x << " " << n.y << " 0.0\n";
    }
    file.close();
}
```

### 13.2 读输入文件

```cpp
// 从文本文件读节点坐标
std::vector<Node> read_nodes(const std::string& filename) {
    std::vector<Node> nodes;
    std::ifstream file(filename);
    int id; double x, y;
    while (file >> id >> x >> y) {
        nodes.push_back({id, x, y});
    }
    return nodes;
}
```

### 13.3 阶段力学案例：完整FEM输入输出

```cpp
// mesh_io.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Node { int id; double x, y; };
struct Element { int id; int n1, n2; };

// 写VTK
void write_vtk(const std::string& fn, const std::vector<Node>& nodes,
               const std::vector<Element>& elems,
               const std::vector<double>& displacements) {
    std::ofstream out(fn);
    out << "# vtk DataFile Version 3.0\nFEM Result\nASCII\nDATASET UNSTRUCTURED_GRID\n";
    out << "POINTS " << nodes.size() << " double\n";
    for (const auto& n : nodes)
        out << n.x << " " << n.y << " 0.0\n";

    out << "CELLS " << elems.size() << " " << (elems.size() * 3) << "\n";
    for (const auto& e : elems)
        out << "2 " << e.n1 << " " << e.n2 << "\n";

    out << "CELL_TYPES " << elems.size() << "\n";
    for (size_t i = 0; i < elems.size(); i++)
        out << "3\n";  // VTK_LINE = 3

    out << "POINT_DATA " << nodes.size() << "\n";
    out << "SCALARS displacement double 1\nLOOKUP_TABLE default\n";
    for (double d : displacements) out << d << "\n";

    out.close();
    std::cout << "已写出: " << fn << std::endl;
}

int main() {
    // 简单1D杆系
    std::vector<Node> nodes = {{0,0,0}, {1,1,0}, {2,2,0}, {3,3,0}};
    std::vector<Element> elems = {{0,0,1}, {1,1,2}, {2,2,3}};
    std::vector<double> disp = {0.0, 0.5, 1.0, 1.2};

    write_vtk("truss_result.vtk", nodes, elems, disp);

    return 0;
}
```

---

# 第四阶段：数值方法与Eigen库（第7–8周）

## 目标
掌握线性代数求解、数值积分，能用Eigen库高效实现力学矩阵运算。

## 第14章 Eigen库入门

### 14.1 安装

```bash
sudo apt install libeigen3-dev
# 或者在CMakeLists.txt中
# find_package(Eigen3 REQUIRED)
```

### 14.2 基本使用

```cpp
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

int main() {
    // 定义向量
    Vector3d f;         // 3×1 double向量
    f << 100, 200, 150; // 逗号初始化

    // 定义矩阵
    Matrix3d K;         // 3×3 double矩阵
    K << 2, -1, 0,
         -1, 2, -1,
         0, -1, 2;

    // 求解线性方程组 K·u = f
    Vector3d u = K.colPivHouseholderQr().solve(f);

    std::cout << "解 u = \n" << u << std::endl;

    // 核验
    std::cout << "残差 = " << (K*u - f).norm() << std::endl;

    return 0;
}
```

### 14.3 力学矩阵运算

```cpp
// 应变-位移矩阵 B
Matrix<double, 3, 6> B;  // 3×6

// 弹性矩阵 D
Matrix3d D = (E / (1-nu*nu)) * (Matrix3d() <<
    1, nu, 0,
    nu, 1, 0,
    0, 0, (1-nu)/2
).finished();

// 单元刚度矩阵 k = ∫BᵀDB dV
Matrix<double, 6, 6> ke = B.transpose() * D * B * detJ * weight;

// 组装到全局矩阵
for (int i = 0; i < 6; i++)
    for (int j = 0; j < 6; j++)
        K(global_i, global_j) += ke(i, j);
```

---

## 第15章 线性方程组求解

### 15.1 直接法（小规模）

```cpp
// 中小规模问题（<10000自由度）
MatrixXd K(1000, 1000);
VectorXd f(1000);
// ...填充K和f...

// LLT分解（对称正定矩阵—弹性力学最常见）
VectorXd u = K.llt().solve(f);

// LU分解（一般方阵）
VectorXd u2 = K.lu().solve(f);
```

### 15.2 迭代法（大规模）

```cpp
#include <Eigen/IterativeLinearSolvers>

// 共轭梯度法（对称正定）
ConjugateGradient<SparseMatrix<double>> cg;
cg.compute(K_sparse);
VectorXd u = cg.solve(f);
std::cout << "#迭代次数: " << cg.iterations() << std::endl;
std::cout << "残差: " << cg.error() << std::endl;
```

### 15.3 稀疏矩阵（大规模FEM关键）

```cpp
#include <Eigen/Sparse>

// 创建稀疏矩阵（三对角，1000×1000）
int n = 1000;
SparseMatrix<double> K(n, n);
K.reserve(VectorXi::Constant(n, 3));  // 每行3个非零

// 填充（三元组方式最方便）
std::vector<Triplet<double>> triplets;
for (int i = 0; i < n; i++) {
    triplets.push_back({i, i, 2.0});
    if (i > 0)    triplets.push_back({i, i-1, -1.0});
    if (i < n-1)  triplets.push_back({i, i+1, -1.0});
}
K.setFromTriplets(triplets.begin(), triplets.end());
```

---

## 第16章 数值积分

### 16.1 Gauss-Legendre积分

```cpp
#include <Eigen/Dense>

// 1D高斯积分点和权重
struct GaussPoint {
    double xi;     // 自然坐标
    double weight; // 权重
};

// n=2点高斯积分
std::vector<GaussPoint> gauss_1d_2 = {
    {-1.0/std::sqrt(3), 1.0},
    { 1.0/std::sqrt(3), 1.0}
};

// n=3点
std::vector<GaussPoint> gauss_1d_3 = {
    {-std::sqrt(3.0/5.0), 5.0/9.0},
    {0.0, 8.0/9.0},
    { std::sqrt(3.0/5.0), 5.0/9.0}
};

// 2D四边形单元积分
// 使用嵌套循环：for 每个ξ方向 × 每个η方向
// 权重乘积 w_ξ × w_η
```

### 16.2 力学案例：数值积分计算截面惯性矩

```cpp
// gauss_integration.cpp — 高斯积分计算I形截面惯性矩
#include <iostream>
#include <vector>
#include <cmath>

struct Gauss1D {
    double xi, w;
};

std::vector<Gauss1D> gauss(int n) {
    if (n == 2) return {{-1.0/std::sqrt(3), 1.0}, {1.0/std::sqrt(3), 1.0}};
    if (n == 3) return {
        {-std::sqrt(3.0/5.0), 5.0/9.0},
        {0.0, 8.0/9.0},
        {std::sqrt(3.0/5.0), 5.0/9.0}
    };
    // n=4
    double w1 = (18.0 - std::sqrt(30.0)) / 36.0;
    double w2 = (18.0 + std::sqrt(30.0)) / 36.0;
    double x1 = std::sqrt(3.0/7.0 + 2.0/7.0*std::sqrt(6.0/5.0));
    double x2 = std::sqrt(3.0/7.0 - 2.0/7.0*std::sqrt(6.0/5.0));
    return {{-x1, w1}, {-x2, w2}, {x2, w2}, {x1, w1}};
}

int main() {
    // 计算 ∫y²dA，梁高h=0.3m，宽度b=0.15m
    double h = 0.3, b = 0.15;
    auto gp = gauss(3);

    double I = 0.0;
    for (const auto& p : gp) {
        // 从自然坐标ξ到物理坐标y
        double y = p.xi * h / 2.0;
        double J = h / 2.0;  // 雅可比
        // 对于矩形截面，y²的贡献
        double integrand = (y*y) * b;
        I += integrand * J * p.w;
    }

    double I_exact = b * h*h*h / 12.0;
    std::cout << "数值积分 I = " << I << " m⁴" << std::endl;
    std::cout << "精确值  I = " << I_exact << " m⁴" << std::endl;
    std::cout << "误差: " << std::abs(I - I_exact) / I_exact * 100 << " %" << std::endl;

    return 0;
}
```

---

# 第五阶段：有限元求解器实现（第9–12周）

## 目标
从零实现2D线弹性有限元求解器（C3D4 / Quad4单元），含前处理→求解→后处理完整流程。

## 第17章 有限元核心数据结构和组装

### 17.1 节点、单元、网格类

```cpp
// 节点
class Node {
public:
    int id;
    double x, y;
    int dof_ids[2];     // 全局自由度编号
    bool is_fixed[2];
    double prescribed[2];

    Node(int id, double x, double y)
        : id(id), x(x), y(y) {
        dof_ids[0] = dof_ids[1] = -1;
        is_fixed[0] = is_fixed[1] = false;
        prescribed[0] = prescribed[1] = 0.0;
    }
};

// 四边形单元
class Quad4Element {
public:
    int id;
    int node_ids[4];   // 4个节点编号
    Material* mat;
    double thickness;

    Quad4Element(int id, const int nids[4], Material* m, double t)
        : id(id), mat(m), thickness(t) {
        for (int i = 0; i < 4; i++) node_ids[i] = nids[i];
    }

    // 形函数在自然坐标(ξ,η)处求值
    void shape_functions(double xi, double eta, double N[4]) const {
        N[0] = 0.25 * (1 - xi) * (1 - eta);
        N[1] = 0.25 * (1 + xi) * (1 - eta);
        N[2] = 0.25 * (1 + xi) * (1 + eta);
        N[3] = 0.25 * (1 - xi) * (1 + eta);
    }

    // 形函数导数
    void shape_derivatives(double xi, double eta,
                          double dN_dxi[4], double dN_deta[4]) const {
        dN_dxi[0]  = -0.25 * (1 - eta);
        dN_dxi[1]  =  0.25 * (1 - eta);
        dN_dxi[2]  =  0.25 * (1 + eta);
        dN_dxi[3]  = -0.25 * (1 + eta);

        dN_deta[0] = -0.25 * (1 - xi);
        dN_deta[1] = -0.25 * (1 + xi);
        dN_deta[2] =  0.25 * (1 + xi);
        dN_deta[3] =  0.25 * (1 - xi);
    }
};
```

### 17.2 全局刚度矩阵组装

```cpp
// 组装流程
void assemble_stiffness(Mesh& mesh, SparseMatrix<double>& K) {
    std::vector<Triplet<double>> triplets;

    for (const auto& elem : mesh.elements) {
        // 1. 获取节点坐标
        Matrix<double, 4, 2> elem_coords;
        for (int i = 0; i < 4; i++) {
            const Node& n = mesh.nodes[elem.node_ids[i]];
            elem_coords(i, 0) = n.x;
            elem_coords(i, 1) = n.y;
        }

        // 2. 2×2 高斯积分计算单元刚度矩阵
        Matrix<double, 8, 8> ke = Matrix<double, 8, 8>::Zero();
        auto gauss_pts = gauss(2);  // 2×2 高斯点

        for (const auto& gp_xi : gauss_pts) {
            for (const auto& gp_eta : gauss_pts) {
                double xi = gp_xi.xi, eta = gp_eta.xi;
                double w = gp_xi.w * gp_eta.w;

                // 形函数导数
                double dN_dxi[4], dN_deta[4];
                elem.shape_derivatives(xi, eta, dN_dxi, dN_deta);

                // 雅可比矩阵
                Matrix2d J = Matrix2d::Zero();
                for (int i = 0; i < 4; i++) {
                    J(0,0) += dN_dxi[i]  * elem_coords(i, 0);
                    J(0,1) += dN_dxi[i]  * elem_coords(i, 1);
                    J(1,0) += dN_deta[i] * elem_coords(i, 0);
                    J(1,1) += dN_deta[i] * elem_coords(i, 1);
                }
                double detJ = J.determinant();
                Matrix2d invJ = J.inverse();

                // B 矩阵（3×8）
                double dN_dx[4], dN_dy[4];
                for (int i = 0; i < 4; i++) {
                    dN_dx[i] = invJ(0,0)*dN_dxi[i] + invJ(0,1)*dN_deta[i];
                    dN_dy[i] = invJ(1,0)*dN_dxi[i] + invJ(1,1)*dN_deta[i];
                }

                Matrix<double, 3, 8> B = Matrix<double, 3, 8>::Zero();
                for (int i = 0; i < 4; i++) {
                    B(0, 2*i)   = dN_dx[i];
                    B(1, 2*i+1) = dN_dy[i];
                    B(2, 2*i)   = dN_dy[i];
                    B(2, 2*i+1) = dN_dx[i];
                }

                ke += B.transpose() * D * B * detJ * w * elem.thickness;
            }
        }

        // 3. 组装到全局矩阵（通过自由度映射）
        int dof_ids[8];
        for (int i = 0; i < 4; i++) {
            const Node& n = mesh.nodes[elem.node_ids[i]];
            dof_ids[2*i]   = n.dof_ids[0];
            dof_ids[2*i+1] = n.dof_ids[1];
        }

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                triplets.push_back({dof_ids[i], dof_ids[j], ke(i,j)});
    }

    K.setFromTriplets(triplets.begin(), triplets.end());
}
```

### 17.3 边界条件处理

```cpp
// 置1法处理位移边界条件
void apply_bc(SparseMatrix<double>& K, VectorXd& f,
              const std::vector<Node>& nodes) {
    for (const auto& node : nodes) {
        for (int d = 0; d < 2; d++) {
            if (node.is_fixed[d]) {
                int dof = node.dof_ids[d];
                // 对角置1，右端置为给定位移
                // （更鲁棒的：将K对应行列清零后对角置1）
                for (int k = 0; k < K.outerSize(); k++) {
                    for (SparseMatrix<double>::InnerIterator it(K, k); it; ++it) {
                        if (it.row() == dof && it.col() != dof)
                            it.valueRef() = 0;
                        if (it.col() == dof && it.row() != dof)
                            it.valueRef() = 0;
                    }
                }
                K.coeffRef(dof, dof) = 1.0;
                f(dof) = node.prescribed[d];
            }
        }
    }
}
```

---

## 第18章 完整2D线弹性求解器

> 见配套代码：`F:\mooseL\fem_solver\`
> 包含完整可运行的2D Quad4单元线弹性求解器。
> 代码结构：
>
> ```
> fem_solver/
> ├── main.cpp          # 主程序
> ├── mesh.h            # 网格类
> ├── element.h         # 单元类 + 形函数
> ├── assembly.h        # 组装 + 边界条件
> ├── solver.h          # 求解 + 后处理
> └── CMakeLists.txt    # 构建文件
> ```

（详见配套代码仓库，此处给出核心流程伪代码）

```cpp
// 主程序流程
int main() {
    // 1. 创建网格
    auto mesh = create_rectangular_mesh(10, 10, 1.0, 1.0);

    // 2. 设置材料
    PlaneStressElastic steel(210e9, 0.3);

    // 3. 施加边界条件（悬臂梁：左端固定，右端受剪力）
    for (auto& node : mesh.nodes) {
        if (std::abs(node.x) < 1e-10) {
            node.is_fixed[0] = node.is_fixed[1] = true;
        }
        if (std::abs(node.x - 1.0) < 1e-10) {
            node.load[1] = -1000.0 / 11;  // 右端均布剪力
        }
    }

    // 4. 组装求解
    SparseMatrix<double> K(total_dofs, total_dofs);
    VectorXd f(total_dofs);
    assemble_stiffness(mesh, K, steel);
    assemble_loads(mesh, f);
    apply_bc(K, f, mesh.nodes);

    // 5. 求解
    VectorXd u = K.llt().solve(f);

    // 6. 后处理：写出VTK
    write_vtk("result.vtk", mesh.nodes, u);

    return 0;
}
```

---

# 第六阶段：多物理场耦合（第13–16周）

## 目标
理解多物理场耦合求解策略，实现热-力耦合和相场断裂求解器。

## 第19章 热-力耦合

### 19.1 耦合类型

```
                  ┌──────────────────┐
                  │  温度场 T(x,t)    │
                  └────────┬─────────┘
                           │ 热膨胀 α·ΔT → 热应变
                           ▼
                  ┌──────────────────┐
                  │  位移场 u(x,t)    │
                  └────────┬─────────┘
                           │ 塑性耗散 → 热源
                           ▼
                  ┌──────────────────┐
                  │  温度场 T(x,t)    │
                  └──────────────────┘
```

### 19.2 热力耦合求解策略

**顺序耦合（弱耦合）：**
```
每个时间步：
  1. 求解热传导方程 → 得到 T
  2. 计算热应变 ε_th = α(T - T₀)
  3. 求解力学平衡方程（含热应变项）
  4. 下一时间步
```

**全耦合（强耦合）：**
```
每个时间步/每次牛顿迭代：
  1. 同时组装温度自由度和位移自由度
  2. 求解耦合系统 [K_uu K_uT; K_Tu K_TT] · [Δu; ΔT] = [R_u; R_T]
  3. 更新 u 和 T
  4. 检查收敛
```

### 19.3 全耦合实现框架

```cpp
// 热力耦合系统的自由度编号
// 每个节点2个自由度：位移u,v + 温度T
// dof_id = node_id * 3 + 0 (u_x), +1 (u_y), +2 (T)

class ThermoMechanicalElement : public Element {
public:
    // 组装3×3分块矩阵
    void assemble_coupled_stiffness(
        const Matrix<double, 9, 9>& K_uu,
        const Matrix<double, 9, 3>& K_uT,
        const Matrix<double, 3, 9>& K_Tu,
        const Matrix<double, 3, 3>& K_TT,
        Matrix<double, 12, 12>& K_coupled) const {

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                K_coupled.block<2,2>(i*3, j*3)          = K_uu.block<2,2>(i*2, j*2);
                K_coupled.block<2,1>(i*3, j*3+2)        = K_uT.block<2,1>(i*2, j);
                K_coupled.block<1,2>(i*3+2, j*3)        = K_Tu.block<1,2>(i, j*2);
                K_coupled(i*3+2, j*3+2)                 = K_TT(i, j);
            }
        }
    }
};
```

---

## 第20章 相场断裂方法基础

### 20.1 相场法基本概念

> 相场变量 d(x,t) ∈ [0,1]
> - d = 0：完好材料
> - d = 1：完全断裂
> - 0 < d < 1：过渡区（扩散裂纹）

### 20.2 控制方程（AT1模型）

```
位移方程：∇·[(1-d)² · σ] + b = 0

相场方程：G_c · (d - l²·∇²d) = 2(1-d)·H

其中 H 为历史应变场（驱动断裂的不可逆变量）
```

### 20.3 交错求解策略（最常用）

```cpp
for (int step = 0; step < n_steps; step++) {
    // 步A：固定相场d，求解位移场u
    solve_mechanical(u, d, f_ext);

    // 更新历史应变场 H = max(H_old, ψ⁺(ε))
    update_history_field(H, u);

    // 步B：固定位移场u，求解相场d
    solve_phase_field(d, H);

    // 检查是否完全断裂
    if (max(d) > 0.99) break;
}
```

### 20.4 相场法C++核心代码

```cpp
// 相场单元刚度（简化1D示例）
class PhaseFieldElement {
public:
    // 相场刚度矩阵组装（1D）
    void assemble_phase_field(
        const std::vector<double>& node_d,
        double Gc, double l0, double H,
        Matrix2d& K_d, Vector2d& R_d) const {

        // 1点高斯积分
        double L = length();
        double J = L / 2.0;  // 雅可比

        for (const auto& gp : gauss(2)) {
            double xi = gp.xi, w = gp.w;

            double N[2] = {(1-xi)/2, (1+xi)/2};
            double dN[2] = {-1.0/L, 1.0/L};

            // 相场内变量 d_h = N·d
            double d_h = N[0]*node_d[0] + N[1]*node_d[1];

            // 相场残差
            // R_d = ∫[2(1-d)·H·N + Gc(d·N/l + l·dN·ddN/dx)] dV
            // 线性化后：K_d = ∂R_d/∂d

            for (int i = 0; i < 2; i++) {
                R_d(i) += (2.0*(1.0-d_h)*H * N[i]
                           + Gc*(d_h*N[i]/l0 + l0*dN[i]*dN[0]*node_d[0] + l0*dN[i]*dN[1]*node_d[1]))
                          * J * w;

                for (int j = 0; j < 2; j++) {
                    K_d(i,j) += ((-2.0*H * N[i]*N[j])
                                  + Gc*(N[i]*N[j]/l0 + l0*dN[i]*dN[j]))
                                * J * w;
                }
            }
        }
    }
};
```

---

## 第21章 MOOSE代码导读与求解器框架设计

### 21.1 MOOSE架构理解的关键点

```
MOOSE框架核心概念：
┌─────────────────────────────────────────────────────┐
│ 问题（Problem）                                      │
│   ├── 网格（Mesh）— libMesh                         │
│   ├── 变量（Variables）— u, v, T, d 等              │
│   ├── 核（Kernels）— 弱形式的积分项                  │
│   │   ├── StressDivergenceTensors  ← 应力散度项     │
│   │   ├── HeatConduction          ← 热传导项         │
│   │   └── AllenCahn               ← 相场演化项       │
│   ├── 材料（Materials）— 本构关系                    │
│   ├── 边界条件（BCs）                                │
│   └── 执行器（Executioner）— 求解策略                │
│       ├── Newton ← 全耦合牛顿法                      │
│       ├── Steady ← 稳态                             │
│       └── Transient ← 瞬态                          │
└─────────────────────────────────────────────────────┘
```

### 21.2 独立求解器框架设计（学习目标）

学完以上内容后，你应能设计这样的求解器架构：

```cpp
// 自研求解器框架（设计模式）
class SolverBase {
public:
    virtual ~SolverBase() = default;
    virtual void solve() = 0;
};

// 热力耦合求解器
class ThermoMechanicalSolver : public SolverBase {
    Mesh mesh_;
    Material* mat_;
    std::vector<double> temperature_;
    std::vector<double> displacement_;

    void solve() override {
        // 全耦合牛顿迭代
        for (int iter = 0; iter < max_iter_; iter++) {
            assemble_system();
            apply_bc();
            solve_linear();
            update_solution();
            if (check_convergence()) break;
        }
    }

    virtual void assemble_system() = 0;  // 不同单元类型重写
};

// 相场断裂求解器
class PhaseFieldSolver : public ThermoMechanicalSolver {
    std::vector<double> phase_field_;
    std::vector<double> history_field_;

    void solve() override {
        for (int step = 0; step < n_steps_; step++) {
            // 固定相场，求解位移
            solve_mechanical_substep();

            // 更新历史应变
            update_history();

            // 固定位移，求解相场
            solve_phase_field_substep();
        }
    }
};
```

---

# 附录

## A. 推荐书籍

| 阶段 | 书名 | 用途 |
|------|------|------|
| C++入门 | 《C++ Primer》（第5版）第1–7章 | 语法系统学习 |
| C++进阶 | 《Effective C++》 | 避坑指南 |
| 数值方法 | 《Numerical Recipes》第2章 | 线性代数基础 |
| 有限元 | 《有限元方法》Bathe / 《The Finite Element Method》Zienkiewicz | 力学理论基础 |
| 相场法 | 《Phase-Field Methods in Materials Science》 | 相场理论基础 |
| MOOSE | MOOSE官方文档 / 源码 | 实用参考 |

## B. Eigen库速查

```cpp
// 常用操作
VectorXd v(n);                              // 动态向量
MatrixXd A(m, n);                           // 动态矩阵
Matrix3d B;                                 // 3×3固定大小
VectorXi idx(5);                            // 整数向量

A.setZero();                                // 置零
A.setIdentity();                            // 单位阵
A = MatrixXd::Random(3,3);                  // 随机

A.transpose();                              // 转置
A.inverse();                                // 求逆
A.determinant();                            // 行列式
A.trace();                                  // 迹

v.norm();                                   // 2-范数
v.dot(w);                                   // 点积

// 子矩阵
A.block(i, j, rows, cols);                  // 子块
A.row(i);                                   // 第i行
A.col(j);                                   // 第j列

// 求解
x = A.llt().solve(b);                       // Cholesky
x = A.lu().solve(b);                        // LU
x = A.colPivHouseholderQr().solve(b);       // QR

// 特征值
EigenSolver<MatrixXd> es(A);
es.eigenvalues();
es.eigenvectors();
```

## C. CMake构建模板

```cmake
cmake_minimum_required(VERSION 3.16)
project(FEMSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Eigen
find_package(Eigen3 REQUIRED NO_MODULE)

# 查找VTK（后处理）
# find_package(VTK REQUIRED)

add_executable(fem_solver
    main.cpp
    mesh.cpp
    element.cpp
    assembly.cpp
    solver.cpp
    postprocess.cpp
)

target_link_libraries(fem_solver
    Eigen3::Eigen
    # VTK::VTK
)
```

## D. MOOSE源码阅读路线

```
第一阶段（第1–2周）：
  ./framework/src/kernels/        ← 最简单的Kernel看起
  ./framework/src/materials/      ← 材料类

第二阶段（第3–4周）：
  ./modules/tensor_mechanics/     ← 固体力学模块
  ./modules/heat_conduction/      ← 热传导模块

第三阶段（第5–8周）：
  ./modules/phase_field/          ← 相场模块

第四阶段（第9周+）：
  ./framework/src/systems/        ← 求解器系统
  ./framework/src/executioners/   ← 执行器
```

---

## 学习建议

1. **每章必须敲代码** — 只看不写等于没学，每个示例都编译运行
2. **先不求甚解** — 第一阶段不懂的语法，第二阶段回头看就懂了
3. **善用 gdb 调试** — `g++ -g main.cpp && gdb ./a.out` 学会看调用栈
4. **VS Code 配合 WSL** — Remote-SSH/Remote-WSL 插件连WSL写代码
5. **Google + StackOverflow** — 遇到编译错误先查，90%的问题已经被问过
6. **对照MOOSE源码** — 学到一定程度后，去MOOSE源码里搜同样的写法
7. **渐近式目标** —— 不要一上来就想跑相场，先让一个桁架程序跑起来

---

> 这份指南是路线图，不是教科书。
> 每个阶段提到的「力学案例」代码都需要你手动敲一遍、跑通、理解。
> 有问题随时来问，我可以展开任何一个章节写出更详细的教程和配套代码。
