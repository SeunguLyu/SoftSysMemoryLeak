#include "game.h"

//current terminal size
int g_terminal_y = 0, g_terminal_x = 0;

//game status controls game behavior
int g_game_status = 0;
int g_title_selection = 0;

//player variables
int g_player_dir = -1;
int g_player_x = WIDTH/2;
int g_player_y = (HEIGHT-6)/2 + 6;

int g_player_move_frame = MAX_PLAYER_MOVE_FRAME;
int g_current_player_move_frame = 0;

//power-up variables
int g_current_pow = 0;
int g_current_spd = 0;
int g_current_score = 0;

PowerUp g_pow_up;
PowerUp g_spd_up;
int g_power_up_color_frame = 100;
int g_current_power_up_color_frame = 0;

//enemy variables
int g_enemy_move_frame = MAX_ENEMY_MOVE_FRAME;
int g_enemy_spawn_frame = MAX_ENEMY_SPAWN_FRAME;
int g_current_enemy_spawn_frame = 0;
Enemy g_enemies[MAX_ENEMY];
int g_enemy_position_map[WIDTH][HEIGHT];

//bullet variables
int g_bullet_move_frame = MAX_BULLET_MOVE_FRAME;
int g_bullet_spawn_frame = MAX_BULLET_SPAWN_FRAME;
int g_current_bullet_spawn_frame = 0;
int g_bullet_dir = 0;
Bullet g_bullet[MAX_BULLET];

//score variables
int g_score_up_frame = MAX_SCORE_UP_FRAME;
int g_current_score_up_frame = 0;

const char TITLE_LOGO[][300] = {

    "███╗░░░███╗███████╗███╗░░░███╗░█████╗░██████╗░██╗░░░██╗██╗░░░░░███████╗░█████╗░██╗░░██╗",
    "████╗░████║██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝██║░░░░░██╔════╝██╔══██╗██║░██╔╝",
    "██╔████╔██║█████╗░░██╔████╔██║██║░░██║██████╔╝░╚████╔╝░██║░░░░░█████╗░░███████║█████═╝░",
    "██║╚██╔╝██║██╔══╝░░██║╚██╔╝██║██║░░██║██╔══██╗░░╚██╔╝░░██║░░░░░██╔══╝░░██╔══██║██╔═██╗░",
    "██║░╚═╝░██║███████╗██║░╚═╝░██║╚█████╔╝██║░░██║░░░██║░░░███████╗███████╗██║░░██║██║░╚██╗",
    "╚═╝░░░░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝",
};

const char GAME_OVER_LOGO[][300] = {
    
    "░██████╗░░█████╗░███╗░░░███╗███████╗░█████╗░██╗░░░██╗███████╗██████╗░",
    "██╔════╝░██╔══██╗████╗░████║██╔════╝██╔══██╗██║░░░██║██╔════╝██╔══██╗",
    "██║░░██╗░███████║██╔████╔██║█████╗░░██║░░██║╚██╗░██╔╝█████╗░░██████╔╝",
    "██║░░╚██╗██╔══██║██║╚██╔╝██║██╔══╝░░██║░░██║░╚████╔╝░██╔══╝░░██╔══██╗",
    "╚██████╔╝██║░░██║██║░╚═╝░██║███████╗╚█████╔╝░░╚██╔╝░░███████╗██║░░██║",
    "░╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝╚══════╝░╚════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝",
};

const char TITLE_DESCRIPTION[][100] = {
    "A long time ago in a SoftSys class far, far away...",
    "An Oliner decided to finish their project in a single day...",
    "It worked perfectly on the day it was presented...",
    "Without knowing that the memory was leaking!!!",
    "You accidentally compiled the program...",
    "And now you have to free all the leaking memories!"
};

const char EXTRA_DESCRIPTION[][30] = {
    "Start Game",
    "Exit Game",
    "Press W,A,S,D to move",
    "Press ENTER to Select",
    "Your Final Score: ",
    "Press ENTER to Exit Game...",
};

/* title: display the title screen of the game on the window. 
    Receive user input W, S, ENTER to start the game or exit the game */

