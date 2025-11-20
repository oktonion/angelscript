/*
   AngelCode Scripting Library
   Copyright (c) 2003-2016 Andreas Jonsson

   This software is provided 'as-is', without any express or implied 
   warranty. In no event will the authors be held liable for any 
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any 
   purpose, including commercial applications, and to alter it and 
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you 
      must not claim that you wrote the original software. If you use
      this software in a product, an acknowledgment in the product 
      documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and 
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source 
      distribution.

   The original version of this library can be located at:
   http://www.angelcode.com/angelscript/

   Andreas Jonsson
   andreas@angelcode.com
*/

#ifndef AS_CMATH_H
#define AS_CMATH_H

#include <math.h>
#include <cmath>

#define AS_ISNAN(v) (v != v)
#define AS_ISINF(v) (!AS_ISNAN(v) && AS_ISNAN(v-v))
#ifndef AS_HUGE_VALF
#   ifdef HUGE_VALF 
#       define AS_HUGE_VALF HUGE_VALF
#   else // HUGE_VALF
#       include <limits>
#       include <climits>
        namespace {
                template<bool>
                struct floating_point_infinity_impl {
                    static float value() throw() {
#                       ifndef __BORLANDC__
                        return std::numeric_limits<float>::infinity();
#                       else
                        return floating_point_infinity_impl<false>::value();
#                       endif
                    }
                };
                template<>
                struct floating_point_infinity_impl<false> {
                    static float value() throw() {
#               ifdef HUGE_VAL
                    return float(HUGE_VAL);
#               else
                    static float infinity = -std::log(0.f);
                    return infinity;
#               endif
                }
            };
            struct floating_point_infinity 
                : floating_point_infinity_impl<std::numeric_limits<float>::has_infinity> {};
        }
#       define AS_HUGE_VALF (floating_point_infinity::value())
#   endif
#endif // AS_HUGE_VALF

#endif // AS_CMATH_H
