﻿//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 16 h 05

#ifndef _SEGMENT_CAPSULE_H
#define _SEGMENT_CAPSULE_H

#include "Vector/Vector.hpp"
#include "ShapeRelation/Intersection.hpp"
#include "Shape3D/Segment.hpp"
#include "GE/Core/Maths/Shape3D/Capsule.hpp"
#include "Shape3D/Cylinder.hpp"
#include "Shape3D/Sphere.hpp"

namespace FoxMath
{
    class SegmentCapsule
    {
        public:

        #pragma region constructor/destructor

        SegmentCapsule ()					                    = delete;
        SegmentCapsule (const SegmentCapsule& other)			= delete;
        SegmentCapsule (SegmentCapsule&& other)				    = delete;
        virtual ~SegmentCapsule ()				                = delete;
        SegmentCapsule& operator=(SegmentCapsule const& other)  = delete;
        SegmentCapsule& operator=(SegmentCapsule && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        static bool isSegmentCapsuleCollided(const Segment& seg, const Capsule& capsule, Intersection& intersection);

        #pragma endregion //!static methods

        private :

        #pragma region static methods

        static void detectSegmentPointPosition(const Segment& seg, const Capsule& capsule, int& outCodePt1, int& outCodePt2);

        static void checkCapsuleInfinitCylinderCollisionPoint(const Capsule& capsule, Intersection& intersection);

        static void checkLeftCapsuleSphereCollision (const Segment& seg, const Capsule& capsule, Intersection& intersection);

        static void checkRightCapsuleSphereCollision(const Segment& seg, const Capsule& capsule, Intersection& intersection);

        static bool pointIsBetweenCapsuleSegLimit(const Capsule& capsule, const Vec3& pt);

        #pragma endregion //!static methods


        #pragma region static attribut

        //OutCode for detect the position of a point with the capsule
        static const int INSIDE           = 0;  // 0000
        static const int LEFT_INTERNAL    = 9;  // 1001
        static const int LEFT_EXTERNAL    = 5;  // 0101
        static const int RIGHT_INTERNAL   = 10;  // 1010
        static const int RIGHT_EXTERNAL   = 6;  // 0110

        static const int ON_THE_LEFT_MASK  = 1;  // 0001
        static const int ON_THE_RIGHT_MASK = 2;  // 0010
        static const int ON_EXTERNAL_MASK  = 4;  // 0100
        static const int ON_INTERNAL_MASK  = 8;  // 1000

        #pragma endregion //!static attribut
    };

} /*namespace FoxMath*/

#endif //_SEGMENT_CAPSULE_H