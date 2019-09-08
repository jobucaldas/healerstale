#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

using namespace sf;

typedef struct {
	float ox;
	float oy;
	float x;
	float y;
	int dir;
	int en;
	Sprite sprite;
	IntRect* rect;
} bullet;

typedef struct {
	int en;
	float x;
	float y;
	Sprite sprite;
	float hp;
	int line;
	int type;
	IntRect* rect;
} mnst;




typedef struct{
	int en;
	bullet b;
	float x;
	float y,py;
	float wy;
	int der;
	Sprite sprite;
	float hp;
	int line;
	int dir;
	mnst* m;
	int bats;
	IntRect *rect;
} character;

void init_m( mnst* m, int n) {
	for (int i = 0; i < n; i++) {
		m[i].en=0;
		m[i].x=0;
		m[i].y=0;
		m[i].sprite;
		m[i].hp=2;
		m[i].line=0;
		m[i].rect=&IntRect(0,0,32,32);
	}

}
void spawn_m(mnst* m, int n,int type,RenderWindow* window) {
	
	for (int i = 0; i < n; i++) {
		if (m[i].en == 0) {
			m[i].sprite.setColor(Color::White);
			m[i].en = 1;
			m[i].x = rand() % window->getSize().x;
			m[i].y = rand() % window->getSize().y;
			m[i]. type = type;
			m[i].hp = 2;
			break;
		}
		
	}
}

void move_m(character* MC,mnst* m, int n, double delta, RenderWindow * window) {
	float j,k;
	
	for (int i = 0; i < n; i++) {
		if (m[i].en == 1) {
			j = MC->x - m[i].x;
			k = MC->y * window->getSize().y / 600.0 - m[i].y;
			m[i].x = m[i].x + (j / abs(j))*5 / delta;
			m[i].y = m[i].y + (k / abs(k) *5/ delta);
			m[i].sprite.setPosition(m[i].x * window->getSize().x / 800.0, m[i].y+MC->py);

		

		}
	}
}

void character_initializer(character* char_obj, string type, int x, int y){
	char_obj->m = new mnst[10];
	init_m(char_obj->m, 10);
	char_obj->hp = 3;
	char_obj->x = x;
	char_obj->en = 1;
	char_obj->wy = y;
	char_obj->bats = 0;
	char_obj->y = y;
	char_obj->dir = 1;
	char_obj->der = 1;
	IntRect rectangular(0, 0, 32, 32);
	IntRect rectangular_shape(0, 0, 32, 32);
	char_obj->b.rect = &rectangular;
	char_obj->rect = &rectangular_shape;
	char_obj->sprite.setOrigin(-200, 16);
	if(type.compare("mc"))
		char_obj->line = 0;
	char_obj->sprite.setOrigin(32 / 2, 32 / 2);
	char_obj->b.en = 0;
}
void spawn_b(character * MC) {
	if (MC->b.en == 0) {
		MC->b.ox = MC->sprite.getPosition().x;
		MC->b.oy = MC->y;

		if (MC->der == 1 && MC->dir == 1) {
			MC->b.dir = 0;
		}
		else if (MC->der == 1) {
			MC->b.dir = 1;
		}
		else if (MC->dir == -1) {
			MC->b.dir = 2;
		}

		MC->b.x = MC->b.ox - MC->b.dir * 30;
		MC->b.y = MC->b.oy - (1 - MC->der) * 30;
		MC->b.en = 1;
		float var = MC->sprite.getPosition().y - MC->b.y - MC->py;
			MC->b.y = MC->b.y + var + MC->py;
		MC->b.sprite.setPosition(MC->b.x, MC->b.y);
	}
}
void move_b(character * MC, double delta) {
	if (MC->b.en == 1) {
		switch (MC->b.dir) {
		case 0:
			MC->b.x = MC->b.x + 50 / delta;
			break;
		case 1:
			MC->b.x = MC->b.x - 50 / delta;
			break;
		case 2:
			MC->b.y = MC->b.y - 50 / delta;
			break;
		}
		MC->b.sprite.setPosition(MC->b.x, MC->b.y);
	}
}

