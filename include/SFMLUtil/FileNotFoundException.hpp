#pragma once
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
namespace SFMLUtil {
using fmt::format;
using spdlog::error;
struct FileNotFoundException : std::runtime_error {
  FileNotFoundException(const char *fileName)
  : runtime_error(format("File \"{}\" not found!", fileName)){
    error(what());
  }
};
}  // namespace SFMLUtil