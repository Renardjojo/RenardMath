/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-05 - 10 h 28
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

#include "Types/Implicit.hpp" //implicit
#include "Types/SFINAEShorthand.hpp" //IsArithmetic<TType>, IsSame, Pack
#include "Numeric/Limits.hpp" //isSame
#include "Angle/Angle.hpp" //Angle

#include <array> //std::array
#include <stddef.h> //sizt_t
#include <iostream> //ostream, istream
#include <cassert> //assert
#define _USE_MATH_DEFINES
#include <math.h> //sqrt, lerp (if c++ 2020) //TODO: only include if C++ 20 when own sqrt implemented
#include <stdexcept> //std::out_of_range

/*Only if c++ >= 2020*/
#if __cplusplus >= 201709L
#include <cstring> //std::memset
#include <type_traits> //std::is_constant_evaluated
#endif

namespace FoxMath
{
    /*Use of IsArithmetic*/
    template <size_t TLength, typename TType = float, 
                IsNotEqualTo<TLength, 0> = true, 
                IsArithmetic<TType> = true>
    class GenericVector;

    /*Specilisation of GenericVector class*/
    template <size_t TLength, typename TType>
    class GenericVector<TLength, TType>
    {
        private:
    
        protected:
    
        #pragma region attribut

        std::array<TType, TLength> m_data {};

        #pragma endregion //!attribut
    
        public:
    
        #pragma region constructor/destructor
    
        /**
         * @brief Default constructor, doesn't init the generic vector's member at zero to optimize class
         * 
         */
        implicit constexpr inline 
        GenericVector () noexcept                                   = default;

        implicit constexpr inline
        GenericVector (const GenericVector& other)			        = default;
        
        implicit constexpr inline 
        GenericVector (GenericVector&& other)				        = default;
        
        implicit inline
        ~GenericVector ()				                            = default;
        
        implicit constexpr inline 
        GenericVector& operator=(GenericVector const& other)		= default;
        
        implicit constexpr inline 
        GenericVector& operator=(GenericVector && other)			= default;
    
        /**
         * @brief Aggregate initialization
         * 
         * @note : If the number of initializer clauses is less than the number of members or initializer list is completely empty, the remaining members are value-initialized. 
         * If a member of a reference type is one of these remaining members, the program is ill-formed.
         * 
         * @example `FoxMath::Vector<2, int> vec (1, 1, 3)` or `FoxMath::Vector<2, int> vec (1, 2)`
         * 
         * @tparam T 
         * @tparam Sfinae IsSame 
         */
        template<typename... T, IsAllSame<TType, T...> = true,
        IsLessThanOrEqualTo<sizeof...(T), TLength> = true>
        explicit inline constexpr
        GenericVector (T... args) noexcept;

        /**
         * @brief Variadic templated constructor to init member with generic vector and scalar
         * @note Is use whene you try to upgrade generic vector with static cast like static_cast<Vec4f>(vec3f). Else use the convertor operator
         * @example `FoxMath::Vector<10, int> vect(FoxMath::Vector<5, int>(), 22, 31)`
         * @tparam TLengthOther 
         * @tparam TScalarArgs
         */
        template<size_t TLengthOther, typename... TScalarArgs, 
        IsAllSame<TType, TScalarArgs...> = true,
        IsLessThanOrEqualTo<sizeof...(TScalarArgs) + TLengthOther, TLength> = true,
        IsLessThan<TLengthOther, TLength> = true>
        explicit inline constexpr
        GenericVector (const GenericVector<TLengthOther, TType>& other, TScalarArgs... args) noexcept;

        #pragma endregion //!constructor/destructor
    
        #pragma region methods

        /**
         * @brief Fill generic vector's member with scalar value
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
        inline constexpr  
        GenericVector& fill (const TscalarType scalar) noexcept;

        /**
         * @brief Return squareLength of generic vector. More optimize to compare distance than length
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType squareLength () const noexcept;

        /**
         * @brief return magnitude of the generic vector 
         * 
         * @return constexpr TType 
         */
        //TODO: method not constexpr because it use std::sqrt. Replace it by my own function
        [[nodiscard]] inline constexpr
        TType length () const noexcept;

        /**
         * @brief Homogenize vector to the lower dimension
         * @note devise each component by the last
         * @example to convert vector 4 to vector 3 it must be homogenize to lose it fourth dimension
         * 
         * @return constexpr GenericVector& 
         */
        inline constexpr
		GenericVector& 	    homogenize	        () noexcept;

