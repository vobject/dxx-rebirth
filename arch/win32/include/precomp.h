#pragma once

#define _WIN32_WINNT 0x0501 // for get/freeaddrinfo()
#define _CRT_SECURE_NO_WARNINGS
#define STRSAFE_NO_DEPRECATE

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <setjmpex.h>
#include <malloc.h>
#include <memory.h>
#include <io.h>
#include <conio.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>

#include <strsafe.h>

#define vsnprintf StringCbVPrintfA
#define snprintf StringCbPrintfA
#define strdup _strdup
#define stricmp _stricmp
#define strcasecmp _stricmp
#define strupr _strupr
#define strlwr _strlwr
#define strrev _strrev
#define strnicmp _strnicmp

#include <algorithm>
#include <array>

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include <digi_audio.h>

#undef min
#undef max

using std::min;
using std::max;

typedef LONG_PTR ssize_t;

#pragma warning(disable:4244) // warning C4244: '=': conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4480) // warning C4480: nonstandard extension used: specifying underlying type for enum 'segment_type_t'
#pragma warning(disable:4201) // warning C4201: nonstandard extension used : nameless struct/union
#pragma warning(disable:4127) // warning C4127: conditional expression is constant

#pragma hdrstop