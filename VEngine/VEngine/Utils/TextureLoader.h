#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "../../stb_image.h"
namespace V {

	static unsigned char* load_texture(
		const char* path,int* width,int* height,
		int* nrChannels,int STBI_rgb_alpha = 0) {
		stbi_set_flip_vertically_on_load(true);
		return stbi_load(path, width, height,
			nrChannels, STBI_rgb_alpha);
	}
	static void free_texture_mem(unsigned char* texture) {
		stbi_image_free(texture);
	}
}