/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-18 - 08 h 31
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

#include "Matrix/EMatrixConvention.hpp" //EMatrixConvention
#include "Types/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>
#include "Vector/GenericVector.hpp" //Vector::GenericVector
#include "Types/Implicit.hpp"

#include <array> //std::array

namespace FoxMath::Matrix
{
    /*Use of IsArithmetic*/
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor,
                Type::IsNotEqualTo<TRowSize, 0> = true, 
                Type::IsNotEqualTo<TColumnSize, 0> = true,
                Type::IsArithmetic<TType> = true>
    class GenericMatrix;

    /*Specilisation of GenericMatrix class*/
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    class GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>
    {
        private:
    
        protected:

        #pragma region static attribut

        /**
         * @brief Return the length if internal vector
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr static inline
        size_t vectorLength () noexcept
        {
            if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
                return TColumnSize;
            else 
                return TRowSize;
        }

        /**
         * @brief Return the number of vector inside the matrix
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr static inline
        size_t numberOfInternalVector () noexcept
        {
            if constexpr (TMatrixConvention == EMatrixConvention::ColumnMajor)
                return TRowSize;
            else 
                return TColumnSize;
        }

        /**
         * @brief Return the number of data inside the matrix
         * 
         * @return constexpr size_t 
         */
        [[nodiscard]] constexpr static inline
        size_t numberOfData () noexcept
        {
            return TRowSize * TColumnSize;
        }

        #pragma endregion //! static attribut

        #pragma region attribut

        using InternalVector = Vector::GenericVector<vectorLength (), TType>;

        union
        {
            std::array<TType, numberOfData ()> m_data;
            std::array<InternalVector, numberOfInternalVector ()>  m_vector {};
        };

        #pragma endregion //!attribut
    
        #pragma region methods
        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        constexpr inline
        GenericMatrix () noexcept 					                    = default;

        constexpr inline
        GenericMatrix (const GenericMatrix& other) noexcept			    = default;

        constexpr inline
        GenericMatrix (GenericMatrix&& other) noexcept				    = default;

        inline
        ~GenericMatrix () noexcept				                        = default;

        constexpr inline
        GenericMatrix& operator=(GenericMatrix const& other) noexcept	= default;

        constexpr inline
        GenericMatrix& operator=(GenericMatrix && other) noexcept		= default;
    
        #pragma endregion //!constructor/destructor
    
        #pragma region methods
        #pragma endregion //!methods
    
        #pragma region accessor

        /**
         * @brief   Returns a reference to the InternalVector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : use at(indexVector).at(indexElem) to access at the element
         * 
         * @param index 
         * @return constexpr InternalVector& 
         */
        [[nodiscard]] inline constexpr
		InternalVector& 	    at (size_t index) throw ();

        /**
         * @brief   Returns a const reference to the InternalVector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : use at(indexVector).at(indexElem) to access at the element
         * 
         * @param index 
         * @return constexpr const InternalVector& 
         */
        [[nodiscard]] inline constexpr
		const InternalVector& 	at (size_t index) const throw ();

        /**
         * @brief   Returns a reference to the element at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : to avoid this check, use that form [indexVec][indexElem]. These both operators are inline and have no impact on read latency 
         * 
         * @param index 
         * @return constexpr TType& 
         */
        [[nodiscard]] inline constexpr
		TType& 	    getData	(size_t index) throw();

        /**
         * @brief   Returns a const reference to the element at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : to avoid this check, use that form [indexVec][indexElem]. These both operators are inline and have no impact on read latency 
         * 
         * @param index 
         * @return constexpr const TType& 
         */
        [[nodiscard]] inline constexpr
		const TType& 	    getData	(size_t index) const throw ();

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention&
         */
        [[nodiscard]] inline constexpr
		const EMatrixConvention& 	    getMatrixConvention	() const noexcept;

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention &
         */
        [[nodiscard]] inline constexpr
		const size_t& 	    getRowSize	() const noexcept;

        /**
         * @brief Get the Matrix Convention enumerator. 
         * 
         * @return constexpr const EMatrixConvention&
         */
        [[nodiscard]] inline constexpr
		const size_t& 	    getColumnSize	() const noexcept;
        
        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma region member access operators

        /**
         * @brief   Returns a reference to the InternalVector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : use at[indexVector][indexElem] to access at the element
         * 
         * @param index 
         * @return constexpr InternalVector& 
         */
        [[nodiscard]] inline constexpr
		InternalVector& 	    operator[]	(size_t index) noexcept;

        /**
         * @brief   Returns a reference to the InternalVector at index in the GenericMatrix
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericMatrix, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @note : use at[indexVector][indexElem] to access at the element
         * 
         * @param index 
         * @return constexpr const InternalVector& 
         */
        [[nodiscard]] inline constexpr
		const InternalVector& 	    operator[]	(size_t index) const noexcept;

        #pragma endregion //!member access operators
        #pragma region  assignment operators

        /**
         * @brief Assignment operator that assign any matrix in another
         * 
         * @tparam TRowSizeOther 
         * @tparam TColumnSizeOther 
         * @tparam TTypeOther 
         * @tparam TMatrixConventionOther 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		implicit inline constexpr
		GenericMatrix& operator=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief simple assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator+=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator+=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator-=(TscalarType scalar) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator-=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator*=(TscalarType scalar) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator*=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator/=(TscalarType scalar) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator/=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator%=(TscalarType scalar) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator%=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator&=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator&=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator|=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator|=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator^=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator^=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator<<=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator<<=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericMatrix& 
         */
        template<typename TscalarType, Type::IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericMatrix& operator>>=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericMatrix& 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
		inline constexpr
		GenericMatrix& operator>>=(const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& other) noexcept;

        #pragma endregion //!region assignment operators
        #pragma region increment decrement operators

        /**
         * @brief  pre-increment operator
         * 
         * @return constexpr GenericMatrix& 
         */
        inline constexpr
		GenericMatrix& 	operator++	() noexcept;

        /**
         * @brief pre-decrement operator
         * 
         * @return constexpr GenericMatrix& 
         */
        inline constexpr
		GenericMatrix& 	operator--	() noexcept;
        
        /**
         * @brief post-increment  operator
         * 
         * @return constexpr GenericMatrix 
         */
        inline constexpr
		GenericMatrix 	    operator++	(int) noexcept;

        /**
         * @brief post-decrement operator
         * 
         * @return constexpr GenericMatrix 
         */
        inline constexpr
		GenericMatrix 	    operator--	(int) noexcept;

        #pragma endregion //!increment decrement operators
        #pragma region convertor

        /**
         * @brief Converte generic vector to another generic vector type
         * @note use static_cast<> to call this function. Is use only if you try to downgrade generic vector like static_cast<Vec3f>(vec4f). Else use the constructor
         * @example `FoxMath::Vector::Vector<2, float> rhs = static_cast<FoxMath::Vector::Vector<2, float>>(vec)`
         * @tparam TLengthOther 
         * @tparam TTypeOther 
         * @return GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> 
         */
        template <size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
        [[nodiscard]] implicit constexpr inline
        operator GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>() const noexcept;

        #pragma endregion //!convertor
        #pragma endregion //!operators
    
    };

