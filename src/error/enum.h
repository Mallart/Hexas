#include <stdlib.h>
#include <stdio.h>

#define throw(errno) exit_error(errno, 0);

enum HEXAS_EXCEPTIONS
{
    EXCEPTION_NO_EXCEPTION,
// #region IO
    EXCEPTION_FILE_NOT_FOUND,
// #region RUNTIME
    EXCEPTION_NULL_POINTER,
// #region COMPILATION
};

static char const * const error_messages[] = {
    "No error.",
    "Could not find specified resource.",
};

inline static int exit_error(enum HEXAS_EXCEPTIONS errno, char* additional_message)
{
    printf("An unhandled error unfortunately occured. Error code: %u | Error message: %s | Context: %s.\n",
        errno, error_messages[errno], additional_message ? additional_message : "no");
    exit(errno);
    return errno;
}
