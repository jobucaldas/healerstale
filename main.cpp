#include <iostream>
#include <string>
#include <math.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

typedef struct{
	int x;
	int y;
	int hp;
	int line;
	IntRect rect;
} character;

void character_initializer(character* char_obj, string type, int x, int y){
	char_obj->hp = 3;
	char_obj->x = x;
	char_obj->y = y;
	if(type.compare("mc"))
		char_obj->line = 0;
	IntRect rect(0,0,16,16);
	char_obj->rect = rect;
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
		scanf("%*c");
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
		scanf("%*c");
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

Sprite get_prop(Clock clock, Texture* textures, int line, float x, float y) {
	IntRect propRect(0,0,50,50);
	Sprite prop(textures[5], propRect);
	animate(clock, &propRect, &prop, 50, 50, 3, line, 3);
	prop.setPosition(x, y);
	return prop;
}

void draw_gameover(Clock clock,int* current_scr, Texture* textures, RenderWindow* window) {
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		scanf("%*c");
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
		scanf("%*c");
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

void draw_credits(int* current_scr, RenderWindow *window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		scanf("%*c");
	}
	Text voltar;
	voltar.setFont(font);
	voltar.setString("Voltar");
	voltar.setCharacterSize((*window).getSize().y * 0.05);
	voltar.setPosition((*window).getSize().x*0.02, (*window).getSize().y*0.5 + (*window).getSize().y * 0.08 * 5);
	Text credits;
	credits.setFont(font);
	credits.setString("Joao Bueno\nMatheus Ramos\nGabriel Penajo\nIsabela Magalhaes");
	credits.setCharacterSize((*window).getSize().y * 0.05);
	credits.setPosition((*window).getSize().x/2-credits.getGlobalBounds().width/2, (*window).getSize().y/2-credits.getGlobalBounds().height/2);

	// Mouse events
	if (voltar.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		voltar.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 0;
	}

	// Draw
	(*window).draw(voltar);
	(*window).draw(credits);
}

void draw_game(Sound sound[], Texture* textures, double delta, Clock clock, int* current_scr, RenderWindow *window, Event event){

}

void draw_scr(Texture* textures,double delta,Clock clock,int* current_scr, RenderWindow *window, Event &event,Sound sound[]) {
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
		draw_game(sound, textures,delta, clock, current_scr, window, event);
		break;
	case 2:
		draw_credits(current_scr, window);
		break;
	case 3:
		draw_gameover(clock,current_scr, textures,window);
		break;
	default:
		break;
	}
}

Texture* load_textures() {
	Texture *textures;
	textures=(Texture*)malloc(sizeof(Texture) * 3);

	Texture gameover;
	if (!gameover.loadFromFile("img/gameover.jpg", sf::IntRect(0, 0, 300, 300))) {
		perror("failed to load gameover image");
		scanf("%*c");
	}
	Texture cursor;
	if (!cursor.loadFromFile("img/cursor.png", sf::IntRect(0, 0, 32, 64))) {
		perror("failed to load cursor image");
		scanf("%*c");
	}
	Texture back_arrow;
	if (!back_arrow.loadFromFile("img/arrow.png", sf::IntRect(0, 0, 32, 32))) {
		perror("failed to load back_arrow image");
		scanf("%*c");
	}

	textures[0] = gameover;
	textures[1] = cursor;
	textures[2] = back_arrow;
	return textures;

}

int main(void) {
	int current_scr[1] = { 0 };
	int cursor_line = 1, old_scr = 0;

	// Initialize clock
	Clock clock;
	// Initialize window
	RenderWindow window(VideoMode::getDesktopMode(), "Gamsecomp 2019.2", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	Texture* textures;
	textures = load_textures();
	Sprite cursor(textures[1]);
	IntRect cursorRect(0,0,32,32);

	SoundBuffer walk;
	if (!walk.loadFromFile("sound/walk.wav")) {
		cout << "Error loading sound" << endl;
		scanf("%*c");
	}
	SoundBuffer bgm;
	if (!bgm.loadFromFile("sound/bgm.wav")) {
		cout << "Error loading sound" << endl;
		scanf("%*c");
	}
	SoundBuffer speech;
	if (!speech.loadFromFile("sound/speech.wav")) {
		cout << "Error loading sound" << endl;
		scanf("%*c");
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
			draw_scr(textures, delta, clock, current_scr, &window, event, sound);
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
