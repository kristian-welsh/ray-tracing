#include "Box.h"
#include "Math.h"
#include "RayTracingFramework\Ray.h"
#include "RayTracingFramework\VirtualObject\IVirtualObject.h"

RayTracingFramework::Box::Box(glm::vec4 P, glm::vec4 Q)
	: P(P)
	, Q(Q)
	, top(Q, glm::vec4(0, 1, 0, 0))
	, bottom(P, glm::vec4(0, -1, 0, 0))
	, right(Q, glm::vec4(1, 0, 0, 0))
	, left(P, glm::vec4(-1, 0, 0, 0))
	, front(Q, glm::vec4(0, 0, 1, 0))
	, back(Q, glm::vec4(0, 0, -1, 0))
{
}

void RayTracingFramework::Box::setOwner(RayTracingFramework::IVirtualObject* _owner) {
	owner = _owner;
	top.setOwner(owner);
	bottom.setOwner(owner);
	right.setOwner(owner);
	left.setOwner(owner);
	front.setOwner(owner);
	back.setOwner(owner);
}

bool RayTracingFramework::Box::testLocalCollision(RayTracingFramework::Ray& ray) {
	//0. Transform origin and direction coordinates to local coordinates (Ray is described in World coordinates):
	glm::vec4 origin_local = owner->getFromWorldToObjectCoordinates()*ray.origin_InWorldCoords;
	glm::vec4 direction_local = owner->getFromWorldToObjectCoordinates()*ray.direction_InWorldCoords;
	//1. Compute intersection with box (compute collision point and normal). 
	glm::vec4 collision_Point, collision_Normal;
	float t;


	if (testRayBoxCollision(ray)) {
		return true;
	}
	return false;

}

bool RayTracingFramework::Box::pointInCube(glm::vec4 point) {
	glm::vec4 min = P;
	glm::vec4 max = Q;
	if (min.x > round(point.x) || round(point.x) > max.x) {
		return false;
	}
	if (min.y > round(point.y) || round(point.y) > max.y) {
		return false;
	}
	if (min.z > round(point.z) || round(point.z) > max.z) {
		return false;
	}
	return true;
}

bool RayTracingFramework::Box::testRayBoxCollision(RayTracingFramework::Ray& ray)
{
	
	top.testLocalCollision(ray);
	bottom.testLocalCollision(ray);
	right.testLocalCollision(ray);
	left.testLocalCollision(ray);
	front.testLocalCollision(ray);
	back.testLocalCollision(ray);

	if (ray.intersections.size() > 0) {
		RayTracingFramework::Ray::Intersection curClosest;
		
		curClosest = ray.getClosestIntersection();
		while (!pointInCube(curClosest.collisionPoint_InObjectCoords) && curClosest.t_distance != FLT_MAX && curClosest.collidingObjectID == owner->getID()) {
			ray.discardClosestIntersection();
			curClosest = ray.getClosestIntersection();
		}
		if (curClosest.t_distance != FLT_MAX) {
			return true;
		}
	}
	return false;
}
