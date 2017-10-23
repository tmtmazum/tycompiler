#pragma once

#include <string>

namespace ty
{

class indexed_string_base
{
  std::string& parent;
protected:
  char const* start;
  char const* end;

  indexed_string_base(std::string& p, size_t b, size_t e)
    : parent{p}
    , start{p.c_str() + b}
    , end{ p.c_str() + e }
  {}

  indexed_string_base(std::string& p, char const* s, char const* e)
    : parent{p}
    , start{s}
    , end{e}
  {}

};

struct indexed_string : public indexed_string_base
{
  std::vector<char const*>  segments;
};

};