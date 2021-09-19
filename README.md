# cub3d
This project is inspired by the world-famous **Wolfenstein 3D** game, which was the first FPS ever.
It was enable me to explore ray-casting.
The goal is to make a dynamic view inside a maze, in which player will have to find your way.

<img src="https://i.giphy.com/media/YlgU3YYqkOksEwM3aC/giphy-downsized.gif" data-canonical-src="https://i.giphy.com/media/YlgU3YYqkOksEwM3aC/giphy-downsized.gif" width="640" height="480" />

## Features

* Display different wall textures (your choice) that change depending on which side the wall is facing (north, south, east, west).

* Program also possible to set two different colours for the floor and ceiling.

* The left and right arrow keys of the keyboard  allow you to look left and right in the maze.

* The `W`, `A`, `S`, `D` keys allow you to move the point of view through the maze.

* Pressing ESC or clicking on the red cross on the window’s frame will close the window and quit the program cleanly.

## Configuration

**Program take as a first argument a scene description file with the `.cub` extension.**

* The map must be composed of only 6 possible characters:
	* `0` for an empty space.
	* `1` for a wall.
	* `N`, `S`, `E`, `W` for the player’s start position and spawning orientation.

* The map must be closed/surrounded by walls, if not the program will return an error

* Except for the map content, each type of element can be separated by one or more empty line or spaces(s).

* Except for the map content which always has to be the last, each type ofelement can be set in any order in the file.

* Each element (except the map) firsts information is the type identifier (com-posed by one or two character(s)), followed by all specific informations for eachobject in a strict order such as:
<br/>`NO ./path_to_the_north_texture`
	* identifier: **NO**
	* path to the north texure
