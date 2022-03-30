#include <iostream>

#if defined(__linux)
#include "client/linux/handler/exception_handler.h"
#elif defined(__APPLE__)

#include "client/mac/handler/exception_handler.h"

#elif defined(WIN32)
#include "client/windows/handler/exception_handler.h"
#include <locale>
#include <codecvt>
#endif

#ifdef defined(WIN32)
bool minidumpCB(const wchar_t *dump_path, const wchar_t *id, void *context, EXCEPTION_POINTERS *exinfo, MDRawAssertionInfo *assertion, bool succeeded) {
#else

bool minidumpCB(const char *dump_path, const char *id, void *context, bool succeeded) {
#endif
    if (succeeded) {
        printf("\"Mini Dump file:%s dump Path=%s\n", id, dump_path);
    }
    return succeeded;
}

using std::string;

void setupBreakpad(const string &outputDirectory) {
    google_breakpad::ExceptionHandler *exception_handler;
#if defined(__linux)
    exception_handler = new google_breakpad::ExceptionHandler(google_breakpad::MinidumpDescriptor(outputDirectory),
                                                            /*FilterCallback*/ 0,
                                                            0,
                                                            /*context*/ 0,
                                                            true,
                                                            -1);
#elif defined(__APPLE__)
    exception_handler = new google_breakpad::ExceptionHandler(
            outputDirectory,
            /*FilterCallback*/ 0,

            minidumpCB, /*context*/ 0, true, NULL);;
#elif defined(WIN32)
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> strConv;
    exception_handler = new google_breakpad::ExceptionHandler(
        strConv.from_bytes(outputDirectory), /* minidump output directory */
        0,   /* filter */
        0,   /* minidump callback */
        0,   /* calback_context */
        google_breakpad::ExceptionHandler::HANDLER_ALL /* handler_types */
    );

    // call TerminateProcess() to prevent any further code from
    // executing once a minidump file has been written following a
    // crash.  See ticket #17814
    exception_handler->set_terminate_on_unhandled_exception(true);
#endif
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    setupBreakpad(".");
    int a = 1;
    free(&a);
    return 0;
}