    #pragma region arithmetic operators

    /**
     * @brief unary plus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept;

    /**
     * @brief unary minus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator+(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, const GenericMatrix< TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& rhs) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator-(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, const GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther>& rhs) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator*(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator*(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator*(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator/(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator%(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise AND 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator&(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise OR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator|(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator^(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator<<(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief bitwise right shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator>>(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief bitwise NOT
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @return constexpr GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> 
     */
	template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
	[[nodiscard]] inline constexpr
    GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> operator~(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> vec) noexcept;

    #pragma endregion //!logical operators
    #pragma region logical operators
    
    // /**
    //  * @brief negation
    //  * 
    //  * @tparam TLength 
    //  * @param mat 
    //  * @return constexpr GenericMatrix<TLength, bool> 
    //  */
    // template <size_t TLength>
	// [[nodiscard]] inline constexpr
    // GenericMatrix<TLength, bool> operator!(GenericMatrix<TLength, bool> vec) noexcept;
	
    // /**
    //  * @brief AND
    //  * 
    //  * @tparam TLength 
    //  * @param lhs 
    //  * @param rhs 
    //  * @return constexpr GenericMatrix<TLength, bool> 
    //  */
    // template <size_t TLength, size_t TLengthOther>
	// [[nodiscard]] inline constexpr
    // GenericMatrix<TLength, bool> operator&&(GenericMatrix<TLength, bool> lhs, GenericMatrix<TLengthOther, bool> const& rhs) noexcept;

