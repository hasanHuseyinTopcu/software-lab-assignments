#include <stdio.h>
#include <stdlib.h>     /* add stdlib library for dynamic memory */
#include <string.h>     /* add string library for split */
#include <math.h>       /* add math library for fabs function */

struct player{              /* player structure, we hold player's score and bar lower bound information */
    int score;
    int barLowerBound;
};

struct Ball{                /* player structure, we hold ball's position and speed information */
    int positionX;
    int positionY;
    int speedX;
    int speedY;
};

struct oldScoreInformation{     /* this structure for go back command and hold all old score information */
    int A_score;                /* this structure is dynamic because */
    int B_score;                /* we do not know how many will score in game */
    int A_barLowerBound;
    int B_barLowerBound;
    int ballPositionX;
    int ballPositionY;
    int ballSpeedX;
    int ballSpeedY;
    int gameMode;
    struct oldInformation *next;
};

void set(struct oldScoreInformation **, struct player *, struct player *, struct Ball *, int *, char[]);            /* functions prototypes */
void changeMode(int *, char[]);
void changeSpeed(struct Ball *, char[]);
void goBack(struct oldScoreInformation **, struct player *, struct player *, struct Ball *, int *, char[]);
void move(struct oldScoreInformation **, struct player *, struct player *, struct Ball *, int *, char[]);
void addOldScoreInformation(struct oldScoreInformation **, struct player *, struct player *, struct Ball *, int *);

int main(void){

    FILE *inputFile, *outputFile;
    char line[100];     /* line length is not big than 100 so this length is suitable for line array */
    struct player playerA, playerB;     /* define player A and B */
    struct Ball ball;       /* define ball */
    struct oldScoreInformation *head = NULL;    /* head of linked list for old score and set information */
    head = (struct oldScoreInformation *)malloc(sizeof(struct oldScoreInformation));
    int gameMode;

    inputFile = fopen("Input.txt","r");     /* open input and output file */
    outputFile = fopen("Result.txt","w");

    if(inputFile){      /* control to open the input.txt file for read */

        if(outputFile){      /* control to create the Result.txt file for write */

            while( fgets(line,100,inputFile) ){     /* read respectively all line as long as not NULL */

                if(line[0] == 's'){                             /* according to first character, select command and call command function */
                    set(&head, &playerA, &playerB, &ball, &gameMode, line);
                }
                else if(line[0] == 'm'){
                    move(&head, &playerA, &playerB, &ball, &gameMode, line);
                }
                else if(line[0] == 'c'){

                    if(line[6] == 'm'){                         /* changemode and changespeed are same first character */
                        changeMode(&gameMode, line);            /* therefore according to sixth character, select command */
                    }
                    else if(line[6] == 's'){
                        changeSpeed(&ball, line);
                    }

                }
                else if(line[0] == 'g'){
                    goBack(&head, &playerA, &playerB, &ball, &gameMode, line);
                }

            }
            /* write the informations of player and ball in outputFile */
            fprintf(outputFile,"%d,%d,%d,%d,%d,%d",playerA.barLowerBound,playerB.barLowerBound,ball.positionX,ball.positionY,playerA.score,playerB.score);

        }

    }

    fclose(inputFile);          /* close files */
    fclose(outputFile);

    return 0;
}

