# Mini Shell in C++ 

A simple **Unix-like command-line shell** implemented in **C++** using the Standard Library and `std::filesystem`.  
This project demonstrates core concepts of **command parsing, file system handling, and shell design**.

## Features
- Interactive shell prompt
- Built-in commands:
  - `help` – Show available commands
  - `pwd` – Print current working directory
  - `cd <dir>` – Change directory
  - `ls [dir]` – List files and directories
  - `cat <file>` – Display file contents
  - `echo <text>` – Print text to console
  - `history` – Show command history
  - `exit` – Exit the shell
- Uses **C++17 `std::filesystem`**
- Handles relative and absolute paths
- Error handling for invalid files/directories
- Command history tracking

## 🛠️ Technologies Used
- **Language:** C++ (C++17)
- **Libraries:**
  - `<iostream>`
  - `<vector>`
  - `<string>`
  - `<algorithm>`
  - `<filesystem>`
  - `<fstream>`

## ## 📂 Project Structure
├── main.cpp
├── README.md
## 🚀 How to Build & Run
### 🔧 Requirements
- GCC / Clang with **C++17 support**
- Linux, macOS, or Windows (MinGW / MSVC)

### 🧱 Compile

g++ -std=c++17 main.cpp -o minishell 

## Usage Examples
test $ : pwd
/home/user/projects

test $ : ls
[DIR] src
      main.cpp

test $ : cd src
Directory changed to: /home/user/projects/src

test $ : cat main.cpp
#include <iostream>
...

test $ : history
1 pwd
2 ls
3 cd src
4 cat main.cpp

## 🧠 Learning Outcomes
-Understanding how shells work internally
-Working with files and directories in C++
-Command parsing and dispatching
-Error handling using modern C++
-Writing modular, readable code

## 👤 Author
Gaurav Patel
Embedded Software Engineer | C++ | Systems Programming

## 📜 License
This project is open-source and free to use for learning and experimentation.
---

If you want, I can also:
- Add **badges (C++17, platform, license)**  
- Rewrite this as a **resume-optimized project description**
- Convert it into an **OOP-based shell**  

Just say the word 🔥