void title(WINDOW *win)
{
    //wclear(win);
    werase(win);
    box(win,0,0);

    char in = getch();
    int end = 0;

    switch(in)
    {
        case 'w':
            g_title_selection -= 1;
            break;
        case 's':
            g_title_selection += 1;
            break;
        case '\n':
            end = 1;
            break;
    }

    if (g_title_selection == 2)
    {
        g_title_selection = 0;
    }
    else if (g_title_selection == -1)
    {
        g_title_selection = 1;
    }
    
    flushinp();

    wattron(win,COLOR_PAIR(3));
    for (int i = 0; i<6; i++)
    {
        mvwprintw(win, 5+i, 7, TITLE_LOGO[i]);
    }
    wattroff(win,COLOR_PAIR(3));

    for (int i = 0; i<6; i++)
    {
        int xpos = (WIDTH - strlen(TITLE_DESCRIPTION[i]))/2;
        mvwprintw(win, 14+2*i, xpos, TITLE_DESCRIPTION[i]);
    }

    int xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[2]))/2;
    wattron(win,COLOR_PAIR(1));
    mvwprintw(win, 27, xpos, EXTRA_DESCRIPTION[2]);
    xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[3]))/2;
    mvwprintw(win, 29, xpos, EXTRA_DESCRIPTION[3]);
    wattroff(win,COLOR_PAIR(1));
    
    if (g_title_selection == 0)
    {
        int xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[0]))/2;
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win, 32, xpos, EXTRA_DESCRIPTION[0]);
        wattroff(win,COLOR_PAIR(2));
        wattron(win,COLOR_PAIR(4));
        xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[1]))/2;
        mvwprintw(win, 34, xpos, EXTRA_DESCRIPTION[1]);
        wattroff(win,COLOR_PAIR(4));
    }
    else
    {
        int xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[0]))/2;
        wattron(win,COLOR_PAIR(4));
        mvwprintw(win, 32, xpos, EXTRA_DESCRIPTION[0]);
        wattroff(win,COLOR_PAIR(4));
        xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[1]))/2;
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win, 34, xpos, EXTRA_DESCRIPTION[1]);
        wattroff(win,COLOR_PAIR(2));
    }

    if (end == 1)
    {
        if (g_title_selection == 0)
        {
            g_game_status = 2;
            spawn_power_up(0);
            spawn_power_up(1);
            wclear(win);
        }
        else
        {
            g_game_status = -1;
        }
    }
    
    wrefresh(win);
    usleep(DELAY);
}

/* gameover: display the game over screen of the game on the window. 
    Receive user ENTER to exit the game */

void gameover(WINDOW *win)
{
    wclear(win);
    //werase(win);
    box(win,0,0);

    char in = getch();
    int end = 0;

    switch(in)
    {
        case '\n':
            end = 1;
            break;
    }

    wattron(win,COLOR_PAIR(3));
    for (int i = 0; i<6; i++)
    {
        mvwprintw(win, 15+i, 15, GAME_OVER_LOGO[i]);
    }
    wattroff(win,COLOR_PAIR(3));

    int xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[4]))/2;
    wattron(win,COLOR_PAIR(5));
    mvwprintw(win, 25, xpos, EXTRA_DESCRIPTION[4]);
    wattroff(win,COLOR_PAIR(5));

    char score[] = "0 0 0 0 0 0";

    int score_value = g_current_score;

    score[0] = score_value/100000 +'0';
    score_value = score_value%100000;
    score[2] = score_value/10000 +'0';
    score_value = score_value%10000;
    score[4] = score_value/1000 +'0';
    score_value = score_value%1000;
    score[6] = score_value/100 +'0';
    score_value = score_value%100;
    score[8] = score_value/10 +'0';
    score_value = score_value%10;
    score[10] = score_value +'0';

    xpos = (WIDTH - strlen(score))/2;
    mvwprintw(win, 27, xpos, score);

    wattron(win,COLOR_PAIR(1));
    xpos = (WIDTH - strlen(EXTRA_DESCRIPTION[5]))/2;
    mvwprintw(win, 30, xpos, EXTRA_DESCRIPTION[5]);
    wattroff(win,COLOR_PAIR(1));

    if (end == 1)
    {
        g_game_status = -1;
    }

    nodelay(stdscr, 0);
    
    wrefresh(win);
    usleep(DELAY);
}

/* resize: show resize message if the terminal size is too small */

