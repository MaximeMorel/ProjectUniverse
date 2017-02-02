
#ifndef ENGINE_EXPORT_H
#define ENGINE_EXPORT_H

#ifdef ENGINE_STATIC_DEFINE
#  define ENGINE_EXPORT
#  define ENGINE_NO_EXPORT
#else
#  ifndef ENGINE_EXPORT
#    ifdef engine_EXPORTS
        /* We are building this library */
#      if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#        define ENGINE_EXPORT __declspec(dllexport)
#      elif defined(__linux__) || defined(__linux) || defined(linux)
#        define ENGINE_EXPORT __attribute__((visibility("default")))
#      endif
#    else
        /* We are using this library */
#      if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#        define ENGINE_EXPORT __declspec(dllimport)
#      elif defined(__linux__) || defined(__linux) || defined(linux)
#        define ENGINE_EXPORT __attribute__((visibility("default")))
#      endif
#    endif
#  endif

#  ifndef ENGINE_NO_EXPORT
#    if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#      define ENGINE_NO_EXPORT
#    elif defined(__linux__) || defined(__linux) || defined(linux)
#      define ENGINE_NO_EXPORT __attribute__((visibility("hidden")))
#    endif
#  endif
#endif

#ifndef ENGINE_DEPRECATED
#  if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#    define ENGINE_DEPRECATED __declspec(deprecated)
#  elif defined(__linux__) || defined(__linux) || defined(linux)
#    define ENGINE_DEPRECATED __attribute__((__deprecated__))
#  endif
#endif

#ifndef ENGINE_DEPRECATED_EXPORT
#  define ENGINE_DEPRECATED_EXPORT ENGINE_EXPORT ENGINE_DEPRECATED
#endif

#ifndef ENGINE_DEPRECATED_NO_EXPORT
#  define ENGINE_DEPRECATED_NO_EXPORT ENGINE_NO_EXPORT ENGINE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ENGINE_NO_DEPRECATED
#    define ENGINE_NO_DEPRECATED
#  endif
#endif

#endif
