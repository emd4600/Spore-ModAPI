This simple mod changes the creature editor play mode to allow walking out of the editor bounds. Before, the play mode was limited in a 5 units radius.
To achieve this, the mod detours two methods in the `Editors::CreatureWalkController` class, responsible of creature movement.
This also works with non-flat editors, as the code does a raycast check every frame to know the height of the floor.

Feel free to download this mod or include the code in your own! With this you can do cooler play mode environments.

![](https://imgur.com/WpjWV16)