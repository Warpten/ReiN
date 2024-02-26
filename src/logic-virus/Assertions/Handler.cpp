#include "assertions/handler.hpp"

#include <cstdlib>
#include <iostream>

#include <crtdbg.h>
#include <io.h>
#include <Windows.h>

void assert_handler(libassert::assert_type type, libassert::ASSERTION fatal, const libassert::assertion_printer& printer) {
#ifndef STDERR_FILENO
    int STDERR_FILENO = _fileno(stderr);
#endif

    std::string message = printer(libassert::utility::terminal_width(STDERR_FILENO));

    if (_isatty(STDERR_FILENO))
        std::cerr << message << std::endl;
    else
        std::cerr << libassert::utility::strip_colors(message) << std::endl;

    std::cerr << "GetLastError() returned " << GetLastError() << std::endl;

    using libassert::assert_type;

    if (fatal == libassert::ASSERTION::FATAL) {
        switch (type) {
        case assert_type::assertion:
        case assert_type::debug_assertion:
        {
#if _DEBUG
            const auto [fileName, lineNumber, _, assert_message] = printer.get_assertion_info();
            _CrtDbgReport(_CRT_ASSERT, fileName, lineNumber, nullptr, "%s",
                libassert::utility::strip_colors(message).c_str());
#else
            std::abort();
#endif

            break;
        }
        case assert_type::verification:
            throw libassert::verification_failure();
        case assert_type::assumption:
            break;
        }
    }
}