        /**
         * @brief Homogenize vector to the lower dimension
         * @note devise each component by the last
         * @example to convert vector 4 to vector 3 it must be homogenize to lose it fourth dimension
         * 
         * @return constexpr GenericVector& 
         */
        [[nodiscard]] inline constexpr
		GenericVector 	    getHomogenized	        () const noexcept;

        /**
         * @brief Normalize the generic vector. If the generic vector is null (all components are set to 0), nothing is done.
         * 
         * @return constexpr GenericVector& 
         */
        inline constexpr
		GenericVector& 	    normalize	        () noexcept;

        /**
         * @brief  Returns the normalized generic vector. If the generic vector is null (all components are set to 0), then generic vector zero is returned.
         * 
         * @return constexpr const GenericVector& 
         */
        [[nodiscard]] inline constexpr
        GenericVector      getNormalized		() const noexcept;

        /**
         * @brief Clamp the generic vector's length to max value
         * 
         * @param maxLength 
         * @return constexpr GenericVector& 
         */
        inline constexpr
        GenericVector&         clampLength         (TType maxLength) noexcept;

        /**
         * @brief Get the Clamped Length object
         * 
         * @param maxLength 
         * @return constexpr GenericVector 
         */
        [[nodiscard]] inline constexpr
        GenericVector         getClampedLength         (TType maxLength) const noexcept;

        /**
         * @brief Perform dot product with another generic vector
         * 
         * @param other 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType           dot		            (const GenericVector& other) const noexcept;

        /**
         * @brief perform cross product with another generic vector
         * 
         * @param other 
         * @return constexpr GenericVector& 
         */
        inline constexpr
        GenericVector&         cross	            (const GenericVector& other) noexcept;

        /**
         * @brief Get the Cross object
         * 
         * @param other 
         * @return constexpr GenericVector 
         */
        [[nodiscard]] inline constexpr
        GenericVector         getCross	            (const GenericVector& other) const noexcept;

        /**
         * @brief Performs a linear interpolation between 2 generic vectors of the same type.
         * 
         * @param other 
         * @param t 
         * @return constexpr GenericVector& 
         */
        inline constexpr
        GenericVector& 	    lerp		        (const GenericVector& other, TType t) noexcept;

        [[nodiscard]] inline constexpr
        GenericVector 	        getLerp		        (const GenericVector& other, TType t) const noexcept;

        /**
         * @brief Performs a reflection with a normal generic vector
         * 
         * @param normalNormalized : Normal must be normalized
         * @return constexpr GenericVector& 
         */
        inline constexpr
        GenericVector&         reflect		        (const GenericVector& normalNormalized) noexcept;

        /**
         * @brief Get the Reflection object
         * 
         * @param normalNormalized 
         * @return constexpr GenericVector 
         */
        [[nodiscard]] inline constexpr
        GenericVector 	        getReflection		 (const GenericVector& normalNormalized) const noexcept;

        /**
         * @brief Set the magnitude of the current generic vector
         * 
         * @param newLength 
         * @return constexpr GenericVector& 
         */
        inline constexpr
        GenericVector& 	    setLength		     (TType newLength) noexcept;

        /**
         * @brief return true if generic vector is colineaire this other generic vector. Comput cross product. If cross product is near of zero, generic vectors is colinear
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        [[nodiscard]] inline constexpr
		bool 	isColinearTo	(const GenericVector& other) const noexcept;

        /**
         * @brief return true if generic vector is perpendicular this other generic vector. Comput dot product. If dot product is near of zero, generic vectors is colinear
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        [[nodiscard]] inline constexpr
		bool 	isPerpendicularTo	(const GenericVector& other) const noexcept;

        /**
         * @brief Area correspond to the ares of parralelogram formed by the two generic vectors.
         * 
         * @param other 
         * @return TType 
         */
        [[nodiscard]] inline constexpr
		TType getParallelogramArea		(const GenericVector& other) const noexcept;

        /**
         * @brief Comput aera of triangle in function of 3 points
         * 
         * @param other 
         * @return TType 
         */
        [[nodiscard]] inline constexpr
		TType getTriangleArea		(const GenericVector& other) const noexcept;

