#include <stdio.h>

struct Player {
    int pos;
    int score;
};

struct Ball {
    int x, y;
    // int target;
    char target_x, target_y;
    /*
    0 - UR
    1 - DR
    2 - DL
    3 - UL
    */
};

struct Player p1 = {11, 0}, p2 = {11, 0};
struct Ball ball = {20, 20, 'R', 'U'};
char cmd;

void ShowField() {
    for (int i = 0; i < 34; i++) {
        printf(" ");
    }
    if (p1.score < 10) {
        printf(" ");
    }
    printf("%d", p1.score);

    for (int i = 0; i < 8; i++) {
        printf(" ");
    }
    if (p2.score < 10) {
        printf(" ");
    }
    printf("%d", p2.score);

    printf("\n");

    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            if (x == 5 && y <= p1.pos && p1.pos <= y + 2) {
                printf("|");
            } else if (x == 75 && y <= p2.pos && p2.pos <= y + 2) {
                printf("|");
            } else if (x == ball.x && y == ball.y) {
                printf("*");
            } else if (x == 39 || x == 40) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void ResetBall(char side) {
    if (side == 'L') {
        ball.x = 6;
        ball.y = p1.pos - 1;
        ball.target_x = 'R';
        ball.target_y = 'U';
    } else {
        ball.x = 74;
        ball.y = p2.pos - 1;
        ball.target_x = 'L';
        ball.target_y = 'D';
    }
}

int main() {
    while (p1.score < 21 && p2.score < 21) {
        ShowField();

        scanf("%c", &cmd);
        if (cmd == 'a') {
            if (p1.pos > 2) {
                p1.pos--;
            }
        } else if (cmd == 'z') {
            if (p1.pos < 24) {
                p1.pos++;
            }
        } else if (cmd == 'k') {
            if (p2.pos > 2) {
                p2.pos--;
            }
        } else if (cmd == 'm') {
            if (p2.pos < 24) {
                p2.pos++;
            }
        }

        if (ball.y == 0 && ball.target_y == 'U') {
            ball.target_y = 'D';
        } else if (ball.y == 24 && ball.target_y == 'D') {
            ball.target_y = 'U';
        }

        if (ball.x == 6 && p1.pos - 2 <= ball.y && ball.y <= p1.pos) {
            ball.target_x = 'R';
        } else if (ball.x == 74 && p2.pos - 2 <= ball.y && ball.y <= p2.pos) {
            ball.target_x = 'L';
        }

        ball.x += ball.target_x == 'R';
        ball.x -= ball.target_x == 'L';
        ball.y += ball.target_y == 'D';
        ball.y -= ball.target_y == 'U';

        if (ball.x == 0) {
            p2.score++;
            ResetBall('L');
        } else if (ball.x == 79) {
            p1.score++;
            ResetBall('R');
        }

        printf("\e[1;1H\e[2J");
    }

    if (p1.score == 21) {
        printf("Player1 win\n");
    } else {
        printf("Player2 win\n");
    }
    return 0;
}