void destroy_b(character* MC, mnst* m, int n,double delta, RenderWindow* window) {
	float w = MC->b.y;
	if (MC->b.x < -15 || MC->b.x > window->getSize().x)
		MC->b.en = 0;
	if (w < -15)
		MC->b.en = 0;
	for (int i = 0; i < n; i++) {
		if (abs(m[i].sprite.getPosition().x - MC->b.sprite.getPosition().x) < 150 && abs(m[i].sprite.getPosition().y - MC->b.sprite.getPosition().y) < 50 && m[i].en == 1 && MC->b.en == 1) {
			MC->b.en = 0;
			m[i].sprite.setColor(Color::Red);
			m[i].hp = m[i].hp - 1;
			if (m[i].hp <= 0)
				m[i].en = 0;
		}
		if (abs(m[i].sprite.getPosition().x - MC->sprite.getPosition().x) < 50 && abs(m[i].sprite.getPosition().y - MC->sprite.getPosition().y) < 50 && m[i].en == 1 && MC->en == 1)
			MC->en = 0;
	}
	}

int cutscene(Clock clock,IntRect* rectSourceSprite, Sprite* sprite, int sizex, int sizey, int frames, int line ,int fps) {
	if (((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)sizex < frames) {
		(*rectSourceSprite).left = ((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)frames * sizex;
		(*rectSourceSprite).top = line * sizey;
		(*sprite).setTextureRect(*rectSourceSprite);
		return 1;
	}

	return 0;
}

void animate(Clock clock, IntRect* rectSourceSprite, Sprite* sprite, int sizex,int sizey, int frames, int line, int fps) {

	(*rectSourceSprite).left = ((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)frames * sizex ;
	(*rectSourceSprite).top = line * sizey;
	(*sprite).setTextureRect(*rectSourceSprite);

}

void write(int n, RenderWindow* window,float size, Color c,float x, float y,int i,string str) {
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		//scanf("%*c");
	}
	Text texto;
	texto.setFont(font);
	texto.setFillColor(c);
	texto.setPosition((*window).getSize().x /800*x, (*window).getSize().y /600*y);
	texto.setCharacterSize((*window).getSize().y * size);
	string s = std::to_string(i);
	switch (n)
	{
	case 0:
		texto.setString(s);
		break;
	case 1:
		texto.setString(str);
		break;
	default:
		texto.setString(" ");
	}

	(*window).draw(texto);
}

void chat(int n, RenderWindow* window) {
	switch (n) {
	case 0:
		write(1, window, 0.03, Color::White, 350, 650, 10, "Est� muito escuro aqui...\n");
		write(1, window, 0.02, Color::White, 350, 650, 10, "\n \n ainda bem que h� uma lanterna\n ..... o que � aquilo?");
		break;
	case 2:

		write(1, window, 0.03, Color::White, 50, 650, 10, "algo ainda me deixa desconfortavel aqui...");
		break;

	case 4:
		write(1, window, 0.03, Color::White, 50, 650, 10, "FUJA!	FUJA!  FUJA RAPIDAMENTE! ,\n ELE N�O EST� T�O LONGE...");
		break;
	case 6:
		write(1, window, 0.03, Color::White, 50, 650, 10, "SAIA DO MEU QUARTO,\n crian�as n�o deveriam estar aqui...");
		break;
	case 8:
		write(1, window, 0.08, Color::White, 50, 650, 10, "*****ROOOONCO******");
		break;

	case 10:
		write(1, window, 0.03, Color::White, 50, 650, 10, "nada aqui");
		break;

	case 101:
		write(1, window, 0.03, Color::White, 350, 650, 10, " vamos, filho");
		break;
	case 102:
		write(1, window, 0.03, Color::White, 350, 650, 10, " vamos, filho\n sua m�e est� nos esperando em casa\n estavamos ansiosos por sua alta");
		break;
	case 103:
		write(1, window, 0.03, Color::White, 350, 650, 10, " estavamos ansiosos por sua alta\n n�o precisa ter medo, estou aqui");
		break;
	case 104:
		write(1, window, 0.03, Color::White, 350, 650, 10, " estavamos ansiosos por sua alta\n n�o precisa ter medo, estou aqui");
		break;
	case 100:
		write(1, window, 0.03, Color::White, 350, 650, 10, "algu�m pode iluminar?");
		break;

	default:
		write(1, window, 0.03, Color::White, 50, 650, 10, "");
		break;

	}
}

void draw_menu(int* current_scr,Texture * textures ,RenderWindow *window) {
	// Create text
	IntRect rec(0,0,800,600);
	//Sprite menu(textures[7],rec);
	//menu.setScale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	//menu.setPosition(0, 0);

	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		//scanf("%*c");
	}
	Text logo;
	Text opt1;
	Text opt2;
	Text opt3;
	logo.setFont(font);
	opt1.setFont(font);
	opt2.setFont(font);
	opt3.setFont(font);
	logo.setString("Healer's Tale");
	opt1.setString("Iniciar");
	opt2.setString("Creditos");
	opt3.setString("Sair");
	logo.setCharacterSize((*window).getSize().y * 0.08);
	opt1.setCharacterSize((*window).getSize().y * 0.05);
	opt2.setCharacterSize((*window).getSize().y * 0.05);
	opt3.setCharacterSize((*window).getSize().y * 0.05);
	logo.setPosition((*window).getSize().x/2-logo.getGlobalBounds().width/2,(*window).getSize().y/2/2-logo.getGlobalBounds().height/2-(*window).getSize().y*0.1);
	//logo.setPosition((*window).getSize().x / 2 - ((*window).getSize().y * 0.08 * 21) / 2 / 2, (*window).getSize().y / 2 / 2 - (*window).getSize().y * 0.08 / 2);
	opt1.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 3);
	opt2.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 4);
	opt3.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 5);

	// Menu events
	if (opt1.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt1.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 1;
	}
	else if (opt2.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt2.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 2;
	}
	else if (opt3.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt3.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			(*window).close();
	}

	// Draw
	//(*window).draw(menu);
	(*window).draw(logo);
	(*window).draw(opt1);
	(*window).draw(opt2);
	(*window).draw(opt3);
}