        /**
         * @brief rotate generic vector around another unit generic vector. This function assert if axis is not unit
         * 
         * @param unitAxis 
         * @param angleRad 
         */
        inline constexpr
		GenericVector& rotateAroundAxis (const GenericVector& unitAxis, const Angle<EAngleType::Radian, TType>& angle) noexcept;

        /**
         * @brief Get the Rotation Around Axis object
         * 
         * @param unitAxis 
         * @param angleRad 
         * @return GenericVector 
         */
        [[nodiscard]] inline constexpr
		GenericVector getRotationAroundAxis (const GenericVector& unitAxis, const Angle<EAngleType::Radian, TType>& angle) const noexcept;

        /**
         * @brief Get the projection with another generic vector
         * 
         * @param other 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getScalarProjectionWith(const GenericVector& other) const noexcept;

        /**
         * @brief Get the rejection with another generic vector
         * 
         * @param other 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getScalarRejectionWith(const GenericVector& other) const noexcept;

        /**
         * @brief Get the GenericVector projection with another
         * 
         * @param other 
         * @return constexpr GenericVector 
         */
        [[nodiscard]] inline constexpr
		GenericVector getVectorProjectionWith(const GenericVector& other) const noexcept;

        /**
         * @brief Get the GenericVector rejection with another
         * 
         * @param other 
         * @return constexpr GenericVector 
         */
        [[nodiscard]] inline constexpr
		GenericVector getVectorRejectionWith(const GenericVector& other) const noexcept;

        #pragma endregion //!methods
    
        #pragma region static methods
        
        /**
         * @brief Get the vector dimension
         * 
         * @return constexpr const size_t& 
         */
        [[nodiscard]] inline static constexpr
		size_t 	getDimension () noexcept
        {
            return TLength;
        }

        /**
         * @brief perform dot product with both generic vector
         * 
         * @param lhs 
         * @param rhs 
         * @return constexpr TType 
         */
        [[nodiscard]] static inline constexpr
        TType           dot		            (const GenericVector& lhs, const GenericVector& rhs) noexcept
        {
            return lhs.dot(rhs); 
        }

        /**
         * @brief perform cross product with both generic vector
         * 
         * @param lhs 
         * @param rhs 
         * @return constexpr GenericVector
         */
        [[nodiscard]] static inline constexpr
        GenericVector         cross	            (const GenericVector& lhs, const GenericVector& rhs) noexcept
        {
            return lhs.getCross(rhs); 
        }


        /**
         * @brief 
         * 
         * @param lhs 
         * @param rhs : normalize normal
         * @return constexpr GenericVector 
         */
        [[nodiscard]] static inline constexpr
        GenericVector         reflect	            (const GenericVector& vec, const GenericVector& normalizedNormal) noexcept
        {
            return vec.getReflection(normalizedNormal);
        }


        /**
         * @brief 
         * 
         * @param lhs 
         * @param rhs 
         * @return constexpr GenericVector 
         */
        [[nodiscard]] static inline constexpr
        GenericVector         lerp	            (const GenericVector& vecStart, const GenericVector& vecEnd, TType t) noexcept
        {
            return vecStart.getLerp(vecEnd, t);
        }

        /**
         * @brief Comput aera of parallelogram in function of 3 points
         * 
         * @param pt1 
         * @param pt2 
         * @param pt3 
         * @return TType 
         */
        [[nodiscard]] static inline constexpr
		TType parallelogramArea		(const GenericVector& pt1, const GenericVector& pt2, const GenericVector& pt3) noexcept
        {
            return (pt2 - pt1).getParallelogramArea(pt3 - pt1);
        }

        /**
         * @brief Comput aera of triangle in function of 3 points
         * 
         * @param pt1 
         * @param pt2 
         * @param pt3 
         * @return TType 
         */
        [[nodiscard]] static inline constexpr
		TType triangleArea		(const GenericVector& pt1, const GenericVector& pt2, const GenericVector& pt3) noexcept
        {
            return (pt2 - pt1).getTriangleArea(pt3 - pt1);
        }

        #pragma endregion //!static methods

        #pragma region accessor

        /**
         * @brief   Returns a const reference to the data at index in the GenericVector
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericVector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * 
         * @param index 
         * @return constexpr const TType (avoid at([...]) = [...])
         */
        [[nodiscard]] inline constexpr
		const TType 	at (size_t index) const throw ();

        #pragma endregion //!accessor
    
        #pragma region mutator

