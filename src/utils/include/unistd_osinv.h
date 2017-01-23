// OS invariant version of unistd.h

#ifndef UNISTD_OSINV_H_
#define UNISTD_OSINV_H_

#ifdef _WIN32

    #include <io.h>
    #define posix_memalign(p, a, s) (((*(p)) = _aligned_malloc((s), (a))), *(p) ? 0 : errno)
    #define posix_memalign_free _aligned_free
    #define ssize_t int

    //#define fopen fopen_s
    //#define strncpy(a, b, c) strncpy_s((a), (c), (b), (c))
    //#define open _open
    //#define read _read
    //#define close _close
    //#define strerror strerror_s

#else

    #include <unistd.h>
    #define posix_memalign_free free
    //#define strerror std::strerror

#endif

#endif
