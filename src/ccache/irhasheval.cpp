#include <ccache/irhasheval.hpp>
#include <ccache/util/string.hpp>

#include <chrono>
#include <fstream>
#include <iostream>

namespace {

auto
toNs(auto dur)
{
  return std::chrono::duration_cast<std::chrono::nanoseconds>(dur);
}

} // namespace

namespace irhasheval {

constinit std::optional<std::filesystem::path> OUTPUT_FILE;
constinit std::optional<Clock::time_point> START;
constinit std::optional<Clock::time_point> HASH_START;
constinit std::optional<Clock::time_point> HASH_END;
constinit std::optional<Hash::Digest> DIGEST;

void
flush(bool actually_finished)
{
  if (!START || !OUTPUT_FILE || !HASH_START || !HASH_END) {
    return; // TODO: log?
  }

  auto end = Clock::now();

  std::ofstream of(OUTPUT_FILE->concat(".ccache-eval"));
  auto complete_ns = toNs(*HASH_END - *START);
  auto hash_ns = toNs(*HASH_END - *HASH_START);
  auto to_exit_ns = toNs(end - *START);
  auto formatted_hash = DIGEST ? util::format_digest(*DIGEST) : "?";
  of << complete_ns.count() << ':' << hash_ns.count() << ':' << formatted_hash
     << '\n';
  if (actually_finished) {
    of << "finish:" << to_exit_ns.count();
  } else {
    of << "start:" << toNs(START->time_since_epoch()).count();
  }
  of.close();
}

EvalGuard::EvalGuard()
{
  START = Clock::now();
}

EvalGuard::~EvalGuard()
{
  flush(true);
}

} // namespace irhasheval
