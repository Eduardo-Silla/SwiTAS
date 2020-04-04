
// Copyright (c) 2010-2019 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef __yas__detail__config__endian_hpp
#define __yas__detail__config__endian_hpp

/***************************************************************************/

#if defined(__linux__) || defined(__ANDROID__) || defined(__EMSCRIPTEN__)
#include <endian.h>
#if(__BYTE_ORDER == __LITTLE_ENDIAN)
#define __YAS_LITTLE_ENDIAN (1)
#define __YAS_BIG_ENDIAN (0)
#elif(__BYTE_ORDER == __BIG_ENDIAN)
#define __YAS_LITTLE_ENDIAN (0)
#define __YAS_BIG_ENDIAN (1)
#elif(__BYTE_ORDER == __PDP_ENDIAN)
#define YAS_PDP_ENDIAN
#else
#error Unknown machine endianness detected.
#endif
#elif defined(_BIG_ENDIAN)
#define __YAS_LITTLE_ENDIAN (0)
#define __YAS_BIG_ENDIAN (1)
#elif defined(_LITTLE_ENDIAN)
#define __YAS_LITTLE_ENDIAN (1)
#define __YAS_BIG_ENDIAN (0)
#elif defined(__sparc) || defined(__sparc__) || defined(_POWER) || defined(__powerpc__) || defined(__ppc__) || defined(__hpux) || defined(_MIPSEB) || defined(_POWER) || defined(__s390__)
#define __YAS_LITTLE_ENDIAN (0)
#define __YAS_BIG_ENDIAN (1)
#elif defined(__i386__) || defined(__alpha__) || defined(__ia64) || defined(__ia64__) || defined(_M_IX86) || defined(_M_IA64) || defined(_M_ALPHA) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) || defined(__x86_64) || defined(__x86_64__) || defined(_M_X64) || defined(__arm64__) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7S__)
#define __YAS_LITTLE_ENDIAN (1)
#define __YAS_BIG_ENDIAN (0)
#else
#error The file yas/detail/config/endian.hpp needs to be set up for your CPU type.
#endif

#define __YAS_BSWAP_NEEDED(F) (((F & ::yas::ebig) && !__YAS_BIG_ENDIAN) || ((F & ::yas::elittle) && !__YAS_LITTLE_ENDIAN))

/***************************************************************************/

#endif // __yas__detail__config__endian_hpp
