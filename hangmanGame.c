#include<stdio.h>
#include<string.h>
#include<time.h>
#define maxLife 5
#define maxStage 7

struct word
{
    char nam[100] ;
    int taken ;
}wordList[100];

char currentWord[100] ;
int life, stage, blankList[] = {3, 4, 3, 3 ,5, 6, 7, 4, 5, 4}, chance = 1 ;
int stageCom[maxStage] ;
int wordListSize = 0 ;
char buff[100] ;

void gameRules()
{
    printf(" _________________________________________________________________________\n") ;
    printf("|::::: Welcome To Hangman :::::\n") ;
    printf("|Rule 1: You have maximum %d chances to guess the correct word\n", life) ;
    printf("|Rule 2: All the characters are in lowercase\n") ;
    printf("|Rule 3: Game has 7 stages. If you can clear all of them you will be ultimate winner\n") ;
    printf("|_________________________________________________________________________\n\n") ;
}
void gameOver()
{
    printf("  |=======|\n") ;
    printf("  O       |\n") ;
    printf("  |       |\n") ;
    printf(" / %c      |\n", '\\') ;
    printf("      _____") ;
}
int play(int numOfblank)
{
    int i, j, correct = 0 ;
    int buffLen = 0 ;
    int ind[100] ;
    int indC = 0 ;
    strcpy(buff, "null") ;

    srand(time(0)) ;
    for(i = 0 ; i < numOfblank ; i++){

        ind[indC] = rand() % strlen(currentWord) ;
        indC++ ;
    }

    for(i = 0 ; i < strlen(currentWord) ; i++){
        int flag = 0 ;
        for(j = 0 ; j < indC ; j++){
            if(i == ind[j]){
                flag = 1 ;
                break ;
            }
        }
        if(flag == 1){
            printf(" _ ") ;
            buff[buffLen] = currentWord[i] ;
            buffLen++ ;
        }
        else printf("%c", currentWord[i]) ;
    }
    printf("\n") ;
    char choice, c ;
    int len = buffLen ;
    buff[buffLen] = '\0' ;

    for( ; ; ){
        if(correct == buffLen){
            return 1 ;
        }
        if(life == 0){
            return 0 ;
        }
        int flag2 = 0 ;

        printf("Guess the character: ") ;
        scanf(" %c", &choice) ;
        //scanf("%c", &c) ;
       // printf("%c\n", choice) ;
        for(i = 0 ; i < strlen(buff) ; i++){
            if(choice == buff[i]){
                flag2 = 1 ;
                break ;
            }
        }


        if(flag2 == 1){
            len-- ;
            printf("!!! Your choice is correct !!!\n") ;
            if(len != 0)
            printf("** You still have to correct %d character **\n", len) ;
            printf("!! You still have %d life left !!\n", life) ;

            correct++ ;
        }
        else
        {
            life-- ;
            printf("!!!! Wrong choice !!!!\n") ;
            if(life != 0)
            printf("!! You still have %d life left !!\n", life) ;

        }
    }
}

void clrwordList(int wordListSize)
{
    int i ;
    for(i = 0 ; i < wordListSize ; i++){
        strcpy(wordList[i].nam, "null");
    }
}
void start()
{
    stage = 1 ;
    int ch, count ;
    char str[100] ;
    for( ; ; )
    {
        count = 0 ;
        int i ;
        for(i = 0 ; i < maxStage ; i++){
            if(stageCom[i] == 1)count++ ;
        }
        if(count == maxStage){
            printf("\n\n***** You have completed all the stages *****\n") ;
            printf("### Game ends Here ###\n\n") ;
            return ;

        }
        printf("\nWant to continue the game? Press 1 otherwise press 2\n ") ;
        scanf("%d", &ch) ;
        if(ch == 1){
            FILE *fptr ;
            if(stage == 1)
                fptr = fopen("stage1.txt", "r") ;
            else{
                fptr = fopen("stageUpper.txt", "r") ;
                clrwordList(wordListSize) ;
                wordListSize = 0 ;
            }
            for(; fscanf(fptr, "%s", &str)!= EOF ; ){
                strcpy(wordList[wordListSize].nam, str) ;
                wordList[wordListSize].taken = 0 ;
                wordListSize++ ;
            }
            fclose(fptr) ;

            srand(time(0)) ;
            int ran = rand() % (wordListSize-1) ;
            if(wordList[ran].taken == 0){
                strcpy(currentWord, wordList[ran].nam) ;
                wordList[ran].taken = 1 ;
            }
            else{
                int i ;
                for(i = 0 ; i < wordListSize ; i++){
                    if(wordList[i].taken == 0){
                        strcpy(currentWord, wordList[i].nam) ;
                        wordList[i].taken = 1 ;
                        break ;
                    }
                }
            }
            srand(time(0)) ;
            if(stage == 1)
                ran = rand() % 5 ;
            else ran = rand() % 9 ;

            int numOfblank = blankList[ran] ;
            int temp = play(numOfblank) ;
            if(temp == 1){
                printf("*** Congratulations You have cleared the stage %d ****\n", stage) ;
                stageCom[stage] = 1 ;
                stage++ ;
                life = 5 ;
            }
            else if(temp == 0 && stage == 1){
                printf("\n\n!!!!!! GAME OVER !!!!!!\n\n") ;
                printf("--- Correct word is ---- %s\n", currentWord) ;
                gameOver() ;
                return ;
            }
            else if(temp == 0 && stage > 1 && chance == 1){
                printf("\n\n!!!!!! GAME OVER !!!!!!\n\n") ;
                printf("--- Correct word is ----%s\n", currentWord) ;
                printf("\n***you can replay this stage onces more time **\n") ;
                life = 5 ;
                chance = 0 ;

            }
            else{
                printf("\n\n!!!!!! GAME OVER !!!!!!\n\n") ;
                printf("--- Correct word is ----%s\n", currentWord) ;
                gameOver() ;
                return ;
            }



        }
        else if(ch == 2) return ;
    }

}
int main()
{
    life = maxLife ;
    gameRules() ;
    start() ;
    return 0 ;
}