void draw_gameover(Clock clock,int* current_scr, Texture* textures, RenderWindow* window) {
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		//scanf("%*c");
	}
	IntRect die(0, 0, 300, 300);
	Sprite died(textures[0], die);
	died.setPosition((*window).getSize().x/2-died.getGlobalBounds().width/2, (*window).getSize().y/2-died.getGlobalBounds().height/2);
	//died.setScale((*window).getSize().x/300.0, (*window).getSize().y / 300.0);
	//animate(clock, &die, &died, 800, 600, 4, 0, 10);
	(*window).draw(died);

	Text gameover;
	gameover.setFont(font);
	gameover.setString("Voce Perdeu\n  o Jogo!");
	gameover.setCharacterSize((*window).getSize().y * 0.08);
	gameover.setPosition((*window).getSize().x / 2 - gameover.getGlobalBounds().width / 2, (*window).getSize().y / 2 / 2 / 2);
	Text menu;
	menu.setFont(font);
	menu.setString("Voltar ao menu");
	menu.setCharacterSize((*window).getSize().y * 0.05);
	menu.setPosition((*window).getSize().x / 2 + 50, (*window).getSize().y / 2 / 2 * 3);
	Text retry;
	retry.setFont(font);
	retry.setString("Tentar novamente");
	retry.setCharacterSize((*window).getSize().y * 0.05);
	retry.setPosition((*window).getSize().x / 2 - 50 - retry.getGlobalBounds().width, (*window).getSize().y / 2 / 2 * 3);

	// Menu events
	if (menu.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		menu.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 0;
	}
	else if (retry.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		retry.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left)) {
			*current_scr = 1;
		}
	}

	(*window).draw(gameover);
	(*window).draw(menu);
	(*window).draw(retry);
}

void draw_credits_gamso(RenderWindow *window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		//scanf("%*c");
	}
	Text credits;
	credits.setFont(font);
	credits.setString("Produzido por Lunare Team e");
	credits.setCharacterSize((*window).getSize().y*0.05);
	credits.setPosition((*window).getSize().x/2-credits.getGlobalBounds().width/2, (*window).getSize().y*0.02);

	// Create texture
	Texture texture;
	if (!texture.loadFromFile("img/gamso.png")){
		cout << "Error loading texture" << endl;
	}
	texture.setSmooth(false);
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(((*window).getSize().y - 200) / sprite.getLocalBounds().width, ((*window).getSize().y - 200) / sprite.getLocalBounds().height);
	sprite.setPosition((*window).getSize().x/2-sprite.getGlobalBounds().width/2, (*window).getSize().y/2-sprite.getGlobalBounds().height/2);

	(*window).draw(credits);
	(*window).draw(sprite);
}

