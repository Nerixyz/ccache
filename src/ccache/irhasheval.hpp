#pragma once

#include <ccache/hash.hpp>

#include <chrono>
#include <filesystem>
#include <optional>

namespace irhasheval {

using Clock = std::chrono::high_resolution_clock;

extern std::optional<std::filesystem::path> OUTPUT_FILE;
extern std::optional<Clock::time_point> START;
extern std::optional<Clock::time_point> HASH_START;
extern std::optional<Clock::time_point> HASH_END;
extern std::optional<Hash::Digest> DIGEST;

void flush(bool actually_finished);

class EvalGuard
{
public:
  EvalGuard();
  ~EvalGuard();
};

} // namespace irhasheval
