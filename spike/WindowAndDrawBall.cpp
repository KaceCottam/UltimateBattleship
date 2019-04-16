#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>

int main() {
  using fmt::format;
  using spdlog::info;
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
  Text text(
      "Hello SFML\n"
      "This is a short test for a ball and events.\n"
      "Click to move the ball.\n"
      "Press Q (grow) or E (shrink), or use the mouse wheel to scale the "
      "ball.\n"
      "You can make the ball Red, Blue, Green, and Yellow by pressing the key\n"
      "\tthat matches the first letter of the color.",
      font, 18);

  auto regular_viewport = FloatRect{0.f, 0.f, 800.f, 600.f};
  View view(regular_viewport);
  // variables for smooth zooming
  struct {
    bool out{false};
    bool in{false};
    const float factor{0.002};
  } zoom;

  struct {
    Vector2f pressed;
    Vector2f current;
  } mouse_properties;
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
        info("Changed zoom by a factor of {}."_format(
            event.mouseWheelScroll.delta));
      }
      // Move view if mouse held down
      if (event.type == Event::MouseButtonPressed &&
          event.mouseButton.button == Mouse::Left &&
          mouse_properties.pressed == Vector2f{0, 0}) {
        mouse_properties.pressed =
            Vector2f{(float)event.mouseButton.x - window.getPosition().x,
                     (float)event.mouseButton.y - window.getPosition().y};
        info("Mouse pressed at {{ {}, {} }}"_format(
          mouse_properties.pressed.x,mouse_properties.pressed.y));
      }
      if (event.type == Event::MouseButtonReleased &&
          event.mouseButton.button == Mouse::Left) {
        mouse_properties.pressed = {0, 0};
      }
      if (event.type == Event::MouseMoved &&
          mouse_properties.pressed != Vector2f{0, 0}) {
        mouse_properties.current =
            Vector2f{(float)event.mouseMove.x - window.getPosition().x,
                     (float)event.mouseMove.y - window.getPosition().y};
        Vector2f move{
            mouse_properties.pressed.x - mouse_properties.current.x,
            mouse_properties.pressed.y - mouse_properties.current.y};

        auto move_ratio = view.getSize().x / regular_viewport.width;
        info("move ratio : {}"_format(move_ratio));

        move *= move_ratio;

        mouse_properties.pressed = mouse_properties.current;
        info("Move {{ {}, {} }}"_format(move.x, move.y));
        view.move(move);
      }
      // Change ball size with Q (grow) and E (shrink) keys
      if (event.type == Event::KeyPressed && event.key.code == Keyboard::Q) {
        zoom.out = true;
      }
      if (event.type == Event::KeyReleased && event.key.code == Keyboard::Q) {
        zoom.out = false;
      }
      if (event.type == Event::KeyPressed && event.key.code == Keyboard::E) {
        zoom.in = true;
      }
      if (event.type == Event::KeyReleased && event.key.code == Keyboard::E) {
        zoom.in = false;
      }
    }
    // Change ball color if B, R, Y, or G is pressed
    if (Keyboard::isKeyPressed(Keyboard::R)) {
      ball.setFillColor(Color::Red);
      info("Changed ball color to red.");
    }
    if (Keyboard::isKeyPressed(Keyboard::B)) {
      ball.setFillColor(Color::Blue);
      info("Changed ball color to blue.");
    }
    if (Keyboard::isKeyPressed(Keyboard::Y)) {
      ball.setFillColor(Color::Yellow);
      info("Changed ball color to yellow.");
    }
    if (Keyboard::isKeyPressed(Keyboard::G)) {
      ball.setFillColor(Color::Green);
      info("Changed ball color to green.");
    }
    if (zoom.out) {
      view.zoom(1 + zoom.factor);
    }
    if (zoom.in) {
      view.zoom(1 - zoom.factor);
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
