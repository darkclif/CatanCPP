#include "Map.h"
#include "ResourceManager.h"

#include <iostream>
#include <queue>

Map::Map(): width( Map::MAP_WIDTH ), height(Map::MAP_HEIGHT)
{
	// Make a square map
	this->tiles.resize(height);
	for (int i = 0; i < height; i++) {
		tiles[i].resize(width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tiles[i][j] = Tile();
		}
	}

	// Prepare circle map to play
	initCircleMap( 3 );

	// TODO: Assign resource tiles at random
}

void Map::initCircleMap( int _radius ) {

	// Calculate center of map
	if (!( this->height % 2 || this->width % 2)) {
		std::cout << "CircleMapInit: Map heigh or width is even - some hexes will remain unused." << std::endl;
	}

	int x = this->width / 2;
	int y = this->height / 2;

	// Add center tile to queue and start spreading map 
	std::queue<sf::Vector2i> qTileToInit;

	tiles[x][y].setInitJump(1);
	qTileToInit.push( sf::Vector2i(x, y) );

	while ( !qTileToInit.empty() ) {
		sf::Vector2i lVector = qTileToInit.front();
		qTileToInit.pop();

		int lJump = getTile(lVector).getInitJump();

		// Set tile type 
		getTile(lVector).setType( Tile::TileType::BLANK );

		/* TODO: Add tile to waiting list - we must assign type and dice numbers */

		// Search for further tiles if current tile is not map edge
		if (getTile(lVector).getInitJump() < _radius) {
			for (int i = 1; i <= 6; i++) {
				bool lStatus;
				sf::Vector2i lNgVector = getNeighborTile( lStatus, lVector, i);

				// Add to queue if tile exist and have not been added yet 
				if (lStatus && getTile(lNgVector).getInitJump() == 0) {
					getTile(lNgVector).setInitJump( lJump + 1);
					qTileToInit.push( lNgVector);
				}
			}
		}

	}/* while*/

}

void Map::Show(sf::RenderWindow & _window, float _x, float _y)
{
	float MAP_SCALE = 0.2;

	// Load deafault tile texture to compute intervals
	sf::Texture* tmpTexture = ResourceManager::getInstance().getTexture("tile_texture_blank");
	float lTriangleA = (float)tmpTexture->getSize().y * 0.75 * MAP_SCALE;	// 1,5 * hex border 
	float lTriangleH = (float)tmpTexture->getSize().x * MAP_SCALE;			// 2   * height of triangle in hex

	float lWidth = _x;
	float lHeight = _y;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			// Draw tile
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

			// Draw number
			sf::Text lText;
			lText.setString( std::to_string( tiles[i][j].getInitJump() ) );

			lText.setFont(*( ResourceManager::getInstance().getFont("roboto") ));
			lText.setCharacterSize(24);
			lText.setFillColor( sf::Color::Red );
			lText.setPosition( sf::Vector2f(lWidth, lHeight ) );

			_window.draw( lText );

			lWidth += lTriangleH;
		}

		lWidth = _x - (lTriangleH / 2.0) * (i + 1);
		lHeight -= lTriangleA;
	}

}

Map::Map(int _width, int _height) : width{_width}, height{ _height }
{

}

sf::Vector2i Map::getNeighborTile(bool & _status, sf::Vector2i _sourceTile, int _number)
{
	sf::Vector2i lReturn( _sourceTile );
	_status = true;

	switch (_number) {
		case 1: lReturn.x++; lReturn.y++; break;
		case 2: lReturn.x++; break;
		case 3: lReturn.y--; break;
		case 4: lReturn.y--; lReturn.x--; break;
		case 5: lReturn.x--; break;
		case 6: lReturn.y++; break;
		default: break;
	}

	if (!(lReturn.x >= 0 && lReturn.x < this->width &&
		lReturn.y >= 0 && lReturn.y < this->height)) {
		_status = false;
	}

	return lReturn;
}

Map::~Map()
{
}

Tile & Map::getTile(sf::Vector2i _vector)
{
	return tiles[_vector.x][_vector.y];
}
