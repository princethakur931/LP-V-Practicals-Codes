# 🚀 C++ & CUDA Setup Guide on Linux

## 🔹 Update System

```bash
sudo apt update && sudo apt upgrade
```

---

# 💻 Install C++ Compiler

```bash
sudo apt install g++
```

Check version:

```bash
g++ --version
```

---

# ⚡ Install CUDA Toolkit

```bash
sudo apt install nvidia-cuda-toolkit
```

Check CUDA compiler:

```bash
nvcc --version
```

---

# 📂 File Extensions

| Language | Extension |
|----------|------------|
| C | `.c` |
| C++ | `.cpp` |
| CUDA | `.cu` |

---

# 🛠️ Compile & Run C++

## Compile

```bash
g++ program.cpp -o program
```

## Run

```bash
./program
```

---

# 🚀 Compile & Run CUDA

## Compile

```bash
nvcc program.cu -o program
```

## Run

```bash
./program
```

---

# 📝 Create File

## C++

```bash
nano program.cpp
```

## CUDA

```bash
nano program.cu
```

Save File:

```text
CTRL + O → ENTER → CTRL + X
```

---

# 🔥 Example C++ Code

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello C++";
    return 0;
}
```

---

# ⚡ Example CUDA Code

```cpp
#include <iostream>
#include <cuda_runtime.h>

__global__ void hello()
{
    printf("Hello CUDA");
}

int main()
{
    hello<<<1,1>>>();
    cudaDeviceSynchronize();
}
```

---

# ✅ Quick Summary

| Task | Command |
|------|----------|
| Install C++ | `sudo apt install g++` |
| Install CUDA | `sudo apt install nvidia-cuda-toolkit` |
| Compile C++ | `g++ file.cpp -o file` |
| Compile CUDA | `nvcc file.cu -o file` |
| Run Program | `./file` |
