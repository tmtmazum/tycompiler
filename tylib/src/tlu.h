#pragma once

#include <string>
#include <vector>

namespace ty
{

template <typename T>
using vector = std::vector<T>;

struct indexed_string : public std::string
{
  vector<size_t>   segments;

  void print_to(FILE* fo)
  {
    auto const start = c_str();
    char const* c = c_str();
    while (iswspace(*c))
      c++;
    fprintf(fo, "  %s\n", c);
    auto const stop = c_str() + size();
    std::string blank( static_cast<std::string::size_type>(stop - c), ' ' );
    for (auto a : segments)
    {
      blank[a + (c - start)] = '^';
    }
    fprintf(fo, "  %s\n", blank.c_str());
  }

  void print() { return print_to(stdout); }
};

//! string where the first character represents the type of literal
//! $		string literal	(e.g. "hello world!\n")
//! #		numeric literal (e.g. 42)
//! ?		identifier (e.g. x, y, z)
//! `		type/constraint
struct literal : public std::string
{

  bool is_string_literal() const noexcept
  {
    return !empty() && at(0) == '$';
  }

  bool is_numeric_literal() const noexcept
  {
    return !empty() && at(0) == '#';
  }

  bool is_identifier() const noexcept
  {
    return !empty() && at(0) == '?';
  }

  bool is_type() const noexcept
  {
    return !empty() && at(0) == '`';
  }

  char const* lexeme() const noexcept
  {
    return &at(1);
  }
};

struct decl
{
  literal id;
  literal type;
};

struct defn : public decl
{
  vector<decl>	decls;
  vector<defn>	defns;
};

struct tlu : public defn
{
  literal				target_triple;
};

}