void draw_credits(int* current_scr, Texture* textures, RenderWindow *window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		//scanf("%*c");
	}
	IntRect voltar_rect(0,0,32,32);
	Sprite voltar;
	voltar.setTextureRect(voltar_rect);
	voltar.setTexture(textures[2]);
	voltar.setScale((*window).getSize().x*0.002,(*window).getSize().x*0.002);
	voltar.setPosition((*window).getSize().x*0.0001, (*window).getSize().x*0.0001);
	Text credits;
	credits.setFont(font);
	credits.setString("Joao Bueno\nMatheus Ramos\nGabriel Penajo\nIsabela Magalhaes");
	credits.setCharacterSize((*window).getSize().y * 0.05);
	credits.setPosition((*window).getSize().x/2-credits.getGlobalBounds().width/2, (*window).getSize().y/2-credits.getGlobalBounds().height/2);

	// Mouse events
	if (voltar.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		voltar.setColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 0;
	}

	// Draw
	(*window).draw(voltar);
	(*window).draw(credits);
}

void draw_game(int* map, character* MC, Sound sound[], Texture* textures, double delta, Clock clock, int* current_scr, RenderWindow* window, Event event) {
	Sprite map_sprite;
	
	IntRect map_rec(0, 0, 64, 64);
	IntRect hp(0, 0, 100, 10);
	Sprite h;
	h.setColor(Color::Green);
	h.setTextureRect(hp);
	h.setScale(MC->hp / 100, 1);
	h.setPosition(100, 100);
	if(Mouse::isButtonPressed(Mouse::Right))
		MC->bats=1;

	if (MC->bats&&(Mouse::isButtonPressed(Mouse::Right)|| 0==((int ) clock.getElapsedTime().asMilliseconds() )% 100)) {
		spawn_m(MC->m, 10, 1, window);

	}
	move_m(MC, MC->m, 10, delta,window);
	
	IntRect rec(0, 0, 32, 32);
	MC->b.sprite.setTextureRect(rec);
	MC->b.sprite.setTexture(textures[6]);

	for (int i = 0; i < 10; i++) {

		animate(clock, &rec, &MC->m[i].sprite, 32, 32, 4, 0, 10);
		MC->m[i].sprite.setTexture(textures[4]);
		MC->m[i].sprite.setTextureRect(rec);
	}
	int var = 0, vel = 7;

	MC->sprite.setTextureRect(rec);
	move_b(MC, delta);
	destroy_b(MC,MC->m ,10,delta, window);
	MC->sprite.setPosition((MC->x) * (*window).getSize().x / 800.0, (MC->wy) * (*window).getSize().y / 600.0);
	MC->sprite.setScale((*window).getSize().x / 400.0, (*window).getSize().y / 300.0);
	MC->b.sprite.setScale((*window).getSize().x / 700.0, (*window).getSize().y / 700.0);
	MC->sprite.setTexture(textures[3]);
	animate(clock, (&rec), &(MC->sprite), 32, 32, 4, 0, 10);
	animate(clock, &rec, &MC->b.sprite, 32, 32, 3, 0, 10);

	int s = (*window).getSize().x, ss = (*window).getSize().y;

	if (MC->y * (*window).getSize().y / 600.0 < (*window).getSize().y / 2.0) {
		MC->wy = MC->y;
		MC->py = 0;
		map_sprite.setPosition(0, 0);
		MC->sprite.setPosition((MC->x) * (*window).getSize().x / 800.0, (MC->wy) * (*window).getSize().y / 600.0);
	}
	else if (MC->y * (*window).getSize().y / 600.0 > (*window).getSize().y / 2.0 + ((*window).getSize().x - (*window).getSize().y)) {
		MC->py = ss - s;
		MC->wy = (((MC->y) * ss / 600.0) + (ss - s)) / ss / 600.0;
		map_sprite.setPosition(0, ss - s);
		MC->sprite.setPosition((MC->x) * s / 800.0, (((MC->y) * ss / 600.0) + (ss - s)));
	}
	else {
		MC->wy = (ss / 2.0) / (ss / 600.00);
		MC->py = (*window).getSize().y / 2 - MC->y * (*window).getSize().y / 600;
		map_sprite.setPosition(0, (*window).getSize().y / 2 - MC->y * (*window).getSize().y / 600);
		MC->sprite.setPosition((MC->x) * s / 800.0, ss / 2.0);
	}


	if (Keyboard::isKeyPressed(Keyboard::W) && MC->y > 134) {
		MC->y = (MC->y) - vel / delta;
		MC->sprite.setTexture(textures[9]);
		MC->der = -1;
		MC->dir = -1;


	}
	else if (Keyboard::isKeyPressed(Keyboard::S) && MC->y < 964) {
		(MC->y) = (MC->y) + vel / delta;
		MC->sprite.setTexture(textures[3]);
		MC->der = 1;
	}
	else {
		var = 1;
	}
	if (MC->der == -1)
		MC->sprite.setTexture(textures[9]);
	else
		MC->sprite.setTexture(textures[3]);
	if (Keyboard::isKeyPressed(Keyboard::D) && MC->x < 726) {
		(MC->x) = (MC->x) + vel / delta;
		MC->der = 1;
		if (MC->dir == -1) {
			MC->dir = 1;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && MC->x > 124) {
		(MC->x) = (MC->x) - vel / delta;
		MC->der = 1;
		if (MC->dir == 1) {
			MC->dir = -1;

		}

	}


	else if (var == 1) {

		rec.left = 32;

		if (Keyboard::isKeyPressed(Keyboard::Space) && MC->der == 1) {
			MC->sprite.setTexture(textures[8]);
			rec.left = 0;
			spawn_b(MC);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space) && MC->der == -1) {
			MC->sprite.setTexture(textures[9]);
			rec.left = 0;
			spawn_b(MC);
		}
		MC->sprite.setTextureRect(rec);

	}
	else {

	}
	MC->sprite.scale(MC->dir, 1);
	if (MC->der == -1)
		MC->b.sprite.scale(0.5, 1);
	switch (*map) {
	case 0:
		map_sprite.setTextureRect(map_rec);
		map_sprite.setTexture(textures[7]);
		map_sprite.setScale(13 * (*window).getSize().x / 800, 13 * (*window).getSize().x / 800);
		break;
	}



	(*window).draw(map_sprite);
	
	if (MC->b.en == 1)
		for (int i = 1; i < 10; i++){
			MC->b.sprite.setPosition(MC->b.x - i * 0.5 *25* (MC->b.dir == 1 ? 1 : -2), MC->b.y + i * 0.5 * 10*((MC->b.dir == 1 ? 0.1*i : i%2)));
			MC->b.sprite.scale( 0.12*(10-i), (10- i)*0.12);
			MC->b.sprite.setColor(Color::Color(255, 255, 255, 255 - i * 20));
			(*window).draw(MC->b.sprite);
		}
	(*window).draw(MC->sprite);
	window->draw(h);
	for(int i=0;i<10;i++)
		if(MC->m[i].en==1)
			window->draw(MC->m[i].sprite);
	if (MC->en == 0) {
		*current_scr = 3;
		init_m(MC->m, 10);
		character_initializer(MC, "mc", 200, 200);
	}
}