void resize()
{
    clear();
    mvprintw(1, 1, "Please resize the terminal and re-run the program");
    mvprintw(2, 1, "The size should be at least 100 columns and 40 lines");
    refresh();
    getch();
}

/* draw_player: draw the player character on the window */

void draw_player(WINDOW *win)
{
    wattron(win,COLOR_PAIR(1));
    mvwprintw(win, g_player_y, g_player_x,"⚇");
    wattroff(win,COLOR_PAIR(1));
}

/* draw_enemies: draw the enemy characters on the window.
    Only prints the enemies with live == 1 */

void draw_enemies(WINDOW *win)
{
    wattron(win,COLOR_PAIR(5));
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (g_enemies[i].live == 1)
        {
            mvwprintw(win, g_enemies[i].y, g_enemies[i].x,"⚉");
        }
    }
    wattroff(win,COLOR_PAIR(5));
}

/* draw_bullets: draw the bullets on the window.
    Only prints the bullets with live == 1 */

void draw_bullets(WINDOW *win)
{
    wattron(win,COLOR_PAIR(4));
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (g_bullet[i].live == 1)
        {
            mvwprintw(win, g_bullet[i].y, g_bullet[i].x,"•");
        }
    }
    wattroff(win,COLOR_PAIR(4));
}

/* draw_pow_up: draw power-up items on the window.
    Randomly changes to one of three colors every g_power_up_color_frame. */

void draw_pow_up(WINDOW *win)
{
    if (g_current_power_up_color_frame >= g_power_up_color_frame)
    {
        int current_color = g_pow_up.color;
        do
        {
            switch(rand() % 3)
            {
                case 0:
                    g_pow_up.color = 6;
                    break;
                case 1:
                    g_pow_up.color = 7;
                    break;
                case 2:
                    g_pow_up.color = 8;
                    break;
            }
        }
        while(g_pow_up.color == current_color);
        
        current_color = g_spd_up.color;
        do
        {
            switch(rand() % 3)
            {
                case 0:
                    g_spd_up.color = 6;
                    break;
                case 1:
                    g_spd_up.color = 7;
                    break;
                case 2:
                    g_spd_up.color = 8;
                    break;
            }
        }
        while(g_spd_up.color == current_color);
        g_current_power_up_color_frame = 0;
    }
    else
    {
        g_current_power_up_color_frame += 1;
    }

    if (g_pow_up.live == 1)
    {
        wattron(win,COLOR_PAIR(g_pow_up.color));
        mvwprintw(win, g_pow_up.y, g_pow_up.x,"P");
        wattroff(win,COLOR_PAIR(g_pow_up.color));
    }

    if (g_spd_up.live == 1)
    {
        wattron(win,COLOR_PAIR(g_spd_up.color));
        mvwprintw(win, g_spd_up.y, g_spd_up.x,"S");
        wattroff(win,COLOR_PAIR(g_spd_up.color));
    }
}

/* player_enemy_collision_check: check collision between player and enemy.
    When hit, change game status to 3 to make transition to game over */

void player_enemy_collision_check()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (g_enemies[i].x == g_player_x && g_enemies[i].y == g_player_y && g_enemies[i].live == 1)
        {
            g_game_status = 3;
        }
    }
}

/* bullet_enemy_collision_check: check collision between bullet and enemy.
    When hit, deactivate both the bullet and the enemy.
    Add KILL_SCORE to the current game score for every enemy hit. */

void bullet_enemy_collision_check()
{
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (g_enemies[i].live == 0)
        {
            continue;
        }
        for (int j = 0; j < MAX_BULLET; j++)
        {
            if (g_bullet[j].live == 0)
            {
                continue;
            }
            if (g_bullet[j].x == g_enemies[i].x && g_bullet[j].y == g_enemies[i].y)
            {
                g_enemy_position_map[g_enemies[i].x][g_enemies[i].y] = 0;
                g_enemies[i].live = 0;
                g_bullet[j].live = 0;
                g_current_score += KILL_SCORE;
                break;
            }
        }
    }
}

/* player_power_up_collision_check: check collision between player and power-up items.
    When hit with power up, add 1 to current power.
    When hit with speed up, improve player move speed, bullet spawn rate, and bullet move frame 
    Add DIFFICULTY_SCORE_AMOUNT to current score when hit.
    Spawn the power-up items again if they are not at the maximum value. */

