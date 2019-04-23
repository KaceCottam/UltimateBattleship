#pragma once
#include <fmt/format.h>
#include <spdlog/spdlog.h>
namespace SFMLUtil {
struct BadIndexError : std::exception {
  BadIndexError(const std::size_t index, const std::size_t size) {
    spdlog::error(fmt::format("Cannot access index {} in vector of size {}!",
                              index, size));
  }
};
}  // namespace SFMLUtil