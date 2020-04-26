#include "Sphere.h"
#include "RayTracingFramework\Ray.h"
#include "RayTracingFramework\VirtualObject\IVirtualObject.h"

RayTracingFramework::Sphere::Sphere(glm::vec4 P0, float r)
	: center(P0)
	, r(r)
{
	;
}

bool RayTracingFramework::Sphere::testLocalCollision(RayTracingFramework::Ray& ray) {
	//0. Transform origin and direction coordinates to local coordinates (Ray is described in World coordinates):
	glm::vec4 origin_local = owner->getFromWorldToObjectCoordinates()*ray.origin_InWorldCoords;
	glm::vec4 direction_local = owner->getFromWorldToObjectCoordinates()*ray.direction_InWorldCoords;
	//1. Compute intersection with plane (compute collision point and normal). 
	glm::vec4 collision_Point, collision_Normal;
	float t;
	if (testRaySphereCollision(origin_local, direction_local
		, t, collision_Point, collision_Normal)) {
		//2. Intersection! --> Add it to the result (ray).
		Ray::Intersection i1;
		i1.t_distance = t;
		i1.collidingObjectID = owner->getID();
		i1.collisionPoint_InObjectCoords = collision_Point;
		i1.collisionNormalVector_InObjectCoords = collision_Normal;
		//3. To transform from local (object) coords to world coordinates 
		i1.fromObjectToWorldCoords = owner->getFromObjectToWorldCoordinates();
		ray.addIntersection(i1);
		return true;
	}
	return false;

}

bool RayTracingFramework::Sphere::testRaySphereCollision(glm::vec4 origin, glm::vec4 direction
	, float& t, glm::vec4& col_P, glm::vec4& col_N)
{
	// vector from center to point under consideration
	glm::vec4 vecOP = origin - center;
	// origin: P0

	// quadratic equation, solving for t
	float a = glm::dot(direction, direction);
	float b = 2 * glm::dot(direction, vecOP);
	float c = glm::dot(vecOP, vecOP) - pow(r, 2);
	if (a == 0) {
		// leads to division by 0 and imaginary solution, which means no collision
		return false;
	}
	float t1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	float t2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	// only display the closest collision (smallest t)
	t = (t1 < t2) ? t1 : t2;

	col_P = origin + t*direction;	//According to parametric equation: P(t)=P0 + t * v
	glm::vec4 vecOQ = col_P - glm::vec4(0, 0, 0, 1);
	col_N = glm::normalize(vecOQ);	// Normal of the sphere = vector from center to point, but normalized
	return true;
}
