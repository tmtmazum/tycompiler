#pragma once

#include "ty_status.h"
#include <string>
#include <experimental/filesystem>

namespace ty
{

using path = std::experimental::filesystem::path;

//! Trims unnecessary whitespace from source code
std::string trim_source(std::string const& input);
void trim_source(std::string& input);

//! Compiles 'target' file into 'output' file
//! \param	target		Target file to compile
//! \param 	output		[optional] Output file. If not provided, 
//										'target' is used with the default output extension
ty::status compile_to_ir(path const& target, path const& output);

std::string compile_to_ir(std::string const& input, ty::status& status);

} // namespace ty

