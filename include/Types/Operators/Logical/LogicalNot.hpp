/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-16 - 14 h 13
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

#include "Types/StrongType.hpp"

namespace FoxMath::Operator
{
    /**
     * @brief Logical NOT operator class
     * 
     * This class is meant to be used in conjunction with the NamedType class.
     * This allows for better and quicker operator integrations to named types.
     * 
     * @tparam TStrongTypedef Base NamedType
     *
     * @see NamedType
     */
    template <typename TStrongTypedef>
    struct LogicalNot
    {
        /**
         * @brief Logical NOT operator
         *
         * @param in_instance Operand instance
         *
         * @return Value of the operation
         */
        constexpr inline
        bool operator!(TStrongTypedef const& in_instance) noexcept
        {
            using Type = UnderlyingType<TStrongTypedef>;

            return !static_cast<Type const&>(in_instance);
        }
    };
} /*namespace FoxMath::Operator*/
