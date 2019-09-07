#include <iostream>
#include <math.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

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
	logo.setString("Gamsecomp 2019.2");
	opt1.setString("Iniciar");
	opt2.setString("Creditos");
	opt3.setString("Sair");
	logo.setCharacterSize((*window).getSize().y * 0.08);
	opt1.setCharacterSize((*window).getSize().y * 0.05);
	opt2.setCharacterSize((*window).getSize().y * 0.05);
	opt3.setCharacterSize((*window).getSize().y * 0.05);
	logo.setPosition((*window).getSize().x / 2 - ((*window).getSize().y * 0.08 * 21) / 2 / 2, (*window).getSize().y / 2 / 2 - (*window).getSize().y * 0.08 / 2);
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

void draw_gameover(Clock clock,int* current_scr, Texture* textures, RenderWindow* window, int propLine[]) {
	for (int i = 0; i < 10; i++)
		propLine[i] = 0;
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		scanf("%*c");
	}
	IntRect die(0, 0, 800, 600);
	Sprite died(textures[13], die);
	died.setPosition(0, 0);
	died.setScale((*window).getSize().x/800.0, (*window).getSize().y / 600.0);
	animate(clock, &die, &died, 800, 600, 4, 0, 10);
	(*window).draw(died);

	Text gameover;
	gameover.setFont(font);
	gameover.setString("Você Perdeu!");
	gameover.setCharacterSize((*window).getSize().y * 0.08);
	gameover.setPosition((*window).getSize().x / 2 - gameover.getGlobalBounds().width / 2, (*window).getSize().y / 2 / 2 - (*window).getSize().y * 0.08 / 2);
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
	sprite.setScale((*window).getSize().y / sprite.getLocalBounds().width, (*window).getSize().y / sprite.getLocalBounds().height);
	sprite.setPosition((*window).getSize().x/2-sprite.getGlobalBounds().width/2-22, 0);

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
	credits.setString("");
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

void draw_scr(Texture* textures,double delta,Clock clock,int* current_scr, RenderWindow *window, Event &event,Sound *sound, int *cursorLine, int *propLine) {
	/*
	 *  0 - Menu
	 *  1 - Game
	 *  2 - Credits
		3-  F
	 */

	switch (*current_scr) {
	case 0:
		draw_menu(current_scr,textures, window);
		for (int i = 0; i < 10; i++)
			propLine[i] = 0;
		break;
	case 1:
		while(true){
			break;
		}
		//draw_game(sound,textures,delta, clock,current_scr, window, event, cursorLine, propLine);
		break;
	case 2:
		draw_credits(current_scr, window);
		break;
	case 3:
		draw_gameover(clock,current_scr, textures,window,propLine);
		break;
	default:
		break;
	}
}

Texture* load_textures() {
	Texture *textures;
	textures=(Texture*)malloc(sizeof(Texture) * 15);

	/*
	Texture end;
	if (!end.loadFromFile("img/final.png", sf::IntRect(0, 0, 4800, 3000))) {
		perror("failed to load final image");
		scanf("%*c");
	}
	*/

	//textures[0] = shadowsheet;
	return textures;

}

int main(void) {
	int current_scr[1] = { 0 }, propLine[10] = {0,0,0,0,0,0,0,0,0,0};

	// Initialize clock
	Clock clock;
	// Initialize window
	RenderWindow window(VideoMode::getDesktopMode(), "Afraid Of The Shadows", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	Texture* textures;
	textures = load_textures();
	Sprite cursor(textures[5]);
	IntRect cursorRect(0,50,50,50);
	SoundBuffer walk,bgm;
	if (!walk.loadFromFile("sound/walk.wav")) {
		cout << "Error loading sound" << endl;
		scanf("%*c");
	}
	if (!bgm.loadFromFile("sound/bgm.wav")) {
		cout << "Error loading sound" << endl;
		scanf("%*c");
	}
	Sound sound,bg;
	sound.setBuffer(walk);
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
		int cursorLine = 1;
		if (time.asSeconds() <= 10)
			draw_credits_gamso(&window);
		else {
			draw_scr(textures, delta, clock, current_scr, &window, event, &sound, &cursorLine, propLine);
			if (bg.getStatus() != bg.Playing && *current_scr == 1)
				bg.play();
			else if (bg.getStatus() == bg.Playing && *current_scr == 0)
				bg.stop();
		}
		cursorRect.top = 50 * cursorLine;
		cursor.setTextureRect(cursorRect);
		cursor.setOrigin(20, 20);
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
		animate(clock, &cursorRect, &cursor, 50,50, 3, cursorLine, 4);
		window.draw(cursor);
		window.display();
		ot = nt;
	}
	free(textures);
	return 0;

}
