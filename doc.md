# C/C++ 心智模型：从底层到现代的深度之旅

> C++ 之道，不在于多，而在于通。本章将带你从最基础的变量声明一路走到现代 C++ 的资源管理与可调用对象，构建起坚固的底层知识骨架。

---

## 第一阶段：筑基——声明、内存与值语义

这三个主题没有严格的前后依赖，但它们共同构成了理解后续所有高级特性的基石。

---

### 1.1 顺时针螺旋法则：复杂声明的解码术

#### 1.1.1 为什么需要这个法则？

C/C++ 的声明语法有时令人困惑，尤其是当指针、数组和函数指针交织在一起时。比如：

```cpp
int *foo[5];    // foo 是什么？
int (*bar)[5];  // bar 又是什么？
```

直觉可能会骗你——这两者看起来只差一对括号，语义却截然不同。**顺时针螺旋法则（Clockwise/Spiral Rule）** 是解读此类声明的利器，它是经典的"右左法则"的改良版。

#### 1.1.2 法则步骤

1. 从变量名开始。
2. 顺时针螺旋向外阅读：先向右，再向上，再向左，再向下……
3. 遇到 `()` 表示函数，`[]` 表示数组，`*` 表示指针。
4. 始终先处理括号内的内容。

#### 1.1.3 实战解析

**案例一：`int *foo[5]`**

```
        +------ 向右：[5] → foo 是一个长度为 5 的数组
        |
int *foo[5]
 |     |
 |     +------ 向左：* → 数组的每个元素是指针
 |
 +------ 继续向左：int → 指针指向 int 类型
```

结论：**foo 是一个包含 5 个 `int*` 元素的数组**（指针数组）。

代码验证：

```cpp
// 文件：modules/clockwise-spiral/main1.cpp
int a = 10, b = 20, c = 30, d = 40, e = 50;

int* foo[5];       // foo 是"指针的数组"

foo[0] = &a;       // 每个元素存储一个 int 的地址
foo[1] = &b;
// ...
std::cout << *foo[1];  // 解引用得到 20

*foo[0] = 100;         // 通过指针修改原变量
std::cout << a;        // 输出 100
```

**案例二：`int (*bar)[5]`**

```
            +------ 向右：先看括号内 → * → bar 是一个指针
            |
int (*bar)[5]
     |      |
     |      +------ 向右出括号：[5] → 指针指向长度为 5 的数组
     |
     +------ 向左：int → 数组元素类型为 int
```

结论：**bar 是一个指向"包含 5 个 int 的数组"的指针**（数组指针）。

代码验证：

```cpp
// 文件：modules/clockwise-spiral/main2.cpp
int (*bar)[5];     // bar 是"数组的指针"

int matrix[2][5] = {
    {1, 2, 3, 4, 5},
    {6, 7, 8, 9, 10}
};

bar = &matrix[0];        // bar 指向 matrix 的第一行
std::cout << (*bar)[0];  // 输出 1（先解引用得到数组，再取下标）

bar++;                    // 指针移动到下一行
std::cout << (*bar)[0];  // 输出 6
```

#### 1.1.4 举一反三：更复杂的声明

用同样的法则来解读：

| 声明 | 解读 |
|------|------|
| `int *arr[10]` | 10 个 `int*` 的数组（指针数组） |
| `int (*arr)[10]` | 指向 `int[10]` 的指针（数组指针） |
| `int *func()` | 返回 `int*` 的函数 |
| `int (*func)()` | 指向"返回 int 的函数"的指针（函数指针） |
| `int *(*func)()` | 指向"返回 `int*` 的函数"的指针 |
| `int (*arr[5])()` | 5 个函数指针的数组，每个指向返回 int 的函数 |

最后一个可能是你见过最棘手的声明之一——它正是本仓库 `type-aliases` 模块的主角，我们将在 3.1 节用类型别名来驯服它。

#### 1.1.5 法则的局限性：`const` 的解读

顺时针螺旋法则虽然直观，但在面对 `const` 修饰符时会失效。例如：

```cpp
const int* p;   // p 是什么？
int* const p;   // p 又是什么？
```

此时请使用**就近原则**：`const` 修饰它左边最近的类型；如果左边没有类型，则修饰它右边的声明符。

| 声明 | 解读 | 推理 |
|------|------|------|
| `const int* p` | 指向常量的指针 | `const` 修饰 `int` → 指向的值不可变 |
| `int const* p` | 同上（等价写法） | `const` 修饰 `int` |
| `int* const p` | 常量指针 | `const` 修饰 `p` → 指针本身不可变 |
| `const int* const p` | 指向常量的常量指针 | 值和指针都不可变 |

> 记法口诀：看 `const` 在 `*` 的哪一边——在 `*` 左边是"指向常量的指针"，在 `*` 右边是"常量指针"。

---

### 1.2 内存分段：程序的物理地图

#### 1.2.1 程序的六大内存区域

当你的 C/C++ 程序运行时，内存并非铁板一块，而是被逻辑地划分为不同的区域，每个区域有不同的生命周期和用途：

| 区域 | 内容 | 生命周期 | 读写性 |
|------|------|----------|--------|
| **.text** | 机器指令（函数代码） | 程序运行全程 | 只读 |
| **.rodata** | 常量数据（字符串字面量、`const` 全局变量） | 程序运行全程 | 只读 |
| **.data** | 已初始化的全局/静态变量（非零值） | 程序运行全程 | 可读写 |
| **.bss** | 未初始化或零初始化的全局/静态变量 | 程序运行全程 | 可读写 |
| **Stack** | 一般称之为栈，局部变量、函数参数、返回地址 | 函数调用期间 | 可读写 |
| **Heap** | 一般称之为堆，`new`/`malloc` 动态分配的内存 | 手动管理 | 可读写 |

> 注：有些教材将 .text 和 .rodata 合并为"只读区"，但此处按逻辑边界分开讨论，共六大区域。

> **物理类比**：把程序想象成一栋大楼——.text 是承重墙（不能动），.rodata 是公告栏（只能看），.data 和 .bss 是长期租用的办公室，栈是临时会议室，堆是自由工位。

#### 1.2.2 代码验证：地址分布

```cpp
// 文件：modules/memory-segmentation/main3.cpp
void function_for_text_segment() {}
const int g_rodata_var = 10;   // .rodata
int g_data_var = 20;           // .data（非零初始化）
int g_bss_var;                 // .bss（未初始化）

int main(int argc, char* argv[]) {
    int* heap_ptr = new int(30);  // Heap 堆

    // 打印各区域地址
    uintptr_t text_addr   = (uintptr_t)function_for_text_segment;  // 注：函数指针→uintptr_t 在 POSIX 有效，C++标准为"实现定义"
    uintptr_t rodata_addr = (uintptr_t)&g_rodata_var;
    uintptr_t data_addr   = (uintptr_t)&g_data_var;
    uintptr_t bss_addr    = (uintptr_t)&g_bss_var;
    uintptr_t heap_addr   = (uintptr_t)heap_ptr;
    uintptr_t stack_addr  = (uintptr_t)&argv[0];

    // 验证静态区布局：.text < .rodata < .data < .bss
    // 注：此布局为 Linux/Windows 等常见平台的典型排布，受 ASLR 影响，C++标准不作保证，仅供学习观察
    std::cout << std::boolalpha;
    std::cout << ((text_addr < rodata_addr) && (rodata_addr < data_addr) && (data_addr < bss_addr));
    // 输出 true
}
```

