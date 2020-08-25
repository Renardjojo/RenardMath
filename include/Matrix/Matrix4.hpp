/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-25 - 20 h 26
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

#include "Matrix/SquareMatrix.hpp"

namespace FoxMath::Matrix
{
    template <typename TType = float, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    class Matrix4 :  public SquareMatrix<4, TType, TMatrixConvention>
    {
        private:

        protected:

        #pragma region attribut
        #pragma endregion //!attribut

        #pragma region static attribut
        #pragma endregion //! static attribut

        #pragma region methods
        #pragma endregion //!methods

        public:

        #pragma region constructor/destructor

        constexpr inline
        Matrix4 () noexcept 					                = default;

        constexpr inline
        Matrix4 (const Matrix4& other) noexcept			        = default;

        constexpr inline
        Matrix4 (Matrix4&& other) noexcept				        = default;

        inline
        ~Matrix4 () noexcept				                    = default;

        constexpr inline
        Matrix4& operator=(Matrix4 const& other) noexcept		= default;

        constexpr inline
        Matrix4& operator=(Matrix4 && other) noexcept			= default;

        #pragma endregion //!constructor/destructor

        #pragma region methods
        #pragma endregion //!methods

        #pragma region accessor
        #pragma endregion //!accessor

        #pragma region mutator
        #pragma endregion //!mutator

        #pragma region operator
        #pragma endregion //!operator

        #pragma region convertor
        #pragma endregion //!convertor

    };

} /*namespace FoxMath::Matrix*/