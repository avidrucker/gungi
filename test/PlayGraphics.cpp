#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(750, 700), "My window");

	//avi finds & combines textures and sprites
	sf::Texture boardTexture;
	boardTexture.loadFromFile("C:/Users/avidr/Desktop/Gungi/GungiVS/GungiVS/master-tileset.png");
	int starting_x = 80;
	int starting_y = 80;
	int spacing_x = 64;
	int spacing_y = 64;
	int tile_width = 64;
	int tile_height = 64;

	srand(time(0)*(int)&tile_height);

	const int num_of_tiles = 81;
	sf::Sprite* all_tile_sprites[num_of_tiles];
	
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			all_tile_sprites[i*(9) + j] = new sf::Sprite(boardTexture);
			if(i % 2)
				all_tile_sprites[i*(9) + j]->setTextureRect(sf::IntRect(spacing_x*(j % 2)+spacing_x*(rand() % 4)*2, spacing_y*2, tile_width, tile_height)); //spacing_x*(j % 2), 0, tile_width, tile_height
			else
				all_tile_sprites[i*(9) + j]->setTextureRect(sf::IntRect(spacing_x*((j+1) % 2) + spacing_x*(rand() % 4) * 2, spacing_y * 2, tile_width, tile_height)); //(spacing_x*((j+1) % 2), 0, tile_width, tile_height
			all_tile_sprites[i*(9) + j]->move(starting_x + spacing_x*j, starting_y + spacing_y*i);
		}
	}

	//sf::Sprite tile_sprite;
	//sf::Sprite tile_sprite2;
	//tile_sprite.setTexture(boardTexture);
	//tile_sprite2.setTexture(boardTexture);
	//tile_sprite.setTextureRect(sf::IntRect(0, 0, tile_width, tile_height));
	//tile_sprite2.setTextureRect(sf::IntRect(spacing_x, 0, tile_width, tile_height));
	//tile_sprite.move(starting_x, starting_y);
	//tile_sprite2.move(starting_x + spacing_x, starting_y);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		for (int i = 0; i < num_of_tiles; ++i)
		{
			window.draw(*all_tile_sprites[i]); //avi
		}
		//window.draw(tile_sprite1); //avi
		//window.draw(tile_sprite2); //avi
		
		// end the current frame
		window.display();
	}

	return 0;
}