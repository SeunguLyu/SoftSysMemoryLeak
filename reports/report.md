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

One big design choice I had to make was using the Ncurses library over many different alternatives to show graphics for my game. Some other considerations included using "windows.h" to print an array of string every short period (which can be checked [here](https://github.com/SeunguLyu/SoftSysMemoryLeak/blob/89a6d7d65a316ad694ff2fe402ee1798256dfbc9/memoryleak.c)), or using [SDL2](https://www.libsdl.org/) library which is commonly used to develop games with C. Considering the scope of the project and available time and resources, I decided to use Ncurses which will serve the purpose of showing simple graphics with colors. This was a great choice because it enabled me to do things that cannot be done with windows.h such as using different colors, creating different windows for UI, and did not require Windows OS to run. One downside was that multiple key input was hard to implement since the game running on the terminal, but I simply gave up the diagonal movement for the game because the benefit of using Ncurses was much better. SDL2 could've been a great choice to develop the game. It comes with powerful tools that are enough to create commercial games, but I liked the idea of playing a game inside the terminal instead of the external window. I also thought that SDL2 might be too much for the scope of the project which aims to make a game similar to old shoot'em up games, leading me to choose Ncurses over SDL2.

One other design choice I made was implementing frames and delays. The game runs in a giant while loop and each calculation is done every 10000 microseconds due to the usage of 

```C
usleep(DELAY)
```

at the end of the loop. This simple code creates the concept of frames for the game, which enables the game to run on controlled time. The code is set to have a 10000-microsecond delay per frame, meaning that the game runs at approximately 100 frames per second. 

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

## Learning Goals
- Learn the advantages and disadvantages of using C for coding games.
- Understand the C structure better by finishing a project.
- Create a clean, efficient program that runs fast without major flaws (like memory leaks)
- Get used to how C manages memories and different data structures.

## Resources
The resources we used to build the project were mostly stack-overflow and looking at an existing project that uses the Ncurses library to implement games with C such as [Tetris](https://github.com/brenns10/tetris). Most of our time was used to understand how to use Ncurses, looking at some documentation such as [Ncurses HOWTO](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/). Ncurses is an old library that there is too much information about it on the web, that finding the right type of information was a bit challenging sometimes.

## Reflection
Creating a game with C was a very interesting experience. The most difficult part was trying to implement the game without using classes and objects. Structs served the same purpose but there was a clear limitation such as not being able to just pass the reference around instead of the actual values. Also, it was so easy to cause an error that was hard to find. For example, I had an issue where the enemy refused to spawn at the given rate, which later I found out the cause was due to me assigning the wrong seed value to the rand() function. Debugging was much harder compared to creating games with other languages because the cause of the error was often unclear. The process of coding and debugging helped me understand the C language better, but there's still a long way to go before being proficient with using it.

Personally, I don't think the program is efficient enough. I used a lot of global variables instead of pointers and heaps, which was a good choice in avoiding errors but not so great in the sense of efficiency. The part that I feel needs improvement is where the program checks the collision between different objects. The current computation time complexity is O(MxN), with a fixed size for M and N (for example, the current maximum for the enemy is 500 and the bullet is 60, which will end up in 30000 computation per frame). There are ways to improve this - dynamically allocating memory and re-allocating every time the program needs more memory will dramatically decrease the number of extra computations done by the program, and I can even briefly think about ways to reduce the time complexity to O(M) instead of O(MxN). If the program was planned better from the beginning, this was an issue that could've been avoided. Also, The current state of the project consists of one header, one giant file, and the main file. I tried to refactor them into small pieces but had difficulty due to writing functions without considering re-factoring. At least now I have a better understanding of the C structure and will do much better in my next project. 

Even though I see some flaws in the structure of the program, I like how I was able to avoid a major error like memory leak and got used to different data structures and memory management through this project. The project ended up completing all the stretch goals I mentioned in the proposal. I can say that I was able to achieve all my learning goals, either by doing it successfully or by failing. I hope to create a more satisfying project for my finals using the knowledge I gained through this project and all the course materials that I'll learn before the end of the semester.

## Links
[Github](https://github.com/SeunguLyu/SoftSysMemoryLeak)