运行结果会确认：静态区的四个段地址依次递增，而栈和堆的相对位置因 ASLR（地址空间布局随机化）可能变化。

#### 1.2.3 BSS 段的细节：零初始化的归属

一个常见的疑问是：**"初始化为 0"的变量到底在 .data 还是 .bss？**

```cpp
// 文件：modules/memory-segmentation/main2.cpp
int global_bss_A;                           // .bss（未初始化，默认为 0）
int global_bss_B = 0;                       // .bss（显式零初始化，编译器优化进 .bss）
static int global_bss_C;                    // .bss
static int global_bss_D = 0;                // .bss
int global_bss_array_E[4096];               // .bss（未初始化数组）
int global_bss_array_F[4096] = {0};         // .bss（零初始化数组）

int main() {
    static int local_bss_G;                 // .bss（静态局部变量）
    static int local_bss_H = 0;             // .bss
    static int local_bss_array_I[128];      // .bss
    static int local_bss_array_J[128] = {0};// .bss
}
```

关键结论：**无论是否显式写 `= 0`，只要最终值是零，编译器都会将其放入 .bss 段**。这是工程上的优化——.bss 不占可执行文件的磁盘空间，只在加载时由操作系统清零。

#### 1.2.4 栈的自动管理

```cpp
// 文件：modules/memory-segmentation/main1.cpp
int main() {
    int a = 10, b = 20;
    return a + b;
}
```

这段最简单的代码揭示了栈的核心机制：`a` 和 `b` 在进入 `main` 时被分配在栈上，函数返回时自动销毁。无需手动释放——这正是栈"自动管理"的本质。

#### 1.2.5 举一反三：常见的内存错误模式

| 错误类型 | 示例 | 原因 |
|----------|------|------|
| 返回栈引用 | `int& f() { int x=1; return x; }` | x 已销毁，引用悬空 |
| 忘记释放堆 | `void f() { new int(1); }` | 内存泄漏 |
| 释放后使用 | `delete p; cout << *p;` | 悬空指针 |
| 双重释放 | `delete p; delete p;` | 未定义行为 |

理解了内存分段，这些错误的原因就不言自明了——每个区域有自己的生命周期规则，违反规则就是 bug。

---

### 1.3 移动语义：从深拷贝到资源窃取

#### 1.3.1 左值与右值：身份 vs 短暂

**左值（lvalue）** 是有名字、有地址、可以取地址的表达式——它有持久的"身份"。

**右值（rvalue）** 是没有持久身份的临时值——字面量、临时对象、函数返回的值。

```cpp
// 文件：modules/move-semantics/main1.cpp
int a = 1;          // a 是左值
int b = 2;          // b 是左值
int c = a + b;      // a+b 的结果是右值（临时值）
```

```cpp
// 文件：modules/move-semantics/main2.cpp
int x = 1;

int get_val() { return x; }  // 返回右值（值的副本）
void set_val(int val) {       // val 是左值（形参是左值）
    int *p = &val;            // 可以取地址
}

auto *p = &"annfeng";        // 字符串字面量是左值（存储在 .rodata）
```

一个关键实验：**右值引用能否绑定到左值？**

```cpp
// 文件：modules/move-semantics/main4.cpp
int a = 0;
// int &&b = a;               // 错误！右值引用不能绑定到左值
int &&b = static_cast<int &&>(a);  // 必须显式转换
```

这个 `static_cast<int&&>` 就是 `std::move` 的底层原理——它并不移动任何东西，只是一个类型转换。

#### 1.3.2 左值引用 vs 右值引用

```cpp
// 文件：modules/move-semantics/main6.cpp
int a = 0;
int &b = a;       // 左值引用：绑定到左值 a
int &&c = 2;      // 右值引用：绑定到右值 2
```

**const 左值引用的特权**：它可以绑定到右值，编译器会为右值创建一个临时对象：

```cpp
// 文件：modules/move-semantics/main4.cpp
const int &x = 11;   // 合法！11 是右值，但 const& 可以绑定
std::cout << &x;      // 有地址——编译器创建了临时变量
```

#### 1.3.3 拷贝语义的开销

先看传统的拷贝构造与赋值：

```cpp
// 文件：modules/move-semantics/main5.cpp
class X {
public:
    X() { std::cout << "Default constructor called." << std::endl; }
    X(const X& other) { std::cout << "Copy constructor called." << std::endl; }
    X& operator=(const X& other) {
        std::cout << "Copy assignment operator called." << std::endl;
        return *this;
    }
};

X make_x() {
    return X();  // 返回临时对象（右值）
}

int main() {
    X x1;                // 默认构造
    X x2(x1);            // 复制构造（x1 是左值）
    X x3(make_x());      // RVO 优化，可能省略拷贝
    x3 = make_x();       // 临时对象赋值给 x3，可能触发复制赋值
}
```

当类持有昂贵资源时，每一次深拷贝都代价高昂。

#### 1.3.4 移动语义：偷走而非复制

**物理类比**：想象你有一幅画（资源）。拷贝是"请画师临摹一幅"——耗时且费钱。移动是"直接把画从旧画框取下，挂到新画框"——瞬间完成。

```cpp
// 文件：modules/move-semantics/main7.cpp
class X {
private:
    char* image;                    // 模拟昂贵的资源（如 2KB 图像数据）
    static const size_t IMAGE_SIZE = 2048;

public:
    X() { image = new char[IMAGE_SIZE]; }
    ~X() { delete[] image; }

    // ---- 拷贝语义：昂贵的深拷贝 ----
    X(const X& other) {
        image = new char[IMAGE_SIZE];           // 1. 分配新内存
        memcpy(this->image, other.image, IMAGE_SIZE); // 2. 逐字节复制
    }

    X& operator=(const X& other) {
        if (this == &other) return *this;
        delete[] image;                         // 1. 释放旧资源
        image = new char[IMAGE_SIZE];           // 2. 分配新内存
        memcpy(this->image, other.image, IMAGE_SIZE); // 3. 逐字节复制
        return *this;
    }

    // ---- 移动语义：高效的资源窃取 ----
    X(X&& other) noexcept {
        this->image = other.image;   // 1. 偷走源对象的指针（O(1)）
        other.image = nullptr;       // 2. 置空源对象，避免析构时释放
    }

    X& operator=(X&& other) noexcept {
        if (this == &other) return *this;
        delete[] image;              // 1. 释放自己的旧资源
        this->image = other.image;   // 2. 偷走源对象的指针（O(1)）
        other.image = nullptr;       // 3. 置空源对象
        return *this;
    }
};
```

移动操作的核心只有三步：**偷指针 → 置空源 → 完事**。没有任何内存分配和字节复制。

#### 1.3.5 std::move：不是移动，是转型

