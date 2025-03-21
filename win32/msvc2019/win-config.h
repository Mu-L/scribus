#ifndef WINCONFIG_H
#define WINCONFIG_H

/* Version number of package */
#define VERSION "1.7.1.svn"

/* Are we building an executable to be included in MacOS/X .app bundle? */
#undef BUILD_MAC_BUNDLE

/* Are we using native api for dll management */
#define DLL_USE_NATIVE_API 1

/* Defines if your system has the boost libraries */
#define HAVE_BOOST 1

/* Defines if your system has the cairo library */
#define HAVE_CAIRO 1

/* Cups */
#undef HAVE_CUPS

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef HAVE_DLFCN_H

/* Defines if your system has the libfontconfig library */
#undef HAVE_FONTCONFIG

/* Defines if your system has the harfbuzz-subset library */
#define HAVE_HARFBUZZ_SUBSET 1

/* Defines if your system has the hunspell library */
#define HAVE_HUNSPELL 1

/* Defines hunspell version if your system has the hunspell library */
#define HUNSPELL_VERSION "1.7.2"

/* ColorManagement (Windows) */
#define HAVE_ICM 1

/* JPEG XL support */
#undef HAVE_JXL

/* ColorManagement (LittleCms2) */
#define HAVE_LCMS2 1

/* Define if you have libz */
#define HAVE_LIBZ 1

/* Define if you have the development files for podofo */
#define HAVE_PODOFO 1

/* Define if you have the development files for podofo */
#define HAVE_POPPLER 1

/* Define if you have the development files for python */
#define HAVE_PYTHON 1

/* Define if you have the development files for librevenge */
#define HAVE_REVENGE 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define snprintf(a, b, c, d) _snprintf(a, b, c, d)
#endif

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Tifflib */
#define HAVE_TIFF 1

/* Can we use unicode functions (Windows) */
#define HAVE_UNICODE 1

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Defines if your system has the libxml2 library */
#define HAVE_XML 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
#undef WORDS_BIGENDIAN

#define HAVE_CONFIG_H 1
#define WIN32_LEAN_AND_MEAN

typedef unsigned char boolean;
#define HAVE_BOOLEAN

#endif
