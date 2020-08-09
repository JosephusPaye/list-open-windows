#include "src/headers.h"
#include <iostream>

int main() {
  auto windows = listWindows();

  for (auto window : windows) {
    std::cout << "{" << std::endl;
    std::cout << "  handle: " << window.handle << std::endl;
    std::cout << "  zOrder: " << window.zOrder << std::endl;
    std::cout << "  className: " << window.className << std::endl;
    std::cout << "  caption: " << window.caption << std::endl;
    std::cout << "  processId: " << window.processId << std::endl;
    std::cout << "  processPath: " << window.processPath << std::endl;
    std::cout << "}" << std::endl;
  }

  return 0;
}
