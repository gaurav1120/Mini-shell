#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <cstdlib>

namespace fs = std::filesystem;
using namespace std;

/* ---------------- Utility ---------------- */

string trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos)
        return "";

    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, end - start + 1);
}

/* ---------------- Commands ---------------- */

void cmd_help()
{
    cout << "Available commands:\n";
    cout << "  help        - Show this help message\n";
    cout << "  pwd         - Print current working directory\n";
    cout << "  cd <dir>    - Change current directory\n";
    cout << "  ls <dir>    - List files in directory\n";
    cout << "  cat <file>  - Display file contents\n";
    cout << "  echo <text> - Print text\n";
    cout << "  history     - Show command history\n";
    cout << "  exit        - Exit the shell\n";
}

void cmd_pwd()
{
    cout << fs::current_path() << endl;
}

void cmd_cd(const string &args)
{
    fs::path target;

#ifdef _WIN32
    const char *home = getenv("USERPROFILE");
#else
    const char *home = getenv("HOME");
#endif

    if (args.empty())
        target = home ? fs::path(home) : fs::current_path();
    else
        target = fs::path(args);

    if (fs::exists(target) && fs::is_directory(target))
    {
        fs::current_path(target);
        cout << "Directory changed to: " << fs::current_path() << endl;
    }
    else
    {
        cerr << "Error: Directory does not exist: " << target << endl;
    }
}

void cmd_ls(const string &args)
{
    fs::path dir = args.empty() ? fs::current_path() : fs::path(args);
    dir = fs::absolute(dir);

    if (!fs::exists(dir))
    {
        cerr << "Error: Directory does not exist: " << dir << endl;
        return;
    }
    if (!fs::is_directory(dir))
    {
        cerr << "Error: Not a directory: " << dir << endl;
        return;
    }

    cout << "Contents of " << dir << ":\n";

    for (const auto &entry : fs::directory_iterator(dir))
    {
        cout << (fs::is_directory(entry) ? "[DIR] " : "      ")
             << entry.path().filename().string() << endl;
    }
}

void cmd_cat(const string &filename)
{
    if (filename.empty())
    {
        cerr << "Error: No file specified\n";
        return;
    }

    fs::path filepath = fs::absolute(filename);

    if (!fs::exists(filepath))
    {
        cerr << "Error: File does not exist: " << filepath << endl;
        return;
    }

    if (!fs::is_regular_file(filepath))
    {
        cerr << "Error: Not a regular file: " << filepath << endl;
        return;
    }

    ifstream in(filepath);
    if (!in)
    {
        cerr << "Error: Cannot open file\n";
        return;
    }

    string line;
    while (getline(in, line))
        cout << line << endl;
}

void cmd_echo(const string &args)
{
    cout << args << endl;
}

/* ---------------- Main Shell ---------------- */

int main()
{
    vector<string> history;
    string cmd;

    while (true)
    {
        cout << fs::current_path() << " $ ";
        getline(cin, cmd);

        cmd = trim(cmd);
        if (cmd.empty())
            continue;

        history.push_back(cmd);

        if (cmd == "exit")
            break;
        else if (cmd == "help")
            cmd_help();
        else if (cmd == "pwd")
            cmd_pwd();
        else if (cmd.rfind("cd", 0) == 0)
            cmd_cd(trim(cmd.substr(2)));
        else if (cmd.rfind("ls", 0) == 0)
            cmd_ls(trim(cmd.substr(2)));
        else if (cmd.rfind("cat", 0) == 0)
            cmd_cat(trim(cmd.substr(3)));
        else if (cmd.rfind("echo", 0) == 0)
            cmd_echo(trim(cmd.substr(4)));
        else if (cmd == "history")
        {
            for (size_t i = 0; i < history.size(); ++i)
                cout << i + 1 << " " << history[i] << endl;
        }
        else
        {
            cout << "Unknown command: " << cmd << endl;
        }
    }

    return 0;
}
