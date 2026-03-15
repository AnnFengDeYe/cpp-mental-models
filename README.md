# Cpp-Mental-Models

中文版 | [English](README_EN.md)

本仓库包含我在 YouTube 和 Bilibili 上分享的代码知识相关的代码示例。

## 🔗 链接

- **YouTube**: [安枫的叶](https://www.youtube.com/@%E5%AE%89%E6%9E%AB%E7%9A%84%E5%8F%B6)
- **Bilibili**: [安枫的叶](https://b23.tv/DglKNYp)

## 💡 设计理念

C++ 之道，不在于多，而在于通。

面对浩瀚的 C++ 语法海洋，碎片化的学习往往让人迷失。尤其在 AI 辅助编程日益普及的今天，单纯记忆语法已无竞争壁垒。本系列教程致力于深度整合 C/C++ 核心体系，拒绝将二者割裂，同时也不沉迷于 Modern C++ 的语法表象。

本仓库希望帮助C/C++学习者构建起坚固的底层知识骨架，让那些生涩的语法细节，不再是死记硬背的条目，而是如枝叶般自然依附于骨架之上的逻辑必然。

🌟 **核心特色**

- **极简物理模型** 所有代码案例均经过精心打磨，剥离繁杂的语法噪音，旨在将抽象的编程概念锚定于最直观的现实物理类比之中，而非堆砌技术细节。
- **软件工程的哲学** 透过工程视角审视技术抉择。
  - **架构设计**：采用工业级全局 CMake 构建系统，实现源码与编译产物的完美隔离，培养规范的工程直觉。
  - **架构权衡**：探讨静态链接追求的“部署隔离性（可靠性）”与动态链接换取的“维护灵活性（扩展性）”之间的权衡之道。
  - 未完待续...

- **直观的思维类比**
  - **智能指针**： 以"私家车"诠释 `unique_ptr` 的独占所有权，以"公交车"映射 `shared_ptr` 的共享机制。
  - **移动语义**： 将资源转移具象化为图像像素的直接"搬运"，而非传统高昂的深拷贝。
  - **解构面向对象**：从类的契约特权、多态继承到虚函数表底层机制，并透过“五之法则”到“零之法则”的演进，重塑现代 C++ 资源管理边界。
  - 未完待续...

希望透过这些最简单的物理场景和代码案例，帮助更多人建立 C/C++ 扎实的系统框架和核心的设计哲学。

## 📚 目录

### C/C++ 系列

| 主题 | 简介 | 前置知识 | YouTube | Bilibili |
|------|------|----------|---------|----------|
| **C_ClockwiseSpiral** | 复杂变量声明的快速判断方法，顺时针螺旋法则是右左法则的改良版 | 无 | [链接](https://www.youtube.com/watch?v=Y4643z08jeM) | [链接](https://www.bilibili.com/video/BV1jKhYzjEgE) |
| **C_MemorySegmentation** | C++ 的内存布局或内存分段 | 无 | [链接](https://www.youtube.com/watch?v=rUAGJAhmpDg) | [链接](https://www.bilibili.com/video/BV1Sepyz7ECL) |
| **MoveSemantic** | C++ 的左值、右值和移动语义 | 无 | [链接](https://www.youtube.com/watch?v=ywFJ-17n_sY) | [链接](https://www.bilibili.com/video/BV17ce7zLEzu) |
| **DynamicStaticLib** | C/C++ 程序从编译到运行的全生命周期 | C_MemorySegmentation | [链接](https://www.youtube.com/watch?v=Xm-feSXlLVk) | [链接](https://www.bilibili.com/video/BV1Bw1qB1EwU) |
| **Cpp_OOP** | 类的契约与行为、继承与多态、虚函数表机制，以及零之法则/五之法则 | C_MemorySegmentation, MoveSemantic | [链接]() | [链接]() |
| **CppTypeAlias** | C++ 类型别名 | C_ClockwiseSpiral, DynamicStaticLib | [链接](https://www.youtube.com/watch?v=ezqmozV3p0M) | [链接](https://www.bilibili.com/video/BV1VWqvB5ELX) |
| **Cpp_SmartPtrs** | C++ 智能指针 | C_MemorySegmentation, MoveSemantic | [链接](https://www.youtube.com/watch?v=l1RRedJbk5k) | [链接](https://www.bilibili.com/video/BV1ajWyzXEpj) |
| **CppCallable** | 函数的超进化 从面向过程的回调、仿函数至函数式编程与万能引用的可调用对象全解析 | MoveSemantic, CppTypeAlias, DynamicStaticLib | [链接](https://www.youtube.com/watch?v=K2QZncoUdLk) | [链接](https://www.bilibili.com/video/BV1F8zNB1EZk) |
| **Cpp_namespace** | C++ 命名空间 | DynamicStaticLib | [链接](https://www.youtube.com/watch?v=n8uNKJSTyQc) | [链接](https://www.bilibili.com/video/BV1NTUpBoE59) |

---

## 📖 学习路径

为了获得最佳学习体验，建议按以下顺序学习：

1. C_ClockwiseSpiral / C_MemorySegmentation / MoveSemantic（可任意顺序）
2. DynamicStaticLib / Cpp_OOP （可任意顺序）
3. CppTypeAlias / Cpp_SmartPtrs（可任意顺序）
4. CppCallable / Cpp_namespace（可任意顺序）

## 🏗️ 项目结构

本项目采用全局 CMake 架构，以实现源码与编译产物的隔离：

```shell
Cpp-Mental-Models/
├── CMakeLists.txt       # 全局 CMake 配置（统一管控 C++ 标准与输出路径）
├── modules/             # 源码目录：按视频主题划分的独立 C++ 进阶代码
│   ├── Cpp_OOP/
│   ├── MoveSemantic/
│   └── ...
├── bin/                 # 📦 编译后自动生成：集中存放所有可执行文件 (Git 忽略)
└── lib/                 # 📦 编译后自动生成：集中存放所有动态/静态库 (Git 忽略)
```

## 🚀 快速开始

本项目要求 **CMake 3.15+** 及支持 **C++20** 的编译器。

### 方法一：IDE 一键运行（强烈推荐）

推荐使用 **CLion** 或 **VSCode** (配合 CMake Tools 插件)。

1. 使用 IDE 打开项目**根目录** `Cpp-Mental-Models`。
2. IDE 会自动识别并解析根目录下的 CMakeLists.txt 文件（若未自动触发，请手动重新加载 CMake 项目）。
3. 等待 CMake 解析彻底完成后，进入各个模块 (modules) 的源码，直接点击 main 函数旁边的绿色运行按钮，即可查看运行结果。或在运行目标 (Target) 下拉菜单中，选择带有模块前缀的特定目标（例如 `Cpp_OOP_demo1`），点击运行即可。

> **💡 避坑提示**：请务必通过 CMake 目标列表运行代码！切勿点击单个 `.cpp` 文件旁边的快捷运行按钮，以免脱离 CMake 架构导致链接失败（如 `Undefined symbols` 报错）。

### 方法二：命令行编译

```shell
# 1. 生成构建系统 (此时会自动创建 bin/ 和 lib/ 目录)
cmake -B build

# 2. 编译所有模块
cmake --build build

# 3. 运行指定的可执行文件
./bin/Cpp_OOP_demo1_inheritance_polymorphism
```



## ⭐ Star 走势

[![Star History Chart](https://api.star-history.com/svg?repos=AnnFengDeYe/Cpp-Mental-Models&type=Date)](https://star-history.com/#AnnFengDeYe/Cpp-Mental-Models&Date)

## 🤝 贡献

如果觉得有帮助，欢迎点个 star ⭐！

## 📧 联系方式

如有任何问题或建议，欢迎在我的 YouTube 或 Bilibili 视频下留言。
