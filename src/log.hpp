// Feuerkraft - A Tank Battle Game
// Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#ifndef HEADER_FEUERKRAFT_LOG_HXX
#define HEADER_FEUERKRAFT_LOG_HXX

#include <cstdio>
#include <cstdarg>
#include <string>

#include <SDL.h>

#ifdef __ANDROID__
#  include <android/log.h>
#endif

#ifndef FEUERKRAFT_VERSION
#  define FEUERKRAFT_VERSION "unknown"
#endif

/** Log helpers that reach Android logcat (and desktop stdout). */
inline void fk_log_v(const char* level, const char* fmt, va_list ap)
{
  char buf[1024];
  vsnprintf(buf, sizeof(buf), fmt, ap);
#ifdef __ANDROID__
  int prio = ANDROID_LOG_INFO;
  if (level[0] == 'E' || level[0] == 'F')
    prio = ANDROID_LOG_ERROR;
  else if (level[0] == 'W')
    prio = ANDROID_LOG_WARN;
  else if (level[0] == 'D')
    prio = ANDROID_LOG_DEBUG;
  __android_log_print(prio, "Feuerkraft", "[%s] %s", FEUERKRAFT_VERSION, buf);
#endif
  /* Always mirror via SDL so desktop and SDLActivity logcat both see it. */
  if (level[0] == 'E' || level[0] == 'F')
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", FEUERKRAFT_VERSION, buf);
  else if (level[0] == 'W')
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", FEUERKRAFT_VERSION, buf);
  else
    SDL_Log("[%s] %s", FEUERKRAFT_VERSION, buf);
}

inline void fk_log(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  fk_log_v("I", fmt, ap);
  va_end(ap);
}

inline void fk_log_error(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  fk_log_v("E", fmt, ap);
  va_end(ap);
}

inline void fk_log_warn(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  fk_log_v("W", fmt, ap);
  va_end(ap);
}

inline void fk_log_string(const std::string& msg)
{
  fk_log("%s", msg.c_str());
}

#endif

/* EOF */
