#pragma once
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
namespace SFMLUtil {
struct FileNotFoundException : std::runtime_error {
  FileNotFoundException(const char *fileName)
  : runtime_error(fmt::format("File \"{}\" not found!", fileName)){
    spdlog::error(what());
  }
};
}  // namespace SFMLUtil