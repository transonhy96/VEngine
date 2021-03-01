#pragma once
#include "../Config.h"
#include <glm/glm.hpp>
namespace V {

	typedef glm::vec3 FVector;

	class V_API Mathf {
	public:
		static float toRadian(float degree) {
			return glm::radians(degree);
		}
	};

}