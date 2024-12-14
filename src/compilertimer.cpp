#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace {

void
save_exit_time()
{
  const char* out_path = std::getenv("EVAL_OUTPUT_PATH");
  if (!out_path) {
    // std::cerr << "EVAL_OUTPUT_PATH not set\n";
    return;
  }

  std::ofstream of(std::string(out_path) + ".compiler-timer");
  of << std::chrono::time_point_cast<std::chrono::nanoseconds>(
          std::chrono::high_resolution_clock::now())
          .time_since_epoch()
          .count();
}

} // namespace

__attribute__((constructor)) void
ctor()
{
  atexit(save_exit_time);
}
