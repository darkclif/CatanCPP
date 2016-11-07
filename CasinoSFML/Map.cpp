#include "Map.h"

#include "ResourceManager.h"
#include <iostream>

Map::Map(): width( Map::MAP_WIDTH ), height(Map::MAP_HEIGHT)
{
	// Prepare tiles
	this->tiles.resize(height);
	for (int i = 0; i < height; i++) {
		tiles[i].resize(width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tiles[i][j] = Tile();
		}
	}

}

void Map::CircleMapInit( int _radius, int _x, int _y) {

	// Calculate center of map
	if (this->height % 2 || this->width % 2) {
		std::cout << "CircleMapInit: Map heigh or width is odd - some hexes will remain unused." << std::endl;
	}

	int x = this->width / 2;
	int y = this->height / 2;


	/*
	while () {
		
	}
	*/
}

void Map::Show(sf::RenderWindow & _window, float _x, float _y)
{
	float MAP_SCALE = 0.4;

	// Load deafault tile texture to compute intervals
	sf::Texture* tmpTexture = ResourceManager::getInstance().getTexture("tile_texture_blank");
	float lTriangleA = (float)tmpTexture->getSize().y * 0.75 * MAP_SCALE;	// 1,5 * hex border 
	float lTriangleH = (float)tmpTexture->getSize().x * MAP_SCALE;			// 2   * height of triangle in hex

	float lWidth = _x;
	float lHeight = _y;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			std::string lTexName = tiles[i][j].getTextureName();
			
			sf::Sprite lTileSprite;
			lTileSprite.setTexture( *(ResourceManager::getInstance().getTexture(lTexName) ) );
			
			sf::Rect<int> lOrigin( lTileSprite.getTextureRect() );
			lOrigin.height /= 2;
			lOrigin.width /= 2;

			lTileSprite.setOrigin((float)lOrigin.width, (float)lOrigin.height );
			lTileSprite.setPosition( sf::Vector2f( lWidth, lHeight ) );
			lTileSprite.setScale( sf::Vector2f( MAP_SCALE, MAP_SCALE) );
			 
			_window.draw( lTileSprite );

			lWidth += lTriangleH;
		}

		lWidth = _x + (lTriangleH / 2.0) * (i + 1);
		lHeight += lTriangleA;
	}

}

Map::Map(int _width, int _height) : width{_width}, height{ _height }
{

}

Map::~Map()
{
}
