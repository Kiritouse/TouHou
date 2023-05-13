#include "Map.h"
#include <graphics.h>
#include "LoadResources.h"
Map::Map() {
	mapY = 0;
}
void Map::update_MapPosition() {
	mapY++;
	if (mapY >= HEIGHT_MAP)mapY = 0;

}
void Map::update_MapImage() {
	putimage(0, mapY - HEIGHT_MAP, &background);
	putimage(0, mapY, &background);
}
void Map::update_Map() {
	update_MapPosition();
	//update_MapImage();
}

