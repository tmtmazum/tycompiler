#pragma once

#include "ty_status.h"

namespace ty
{

//! Compiles 'target' into 'output' 
//! \param	target		Target file to compile
//! \param 	output		[optional] Output file. If not provided, 
//										'target' is used with the default output extension
ty::status compile_target(char const* target, char const* output = "");

} // namespace ty

