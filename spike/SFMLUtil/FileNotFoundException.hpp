#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
struct FileNotFoundException : std::exception {
  FileNotFoundException(const char *fileName) {
    spdlog::error(fmt::format("File \"{}\" not found!",fileName));
  }
};