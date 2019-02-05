#ifndef LIB_INCLUDES
#define LIB_INCLUDES
#pragma once

#pragma warning(disable:4091)
#pragma warning(disable:4100)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <windows.h>
#include <versionhelpers.h>
#include <wdbgexts.h>
#include <process.h>
#include <commctrl.h>
#include <stdlib.h>
#include <malloc.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <locale>
#include <codecvt>
#include <tlhelp32.h>
#include <Psapi.h>
#include <DbgHelp.h>
#include <Winternl.h>
#include <Shlwapi.h>
#include <shellapi.h>
#include <inttypes.h>
#include <stdio.h>
#include <stddef.h>
#include <intrin.h>
#include <strsafe.h>
#include <iostream>
#include <utility>
#include <functional>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <direct.h>
#include <list>
#include <tchar.h>
#include <ShlObj.h>
#include <cstddef>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <apiset.h>
#include "zlib.h"
#include "rsa.h"
#include "randpool.h"
#include "rdrand.h"
#include "osrng.h"
#include "modes.h"

#ifdef CSGODLL
#include "..\DLL_CSGO\SDK.hxx"
#endif

#pragma warning(disable:4191)
#ifdef _DEBUG
#define __WXDEBUG__
#endif

#endif