﻿//Project : Engine
//Editing by Gavelle Anthony, Nisi Guillaume, Six Jonathan
//Date : 2020-05-07 - 17 h 30

#ifndef _SEGMENT_SEGMENT_H
#define _SEGMENT_SEGMENT_H

#include "ShapeRelation/Intersection.hpp"
#include "Shape3D/Segment.hpp"
#include "Shape3D/Cylinder.hpp"

namespace FoxMath
{
    class SegmentCylinder
    {
        public:

        #pragma region constructor/destructor

        SegmentCylinder ()					                        = delete;
        SegmentCylinder (const SegmentCylinder& other)			    = delete;
        SegmentCylinder (SegmentCylinder&& other)				    = delete;
        virtual ~SegmentCylinder ()				                    = delete;
        SegmentCylinder& operator=(SegmentCylinder const& other)    = delete;
        SegmentCylinder& operator=(SegmentCylinder && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        static bool isSegmentCylinderCollided(const Segment& seg, const Cylinder& cylinder, Intersection& intersection);

        #pragma endregion //!static methods

        private :

        #pragma region static methods

        #pragma endregion //!static methods
    };

} /*namespace FoxMath*/

#endif //_SEGMENT_SEGMENT_H