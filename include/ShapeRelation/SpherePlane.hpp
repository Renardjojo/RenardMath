﻿//Project : Engine
//Editing by Six Jonathan
//Date : 2020-06-07 - 14 h 13

#ifndef _SPHERE_PLANE_H
#define _SPHERE_PLANE_H

#include "GE/Core/Maths/Shape3D/Plane.hpp"
#include "GE/Core/Maths/Shape3D/Sphere.hpp"

namespace Engine::Core::Maths::ShapeRelation
{
    class SpherePlane
    {
        public:

        #pragma region constructor/destructor

        SpherePlane ()					                    = delete;
        SpherePlane (const SpherePlane& other)			    = delete;
        SpherePlane (SpherePlane&& other)				    = delete;
        virtual ~SpherePlane ()				                = delete;
        SpherePlane& operator=(SpherePlane const& other)    = delete;
        SpherePlane& operator=(SpherePlane && other)		= delete;

        #pragma endregion //!constructor/destructor

        #pragma region static methods

        static bool isSphereOnOrForwardPlanCollided(const Shape3D::Sphere& sphere, const Shape3D::Plane& plane);

        #pragma endregion //!static methods

        private :

        #pragma region static methods
        #pragma endregion //!static methods
    };

} /*namespace Engine::Core::Maths::ShapeRelation*/

#endif //_SPHERE_PLANE_H