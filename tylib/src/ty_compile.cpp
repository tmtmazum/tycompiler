#include "ty_compile.h"
#include "ty_utils.h"
#include "tlu.h"
#include <experimental/filesystem>
#include <fstream>

namespace ty
{

template <typename CharType, typename Cond>
indexed_string extract_while(std::basic_ifstream<CharType>& ifs, Cond cond)
{
  indexed_string out;
  auto last = '?';
  for (auto c = ifs.get(); cond(c); last = c, c = ifs.get())
  {
    if(c != '\t' && c != '\n' && (!iswspace(last) || !iswspace(c)))
      out.push_back(c);

    if (!ifs.good())
      break;
  }
  return out;
}

template <typename CharType>
indexed_string extract_env(std::basic_ifstream<CharType>& ifs)
{
  indexed_string out = extract_while(ifs, [](auto c) { return c != ';'; });
  printf("Extracted env : \n");
  out.print();
  printf("\n");

  return out;
}
template <typename CharType>
auto extract_declproc(std::basic_ifstream<CharType>& ifs)
{
  indexed_string out = extract_while(ifs, [](auto c) { return c != ';'; });
  //printf("Extracted declproc '%s'\n", out.c_str());
  printf("Extracted declproc : \n");
  out.print();
  printf("\n");
  return out;
}
template <typename CharType>
auto extract_ret(std::basic_ifstream<CharType>& ifs)
{
  indexed_string out = extract_while(ifs, [](auto c) { return c != ';'; });
  printf("Extracted ret : \n");
  out.print();
  printf("\n");

  return out;
}
template <typename CharType>
auto extract_proc(std::basic_ifstream<CharType>& ifs)
{
  indexed_string out = extract_while(ifs, [](auto c) { return c != '{'; });
  out.segments.emplace_back(out.size());
  out.push_back('{');
  indexed_string l2 = extract_while(ifs, [](auto c) { return c != '}'; });
  out += l2;
  out.push_back('}');
  printf("Extracted proc : \n");
  out.print();
  printf("\n");

  return out;
}

void process_env(indexed_string const& in_literal, tlu& out_defn)
{

}
void process_declproc(indexed_string const& in_literal, defn& out_defn)
{

}
void process_proc(indexed_string const& in_literal, defn& out_defn)
{
  
}


ty::status impl_compile_target(path const& target, path const& output)
{
  if (!std::experimental::filesystem::exists(target))
    return ty::status::invalid_argument;

  std::ifstream ifs{ target, std::ifstream::in };

  std::ofstream ofs{ output, std::ofstream::out };
  ofs << R"(define i32 @magic_number() {
    ret i32 42
})";

  tlu current_tlu;
  std::string word;
  while (1)
  {
    ifs >> word;
    if (word == "env")
    {
      indexed_string env_stmt = extract_env(ifs);
      process_env(env_stmt, current_tlu);
    }
    else if (word == "declproc")
    {
      indexed_string declproc = extract_declproc(ifs);
      process_declproc(declproc, current_tlu);
    }
    else if (word == "proc")
    {
      indexed_string proc = extract_proc(ifs);
      process_proc(proc, current_tlu);
    }
    else if (word == "return")
    {
      indexed_string ret = extract_ret(ifs);
    }
    else if (word == ";")
    {
      printf("Ignoring no-op\n");
      return ty::status::ok;
    }
    else
    {
      printf("Unrecognized directive '%s'", word.c_str());
      return ty::status::ok;
    }
  }
  return ty::status::unsupported;
}


//! Compiles 'target' into 'output' 
//! \param	target		Target file to compile
//! \param 	output		[optional] Output file. If not provided, 
//										'target' is used with the default output extension
ty::status compile_to_ir(path const& target, path const& output)
{
  if (!std::experimental::filesystem::exists(target))
    return ty::status::invalid_argument;
 
  std::ifstream ifs{ target, std::ifstream::in };
  std::string in{ std::istreambuf_iterator<char>(ifs), {} };
  
  auto status = ty::status::ok;
  std::string out = compile_to_ir(in, status);

  std::ofstream ofs{ output, std::ofstream::out };
  ofs << out;
  return status;
}

//! Trims unnecessary whitespace from source code
std::string trim_source(std::string const& input)
{
  auto last = '?';
  std::string out;
  for(auto c : input)
  {
    if(c != '\t' && c != '\n' && (!iswspace(last) || !iswspace(c)))
      out.push_back(c);
    last = c;
  }
  return out;
}

std::string compile_to_ir(std::string const& input, ty::status& status)
{
  auto const trimmed_in = trim_source(input);
  return R"(define i32 @magic_number() {
    ret i32 42
})";
  //return input;
}

} // namespace ty