```cpp
// 文件：modules/move-semantics/main9.cpp
std::string uploader_name = "安枫的叶";

// 拷贝：两个字符串独立存在
std::string uploader = uploader_name;
// uploader: "安枫的叶"  |  uploader_name: "安枫的叶"

// 移动：资源被转移
std::string new_name = std::move(uploader_name);
// new_name: "安枫的叶"  |  uploader_name: ""（通常变为空）
```

`std::move` 的本质是 `static_cast<typename std::remove_reference<T>::type&&>`，它**不做任何移动**，只是将左值转换为右值引用，使得移动构造/赋值函数被匹配调用。`remove_reference` 保证了无论传入左值还是右值，都能正确推导为对应类型的右值引用（结合引用折叠原则）。

```cpp
// 文件：modules/move-semantics/main8.cpp
int a = 0;
int &&b = static_cast<int&&>(a);  // std::move 的底层实现

b = 100;
std::cout << a;  // 输出 100——b 是 a 的别名，修改 b 就是修改 a
```

> **⚠️ 致命陷阱：具名的右值引用是左值**
>
> 这是 C++11 移动语义中最容易栽跟头的铁律：**右值引用作为具名变量时，它是一个左值！** 有了名字的右值引用，编译器就认为它拥有持久的"身份"，因此可以取地址、可以赋值。
>
> 这意味着在移动构造/移动赋值函数内部，**参数名 `other` 是左值**。如果要移动它的成员变量，必须再次使用 `std::move`：
>
> ```cpp
> // ❌ 错误：other.member 是左值，将触发拷贝而非移动
> X(X&& other) { member = other.member; }
>
> // ✅ 正确：显式 std::move 才能触发 member 的移动语义
> X(X&& other) : member(std::move(other.member)) {}
> ```
>
> 回看下文 2.2.3 Demo 2 的移动构造函数，我们在初始化列表中写了 `Shape(std::move(other))`，正是因为 `other` 虽然是右值引用参数，但它是左值，必须用 `std::move` 才能唤醒基类的移动构造。而对于原生指针 `tag`，直接窃取指针值（`this->tag = other.tag`）本身就是 O(1) 的转移，无需 `std::move`。

对于简单类型如 `int`，移动和拷贝没有区别。移动语义的价值体现在持有资源的类上。

#### 1.3.6 性能对比

```cpp
// 文件：modules/move-semantics/main7.cpp（续）
std::vector<X> make_bunch_of_x(size_t count) {
    std::vector<X> vec;
    vec.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        vec.push_back(X());  // 临时对象触发移动（而非拷贝）
    }
    return vec;
}
```

如果没有移动语义，`push_back` 每次都要深拷贝 2KB 数据。有了移动语义，只需转移一个指针。在 10000 个对象的测试中，移动版本的速度优势是数量级的。

#### 1.3.7 举一反三：移动语义的适用场景

| 场景 | 是否受益 | 原因 |
|------|----------|------|
| `std::vector` 扩容 | 是 | 旧元素被移动到新内存 |
| 函数返回大对象 | 是 | 返回值优化 (RVO) 或移动语义 |
| `std::swap` | 是 | 三次移动替代三次深拷贝 |
| `std::unique_ptr` 传递 | 是 | 所有权转移依赖移动 |
| 简单类型 (`int`, `double`) | 否 | 移动和拷贝开销相同 |

---

## 第二阶段：工程——链接与面向对象

---

### 2.1 静态库与动态库：编译全生命周期的工程权衡

#### 2.1.1 从源码到运行：五大阶段

```
源代码(.cpp) → [预处理] → [编译] → [汇编] → 目标文件(.o/.obj)
                                              ↓
                                        [链接] → 可执行文件
                                              ↓
                                        [加载] → 运行中的进程
```

- **预处理**：展开 `#include`、`#define`，处理条件编译
- **编译**：将预处理后的源码翻译为汇编
- **汇编**：将汇编翻译为目标文件（机器码 + 符号表）
- **链接**：解析符号引用，合并目标文件和库
- **加载**：操作系统将可执行文件载入内存

```cpp
// 文件：modules/dynamic-static-libs/main.cpp
#define NUM 10
#define SQUARE(x) ((x)*(x))
#define DEBUG

int main() {
    int result = SQUARE(NUM);    // 预处理后变为：int result = ((10)*(10));

#ifdef DEBUG                     // 条件编译
    std::cout << "Debug" << std::endl;
#endif
}
```

#### 2.1.2 静态库：编译时合并

静态库（`.a` / `.lib`）是目标文件的归档。链接器从静态库中提取所需的目标文件，**直接合并到最终可执行文件中**。

```cpp
// 文件：modules/dynamic-static-libs/StaticDemo_1/
// --- my_add.h ---
int add(int a, int b);

// --- my_add.cpp ---
int add(int a, int b) { return a + b; }

// --- my_multiply.h ---
int multiply(int a, int b);

// --- my_multiply.cpp ---
int multiply(int a, int b) { return a * b; }

// --- main.cpp ---
#include "my_add.h"
#include "my_multiply.h"
int main() {
    std::cout << add(10, 5);       // 输出 15
    std::cout << multiply(10, 5);  // 输出 50
}
```

CMake 配置（简化）：

```cmake
add_library(my_add_lib STATIC my_add.cpp)      # 编译为静态库
add_executable(my_app main.cpp)
target_link_libraries(my_app my_add_lib)        # 链接时合并
```

**静态库的链式依赖**：

```cpp
// 文件：modules/dynamic-static-libs/StaticDemo_2/
// main → libA → libB（链式依赖）

// libB：底层
int funcB() { return 100; }

// libA：依赖 libB
int funcA() { return funcB() + 50; }

// main：只直接依赖 libA
int main() { int result = funcA(); }  // result = 150
```

注意：在静态链接中，如果 `main` 只声明链接 `libA`，但 `libA` 内部调用了 `libB` 的函数，链接器需要在命令行中 **先写 `libA` 再写 `libB`**（或使用 `--start-group`），否则可能报 `undefined symbol`。CMake 的 `target_link_libraries` 会自动处理传递依赖。

#### 2.1.3 动态库：运行时加载

动态库（`.so` / `.dylib` / `.dll`）在运行时才被加载到进程地址空间。

```cpp
// 文件：modules/dynamic-static-libs/DynamicDemo_1/
// 代码与 StaticDemo_1 完全相同！
// 区别只在 CMake 配置：
add_library(my_add_lib SHARED my_add.cpp)  # SHARED = 动态库
```

**静态库 vs 动态库的工程权衡**：

| 维度 | 静态库 | 动态库 |
|------|--------|--------|
| 链接时机 | 编译时 | 运行时 |
| 可执行文件大小 | 较大（包含库代码） | 较小（仅含引用） |
| 部署 | 单文件即可运行 | 需附带 .so/.dll |
| 更新库 | 需重新编译 | 替换 .so 即可（兼容更新） |
| 内存共享 | 否（每个进程一份） | 是（多个进程共享同一 .so） |
| 可靠性 | 高（版本固定） | 需处理版本兼容（ABI 稳定性） |

> **架构哲学**：静态链接追求**部署隔离性（可靠性）**，动态链接换取**维护灵活性（扩展性）**。没有绝对的对错，只有场景的取舍。

