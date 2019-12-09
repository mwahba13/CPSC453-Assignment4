/**
 * @author	Andrew Robert Owens, Philmo Gu
 * @date 	2019-10-15.
 * @details Organization: Biological Modeling and Visualization research group
 * University of Calgary, Calgary, AB, Canada
 *
 * Contact:	arowens [at] ucalgary.ca
 * @copyright Copyright (c) 2019 ___ALGORITHMIC_BOTANY___. All rights reserved.
 *
 * @brief
 */

#include "ray_intersect.hpp"
#include "mat3f.hpp"

namespace geometry {

Hit::operator bool() const { return didIntersect; }

Hit intersect(Ray const &ray, Triangle const &triangle) {
	Hit hit;

	//algorithm for calculating triangle intersection as per the textbook
	math::Vec3f A = triangle.operator[](0);
	math::Vec3f B = triangle.operator[](1);
	math::Vec3f C = triangle.operator[](2);

	float a = triangle.a().x - triangle.b().x;
	float b = triangle.a().y - triangle.b().y;
	float c = triangle.a().z - triangle.b().z;

	float d = triangle.a().x - triangle.c().x;
	float e = triangle.a().y - triangle.c().y;
	float f = triangle.a().z - triangle.c().z;

	float g = ray.direction.x;
	float h = ray.direction.y;
	float i = ray.direction.z;

	float j = triangle.a().x - ray.origin.x;
	float k = triangle.a().y - ray.origin.y;
	float l = triangle.a().z - ray.origin.z;

	float M = a * (e*i - h * f) + b * (g*f - d * i) + c * (d*h - e * g);

	float beta = (j*(e*i - h * f) + k * (g*f - d * i) + l * (d*h - e * g))/M;
	float gamma = (i*(a*k - j * b) + h * (j*c - a * l) + g * (b*l - k * c)) / M;

	float t = (f*(a*k - j * b) + e * (j*c - a * l) + d * (b*l - k * c)) / M;


	/*
	math::Mat3f matA;
	matA.fill((A.x - B.x, A.x - C.x, ray.direction.x,
		A.y - B.y, A.y - C.y, ray.direction.y,
		A.z - B.z, A.z - C.z, ray.direction.z
		));



	
	math::Mat3f matT;
	matT.fill((A.x - B.x, A.x - C.x, A.x - ray.origin.x,
		A.y - B.y, A.y - C.y, A.y - ray.origin.y,
		A.z - B.z, A.z - C.z, A.z - ray.origin.z));
	float t = math::determinant(matT) / math::determinant(matA);

	math::Mat3f matBeta;
	matBeta.fill((A.x - ray.origin.x, A.x - C.x, ray.direction.x,
		A.y - ray.origin.y, A.y - C.y, ray.direction.y,
		A.z - ray.origin.z, A.z - C.z, ray.direction.z));

	float beta = math::determinant(matBeta) / math::determinant(matA);

	math::Mat3f matGamma;
	matGamma.fill((A.x - B.x, A.x - ray.origin.x, ray.direction.x,
		A.y - B.y, A.y - ray.origin.y, ray.direction.y,
		A.z - B.z, A.z - ray.origin.z, ray.direction.z));

	float gamma = math::determinant(matGamma) / math::determinant(matA);
	*/

	if (gamma < 0 || gamma > 1) {
		return hit;
	}
	if (beta < 0 || beta >(1 - gamma)) {
		return hit;
	}

	hit.didIntersect = true;
	hit.rayDepth = t;
	return hit;

	  /*

	  if (gamma < 0 || gamma > 1) {
		  hit.didIntersect = false;
		  return hit;
	  }
	  else {
		  math::Mat3f matBeta;
		  matBeta.fill((A.x - ray.origin.x, A.x - C.x, ray.direction.x,
			  A.y - ray.origin.y, A.y - C.y, ray.direction.y,
			  A.z - ray.origin.z, A.z - C.z, ray.direction.z));

		  float beta = math::determinant(matBeta) / math::determinant(matA);

		  if (beta < 0 || beta > (1 - gamma)) {
			  hit.didIntersect = false;
			  return hit;
		  }
		  else {
			  hit.didIntersect = true;
			  hit.rayDepth = t;
			  return hit;
		  }
	  }
	  */
  
  

  // TODO
  
}

Hit intersect(Ray const &ray, Sphere const &sphere) {
  Hit hit;
  hit.color = sphere.color;

  //algorithm for calculating sphere intersection as per the textbook
  math::Vec3f d = ray.direction;
  math::Vec3f e = ray.origin;
  math::Vec3f c = sphere.origin;
  float R = sphere.radius;

  float det = pow((d*(e - c)),2.0) - (d*d)*((e-c)*(e-c) - pow(R,2.0));

  

  if (det < 0) {
	  hit.didIntersect = false;
  }
  else if (det == 0) {
	  float t = (-d * (e - c)) / (d*d);
	  hit.didIntersect = true;
	  hit.rayDepth = t;
  }
  else {
	  float tPlus = (-d * (e - c) + det) / (d*d);
	  float tMinus = (-d * (e - c) - det) / (d*d);

	  if (tPlus < tMinus) {
		  hit.didIntersect = true;
		  hit.rayDepth = tPlus;
	  }
	  else {
		  hit.didIntersect = true;
		  hit.rayDepth = tMinus;
	  }
  }

  //TODO
  return hit;
}

Hit intersect(Ray const &r, Plane const &p) {
  Hit hit;

  hit.color = p.color;

  auto denom = r.direction * p.normal;
  if (std::abs(denom) < 1e-5f)
    return hit;

  auto t = ((p.origin - r.origin) * p.normal) / denom;

  if (t < 0.f)
    return hit;

  hit.didIntersect = true;
  hit.rayDepth = t;

  return hit;
}

} // namespace geometry