        /**
         * @brief Set the Data a index
         * 
         * A similar member function, GenericsetDataAt, has the same behavior as this operator function,
         * except that GenericsetDataAt is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param index 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& setData(size_t index, TscalarType scalar) noexcept;

        /**
         * @brief Set the Data at index
         * 
         * The function automatically checks whether index is within the bounds of valid elements in the GenericVector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with function GenericsetData, that does not check against bounds.
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param index 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& setDataAt(size_t index, TscalarType scalar) throw ();


        #pragma endregion //!mutator
    
        #pragma region operator
        #pragma region member access operators

        /**
         * @brief Returns a reference to the element at position index in the GenericVector.
         * 
         * A similar member function, Genericat, has the same behavior as this operator function,
         * except that Genericat is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
         * 
         * Portable programs should never call this function with an argument index that is out of range,
         * since this causes undefined behavior.
         * 
         * @param index 
         * @return constexpr const TType (avoid vec[...] = [...])
         */
        [[nodiscard]] inline constexpr
		const TType 	    operator[]	(size_t index) const noexcept;

        #pragma endregion //!member access operators
        #pragma region  assignment operators

        /**
         * @brief fill the vector with scalar assigned
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return implicit constexpr& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		implicit inline constexpr
		GenericVector& operator=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator+=(TscalarType scalar) noexcept;

        /**
         * @brief addition assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator+=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator-=(TscalarType scalar) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator-=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator*=(TscalarType scalar) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator*=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator/=(TscalarType scalar) noexcept;

        /**
         * @brief division assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator/=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator%=(TscalarType scalar) noexcept;

        /**
         * @brief modulo assignment
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator%=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator&=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise AND assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator&=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator|=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise OR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator|=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator^=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise XOR assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator^=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator<<=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise left shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator<<=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TscalarType 
         * @tparam true 
         * @param scalar 
         * @return constexpr GenericVector& 
         */
        template<typename TscalarType, IsArithmetic<TscalarType> = true>
		inline constexpr
		GenericVector& operator>>=(TscalarType scalar) noexcept;

        /**
         * @brief bitwise right shift assignment 
         * 
         * @tparam TLengthOther 
         * @tparam TType 
         * @param other 
         * @return constexpr GenericVector& 
         */
        template <size_t TLengthOther, typename TTypeOther>
		inline constexpr
		GenericVector& operator>>=(const GenericVector<TLengthOther, TTypeOther>& other) noexcept;

        #pragma endregion //!region assignment operators
        #pragma region increment decrement operators

        /**
         * @brief  pre-increment operator
         * 
         * @return constexpr GenericVector& 
         */
        inline constexpr
		GenericVector& 	operator++	() noexcept;

        /**
         * @brief pre-decrement operator
         * 
         * @return constexpr GenericVector& 
         */
        inline constexpr
		GenericVector& 	operator--	() noexcept;
        
        /**
         * @brief post-increment  operator
         * 
         * @return constexpr GenericVector 
         */
        inline constexpr
		GenericVector 	    operator++	(int) noexcept;

        /**
         * @brief post-decrement operator
         * 
         * @return constexpr GenericVector 
         */
        inline constexpr
		GenericVector 	    operator--	(int) noexcept;

        #pragma endregion //!increment decrement operators
        #pragma region convertor

        /**
         * @brief Converte generic vector to another generic vector type
         * @note use static_cast<> to call this function. Is use only if you try to downgrade generic vector like static_cast<Vec3f>(vec4f). Else use the constructor
         * @example `FoxMath::Vector<2, float> rhs = static_cast<FoxMath::Vector<2, float>>(vec)`
         * @tparam TLengthOther 
         * @tparam TTypeOther 
         * @return GenericVector<TLengthOther, TTypeOther> 
         */
        template <size_t TLengthOther, typename TTypeOther>
        [[nodiscard]] implicit constexpr inline
        operator GenericVector<TLengthOther, TTypeOther>() const noexcept;

        #pragma endregion //!convertor
        #pragma endregion //!operators
    
    };

    #pragma region arithmetic operators

