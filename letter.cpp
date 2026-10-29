#include <chrono>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

std::vector<char> LineToarr(std::string &p) {
  std::vector<char> superarr;
  const char *kaisar = p.c_str();

  for (std::size_t i = 0; kaisar[i] != '\0'; i++) {
    superarr.push_back(kaisar[i]);
  }
  return superarr;
}

int main(int argc, char *argv[]) {
  namespace file = std::filesystem;
  std::string dummy{};
  int LineDuration{};
  std::cout << "Please enter a duration between lines(milliseconds)\n";
  if (!(std::cin >> LineDuration) || LineDuration < 0) {
    std::cerr << "fallo en lectura jeje\n";
  }
  if (LineDuration == 0) {
    goto rest;
  }
rest:
  if (argc > 1) {
    dummy = argv[1];
    file::path DirectoryFile = dummy;
    std::ifstream FileOpener(DirectoryFile);
    if (!FileOpener.is_open()) {
      std::cerr << "Something failed here hehe\n";
      return 1;
    }
    auto ExecutionLine = [&FileOpener](int duration) {
      std::string ActualLine{};
      while (std::getline(FileOpener, ActualLine)) {
        if (ActualLine.empty()) {
          std::cout << "\n";
          continue;
        }
        std::vector<char> split = LineToarr(ActualLine);
        auto letterduration = std::chrono::duration<float, std::milli>(
            static_cast<double>(duration / split.size()));
        for (std::size_t i = 0; i < static_cast<int>(split.size()); i++) {
          std::cout << split[i] << std::flush;
          std::this_thread::sleep_for(letterduration);
        }
        std::cout << "\n";
        // std::cout << ActualLine << "\n";
        //        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
      }
      return;
    };
    ExecutionLine(LineDuration);

  }

  else {
    std::cerr << "this shouldn't have been here \n";
    return 1;
  }

  return 0;
}
