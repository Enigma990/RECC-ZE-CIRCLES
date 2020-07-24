#include "GameOver.h"

GameOver::GameOver()
{
	//Loading Font
	if (gameOverFont.loadFromFile("Assets/Beon-Regular.otf") == false)
	{
		std::cerr << "Font Loading Failed" << std::endl;
	}

	//Background Image
	if (!texBackground.loadFromFile("Assets/background.jpeg"))
	{
		std::cerr << "Background Image Loading Failed" << std::endl;
	}

	background.setTextureRect(sf::IntRect(0, 0, 800, 600));
	background.setPosition(0, 0);
	background.setTexture(texBackground);

	//Menu
	//Menu Option 1
	menu[0].setFont(gameOverFont);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Play Again");
	menu[0].setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / (MAXITEMS + 1) * 1));

	//Menu Option 2
	menu[1].setFont(gameOverFont);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Main Menu");
	menu[1].setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / (MAXITEMS + 1) * 2));

	//Menu Option 3
	menu[2].setFont(gameOverFont);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / (MAXITEMS + 1) * 3));
}

GameOver::~GameOver()
{
}

void GameOver::updateScore()
{
	currentScore.open("currentScore.txt");
	while (!currentScore.eof())
	{
		currentScore >> scoreText;
	}
	currentScore.close();

	score.setFont(gameOverFont);
	score.setCharacterSize(50);
	score.setPosition(sf::Vector2f(200, 300));
	score.setFillColor(sf::Color::White);

	score.setString(scoreText);
}

void GameOver::update(sf::Vector2f mPos, int& stateId)
{
	//Game Over Menu
	for (int i = 0; i < MAXITEMS; i++)
	{
		if (menu[i].getGlobalBounds().contains(mPos))
		{
			menu[i].setFillColor(sf::Color::Red);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				switch (i)
				{
				case 0:
					stateId = 1;		//Game State
					break;

				case 1:
					stateId = 0;		//Main Menu State
					break;

				case 2:
					stateId = -1;		//Exit State
					break;

				default:
					break;
				}
			}
		}
		else
		{
			menu[i].setFillColor(sf::Color::White);
		}
	}

	//Score Update
	updateScore();

}

void GameOver::draw(sf::RenderTarget& window)
{
	window.draw(background);
	window.draw(score);

	for (int i = 0; i < MAXITEMS; i++)
	{
		window.draw(menu[i]);
	}
}