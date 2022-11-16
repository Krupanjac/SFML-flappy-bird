#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>
#include <string>

using namespace sf;
int flag1=0,flag2=0;
CircleShape bird;
int score=0;
RectangleShape cevi[2];


char CircleRecteSudar(RectangleShape &c) {
	float r = bird.getRadius();
	float bx = bird.getPosition().x + r;
	float by = bird.getPosition().y + r;
	Vector2f tpos, tsize;\

	tpos = c.getPosition();
	tsize = c.getSize();

	if (bx > tpos.x && bx < (tpos.x + tsize.x) && by > tpos.y && by < (tpos.y + tsize.y))
		return 1;
	else 
		return 0; 
}

char sudar(RectangleShape &c1, RectangleShape &c2)
{
	if (CircleRecteSudar(c1)) return 1;
	if (CircleRecteSudar(c2)) return 1;
	if (CircleRecteSudar(cevi[0])) return 1;
	if (CircleRecteSudar(cevi[1])) return 1;

	if(bird.getPosition().y>510 || bird.getPosition().y<0) return 1;

	return 0;
	
}

const float GRAVITY = 0.0009;
float visina, dh;

void reset() {
	visina=rand()%(350-100+1)+100;

	cevi[0].setSize(Vector2f(45,visina));
	cevi[1] = cevi[0];
	cevi[0].setPosition(480,550-visina);
	cevi[1].setPosition(480+217.5+45,550-visina);
	bird.setPosition(235, 220);

	dh = 0;	
	while(1) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) return;
		if (Keyboard::isKeyPressed(Keyboard::Escape)) exit(0);
	}

}

int main () {
	float s1=0.05,s2=0.08;
	Sprite oblak;
	Sprite oblak2;
	Text text;
	Texture texture, tica_tx, cev_tx,oblak_tx;
	Font font;
texture.setSmooth(true);

if(!oblak_tx.loadFromFile("IMG/oblak.png")){
	exit(0);
}
oblak.setTexture(oblak_tx);

oblak.setScale(sf::Vector2f(0.3f,0.3f));
	if(!texture.loadFromFile("IMG/nebo.png")){
        fprintf(stderr, "lol\n");
    }

	oblak2.setTexture(oblak_tx);
	oblak2.setScale(sf::Vector2f(0.2f,0.2f));
	oblak2.setPosition(520,0);

    tica_tx.loadFromFile("IMG/tica.png");
    bird.setTexture(&tica_tx);

    cev_tx.loadFromFile("IMG/cigla.jpg",IntRect(0,0,100,150));
    cevi[0].setTexture(&cev_tx);
   cevi[1].setTexture(&cev_tx);

    Sprite background(texture);
    background.setPosition(0,0);


	font.loadFromFile("FONT/iomanoid.ttf");
	text.setFillColor(Color::Black);
	text.setFont(font);
	text.setCharacterSize(50);
	text.setPosition(240,5);
	srand(time(0));

	RenderWindow window(VideoMode(480,550),"TICA 1.01");

	Event event;

	visina=rand()%(350-100+1)+100;
oblak.setPosition(480,0);
	cevi[0].setSize(Vector2f(45,visina));
	cevi[1] = cevi[0];
	cevi[0].setPosition(480,550-visina);
	cevi[1].setPosition(480+217.5+45,550-visina);

	bird.setRadius(20);
	bird.setPosition(235, 220);

	dh = 0;

	window.setKeyRepeatEnabled(false);




	while(window.isOpen()){
		text.setString(std::to_string(score));

		RectangleShape cev1, cev2;

		while(window.pollEvent(event)){

			if(event.type==Event::Closed){
				window.close();
			}
				if(event.type==Event::KeyPressed){

					if(event.key.code==Keyboard::Escape){
						window.close();

					} else if (event.key.code==Keyboard::Space){
						dh = -0.47;
					}
				}
		}

		dh += GRAVITY;
		bird.move(0, dh);

		if (cevi[0].getPosition().x <= -45){
			visina=rand()%(350-100+1)+100;

			cevi[0].setPosition(480, 550-visina);
			cevi[0].setSize(Vector2f(45,visina));

			score++;
		}

		if (cevi[1].getPosition().x <= -45){
			visina=rand()%(350-100+1)+100;
			cevi[1].setPosition(480, 550-visina);
			cevi[1].setSize(Vector2f(45,visina));
			score++;
		}
		if(oblak.getPosition().x < -200){
			visina=rand()%(3-1+1)+1;
			oblak.setScale(sf::Vector2f(visina/10.f,visina/10.f));
			oblak.setPosition(480,0);
			if(visina==3){
				s1=0.05;
			}
			else if(visina==2){
				s1=0.07;
			}
			else{
				s1=0.08;
			}
		}
			if(oblak2.getPosition().x < -200){
			visina=rand()%(3-1+1)+1;
			oblak2.setScale(sf::Vector2f(visina/10.f,visina/10.f));
			oblak2.setPosition(520,0);
					if(visina==3){
				s2=0.05;
			}
			else if(visina==2){
				s2=0.07;
			}
			else{
				s2=0.08;
			}
		}
		oblak.move(-s1,0);
		oblak2.move(-s2,0);
		cevi[0].move(-0.09,0);
		cevi[1].move(-0.09,0);
		cev1 = cevi[0];
		cev2 = cevi[1];
		cev1.setSize(Vector2f(45,400));
		cev1.move(0, - cev1.getSize().y - 135);
		cev2.setSize(Vector2f(45,400));
		cev2.move(0, - cev2.getSize().y - 135);

		if (sudar(cev1, cev2)){
			score=0;

	text.setString("U DED M8");
	text.setFont(font);
	text.setPosition(130,225);
	text.setCharacterSize(60);
	window.draw(text);
	window.display();
	

			reset();

				text.setCharacterSize(50);
	text.setPosition(240,5);
		}

		text.setString(std::to_string(score));

		window.clear();
		 window.draw(background);
		 window.draw(oblak);
		 window.draw(oblak2);

		window.draw(bird);
		window.draw(cevi[0]);
		window.draw(cevi[1]);
		window.draw(cev1);
		window.draw(cev2);
		window.draw(text);
		window.display();

	}	

	return 0;
}