#### 2.1.4 举一反三：动态库版本更新陷阱

假设 `DynamicDemo_1` 的 `add` 函数从 `int add(int, int)` 变更为 `long add(long, long)`：
- **静态库**：旧的可执行文件不受影响，因为它已经包含了旧代码。
- **动态库**：如果只替换了 `.so` 文件而没有重新编译可执行文件，可能出现 **ABI 不兼容**（参数类型/大小变了），导致运行时崩溃或数据错误。

这就是为什么动态库的版本管理（如 `libfoo.so.1` → `libfoo.so.2`）在工程实践中如此重要。

---

### 2.2 面向对象：从封装噩梦到零之法则

#### 2.2.1 Demo 0：封装噩梦——一个类搞定一切

```cpp
// 文件：modules/oop/demo0_encapsulation_nightmare/Shape.h
class Shape {
private:
    enum Type { CIRCLE, RECTANGLE, POLYGON } type;  // 用枚举区分类型
    double radius;
    double width, height;
    std::vector<Point> vertices;
    mutable double cachedArea;
    mutable bool isAreaCached;

public:
    explicit Shape(double r);           // 构造圆形
    explicit Shape(double w, double h); // 构造矩形
    explicit Shape(const std::vector<Point>& v); // 构造多边形

    double getArea() const {
        if (type == CIRCLE)       return 3.14159 * radius * radius;
        else if (type == RECTANGLE) return width * height;
        else if (type == POLYGON)   /* ... 鞋带公式 ... */
    }
};
```

**问题在哪？**

- **违反开闭原则**：每新增一种形状，都要修改 `Shape` 类的内部和 `getArea()`。
- **内存浪费**：每个 `Shape` 对象都携带所有类型的字段，圆形也有 `width` 和 `height`。
- **类型安全丧失**：编译器无法阻止你给"圆形"设置 `width`。

#### 2.2.2 Demo 1：继承与多态——正确的设计

```cpp
// 文件：modules/oop/demo1_inheritance_polymorphism/Shape.h
class Shape {
public:
    virtual ~Shape() {}                      // 虚析构函数
    virtual double getArea() const = 0;      // 纯虚函数——接口契约

protected:
    virtual void print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        shape.print(os);                     // 动态绑定
        return os;
    }
};

class Circle final : public Shape {
    double radius;
public:
    explicit Circle(double r);
    double getArea() const override final;   // 必须实现
protected:
    void print(std::ostream& os) const override;
};

class Rectangle : public Shape { /* ... */ };
class Polygon : public Shape { /* ... */ };
```

**关键设计点**：

1. **`virtual` 析构函数**：确保通过基类指针 `delete` 时调用正确的派生类析构函数。
2. **纯虚函数 `= 0`**：定义接口契约，派生类必须实现。
3. **`override`**：编译器检查你确实在重写虚函数，防止拼写错误。
4. **`final`**：阻止进一步继承或重写，表明设计意图。
5. **`protected` 的 `print`**：NVI（Non-Virtual Interface）模式——公共接口非虚，内部实现虚函数。

**多态的威力**：

```cpp
// 文件：modules/oop/demo1_inheritance_polymorphism/main.cpp
std::vector<Shape*> shapeCollection;
shapeCollection.push_back(&myCircle);
shapeCollection.push_back(&myRect);
shapeCollection.push_back(&myPolygon);

for (const Shape* s : shapeCollection) {
    std::cout << *s << " | Area: " << s->getArea() << "\n";
    // 运行时动态绑定到正确的实现！
}
```

> **⚠️ 注意**：上述示例使用的是栈上对象的地址（`&myCircle`），因此不存在内存泄漏。但在真实工程中，多态容器常常持有堆上分配的对象（通过 `new` 创建）。如果你写了 `shapeCollection.push_back(new Circle(5.0))`，则必须在析构前手动 `delete` 每个元素，否则会内存泄漏。**现代 C++ 的最佳实践是使用 `std::vector<std::unique_ptr<Shape>>`**，让智能指针自动管理生命周期——这将在 3.2 节深入讨论。

**虚函数表的底层原理**：每个含有虚函数的类都有一个虚函数表（vtable），存储着各虚函数的函数指针。每个对象含有一个指向 vtable 的隐式指针（vptr）。调用 `s->getArea()` 时，运行时通过 vptr 查找 vtable，定位到正确的函数——这就是"动态绑定"。

#### 2.2.3 Demo 2：五之法则——手动管理资源

当类持有原始资源（如 `char*`）时，必须定义以下五个特殊成员函数：

1. **析构函数** — 释放资源
2. **复制构造函数** — 深拷贝资源
3. **复制赋值运算符** — 先释放再深拷贝
4. **移动构造函数** — 窃取资源
5. **移动赋值运算符** — 先释放再窃取

```cpp
// 文件：modules/oop/demo2_rule_of_five/Shape.cpp
class Circle final : public Shape {
    double radius;
    char* tag;  // 原始资源！必须手动管理

public:
    // 构造
    explicit Circle(double r, const char* t = "Default Circle") : radius(r) {
        tag = new char[std::strlen(t) + 1];
        std::strcpy(tag, t);
    }

    // 析构
    ~Circle() override { delete[] tag; }

    // 复制构造——深拷贝（⚠️ 必须防御被移动过的源对象）
    Circle(const Circle& other) : Shape(other), radius(other.radius) {
        const char* src = other.tag ? other.tag : "";   // 防御 nullptr
        tag = new char[std::strlen(src) + 1];
        std::strcpy(tag, src);
    }

    // 复制赋值——copy-and-swap 的简化版
    Circle& operator=(const Circle& other) {
        if (this == &other) return *this;  // 自赋值检查
        Shape::operator=(other);           // 别忘了基类！
        const char* src = other.tag ? other.tag : "";   // 防御 nullptr
        char* new_tag = new char[std::strlen(src) + 1];
        std::strcpy(new_tag, src);
        delete[] tag;       // 先分配再释放——异常安全
        tag = new_tag;
        radius = other.radius;
        return *this;
    }

    // 移动构造——窃取
    Circle(Circle&& other) noexcept : Shape(std::move(other)), radius(other.radius), tag(other.tag) {
        other.tag = nullptr;  // 置空源对象
    }

    // 移动赋值——先释放再窃取
    Circle& operator=(Circle&& other) noexcept {
        if (this == &other) return *this;
        Shape::operator=(std::move(other));
        delete[] tag;
        radius = other.radius;
        tag = other.tag;
        other.tag = nullptr;
        return *this;
    }
};
```

> **⚠️ 为什么拷贝操作要防御 `nullptr`？** C++ 标准规定被移动后的对象处于"有效但未指定"（valid but unspecified）的状态——可以安全析构和赋值，但不应假设其值。如果移动构造将 `other.tag` 置为 `nullptr`，随后又用这个被移动过的对象去拷贝构造另一个对象，`std::strlen(nullptr)` 将直接导致**程序崩溃**。因此在拷贝操作中，对任何可能被移动后为空的指针，必须做 `nullptr` 检查。

**移动后的状态**：

```cpp
Circle c4 = std::move(c1);
// c4 (Thief): 拥有原 c1 的所有资源
// c1 (Victim): tag == nullptr，radius 值未定义但安全
```

