# STL Container Inspector

A C++ benchmarking project that analyzes the behavior of major STL containers in terms of:

- ⏱️ Execution time (insert, find, erase)
- 📦 Memory allocations (custom counting allocator)
- 🔁 Iterator invalidation rules

Containers tested:

- `std::vector`
- `std::deque`
- `std::list`
- `std::unordered_map`

---

## 📌 Features

✔ Measures performance using `std::chrono`  
✔ Tracks allocations and deallocations with a custom allocator  
✔ Uses identical workloads for fair comparison  
✔ Demonstrates iterator invalidation behavior  
✔ Clean modular structure (headers + source)

---

## 📂 Project Structure

STL-Container-Inspector/
├─ include/
│ ├─ counting_allocator.h
│ ├─ timer.h
│ ├─ keys.h
│ └─ iterator_rules.h
├─ src/
│ └─ main.cpp
├─ CMakeLists.txt
└─ README.md


---

## ⚙️ Build & Run

### Option 1 — g++

```bash
g++ -std=c++20 -O2 -Iinclude src/main.cpp -o stl_inspector
./stl_inspector
Option 2 — CMake
cmake -S . -B build
cmake --build build -j
./build/stl_inspector

```

🧪 Benchmarked Operations
For each container:

Insert
Sequential insertion of N elements

Find
Linear search (std::find) for vector/deque/list

Hash lookup for unordered_map

Erase
Range erase for vector/deque/list

Key erase for unordered_map

All tests use the same generated key set for consistency.

📊 Allocation Tracking
A custom allocator counts:

Number of allocations

Number of deallocations

Total allocated bytes

This highlights:

vector → few large allocations

list → one allocation per element

unordered_map → bucket + node allocations

🔁 Iterator Invalidation Summary
vector
Reallocation invalidates all iterators, references, pointers

erase invalidates iterators from erased position to end

deque
insert/erase may invalidate iterators (implementation dependent)

list
insert does NOT invalidate iterators

erase invalidates only erased elements

unordered_map
rehash invalidates all iterators

erase invalidates only erased element

📈 What You Learn From This Project
Why vector is fastest for contiguous data

Why list is slow despite O(1) erase

How memory layout affects performance

Real-world behavior of STL allocators

Iterator safety rules in practice

🚀 Possible Improvements
ASCII bar charts for timings

CSV/JSON export of results

More container types (set, map, flat_map)

Randomized erase workloads

Command-line parameters

🛠 Requirements
C++20 compatible compiler (GCC, Clang, MSVC)

CMake (optional)

📜 License
MIT License (feel free to use and modify)

⭐ Author
Built as a learning and performance exploration project for STL containers in C++.
