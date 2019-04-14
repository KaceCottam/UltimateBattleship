# Battleship Ideas

## GUI

We can use `sf::FloatRect` for areas on the screen that are important.

These can be set up in a class called `Button`, stated below.

```cpp
// A button class
class Button {
public:
  // Functions that draw according to state.
  void OnHover() = 0;
  void OnEnter() = 0;
  void OnExit() = 0;
  void OnMove() = 0;

  void OnClick() = 0;

  /*
   * A function for updating the look of the button
   * Needs the window so we can tell if the mouse
   * is over the button in the window.
   */
  void Update(const sf::Window &window);

  const sf::Shape* GetButtonShape() const;

private:
  enum MouseState {
    MOUSE_ENTER,
    MOUSE_HOVER,
    MOUSE_MOVE,
    MOUSE_EXIT
  } mouse_state_;
  sf::Shape* button_shape_;
};
```

The button will update its appearance each frame. It will use the window
reference in the update function to do this.

To simplify this further and make this more modular we could have two base
classes, IHoverable and IClickable which would provide us with more accessability.

```cpp
/// All classes will be in separate files!

// base class for telling if the mouse is hovering over an object.
class IHoverable {
protected:
  // Functions that change the shape according to state.
  void OnHover(sf::Shape &shape) = 0;
  void OnEnter(sf::Shape &shape) = 0;
  void OnExit(sf::Shape &shape) = 0;
  void OnMove(sf::Shape &shape)  = 0;
};

// base class for calling a function if the mouse clicked an object.
class IClickable {
protected:
  void OnClick(sf::Shape &shape) = 0;
};

// a button class, handles both drawing and clicking on.
class Button
  : IHoverable, IClickable {
protected:

  /*
   * A function for updating the look of the button
   * Needs the window so we can tell if the mouse
   * is over the button in the window.
   */
  void Update(const sf::Window &window);

  private:
  sf::Shape button_shape_;
  // We wouldn't need a mouse state because it is handled by the base classes.
};
```

## State Machine

We will definitely need a state machine for:

  1. Main Menu
  2. Connection Screen
  3. Options
  4. Ship Setup Screen
  5. Battle Screen

We should have a program-wide singleton state machine. We can set up game
screens into "scenes" like in Unity, Unreal Engine, and other game engines.
