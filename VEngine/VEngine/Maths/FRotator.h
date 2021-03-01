#pragma once
#include "../Config.h"
#include "Mathf.h"
namespace V {

	struct V_API FRotator {
		float Pitch;
		float Yaw;
		float Roll;
		FRotator(float p, float y, float r) :
			Pitch(p), Yaw(y), Roll(r) {
		}
		glm::vec3 getForwardVector() {
			glm::vec3 vec = glm::vec3(
				cos(Mathf::toRadian(Yaw)) * cos(Mathf::toRadian(Pitch)),
				sin(Mathf::toRadian(Pitch)),
				sin(Mathf::toRadian(Yaw)) * cos(Mathf::toRadian(Pitch))
			);
			return vec;
		}
	};

}
