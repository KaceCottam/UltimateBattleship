# Ultimate Battleship

Created for a final project in Washington State University's CPTS 122 course.

Currently, we are on a very early pre-release. The simple playable version is a subproject in the spike folder named
 "BasicBattleship". To build this project, make sure that you compile cmake with the option `-DBUILD_BasicBattleship=ON`.

## [Website](www.KaceCottam.github.io/UltimateBattleship) | [Github Index](docs/index.md)

An [SFML-Based](https://www.sfml-dev.org/index.php) Battleship program with networking capabilities.

We also use [fmt](https://github.com/fmtlib/fmt), and [spdlog](https://github.com/gabime/spdlog).
This project also uses [CMake](https://cmake.org/).

Built in Visual Studio Code and Visual Studio 2015.

## Contributing: See [this](docs/contrib.md)

## Project Layout

- [src](src/) is used for the source code of the project.
- [tests](tests/) is used for testing code.
- [spike](spike/) is used for testing projects. Simple things such as drawing balls and working out GUI constructs.
- [lib](lib/) is where we keep our libraries.
- [docs](docs/) is where we keep documentation.
- [assets](assets/) is where we keep things like sprites and sounds.
- [include](include/) is where we keep our self-made libraries.

## Installation

In the [releases](projects) tab. (When there is a release)

## Compiling

To compile, in the root directory use the command. (CMAKE IS REQUIRED)

```bash
cmake -B build -DBUILD_SOURCE=OFF -DBUILD_TESTS=OFF -DBUILD_SPIKE=ON -DBUILD_WindowAndDrawBall=OFF -DBUILD_ButtonTest=OFF -DBUILD_BoardTest=OFF -DBUILD_SceneManagerTest=OFF -DBUILD_BasicBattleship=ON
```

You can change `OFF`s to `ON`s if you want to compile a specific sub-project.

## Playing

Click singleplayer or multiplayer. In singleplayer you play against an AI. Choose a dificulty, then start playing!
In multiplayer you must connect to a host by IP Address, then you may play!

## Features *all subject to change

- [x] **GUI**
- [x] **Placing ships**
- [x] **Shooting ships**
- [x] **Winning or Losing**
- [x] Multiplayer seeing enemy ships // Splitscreen
- [x] Multiplayer shooting at enemy ships // Splitscreen
- [ ] Being shot at by an AI
- [ ] Singleplayer Difficulty options
- [ ] Special ship abilities?
- [ ] Maps?
- [ ] User-customizable maps?
\* Bolded items are on the priority list.
