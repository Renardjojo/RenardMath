/*
 * Project : FoxMath
 * Editing by Six Jonathan
 * Date : 2020-08-11 - 10 h 14
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

#include <array>
#include <limits>
#include "Types/SFINAEShorthand.hpp" //Type::IsArithmetic<TType>
#include "Vector/Vector3.hpp" //Vector::Vector3<TType>
#include "Numeric/Limits.hpp" //Vector::Vector3<TType>
#include "Angle/Angle.hpp" //Angle<Angle::EAngleType::Radian, TType>

namespace FoxMath::Quaternion
{
    /*Use of IsArithmetic*/
    template <typename TType = float, Type::IsArithmetic<TType> = true>
    class Quaternion;

    template <typename TType>
    class Quaternion<TType>
    {
        private:
    
        public:
            
        #pragma region attribut

        union
        {
            struct
            {
                TType m_x;
                TType m_y;
                TType m_z;
                TType m_w;
            };

            Vector::Vector3<TType>  m_xyz;
            std::array<TType, 4>    m_data {};
        };
        
        #pragma endregion //!attribut
    
        #pragma region static attribut
        #pragma endregion //! static attribut
    
        #pragma region methods

        #pragma endregion //!methods
    
        public:
    
        #pragma region constructor/destructor
    
        Quaternion () noexcept				                        = default;

        Quaternion (const Quaternion& other) noexcept				= default;

        Quaternion (Quaternion&& other) noexcept				    = default;

        ~Quaternion () noexcept				                        = default;
        
        Quaternion& operator=(Quaternion const& other) noexcept	    = default;

        Quaternion& operator=(Quaternion && other) noexcept         = default;

        /**
         * @brief Create quaternion based on axis and angle
         * 
         */
        explicit inline constexpr
        Quaternion (Vector::Vector3<TType> axis, Angle::Angle<Angle::EAngleType::Radian, TType> angle = Angle::Angle<Angle::EAngleType::Radian, TType>(0)) noexcept;
    
        /**
         * @brief Create quaternion based on it's paramter
         * 
         */
        explicit inline constexpr
        Quaternion (TType x, TType y, TType z, TType w) noexcept;

        #pragma endregion //!constructor/destructor
    
        #pragma region methods
        
        /**
         * @brief Get the Squared Magnitude of the quaternion
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getSquaredMagnitude() const noexcept;

        /**
         * @brief Get the Magnitude of the quation
         * 
         * @return constexpr TType 
         */
        [[nodiscard]] inline constexpr
        TType getMagnitude() const noexcept;

        /**
         * @brief Check if quaternion squared magnitude is less than epsilon. Quaternion can express rotaiton only if it is unit
         * 
         * @param epsilon 
         * @return true 
         * @return false 
         */
        [[nodiscard]] inline constexpr
        bool isRotation(TType epsilon = std::numeric_limits<TType>::epsilon()) const noexcept;

        /**
         * @brief Normalize the quaternion
         * 
         * @return constexpr Quaternion& 
         */
        [[nodiscard]] inline constexpr
        Quaternion& normalize() noexcept;

        /**
         * @brief Perfgorm conjugate of the quaternion : q4 - iq1 - jq2 - kq3
         * 
         * @return constexpr Quaternion& 
         */
        [[nodiscard]] inline constexpr
        Quaternion& conjugate() noexcept;

        /**
         * @brief Compute the angle of the quaternion
         * 
         * @return constexpr Angle::Angle<Angle::EAngleType::Radian, TType> 
         */
        [[nodiscard]] inline constexpr
        Angle::Angle<Angle::EAngleType::Radian, TType> getAngle() const noexcept;

        /**
         * @brief Compute the axis of the quaternion
         * 
         * @return constexpr Vector::Vector3<TType> 
         */
        [[nodiscard]] inline constexpr
        Vector::Vector3<TType> getAxis() const noexcept;

        #pragma endregion //!methods
    
        #pragma region accessor

        [[nodiscard]] inline constexpr
        TType getX() const noexcept { return m_x; }

        [[nodiscard]] inline constexpr
        TType getY() const noexcept { return m_y; }

        [[nodiscard]] inline constexpr
        TType getZ() const noexcept { return m_z; }

        [[nodiscard]] inline constexpr
        TType getW() const noexcept { return m_w; }

        [[nodiscard]] inline constexpr
        Vector::Vector3<TType> getXYZ() const noexcept { return m_xyz; }

        #pragma endregion //!accessor
    
        #pragma region mutator
        #pragma endregion //!mutator
    
        #pragma region operator

        #pragma region assignment operators

        /**
         * @brief addition assignment 
         * 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeOther>
		inline constexpr
		Quaternion& operator+=(const Quaternion<TTypeOther>& other) noexcept;

        /**
         * @brief subtraction assignment 
         * 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeOther>
		inline constexpr
		Quaternion& operator-=(const Quaternion<TTypeOther>& other) noexcept;

        /**
         * @brief multiplication assignment 
         * 
         * @tparam TTypeOther 
         * @param other 
         * @return constexpr Quaternion& 
         */
        template <typename TTypeOther>
		inline constexpr
		Quaternion& operator*=(const Quaternion<TTypeOther>& other) noexcept;

        /**
         * @brief multiplication with a scalar number
         * 
         * @param scalar 
         * @return constexpr Quaternion& 
         */
		inline constexpr
		Quaternion& operator*=(TType scalar) noexcept;

        #pragma endregion //!assignment operators
        #pragma endregion //!operator
    
        #pragma region convertor
        #pragma endregion //!convertor    
    };

    #pragma region arithmetic operators

    /**
     * @brief unary plus 
     * 
     * @tparam TType 
     * @param quat 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator+(const Quaternion<TType>& quat) noexcept;

    /**
     * @brief unary minus 
     * 
     * @tparam TType 
     * @param quat 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator-(const Quaternion<TType>& quat) noexcept;

    /**
     * @brief addition 
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeOther>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator+(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept;

    /**
     * @brief subtraction
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeOther>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator-(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept;

    /**
     * @brief multiplication
     * 
     * @tparam TLength 
     * @tparam TType 
     * @param lhs 
     * @param rhs 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeOther>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator*(Quaternion<TType> lhs, const Quaternion<TTypeOther>& rhs) noexcept;

    /**
     * @brief multiplication of quaternion with a scale
     * 
     * @tparam TType 
     * @tparam TTypeScalar 
     * @param quat 
     * @param scalar 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator*(Quaternion<TType> quat, TTypeScalar scalar) noexcept;

    /**
     * @brief multiplication of quaternion with a scale
     * 
     * @tparam TType 
     * @tparam TTypeScalar 
     * @param scalar 
     * @param quat 
     * @return constexpr Quaternion<TType> 
     */
	template <typename TType, typename TTypeScalar, Type::IsArithmetic<TTypeScalar> = true>
	[[nodiscard]] inline constexpr
    Quaternion<TType> operator*(TTypeScalar scalar, Quaternion<TType> quat) noexcept;


    #pragma endregion //!arithmetic operators

    #pragma region stream operators

    /**
     * @brief output stream
     * 
     * @tparam TType 
     * @param out 
     * @param angle 
     * @return constexpr std::ostream& 
     */
    template <typename TType>
    [[nodiscard]] inline constexpr
    std::ostream& 	operator<<		(std::ostream& out, const Quaternion<TType>& quaternion) noexcept;

    #pragma endregion //!stream operators

    #include "Quaternion.inl"

} /*namespace FoxMath::Quaternion*/
