//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// distance between bricks
#define PADDING 3

// height of the brick
#define B_HEIGHT 8

// diameter of ball in pixels
#define RADIUS 10

// velocity of the ball
#define VELOCITY 3.0

// lives
#define LIVES 3

// paddle
#define P_HEIGHT 10
#define P_WIDTH 60

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
int getPoints(GObject brick);

int main(int argc, char* argv[])
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
    
    // velocity of the ball initially
    double xVelocity = (VELOCITY - 1) * (drand48() + 1);
    double yVelocity = VELOCITY;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        if (argc > 1 && strcmp(argv[1], "GOD") == 0)
        {
            double x = getX(ball) + getWidth(ball) / 2.0 - 
                       getWidth(paddle) / 2.0;
            double y = getY(paddle);
            if (x < 0)
            {
                x = 0;
            }
            else if (x > getWidth(window) - getWidth(paddle))
            {
                x = getWidth(window) - getWidth(paddle);
            }
            setLocation(paddle, x, y);
        }
        else
        {
            // implement paddle movement
            GEvent event = getNextEvent(MOUSE_EVENT);
            
            if (event != NULL)
            {
                if (getEventType(event) == MOUSE_MOVED)
                {
                    double x = getX(event) - getWidth(paddle) / 2;
                    double y = getY(paddle);
                    
                    if (x < 0)
                    {
                        x = 0;
                    }
                    else if (x > getWidth(window) - getWidth(paddle))
                    {
                        x = getWidth(window) - getWidth(paddle);
                    }
                    
                    setLocation(paddle, x, y);
                }
            }
        }
        
        // implement ball movement  
        move(ball, xVelocity / 2, yVelocity);
        pause(10);
        
        GObject object = detectCollision(window, ball);
        
        if (object != NULL && strcmp(getType(object), "GRect") == 0)
        {   
            yVelocity = -yVelocity;
            if (object != paddle)
            {
                points += getPoints(object);
                bricks--;
                removeGWindow(window, object);
                updateScoreboard(window, label, points);
            }
        }
        else if (getX(ball) <= 0 || getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xVelocity = -xVelocity;
        }
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            if (lives > 0)
            {
                waitForClick();
                removeGWindow(window, ball);
                ball = initBall(window);
            }
        }
        else if (getY(ball) <= 0)
        {
            yVelocity = -yVelocity;
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
    char* colors[] = {
        "BLUE", "CYAN", "GREEN", 
        "MAGENTA", "ORANGE", "PINK",
        "DARK_GRAY", "RED", "YELLOW" };
        
    double width = (getWidth(window) - PADDING * (COLS + 1)) / COLS;
    double height = B_HEIGHT;
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            double x = PADDING * (j + 1) + width * j;
            double y = 40 + (B_HEIGHT + PADDING) * i;
            
            GRect brick = newGRect(x, y, width, B_HEIGHT);
            setFilled(brick, true);
            setColor(brick, colors[i]);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double x = (getWidth(window) / 2 - RADIUS);
    double y = (getHeight(window) / 2 - RADIUS);
    
    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double x = (getWidth(window) - P_WIDTH) / 2;
    double y = HEIGHT - 40;
    
    GRect paddle = newGRect(x, y, P_WIDTH, P_HEIGHT);
    
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-42");
    setColor(label, "GRAY");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    
    setLocation(label, x, y);
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

int getPoints(GObject brick)
{
    int points;
    
    int y = getY(brick);
    switch(y)
    {
        case 40:
            points = 100;
            break;
        case 40 + (B_HEIGHT + PADDING):
            points = 50;
            break;
        case 40 + (B_HEIGHT + PADDING) * 2:
            points = 25;
            break;
        case 40 + (B_HEIGHT + PADDING) * 3:
            points = 10;
            break;
        case 40 + (B_HEIGHT + PADDING) * 4:
            points = 5;
            break;
        default:
            points = 1;
            break;
    }
    
    return points;
}
