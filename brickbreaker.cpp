#include<iostream>
#include<sstream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
using namespace sf;

const int col = 12;
const int row = 6;

void bricks(double &rec_pos_x,double &rec_pos_y,double &rec_width,double &rec_height,bool destroy[][col],RectangleShape rectangle[][col]) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			rectangle[i][j].setSize(Vector2f(rec_width, rec_height));
			if (i % 2 == 0) {
				if (j % 2 == 0)
					rectangle[i][j].setFillColor(Color::Yellow);
				else
					rectangle[i][j].setFillColor(Color::Red);
			}
			else {
				if (j % 2 == 0)
					rectangle[i][j].setFillColor(Color::Red);
				else
					rectangle[i][j].setFillColor(Color::Yellow);
			}
			rectangle[i][j].setPosition(rec_pos_x + (j * (rec_width + 10)), rec_pos_y + (i * (rec_height + 10)));
			destroy[i][j] = true;
		}
	}
}

void reset()
{
	double rec_pos_x = 0, rec_pos_y = 50;
	double rec_width = 120, rec_height = 30;
	RectangleShape rectangle[row][col];
	bool destroy[row][col];
	bricks(rec_pos_x, rec_pos_y, rec_width, rec_height, destroy, rectangle);
}

int main()
{
	Music music, music2;
	music.openFromFile("brick.mp3");
	music2.openFromFile("game.mp3");
	music2.play();

	const double Width = 1500, Height = 1000;
	RenderWindow window(VideoMode(Width, Height), "Brick Breaker");

	CircleShape circle;
	double x = 500, y = 500;
	circle.setRadius(10);
	circle.setFillColor(Color::Cyan);
	circle.setPosition(x, y);

	int score = 0, count = 0;
	double rec_pos_x = 0, rec_pos_y = 50;
	double rec_width = 120, rec_height = 30;
	RectangleShape rectangle[row][col];
	bool destroy[row][col];
	bricks(rec_pos_x, rec_pos_y, rec_width, rec_height, destroy, rectangle);

	Font font;
	font.loadFromFile("arial.ttf");
	Text text, text2, text3, text4, text5, text6, text7, text8, text9, text10;
	text.setFont(font);
	text.setCharacterSize(100);
	text.setString("BRICK BREAKER");
	text.setFillColor(Color::Red);
	text.setPosition(400, 10);

	text2.setFont(font);
	text2.setCharacterSize(70);
	text2.setString("Play Game");
	text2.setFillColor(Color::Green);
	text2.setPosition(550, 200);

	text3.setFont(font);
	text3.setCharacterSize(70);
	text3.setString("Scores");
	text3.setFillColor(Color::Green);
	text3.setPosition(550, 300);

	text4.setFont(font);
	text4.setCharacterSize(70);
	text4.setString("Load Game");
	text4.setFillColor(Color::Green);
	text4.setPosition(550, 400);

	text5.setFont(font);
	text5.setCharacterSize(70);
	text5.setString("Controls");
	text5.setFillColor(Color::Green);
	text5.setPosition(550, 500);

	text6.setFont(font);
	text6.setCharacterSize(70);
	text6.setString("About Game");
	text6.setFillColor(Color::Green);
	text6.setPosition(550, 600);

	text7.setFont(font);
	text7.setCharacterSize(40);
	text7.setString("Score: ");
	text7.setFillColor(Color::White);
	text7.setPosition(5, 2);

	text8.setFont(font);
	text8.setCharacterSize(40);
	text8.setFillColor(Color::White);
	text8.setPosition(100, 2);

	text9.setFont(font);
	text9.setCharacterSize(150);
	text9.setString("Game Over");
	text9.setFillColor(Color::Red);
	text9.setPosition(Width/2-300, Height/2-200);

	text10.setFont(font);
	text10.setCharacterSize(40);
	text10.setString("Press ESC to return to menu");
	text10.setFillColor(Color::Magenta);
	text10.setPosition(Width / 2 - 300+100, Height / 2 - 200+300);

	std::stringstream ss;

	Texture t1;
	t1.loadFromFile("green.png");

	Sprite s1(t1);
	double s1pos_x = 700, s1pos_y = 900;
	s1.setScale(10, 1);
	s1.setPosition(s1pos_x, s1pos_y);

	bool startgame = false;
	bool right = false, left = false;
	bool gameover = false, back = false;

	double ballSpeedX = 0.4, ballSpeedY = 0.5;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					if (text2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
						startgame = true;
				}
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.scancode == Keyboard::Scan::Right) {
					right = true;
					left = false;
				}
				else if (event.key.scancode == Keyboard::Scan::Left) {
					right = false;
					left = true;
				}
				if (event.key.scancode == Keyboard::Scan::Escape) {
					back = true;
				}
			}
		}

		if (right) {
			s1pos_x += 0.6;
			s1.setPosition(s1pos_x, s1pos_y);
		}
		else if (left) {
			s1pos_x -= 0.6;
			s1.setPosition(s1pos_x, s1pos_y);
		}

		// Wall collision of player
		if (s1pos_x <= 0) {
			s1pos_x = 1;
			s1.setPosition(s1pos_x, s1pos_y);
		}
		else if (s1pos_x >= 1350) {
			s1pos_x = 1349;
			s1.setPosition(s1pos_x, s1pos_y);
		}

		//ball movement
		if (startgame) {

			x += ballSpeedX;
			y += ballSpeedY;

			// Ball collision with window boundaries
			if (x <= 0 || x >= Width) {
				ballSpeedX = -ballSpeedX;
			}
			if (y <= 0 ) {
				ballSpeedY = -ballSpeedY;
			}
			if (y >= Height) {
				gameover = true;
			}

			// Ball collision with paddle

		    /*if (circle.getGlobalBounds().intersects(s1.getGlobalBounds())) {
				music2.play();
			}*/

			if (s1.getGlobalBounds().contains(x, y)) {
				ballSpeedY = -ballSpeedY;
			}

			//ball collision with bricks
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if ( destroy[i][j] && rectangle[i][j].getGlobalBounds().contains(x, y)) {
						music.play();
						ballSpeedY = -ballSpeedY;
						destroy[i][j] = false;
						ss.str("");
						score++;
						ss << score;
						text8.setString(ss.str());
					}
				}
			}

			circle.setPosition(x, y);
		}

		//Endgame
		if (gameover) {
			window.clear();
			window.draw(text9);
			window.draw(text10);
			window.display();
			//reset
			if (back) {
				gameover = false;
				startgame = false;
				back = false;
				music2.play();
				x = 500, y = 500;
				circle.setPosition(x, y);
				score = 0;
				count = 0;
				reset();
			}
		}
		//Play game
		else if (startgame) {
			music2.pause();
			window.clear();
			window.draw(text7);
			window.draw(text8);
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (destroy[i][j])
						window.draw(rectangle[i][j]);
				}
			}
			window.draw(s1);
			window.draw(circle);
			window.display();
	        
			if (count == 0) {
				sf::sleep(sf::seconds(1));
				count++;
			}
		}
		//Menu
		else if (!startgame) {
			window.clear();
			window.draw(text);
			window.draw(text2);
			window.draw(text3);
			window.draw(text4);
			window.draw(text5);
			window.draw(text6);
			window.display();
		}
	}

	return 0;
}