void player_power_up_collision_check(WINDOW *win)
{
    if (g_pow_up.x == g_player_x && g_pow_up.y == g_player_y && g_pow_up.live == 1)
    {
        g_current_pow += 1;
        g_current_score += DIFFICULTY_SCORE_AMOUNT;

        g_pow_up.live = 0;
        if (g_current_pow < 8)
        {
            spawn_power_up(0);
        }
        wclear(win);
    }

    if (g_spd_up.x == g_player_x && g_spd_up.y == g_player_y && g_spd_up.live == 1)
    {
        g_current_spd += 1;
        g_current_score += DIFFICULTY_SCORE_AMOUNT;

        g_player_move_frame = MAX_PLAYER_MOVE_FRAME - (MAX_PLAYER_MOVE_FRAME - MIN_PLAYER_MOVE_FRAME)/8.0*g_current_spd;
        g_bullet_spawn_frame = MAX_BULLET_SPAWN_FRAME - (MAX_BULLET_SPAWN_FRAME - MIN_BULLET_SPAWN_FRAME)/8.0*g_current_spd;
        g_bullet_move_frame = MAX_BULLET_MOVE_FRAME - (MAX_BULLET_MOVE_FRAME - MIN_BULLET_MOVE_FRAME)/8.0*g_current_spd;
        g_spd_up.live = 0;
        if (g_current_spd < 8)
        {
            spawn_power_up(1);
        }
        wclear(win);
    }
}

/* enemy_move: move all the activated enemies that has enough frames to move. 
    Move toward the player by comparing current x,y position with the player character
    If x,y coordinate are both different, 50% chance to move toward each direction
    If either x, y coordinate is the same, move toward direction that is not same */

void enemy_move()
{
    for (int i = 0; i<MAX_ENEMY; i++)
    {
        if (g_enemies[i].live == 1)
        {
            if (g_enemies[i].current_move_frame >= g_enemy_move_frame)
            {
                int x_axis, y_axis;
                int x,y;

                x_axis = g_player_x - g_enemies[i].x;
                y_axis = g_player_y - g_enemies[i].y;

                x_axis = x_axis/abs(x_axis);
                y_axis = y_axis/abs(y_axis);

                if (x_axis != 0 && y_axis != 0)
                {
                    switch(rand() % 2)
                    {
                        case 0:
                            x = g_enemies[i].x + x_axis;
                            y = g_enemies[i].y;
                            break;
                        case 1:
                            x = g_enemies[i].x;
                            y = g_enemies[i].y + y_axis;
                            break;
                    }
                }
                else if (x_axis != 0)
                {
                    x = g_enemies[i].x + x_axis;
                    y = g_enemies[i].y;
                }
                else if (y_axis != 0)
                {
                    x = g_enemies[i].x;
                    y = g_enemies[i].y + y_axis;
                }

                if (x == 1 || x == (WIDTH - 1) || y == 6 || y == (HEIGHT - 1))
                {
                    continue;
                }

                if (g_enemy_position_map[x][y] == 0)
                {
                    g_enemy_position_map[g_enemies[i].x][g_enemies[i].y] = 0;
                    g_enemies[i].x = x;
                    g_enemies[i].y = y;
                    g_enemy_position_map[x][y] = 1;

                    g_enemies[i].current_move_frame = 0;
                }
            }
            else
            {
                g_enemies[i].current_move_frame += 1;
            }
        }
    }
}

/* bullet_move: move all the activated bullets that has enough frames to move. 
    Move toward the direction set when the bullet was spawned.
    When bullet traveled the maximum distance or is out of screen, deactivate it. */

