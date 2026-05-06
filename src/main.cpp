#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "My window",
                          sf::Style::Resize);
  window.setPosition({10, 50});

  std::vector<sf::CircleShape> particles;

  sf::CircleShape hole(50.f);
  hole.setFillColor(sf::Color::Black);
  hole.setOutlineThickness(1.f);
  hole.setOutlineColor(sf::Color::Red);
  hole.setPosition({400, 300});

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    while (const std::optional event = window.pollEvent()) {
      // "close requested" event: we close the window
      if (event->is<sf::Event::Closed>())
        window.close();
      if (const auto *mouseButtonPressed =
              event->getIf<sf::Event::MouseButtonPressed>()) {
        sf::CircleShape particle(10.f);
        particle.setFillColor(sf::Color(255, 255, 255));
        sf::Vector2i mousePosition = mouseButtonPressed->position;
        sf::Vector2f position({static_cast<float>(mousePosition.x),
                               static_cast<float>(mousePosition.y)});
        particle.setPosition(position);

        particles.push_back(particle);
      }
    }
    window.clear(sf::Color::Black);

    for (auto &particle : particles) {
      particle.move({.25f, 0.f});
      window.draw(particle);
    }
    window.draw(hole);
    window.display();
  }
}