被移动后的对象处于**有效但未指定**（valid but unspecified）的状态——可以安全析构和赋值，但不应假设其值。

#### 2.2.4 Demo 3：零之法则——用标准库代替手动管理

```cpp
// 文件：modules/oop/demo3_rule_of_zero/Shape.h
class Circle final : public Shape {
    double radius;
    std::string tag;  // 用 std::string 代替 char*！

public:
    explicit Circle(double r, std::string t = "Default Circle")
        : radius(r), tag(std::move(t)) {}  // 构造

    // 不需要析构函数！std::string 自动释放
    // 不需要复制/移动操作！编译器自动生成正确的版本
    // 这就是"零之法则"——不需要写任何一个特殊成员函数

    double getArea() const override { return 3.14159 * radius * radius; }
};
```

**零之法则**：如果一个类的所有成员都遵循零之法则（或三/五之法则），那么这个类本身不需要定义任何特殊成员函数——编译器默认生成的版本就是正确的。

配合智能指针，零之法则的威力倍增：

```cpp
// 文件：modules/oop/demo3_rule_of_zero/main.cpp
std::unique_ptr<Shape> s1 = std::make_unique<Circle>(5.0, "Smart_Circle_A");
std::unique_ptr<Shape> s2 = std::move(s1);  // 所有权转移

std::vector<std::unique_ptr<Shape>> canvas;
canvas.push_back(std::move(s2));
canvas.push_back(std::make_unique<Circle>(10.0, "Smart_Circle_B"));

for (const auto& shape : canvas) {
    std::cout << *shape << " | Area: " << shape->getArea() << "\n";
}
// main 结束时，所有 unique_ptr 自动析构，Circle 自动析构，string 自动释放
// 没有内存泄漏，没有手动 delete
```

#### 2.2.5 举一反三：三法则 vs 五法则 vs 零法则的演进

| 法则 | 时代 | 内容 | 核心思想 |
|------|------|------|----------|
| 三法则 | C++98 | 析构 + 复制构造 + 复制赋值 | 如果需要其中一个，通常三个都需要 |
| 五法则 | C++11 | 三法则 + 移动构造 + 移动赋值 | 移动语义是拷贝的优化，应一并考虑 |
| 零法则 | 现代 C++ | 什么都不写 | 优先使用 RAII 类型，让编译器代劳 |

---

## 第三阶段：抽象——类型别名与智能指针

---

### 3.1 类型别名：驯服复杂声明

#### 3.1.1 typedef vs using

```cpp
// 文件：modules/type-aliases/main2.cpp

// typedef：名字在中间，阅读需要"从中间往两边找"
typedef void (*Handler)(int, int);

// using：名字 = 类型，从左到右阅读
using Handler = void (*)(int, int);
```

`using` 语法更直观，且支持模板别名（`typedef` 不行），是现代 C++ 的推荐写法。

#### 3.1.2 宏定义的陷阱

```cpp
// 文件：modules/type-aliases/main3.cpp
#define IntPtr int*
IntPtr a, b;   // 展开为 int *a, b; → a 是 int*，b 只是 int！

using IntPtr1 = int*;
IntPtr1 c, d;  // c 和 d 都是 int*
```

宏是文本替换，不尊重类型边界。**永远不要用宏定义类型别名**。

#### 3.1.3 分步简化复杂声明

回忆 1.1 节那个最棘手的声明：`int *(*var[5])(void)`——"5 个函数指针的数组，每个指向返回 `int*` 且无参数的函数"。

用 `using` 分步拆解：

```cpp
// 文件：modules/type-aliases/main7.cpp
using IntPtr = int*;                  // 步骤1：定义返回类型
using RawFuncType = IntPtr(void);     // 步骤2：定义函数类型
using FuncPtr = RawFuncType*;         // 步骤3：加 * 变函数指针

FuncPtr myVar;  // 等同于 int* (*myVar)(void);
```

**等价的一步写法**：

```cpp
// 文件：modules/type-aliases/main5.cpp
using FuncPtr = int* (*)(void);  // 直接定义函数指针类型
FuncPtr var[5];                   // 5 个这样的函数指针
```

#### 3.1.4 结合 std::function 的现代写法

```cpp
// 文件：modules/type-aliases/main5.cpp（续）
using FuncPtr = std::function<int*(void)>;  // 现代、类型安全
FuncPtr var[5];  // 同样是 5 个可调用对象
```

`std::function` 可以包装函数指针、仿函数、lambda 等任何可调用对象，比原始函数指针更灵活。

#### 3.1.5 跨平台类型别名

```cpp
// 文件：modules/type-aliases/main4.cpp
#ifdef _WIN64
using WindowHandle = unsigned long long;
#else
using WindowHandle = unsigned long;
#endif

void InitializeWindow(WindowHandle handle);
```

类型别名使得平台相关的类型细节被封装在一个名字背后，上层代码只需使用 `WindowHandle`。

#### 3.1.6 举一反三：函数指针数组 + 容器

```cpp
// 文件：modules/type-aliases/main6.cpp
using FuncPtr = int* (*)(void);

FuncPtr listA[5];                    // 静态数组
FuncPtr listB[100];                  // 更大的静态数组
FuncPtr* dynamicArr = new FuncPtr[n]; // 动态数组
std::vector<FuncPtr> vec;            // STL 容器
```

有了类型别名，无论数组大小、存储方式如何变化，核心类型定义只需一处——这就是抽象的力量。

---

### 3.2 智能指针：自动化的资源管理

#### 3.2.1 unique_ptr：私家车的独占所有权

**物理类比**：`unique_ptr` 就像私家车——同一时刻只有一个人拥有它，转让需要过户（`std::move`）。

```cpp
// 文件：modules/smart-pointers/main2.cpp
class Car {
    std::string name_;
public:
    explicit Car(std::string name) : name_{std::move(name)} {}
    void drive() const { std::cout << "驾驶 " << name_ << " 出发！\n"; }
};

void sell_car_to_friend(std::unique_ptr<Car> car_ownership) {
    car_ownership->drive();   // 朋友使用车
    // 函数结束，car_ownership 析构，Car 对象被销毁
}

void demo_unique_ptr() {
    auto my_car = std::make_unique<Car>("Tesla");
    my_car->drive();

    // sell_car_to_friend(my_car);  // 编译错误！unique_ptr 不可拷贝
    sell_car_to_friend(std::move(my_car));  // 必须显式移动（过户）

    if (!my_car) {
        std::cout << "车已经不是我的了\n";  // my_car 现在是 nullptr
    }
}
```

**为什么 `unique_ptr` 不可拷贝？** 因为拷贝意味着两个指针同时拥有同一对象的所有权，离开作用域时会 double free。禁止拷贝从根源上消除了这类错误。

#### 3.2.2 unique_ptr 与 RAII