    // /**
    //  * @brief inclusive OR
    //  * 
    //  * @tparam TLength 
    //  * @param lhs 
    //  * @param rhs 
    //  * @return constexpr GenericMatrix<TLength, bool> 
    //  */
	// template <size_t TLength, size_t TLengthOther>
	// [[nodiscard]] inline constexpr
    // GenericMatrix<TLength, bool> operator||(GenericMatrix<TLength, bool> lhs, GenericMatrix<TLengthOther, bool> const& rhs) noexcept;
    
    #pragma endregion //!logical operators
    #pragma region comparision operators

    /**
     * @brief equal to
     * @note    if VECTOR_OPERATOR_EGALE_COMPARE_LENGTH is define, this function compare length of the both generic vector. Else it compare the both member.
     *          By default, VECTOR_OPERATOR_EGALE_COMPARE_LENGTH is not define
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
    template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
    [[nodiscard]] inline constexpr
    bool operator==(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator==(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat, TTypeScalar scalar) noexcept;

    /**
     * @brief equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator==(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept;

    /**
     * @brief not equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
        template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
    [[nodiscard]] inline constexpr
    bool operator!=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief not equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator!=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat, TTypeScalar scalar) noexcept;

    /**
     * @brief not equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator!=(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept;

    /**
     * @brief less than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
        template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
    [[nodiscard]] inline constexpr
    bool operator<(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief less than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat, TTypeScalar scalar) noexcept;

    /**
     * @brief less than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept;

    /**
     * @brief greater than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
        template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
    [[nodiscard]] inline constexpr
    bool operator>(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief greater than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat, TTypeScalar scalar) noexcept;

    /**
     * @brief greater than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept;

    /**
     * @brief less than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
        template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
    [[nodiscard]] inline constexpr
    bool operator<=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief less than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat, TTypeScalar scalar) noexcept;

    /**
     * @brief less than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<=(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept;

    /**
     * @brief greater than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return true 
     * @return false 
     */
        template <  size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention,
                size_t TRowSizeOther, size_t TColumnSizeOther, typename TTypeOther, EMatrixConvention TMatrixConventionOther>
    [[nodiscard]] inline constexpr
    bool operator>=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& lhs, GenericMatrix<TRowSizeOther, TColumnSizeOther, TTypeOther, TMatrixConventionOther> const& rhs) noexcept;

    /**
     * @brief greater than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param mat 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>=(GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat, TTypeScalar scalar) noexcept;

    /**
     * @brief greater than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param mat 
     * @return true 
     * @return false 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>=(TTypeScalar scalar, GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention> const& mat) noexcept;

    #pragma endregion //!comparision operators
    #pragma region stream operators

    /**
     * @brief output stream
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param out 
     * @param mat 
     * @return constexpr std::ostream& 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    [[nodiscard]] inline constexpr
    std::ostream& 	operator<<		(std::ostream& out, const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& vec) noexcept;

    /**
     * @brief input stream
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param out 
     * @param mat 
     * @return constexpr std::ostream& 
     */
    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention>
    [[nodiscard]] inline constexpr
    std::istream& 	operator>>		(std::istream& in, const GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>& vec) noexcept;

    #pragma endregion //!stream operators

    #include "GenericMatrix.inl"

    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Matrix = GenericMatrix<TRowSize, TColumnSize, TType, TMatrixConvention>;

    template <size_t TRowSize, size_t TColumnSize, typename TType, EMatrixConvention TMatrixConvention = EMatrixConvention::ColumnMajor>
    using Mat = Matrix<TRowSize, TColumnSize, TType, TMatrixConvention>;

} /*namespace FoxMath::Matrix*/