//Ping-Pong Game In C
//A.Goktug
//19.08.2024
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define WIDTH 40
#define HEIGHT 10
#define PADDLE_SIZE 3

int kbhit(void) 
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) 
	{
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void draw(int ballX, int ballY, int paddleY, int score) 
{
    printf("\033[H\033[J");

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf(" Credits: A.Goktug\n");

    for (int y = 0; y < HEIGHT; y++) 
	{
        printf("#");
        for (int x = 0; x < WIDTH; x++)
		{
            if (x == ballX && y == ballY)
			{
                printf("O");
            } else if (x == WIDTH - 1 && y >= paddleY && y < paddleY + PADDLE_SIZE) 
			{
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("#\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

int main() 
{
    int ballX = WIDTH / 2, ballY = HEIGHT / 2;
    int ballDirX = 1, ballDirY = 1;
    int paddleY = HEIGHT / 2 - PADDLE_SIZE / 2;
    int score = 0;

    while (1) 
	{
        draw(ballX, ballY, paddleY, score);
        ballX += ballDirX;
        ballY += ballDirY;
        if (ballX <= 0 || ballX >= WIDTH - 1) 
		{
            ballDirX *= -1;
        }
        if (ballY <= 0 || ballY >= HEIGHT - 1) 
		{
            ballDirY *= -1;
        }
        if (ballX == WIDTH - 1 && ballY >= paddleY && ballY < paddleY + PADDLE_SIZE) 
		{
            ballDirX *= -1;
            score++;
        }
        if (kbhit()) 
		{
            char c = getchar();
            if (c == 'q') 
			{
                break;
            } else if (c == 'w' && paddleY > 0) 
			{
                paddleY--;
            } else if (c == 's' && paddleY < HEIGHT - PADDLE_SIZE) 
			{
                paddleY++;
            }
        }

        usleep(100000);
    }

    printf("Game End! Score: %d\n", score);
    return 0;
}
