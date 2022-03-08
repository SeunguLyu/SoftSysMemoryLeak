# MemoryLeak - Interactive C Game In Terminal

## Members
[SeungU Lyu](https://github.com/SeunguLyu)

## Overview
This project focuses on creating a simple interactive game with C from scratch that can be played directly in a terminal window. The game will be similar to old Shoot'em up genre games like the *Space Invaders(1978)* in the sense of graphics and style. Characters and enemies will be portrayed with Unicode characters. The main goal will be using the arrow keys to survive as long as possible from emerging enemies - the character that moves with the user input will shoot bullets automatically toward the enemies. When the user picks up the power-up item, the number of bullets and speed of bullets will vary so that the player can survive longer. The MVP for this project will be able to get user input, be able to collide with an enemy (game over condition), be able to kill an enemy with the bullet.

The current state of the project is almost at MVP, where there is collision detection with the enemy and the character, yet there's no bullet to kill the enemy. Once the bullet is implemented and MVP is reached, we will start implementing the stretch goals, such as adding multiple enemies that have simple AI, adding a power-up system, adding a scoring system, and adding difficulties over time. 

![](/reports/img1.png)
![](/reports/img2.png)
![](/reports/img3.png)

## Learning Goals
- Learn the advantages and disadvantages of using C for coding games.
- Understand the C structure better by finishing a project.
- Create a clean, efficient program that runs fast without major flaws (like memory leaks)
- Get used to how C manages memories and different data structures.

## Resources
The resources we used to build the project were mostly stack-overflow and looking at an existing project that uses the ncurses library to implement games with C such as [Tetris](https://github.com/brenns10/tetris). Most of our time was used to understand how to use ncurses, looking at some documentation such as [Ncurses HOWTO](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/). Ncurses is such an old library that there is too much information about it on the web, that finding the right type of information was a bit challenging sometimes.

## Next Steps
1. Add bullets that will shoot automatically. The direction of the bullet rotates clockwise, enabling the user to cover all 8 sides. The task is done if the bullet can delete the enemy when hit.
2. Create a smart spawn system that will make sure that enemies/spawns/power-ups/player isn't at the same position. The task is done when the game can track where all the objects are and avoid creating something in the same position.
3. Create simple AI so that enemies can slowly approach the player. The task is done if the enemies do not randomly move around but show a clear pattern.

## Links
[Todoist](https://todoist.com/app/project/2285818211)
[Github](https://github.com/SeunguLyu/SoftSysMemoryLeak)