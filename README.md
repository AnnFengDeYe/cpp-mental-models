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

- **Minimalist Physical Models** Every code example is meticulously crafted to strip away syntactic noise, grounding abstract programming concepts in intuitive, real-world analogies rather than overwhelming technical details.

- **Intuitive Mental Analogies**
  - **Smart Pointers**: `unique_ptr` is likened to a **"private car"** (exclusive ownership), while `shared_ptr` mirrors a **"public bus"** (shared access/mechanism).
  - **Move Semantics**: Visualizes resource transfer as the direct **"relocation"** of image pixels, avoiding the high cost of traditional deep copying.
  - Discover more insightful analogies in the accompanying video series.

- **The Philosophy of Software Engineering** Technical choices are analyzed through an engineering lens. For instance, static linking is a strategy prioritizing deployment isolation (reliability), whereas dynamic linking acts as a trade-off favoring maintenance flexibility (extensibility).

By leveraging these minimalist physical scenarios and code examples, this project aims to help learners construct a solid C/C++ system framework and grasp the essential design philosophy of the language.

## 📚 Contents

### C/C++ Series

| Topic | Description | Prerequisites | YouTube | Bilibili |
|-------|-------------|---------------|---------|----------|
| **C_ClockwiseSpiral** | Quick method for parsing complex variable declarations. The Clockwise Spiral Rule is an improved version of the Right-Left Rule | None | [Link](https://www.youtube.com/watch?v=Y4643z08jeM) | [Link](https://www.bilibili.com/video/BV1jKhYzjEgE) |
| **C_MemorySegmentation** | Introduction to C++ memory layout and memory segmentation | None | [Link](https://www.youtube.com/watch?v=rUAGJAhmpDg) | [Link](https://www.bilibili.com/video/BV1Sepyz7ECL) |
| **MoveSemantic** | Introduction to lvalues, rvalues, and move semantics in C++ | None | [Link](https://www.youtube.com/watch?v=ywFJ-17n_sY) | [Link](https://www.bilibili.com/video/BV17ce7zLEzu) |
| **DynamicStaticLib** | Complete lifecycle of C/C++ programs from compilation to runtime | C_MemorySegmentation | [Link](https://www.youtube.com/watch?v=Xm-feSXlLVk) | [Link](https://www.bilibili.com/video/BV1Bw1qB1EwU) |
| **CppTypeAlias** | Introduction to type aliases in C++ | C_C++_ClockwiseSpiral, DynamicStaticLib | [Link](https://www.youtube.com/watch?v=ezqmozV3p0M) | [Link](https://www.bilibili.com/video/BV1VWqvB5ELX) |
| **Cpp_SmartPtrs** | Introduction to C++ smart pointers | C_MemorySegmentation, MoveSemantic | [Link](https://www.youtube.com/watch?v=l1RRedJbk5k) | [Link](https://www.bilibili.com/video/BV1ajWyzXEpj) |
| **CppCallable** | Evolution of callables: from C callbacks and functors to functional programming and universal references | MoveSemantic, CppTypeAlias, DynamicStaticLib | [Link](https://www.youtube.com/watch?v=K2QZncoUdLk) | [Link](https://www.bilibili.com/video/BV1F8zNB1EZk) |
| **Cpp_namespace** | Introduction to C++ namespaces | DynamicStaticLib | [Link](https://www.youtube.com/watch?v=n8uNKJSTyQc) | [Link](https://www.bilibili.com/video/BV1NTUpBoE59) |

---

## 📖 Learning Path

For optimal learning experience, follow this suggested order:

1. C_C++_ClockwiseSpiral / C_MemorySegmentation / MoveSemantic (can learn in any order)
2. DynamicStaticLib
3. CppTypeAlias / Cpp_SmartPtrs (can learn in any order)
4. CppCallable / Cpp_namespace (can learn in any order)

## ⭐ Star History

[![Star History Chart](https://api.star-history.com/svg?repos=AnnFengDeYe/Cpp-Mental-Models&type=Date)](https://star-history.com/#AnnFengDeYe/Cpp-Mental-Models&Date)

## 🤝 Contributing

Feel free to star ⭐ this repository if you find it helpful!

## 📧 Contact

If you have any questions or suggestions, please leave a comment on my YouTube or Bilibili videos.
