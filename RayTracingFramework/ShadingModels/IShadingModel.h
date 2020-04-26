#ifndef _SHADINGMODEL_RAYTRACINGFRAMEWORK
#define _SHADINGMODEL_RAYTRACINGFRAMEWORK
#include <RayTracingFramework\RayTracingPrerequisites.h>


namespace RayTracingFramework{
	class IShadingModel
	{
	protected:
	public:
		virtual ~IShadingModel() { ; }
		/**
		Given an Intersection (the closest to the camera, in ray), this method will compute a particular shading, depending on the object's properties.
		This is where most of the interesting stuff happens:
		- Shading due to position of the lights
		- recursive generation of secondary rays, to detect shadows, reflections, refractions...

		Attributes:
		@param ray: Contains all the intersections for the current ray. Usually, the method will only use the first intersection (ray.getClosestIntersection). The intersection contains all data to compute shading (3D position and orientation, material, etc).
		@param scene: Reference to the base scene. This will be necessary to compute secondary ray (e.g. check if a reflected ray hits any other object of the scene).
		@param recursiveLevel: The last parameter controls the recursion limit (we stop when recursiveLevel<0). The default parameter just computes primary rays. Hicher values enable reflections, refractions, etc...

		*/
		virtual RayTracingFramework::Colour computeShading(Ray& ray, RayTracingFramework::IScene& scene, int recursiveLevel = 0);
	};
};
#endif