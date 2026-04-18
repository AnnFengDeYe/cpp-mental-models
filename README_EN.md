# Cpp-Mental-Models

[中文版](README.md) | English

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
  - *For deeper architectural insights and engineering trade-offs, check out the companion videos...*
- **Intuitive Mental Analogies**:
  - **Smart Pointers**: Interpreting the exclusive ownership of `unique_ptr` as a "private car", and mapping the shared mechanism of `shared_ptr` to a "public bus".
  - **Move Semantics**: Visualizing resource transfer as the direct physical "relocation" of image pixels, avoiding the high cost of traditional deep copying.
  - **Deconstructing OOP**: From the contractual privileges of classes and polymorphic inheritance to the underlying mechanisms of virtual function tables (vtable), ultimately reshaping the boundaries of modern C++ resource management through the evolution from the "Rule of Five" to the "Rule of Zero".
  - *For more intuitive analogies and source-level deep dives, check out the companion videos....*

  Through these minimalist physical scenarios and code examples, this project aims to help more learners construct a solid C/C++ system framework and grasp its core design philosophy.

## 📚 Contents

### C/C++ Series

| Topic | Description | Prerequisites | YouTube | Bilibili |
|:-----:|:-----------:|:-------------:|:-------:|:--------:|
| **clockwise-spiral** | Quick method for parsing complex variable declarations. The Clockwise Spiral Rule is an improved version of the Right-Left Rule | None | [Link](https://www.youtube.com/watch?v=Y4643z08jeM) | [Link](https://www.bilibili.com/video/BV1jKhYzjEgE) |
| **memory-segmentation** | Introduction to C++ memory layout and memory segmentation | None | [Link](https://www.youtube.com/watch?v=rUAGJAhmpDg) | [Link](https://www.bilibili.com/video/BV1Sepyz7ECL) |
| **move-semantics** | Introduction to lvalues, rvalues, and move semantics in C++ | None | [Link](https://www.youtube.com/watch?v=ywFJ-17n_sY) | [Link](https://www.bilibili.com/video/BV17ce7zLEzu) |
| **dynamic-static-libs** | Complete lifecycle of C/C++ programs from compilation to runtime | memory-segmentation | [Link](https://www.youtube.com/watch?v=Xm-feSXlLVk) | [Link](https://www.bilibili.com/video/BV1Bw1qB1EwU) |
| **oop** | Class contracts and behaviors, inheritance and polymorphism, virtual function tables, and the Rule of Zero/Five | memory-segmentation, move-semantics | [Link]() | [Link]() |
| **type-aliases** | Introduction to type aliases in C++ | clockwise-spiral, dynamic-static-libs | [Link](https://www.youtube.com/watch?v=ezqmozV3p0M) | [Link](https://www.bilibili.com/video/BV1VWqvB5ELX) |
| **smart-pointers** | Introduction to C++ smart pointers | memory-segmentation, move-semantics | [Link](https://www.youtube.com/watch?v=l1RRedJbk5k) | [Link](https://www.bilibili.com/video/BV1ajWyzXEpj) |
| **callable-objects** | Evolution of callables: from C callbacks and functors to functional programming and universal references | move-semantics, type-aliases, dynamic-static-libs | [Link](https://www.youtube.com/watch?v=K2QZncoUdLk) | [Link](https://www.bilibili.com/video/BV1F8zNB1EZk) |
| **namespaces** | Introduction to C++ namespaces | dynamic-static-libs | [Link](https://www.youtube.com/watch?v=n8uNKJSTyQc) | [Link](https://www.bilibili.com/video/BV1NTUpBoE59) |

---

## 📖 Learning Path

For optimal learning experience, follow this suggested order:

1. clockwise-spiral / memory-segmentation / move-semantics (can learn in any order)
2. dynamic-static-libs / oop (can learn in any order)
3. type-aliases / smart-pointers (can learn in any order)
4. callable-objects / namespaces (can learn in any order)

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

It is recommended to use **CLion** or **VS Code** (with the CMake Tools extension).

1. Open the project **root directory** Cpp-Mental-Models using your IDE.
2. The IDE will automatically detect and parse the **CMakeLists.txt** file in the root directory (If not triggered automatically, please manually reload the CMake project).
3. Wait until the CMake parsing is completely finished. You can then open the source code of each module and directly click the green run button next to the main function to see the execution results. Alternatively, you can select a specific target with the module prefix (e.g., Cpp_OOP_demo1) from the Run/Debug Target drop-down menu and click Run.

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

 <picture>
   <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/chart?repos=AnnFengDeYe/cpp-mental-models&type=date&theme=dark&legend=top-left" />
   <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/chart?repos=AnnFengDeYe/cpp-mental-models&type=date&legend=top-left" />
   <img alt="Star History Chart" src="https://api.star-history.com/chart?repos=AnnFengDeYe/cpp-mental-models&type=date&legend=top-left" />
 </picture>


## 🤝 Contributing

Feel free to star ⭐ this repository if you find it helpful!

## 📧 Contact

If you have any questions or suggestions, please leave a comment on my YouTube or Bilibili videos.
