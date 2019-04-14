#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>

int main() {
  using spdlog::info;
  using fmt::format;
  using namespace sf;
  using namespace fmt::literals;
  // Create the main window
  RenderWindow window{VideoMode(800, 600), "SFML window"};
  // Create a ball
  CircleShape ball{100.f, 90ULL};
  ball.setFillColor(Color::Blue);
  ball.setPosition(300.f, 300.f);
  // Create a graphical text to display
  Font font;
  // If this returns EXIT_FAILURE you are not running it from the bin/ directory
  if (!font.loadFromFile("ARIAL.TTF")) return EXIT_FAILURE;
  Text text("Hello SFML\n"
      "This is a short test for a ball and events.\n"
      "Click to move the ball.\n"
      "Press Q (grow) or E (shrink), or use the mouse wheel to scale the "
      "ball.\n"
      "You can make the ball Red, Blue, Green, and Yellow by pressing the key\n"
      "\tthat matches the first letter of the color.", font, 18);

  auto regular_viewport = FloatRect{0.f, 0.f, 800.f, 600.f};
  View view(regular_viewport);
  // Start the game loop
  while (window.isOpen()) {
    // Process events
    Event event{};
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == Event::Closed) {
        window.close();
      }

      // Change ball size with mouse scrolling
      if (event.type == Event::MouseWheelScrolled) {
        view.zoom(1 + event.mouseWheelScroll.delta);
        info("Changed zoom by a factor of {}."_format(event.mouseWheelScroll.delta));
      }
      // Move view if mouse moved and pressed mouse button.
      if (event.type == Event::MouseMoved) {
        if (Mouse::isButtonPressed(Mouse::Left)) {
          view.setCenter(800.f - event.mouseMove.x, 600.f - event.mouseMove.y);
          info("Moved center of view to {{{},{}}}."_format(view.getCenter().x,
                                                           view.getCenter().y));
        }
      }

      // Change ball size with Q (grow) and E (shrink) keys
      if (Keyboard::isKeyPressed(Keyboard::Q)) {
        view.zoom(1.02f);
        info("Increased zoom by a factor of 2%.");
      }
      if (Keyboard::isKeyPressed(Keyboard::E)) {
        view.zoom(0.98f);
        info("Decreased zoom by a factor of 2%.");
      }

      // Change ball color if B, R, Y, or G is pressed
      if (event.type == Event::KeyPressed) {
        switch (event.key.code) {
          case Keyboard::B:
            ball.setFillColor(Color::Blue);
            info("Changed ball color to blue.");
            break;
          case Keyboard::R:
            if (event.key.shift) {
              view.reset(regular_viewport);
              info("Viewport reset.");
              break;
            }
            ball.setFillColor(Color::Red);
            info("Changed ball color to red.");
            break;
          case Keyboard::Y:
            ball.setFillColor(Color::Yellow);
            info("Changed ball color to yellow.");
            break;
          case Keyboard::G:
            ball.setFillColor(Color::Green);
            info("Changed ball color to green.");
            break;
        }
      }
    }
    // Clear screen
    window.clear();
    // Set window viewport to `view`
    window.setView(view);
    // Draw the sprite
    window.draw(ball);
    // Draw the string
    window.draw(text);
    // Update the window
    window.display();
  }
  return EXIT_SUCCESS;
}
