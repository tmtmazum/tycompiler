#include "ty_compile.h"
#include "ty_utils.h"
#include <experimental/filesystem>
#include <fstream>


namespace
{

template <typename CharType>
ty::status impl_compile_target(CharType const* target, CharType const* output)
{
  if (!std::experimental::filesystem::exists(target))
    return ty::status::invalid_argument;

  std::basic_ifstream<CharType> ifs{ target, std::ifstream::in };

  if (str_eq(output, ""))
  {

  }
  return ty::status::unsupported;
}

}

namespace ty
{

//! Compiles 'target' into 'output' 
//! \param	target		Target file to compile
//! \param 	output		[optional] Output file. If not provided, 
//										'target' is used with the default output extension
ty::status compile_target(char const* target, char const* output)
{
  return impl_compile_target(target, output);
}

} // namespace ty

