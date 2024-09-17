# The Maze Project

Welcome to **The Maze Project**, a simple yet exciting maze game built using C and SDL2. Navigate a 3D world generated from a 2D map using raycasting techniques.

## Installation

### Cloning the Repository

To clone the repository, run the following command in your terminal:
git clone https://github.com/borisngong/Maze-project.git

After cloning, enter the repository using:

cd Maze-project

### Installing SDL2 with CMake

To install SDL2 using CMake, follow these steps:

1. **Install CMake making sure version is above 3**: If no cmake exists, insall on Ubuntu using:
2. sudo apt update sudo apt install cmake


2. **Download SDL2**: Clone the SDL2 repository:
git clone https://github.com/libsdl-org/SDL.git


3. **Build and Install SDL2**:

- Navigate into the SDL directory:

  ```
  cd SDL
  ```

- Create a build directory and navigate into it:

  ```
  mkdir build
  cd build
  ```

- Run CMake to configure the build:

  ```
  cmake ..
  ```

- Compile and install SDL2:

  ```
  make
  sudo make install
  ```

- Return to your project directory:

  ```
  cd ../..
  ```

### Compiling the Game

Ensure you have **gcc** and **make** installed on your system. if not install on Ubuntu with:
sudo apt update sudo apt install gcc make


To compile the game, run:

make


## Running the Game in the SDL window

After compilation, play the game by running the executable:
./play_game


To quit the game, press the **ESC** key.

## Controls

- **W**: Move forward  
- **S**: Move backward  
- **A**: Look left  
- **D**: Look right

## Cleaning Up

After compilation you can removed the compiled files by running:

make clean


## Future Features

In the nearest future, I intend to continue improving the game:

- Add player(s) and Weapons
- Enemies and objects
- Weather and lighting effects  
- Scoring system  
- levels
- Multiplayer

## Project Links

- **GitHub Repository**: [Maze Project GitHub](https://github.com/borisngong/Maze-project)
- **Project Landing Page**: [The Maze Project Landing Page](http://borisngong.github.io/Maze-project/)
- **LinkedIn Profile**: [Boris Ngong LinkedIn](https://www.linkedin.com/in/ngong-boris-kukwah-34063821a/)

