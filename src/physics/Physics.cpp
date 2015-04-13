#include "physics/Physics.h"

Physics::Physics(){
    physicsWorld = new PhysicsWorld(this);
}

Physics::~Physics(){

}

void Physics::update(float dt) {
    physicsWorld->update(dt);
}

PhysicsWorld *Physics::getWorld() {
    return this->physicsWorld;
}


// Intersection method from Real-Time Rendering and Essential Mathematics for Games


bool Physics::castRay(glm::vec3 rayOrigin, glm::vec3 rayDirection, Body* body, float& intersectionDistance) {
	glm::vec3 aabbMin = body->getBoundingBox()->minVertex;
	glm::vec3 aabbMax = body->getBoundingBox()->maxVertex;
	return this->castRay(rayOrigin, rayDirection, aabbMin, aabbMax, body->getEntity()->getTransformation(), intersectionDistance);
}

// Intersection method from Real-Time Rendering and Essential Mathematics for Games
bool Physics::castRay(glm::vec3 rayOrigin,        // Ray origin, in world space
			 glm::vec3 rayDirection,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
		//abbb_min, abb_max, ModelMatrix is the target
			 glm::vec3 aabbMin,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
		// aabb is Axis-aligned minimum bounding box
			 glm::vec3 aabbMax,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.

			 glm::mat4 modelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)

			 float& intersection_distance) {

	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBposition_worldspace(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = OBBposition_worldspace - rayOrigin;

	// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		glm::vec3 xaxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
		float e = glm::dot(xaxis, delta);
		float f = glm::dot(rayDirection, xaxis);

		if (fabs(f) > 0.001f){ // Standard case

			float t1 = (e + aabbMin.x) / f; // Intersection with the "left" plane
			float t2 = (e + aabbMax.x) / f; // Intersection with the "right" plane
			// t1 and t2 now contain distances betwen ray origin and ray-plane intersections

			// We want t1 to represent the nearest intersection,
			// so if it's not the case, invert t1 and t2
			if (t1>t2){
				float w = t1; t1 = t2; t2 = w; // swap t1 and t2
			}

			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if (t2 < tMax)
				tMax = t2;
			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if (t1 > tMin)
				tMin = t1;

			// And here's the trick :
			// If "far" is closer than "near", then there is NO intersection.
			// See the images in the tutorials for the visual explanation.
			if (tMax < tMin)
				return false;

		}
		else{ // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
			if (-e + aabbMin.x > 0.0f || -e + aabbMax.x < 0.0f)
				return false;
		}
	}

	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
	// Exactly the same thing than above.
	{
		glm::vec3 yaxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
		float e = glm::dot(yaxis, delta);
		float f = glm::dot(rayDirection, yaxis);

		if (fabs(f) > 0.001f){

			float t1 = (e + aabbMin.y) / f;
			float t2 = (e + aabbMax.y) / f;

			if (t1>t2){ float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else{
			if (-e + aabbMin.y > 0.0f || -e + aabbMax.y < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
	// Exactly the same thing than above.
	{
		glm::vec3 zaxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
		float e = glm::dot(zaxis, delta);
		float f = glm::dot(rayDirection, zaxis);

		if (fabs(f) > 0.001f){

			float t1 = (e + aabbMin.z) / f;
			float t2 = (e + aabbMax.z) / f;

			if (t1>t2){ float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else{
			if (-e + aabbMin.z > 0.0f || -e + aabbMax.z < 0.0f)
				return false;
		}
	}
	intersection_distance = tMin;
	return true;

}