```cpp
// 文件：modules/smart-pointers/main1.cpp
class MyObject {
public:
    MyObject() { std::cout << "MyObject 诞生\n"; }
    ~MyObject() { std::cout << "MyObject 死亡\n"; }
};

// 正确：unique_ptr 在栈上，出作用域自动析构
void stack_ptr_via_make_unique() {
    auto p2 = std::make_unique<MyObject>();
    p2->greet();
    // 函数结束，p2 析构 → MyObject 析构
}

// 错误：unique_ptr 在堆上，破坏了 RAII
void heap_ptr_breaks_raii() {
    auto p3 = new std::unique_ptr<MyObject>{new MyObject{}};
    // p3 是原始指针，指向堆上的 unique_ptr
    // 如果忘记 delete p3，MyObject 和 unique_ptr 都会泄漏
}
```

**核心原则**：智能指针本身应该在栈上（或作为对象的成员），而不是在堆上。否则就违背了 RAII 的初衷。

#### 3.2.3 shared_ptr：公交车的共享机制

**物理类比**：`shared_ptr` 就像公交车——多个人可以同时"持有"它（引用计数），最后一个人下车时，公交车回总站（对象被销毁）。

```cpp
// 文件：modules/smart-pointers/main3.cpp
class Bus { /* ... */ };

void demo_shared_ptr() {
    auto dispatch_center = std::make_shared<Bus>();     // 引用计数 = 1
    std::cout << dispatch_center.use_count() << "\n";   // 1

    std::vector<std::shared_ptr<Bus>> passengers;
    passengers.push_back(dispatch_center);  // 拷贝，计数 +1 → 2
    passengers.push_back(dispatch_center);  // 拷贝，计数 +1 → 3

    std::shared_ptr<Bus> late_passenger = dispatch_center;  // 计数 → 4

    passengers.pop_back();       // 计数 -1 → 3
    late_passenger = nullptr;    // 计数 -1 → 2
    passengers.pop_back();       // 计数 -1 → 1

    // dispatch_center 仍持有，计数为 1，Bus 对象仍活着
}
```

**引用计数的工作原理**：`shared_ptr` 内部维护两个指针——一个指向对象，一个指向控制块（包含引用计数和弱引用计数）。每次拷贝 `shared_ptr` 时计数 +1，每次析构时 -1，计数归零时销毁对象。

#### 3.2.4 weak_ptr：代客泊车的凭证

**物理类比**：`weak_ptr` 就像代客泊车凭证——它不拥有车，但可以凭凭证去取车。如果车已经被取走了（`shared_ptr` 被销毁），凭证就失效了。

```cpp
// 文件：modules/smart-pointers/main4.cpp
class Car { /* ... */ };

class CarOwner {
    std::weak_ptr<Car> valet_ticket;  // 凭证，不增加引用计数
public:
    void retrieveCar() const {
        if (auto car = valet_ticket.lock()) {  // 尝试提升为 shared_ptr
            car->drive();  // 凭证有效，取车成功
        } else {
            std::cout << "凭证已失效！\n";  // 车已不在服务中
        }
    }
};
```

**`lock()` 的意义**：`weak_ptr::lock()` 尝试将弱引用提升为 `shared_ptr`。如果对象已被销毁，返回空的 `shared_ptr`。这是检查对象是否还活着的安全方式。

#### 3.2.5 循环引用与 weak_ptr 的解法

```cpp
// 文件：modules/smart-pointers/main5.cpp
struct Node {
    std::shared_ptr<Node> partner;  // 强引用：互相持有 → 循环引用
};

void demonstrate_problem() {
    auto nodeA = std::make_shared<Node>("A");  // A 计数 = 1
    auto nodeB = std::make_shared<Node>("B");  // B 计数 = 1

    nodeA->partner = nodeB;  // B 计数 = 2
    nodeB->partner = nodeA;  // A 计数 = 2
}
// 离开作用域：A 计数 2→1，B 计数 2→1，都不归零 → 内存泄漏！
```

**解法**：将其中一个改为 `weak_ptr`：

```cpp
// 文件：modules/smart-pointers/main6.cpp
struct GoodNode {
    std::shared_ptr<GoodNode> next;  // 强引用：下一个节点
    std::weak_ptr<GoodNode> prev;    // 弱引用：上一个节点
};

// A->next = B (B 计数+1), B->prev = A (A 计数不变！)
// 离开作用域：A 计数 1→0 析构，B 计数 1→0 析构 → 正确释放
```

**通用原则**：在双向数据结构（双向链表、树形结构的父子引用）中，"拥有"方向用 `shared_ptr`，"被拥有"方向用 `weak_ptr`。

#### 3.2.6 在类内部返回自身的 shared_ptr：enable_shared_from_this

一个常见的需求：在类的成员函数中返回指向自身的 `shared_ptr`。**千万不要写 `shared_ptr(this)`！** 这会创建一个全新的控制块，导致同一对象被两个独立的引用计数管理，最终**双重释放**。

```cpp
// ❌ 致命错误：双重控制块，双重释放！
class Bad {
    std::shared_ptr<Bad> get_shared() {
        return std::shared_ptr<Bad>(this);  // 新建控制块！
    }
};
auto p = std::make_shared<Bad>();
auto q = p->get_shared();  // p 和 q 各自认为自己是唯一的拥有者
// 离开作用域 → double free 崩溃
```

**正确做法**：继承 `std::enable_shared_from_this<T>`，调用 `shared_from_this()`：

```cpp
// ✅ 正确：共享同一个控制块
class Good : public std::enable_shared_from_this<Good> {
public:
    std::shared_ptr<Good> get_shared() {
        return shared_from_this();  // 返回与当前持有者共享控制块的 shared_ptr
    }
};
auto p = std::make_shared<Good>();
auto q = p->get_shared();  // p 和 q 共享同一个控制块，引用计数 = 2
// 安全！
```

> `shared_from_this()` 内部依赖 `weak_ptr` 存储控制块的弱引用——这也是 `weak_ptr` 除解决循环引用外的另一大用武之地。**前提**：调用 `shared_from_this()` 时，对象必须已被至少一个 `shared_ptr` 管理，否则会抛出 `std::bad_weak_ptr` 异常。

#### 3.2.7 举一反三：智能指针选择指南

| 场景 | 选择 | 原因 |
|------|------|------|
| 独占所有权 | `unique_ptr` | 零开销，最安全 |
| 共享所有权 | `shared_ptr` | 引用计数自动管理 |
| 观察者/非拥有引用 | `weak_ptr` | 不影响生命周期 |
| 多态容器 | `unique_ptr<Base>` | 配合移动语义 |
| 需要自定义删除器 | `unique_ptr<T, Deleter>` | 如文件句柄、C API 资源 |

---

### 3.3 构建类型：Debug 与 Release 的底层差异

#### 3.3.1 核心编译选项

| 选项 | Debug | Release | 作用 |
|------|-------|---------|------|
| `-O0` vs `-O3` | `-O0` | `-O3` | 优化级别 |
| `-g` | 有 | 无 | 调试信息 |
| `NDEBUG` | 未定义 | 已定义 | 控制 `assert` |
| `-march=native` | 通常不用 | 常用 | 针对 CPU 指令集优化 |

#### 3.3.2 性能差异的实测