void draw_scr(int* map, character* MC, Texture* textures, double delta, Clock clock, int* current_scr, RenderWindow* window, Event& event, Sound sound[]) {
	/*
	 *  0 - Menu
	 *  1 - Game
	 *  2 - Credits
	 *  3 - Game Over Yeah
	 */

	switch (*current_scr) {
	case 0:
		draw_menu(current_scr, textures, window);
		break;
	case 1:
		draw_game(map, MC,sound, textures,delta, clock, current_scr, window, event);
		break;
	case 2:
		draw_credits(current_scr, textures, window);
		break;
	case 3:
		draw_gameover(clock,current_scr, textures,window);
		break;
	default:
		break;
	}
}

Texture* load_textures() {
	/*
	 *  0 - Game Over , 300 300 1 1
	 *  1 - Cursor    , 32  32  1 2
	 *  2 - Arrow     , 32  32  1 1
	 *  3 - MC        , 32  32  4 1
	 *  4 - Bat       , 32  32  6 1
	 *  5 - Butterfly , 32  32  6 1
	 *  6 - Heal      , 32  32  3 1
	 *  7 - Dungeon   , 64  64  1 1
	 *  8 - Pawa      , 32  32  1 1
	 *  9 - back      , 32  32  4 1
	 */

	Texture *textures;
	textures=(Texture*)malloc(sizeof(Texture) * 10);

	Texture gameover;
	if (!gameover.loadFromFile("img/gameover.jpg", sf::IntRect(0, 0, 300, 300))) {
		perror("failed to load gameover image");
		//scanf("%*c");
	}
	Texture cursor;
	if (!cursor.loadFromFile("img/cursor.png", sf::IntRect(0, 0, 32, 64))) {
		perror("failed to load cursor image");
		//scanf("%*c");
	}
	Texture back_arrow;
	if (!back_arrow.loadFromFile("img/arrow.png", sf::IntRect(0, 0, 32, 32))) {
		perror("failed to load back_arrow image");
		//scanf("%*c");
	}
	Texture mc;
	if (!mc.loadFromFile("img/mc.png", sf::IntRect(0, 0, 128, 32))) {
		perror("failed to load mc image");
		//scanf("%*c");
	}
	Texture bat;
	if (!bat.loadFromFile("img/bat.png", sf::IntRect(0, 0, 192, 32))) {
		perror("failed to load bat image");
		//scanf("%*c");
	}
	Texture butterfly;
	if (!butterfly.loadFromFile("img/samurai.png", sf::IntRect(0, 0, 192, 32))) {
		perror("failed to load samurai image");
		//scanf("%*c");
	}
	Texture heal;
	if (!heal.loadFromFile("img/heal.png", sf::IntRect(0, 0, 96, 32))) {
		perror("failed to load heal image");
		//scanf("%*c");
	}
	Texture dungeon;
	if (!dungeon.loadFromFile("img/initialdungeon.png", sf::IntRect(0, 0, 64, 64))) {
		perror("failed to load dungeon image");
		//scanf("%*c");
	}
	Texture pawa;
	if (!pawa.loadFromFile("img/pawa.png", sf::IntRect(0, 0, 32, 32))) {
		perror("failed to load kono pawa image");
		//scanf("%*c");
	}
	Texture back;
	if (!back.loadFromFile("img/persona.png", sf::IntRect(0, 0, 4*32, 32))) {
		perror("failed to load kono pawa image");
		//scanf("%*c");
	}

	textures[0] = gameover;
	textures[1] = cursor;
	textures[2] = back_arrow;
	textures[3] = mc;
	textures[4] = bat;
	textures[5] = butterfly;
	textures[6] = heal;
	textures[7] = dungeon;
	textures[8] = pawa;
	textures[9] = back;
	return textures;

}

