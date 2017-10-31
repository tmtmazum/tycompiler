#pragma once

#include <string>

namespace ty
{

struct indexed_string
{
public:
  indexed_string(char const* start0, size_t size0)
		: indexed_string{s0, start0 + size0}
	{}

	indexed_string(char const* s0, char const* e0)
		: start{ s0 }
		, end{ e0 }
	{}

  void add_index(char const* a)
  {
    assert(a < end);
    segments.emplace_back(a);
  }

  void add_index_at(size_t s)
  {
    assert(start + s < end);
    segments.emplace_back(start + s);
  }

	size_t size() const noexcept { return end - start; }

	auto as_string() const { return std::string{start, end}; }

	auto& at(size_t a) { return start + a; }

	auto& segment(size_t a) { return segments.at(a); }

private:
  char const* start;

  char const* end;

  std::vector<char const*>  segments;
};

};