void bullet_move()
{
    for (int i = 0; i<MAX_BULLET; i++)
    {
        if (g_bullet[i].live == 1)
        {
            if (g_bullet[i].current_move_frame >= g_bullet_move_frame)
            {
                int x,y;
                x = g_bullet[i].x;
                y = g_bullet[i].y;
                switch(g_bullet[i].dir)
                {
                    case 0:
                        y -= 1;
                        break;
                    case 1:
                        x += 1;
                        y -= 1;
                        break;
                    case 2:
                        x += 1;
                        break;
                    case 3:
                        x += 1;
                        y += 1;
                        break;
                    case 4:
                        y += 1;
                        break;
                    case 5:
                        x -= 1;
                        y += 1;
                        break;
                    case 6:
                        x -= 1;
                        break;
                    case 7:
                        x -= 1;
                        y -= 1;
                        break;
                }

                if (x == 1 || x == (WIDTH - 1) || y == 6 || y == (HEIGHT - 1))
                {
                    g_bullet[i].live = 0;
                }
                else
                {
                    g_bullet[i].x = x;
                    g_bullet[i].y = y;
                    g_bullet[i].travel_distance += 1;
                    g_bullet[i].current_move_frame = 0;
                }

                if (g_bullet[i].travel_distance == g_current_pow * 3 + 4)
                {
                    g_bullet[i].live = 0;
                }
                
            }
            else
            {
                g_bullet[i].current_move_frame += 1;
            }
        }
    }
}

/* spawn_enemy: activate a single enemy if there is enough enemy spawn frame. 
    Do not activate if the number of enemies reached at maximum.
    Activate and place enemy randomly on the border of the screen.
    Skip the current frame if there's already enemy in the spawning coordinate. */

void spawn_enemy()
{
    if (g_current_enemy_spawn_frame >= g_enemy_spawn_frame)
    {
        int empty;
        for (int i = 0; i<MAX_ENEMY; i++)
        {
            if (g_enemies[i].live == 0)
            {
                empty = i;
                break;
            }
            else if (i == MAX_ENEMY - 1)
            {
                return;
            }
        }

        int x,y;
        int pattern;

        pattern = rand() % 4;

        switch(pattern)
        {
            case 0:
                x = 2;
                y = 7+(rand() % (HEIGHT-8));
                break;
            case 1:
                x = 2+(rand() % (WIDTH-4));
                y = 7;
                break;
            case 2:
                x = WIDTH - 3;
                y = 7+(rand() % (HEIGHT-8));
                break;
            case 3:
                x = 2+(rand() % (WIDTH-4));
                y = HEIGHT - 3;
                break;
        }

        if (g_enemy_position_map[x][y] == 0)
        {
            g_enemies[empty].live = 1;
            g_enemies[empty].x = x;
            g_enemies[empty].y = y;
            g_enemies[empty].current_move_frame = 0;

            g_enemy_position_map[x][y] = 1;

            g_current_enemy_spawn_frame = 0;
        }
    }
    else
    {
        g_current_enemy_spawn_frame += 1;
    }
}

/* spawn_bullet: activate bullets if there is enough bullet spawn frame. 
    Do not activate if the number of bullets reached at maximum.
    Activate and place bullets around the player character depending on current power level.
    Do not activate if the bullet is out of boundary.
    Rotate the shooting direction every time spawn_bullet is called successfully. */

void spawn_bullet()
{
    if (g_current_bullet_spawn_frame >= g_bullet_spawn_frame)
    {
        int current_dir = g_bullet_dir;

        for (int j = 0; j <g_current_pow; j++)
        {
            int empty;
            for (int i = 0; i<MAX_BULLET; i++)
            {
                if (g_bullet[i].live == 0)
                {
                    empty = i;
                    break;
                }
                else if (i == MAX_BULLET - 1)
                {
                    g_current_bullet_spawn_frame = 0;
                    return;
                }
            }

            int x, y;

            x = g_player_x;
            y = g_player_y;

            switch(current_dir)
            {
                case 0:
                    y -= 1;
                    break;
                case 1:
                    x += 1;
                    y -= 1;
                    break;
                case 2:
                    x += 1;
                    break;
                case 3:
                    x += 1;
                    y += 1;
                    break;
                case 4:
                    y += 1;
                    break;
                case 5:
                    x -= 1;
                    y += 1;
                    break;
                case 6:
                    x -= 1;
                    break;
                case 7:
                    x -= 1;
                    y -= 1;
                    break;
            }

            if (x == 1 || x == (WIDTH - 1) || y == 6 || y == (HEIGHT - 1))
            {

            }
            else
            {
                g_bullet[empty].live = 1;
                g_bullet[empty].dir = current_dir;
                g_bullet[empty].current_move_frame = 0;
                g_bullet[empty].travel_distance = 0;
                g_bullet[empty].x = x;
                g_bullet[empty].y = y;
            }

            current_dir += 1;

            if (current_dir >= 8)
            {
                current_dir = 0;
            }
        }

        g_current_bullet_spawn_frame = 0;
        g_bullet_dir += 1;

        if (g_bullet_dir >= 8)
        {
            g_bullet_dir = 0;
        }
    }
    else
    {
        g_current_bullet_spawn_frame += 1;
    }
}

