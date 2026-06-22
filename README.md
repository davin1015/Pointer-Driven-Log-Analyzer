# Pointer-Driven Log Analyzer

A foundational systems programming project designed to explore low-level memory management, pointer manipulation, and data aggregation structures in modern **C++17**. 

Instead of relying on high-level abstractions, this implementation dives straight into C-style memory structures to understand the core mechanics of file I/O operations and tokenization.

## 🧠 Core Learning Objectives & Key Takeaways

### 1. Raw Pointer Arithmetic & Buffer Mutation
* **What I Learned:** How to manipulate standard strings at the byte level using memory addresses. 
* **Implementation Details:** Instead of invoking expensive string copy operations (which trigger memory manager overhead), I used a raw character pointer (`char* p`) to manually traverse the stream buffer. By injecting null-terminators (`\0`) directly at delimiter boundaries, I effectively tokenized sequential data segments without allocating any additional heap memory.

### 2. Stream Ingestion & I/O Bottlenecks
* **What I Learned:** Gained a deep understanding of data-stream processing patterns via `std::ifstream` and `std::getline`.
* **Implementation Details:** Learned how memory caching works under the hood by recycling a stack-allocated line buffer throughout the entire file lifecycle. This practice maximized CPU cache locality and protected the system against localized memory fragmentation during massive dataset parsing.

### 3. Associative Containers & Lookup Complexities
* **What I Learned:** The practical engineering trade-offs between sorted and unsorted associative data structures.
* **Implementation Details:** 
  * Leveraged `std::unordered_map` (Hash Map) for network asset metrics (IP tracking), utilizing its average $O(1)$ time complexity to maintain responsive ingestion speeds.
  * Integrated `std::map` (Red-Black Tree) for telemetry logging (HTTP Status Codes), utilizing its sorted structure ($O(\log N)$ insertion) to ensure the data is automatically organized sequentially for analysis output.

### 4. Cross-Paradigm Engineering (Python & C++)
* **What I Learned:** How to build an isolated, automated test pipeline by combining scripting and native programming languages.
* **Implementation Details:** Wrote a test data generation tool in **Python 3** to model synthetic, industry-standard server log topologies. This script served as the validation baseline for testing edge cases, empty rows, and malformed strings within the compiled **C++ native binary**.

## 📦 How to Compile and Run

```bash
python3 generate_logs.py

g++ -std=c++17 main.cpp -o log_parser

./log_parser
```
