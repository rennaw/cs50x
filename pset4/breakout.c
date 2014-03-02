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

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// define brick height and width
#define BR_HEIGHT 12
#define BR_WIDTH 30

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// speed constant
#define SPEED 4

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

// global color pallette
const string COLORS[6] = {"RED", "YELLOW", "GREEN", "CYAN", "BLUE", "MAGENTA"};

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

    // game starts after initial click
    waitForClick();

    // velocity for ball
    double velocity_x = drand48() * SPEED;
    double velocity_y = drand48() * SPEED;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {   
        // update ball location
        move(ball, velocity_x, velocity_y);
        pause(25);

        // update scoreboard
        updateScoreboard(window, label, points);

        // bounce ball off the walls
        if (getX(ball) <= 0 || getX(ball) + getWidth(ball) >= WIDTH)
        {
            velocity_x = -velocity_x;
        }
        // bounce off the ceiling
        if (getY(ball) <= 0)
        { 
            velocity_y = -velocity_y;
        }
        // if ball reaches the floor, lose a life
        if (getY(ball) + getHeight(ball) >= HEIGHT)
        {
            lives--;
            int bal_x = (WIDTH / 2) - (RADIUS / 2);
            int bal_y = (HEIGHT / 2) - (RADIUS / 2);
            setLocation(ball, bal_x, bal_y);
            velocity_x = drand48();
            velocity_y = drand48();
            waitForClick();
        }
        GObject collision = detectCollision(window, ball);
        if (collision != NULL)
        {
            if (strcmp(getType(collision), "GRect") == 0)
            {
                velocity_y = -velocity_y;
            
                if (collision != paddle)
                {
                    removeGWindow(window, collision);
                    points += lives;
                    bricks--;
                    updateScoreboard(window, label, points);
                }
            }
        }
        // listen for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard something
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // move paddle to follow cursor's x
                double pdl_x = getX(event) - BR_WIDTH;
                double pdl_y = getY(paddle);
                setLocation(paddle, pdl_x, pdl_y);
            }
        }
    }
    if (bricks == 0)
    {
        // makes victory message and replaces scoreboard
        removeGWindow(window, label);
        GLabel victory = newGLabel("You are the winner!");
        int victory_x = (WIDTH / 2) - (getWidth(victory) / 2);
        int victory_y = (HEIGHT / 2) - (getHeight(victory) / 2);
        setLocation(victory, victory_x, victory_y);
        add(window, victory);
    }
    if (lives == 0)
    {
        // makes defeat message and replaces scoreboard
        removeGWindow(window, label);
        GLabel defeat = newGLabel("You have lost all your lives....");
        int defeat_x = (WIDTH / 2) - (getWidth(defeat) / 2);
        int defeat_y = (HEIGHT / 2) - (getHeight(defeat) / 2);
        setLocation(defeat, defeat_x, defeat_y);
        add(window, defeat);
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
    // make some bricks
    for (int i = 0; i <= ROWS; i++)
    {
        for (int j = 0; j <= COLS; j++)
        {
            // this uses i to define y and j for x
            int br_x = (BR_WIDTH + 3) * j + 15;
            int br_y = (BR_HEIGHT + 3) * i + 30;

            // sets the color for the bricks for this row
            string br_color = COLORS[i];

            // makes instance of brick and adds to window
            GRect brick = newGRect(br_x, br_y, BR_WIDTH, BR_HEIGHT);
            setColor(brick, br_color);
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // set ball x, y, height, width 
    int bal_x = (WIDTH / 2) - (RADIUS / 2);
    int bal_y = (HEIGHT / 2) - (RADIUS / 2);
    int bal_height = RADIUS * 2;
    int bal_width = RADIUS * 2;
    GOval ball = newGOval(bal_x, bal_y, bal_height, bal_width);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
    
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int pdl_height = BR_HEIGHT;
    int pdl_width = BR_WIDTH * 2;
    int pdl_x = WIDTH / 2 - pdl_width / 2;
    int pdl_y = HEIGHT - pdl_height * 2;
    GRect paddle = newGRect(pdl_x, pdl_y, pdl_width, pdl_height);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // place scoreboard in middle of window
    GLabel label = newGLabel("0");
    add(window, label);
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
    double x = (getWidth(window) / 2) - (getWidth(label) / 2);
    double y = (getHeight(window) / 2) - (getHeight(label) / 2);
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