/* spawn_power_up: activate power-ups. 
    Spawns the power-up at random x,y coordinate that does not have power-up item already. */

void spawn_power_up(int type)
{
    if (type == 0)
    {
        int x,y;
        do
        {
            x = 3+(rand() % (WIDTH-6));
            y = 8+(rand() % (HEIGHT-10));
        }
        while(x == g_spd_up.x && y == g_spd_up.y);

        g_pow_up.live = 1;
        g_pow_up.x = x;
        g_pow_up.y = y;
        g_pow_up.color = 6;
    }
    else if (type == 1)
    {
        int x,y;
        do
        {
            x = 3+(rand() % (WIDTH-6));
            y = 8+(rand() % (HEIGHT-10));
        }
        while(x == g_pow_up.x && y == g_pow_up.y);

        g_spd_up.live = 1;
        g_spd_up.x = x;
        g_spd_up.y = y;
        g_spd_up.color = 6;
    }
}

/* draw_rectangle: draws rectangle for UI elements on the window. */

void draw_rectangle(WINDOW *win, int y1, int x1, int y2, int x2)
{
    mvwhline(win, y1, x1, 0, x2-x1);
    mvwhline(win, y2, x1, 0, x2-x1);
    mvwvline(win, y1, x1, 0, y2-y1);
    mvwvline(win, y1, x2, 0, y2-y1);
    mvwaddch(win, y1, x1, ACS_ULCORNER);
    mvwaddch(win, y2, x1, ACS_LLCORNER);
    mvwaddch(win, y1, x2, ACS_URCORNER);
    mvwaddch(win, y2, x2, ACS_LRCORNER);
}

/* draw_score_UI: draws score UI on the window. */

void draw_score_UI(WINDOW *win)
{
    mvwhline(win, 6, 1, 0, WIDTH-2);
    draw_rectangle(win, 1, 2, 5, WIDTH - 3);

    wattron(win,COLOR_PAIR(5));
    switch(g_current_pow)
    {
        case 0:
            mvwprintw(win, 3, 9,"POW □□□□□□□□");
            break;
        case 1:
            mvwprintw(win, 3, 9,"POW ■□□□□□□□");
            break;
        case 2:
            mvwprintw(win, 3, 9,"POW ■■□□□□□□");
            break;
        case 3:
            mvwprintw(win, 3, 9,"POW ■■■□□□□□");
            break;
        case 4:
            mvwprintw(win, 3, 9,"POW ■■■■□□□□");
            break;
        case 5:
            mvwprintw(win, 3, 9,"POW ■■■■■□□□");
            break;
        case 6:
            mvwprintw(win, 3, 9,"POW ■■■■■■□□");
            break;
        case 7:
            mvwprintw(win, 3, 9,"POW ■■■■■■■□");
            break;
        case 8:
            mvwprintw(win, 3, 9,"POW ■■■■■■■■");
            break;
    }
    wattroff(win,COLOR_PAIR(5));

    mvwvline(win, 2, 35, 0, 3);

    wattron(win,COLOR_PAIR(4));
    switch(g_current_spd)
    {
        case 0:
            mvwprintw(win, 3, 42,"SPD □□□□□□□□");
            break;
        case 1:
            mvwprintw(win, 3, 42,"SPD ■□□□□□□□");
            break;
        case 2:
            mvwprintw(win, 3, 42,"SPD ■■□□□□□□");
            break;
        case 3:
            mvwprintw(win, 3, 42,"SPD ■■■□□□□□");
            break;
        case 4:
            mvwprintw(win, 3, 42,"SPD ■■■■□□□□");
            break;
        case 5:
            mvwprintw(win, 3, 42,"SPD ■■■■■□□□");
            break;
        case 6:
            mvwprintw(win, 3, 42,"SPD ■■■■■■□□");
            break;
        case 7:
            mvwprintw(win, 3, 42,"SPD ■■■■■■■□");
            break;
        case 8:
            mvwprintw(win, 3, 42,"SPD ■■■■■■■■");
            break;
    }
    wattroff(win,COLOR_PAIR(4));

    mvwvline(win, 2, 68, 0, 3);

    char score[] = "SCORE 0 0 0 0 0 0";

    int score_value = g_current_score;

    score[6] = score_value/100000 +'0';
    score_value = score_value%100000;
    score[8] = score_value/10000 +'0';
    score_value = score_value%10000;
    score[10] = score_value/1000 +'0';
    score_value = score_value%1000;
    score[12] = score_value/100 +'0';
    score_value = score_value%100;
    score[14] = score_value/10 +'0';
    score_value = score_value%10;
    score[16] = score_value +'0';

    wattron(win,COLOR_PAIR(3));
    mvwprintw(win, 3, 75,"%s", score);
    wattroff(win,COLOR_PAIR(3));
}

