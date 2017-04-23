#include "TerrainType.hpp"

TerrainType::TerrainType(json jsonSection) {
	id = jsonSection["id"].get<string>().at(0);
	image = std::shared_ptr<Image>(new Image(jsonSection["Image"].get<string>()));
}
