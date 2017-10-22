#pragma once

namespace ty
{

  enum status
  {
    ok = 0, 
    unsupported,
    invalid_argument,
    dependency_not_found,
    unknown_error
  };

} // namespace ty
