#ifndef NUMEXPR_CONFIG_HPP
#define NUMEXPR_CONFIG_HPP

// x86 platform works with unaligned reads and writes
// MW: I have seen exceptions to this when the compiler chooses to use aligned SSE
#if (defined(NPY_CPU_X86) || defined(NPY_CPU_AMD64))
#  define USE_UNALIGNED_ACCESS 1
#endif

#ifdef USE_VML
/* The values below have been tuned for a Haswell processor (E3-1240 v3) */
/* Note: with VML functions a larger block size (e.g. 8192) allows to make use
 * of the automatic multithreading capabilities of the VML library */
#define BLOCK_SIZE1 8192
#define BLOCK_SIZE2 16
#else
/* The values below have been tuned for a Haswell processor (E3-1240 v3) */
#define BLOCK_SIZE1 8192
#define BLOCK_SIZE2 16
#endif

/* The maximum number of threads (for some static arrays).
 * Choose this large enough for most monsters out there.
   Keep in sync this with the number in __init__.py. */
#define MAX_THREADS 4096

#if defined(_WIN32)
  #include "win32/pthread.h"
  #include <process.h>
  #define getpid _getpid
#else
  #include <pthread.h>
  #include "unistd.h"
#endif

#ifdef SCIPY_MKL_H
#define USE_VML
#endif

#ifdef USE_VML
#include "mkl_vml.h"
#include "mkl_service.h"
#endif

#ifdef _WIN32
  #ifndef __MINGW32__
    #include "missing_posix_functions.hpp"
  #endif
  #include "msvc_function_stubs.hpp"
#endif

#endif // NUMEXPR_CONFIG_HPP