```cpp
// 文件：modules/build-type/matrix_bench.cpp
// 使用 Eigen 库进行矩阵 LLT 分解基准测试
static void BM_MatrixDecomposition(benchmark::State& state) {
    const int N = state.range(0);
    Eigen::MatrixXd SPD = /* ... 生成正定矩阵 ... */;

    for (auto _ : state) {
        Eigen::LLT<Eigen::MatrixXd> lltOfA(SPD);  // Cholesky 分解
        benchmark::DoNotOptimize(lltOfA.matrixLLT().data());
    }
}
BENCHMARK(BM_MatrixDecomposition)->Arg(500)->Arg(1000)->Arg(2000);
```

对应的 CMake 配置展现了 Debug 与 Release 的关键差异：

```cmake
# Debug 版本：无优化，有调试信息
add_executable(matrix_bench_debug matrix_bench.cpp)
target_compile_options(matrix_bench_debug PRIVATE -O0 -g -UNDEBUG)

# Release 版本：最高优化，无调试信息
add_executable(matrix_bench_release matrix_bench.cpp)
target_compile_options(matrix_bench_release PRIVATE -O3 -march=native)
target_compile_definitions(matrix_bench_release PRIVATE NDEBUG)
```

**典型结果**：Release 版本的矩阵分解速度可能是 Debug 的 10 倍以上。

#### 3.3.3 工程构建 Profile

```cmake
# 文件：modules/build-type/CMakeLists.txt

# Profile：适度优化 + 调试信息（性能分析用）
add_executable(matrix_profiles_profile ...)
target_compile_options(... PRIVATE -O2 -g -march=native)
target_compile_definitions(... PRIVATE NDEBUG BUILD_PROFILE_NAME="Profile")

# FastRelease：最高优化（生产环境）
add_executable(matrix_profiles_fast ...)
target_compile_options(... PRIVATE -O3 -march=native)
target_compile_definitions(... PRIVATE NDEBUG BUILD_PROFILE_NAME="FastRelease")

# MinSizeRel：最小体积（嵌入式/移动端）
add_executable(matrix_profiles_size ...)
target_compile_options(... PRIVATE -Os)
target_compile_definitions(... PRIVATE NDEBUG BUILD_PROFILE_NAME="MinSizeRelCustom")
```

| Profile | 优化 | 调试 | 适用场景 |
|---------|------|------|----------|
| Debug | `-O0` | 有 | 开发调试 |
| Profile | `-O2 -g` | 有 | 性能分析 |
| Release | `-O3` | 无 | 生产部署 |
| MinSizeRel | `-Os` | 无 | 体积敏感场景 |

#### 3.3.4 举一反三：assert 与 NDEBUG

```cpp
#include <cassert>
void process(int* p) {
    assert(p != nullptr);  // Debug 下检查，Release 下被编译器移除
    *p = 42;
}
```

`assert` 在定义了 `NDEBUG` 后变为空操作。这是零开销设计的典范——开发期有安全网，发布期零开销。

> **⚠️ 工程铁律：不要在头文件中用 `NDEBUG` 改变类的内存布局**。如果你的类定义中有 `#ifdef NDEBUG` 改变了成员变量或虚函数的数量/顺序，会导致 Debug 和 Release 编译的 `.o` 文件具有不同的对象大小和虚函数表结构——**ABI 不兼容**。当混用不同构建模式编译的目标文件时，会出现难以排查的堆栈破坏、虚函数跳转错误。`assert` 只在 `.cpp` 源文件中使用，或仅用于不影响内存布局的逻辑检查。

---

## 第四阶段：进阶——可调用对象与命名空间

---

### 4.1 可调用对象：函数的超进化

#### 4.1.1 起点：普通函数

```cpp
// 文件：modules/callable-objects/main0.cpp
int freeFunc(int value) {
    int result = 0;
    // do sth
    return result;
}

int main() {
    freeFunc(1);
}
```

普通函数的问题：**没有状态**。每次调用的行为完全相同，无法携带上下文信息。

```cpp
// 文件：modules/callable-objects/main1.cpp
int check_and_count(int value) {
    int count = 0;              // 局部变量，每次调用都重置
    if (value % 2 == 0) count++;
    return count;               // 永远只能返回 0 或 1，无法累计
}
```

#### 4.1.2 C 风格回调：函数指针 + void* 上下文

```cpp
// 文件：modules/callable-objects/main3.cpp
using CallbackHandler = void(*)(int value, void* context);

void process_data(const std::vector<int>& data, CallbackHandler handler, void* context) {
    for (int value : data) {
        handler(value, context);  // 将上下文传给回调
    }
}

struct MyStatsContext {
    int sum = 0;
    int count_even = 0;
};

void specific_logic(int value, void* env_ptr) {
    auto* ctx = static_cast<MyStatsContext*>(env_ptr);  // 类型不安全的转换！
    ctx->sum += value;
    if (value % 2 == 0) ctx->count_even++;
}

int main() {
    MyStatsContext env;
    process_data(dataset, specific_logic, &env);  // 传递状态
}
```

**痛点**：`void*` 丧失了类型安全，每次都要手动转型。

#### 4.1.3 仿函数：带状态的函数对象

```cpp
// 文件：modules/callable-objects/main4.cpp
class MyStatsFunctor {
public:
    int sum = 0;           // 状态直接存储在对象中
    int count_even = 0;

    void operator()(int value) {   // 重载 operator()
        sum += value;
        if (value % 2 == 0) count_even++;
    }
};

void process_data(const std::vector<int>& data, MyStatsFunctor& handler) {
    for (int value : data) {
        handler(value);  // 像函数一样调用
    }
}

int main() {
    MyStatsFunctor stats_obj;
    process_data(dataset, stats_obj);
    std::cout << stats_obj.sum;  // 状态保留在对象中
}
```

仿函数解决了状态问题，但 `process_data` 的参数类型被写死为 `MyStatsFunctor&`，无法接受其他可调用对象。

#### 4.1.4 模板泛化：接受任意可调用对象

```cpp
// 文件：modules/callable-objects/main5.cpp
template <typename Handler>
void process_data(const std::vector<int>& data, Handler handler) {
    for (int value : data) {
        handler(value);
    }
}

// 现在可以传入仿函数
MyStatsFunctor stats_obj;
process_data(dataset, stats_obj);
```

模板使得 `process_data` 不再依赖具体的可调用类型。

#### 4.1.5 Lambda：内联的匿名函数对象

```cpp
// 文件：modules/callable-objects/main7.cpp
int sum = 0;
int count_even = 0;

auto lambda_logic = [&](int value) {   // [&] 按引用捕获所有外部变量
    sum += value;
    if (value % 2 == 0) count_even++;
};

process_data(dataset, lambda_logic);
```

> **⚠️ 悬空引用陷阱**：`[&]` 按引用捕获的变量必须在 Lambda 被调用时仍然存活。**永远不要将按引用捕获的 Lambda 传出当前函数！** 如果 Lambda 的生命周期可能超过局部变量（比如存储到全局容器、传递给异步任务、作为回调注册到长生命周期对象），必须改用值捕获 `[=]` 或配合 `shared_ptr` 管理变量生命周期，否则将引用到已销毁的栈内存，导致未定义行为。

**Lambda 的本质**：编译器为每个 lambda 生成一个匿名的仿函数类，`[&]` 对应构造函数中按引用存储的成员变量。

