#ifndef _BOXGEOMETRY_RAYTRACINGFRAMEWORK
#define _BOXGEOMETRY_RAYTRACINGFRAMEWORK
#include <RayTracingFramework\RayTracingPrerequisites.h>
#include <RayTracingFramework\VirtualObject\IVirtualObject.h>
#include "IGeometry.h"
#include "Plane.h"

namespace RayTracingFramework {

	class Box : public IGeometry
	{
		glm::vec4 P, Q;		// Two points describing the box.
		RayTracingFramework::Plane top, bottom, right, left, front, back;		// 6 planes that make up the box.
	public:
		Box(glm::vec4 P, glm::vec4 Q);
		virtual bool testLocalCollision(RayTracingFramework::Ray& ray);
		void setOwner(RayTracingFramework::IVirtualObject* _owner);
	private:
		/**
		Computes a collision of a ray (in coords local to the box) with the box
		@param origin, direction: definition of the ray (origin point and unitary direction vector)
		@param t (Output parameter): Distance of the intersection point to the origin
		@param col_P (Output parameter): Point of intersection (point on the box where the ray hits the box)
		@param col_N (Output parameter): Normal of the box at the intersection point (... all points on a box share the same normal vector).
		*/
		bool testRayBoxCollision(RayTracingFramework::Ray& ray);
		bool pointInCube(glm::vec4 point);
	};
};
#endif