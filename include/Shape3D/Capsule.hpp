﻿//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 14 h 01

#ifndef _CAPSULE_H
#define _CAPSULE_H

#include "Shape3D/Volume.hpp"
#include "Vector/Vector.hpp"
#include "Shape3D/Segment.hpp"
#include "Shape3D/InfiniteCylinder.hpp"
#include "Shape3D/Sphere.hpp"
#include "Shape3D/Cylinder.hpp"

namespace FoxMath
{
    class Capsule : public Volume
    {
        public:

        #pragma region constructor/destructor

        Capsule ()					                = default;
        Capsule (const Capsule& other)			    = default;
        Capsule (Capsule&& other)				    = default;
        virtual ~Capsule ()				            = default;
        Capsule& operator=(Capsule const& other)    = default;
        Capsule& operator=(Capsule && other)		= default;

        explicit Capsule (const Vec3& center, const Vec3& normal, float height, float radius)
        :       Volume          {},
                segment_    {Vec3(center - normal * (height / 2.f)), Vec3(center + normal * (height / 2.f))},
                radius_     {radius}
        {}

        explicit Capsule (const Segment& segment, float radius)
        :       Volume          {},
                segment_    {segment},
                radius_     {radius}
        {}

        #pragma endregion //!constructor/destructor

        #pragma region methods

        /**
         * @brief Get the InfiniteCapsule object on the capsule
         * 
         * @return InfiniteCapsule 
         */
        InfiniteCylinder getInfiniteCylinder() const noexcept
        {
            return InfiniteCylinder(static_cast<Line>(segment_), radius_);
        }

        Cylinder BodyCylinder () const noexcept
        {
            return Cylinder(segment_.getPt1(), segment_.getPt2(), radius_);
        }

        Sphere LeftSphere () const noexcept
        {
            return Sphere(radius_, segment_.getPt1());
        }

        Sphere RightSphere () const noexcept
        {
            return Sphere(radius_, segment_.getPt2());
        }

        bool isInside(const Vec3& pt) const noexcept
        {
            return segment_.getDistanceWithPoint(pt) <= radius_;
        }

        Vec3 getCenter() const noexcept
        {
            return segment_.getCenter();
        }

        #pragma endregion //!methods

        #pragma region accessor

        const Segment&  getSegment      () const noexcept   { return segment_;}
        Segment&        getSegment      () noexcept         { return segment_;}
        const float&    getRadius       () const noexcept   { return radius_;}

        #pragma endregion //!accessor
    
        #pragma region mutator

        void setSegment  (const Segment& newSegment)    noexcept { segment_ = newSegment;}
        void setRadius   (const float& newRadius)       noexcept { radius_ = newRadius;}

        #pragma endregion //!mutator

        #pragma region convertor
        #pragma endregion //!convertor

        protected:

        #pragma region attribut

        Segment segment_;
        float   radius_;

        #pragma endregion //!attribut

        #pragma region static attribut
        #pragma endregion //! static attribut

        #pragma region methods
        #pragma endregion //!methods

        private:

    };

} /*namespace FoxMath*/

#endif //_CAPSULE_H