/* this function assign game starting information */
void set(struct oldScoreInformation **head, struct player *playerA, struct player *playerB, struct Ball *ball, int *gameMode, char line[]){

    char *values, *token;
    int value[7], i=0;      /* value array defined to hold information of the first line(set line) */
    struct oldScoreInformation *temp = *head;

    values = strchr(line, ' ');     /* strchr ile line daki ilk ve tek olan boşluk deðerini values pointerına atıyoruz */
    values++;                       /* values pointerını bir arttırma işlemi ile artık "set "den sonraki gelen ilk */
                                    /* sayıdan itibaren olan yeri tutmuş oluyoruz */

    token = strtok(values, ",");    /* split by ',' character and assign token pointer */
    while(token){                   /* convert integer and assign value array */
        value[i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    playerA->barLowerBound = value[0];          /* according to respectively, assign player, ball and gameMode's information from value array */
    playerA->score = 0;
    playerB->barLowerBound = value[1];
    playerB->score = 0;
    ball->positionX = value[2];
    ball->positionY = value[3];
    ball->speedX = value[4];
    ball->speedY = value[5];
    *gameMode = value[6];

    temp->A_score = playerA->score;                     /* when game is 1-0 or 0-1 (or any other score) , if come goback 1 (or goback 2,3,4..) command */
    temp->B_score = playerB->score;                     /* game return at set moment therefore we hold information of set command */
    temp->A_barLowerBound = playerA->barLowerBound;
    temp->B_barLowerBound = playerB->barLowerBound;
    temp->ballPositionX = ball->positionX;
    temp->ballPositionY = ball->positionY;
    temp->ballSpeedX = ball->speedX;
    temp->ballSpeedY = ball->speedY;
    temp->gameMode = *gameMode;
    temp->next = NULL;

}

/* this function change game mode */
void changeMode(int *gameMode, char line[]){

    char *value;

    value = strtok(line, " ");      /* split line by " " character */
    value = strtok(NULL, " ");
    *gameMode = atoi(value);        /* turn integer and assign gameMode */

}

/* this function change ball's speed */
void changeSpeed(struct Ball *ball, char line[]){

    char *values, *token;
    int value[2], i=0;

    values = strchr(line, ' ');
    values++;

    token = strtok(values, ",");        /* split line and turn integer and assign value array */
    while(token){
        value[i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    ball->speedX = value[0];        /* assign ball'speed */
    ball->speedY = value[1];
}

/* this function assign game information from old score information */
void goBack(struct oldScoreInformation **head, struct player *playerA, struct player *playerB, struct Ball *ball, int *gameMode, char line[]){

    char *token;
    int gobackNumber, i, totalScore = playerA->score + playerB->score;

    token = strtok(line, " ");      /* split and assign goBackNumber */
    token = strtok(NULL, " ");

    gobackNumber = atoi(token);

    struct oldScoreInformation *temp = *head, *current, *prev;      /* define temp for move in linked list */
                                                                    /* define current and prev for free */
    for(i=0; i<totalScore-gobackNumber; i++){        /* toplam golden kaç geri gidileceğini çıkarıyoruz bu ise bize */
        temp = temp->next;                           /* listenin başından itibaren kaç ileri gideceğimiz veriyo */
    }

    playerA->barLowerBound = temp->A_barLowerBound;     /* assign game information from old score information  */
    playerA->score = temp->A_score;
    playerB->barLowerBound = temp->B_barLowerBound;
    playerB->score = temp->B_score;
    ball->positionX = temp->ballPositionX;
    ball->positionY = temp->ballPositionY;
    ball->speedX = temp->ballSpeedX;
    ball->speedY = temp->ballSpeedY;
    *gameMode = temp->gameMode;
    current = temp->next;
    temp->next = NULL;

    while(current != NULL){     /* free for unneeded information */
        prev = current;
        current = current->next;
        free(prev);
    }

}

/* this function for move player and ball */
void move(struct oldScoreInformation **head, struct player *playerA, struct player *playerB, struct Ball *ball, int *gameMode, char line[]){

    char *values, *token;
    int value[2], i=0;
    int numberOfMovedBox = fabs(ball->speedX);      /* numberOfMovedBox = move komutundaki toplam kaç birim sağ ve sol... çarpaz gidiliceği */
                                                    /* yani speed 5 ise 5 birim çaprz gidilcek */
    int scoreOfBeforeMoveCommand = playerA->score + playerB->score;
    struct oldScoreInformation *temp = *head;

    values = strchr(line, ' ');
    values++;

    token = strtok(values, ",");        /* split and assign to value array */
    while(token){
        value[i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    playerA->barLowerBound += value[0];     /* assign players's bar information from value array */
    playerB->barLowerBound += value[1];


    for(i=0; i<numberOfMovedBox; i++){          /* this loop for move each box */

        if(*gameMode == 1){         /* if game is gamed mode 1 */


            if( ball->speedX > 0 && ball->speedY > 0 ){     /* direction is +,+ */

                ball->positionX++;      /* move ball a box direction of +x,+y */
                ball->positionY++;

                if( ball->positionX == 0 || ball->positionX == 79 ){    /* control for hit yellow wall  */
                    ball->speedX *= -1;         /* change ball's x axis direction */
                }
                if( ball->positionY == 0 || ball->positionY == 24 ){    /* control for hit green ball */
                    ball->speedY *= -1;         /* change ball's y axis direction */
                }

                if( ball->positionX == 0 ){      /* score possible for player B */
                    if( ball->positionY < playerA->barLowerBound || ball->positionY > playerA->barLowerBound+4 ){       /* score control for player B */
                        playerB->score++;
                    }
                }
                if( ball->positionX == 79 ){     /* score possible for player A */
                    if( ball->positionY < playerB->barLowerBound || ball->positionY > playerB->barLowerBound+4 ){       /* score control for player A */
                        playerA->score++;
                    }
                }

            }

            else if( ball->speedX > 0 && ball->speedY < 0 ){        /* direction is +,- */

                ball->positionX++;              /* move ball a box direction of +x,-y */
                ball->positionY--;

                if( ball->positionX == 0 || ball->positionX == 79 ){    /* control for hit yellow wall  */
                    ball->speedX *= -1;         /* change ball's x axis direction */
                }
                if( ball->positionY == 0 || ball->positionY == 24 ){    /* control for hit green ball */
                    ball->speedY *= -1;         /* change ball's y axis direction */
                }

                if( ball->positionX == 0 ){      /* score possible for player B */
                    if( ball->positionY < playerA->barLowerBound || ball->positionY > playerA->barLowerBound+4 ){          /* score control for player B */
                        playerB->score++;
                    }
                }
                if( ball->positionX == 79 ){      /* score possible for player A */
                    if( ball->positionY < playerB->barLowerBound || ball->positionY > playerB->barLowerBound+4 ){       /* score control for player A */
                        playerA->score++;
                    }
                }

            }

            else if( ball->speedX < 0 && ball->speedY > 0 ){        /* direction is -,+ */

                ball->positionX--;              /* move ball a box direction of -x,+y */
                ball->positionY++;

                if( ball->positionX == 0 || ball->positionX == 79 ){    /* control for hit yellow wall  */
                    ball->speedX *= -1;         /* change ball's x axis direction */
                }
                if( ball->positionY == 0 || ball->positionY == 24 ){    /* control for hit green ball */
                    ball->speedY *= -1;         /* change ball's y axis direction */
                }

                if( ball->positionX == 0 ){      /* score possible for player B */
                    if( ball->positionY < playerA->barLowerBound || ball->positionY > playerA->barLowerBound+4 ){         /* score control for player B */
                        playerB->score++;
                    }
                }
                if( ball->positionX == 79 ){      /* score possible for player A */
                    if( ball->positionY < playerB->barLowerBound || ball->positionY > playerB->barLowerBound+4 ){       /* score control for player A */
                        playerA->score++;
                    }
                }

            }

            else if( ball->speedX < 0 && ball->speedY < 0 ){        /* direction is -,- */

                ball->positionX--;              /* move ball a box direction of -x,-y */
                ball->positionY--;

                if( ball->positionX == 0 || ball->positionX == 79 ){    /* control for hit yellow wall  */
                    ball->speedX *= -1;         /* change ball's x axis direction */
                }
                if( ball->positionY == 0 || ball->positionY == 24 ){    /* control for hit green ball */
                    ball->speedY *= -1;         /* change ball's y axis direction */
                }

                if( ball->positionX == 0 ){      /* score possible for player B */
                    if( ball->positionY < playerA->barLowerBound || ball->positionY > playerA->barLowerBound+4 ){         /* score control for player B */
                        playerB->score++;
                    }
                }
                if( ball->positionX == 79 ){      /* score possible for player A */
                    if( ball->positionY < playerB->barLowerBound || ball->positionY > playerB->barLowerBound+4 ){       /* score control for player A */
                        playerA->score++;
                    }
                }

            }

        }/* end if */

        else if(*gameMode == 2){         /* if game is gamed mode 2 */

            if( ball->speedX > 0 && ball->speedY > 0 ){        /* direction is +,+ */

                ball->positionX++;                  /* move ball a box direction of +x */

                                                    /* control for ball hit green wall. We control top green wall */
                if( ball->positionY == 24 ){        /* because ball move +y direction so do not hit bottom green wall */
                    ball->positionY = 0;            /* if ball hit green ball new positionY is 0 */
                }else{
                    ball->positionY++;              /* else move ball a box direction of +y */
                }

                if( ball->positionX == 0 || ball->positionX == 79 ){    /* control for hit yellow wall  */
                    ball->speedX *= -1;         /* change ball's x axis direction */
                }
                if( ball->positionY == 0 || ball->positionY == 24 ){    /* control for hit green wall */
                    ball->speedY *= +1;         /* change ball's y axis direction */
                }

                if( ball->positionX == 0 ){      /* score possible for player B */
                    if( ball->positionY < playerA->barLowerBound || ball->positionY > playerA->barLowerBound+4 ){         /* score control for player B */
                        playerB->score++;
                    }
                }
                if( ball->positionX == 79 ){      /* score possible for player A */
                    if( ball->positionY < playerB->barLowerBound || ball->positionY > playerB->barLowerBound+4 ){       /* score control for player A */
                        playerA->score++;
                    }
                }

            }

            else if( ball->speedX > 0 && ball->speedY < 0 ){        /* direction is +,- */

                ball->positionX++;                  /* move ball a box direction of +x */

                                                    /* control for ball hit green wall. We control bottom green wall */
                if( ball->positionY == 0 ){        /* because ball move -y direction so do not hit top green wall */
                    ball->positionY = 24;            /* if ball hit green ball new positionY is 24 */
                }else{
                    ball->positionY--;              /* else move ball a box direction of -y */
                }

                if( ball->positionX == 0 || ball->positionX == 79 ){    /* control for hit yellow wall  */
                    ball->speedX *= -1;         /* change ball's x axis direction */
                }
                if( ball->positionY == 0 || ball->positionY == 24 ){    /* control for hit green wall */
                    ball->speedY *= +1;         /* change ball's y axis direction */
                }

                if( ball->positionX == 0 ){      /* score possible for player B */
                    if( ball->positionY < playerA->barLowerBound || ball->positionY > playerA->barLowerBound+4 ){         /* score control for player B */
                        playerB->score++;
                    }
                }
                if( ball->positionX == 79 ){      /* score possible for player A */
                    if( ball->positionY < playerB->barLowerBound || ball->positionY > playerB->barLowerBound+4 ){       /* score control for player A */
                        playerA->score++;
                    }
                }

            }

            else if( ball->speedX < 0 && ball->speedY > 0 ){        /* direction is -,+ */

                ball->positionX--;                  /* move ball a box direction of -x */

                                                    /* control for ball hit green wall. We control top green wall */
                if( ball->positionY == 24 ){        /* because ball move +y direction so do not hit bottom green wall */
                    ball->positionY = 0;            /* if ball hit green ball new positionY is 0 */
                }else{
                    ball->positionY++;              /* else move ball a box direction of +y */
                }

                if( ball->positionX == 0 || ball->positionX == 79 ){    /* control for hit yellow wall  */
                    ball->speedX *= -1;         /* change ball's x axis direction */
                }
                if( ball->positionY == 0 || ball->positionY == 24 ){    /* control for hit green wall */
                    ball->speedY *= +1;         /* change ball's y axis direction */
                }

                if( ball->positionX == 0 ){      /* score possible for player B */
                    if( ball->positionY < playerA->barLowerBound || ball->positionY > playerA->barLowerBound+4 ){         /* score control for player B */
                        playerB->score++;
                    }
                }
                if( ball->positionX == 79 ){      /* score possible for player A */
                    if( ball->positionY < playerB->barLowerBound || ball->positionY > playerB->barLowerBound+4 ){       /* score control for player A */
                        playerA->score++;
                    }
                }

            }

            else if( ball->speedX < 0 && ball->speedY < 0 ){        /* direction is -,- */

                ball->positionX--;                  /* move ball a box direction of -x */

                                                    /* control for ball hit green wall. We control bottom green wall */
                if( ball->positionY == 0 ){        /* because ball move +y direction so do not hit top green wall */
                    ball->positionY = 24;            /* if ball hit green ball new positionY is 24 */
                }else{
                    ball->positionY--;              /* else move ball a box direction of -y */
                }

                if( ball->positionX == 0 || ball->positionX == 79 ){    /* control for hit yellow wall  */
                    ball->speedX *= -1;         /* change ball's x axis direction */
                }
                if( ball->positionY == 0 || ball->positionY == 24 ){    /* control for hit green wall */
                    ball->speedY *= +1;         /* change ball's y axis direction */
                }

                if( ball->positionX == 0 ){      /* score possible for player A */
                    if( ball->positionY < playerA->barLowerBound || ball->positionY > playerA->barLowerBound+4 ){         /* score control for player B */
                        playerB->score++;
                    }
                }
                if( ball->positionX == 79 ){      /* score possible for player A */
                    if( ball->positionY < playerB->barLowerBound || ball->positionY > playerB->barLowerBound+4 ){       /* score control for player A */
                        playerA->score++;
                    }
                }

            }

        }/* end else if */

    }/* end for loop */

    if(scoreOfBeforeMoveCommand != playerA->score + playerB->score){        /* if any player score at this move step, we must add oldScoreInformation linked list */
                                                                            /* because we use this information for goback command */
        while(temp->next != NULL){      /* move last of list */
            temp = temp->next;
        }
        temp->next = (struct oldScoreInformation *)malloc(sizeof(struct oldScoreInformation));      /* take memory for new node */
        temp = temp->next;

        temp->A_score = playerA->score;         /* assign values */
        temp->B_score = playerB->score;
        temp->A_barLowerBound = playerA->barLowerBound;
        temp->B_barLowerBound = playerB->barLowerBound;
        temp->ballPositionX = ball->positionX;
        temp->ballPositionY = ball->positionY;
        temp->ballSpeedX = ball->speedX;
        temp->ballSpeedY = ball->speedY;
        temp->gameMode = *gameMode;
        temp->next = NULL;

    }/* end if */

}/* end move function */