**内联写法**：

```cpp
// 文件：modules/callable-objects/main8.cpp
process_data(dataset, [&](int value) {
    sum += value;
    if (value % 2 == 0) count_even++;
});
```

#### 4.1.6 万能引用：完美转发可调用对象

```cpp
// 文件：modules/callable-objects/main9.cpp
template <typename Handler>
void process_data(const std::vector<int>& data, Handler&& handler) {
    // Handler&& 是万能引用，不是右值引用！
    // 当传入左值时，Handler 推导为 T&，Handler&& 折叠为 T&
    // 当传入右值时，Handler 推导为 T，Handler&& 就是 T&&
    for (int value : data) {
        handler(value);
    }
}

// 配合 mutable lambda（有内部计数器）
process_data(dataset, [&, count = 0](int value) mutable {
    count++;
    sum += value;
    if (value % 2 == 0) count_even++;
});
```

**`mutable` lambda**：默认 lambda 的 `operator()` 是 `const` 的，`mutable` 移除 const 限定，允许修改按值捕获的变量。

#### 4.1.7 仿函数的经典应用：自定义排序

```cpp
// 文件：modules/callable-objects/main2.cpp
struct Sorter {
    bool is_ascending;
    explicit Sorter(bool mode) : is_ascending(mode) {}

    bool operator()(int a, int b) const {
        return is_ascending ? a < b : a > b;
    }
};

int main() {
    std::vector<int> dataset = {10, 5, 8, 3, 12};
    std::sort(dataset.begin(), dataset.end(), Sorter(false));  // 降序
}
```

#### 4.1.8 举一反三：可调用对象的演进路线

```
普通函数（无状态）
  → 函数指针 + void*（有状态但类型不安全）
    → 仿函数（有状态且类型安全，但不通用）
      → 模板 + 仿函数（通用但有类型膨胀）
        → Lambda（内联、简洁、自动推导类型）
          → 万能引用 + Lambda（完美转发）
```

| 方式 | 状态 | 类型安全 | 内联性 | 通用性 |
|------|------|----------|--------|--------|
| 函数指针 | 无 | 弱 | 无 | 低 |
| 函数指针 + void* | 有 | 无 | 无 | 中 |
| 仿函数 | 有 | 有 | 可能 | 低 |
| Lambda | 有 | 有 | 高 | 高 |

---

### 4.2 命名空间：从名称冲突到版本控制

#### 4.2.1 三种使用方式

```cpp
// 文件：modules/namespaces/main3.cpp — 完全限定（最安全）
std::cout << "Hello, World!";

// 文件：modules/namespaces/main2.cpp — using 声明（推荐）
using std::cout;
cout << "Hello, World!";

// 文件：modules/namespaces/main1.cpp — using 指令（最方便但最危险）
using namespace std;
cout << "Hello, World!";
```

**最佳实践**：
- **头文件中**：永远使用完全限定名，避免污染包含该头文件的所有代码。
- **源文件中**：`using` 声明是可以接受的；`using namespace` 应限于函数内部的小范围。

#### 4.2.2 解决名称冲突

```cpp
// 文件：modules/namespaces/main5.cpp
namespace foo {
    constexpr int magic_number = 42;
}

namespace bar {
    constexpr float magic_number = 3.14;
}

int main() {
    std::cout << foo::magic_number;  // 42
    std::cout << bar::magic_number;  // 3.14
}
```

没有命名空间，两个 `magic_number` 就会冲突。有了命名空间，相同的名字可以在不同的上下文中和平共处。

#### 4.2.3 混合使用

```cpp
// 文件：modules/namespaces/main4.cpp
namespace S1 { void foo() {} void foo1() {} }
namespace S2 { void bar() {} }
namespace S3 { void baz() {} void baz1() {} }

int main() {
    S2::bar();             // 完全限定：偶尔用一次的函数

    using namespace S1;    // using 指令：频繁使用整个命名空间
    foo();
    foo1();

    using S3::baz;         // using 声明：频繁使用特定函数
    baz();
}
```

#### 4.2.4 inline namespace：版本控制的利器

```cpp
// 文件：modules/namespaces/lib_v1/my_math.h
namespace MyLib {
    inline namespace v1 {           // inline：v1 是 MyLib 的默认版本
        int add(int a, int b);
    }
}
```

```cpp
// 文件：modules/namespaces/app_v1/main.cpp
int result = MyLib::add(10, 5);  // 无需写 MyLib::v1::add
```

当库升级到 v2：

```cpp
// 文件：modules/namespaces/lib_v2/my_math.h
namespace MyLib {
    namespace v1 {                 // v1 不再是 inline
        int add(int a, int b);
    }

    inline namespace v2 {          // v2 成为新的默认版本
        double add(double a, double b);
    }
}
```

```cpp
// 文件：modules/namespaces/app_v2/main.cpp
double result_v2 = MyLib::add(10.5, 5.5);  // 调用 v2（默认）
int result_v1 = MyLib::v1::add(10, 5);     // 显式调用旧版本
```

**`inline namespace` 的精妙之处**：
- 对现有代码：`MyLib::add(10, 5)` 无需修改，自动路由到新的默认版本。
- 对旧代码：显式写 `MyLib::v1::add` 即可继续使用旧版本。
- 这就是**ABI 兼容的版本控制**——不需要重新编译旧代码就能享受新版本。

#### 4.2.5 举一反三：命名空间与链接的关系

结合 2.1 节的动态库知识：`MyLib` 的 v1 和 v2 分别编译为两个 `.so` 文件。`app_v1` 链接 v1 的 `.so`，`app_v2` 链接 v2 的 `.so`。当 v2 发布后，旧应用仍运行在 v1 上，新应用自动使用 v2——这就是**动态库 + 命名空间**的协同设计。

---

## 总结：知识的骨架

回顾我们的学习路径：

```
第一阶段（筑基）
├── 顺时针螺旋法则 → 解读复杂声明
├── 内存分段       → 理解程序的物理布局
└── 移动语义       → 从深拷贝到资源窃取

第二阶段（工程）
├── 静态/动态库    → 编译全生命周期与工程权衡
└── 面向对象       → 封装→继承多态→五之法则→零之法则

第三阶段（抽象）
├── 类型别名       → 驯服复杂声明，跨平台抽象
├── 智能指针       → RAII 自动资源管理
└── 构建类型       → Debug/Release 的底层差异

第四阶段（进阶）
├── 可调用对象     → 函数→仿函数→Lambda→万能引用
└── 命名空间       → 名称冲突→版本控制→ABI 兼容
```

每一个知识点都不是孤立的——

- 不理解**内存分段**，就无法理解为什么移动语义比拷贝快。
- 不理解**移动语义**，就无法理解 `unique_ptr` 为什么不可拷贝。
- 不理解**五之法则**，就无法体会**零之法则**为何是终极追求。
- 不理解**类型别名**，就无法驯服回调函数的复杂声明。
- 不理解**动态库**，就无法理解 `inline namespace` 的版本控制价值。

这些知识的枝叶，自然依附于骨架之上，成为逻辑的必然——这正是 C++ 心智模型的意义。