    /**
     * @brief unary plus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> const& vec) noexcept;

    /**
     * @brief unary minus 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator+(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator+(GenericVector<TLength, TType> lhs, const GenericVector< TLengthOther, TTypeOther>& rhs) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator-(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator-(GenericVector<TLength, TType> lhs, const GenericVector<TLengthOther, TTypeOther>& rhs) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator*(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator*(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator*(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator/(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator/(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief division
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator/(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator%(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator%(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief modulo
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator%(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    #pragma endregion //!arithmetic operators
    #pragma region logical operators
    
    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator&(GenericVector<TLength, TType> lhs, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise AND
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator&(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise AND 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator&(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator|(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise OR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator|(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise OR 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator|(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator^(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator^(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise XOR
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator^(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator<<(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator<<(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise left shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator<<(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise right shift
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator>>(GenericVector<TLength, TType> vec, TTypeScalar scalar) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator>>(TTypeScalar scalar, GenericVector<TLength, TType> vec) noexcept;

    /**
     * @brief bitwise right shift 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator>>(GenericVector<TLength, TType> lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief bitwise NOT
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @return constexpr GenericVector<TLength, TType> 
     */
	template <size_t TLength, typename TType>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, TType> operator~(GenericVector<TLength, TType> vec) noexcept;


    /**
     * @brief negation
     * 
     * @tparam TLength 
     * @param vec 
     * @return constexpr GenericVector<TLength, bool> 
     */
    template <size_t TLength>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, bool> operator!(GenericVector<TLength, bool> vec) noexcept;
	
    /**
     * @brief AND
     * 
     * @tparam TLength 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, bool> 
     */
    template <size_t TLength, size_t TLengthOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, bool> operator&&(GenericVector<TLength, bool> lhs, GenericVector<TLengthOther, bool> const& rhs) noexcept;

    /**
     * @brief inclusive OR
     * 
     * @tparam TLength 
     * @param lhs 
     * @param rhs 
     * @return constexpr GenericVector<TLength, bool> 
     */
	template <size_t TLength, size_t TLengthOther>
	[[nodiscard]] inline constexpr
    GenericVector<TLength, bool> operator||(GenericVector<TLength, bool> lhs, GenericVector<TLengthOther, bool> const& rhs) noexcept;
    
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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator==(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator==(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

    /**
     * @brief equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator==(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator!=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief not equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator!=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

    /**
     * @brief not equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator!=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator<(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief less than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

    /**
     * @brief less than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator>(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief greater than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

    /**
     * @brief greater than
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator<=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief less than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

    /**
     * @brief less than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator<=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

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
    template <size_t TLength, typename TType, size_t TLengthOther, typename TTypeOther>
    [[nodiscard]] inline constexpr
    bool operator>=(GenericVector<TLength, TType> const& lhs, GenericVector<TLengthOther, TTypeOther> const& rhs) noexcept;

    /**
     * @brief greater than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param vec 
     * @param scalar 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    [[nodiscard]] inline constexpr
    bool operator>=(GenericVector<TLength, TType> const& vec, TTypeScalar scalar) noexcept;

    /**
     * @brief greater than or equal to
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param scalar 
     * @param vec 
     * @return true 
     * @return false 
     */
    template <size_t TLength, typename TType, typename TTypeScalar, IsArithmetic<TTypeScalar> = true>
    inline constexpr
    bool operator>=(TTypeScalar scalar, GenericVector<TLength, TType> const& vec) noexcept;

    #pragma endregion //!comparision operators
    #pragma region stream operators

    /**
     * @brief output stream
     * 
     * @note : define std::setprecision(n) before calling this operator to define floating point prescision like : 
     * i.e. : std::cout << std::setprecision(4) << std::fixed  << vec; (don't forgot to include <iomanip>)
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param out 
     * @param vec 
     * @return constexpr std::ostream& 
     */
    template <size_t TLength, typename TType>
    inline constexpr
    std::ostream& 	operator<<		(std::ostream& out, const GenericVector<TLength, TType>& vec) noexcept;

    /**
     * @brief input stream
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param out 
     * @param vec 
     * @return constexpr std::ostream& 
     */
    template <size_t TLength, typename TType>
    [[nodiscard]] inline constexpr
    std::istream& 	operator>>		(std::istream& in, const GenericVector<TLength, TType>& vec) noexcept;

    #pragma endregion //!stream operators

    #include "GenericVector.inl"

    template <size_t TLength, typename TType  = float>
    using Vector = GenericVector<TLength, TType>;

    template <size_t TLength, typename TType  = float>
    using Vec = Vector<TLength, TType>;

} /*namespace FoxMath*/