# MemoryLeak - Interactive C Game In Terminal

## Members
[SeungU Lyu](https://github.com/SeunguLyu)

## Overview
This project focuses on creating a simple interactive game with C from scratch that can be played directly in a terminal window. The game will be similar to old Shoot'em up genre games like the *Space Invaders(1978)* in the sense of graphics and style. Characters and enemies will be portrayed with Unicode characters. The main goal will be using the arrow keys to survive as long as possible from emerging enemies - the character that moves with the user input will shoot bullets automatically toward the enemies. When the user picks up the power-up item, the number of bullets and speed of bullets will vary so that the player can survive longer. The MVP for this project will be able to get user input, be able to collide with an enemy (game over condition), be able to kill an enemy with the bullet. The Stretch goal will be making the game more engaging by adding multiple enemies that have simple AI, adding a power-up system, adding a scoring system, and adding difficulties over time. 

The game is currently finished with all the stretch goals implemented successfully. Here is some preview of the gameplay:

![Title](/Images/1.gif)

![Beginning](/Images/2.gif)

![Later](/Images/3.gif)

![Game Over](/Images/4.gif)

These are the major features of the game:

- The player character moves automatically in the direction of the last key input. It is similar to the movement of the "Snake Game".   
    - [Link](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L877)
- Bullets are automatically shot from the player character. The number/speed/rate of the bullet depends on the current power/speed up the status 
    - [Link 1](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L602)
    - [Link 2](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L472)
- Enemies spawn randomly from the edge of the map. The rate of spawn depends on the current score.
    - [Link](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L541)
- Enemies move toward the player's position, which creates a simple AI where enemies approach the player.
    - [Link](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L407)
- The game detects collisions between player-enemy, enemy-bullet, and player-power-up items. They are done by simple for loops comparing the x,y coordinate of each object. 
    - [Link 1](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L338)
    - [Link 2](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L349)
    - [Link 3](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L375)
- Power-up items change the number of directions of bullets, speed of bullets, rate of bullet fire, and speed of the player. 
    - [Link](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L375)
- The current score increases in three conditions: when the bullet hits an enemy when the player gets a power-up item, and when the player survives longer 
    - [Link 1](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L368)
    - [Link 2](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L380)
    - [Link 3](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L844)
- Speed of the enemy movement/spawn rate increases depending on the current score, adding more difficulties over time.
    - [Link](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/7ec0aedd0f9095d97e5e9f5a69dbc1250c3232f5/game.c#L840)


## Design Choices

One big design choice I had to make was using the Ncurses library over many different alternatives to show graphics for my game. Some other considerations included using "windows.h" to print an array of string every short period (which can be checked [here](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/89a6d7d65a316ad694ff2fe402ee1798256dfbc9/memoryleak.c)), or using [SDL2](https://www.libsdl.org/) library which is commonly used to develop games with C. Considering the scope of the project and available time and resources, I decided to use Ncurses which will serve the purpose of showing simple graphics with colors. This was a great choice because it enabled me to do things that cannot be done with windows.h such as using different colors, creating different windows for UI, and did not require Windows OS to run. One downside was that multiple key input was hard to implement since the game running on the terminal, but I simply gave up the diagonal movement for the game because the benefit was much better. SDL2 could've been a great choice to develop the game if I had more time to invest in the project, but it required a little more learning curve which wasn't ideal for a 3-week project (which eventually became a 4~5 week project but didn't know that at the beginning).

One other design choice I made was implementing frames and delays. The game runs in a giant while loop and each calculation is done every 10000 microseconds due to the usage of 

```C
usleep(DELAY)
```

at the end of the loop. This simple code creates the concept of frames for the game, which enables the game to run on time. The code is set to have a 10000-microsecond delay per frame, meaning that the game runs at approximately 100 frames per second. 

```C++
if (g_current_player_move_frame >= g_player_move_frame)
{
    switch(g_player_dir)
    {
        //perform movement
        ...
    }
    g_current_player_move_frame = 0;
}
else
{
    g_current_player_move_frame += 1;
}
```
By using the frames, actions done by the player/enemy can be precisely controlled. The example shows how the frame is used to control the player's movement. For every frame, the current player move frame will increase by 1 until it is equal to the player move frame and movement is executed. Changing the player move frame will change the behavior of the player in real-time without needing to re-compile the code. Every behavior of objects inside the game is controlled using this frames/delays mechanism. There might be a more clean and more efficient way to implement this, but the implementation above meets the requirement for my game and runs without big issue.

The last design choice I made was using multiple global variables instead of using pointers and heap. Using pointers and heap is efficient in many applications but has the risk of causing errors and memory leaks. Since the scope of the project is small and there isn't a big need for memory re-allocation, most variables are set as global variables to avoid possible errors. Currently, the size of the array that stores enemies and bullets are fixed with constant numbers. One possible way to make the program more efficient is to start with a small array size and re-allocate more memory later on. For example, the current size for enemy and bullet is 500 and 60 each. This means that for every frame the program has to check 30000 times to see if an enemy is colliding with a bullet. This might be useful in the latter part of the game when there are multiple enemies and multiple bullets, but not efficient at the beginning of the game. Using heap will enable us to set the limit of the enemies at something like 50 and the limit of bullets at 10 in the beginning, which will be only 500 computations per frame. Whenever the number of each object reaches the limit, re-allocating twice the size of array-like how the "List" data structure works in other languages-will efficiently adjust the size of the allocated memory. 

## Learning Goals
- Learn the advantages and disadvantages of using C for coding games.
- Understand the C structure better by finishing a project.
- Create a clean, efficient program that runs fast without major flaws (like memory leaks)
- Get used to how C manages memories and different data structures.

## Resources
The resources we used to build the project were mostly stack-overflow and looking at an existing project that uses the Ncurses library to implement games with C such as [Tetris](https://github.com/brenns10/tetris). Most of our time was used to understand how to use Ncurses, looking at some documentation such as [Ncurses HOWTO](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/). Ncurses is an old library that there is too much information about it on the web, that finding the right type of information was a bit challenging sometimes.

## Reflection
Creating a game with C was a very interesting experience. There is definitely difficulties in creating a 

## Links
[Todoist](https://todoist.com/app/project/2285818211)
[Github](https://github.com/SeunguLyu/SoftSysMemoryLeak)