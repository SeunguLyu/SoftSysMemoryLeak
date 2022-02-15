# MemoryLeak - Interactive C Game without Memory Leaks

## Members
[SeungU Lyu](https://github.com/SeunguLyu)

## Overview
This project focuses on creating a simple interactive game with C from scratch. The game will be similar to old Shoot'em up genre games like the *Space Invaders(1978)* in the sense of graphics and style. Characters and enemies will be portrayed as simple symbol characters (such as @, *, $), and the game will run on either a terminal window or an external window from the windows.h library. The main goal will be using the arrow keys to survive as long as possible from emerging enemies - the character that moves with the user input will shoot bullets automatically toward the enemies. When the user picks up the power-up item, the number of bullets and speed of bullets will vary so that the player can survive longer. The MVP for this project will be able to get user input, be able to collide with an enemy (game over condition), be able to kill an enemy with the bullet. The Stretch goal will be making the game more engaging by adding multiple enemies that have simple AI, adding a power-up system, adding a scoring system, and adding difficulties over time. We are confident that we will be able to finish the MVP, but hopefully, we can finish all the stretch goals in time.

## Learning Goals
- Learn the advantages and disadvantages of using C for coding games.
- Understand the C structure better by finishing a project.
- Create a clean, efficient program that runs fast without major flaws (like memory leaks)

## Resources
There are so many good resources out there. I will start with looking at [Project Based Tutorials in C](https://github.com/rby90/project-based-tutorials-in-c?fbclid=IwAR0LFioeE0KdA_KFLhevb2YDz0_z1djQlravOBZUQQ0NV4dNBIY3iGEhBCw#game-development) Github repo, which I think is a good way to start with a game project.

## Initial Steps
1. Decide which display we want to use for our game, and create a simple character to move around according to the user input.
2. Create a time frame system in the game so that collision detection, character/enemy movement, enemy spawn, etc. can be calculated for every frame.
3. Implement a simple system that will end the game and restart the game if possible.