#pragma once

#ifdef ASSERT_FAIL
# undef ASSERT_FAIL
# define ASSERT_FAIL assert_handler
#endif

#include <assert.hpp>

void assert_handler(libassert::assert_type type, libassert::ASSERTION fatal, const libassert::assertion_printer& printer);
