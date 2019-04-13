#include <SFML/Graphics.hpp>

int main() {
  // Create the main window
  sf::RenderWindow window{sf::VideoMode(800, 600), "SFML window"};
  // Create a ball
  sf::CircleShape ball{100, 90ULL};
  ball.setFillColor(sf::Color::Blue);
  // Create a graphical text to display
  sf::Font font;
  // If this returns EXIT_FAILURE you are not running it from the bin/ directory
  if (!font.loadFromFile("ARIAL.TTF")) return EXIT_FAILURE; 
  const char* main_text{
      "Hello SFML\n"
      "This is a short test for a ball and events.\n"
      "Click to move the ball.\n"
      "Press Q or E, or use the mouse wheel to scale the ball.\n"
      "You can make the ball Red, Blue, Green, and Yellow by pressing the key\n"
      "\tthat matches the first letter of the color."};
  sf::Text text(main_text, font, 18);
  text.setPosition(100,100);
  // Variable to know if we are dragging the ball
  bool toggle_drag = false;
  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event{};
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // Change ball size with mouse scrolling
      if (event.type == sf::Event::MouseWheelScrolled) {
        ball.scale(event.mouseWheelScroll.delta,event.mouseWheelScroll.delta);
        ball.move(-event.mouseWheelScroll.delta, -event.mouseWheelScroll.delta);
      }

      // Change ball size with Q (grow) and E (shrink) keys
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Q:  // Grow
            ball.scale(1.02f,1.02f);
            ball.move(-ball.getScale());
            break;
          case sf::Keyboard::E:  // Shrink
            ball.scale(0.98f,0.98f);
            ball.move(ball.getScale());
            break;

          case sf::Keyboard::B:
            ball.setFillColor(sf::Color::Blue);
            break;
          case sf::Keyboard::R:
            ball.setFillColor(sf::Color::Red);
            break;
          case sf::Keyboard::Y:
            ball.setFillColor(sf::Color::Yellow);
            break;
          case sf::Keyboard::G:
            ball.setFillColor(sf::Color::Green);
            break;
        }
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left || window.hasFocus()) {
          toggle_drag = true;
        }
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left || window.hasFocus()) {
          toggle_drag = false;
        }
      }
      if (event.type == sf::Event::MouseMoved) {
        if (toggle_drag) {
          // Set ball position to where the mouse is - the ball's radius
          ball.setPosition(
              window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}) -
              sf::Vector2f{ball.getRadius(), ball.getRadius()});
        }
      }
    }
    // Clear screen
    window.clear();
    // Draw the sprite
    window.draw(ball);
    // Draw the string
    window.draw(text);
    // Update the window
    window.display();
  }
  return EXIT_SUCCESS;
}
