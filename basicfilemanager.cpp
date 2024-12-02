#include <iostream>
#include <filesystem> 
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void showHelp() {
    std::cout << "Commands:\n";
    std::cout << "  ls           - List contents of the current directory\n";
    std::cout << "  cd <path>    - Change directory\n";
    std::cout << "  view <file>  - View contents of a file\n";
    std::cout << "  mkdir <dir>  - Create a new directory\n";
    std::cout << "  cp <src> <dst> - Copy a file\n";
    std::cout << "  mv <src> <dst> - Move a file\n";
    std::cout << "  help         - Show available commands\n";
    std::cout << "  exit         - Exit the file manager\n";
}

void listContents(const fs::path& path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        std::cout << "Contents of " << path << ":\n";
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << "  " << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << "\n";
        }
    } else {
        std::cout << "Directory does not exist.\n";
    }
}

void changeDirectory(fs::path& currentPath, const std::string& newPath) {
    fs::path tempPath = currentPath / newPath;
    if (fs::exists(tempPath) && fs::is_directory(tempPath)) {
        currentPath = fs::canonical(tempPath);
        std::cout << "Current Directory: " << currentPath << "\n";
    } else {
        std::cout << "Directory does not exist.\n";
    }
}

void viewFile(const fs::path& path) {
    if (fs::exists(path) && fs::is_regular_file(path)) {
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
    } else {
        std::cout << "File does not exist or is not a regular file.\n";
    }
}

void createDirectory(const fs::path& path) {
    if (!fs::exists(path)) {
        fs::create_directory(path);
        std::cout << "Directory created: " << path << "\n";
    } else {
        std::cout << "Directory already exists.\n";
    }
}

void copyFile(const fs::path& src, const fs::path& dst) {
    if (fs::exists(src) && fs::is_regular_file(src)) {
        fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
        std::cout << "File copied from " << src << " to " << dst << "\n";
    } else {
        std::cout << "Source file does not exist.\n";
    }
}

void moveFile(const fs::path& src, const fs::path& dst) {
    if (fs::exists(src) && fs::is_regular_file(src)) {
        fs::rename(src, dst);
        std::cout << "File moved from " << src << " to " << dst << "\n";
    } else {
        std::cout << "Source file does not exist.\n";
    }
}

int main() {
    fs::path currentPath = fs::current_path();
    std::string command, arg1, arg2;

    std::cout << "Welcome to the C++ File Manager!\n";
    std::cout << "Current Directory: " << currentPath << "\n";
    showHelp();

    while (true) {
        std::cout << "\n> ";
        std::cin >> command;

        if (command == "ls") {
            listContents(currentPath);
        } else if (command == "cd") {
            std::cin >> arg1;
            changeDirectory(currentPath, arg1);
        } else if (command == "view") {
            std::cin >> arg1;
            viewFile(currentPath / arg1);
        } else if (command == "mkdir") {
            std::cin >> arg1;
            createDirectory(currentPath / arg1);
        } else if (command == "cp") {
            std::cin >> arg1 >> arg2;
            copyFile(currentPath / arg1, currentPath / arg2);
        } else if (command == "mv") {
            std::cin >> arg1 >> arg2;
            moveFile(currentPath / arg1, currentPath / arg2);
        } else if (command == "help") {
            showHelp();
        } else if (command == "exit") {
            std::cout << "Exiting File Manager.\n";
            break;
        } else {
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
        }
    }

    return 0;
}
