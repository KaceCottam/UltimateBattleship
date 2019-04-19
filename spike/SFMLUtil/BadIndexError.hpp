#pragma once
#include <fmt/format.h>
#include <spdlog/spdlog.h>
namespace SFMLUtil {
using fmt::format;
using spdlog::error;
struct BadIndexError : std::exception {
  BadIndexError(const std::size_t index, const std::size_t size) {
    error(format("Cannot acces index {} in vector of size {}!", index, size));
  }
};
}  // namespace SFMLUtil