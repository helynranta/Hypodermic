#pragma once

#if defined(__CLANG__) or defined(__APPLE__)
  #define HYPODERMIC_EXPORT __attribute__((visibility("default")))
#elif defined(WIN32)
  #define HYPODERMIC_EXPORT
#endif

