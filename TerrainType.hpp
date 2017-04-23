#pragma once

#include "GlobalIncludes.hpp"
#include "Image.hpp"

class TerrainType {
public:
	TerrainType(json jsonSection);

	char id;
	std::shared_ptr<Image> image;	
};
