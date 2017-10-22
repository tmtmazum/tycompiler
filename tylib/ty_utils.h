#pragma once

#include <string>

namespace ty
{

template <typename CharType>
bool str_eq(CharType const* A, CharType const* B)
{
	using traits = std::char_traits<CharType>;
	auto const lA = traits::length(A);
	auto const lB = traits::length(B);

	return (lA == lB) && (0 == traits::compare(A, B, lA));
}

}