/* difficulty_control: controls enemy move speed and spawn rate over time.
    Also adds TIME_SCORE if there is enough score up frame.
    Rate of earning score also increases over time. */

void difficulty_control()
{
    if (g_current_score_up_frame >= g_score_up_frame)
    {
        g_current_score += TIME_SCORE;
        g_current_score_up_frame = 0;
    }
    else
    {
        g_current_score_up_frame += 1;
    }

    int difficulty_level;

    difficulty_level = g_current_score/DIFFICULTY_SCORE_AMOUNT;

    if (difficulty_level > MAX_DIFFICULTY_LEVEL)
    {
        difficulty_level = MAX_DIFFICULTY_LEVEL;
    }

    g_enemy_move_frame = MAX_ENEMY_MOVE_FRAME - (MAX_ENEMY_MOVE_FRAME - MIN_ENEMY_MOVE_FRAME)/(float)MAX_DIFFICULTY_LEVEL*difficulty_level;
    g_enemy_spawn_frame = MAX_ENEMY_SPAWN_FRAME - (MAX_ENEMY_SPAWN_FRAME - MIN_ENEMY_SPAWN_FRAME)/(float)MAX_DIFFICULTY_LEVEL*difficulty_level;
    g_score_up_frame = MAX_SCORE_UP_FRAME - (MAX_SCORE_UP_FRAME - MIN_SCORE_UP_FRAME)/(float)MAX_DIFFICULTY_LEVEL*difficulty_level;
}

/* gameplay: display the main game screen on the window
    Gets user input for keys W, S, A, D for movement direction. 
    Moves the player character if there is enough player move frame. */

void gameplay(WINDOW *win)
{
    //wclear(win);
    werase(win);

    box(win,0,0);
    
    draw_score_UI(win);

    char in = getch();

    switch(in)
    {
        case 'w':
            g_player_dir = 0;
            break;
        case 's':
            g_player_dir = 1;
            break;
        case 'a':
            g_player_dir = 2;
            break;
        case 'd':
            g_player_dir = 3;
            break;
    }
    
    if (g_current_player_move_frame >= g_player_move_frame)
    {
        switch(g_player_dir)
        {
            case 0:
                if (g_player_y > 7)
                    g_player_y -= 1;
                break;
            case 1:
                if (g_player_y < HEIGHT - 2)
                    g_player_y += 1;
                break;
            case 2:
                if (g_player_x > 2)
                    g_player_x -= 1;
                break;
            case 3:
                if (g_player_x < WIDTH - 2)
                    g_player_x += 1;
                break;
        }
        g_current_player_move_frame = 0;
    }
    else
    {
        g_current_player_move_frame += 1;
    }
    
    flushinp();

    difficulty_control();

    spawn_enemy();
    enemy_move();

    spawn_bullet();
    bullet_move();

    draw_pow_up(win);
    draw_enemies(win);
    draw_player(win);
    draw_bullets(win);

    player_enemy_collision_check();
    bullet_enemy_collision_check();
    player_power_up_collision_check(win);

    wrefresh(win);
    usleep(DELAY);
}

/* initialize_colors: initialize colors used for Ncurses */

void initialize_colors()
{
    start_color();
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_WHITE);
    init_pair(3,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_RED,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(7,COLOR_BLUE,COLOR_BLACK);
    init_pair(8,COLOR_GREEN,COLOR_BLACK);
}