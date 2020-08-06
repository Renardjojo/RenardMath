/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-05 - 09 h 35
 * 
 * 
 * MIT License
 * 
 * Copyright (c) 2020 Six Jonathan
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <type_traits>

namespace FoxMath::Type
{
    /**
     * @brief Sfinae shorthand for std::is_signed_v
     * @note us
     * @param T Type to test
     */
    template<typename T>
    using IsSigned = std::enable_if_t<std::is_signed_v<T>, bool>;

    /**
     * @brief Sfinae shorthand for std::is_unsigned_v
     * @note usage : `template<IsUnsigned<T> = true>`
     * @param T Type to test
     */
    template<typename T>
    using IsUnsigned = std::enable_if_t<std::is_unsigned_v<T>, bool>;

    /**
     * @brief Sfinae shorthand for std::is_arithmetic_v
     * @note usage : `template<IsArithmetic<T> = true>`
     * @param T Type to test
     */
    template<typename T>
    using IsArithmetic = std::enable_if_t<std::is_arithmetic_v<T>, bool>;

    /**
     * @brief Sfinae shorthand for std::is_floating_point_v
     * @note usage : `template<IsFloatingPoint<T> = true>`
     * @param T Type to test
     */
    template<typename T>
    using IsFloatingPoint = std::enable_if_t<std::is_floating_point_v<T>, bool>;

} /*namespace FoxMath::Type*/