int main(void) {
	int current_scr[1] = { 0 };
	int cursor_line = 1, map = 0;

	// Initialize clock
	Clock clock;
	// Initialize window
	RenderWindow window(VideoMode::getDesktopMode(), "Healer's Tale", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	Texture* textures;
	textures = load_textures();
	Sprite cursor(textures[1]);
	IntRect cursorRect(0,0,32,32);
	character MC;
	character_initializer(&MC, "mc", 200, 200);
	SoundBuffer walk;
	if (!walk.loadFromFile("sound/walk.wav")) {
		cout << "Error loading sound" << endl;
		//scanf("%*c");
	}
	SoundBuffer bgm;
	if (!bgm.loadFromFile("sound/bgm.ogg")) {
		cout << "Error loading sound" << endl;
		//scanf("%*c");
	}
	SoundBuffer speech;
	if (!speech.loadFromFile("sound/speech.wav")) {
		cout << "Error loading sound" << endl;
		//scanf("%*c");
	}
	Sound sound[4], bg;
	sound[0].setBuffer(walk);
	sound[1].setBuffer(speech);
	bg.setBuffer(bgm);

	double nt,ot=0,delta;
	while( window.isOpen()) {

		Time time;
		time = clock.getElapsedTime();
		nt = time.asMicroseconds();

		delta = 50000/(nt - ot) ;
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}


		window.clear();
		if (time.asSeconds() <= 8)
			draw_credits_gamso(&window);
		else {
			draw_scr(&map, &MC,textures, delta, clock, current_scr, &window, event, sound);
			if (bg.getStatus() != bg.Playing && *current_scr == 1)
				bg.play();
			else if (bg.getStatus() == bg.Playing && *current_scr == 0)
				bg.stop();
		}

		cursorRect.top = 0;
		cursor.setTextureRect(cursorRect);

		if (Mouse::isButtonPressed(Mouse::Left))
			cursor_line = 0;
		else
			cursor_line = 1;

		cursor.setOrigin(16, 16);
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
		cursor.setScale((window).getSize().x*0.001, (window).getSize().x*0.001);
		animate(clock, &cursorRect, &cursor, 32, 32, 1, cursor_line, 4);
		window.draw(cursor);
		window.display();
		ot = nt;
	}

	free(textures);
	return 0;

}
