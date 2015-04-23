//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
#define PHEIGHT 10
#define PWIDTH 80

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    double velocity_x = drand48();
    double velocity_y = -2;
    waitForClick();

    // keep playing until game over
   
    while (lives > 0 && bricks > 0)
    {
       
       
        GEvent event = getNextEvent(MOUSE_EVENT);
        if(event != NULL)
        {
            if(getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - (PWIDTH/2);
                double y = getY(paddle);
                if(x >= 0 && x <= WIDTH - PWIDTH)
                {
                    setLocation(paddle, x, y);
                }
            }
        }

        move(ball, velocity_x, velocity_y);
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity_x = -velocity_x;
        }
        else if (getX(ball) <= 0)
        {
            velocity_x = -velocity_x;
        }
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball, WIDTH/2, HEIGHT/2);
            waitForClick();
            
        }
        else if (getY(ball) <= 0)
        {
            velocity_y = -velocity_y;
        }
        pause(10);
        
        GObject object = detectCollision(window, ball);
        if(object != NULL)
        {
            if (strcmp(getType(object), "GRect") == 0)
            {
                if (paddle == object)
                {
                    if(velocity_y > 0)
                    {
                    velocity_y = -velocity_y;
                    }
                }
                
                else
                {
                    removeGWindow(window, object);
                    velocity_y = -velocity_y;
                    bricks--;
                    points++;
                    updateScoreboard(window, label, points);
                    
                }
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    //decides width per brick if gap is 2 pixcels.
    int gap=5;
    double width_brick = (WIDTH - gap*(COLS+1))/COLS;
    double height_brick = 10;
    double x = gap,y = gap;
    char* colour_bricks[ROWS];
    int j = 0;
    
    for(int i = 0; i < ROWS; i++)
    {
        char* colours[9] = {"BLUE", "CYAN", "GRAY", "GREEN", "MAGENTA", "ORANGE", "PINK", "RED", "YELLOW"};
        colour_bricks[i]=colours[j];
        if(j<9)
        {
            j++;
        }
        else
        {
            j=0;
        }
    }
    for(int i=0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(x, y+50, width_brick, height_brick);
            setColor(brick, colour_bricks[i]);
            setFilled(brick, true);
            add(window, brick);
            x=width_brick+x+gap;
            
        }
        x=gap;
        y=height_brick+y+gap;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2, HEIGHT/2, 2*RADIUS, 2*RADIUS);
    setFilled(ball, true);
    add(window, ball); 
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    
    double x = (getWidth(window) - PWIDTH) / 2;
    double y = (getHeight(window) - 80);
    GRect paddle = newGRect(x, y, PWIDTH, PHEIGHT);
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
    
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setFont(label, "SansSerif-40");
    setColor(label, "LIGHT_GRAY");
    add(window, label);
    setLocation(label, x, y);

    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
