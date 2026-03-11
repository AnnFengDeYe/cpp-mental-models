# Cpp-Mental-Models

[中文版](README_CN.md) | English

This repository contains code examples from my YouTube and Bilibili coding knowledge sharing videos.

## 🔗 Links

- **YouTube**: [安枫的叶](https://www.youtube.com/@%E5%AE%89%E6%9E%AB%E7%9A%84%E5%8F%B6)
- **Bilibili**: [安枫的叶](https://b23.tv/DglKNYp)

## 💡 Design Philosophy

The Tao of C++ lies not in accumulation, but in integration.

Faced with the vast ocean of C++ syntax, fragmented learning often leads one astray. This is especially true in the era of ubiquitous AI-assisted programming, where rote memorization of syntax no longer builds a competitive moat.

This series is dedicated to a deep synthesis of the C/C++ core, rejecting any artificial separation of the two or immersion in the superficial allure of Modern C++ syntax.

This repository aims to assist learners in constructing a robust mental framework. With this foundation, obscure syntactic details cease to be items for rote memorization; instead, they become logical necessities, sprouting naturally like leaves from a solid trunk.

**Core Features**

- **Minimalist Physical Models**: Every code example is meticulously crafted to strip away syntactic noise. The goal is to anchor abstract programming concepts in the most intuitive real-world physical analogies, rather than merely piling up technical details.
- **Software Engineering Philosophy**: Examining technical choices through an engineering lens.
  - **Architecture Design**: Adopting an industry-standard global CMake build system to achieve perfect isolation between source code and build artifacts, cultivating standard engineering intuition.
  - **Architectural Trade-offs**: Exploring the balance between the "deployment isolation (reliability)" pursued by static linking and the "maintenance flexibility (extensibility)" gained through dynamic linking.
  - *More to come...*
- **Intuitive Mental Analogies**:
  - **Smart Pointers**: Interpreting the exclusive ownership of `unique_ptr` as a "private car", and mapping the shared mechanism of `shared_ptr` to a "public bus".
  - **Move Semantics**: Visualizing resource transfer as the direct physical "relocation" of image pixels, avoiding the high cost of traditional deep copying.
  - **Deconstructing OOP**: From the contractual privileges of classes and polymorphic inheritance to the underlying mechanisms of virtual function tables (vtable), ultimately reshaping the boundaries of modern C++ resource management through the evolution from the "Rule of Five" to the "Rule of Zero".
  - *More to come...*

Through these minimalist physical scenarios and code examples, this project aims to help more learners construct a solid C/C++ system framework and grasp its core design philosophy.

## 📚 Contents

### C/C++ Series

| Topic | Description | Prerequisites | YouTube | Bilibili |
|-------|-------------|---------------|---------|----------|
| **C_ClockwiseSpiral** | Quick method for parsing complex variable declarations. The Clockwise Spiral Rule is an improved version of the Right-Left Rule | None | [Link](https://www.youtube.com/watch?v=Y4643z08jeM) | [Link](https://www.bilibili.com/video/BV1jKhYzjEgE) |
| **C_MemorySegmentation** | Introduction to C++ memory layout and memory segmentation | None | [Link](https://www.youtube.com/watch?v=rUAGJAhmpDg) | [Link](https://www.bilibili.com/video/BV1Sepyz7ECL) |
| **MoveSemantic** | Introduction to lvalues, rvalues, and move semantics in C++ | None | [Link](https://www.youtube.com/watch?v=ywFJ-17n_sY) | [Link](https://www.bilibili.com/video/BV17ce7zLEzu) |
| **DynamicStaticLib** | Complete lifecycle of C/C++ programs from compilation to runtime | C_MemorySegmentation | [Link](https://www.youtube.com/watch?v=Xm-feSXlLVk) | [Link](https://www.bilibili.com/video/BV1Bw1qB1EwU) |
| **Cpp_OOP** | Class contracts and behaviors, inheritance and polymorphism, virtual function tables, and the Rule of Zero/Five | C_MemorySegmentation, MoveSemantic | [Link]() | [Link]() |
| **CppTypeAlias** | Introduction to type aliases in C++ | C_ClockwiseSpiral, DynamicStaticLib | [Link](https://www.youtube.com/watch?v=ezqmozV3p0M) | [Link](https://www.bilibili.com/video/BV1VWqvB5ELX) |
| **Cpp_SmartPtrs** | Introduction to C++ smart pointers | C_MemorySegmentation, MoveSemantic | [Link](https://www.youtube.com/watch?v=l1RRedJbk5k) | [Link](https://www.bilibili.com/video/BV1ajWyzXEpj) |
| **CppCallable** | Evolution of callables: from C callbacks and functors to functional programming and universal references | MoveSemantic, CppTypeAlias, DynamicStaticLib | [Link](https://www.youtube.com/watch?v=K2QZncoUdLk) | [Link](https://www.bilibili.com/video/BV1F8zNB1EZk) |
| **Cpp_namespace** | Introduction to C++ namespaces | DynamicStaticLib | [Link](https://www.youtube.com/watch?v=n8uNKJSTyQc) | [Link](https://www.bilibili.com/video/BV1NTUpBoE59) |

---

## 📖 Learning Path

For optimal learning experience, follow this suggested order:

1. C_ClockwiseSpiral / C_MemorySegmentation / MoveSemantic (can learn in any order)
2. DynamicStaticLib / Cpp_OOP (can learn in any order)
3. CppTypeAlias / Cpp_SmartPtrs (can learn in any order)
4. CppCallable / Cpp_namespace (can learn in any order)

## 🏗️ Project Structure 

This project uses a global CMake architecture, cleanly separating source code from build artifacts:

```shell
Cpp-Mental-Models/
├── CMakeLists.txt       # Global CMake config (Centralized C++ standards & output paths)
├── modules/             # Source code: Independent C++ topics aligned with video tutorials
│   ├── Cpp_OOP/
│   ├── MoveSemantic/
│   └── ...
├── bin/                 # 📦 Generated after build: Unified output for all executables (Git ignored)
└── lib/                 # 📦 Generated after build: Unified output for all libraries (Git ignored)
```

## 🚀 Quick Start

**Prerequisites:** CMake 3.15+ and a C++20 compatible compiler.

### Option 1: IDE (Highly Recommended)

We recommend using **CLion** or **VSCode** (with the CMake Tools extension).

1. Open the project **root directory** (`Cpp-Mental-Models`) directly in your IDE.
2. Allow the IDE to automatically parse the global `CMakeLists.txt`.
3. Select your desired target from the run/build dropdown menu (e.g., `Cpp_OOP_demo1`) and click Run.

> **💡 Pro Tip**: Always run the code via the generated CMake Targets! Avoid using "single-file run" shortcuts next to the `main()` function, as they will bypass standard CMake linkage and cause `Undefined symbols` errors.


### Option 2: Command Line 

```shell
# 1. Generate build system (This will automatically create bin/ and lib/ dirs)
cmake -B build

# 2. Build all modules
cmake --build build

# 3. Run the specific executable
./bin/Cpp_OOP_demo1_inheritance_polymorphism
```



## ⭐ Star History

[![Star History Chart](https://api.star-history.com/svg?repos=AnnFengDeYe/Cpp-Mental-Models&type=Date)](https://star-history.com/#AnnFengDeYe/Cpp-Mental-Models&Date)

## 🤝 Contributing

Feel free to star ⭐ this repository if you find it helpful!

## 📧 Contact

If you have any questions or suggestions, please leave a comment on my YouTube or Bilibili videos.
