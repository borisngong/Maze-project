# The Maze Project

Welcome to **The Maze Project**, a simple yet exciting maze game built using C and SDL2. Navigate a 3D world generated from a 2D map using raycasting techniques.

## Installation

### Cloning the Repository

To clone the repository, run the following command in your terminal:






The Maze Project
Welcome to The Maze Project, a simple yet exciting maze game built using C and SDL2. Navigate a 3D world generated from a 2D map using raycasting techniques.

Installation
Cloning the Repository
To clone the repository, run the following command in your terminal:

git clone https://github.com/borisngong/Maze-project.git

After cloning, enter the repository using:

cd Maze-project

Installing SDL2 with CMake
To install SDL2 using CMake, follow these steps:

Install CMake: If you don’t have CMake installed, you can install it on Ubuntu with:

sudo apt update
sudo apt install cmake

Download SDL2: Clone the SDL2 repository:

git clone https://github.com/libsdl-org/SDL.git

Build and Install SDL2:

Navigate into the SDL directory:

cd SDL

Create a build directory and navigate into it:

mkdir build
cd build

Run CMake to configure the build:

cmake ..

Compile and install SDL2:

make
sudo make install

Return to your project directory:

cd ../..

Compiling the Game
Ensure you have gcc and make installed on your system. You can install them on Ubuntu with:

sudo apt update
sudo apt install gcc make

To compile the game, run:

make

Running the Game
After compiling the project, play the game by executing:

./play_game

To quit the game, press the ESC key.

Controls
W: Move forward
S: Move backward
A: Look left
D: Look right
Cleaning Up
To remove compiled files and clean the project, run:

make clean

Future Features
Upcoming improvements to the game:

Enemies and AI interactions
Weather and lighting effects
Scoring system
Difficulty levels
Multiplayer functionality
Project Links
GitHub Repository: https://github.com/borisngong/Maze-project.git
Project Landing Page: http://borisngong.github.io/Maze-project/
LinkedIn Profile: 
