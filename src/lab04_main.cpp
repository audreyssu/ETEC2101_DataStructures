#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Audrey Lab04");
	sf::CircleShape test(100.0f);
	test.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		window.clear();
		window.draw(test);
		window.display();
	}

	return 0;
}