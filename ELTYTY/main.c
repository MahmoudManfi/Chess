#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

void pownBlackMoves(int row1,int column1,int row2,int column2);
void pownWhiteMoves(int row1,int column1,int row2,int column2);
void bishopBlackMove(int row1,int column1,int row2,int column2);
void bishopWhiteMove(int row1,int column1,int row2,int column2);
void undo(int *row1,int *column1,int *row2,int *column2);
void redo(int *row1,int *column1,int *row2,int *column2);
void saveFile();
void loadFile();
void rookWhiteMoves(int row1,int col1,int row2,int col2);
void rookBlackMoves(int row1,int col1,int row2,int col2);
void queenBlackMoves(int row1,int col1,int row2,int col2);
void queenWhiteMoves(int row1,int col1,int row2,int col2);
void whiteKnightMoves(int row1,int col1,int row2,int col2);
void blackKnightMoves(int row1,int col1,int row2,int col2);
void blackKingMoves(int row1,int col1,int row2,int col2);
void whiteKingMoves(int row1,int col1,int row2,int col2);
int checkTheKingBlack(int row1,int col1,int row2,int col2);
int checkTheKingWhite(int row1,int col1,int row2,int col2);
void stalemateblack();
void checkmateblack();
void undoAndRedowblack(int row2,int column2,int row1,int column1);
void stalematewhite();
void checkmatewhite();
void checkTheKingWhite2();
void checkTheKingBlack2();
void undoAndRedowwhite(int row2,int column2,int row1,int column1);

typedef struct{
int row11;
int column11;
int row22;
int column22;
int dead;
int promotion;
char promotionType;
}DO;
DO undoRedo[500];
short numberOfdeadWhiteRow=0;
short numberOfdeadWhiteColumn=0;
short numberOfdeadBlackRow=0;
short numberOfdeadBlackColumn=0;
short numberOfMoves=0;
short checkMateBlack=0;
short checkMateWhite=0;
short numberOfundo1=0;
short numberOfundo2=0;
short stalemate=0;
short x=0,y=0;
short piececolumn=0;
short piecerow=0;
char piece;
char check;
short checkmate=0;


char board[8][8]={{'R','N','B','Q','K','B','N','R'},{'P','P','P','P','P','P','P','P'},
{'+','-','+','-','+','-','+','-'},{'-','+','-','+','-','+','-','+'},
{'+','-','+','-','+','-','+','-'},{'-','+','-','+','-','+','-','+'},
{'p','p','p','p','p','p','p','p'},{'r','n','b','q','k','b','n','r'}};

char deadWhite[8][2]={{'X','X'},{'X','X'},{'X','X'},{'X','X'},{'X','X'},{'X','X'},{'X','X'},{'X','X'}};
char deadBlack[8][2]={{'X','X'},{'X','X'},{'X','X'},{'X','X'},{'X','X'},{'X','X'},{'X','X'},{'X','X'}};
char columnA,columnB;

int main()
{
    for(int i=0;i<500;i++){
        undoRedo[i].promotion=0;    undoRedo[i].promotionType='&';
    }

    while(!checkmate && !stalemate){
    short numberOfRow[8]={1,2,3,4,5,6,7,8};
    char numberOfcolumn[8]={'A','B','C','D','E','F','G','H'};
    printf("\tBlack\t\t  ");
    for(int i=0;i<8;i++)
    printf("  %c   ",numberOfcolumn[i]);
    printf("\t      White");
    printf("\n");
    for(int i=0;i<9;i++){
        printf("      *********          *************************************************          *********\n");
        for(int j=0;j<3;j++){
                if(i==8)
                break;
        if(j==1){
          printf("      | %c | %c |         %d|  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |%d         | %c | %c | \n",
       deadBlack[i][0],deadBlack[i][1],numberOfRow[i],board[i][0],board[i][1],board[i][2],board[i][3],board[i][4],board[i][5],board[i][6],board[i][7],
                 numberOfRow[i],deadWhite[i][0],deadWhite[i][1]);
        }else{
        printf("      |   |   |          |     |     |     |     |     |     |     |     |          |   |   |");
        printf("\n");
         }
        }
    }
    //column1 for the first character entered and row1 for the first number
    printf("\t\t\t  ");
    for(int i=0;i<8;i++)
    printf("  %c   ",numberOfcolumn[i]);
    printf("\n\n");
  //////////////////////////////////////////////////////////
  if(checkMateBlack==0&&checkMateWhite==0&&numberOfMoves%2==0){
    stalematewhite();   if(stalemate==1){break;}   checkTheKingWhite2();
    }
    if(checkMateBlack==0&&checkMateWhite==0&&numberOfMoves%2==1){
    stalemateblack();   if(stalemate==1){break;}    checkTheKingBlack2();
    }
    if(checkMateWhite==1){
        checkmatewhite();   if(checkmate==1){break;}}
    if(checkMateBlack==1){
        checkmateblack();
        if(checkmate==1){break;}
    }
  checkMateBlack=0; checkMateWhite=0;
    int column1=0,column2=0;
    int row1=0,row2=0;
    int error=0;
    printf("please enter the move \t\t");
    printf("(if you want to save press (S) and (L) for load and (U) for undo and (R) for redo)\n");
    do{
            error=0;
    while((columnA=getchar())=='\n');
    if(islower(columnA))
        columnA=toupper(columnA);
    if(columnA=='S'){
       saveFile();
        break;
    }
    if(columnA=='L'){
        loadFile();
        break;
    }
    if(columnA=='U'){
        undo(&row1,&column1,&row2,&column2);
        break;
    }
    if(columnA=='R'){
      redo(&row1,&column1,&row2,&column2);
        break;
    }
    if(columnA!='A' && columnA!='B' &&columnA!='C' &&columnA!='D' &&columnA!='E' &&columnA!='F' &&columnA!='G' &&columnA!='H' ){
         error=1;
    }
    scanf("%1d",&row1);
    while((columnB=getchar())=='\n');
    if(islower(columnB))
        columnB=toupper(columnB);
    if(columnB!='A' && columnB!='B' &&columnB!='C' &&columnB!='D' &&columnB!='E' &&columnB!='F' &&columnB!='G' &&columnB!='H' ){
         error=1;
    }
    scanf("%1d",&row2);
    row1-=1;     row2-=1;
    column1=columnA-65;    column2=columnB-65;
    if(row1<0 && row1>7 && row2<0 && row2>7)
        error=1;
    if(error==1){
    printf("Error,\n please enter the move again\n");
    Sleep(2000);
    }


    }while(error==1 );



if(columnA=='R'){
        if (numberOfMoves%2==0){
                if(board[row1][column1]=='R'){
                        rookBlackMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='N'){
        blackKnightMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='B'){
        bishopBlackMove(row1,column1,row2,column2);

    }else if(board[row1][column1]=='Q'){
        queenBlackMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='K'){
        blackKingMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='P'){
        pownBlackMoves(row1,column1,row2,column2);

}else{
   printf("error in the move\n");
      Sleep(2000);}
}else{
    if(board[row1][column1]=='r'){
            rookWhiteMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='n'){
        whiteKnightMoves(row1,column1,row2,column2);


    }else if(board[row1][column1]=='b'){
        bishopWhiteMove(row1,column1,row2,column2);

    }else if(board[row1][column1]=='q'){
       queenWhiteMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='k'){
        whiteKingMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='p'){
        pownWhiteMoves(row1,column1,row2,column2);

    }else{
     printf("error in the move\n");
      Sleep(2000);
    }
}

    // write here the function of movements
}else{
    if(numberOfMoves%2==1 && columnA!='S' && columnA!='L'){
            if(board[row1][column1]=='R'){
                    rookBlackMoves(row1,column1,row2,column2);
        //function of the rooks for black
    }else if(board[row1][column1]=='N'){
        blackKnightMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='B'){
        bishopBlackMove(row1,column1,row2,column2);
       //function of the bishops for black
    }else if(board[row1][column1]=='Q'){
        queenBlackMoves(row1,column1,row2,column2);
       //function of the queen for black
    }else if(board[row1][column1]=='K'){
        blackKingMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='P'){
        pownBlackMoves(row1,column1,row2,column2);
       //function of the pawns for black
}else{
   printf("error in the move\n");
      Sleep(2000);}
}else{
    if(board[row1][column1]=='r'){
            rookWhiteMoves(row1,column1,row2,column2);
       //function of the rooks for white
    }else if(board[row1][column1]=='n'){
                whiteKnightMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='b'){
        bishopWhiteMove(row1,column1,row2,column2);
       //function of the bishops for white
    }else if(board[row1][column1]=='q'){
       queenWhiteMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='k'){
    whiteKingMoves(row1,column1,row2,column2);

    }else if(board[row1][column1]=='p'){
        pownWhiteMoves(row1,column1,row2,column2);
       //function of the pawns for white
    }else{
        if(columnA!='S'&& columnA!='L')
    printf("error in the move\n");
        Sleep(2000);}
    }}


    system("cls");
    }

    if(stalemate){
        printf("\n the game finished draw because of stalemate\n");

    }else if(checkMateBlack==1){
    printf("\n the first player won ( the player with white pieces) \n");
    }else
    printf("\n the second player won ( the player with black pieces) \n");




    return 0;
}
//////////////////////////////////////////////////////////////////////////////////
// for read and debug the enter
// function of undo
void undo(int *row1,int *column1,int *row2,int *column2){
if(numberOfMoves>numberOfundo2){
    *column1=undoRedo[numberOfMoves-1].column11;
    *column2=undoRedo[numberOfMoves-1].column22;
    *row1=undoRedo[numberOfMoves-1].row11;
    *row2=undoRedo[numberOfMoves-1].row22;
    numberOfMoves--;      numberOfundo1++;
    if(undoRedo[numberOfMoves].promotion==1){
        if(isupper(board[*row1][*column1]))
     board[*row1][*column1]='P';
     else
             board[*row1][*column1]='p';
     }
}else{
printf("you can't make undo now\n");
Sleep(2000);
}

}
void redo(int *row1,int *column1,int *row2,int *column2){
if(numberOfundo1>0){

    *column1=undoRedo[numberOfMoves].column22;
    *column2=undoRedo[numberOfMoves].column11;
    *row1=undoRedo[numberOfMoves].row22;
    *row2=undoRedo[numberOfMoves].row11;
    numberOfMoves++;      numberOfundo1--;
}else{
printf("you can't make redo now\n");
Sleep(2000);
}

}
/////////////////////////////////////////////////////////////////
// function of the pawn
////////////////////////////////////////////////////////////////
void saveFile(){
FILE *chess;
chess=fopen("manfi&Andrew.txt","w");
for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        fputc(board[i][j],chess);
    }
}
for(int i=0;i<8;i++){
    for(int j=0;j<2;j++){
        fputc(deadBlack[i][j],chess);
    }
}
for(int i=0;i<8;i++){
    for(int j=0;j<2;j++){
        fputc(deadWhite[i][j],chess);
    }
}
putw(numberOfdeadBlackColumn,chess);
putw(numberOfdeadBlackRow,chess);
putw(numberOfdeadWhiteColumn,chess);
putw(numberOfdeadWhiteRow,chess);
putw(numberOfMoves,chess);
putw(numberOfMoves,chess);
fclose(chess);
printf("\t Saving.......\n");
}
/////////////////////////////////////////
void loadFile(){
FILE *chess;
chess=fopen("manfi&Andrew.txt","r");
if(chess==NULL){
    printf("you can't open this file \n");
    exit(1);
}else{
   for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        board[i][j]=fgetc(chess);
    }
}
for(int i=0;i<8;i++){
    for(int j=0;j<2;j++){
        deadBlack[i][j]=fgetc(chess);
    }
}
for(int i=0;i<8;i++){
    for(int j=0;j<2;j++){
        deadWhite[i][j]=fgetc(chess);
    }

}
  numberOfdeadBlackColumn=getw(chess);
  numberOfdeadBlackRow=getw(chess);
  numberOfdeadWhiteColumn=getw(chess);
  numberOfdeadWhiteRow=getw(chess);
  numberOfMoves=getw(chess);
  numberOfundo2=getw(chess);

}
fclose(chess);
printf("\t Loading....... \n");
}


















void undoAndRedowblack(int row2,int column2,int row1,int column1){

    board[row2][column2]=board[row1][column1];
       if(undoRedo[numberOfMoves].dead==1){
              if(numberOfdeadWhiteColumn==1){
        numberOfdeadWhiteColumn=0;
        board[row1][column1]=deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn];
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]='X';
     }else{
          numberOfdeadWhiteColumn=1;     numberOfdeadWhiteRow--;
        board[row1][column1]=deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn];
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]='X';
     }}else{  if((column1+row1)%2==0)
    board[row1][column1]='+';
else
    board[row1][column1]='-';
   }}


   void undoAndRedowwhite(int row2,int column2,int row1,int column1){

    board[row2][column2]=board[row1][column1];
       if(undoRedo[numberOfMoves].dead==1){
              if(numberOfdeadBlackColumn==1){
        numberOfdeadBlackColumn=0;
        board[row1][column1]=deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn];
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]='X';
     }else{
          numberOfdeadBlackColumn=1;     numberOfdeadBlackRow--;
        board[row1][column1]=deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn];
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]='X';
     }}else{  if((column1+row1)%2==0)
    board[row1][column1]='+';
else
    board[row1][column1]='-';
   }}





















void pownBlackMoves(int row1,int column1,int row2,int column2){
int color=0;  char promotion;  int deadPiece=0; int dangerous;
// i will use number color for make sure that the piece is moved
dangerous=checkTheKingBlack(row1,column1,row2,column2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
    printf("NOT VALID");  Sleep(2000);
}else{
if((column1-column2)==0 && (row2-row1)==1 &&columnA!='U'){
        if(isalpha(board[row2][column2])){
        printf("this move not valid\n");
        Sleep(2000);
        //to make sure from move first here we should add function system
        }else{
            if(row2==7 && columnA!='R'){
                    while((promotion=getchar())=='\n');
              switch(promotion){
    case 'Q': board[row2][column2]='Q';   color=1; undoRedo[numberOfMoves].promotion=1; undoRedo[numberOfMoves].promotionType='Q';  break;
    case 'R': board[row2][column2]='R';   color=1;   undoRedo[numberOfMoves].promotion=1;  undoRedo[numberOfMoves].promotionType='R';  break;
    case 'N': board[row2][column2]='N';   color=1;   undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='N'; break;
    case 'B': board[row2][column2]='B';    color=1;  undoRedo[numberOfMoves].promotion=1;     undoRedo[numberOfMoves].promotionType='B'; break;
    default : printf("Error in promotion\n");
    printf("please enter the type of piece you want again\n");
    Sleep(2000);
    }
 if(promotion=='B'){
         int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='k'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='k'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateWhite=1;    piece='B';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='k'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='k'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;      piece='B';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='k'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;     piece='B';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='k'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='k'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateWhite=1;     piece='B';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }}else if(promotion=='R'){
        for(int i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][column2])&&board[row2-i][column2]!='k'){
        break;
       }
       if(board[row2-i][column2]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateWhite=1;     piece='R';
          x=row2-i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int i=row2+1;i<8;i++){
        if(isalpha(board[i][column2])&&board[i][column2]!='k'){
            break;
        }
        if(board[i][column2]=='k'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;     piece='R';
             x=i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int j=column2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='k'){
            break;
        }
        if(board[row2][j]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateWhite=1;    piece='R';
           x=row2;  y=j;   piecerow=row2;  piececolumn=column2;
                break;}
       }

        for(int j=1;j<=column2;j++){
        if(isalpha(board[row2][column2-j])&&board[row2][column2-j]!='k'){
            break;
        }
        if(board[row2][column2-j]=='k'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;    piece='R';
             x=row2;  y=column2-j;   piecerow=row2;  piececolumn=column2;
                break;}
        }


    }else if(promotion=='Q'){
     for(int i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][column2])&&board[row2-i][column2]!='k'){
        break;
       }
       if(board[row2-i][column2]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateWhite=1;   piece='Q';
          x=row2-i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int i=row2+1;i<8;i++){
        if(isalpha(board[i][column2])&&board[i][column2]!='k'){
            break;
        }
        if(board[i][column2]=='k'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;      piece='Q';
             x=i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int j=column2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='k'){
            break;
        }
        if(board[row2][j]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateWhite=1;     piece='Q';
           x=row2;  y=j;   piecerow=row2;  piececolumn=column2;
                break;}
       }

        for(int j=1;j<=column2;j++){
        if(isalpha(board[row2][column2-j])&&board[row2][column2-j]!='k'){
            break;
        }
        if(board[row2][column2-j]=='k'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;      piece='Q';
             x=row2;  y=column2-j;   piecerow=row2;  piececolumn=column2;
                break;}
        }
         int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='k'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='k'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateWhite=1;      piece='Q';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='k'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='k'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;    piece='Q';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='k'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;     piece='Q';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='k'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='k'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateWhite=1;    piece='Q';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}

}    }else{
    int n=0;
   for(int i=-2;i<3;i++){
        for(int j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&i!=0&&j!=0&&(row2+i)>=0&&(row2+i)<8&&(column2+j)>=0&&(column2+j)<8){
    if(board[row2+i][column2+j]=='k'){
       checkMateWhite=1;    piece='N';
         if(board[row2+i][column2+j]=='k'&&row2+i<8&&column2+j<8){
        x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
      }else if(board[row2+i][column2-j]=='k'&&row2+i<8&&column2-j>=0){
       x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
      }else if(board[row2-i][column2+j]=='k'&&row2-i>=0&&column2+j<8){
       x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
      }else{
       x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
      }
             printf("black king in dangerous\n");   Sleep(2000);
       n=1; break;
    }

        }}
      if(n==1){break;}

   }

    }

            }else{
        board[row2][column2]=board[row1][column1];
        color=1;
        }}
}else if(abs(column1-column2)==1 && (row2-row1)==1 &&columnA!='U'){
       if(islower(board[row2][column2])){
            if(numberOfdeadWhiteColumn==0){
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][column2];
        numberOfdeadWhiteColumn=1;
     }else{
       deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][column2];
        numberOfdeadWhiteColumn=0;     numberOfdeadWhiteRow++;
     }
       if(row2==7 &&columnA!='R'){
                while((promotion=getchar())=='\n');
                 switch(promotion){
    case 'Q': board[row2][column2]='Q';  deadPiece=1; color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='Q'; break;
    case 'R': board[row2][column2]='R';  deadPiece=1; color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='R'; break;
    case 'N': board[row2][column2]='N';  deadPiece=1; color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='N'; break;
    case 'B': board[row2][column2]='B';  deadPiece=1; color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='B'; break;
    default : printf("Error in promotion\n");
    printf("please enter the type of piece you want again\n");
    Sleep(2000);
    }
    if(promotion=='B'){
         int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='k'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='k'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateWhite=1;     piece='B';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='k'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='k'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;    piece='B';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='k'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;    piece='B';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='k'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='k'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateWhite=1;    piece='B';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }}else if(promotion=='R'){
        for(int i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][column2])&&board[row2-i][column2]!='k'){
        break;
       }
       if(board[row2-i][column2]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateWhite=1;    piece='R';
          x=row2-i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int i=row2+1;i<8;i++){
        if(isalpha(board[i][column2])&&board[i][column2]!='k'){
            break;
        }
        if(board[i][column2]=='k'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;    piece='R';
             x=i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int j=column2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='k'){
            break;
        }
        if(board[row2][j]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateWhite=1;     piece='R';
           x=row2;  y=j;   piecerow=row2;  piececolumn=column2;
                break;}
       }

        for(int j=1;j<=column2;j++){
        if(isalpha(board[row2][column2-j])&&board[row2][column2-j]!='k'){
            break;
        }
        if(board[row2][column2-j]=='k'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;    piece='R';
             x=row2;  y=column2-j;   piecerow=row2;  piececolumn=column2;
                break;}
        }


    }else if(promotion=='Q'){
     for(int i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][column2])&&board[row2-i][column2]!='k'){
        break;
       }
       if(board[row2-i][column2]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateWhite=1;   piece='Q';
          x=row2-i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int i=row2+1;i<8;i++){
        if(isalpha(board[i][column2])&&board[i][column2]!='k'){
            break;
        }
        if(board[i][column2]=='k'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;     piece='Q';
             x=i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int j=column2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='k'){
            break;
        }
        if(board[row2][j]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateWhite=1;      piece='Q';
           x=row2;  y=j;   piecerow=row2;  piececolumn=column2;
                break;}
       }

        for(int j=1;j<=column2;j++){
        if(isalpha(board[row2][column2-j])&&board[row2][column2-j]!='k'){
            break;
        }
        if(board[row2][column2-j]=='k'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;     piece='Q';
             x=row2;  y=column2-j;   piecerow=row2;  piececolumn=column2;
                break;}
        }
         int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='k'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='k'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateWhite=1;    piece='Q';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='k'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='k'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;       piece='Q';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='k'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='k'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;    piece='Q';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='k'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='k'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateWhite=1;   piece='Q';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}

}    }else{
    int n=0;
   for(int i=-2;i<3;i++){
        for(int j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&i!=0&&j!=0&&(row2+i)>=0&&(row2+i)<8&&(column2+j)>=0&&(column2+j)<8){
    if(board[row2+i][column2+j]=='k'){
       checkMateWhite=1;    piece='N';
         if(board[row2+i][column2+j]=='k'&&row2+i<8&&column2+j<8){
        x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
      }else if(board[row2+i][column2-j]=='k'&&row2+i<8&&column2-j>=0){
       x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
      }else if(board[row2-i][column2+j]=='k'&&row2-i>=0&&column2+j<8){
       x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
      }else{
       x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
      }
             printf("black king in dangerous\n");   Sleep(2000);
       n=1; break;
    }

        }}
      if(n==1){break;}

   }

    }

       }else{
       board[row2][column2]=board[row1][column1];   deadPiece=1;
       color=1;
       }}else{
       printf("this move not valid\n");
       Sleep(2000);
       //to make sure from move first here we should add function system
       }
}else if((column1-column2)==0 && (row2-row1)==2 && row1==1 &&columnA!='U'){
    if(isalpha(board[row2-1][column1])){
        printf("this move not valid\n");
        Sleep(2000);
        //
        }else{
        if(isalpha(board[row2][column2])){
        printf("this move not valid\n");
        Sleep(2000);
        //to make sure from move first here we should add function system
        }else{
        board[row2][column2]=board[row1][column1];
        color=1;
        }}
}else if(columnA=='U'){
undoAndRedowblack(row2,column2,row1,column1);
}

else{
       printf("this move not valid\n");
       Sleep(2000);
       }
if(columnA=='R' && isalpha(undoRedo[numberOfMoves-1].promotionType)){
    board[row2][column2]=undoRedo[numberOfMoves-1].promotionType;
}

if(color==1 && columnA!='R'){
    undoRedo[numberOfMoves].column11=column2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=column1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadPiece;
    numberOfMoves++;
}
if(color==1){
if((column1+row1)%2==0)
    board[row1][column1]='+';
else
    board[row1][column1]='-';
}
if(color==1 && (column2-1)>=0 && (column2+1)<=7 && (row2+1)<=7){
    if((board[row2+1][column2+1]=='k'&&(column2+1)<8 ) || (board[row2+1][column2-1]=='k'&&(column2-1)>=0)){
        printf("your king in problem you should escape him  \n");   Sleep(2000);
        checkMateWhite=1;  if(board[row2+1][column2+1]=='k'){
                x=row2+1;  y=column2+1;   piecerow=row2;  piececolumn=column2;   piece='P';
        }else{

x=row2+1;  y=column2-1;   piecerow=row2;  piececolumn=column2;   piece='P';
        }

    }
}
////////////////////////////////////////////////////////////////////////
}}






















void pownWhiteMoves(int row1,int column1,int row2,int column2){
int color=0;  char promotion;  int deadPiece=0;   int dangerous;
// i will use number color for make sure that the piece is moved
dangerous=checkTheKingWhite(row1,column1,row2,column2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
   printf("NOT VALID");  Sleep(2000);
}else{
if((column1-column2)==0 && (row1-row2)==1 &&columnA!='U'){
        if(isalpha(board[row2][column2])){
        printf("this move not valid\n");
        Sleep(2000);
        //to make sure from move first here we should add function system
        }else{
            if(row2==0 &&columnA!='R'){
                    while((promotion=getchar())=='\n');
              switch(promotion){
    case 'q': board[row2][column2]='q';   color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='q';  break;
    case 'r': board[row2][column2]='r';   color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='r'; break;
    case 'n': board[row2][column2]='n';   color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='n'; break;
    case 'b': board[row2][column2]='b';    color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='b'; break;
    default : printf("Error in promotion\n");
    printf("please enter the type of piece you want again\n");
    Sleep(2000);
    }
    if(promotion=='b'){
         int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='K'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='K'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateBlack=1;   piece='b';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='K'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='K'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;     piece='b';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='K'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;    piece='b';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='K'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='K'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateBlack=1;     piece='b';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }}else if(promotion=='r'){
        for(int i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][column2])&&board[row2-i][column2]!='K'){
        break;
       }
       if(board[row2-i][column2]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;   piece='r';
          x=row2-i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int i=row2+1;i<8;i++){
        if(isalpha(board[i][column2])&&board[i][column2]!='K'){
            break;
        }
        if(board[i][column2]=='K'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;   piece='r';
             x=i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int j=column2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='K'){
            break;
        }
        if(board[row2][j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;    piece='r';
           x=row2;  y=j;   piecerow=row2;  piececolumn=column2;
                break;}
       }

        for(int j=1;j<=column2;j++){
        if(isalpha(board[row2][column2-j])&&board[row2][column2-j]!='K'){
            break;
        }
        if(board[row2][column2-j]=='K'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;    piece='r';
             x=row2;  y=column2-j;   piecerow=row2;  piececolumn=column2;
                break;}
        }


    }else if(promotion=='q'){
     for(int i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][column2])&&board[row2-i][column2]!='K'){
        break;
       }
       if(board[row2-i][column2]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;     piece='q';
          x=row2-i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int i=row2+1;i<8;i++){
        if(isalpha(board[i][column2])&&board[i][column2]!='K'){
            break;
        }
        if(board[i][column2]=='K'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;     piece='q';
             x=i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int j=column2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='K'){
            break;
        }
        if(board[row2][j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;     piece='q';
           x=row2;  y=j;   piecerow=row2;  piececolumn=column2;
                break;}
       }

        for(int j=1;j<=column2;j++){
        if(isalpha(board[row2][column2-j])&&board[row2][column2-j]!='K'){
            break;
        }
        if(board[row2][column2-j]=='K'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;    piece='q';
             x=row2;  y=column2-j;   piecerow=row2;  piececolumn=column2;
                break;}
        }
         int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='K'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='K'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateBlack=1;     piece='q';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='K'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='K'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;     piece='q';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='K'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;    piece='q';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='K'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='K'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateBlack=1;     piece='q';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
    }else{
    int n=0;
   for(int i=-2;i<3;i++){
        for(int j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&i!=0&&j!=0&&(row2+i)>=0&&(row2+i)<8&&(column2+j)>=0&&(column2+j)<8){
    if(board[row2+i][column2+j]=='K'){
       checkMateBlack=1;   piece='n';
         if(board[row2+i][column2+j]=='K'&&row2+i<8&&column2+j<8){
        x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
      }else if(board[row2+i][column2-j]=='K'&&row2+i<8&&column2-j>=0){
       x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
      }else if(board[row2-i][column2+j]=='K'&&row2-i>=0&&column2+j<8){
       x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
      }else{
       x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
      }
             printf("black king in dangerous\n");   Sleep(2000);
       n=1; break;
    }

        }}
      if(n==1){break;}

   }
    }


            }else{
        board[row2][column2]=board[row1][column1];
        color=1;
        }}
}else if(abs(column1-column2)==1 && (row1-row2)==1 &&columnA!='U'){
       if(isupper(board[row2][column2])){
            if(numberOfdeadBlackColumn==0){
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][column2];
        numberOfdeadBlackColumn=1;
     }else{
       deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][column2];
        numberOfdeadBlackColumn=0;     numberOfdeadBlackRow++;
     }
       if(row2==0 && columnA!='R'){
                               while((promotion=getchar())=='\n');
                               printf("%c",promotion);
                 switch(promotion){
    case 'q': board[row2][column2]='q';  deadPiece=1; color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='q'; break;
    case 'r': board[row2][column2]='r';  deadPiece=1; color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='r'; break;
    case 'n': board[row2][column2]='n';  deadPiece=1; color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='n'; break;
    case 'b': board[row2][column2]='b';  deadPiece=1; color=1;  undoRedo[numberOfMoves].promotion=1;   undoRedo[numberOfMoves].promotionType='b'; break;
    default : printf("Error in promotion\n");
    printf("please enter the type of piece you want again\n");
    Sleep(2000);
    }
    if(promotion=='b'){
         int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='K'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='K'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateBlack=1;     piece='b';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='K'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='K'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;      piece='b';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='K'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;      piece='b';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='K'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='K'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateBlack=1;    piece='b';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }}else if(promotion=='r'){
        for(int i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][column2])&&board[row2-i][column2]!='K'){
        break;
       }
       if(board[row2-i][column2]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;     piece='r';
          x=row2-i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int i=row2+1;i<8;i++){
        if(isalpha(board[i][column2])&&board[i][column2]!='K'){
            break;
        }
        if(board[i][column2]=='K'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;     piece='r';
             x=i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int j=column2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='K'){
            break;
        }
        if(board[row2][j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;    piece='r';
           x=row2;  y=j;   piecerow=row2;  piececolumn=column2;
                break;}
       }

        for(int j=1;j<=column2;j++){
        if(isalpha(board[row2][column2-j])&&board[row2][column2-j]!='K'){
            break;
        }
        if(board[row2][column2-j]=='K'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;      piece='r';
             x=row2;  y=column2-j;   piecerow=row2;  piececolumn=column2;
                break;}
        }


    }else if(promotion=='q'){
     for(int i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][column2])&&board[row2-i][column2]!='K'){
        break;
       }
       if(board[row2-i][column2]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;   piece='q';
          x=row2-i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int i=row2+1;i<8;i++){
        if(isalpha(board[i][column2])&&board[i][column2]!='K'){
            break;
        }
        if(board[i][column2]=='K'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;    piece='q';
             x=i;  y=column2;   piecerow=row2;  piececolumn=column2;
                break;}
       }
       for(int j=column2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='K'){
            break;
        }
        if(board[row2][j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;     piece='q';
           x=row2;  y=j;   piecerow=row2;  piececolumn=column2;
                break;}
       }

        for(int j=1;j<=column2;j++){
        if(isalpha(board[row2][column2-j])&&board[row2][column2-j]!='K'){
            break;
        }
        if(board[row2][column2-j]=='K'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;    piece='q';
             x=row2;  y=column2-j;   piecerow=row2;  piececolumn=column2;
                break;}
        }
         int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='K'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='K'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateBlack=1;     piece='q';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='K'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='K'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;   piece='q';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='K'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;    piece='q';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='K'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='K'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateBlack=1;   piece='q';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}

}    }else{
    int n=0;
   for(int i=-2;i<3;i++){
        for(int j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&i!=0&&j!=0&&(row2+i)>=0&&(row2+i)<8&&(column2+j)>=0&&(column2+j)<8){
    if(board[row2+i][column2+j]=='K'){
       checkMateBlack=1;   piece='n';
         if(board[row2+i][column2+j]=='K'&&row2+i<8&&column2+j<8){
        x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
      }else if(board[row2+i][column2-j]=='K'&&row2+i<8&&column2-j>=0){
       x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
      }else if(board[row2-i][column2+j]=='K'&&row2-i>=0&&column2+j<8){
       x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
      }else{
       x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
      }
             printf("black king in dangerous\n");   Sleep(2000);
       n=1; break;
    }

        }}
      if(n==1){break;}

   }

    }

       }else{
       board[row2][column2]=board[row1][column1];   deadPiece=1;
       color=1;
       }}else{
       printf("this move not valid\n");
       Sleep(2000);
       //to make sure from move first here we should add function system
       }
}else if((column1-column2)==0 && (row1-row2)==2 && row1==6 &&columnA!='U'){
    if(isalpha(board[row1-1][column1])){
        printf("this move not valid\n");
        Sleep(2000);
        //
        }else{
        if(isalpha(board[row2][column2])){
        printf("this move not valid\n");
        Sleep(2000);
        //to make sure from move first here we should add function system
        }else{
        board[row2][column2]=board[row1][column1];
        color=1;
        }}
}else if(columnA=='U'){

    undoAndRedowwhite(row2,column2,row1,column1);
}else{
       printf("this move not valid\n");
       Sleep(2000);
       }
       if(columnA=='R' && isalpha(undoRedo[numberOfMoves-1].promotionType)){
    board[row2][column2]=undoRedo[numberOfMoves-1].promotionType;
}
if(color==1 && columnA!='R'){
    undoRedo[numberOfMoves].column11=column2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=column1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadPiece;
    numberOfMoves++;
}
if(color==1){
if((column1+row1)%2==0)
    board[row1][column1]='+';
else
    board[row1][column1]='-';
}
if(color==1 && (column2-1)>=0 && (column2+1)<=7 && (row2-1)>=0){
    if(board[row2-1][column2+1]=='K'&&column2+1<8 || board[row2-1][column2-1]=='K' &&column2-1>=0){
         printf("black king in dangerous\n");   Sleep(2000);
             checkMateBlack=1;if(board[row2-1][column2+1]=='K'){
                 piece='p';
             x=row2-1;  y=column2+1;   piecerow=row2;  piececolumn=column2;

             }else{
                 piece='p';
             x=row2-1;  y=column2-1;   piecerow=row2;  piececolumn=column2;

             }
    }
}
////////////////////////////////////////////////////////////////////////
}}

















//ßæÏ ÇáÝíá ÇæÚì æÔß
void bishopBlackMove(int row1,int column1,int row2,int column2){
int emptyspace=1;   int counter=0;  int color=0; int deadpiece=0; int dangerous;
if(columnA=='U'){
   undoAndRedowblack(row2,column2,row1,column1);
   }else{
       dangerous=checkTheKingBlack(row1,column1,row2,column2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
  printf("NOT VALID");  Sleep(2000);
}else{
if(abs(row1-row2)==abs(column1-column2)){
           counter = abs(row1-row2);
     for(int i=1;i<counter;i++){
       if(row1>row2 && column1>column2){
           if(isalpha(board[row1-i][column1-i]))
              emptyspace=0;
        }else if(row1>row2 && column1<column2){
            if(isalpha(board[row1-i][column1+i]))
              emptyspace=0;
        }else if(row1<row2 && column1>column2){
            if(isalpha(board[row1+i][column1-i]))
              emptyspace=0;
        }else if(row1<row2 && column1<column2){
            if(isalpha(board[row1+i][column1+i]))
              emptyspace=0;
        }
    }
if(emptyspace==0){
    printf("this move not valid\n");
    Sleep(2000);}
if(emptyspace==1){
    if(isupper(board[row2][column2])){
        printf("this move not valid\n");
        Sleep(2000);
        //
    }else if(islower(board[row2][column2])){
     if(numberOfdeadWhiteColumn==0){
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][column2];
        numberOfdeadWhiteColumn=1;
     }else{
      deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][column2];
        numberOfdeadWhiteColumn=0;     numberOfdeadWhiteRow++;
     }
      board[row2][column2]=board[row1][column1];
      deadpiece=1;
      color=1;
    }else{
    board[row2][column2]=board[row1][column1];
    color=1;
    }


}
}else{
printf("this move not valid");
Sleep(2000);
}
if(color==1 &&columnA!='R'){
    undoRedo[numberOfMoves].column11=column2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=column1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}
if(color==1){
if((column1+row1)%2==0)
    board[row1][column1]='+';
else
    board[row1][column1]='-';
}

if(color==1){
      int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='k'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='k'){
           printf("white king in dangerous\n");   Sleep(2000);
             checkMateWhite=1;    piece='B';
             x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;

               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='k'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='k'){
           printf("white king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;    piece='B';
            x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='k'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='k'){
           printf("white king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;    piece='B';
            x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='k'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='k'){
                 printf("white king in dangerous\n");   Sleep(2000);
                   checkMateWhite=1;   piece='B';
                   x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }

}
   }}
/////////////////////////////////////////////////
}




















void bishopWhiteMove(int row1,int column1,int row2,int column2){
int emptyspace=1;   int counter=0;  int color=0; int deadpiece=0;     int dangerous;
if(columnA=='U'){
undoAndRedowwhite(row2,column2,row1,column1);
}else{
       dangerous=checkTheKingWhite(row1,column1,row2,column2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
  printf("NOT VALID");  Sleep(2000);
}else{
if(abs(row1-row2)==abs(column1-column2)){
           counter = abs(row1-row2);
     for(int i=1;i<counter;i++){
       if(row1>row2 && column1>column2){
           if(isalpha(board[row1-i][column1-i]))
              emptyspace=0;
        }else if(row1>row2 && column1<column2){
            if(isalpha(board[row1-i][column1+i]))
              emptyspace=0;
        }else if(row1<row2 && column1>column2){
            if(isalpha(board[row1+i][column1-i]))
              emptyspace=0;
        }else if(row1<row2 && column1<column2){
            if(isalpha(board[row1+i][column1+1]))
              emptyspace=0;
        }
    }
if(emptyspace==0){
    printf("this move not valid\n");
    Sleep(2000);
    }
if(emptyspace==1){
    if(islower(board[row2][column2])){
        printf("this move not valid\n");
        Sleep(2000);
        //
    }else if(isupper(board[row2][column2])){
     if(numberOfdeadBlackColumn==0){
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][column2];
        numberOfdeadBlackColumn=1;
     }else{
      deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][column2];
        numberOfdeadBlackColumn=0;     numberOfdeadBlackRow++;
     }
      board[row2][column2]=board[row1][column1];
      deadpiece=1;
      color=1;
    }else{
    board[row2][column2]=board[row1][column1];
    color=1;
    }


}
}else{
printf("this move not valid");
Sleep(2000);
}
if(color==1  && columnA!='R'){
    undoRedo[numberOfMoves].column11=column2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=column1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}
if(color==1){
if((column1+row1)%2==0)
    board[row1][column1]='+';
else
    board[row1][column1]='-';

    if(color==1){

      int flag=0,stop=0,n=0,m=0,k=0;

       for(int i=1;i<8;i++){      //check if there is a check
       for(int j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||column2+j>7){flag=1;}
       if(isalpha(board[row2+i][column2+j])&&board[row2+i][column2+j]!='K'){flag=1;}
       if(flag==0){
       if(board[row2+i][column2+j]=='K'){
            printf("black king in dangerous\n");   Sleep(2000);
           checkMateBlack=1;   piece='b';
           x=row2+i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||column2-j<0){k=1;}
       if(isalpha(board[row2-i][column2-j])&&board[row2-i][column2-j]!='K'){k=1;}
       if(k==0){
       if(board[row2-i][column2-j]=='K'){
         printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;   piece='b';
         x=row2-i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||column2+j>7){n=1;}
        if(isalpha(board[row2-i][column2+j])&&board[row2-i][column2+j]!='K'){n=1;}
        if(n==0){
        if(board[row2-i][column2+j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
         checkMateBlack=1;   piece='b';
         x=row2-i;  y=column2+j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||column2-j<0){m=1;}
        if(isalpha(board[row2+i][column2-j])&&board[row2+i][column2-j]!='K'){m=1;}
        if(m==0){
        if(board[row2+i][column2-j]=='K'){
               printf("black king in dangerous\n");   Sleep(2000);
             checkMateBlack=1;   piece='b';
             x=row2+i;  y=column2-j;   piecerow=row2;  piececolumn=column2;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
    }
}}
//
}}
////////////////////////////////////////////////////////////////////////














void rookWhiteMoves(int row1,int col1,int row2,int col2){
    int i,j,n=0,deadpiece=0,color=0;  int dangerous;    //i,j for loops & n is a flag
    if(columnA=='U'){
     undoAndRedowwhite(row2,col2,row1,col1);
     }else{
       dangerous=checkTheKingWhite(row1,col1,row2,col2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
printf("NOT VALID");  Sleep(2000);
}else{
    if(abs(row2-row1)<8&&col1==col2||abs(col2-col1)<8&&row1==row2){                                                                         //for white rook
     if(row2>row1){
     for(i=row1+1;i<row2;i++){
        if(isalpha(board[i][col1])){
           printf("not valid");
           Sleep(2000);
           n=1; break;
         }
     }}
      if(row2<row1){                         // ÇÔØÇ åÚãá ßÏÇ  //replace each else if with if and use n as flag
        for(i=row1-1;i>row2;i--){
        if(isalpha(board[i][col1])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
      if(col2>col1){
        for(i=col1+1;i<col2;i++){
        if(isalpha(board[row1][i])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
      if(col2<col1){
        for(i=col1-1;i>col2;i--){
        if(isalpha(board[row1][i])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
     if(n==0){

      if(islower(board[row2][col2])){         //the next index is white piece
        printf("not valid");
        Sleep(2000);
      }

     if(board[row2][col2]=='+'||board[row2][col2]=='-'){      //the next index is empty
        board[row2][col2]=board[row1][col1];
        color=1;
        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';
     }

     if(isupper(board[row2][col2])){         //the next index is black piece
        if(numberOfdeadBlackColumn==0){
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=1;
     }else{
      deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=0;     numberOfdeadBlackRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;

        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';

     }

      for(i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][col2])&&board[row2-i][col2]!='K'){
        break;
       }
       if(board[row2-i][col2]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;   piece='r';
          x=row2-i;  y=col2;   piecerow=row2;  piececolumn=col2;
                break;}
       }
       for(i=row2+1;i<8;i++){
        if(isalpha(board[i][col2])&&board[i][col2]!='K'){
            break;
        }
        if(board[i][col2]=='K'){
        printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;     piece='r';
             x=i;  y=col2;   piecerow=row2;  piececolumn=col2;
                break;}
       }
       for(j=col2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='K'){
            break;
        }
        if(board[row2][j]=='K'){
          printf("black king in dangerous\n");   Sleep(2000);
          checkMateBlack=1;    piece='r';
           x=row2;  y=j;   piecerow=row2;  piececolumn=col2;
                break;}
       }

        for(j=1;j<=col2;j++){
        if(isalpha(board[row2][col2-j])&&board[row2][col2-j]!='K'){
            break;
        }
        if(board[row2][col2-j]=='K'){
                 printf("black king in dangerous\n");   Sleep(2000);
            checkMateBlack=1;    piece='r';
             x=row2;  y=col2-j;   piecerow=row2;  piececolumn=col2;
                break;}
        }

if(color==1  && columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}

}}
    else printf("not valid");  //the user entered invalid index
    ///////////////////////////////////////////////////////
    }}}














    void rookBlackMoves(int row1,int col1,int row2,int col2){
    int i,j,n=0,deadpiece=0,color=0;   int dangerous;   //i,j for loops & n is a flag
    if(columnA=='U'){
    undoAndRedowblack(row2,col2,row1,col1);
    }else{
       dangerous=checkTheKingBlack(row1,col1,row2,col2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
 printf("NOT VALID");  Sleep(2000);
}else{
    if(abs(row2-row1)<8&&col1==col2||abs(col2-col1)<8&&row1==row2){                                                                         //for white rook
     if(row2>row1){
     for(i=row1+1;i<row2;i++){
        if(isalpha(board[i][col1])){
           printf("not valid");
           Sleep(2000);
           n=1; break;
         }
     }}
      if(row2<row1){                         // ÇÔØÇ åÚãá ßÏÇ  //replace each else if with if and use n as flag
        for(i=row1-1;i>row2;i--){
        if(isalpha(board[i][col1])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
      if(col2>col1){
        for(i=col1+1;i<col2;i++){
        if(isalpha(board[row1][i])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
      if(col2<col1){
        for(i=col1-1;i>col2;i--){
        if(isalpha(board[row1][i])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
     if(n==0){

      if(isupper(board[row2][col2])){         //the next index is white piece
        printf("not valid");
        Sleep(2000);
      }

     if(board[row2][col2]=='+'||board[row2][col2]=='-'){      //the next index is empty
        board[row2][col2]=board[row1][col1];
        color=1;
        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';
     }

     if(islower(board[row2][col2])){         //the next index is black piece
        if(numberOfdeadWhiteColumn==0){
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=1;
     }else{
      deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=0;     numberOfdeadWhiteRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;

        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';

     }

      for(i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][col2])&&board[row2-i][col2]!='k'){
        break;
       }
       if(board[row2-i][col2]=='k'){
           printf("white king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;   piece='R';
          x=row2-i;  y=col2;  piecerow=row2;  piececolumn=col2;
                break;}
       }
       for(i=row2+1;i<8;i++){
        if(isalpha(board[i][col2])&&board[i][col2]!='k'){
            break;
        }
        if(board[i][col2]=='k'){
            printf("white king in dangerous\n");   Sleep(2000);
        checkMateWhite=1;    piece='R';
         x=i;  y=col2;   piecerow=row2;  piececolumn=col2;
                break;}
       }
       for(j=col2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='k'){
            break;
        }
        if(board[row2][j]=='k'){
             printf("white king in dangerous\n");   Sleep(2000);
        checkMateWhite=1;    piece='R';
         x=row2;  y=j;   piecerow=row2;  piececolumn=col2;
                break;}
       }

        for(j=1;j<=col2;j++){
        if(isalpha(board[row2][col2-j])&&board[row2][col2-j]!='k'){
            break;
        }
        if(board[row2][col2-j]=='k'){
           printf("white king in dangerous\n");   Sleep(2000);
             checkMateWhite=1;     piece='R';
              x=row2;  y=col2-j;   piecerow=row2;  piececolumn=col2;
                break;}
        }

if(color==1  && columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}

}}
    else printf("not valid");  //the user entered invalid index
    ///////////////////////////////////////////////////////
    }}}
////////////////////////////////////////////////////////////














void queenBlackMoves(int row1,int col1,int row2,int col2){
    int counter=0,i,j,n=0,deadpiece=0,color=0,emptyspace=1;   int dangerous;
        if(columnA=='U'){
    undoAndRedowblack(row2,col2,row1,col1);
    }else{
       dangerous=checkTheKingBlack(row1,col1,row2,col2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
printf("NOT VALID");  Sleep(2000);
}else{

     if(abs(row2-row1)<8&&col1==col2||abs(col2-col1)<8&&row1==row2){                                                                         //for white rook
     if(row2>row1){
     for(i=row1+1;i<row2;i++){
        if(isalpha(board[i][col1])){
           printf("not valid");
           Sleep(2000);
           n=1; break;
         }
     }}
      if(row2<row1){                         // ÇÔØÇ åÚãá ßÏÇ  //replace each else if with if and use n as flag
        for(i=row1-1;i>row2;i--){
        if(isalpha(board[i][col1])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
      if(col2>col1){
        for(i=col1+1;i<col2;i++){
        if(isalpha(board[row1][i])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
      if(col2<col1){
        for(i=col1-1;i>col2;i--){
        if(isalpha(board[row1][i])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
     if(n==0){

      if(isupper(board[row2][col2])){         //the next index is white piece
        printf("not valid");
        Sleep(2000);
      }

     if(board[row2][col2]=='+'||board[row2][col2]=='-'){      //the next index is empty
        board[row2][col2]=board[row1][col1];
        color=1;
        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';
     }

     if(islower(board[row2][col2])){         //the next index is black piece
        if(numberOfdeadWhiteColumn==0){
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=1;
     }else{
      deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=0;     numberOfdeadWhiteRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;

        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';

     }



if(color==1  && columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}

}}




    else if(abs(row1-row2)==abs(col1-col2)){
           counter = abs(row1-row2);
     for(int i=1;i<counter;i++){
       if(row1>row2 && col1>col2){
           if(isalpha(board[row1-i][col1-i]))
              emptyspace=0;
        }else if(row1>row2 && col1<col2){
            if(isalpha(board[row1-i][col1+i]))
              emptyspace=0;
        }else if(row1<row2 && col1>col2){
            if(isalpha(board[row1+i][col1-i]))
              emptyspace=0;
        }else if(row1<row2 && col1<col2){
            if(isalpha(board[row1+i][col1+i]))
              emptyspace=0;
        }
    }
if(emptyspace==0){
    printf("this move not valid\n");
    Sleep(2000);}
if(emptyspace==1){
    if(isupper(board[row2][col2])){
        printf("this move not valid\n");
        Sleep(2000);
        //
    }else if(islower(board[row2][col2])){
     if(numberOfdeadWhiteColumn==0){
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=1;
     }else{
      deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=0;     numberOfdeadWhiteRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;
    }else{
    board[row2][col2]=board[row1][col1];
    color=1;
    }


}
if(color==1 &&columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}
if(color==1){
if((col1+row1)%2==0)
    board[row1][col1]='+';
else
    board[row1][col1]='-';
}


}
else {printf("not valid");
         Sleep(2000);}  //not rook or bishop
if(color==1){
           int flag=0,stop=0,n=0,m=0,k=0;

       for(i=1;i<8;i++){      //check if there is a check
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||col2+j>7){flag=1;}
       if(isalpha(board[row2+i][col2+j])&&board[row2+i][col2+j]!='k'){flag=1;}
       if(flag==0){
       if(board[row2+i][col2+j]=='k'){
           printf("white king in dangerous\n");   Sleep(2000);
       checkMateWhite=1;  piece='Q';piececolumn=col2;
                                           piecerow=row2;
                                           x=row2+i; y=col2+j; //check function
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||col2-j<0){k=1;}
       if(isalpha(board[row2-i][col2-j])&&board[row2-i][col2-j]!='k'){k=1;}
       if(k==0){
      if(board[row2-i][col2-j]=='k'){
        printf("white king in dangerous\n");   Sleep(2000);
       checkMateWhite=1; piece='Q'; piececolumn=col2;
                                           piecerow=row2;
                                           x=row2-i; y=col2-j; //check function
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||col2+j>7){n=1;}
        if(isalpha(board[row2-i][col2+j])&&board[row2-i][col2+j]!='k'){n=1;}
        if(n==0){
        if(board[row2-i][col2+j]=='k'){
           printf("white king in dangerous\n");   Sleep(2000);
        checkMateWhite=1; piece='Q';piececolumn=col2;
                                           piecerow=row2;
                                           x=row2-i; y=col2+j; //check function
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||col2-j<0){m=1;}
        if(isalpha(board[row2+i][col2-j])&&board[row2+i][col2-j]!='k'){m=1;}
        if(m==0){
        if(board[row2+i][col2-j]=='k'){
                  printf("white king in dangerous\n");   Sleep(2000);
             checkMateWhite=1;  piece='Q'; piececolumn=col2;
                                           piecerow=row2;
                                           x=row2+i; y=col2-j; //check function
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }

  for(i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][col2])&&board[row2-i][col2]!='k'){
        break;
       }
       if(board[row2-i][col2]=='k'){
           printf("white king in dangerous\n");   Sleep(2000);
        checkMateWhite=1; piece='Q'; piececolumn=col2;
                                           piecerow=row2;
                                           x=row2-i; y=col2;//check function
                break;}
       }
       for(i=row2+1;i<8;i++){
        if(isalpha(board[i][col2])&&board[i][col2]!='k'){
            break;
        }
        if(board[i][col2]=='k'){
          printf("white king in dangerous\n");   Sleep(2000);
         checkMateWhite=1;  piece='Q'; piececolumn=col2;
                                           piecerow=row2;
                                           x=i; y=col2;//check function
                break;}
       }
       for(j=col2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='k'){
            break;
        }
        if(board[row2][j]=='k'){
        printf("white king in dangerous\n");   Sleep(2000);
       checkMateWhite=1;  piece='Q'; piececolumn=col2;
                                           piecerow=row2;
                                           x=row2; y=j;//check function
                break;}
       }

        for(j=1;j<=col2;j++){
        if(isalpha(board[row2][col2-j])&&board[row2][col2-j]!='k'){
            break;
        }
        if(board[row2][col2-j]=='k'){
                 printf("white king in dangerous\n");   Sleep(2000);
            checkMateWhite=1;  piece='Q';  piececolumn=col2;
                                           piecerow=row2;
                                           x=row2; y=col2-j;   //check function
                break;}
        }
}
}
}}
////////////////////////////////////////////////////////////////////















void queenWhiteMoves(int row1,int col1,int row2,int col2){
    int counter=0,i,j,n=0,deadpiece=0,color=0,emptyspace=1; int dangerous;
        if(columnA=='U'){
  undoAndRedowwhite(row2,col2,row1,col1);
  }else{
       dangerous=checkTheKingWhite(row1,col1,row2,col2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
printf("NOT VALID");  Sleep(2000);
}else{

     if(abs(row2-row1)<8&&col1==col2||abs(col2-col1)<8&&row1==row2){                                                                         //for white rook
     if(row2>row1){
     for(i=row1+1;i<row2;i++){
        if(isalpha(board[i][col1])){
           printf("not valid");
           Sleep(2000);
           n=1; break;
         }
     }}
      if(row2<row1){                         // ÇÔØÇ åÚãá ßÏÇ  //replace each else if with if and use n as flag
        for(i=row1-1;i>row2;i--){
        if(isalpha(board[i][col1])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
      if(col2>col1){
        for(i=col1+1;i<col2;i++){
        if(isalpha(board[row1][i])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
      if(col2<col1){
        for(i=col1-1;i>col2;i--){
        if(isalpha(board[row1][i])){
           printf("not valid");
           Sleep(2000);
           n=1; break;}
         }
     }
     if(n==0){

      if(islower(board[row2][col2])){         //the next index is white piece
        printf("not valid");
        Sleep(2000);
      }

     if(board[row2][col2]=='+'||board[row2][col2]=='-'){      //the next index is empty
        board[row2][col2]=board[row1][col1];
        color=1;
        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';
     }

     if(isupper(board[row2][col2])){         //the next index is black piece
        if(numberOfdeadBlackColumn==0){
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=1;
     }else{
      deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=0;     numberOfdeadBlackRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;

        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';

     }



if(color==1  && columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}

}}




    else if(abs(row1-row2)==abs(col1-col2)){
           counter = abs(row1-row2);
     for(int i=1;i<counter;i++){
       if(row1>row2 && col1>col2){
           if(isalpha(board[row1-i][col1-i]))
              emptyspace=0;
        }else if(row1>row2 && col1<col2){
            if(isalpha(board[row1-i][col1+i]))
              emptyspace=0;
        }else if(row1<row2 && col1>col2){
            if(isalpha(board[row1+i][col1-i]))
              emptyspace=0;
        }else if(row1<row2 && col1<col2){
            if(isalpha(board[row1+i][col1+i]))
              emptyspace=0;
        }
    }
if(emptyspace==0){
    printf("this move not valid\n");
    Sleep(2000);}
if(emptyspace==1){
    if(islower(board[row2][col2])){
        printf("this move not valid\n");
        Sleep(2000);
        //
    }else if(isupper(board[row2][col2])){
     if(numberOfdeadBlackColumn==0){
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=1;
     }else{
      deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=0;     numberOfdeadBlackRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;
    }else{
    board[row2][col2]=board[row1][col1];
    color=1;
    }


}
if(color==1 &&columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}
if(color==1){
if((col1+row1)%2==0)
    board[row1][col1]='+';
else
    board[row1][col1]='-';
}

       }
         else {printf("not valid");
         Sleep(2000);}    //not rook or bishop
}
if(color==1){

      int flag=0,stop=0,n=0,m=0,k=0;

       for(i=1;i<8;i++){      //check if there is a check
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||col2+j>7){flag=1;}
       if(isalpha(board[row2+i][col2+j])&&board[row2+i][col2+j]!='K'){flag=1;}
       if(flag==0){
       if(board[row2+i][col2+j]=='K'){
        checkMateBlack=1;   piece='q';
         x=row2+i;  y=col2+j;   piecerow=row2;  piececolumn=col2;
                printf("black king in dangerous\n");   Sleep(2000);
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||col2-j<0){k=1;}
       if(isalpha(board[row2-i][col2-j])&&board[row2-i][col2-j]!='K'){k=1;}
       if(k==0){
       if(board[row2-i][col2-j]=='K'){
        checkMateBlack=1;    piece='q';
        x=row2-i;  y=col2-j;   piecerow=row2;  piececolumn=col2;
                    printf("black king in dangerous\n");   Sleep(2000);
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||col2+j>7){n=1;}
        if(isalpha(board[row2-i][col2+j])&&board[row2-i][col2+j]!='K'){n=1;}
        if(n==0){
        if(board[row2-i][col2+j]=='K'){
         checkMateBlack=1;     piece='q';
         x=row2-i;  y=col2+j;   piecerow=row2;  piececolumn=col2;
              printf("black king in dangerous\n");   Sleep(2000);
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||col2-j<0){m=1;}
        if(isalpha(board[row2+i][col2-j])&&board[row2+i][col2-j]!='K'){m=1;}
        if(m==0){
        if(board[row2+i][col2-j]=='K'){
             checkMateBlack=1;     piece='q';
             x=row2+i;  y=col2-j;   piecerow=row2;  piececolumn=col2;
                   printf("black king in dangerous\n");   Sleep(2000);
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       for(i=1;i<=row2;i++){         //check if there is a check
       if(isalpha(board[row2-i][col2])&&board[row2-i][col2]!='K'){
        break;
       }
       if(board[row2-i][col2]=='K'){
              printf("black king in dangerous\n");   Sleep(2000);
        checkMateBlack=1;    piece='q';
        x=row2-i;  y=col2;   piecerow=row2;  piececolumn=col2;
                break;}
       }
       for(i=row2+1;i<8;i++){
        if(isalpha(board[i][col2])&&board[i][col2]!='K'){
            break;
        }
        if(board[i][col2]=='K'){
             printf("black king in dangerous\n");   Sleep(2000);
        checkMateBlack=1;     piece='q';
        x=i;  y=col2;   piecerow=row2;  piececolumn=col2;
                break;}
       }
       for(j=col2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='K'){
            break;
        }
        if(board[row2][j]=='K'){
           printf("black king in dangerous\n");   Sleep(2000);
        checkMateBlack=1;     piece='q';
        x=row2;  y=j;   piecerow=row2;  piececolumn=col2;
                break;}
       }

        for(j=1;j<=col2;j++){
        if(isalpha(board[row2][col2-j])&&board[row2][col2-j]!='K'){
            break;
        }
        if(board[row2][col2-j]=='K'){
                   printf("black king in dangerous\n");   Sleep(2000);
           checkMateBlack=1;    piece='q';
           x=row2;  y=col2-j;   piecerow=row2;  piececolumn=col2;
                break;}
        }
}
}}





















 void whiteKnightMoves(int row1,int col1,int row2,int col2){
  int i,j,n=0,deadpiece=0,color=0;   int dangerous;
   if(columnA=='U'){
undoAndRedowwhite(row2,col2,row1,col1);
}else{
       dangerous=checkTheKingWhite(row1,col1,row2,col2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
   printf("NOT VALID");  Sleep(2000);
}else{
  if(abs(row2-row1)==2&&abs(col2-col1)==1||abs(col2-col1)==2&&abs(row2-row1)==1){
    if(islower(board[row2][col2])){
        printf("not valid");
        Sleep(2000);
    }

    if(board[row2][col2]=='+'||board[row2][col2]=='-'){
        board[row2][col2]=board[row1][col1];
        color=1;
        if(row1%2==0&&col1%2==0||row1%2!=0&&col2%2!=0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';
    }

    if(isupper(board[row2][col2])){
        if(numberOfdeadBlackColumn==0){
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=1;
     }else{
      deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=0;     numberOfdeadBlackRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;

        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';

    }
   if(color==1 &&columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}

   n=0;
   for(i=-2;i<3;i++){
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&i!=0&&j!=0&&(row2+i)>=0&&(row2+i)<8&&(col2+j)>=0&&(col2+j)<8){
    if(board[row2+i][col2+j]=='K'){
       checkMateBlack=1;   piece='n';
         if(board[row2+i][col2+j]=='K'&&row2+i<8&&col2+j<8){
        x=row2+i;  y=col2+j;   piecerow=row2;  piececolumn=col2;
      }else if(board[row2+i][col2-j]=='K'&&row2+i<8&&col2-j>=0){
       x=row2+i;  y=col2-j;   piecerow=row2;  piececolumn=col2;
      }else if(board[row2-i][col2+j]=='K'&&row2-i>=0&&col2+j<8){
       x=row2-i;  y=col2+j;   piecerow=row2;  piececolumn=col2;
      }else{
       x=row2-i;  y=col2-j;   piecerow=row2;  piececolumn=col2;
      }
             printf("black king in dangerous\n");   Sleep(2000);
       n=1; break;
    }

        }}
      if(n==1){break;}

   }
}
else{ printf("not valid");
Sleep(2000);
}
 }
}}






















void blackKnightMoves(int row1,int col1,int row2,int col2){
  int i,j,n=0,deadpiece=0,color=0;    int dangerous;
   if(columnA=='U'){
 undoAndRedowblack(row2,col2,row1,col1);
 }else{
       dangerous=checkTheKingBlack(row1,col1,row2,col2);
if(dangerous==1 && (columnA!='R'||columnA!='U')){
    printf("NOT VALID");  Sleep(2000);
}else{
  if(abs(row2-row1)==2&&abs(col2-col1)==1||abs(col2-col1)==2&&abs(row2-row1)==1){
    if(isupper(board[row2][col2])){
        printf("not valid");
        Sleep(2000);
    }

    if(board[row2][col2]=='+'||board[row2][col2]=='-'){
        board[row2][col2]=board[row1][col1];
        color=1;
        if(row1%2==0&&col1%2==0||row1%2!=0&&col2%2!=0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';
    }

    if(islower(board[row2][col2])){
        if(numberOfdeadWhiteColumn==0){
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=1;
     }else{
      deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=0;     numberOfdeadWhiteRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;

        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';

    }
   if(color==1 &&columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}

   n=0;
   for(i=-2;i<3;i++){
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&i!=0&&j!=0&&(row2+i)>=0&&(row2+i)<8&&(col2+j)>=0&&(col2+j)<8){
    if(board[row2+i][col2+j]=='k'){
      checkMateWhite=1;    piece='N';
      if(board[row2+i][col2+j]=='k'&&row2+i<8&&col2+j<8){
        x=row2+i;  y=col2+j;   piecerow=row2;  piececolumn=col2;
      }else if(board[row2+i][col2-j]=='k'&&row2+i<8&&col2-j>=0){
       x=row2+i;  y=col2-j;   piecerow=row2;  piececolumn=col2;
      }else if(board[row2-i][col2+j]=='k'&&row2-i>=0&&col2+j<8){
       x=row2-i;  y=col2+j;   piecerow=row2;  piececolumn=col2;
      }else{
       x=row2-i;  y=col2-j;   piecerow=row2;  piececolumn=col2;
      }
              printf("White king in dangerous\n");   Sleep(2000);
       n=1; break;
    }

        }}
      if(n==1){break;}

   }
}
else{ printf("not valid");
Sleep(2000);
}
 }
}}
///////////////////////////////////////////////////////////////////////////////////////////////////////////





















void blackKingMoves(int row1,int col1,int row2,int col2){
int flag,stop,error=0,i,j,k,n,m,deadpiece=0,color=0;
if(columnA=='U'){
 undoAndRedowblack(row2,col2,row1,col1);
 }else{

if(abs(row2-row1)==1&&abs(col2-col1)==1||abs(row2-row1)==1&&col2==col1||abs(col2-col1)==1&&row2==row1){

    for(i=1;i<=row2;i++){               //check if there will be check by rook or queen
        if(isalpha(board[row2-i][col2])&&board[row2-i][col2]!='r'&&board[row2-i][col2]!='q'){break;}
        if(board[row2-i][col2]=='r'||board[row2-i][col2]=='q'){
            printf("not valid");error=1; Sleep(2000); break;
        }
    }

    if(error==0){
    for(i=row2+1;i<8;i++){
        if(isalpha(board[i][col2])&&board[i][col2]!='r'&&board[i][col2]!='q'){
              break;
        }
        if(board[i][col2]=='r'||board[i][col2]=='q'){
                printf("not valid");error=1; Sleep(2000); break;}
       }}

    if(error==0){
    for(j=col2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='r'&&board[row2][j]!='q'){
              break;
        }
        if(board[row2][j]=='r'||board[row2][j]=='q'){
                printf("not valid");error=1;  Sleep(2000);  break;}
       }}

    if(error==0){
    for(j=1;j<=col2;j++){
        if(isalpha(board[row2][col2-j])&&board[row2][col2-j]!='r'&&board[row2][col2-j]!='q'){
             break;
        }
        if(board[row2][col2-j]=='r'||board[row2][col2-j]=='q'){
                printf("not valid");error=1;  Sleep(2000);  break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||col2+j>7){flag=1;}
       if(isalpha(board[row2+i][col2+j])&&board[row2+i][col2+j]!='b'&&board[row2+i][col2+j]!='q'){flag=1;}
       if(flag==0){
       if(board[row2+i][col2+j]=='b'||board[row2+i][col2+j]=='q'){
         printf("not valid");error=1;     Sleep(2000);
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||col2-j<0){k=1;}
       if(isalpha(board[row2-i][col2-j])&&board[row2-i][col2-j]!='b'&&board[row2-i][col2-j]!='q'){k=1;}
       if(k==0){
       if(board[row2-i][col2-j]=='b'||board[row2-i][col2-j]=='q'){
         printf("not valid");error=1;   Sleep(2000);
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||col2+j>7){n=1;}
        if(isalpha(board[row2-i][col2+j])&&board[row2-i][col2+j]!='b'&&board[row2-i][col2+j]!='q'){n=1;}
        if(n==0){
        if(board[row2-i][col2+j]=='b'||board[row2-i][col2+j]=='q'){
         printf("not valid");error=1;    Sleep(2000);
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||col2-j<0){m=1;}
        if(isalpha(board[row2+i][col2-j])&&board[row2+i][col2-j]!='b'&&board[row2+i][col2-j]!='q'){m=1;}
        if(m==0){
        if(board[row2+i][col2-j]=='b'||board[row2+i][col2-j]=='q'){
                printf("not valid");error=1;   Sleep(2000);
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&i!=0&&j!=0&&(row2+i)>=0&&(row2+i)<8&&(col2+j)>=0&&(col2+j)<8){
    if(board[row2+i][col2+j]=='n'){
        printf("not valid");error=1;   Sleep(2000);
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((row2+1)<8&&(col2-1)>=0&&(col2+1)<8)
   if(board[row2+1][col2-1]=='p'||board[row2+1][col2+1]=='p'){     //check if there will be check by pawn
    printf("not valid");error=1;     Sleep(2000);
   }
    }

    if(error==0){
    flag=0;
    for(i=-1;i<2;i++){                //check if there will be danger by the other king
       for(j=-1;j<2;j++){
        if((row2+i)>=0&&(row2+i)<8&&(col2+j)>=0&&(col2+j)<8)
        if(board[row2+i][col2+j]=='k'){
            printf("not valid");flag=1;error=1;   Sleep(2000); break;
        }
        }
        if(flag==1){break;}
        }}

     if(error==0){

        if(isupper(board[row2][col2])){         //the next index is black piece
        printf("not valid");    Sleep(2000);
      }

       if(board[row2][col2]=='+'||board[row2][col2]=='-'){      //the next index is empty
        board[row2][col2]=board[row1][col1];
        color=1;
        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';
     }


           if(islower(board[row2][col2])){         //the next index is white piece
       if(numberOfdeadWhiteColumn==0){
        deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=1;
     }else{
      deadWhite[numberOfdeadWhiteRow][numberOfdeadWhiteColumn]=board[row2][col2];
        numberOfdeadWhiteColumn=0;     numberOfdeadWhiteRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;
              //the white piece is captured
        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';

     }
        if(color==1 &&columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}


     }


    }

    else{ printf("not valid");    Sleep(2000);}

}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////






















void whiteKingMoves(int row1,int col1,int row2,int col2){
int flag,stop,error=0,i,j,k,n,m,deadpiece=0,color=0;
if(columnA=='U'){
   undoAndRedowwhite(row2,col2,row1,col1);
   }else{

if(abs(row2-row1)==1&&abs(col2-col1)==1||abs(row2-row1)==1&&col2==col1||abs(col2-col1)==1&&row2==row1){

    for(i=1;i<=row2;i++){               //check if there will be check by rook or queen
        if(isalpha(board[row2-i][col2])&&board[row2-i][col2]!='R'&&board[row2-i][col2]!='Q'){break;}
        if(board[row2-i][col2]=='R'||board[row2-i][col2]=='Q'){
            printf("not valid");error=1; Sleep(2000); break;
        }
    }

    if(error==0){
    for(i=row2+1;i<8;i++){
        if(isalpha(board[i][col2])&&board[i][col2]!='R'&&board[i][col2]!='Q'){
              break;
        }
        if(board[i][col2]=='R'||board[i][col2]=='Q'){
                printf("not valid");error=1; Sleep(2000); break;}
       }}

    if(error==0){
    for(j=col2+1;j<8;j++){
        if(isalpha(board[row2][j])&&board[row2][j]!='R'&&board[row2][j]!='Q'){
              break;
        }
        if(board[row2][j]=='R'||board[row2][j]=='Q'){
                printf("not valid");error=1;  Sleep(2000);  break;}
       }}

    if(error==0){
    for(j=1;j<=col2;j++){
        if(isalpha(board[row2][col2-j])&&board[row2][col2-j]!='R'&&board[row2][col2-j]!='Q'){
             break;
        }
        if(board[row2][col2-j]=='R'||board[row2][col2-j]=='Q'){
                printf("not valid");error=1;  Sleep(2000);  break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(row2+i>7||col2+j>7){flag=1;}
       if(isalpha(board[row2+i][col2+j])&&board[row2+i][col2+j]!='B'&&board[row2+i][col2+j]!='Q'){flag=1;}
       if(flag==0){
       if(board[row2+i][col2+j]=='B'||board[row2+i][col2+j]=='Q'){
         printf("not valid");error=1;     Sleep(2000);
               stop=1; break;}
       }}

       if(k==0){
       if(row2-i<0||col2-j<0){k=1;}
       if(isalpha(board[row2-i][col2-j])&&board[row2-i][col2-j]!='B'&&board[row2-i][col2-j]!='Q'){k=1;}
       if(k==0){
       if(board[row2-i][col2-j]=='B'||board[row2-i][col2-j]=='Q'){
         printf("not valid");error=1;   Sleep(2000);
               stop=1; break;}
       }}

        if(n==0){
        if(row2-i<0||col2+j>7){n=1;}
        if(isalpha(board[row2-i][col2+j])&&board[row2-i][col2+j]!='B'&&board[row2-i][col2+j]!='Q'){n=1;}
        if(n==0){
        if(board[row2-i][col2+j]=='B'||board[row2-i][col2+j]=='Q'){
         printf("not valid");error=1;    Sleep(2000);
               stop=1; break;}
        }}

        if(m==0){
        if(row2+i>7||col2-j<0){m=1;}
        if(isalpha(board[row2+i][col2-j])&&board[row2+i][col2-j]!='B'&&board[row2+i][col2-j]!='Q'){m=1;}
        if(m==0){
        if(board[row2+i][col2-j]=='B'||board[row2+i][col2-j]=='Q'){
                printf("not valid");error=1;   Sleep(2000);
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&i!=0&&j!=0&&(row2+i)>=0&&(row2+i)<8&&(col2+j)>=0&&(col2+j)<8){
    if(board[row2+i][col2+j]=='N'){
        printf("not valid");error=1;   Sleep(2000);
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((row2-1)>=0&&(col2-1)>=0&&(col2+1)<8)
   if(board[row2-1][col2-1]=='P'||board[row2-1][col2+1]=='P'){     //check if there will be check by pawn
    printf("not valid");error=1;     Sleep(2000);
   }
    }

    if(error==0){
    flag=0;
    for(i=-1;i<2;i++){                //check if there will be danger by the other king
       for(j=-1;j<2;j++){
        if((row2+i)>=0&&(row2+i)<8&&(col2+j)>=0&&(col2+j)<8)
        if(board[row2+i][col2+j]=='K'){
            printf("not valid");flag=1;error=1;   Sleep(2000); break;
        }
        }
        if(flag==1){break;}
        }}

     if(error==0){

        if(islower(board[row2][col2])){         //the next index is black piece
        printf("not valid");    Sleep(2000);
      }

       if(board[row2][col2]=='+'||board[row2][col2]=='-'){      //the next index is empty
        board[row2][col2]=board[row1][col1];
        color=1;
        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';
     }


           if(isupper(board[row2][col2])){         //the next index is white piece
       if(numberOfdeadBlackColumn==0){
        deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=1;
     }else{
      deadBlack[numberOfdeadBlackRow][numberOfdeadBlackColumn]=board[row2][col2];
        numberOfdeadBlackColumn=0;     numberOfdeadBlackRow++;
     }
      board[row2][col2]=board[row1][col1];
      deadpiece=1;
      color=1;
              //the white piece is captured
        if(row1%2!=0&&col1%2!=0||row1%2==0&&col1%2==0){
            board[row1][col1]='+';
        }
        else board[row1][col1]='-';

     }
        if(color==1 &&columnA!='R'){
    undoRedo[numberOfMoves].column11=col2;
    undoRedo[numberOfMoves].row11=row2;
    undoRedo[numberOfMoves].column22=col1;
    undoRedo[numberOfMoves].row22=row1;
    undoRedo[numberOfMoves].dead=deadpiece;
    numberOfMoves++;
}


     }


    }

    else{ printf("not valid");    Sleep(2000);}

}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////












































int checkTheKingBlack(int row1,int col1,int row2,int col2){
int dangerous=0;  char c;   int x,y;
c=board[row2][col2];
board[row2][col2]=board[row1][col1];
board[row1][col1]='+';
for(x=0;x<8;x++){
    for(y=0;y<8;y++)
       if(board[x][y]=='K'&&x<8&&y<8)
        break;
if(board[x][y]=='K'&&x<8&&y<8)
break;
}
if(board[x+1][y-1]=='p'||board[x+1][y+1]=='p')
      dangerous=1;
if(!dangerous)
    if(board[x+1][y+2]=='n'||board[x+1][y-2]=='n'||board[x+2][y+1]=='n'||board[x+2][y-1]=='n'||board[x-1][y+2]=='n'||board[x-1][y-2]=='n'||board[x-2][y+1]=='n'||board[x-2][y-1]=='n')
    dangerous=1;
if(!dangerous)
    for(int i=1;(i+x)<8;i++)
        if(isalpha(board[x+i][y]))
            if(board[x+i][y]=='q'||board[x+i][y]=='r'){
                dangerous=1;    break;
               }
            else      break;
if(!dangerous)
        for(int i=1;(x-i)>=0;i++)
           if(isalpha(board[x-i][y]))
               if(board[x-i][y]=='q'||board[x-i][y]=='r'){
                dangerous=1;     break;
               }
               else      break;
if(!dangerous)
    for(int i=1;(y+i)<8;i++)
        if(isalpha(board[x][y+i]))
            if(board[x][y+i]=='q'||board[x][y+i]=='r'){
                dangerous=1;    break;
               }
            else      break;
if(!dangerous)
        for(int i=1;(y-i)>=0;i++)
           if(isalpha(board[x][y-i]))
               if(board[x][y-i]=='q'||board[x][y-i]=='r'){
                dangerous=1;     break;
               }
               else      break;
if(!dangerous)
    for(int i=1;((x+i)<8||(y-i)>=0);i++)
        if(isalpha(board[x+i][y-i]))
            if(board[x+i][y-i]=='q'||board[x+i][y-i]=='b'){
                dangerous=1;    break;
               }
            else      break;
if(!dangerous)
        for(int i=1;((y+i)<8||(x-i)>=0);i++)
           if(isalpha(board[x-i][y+i]))
               if(board[x-i][y+i]=='q'||board[x-i][y+i]=='b'){
                dangerous=1;     break;
               }
               else      break;
if(!dangerous)
    for(int i=1;((x+i)<8||(y+i)<8);i++)
        if(isalpha(board[x+i][y+i]))
            if(board[x+i][y+i]=='q'||board[x+i][y+i]=='b'){
                dangerous=1;    break;
               }
            else      break;
if(!dangerous)
        for(int i=1;((y-i)>=0||(x-i)>=0);i++)
           if(isalpha(board[x-i][y-i]))
               if(board[x-i][y-i]=='q'||board[x-i][y-i]=='b'){
                dangerous=1;     break;
               }
               else      break;

board[row1][col1]=board[row2][col2];
board[row2][col2]=c;

return dangerous;
}





















int checkTheKingWhite(int row1,int col1,int row2,int col2){
int dangerous=0;  char c;   int x,y;
c=board[row2][col2];
board[row2][col2]=board[row1][col1];
board[row1][col1]='+';
for(x=0;x<8;x++){
    for(y=0;y<8;y++)
       if(board[x][y]=='k'&&y<8&&x<8)
           break;
if(board[x][y]=='k'&&y<8&&x<8)
break;
}
if(board[x-1][y-1]=='P'||board[x-1][y+1]=='P')
      dangerous=1;
if(!dangerous)
    if(board[x+1][y+2]=='N'||board[x+1][y-2]=='N'||board[x+2][y+1]=='N'||board[x+2][y-1]=='N'||board[x-1][y+2]=='N'||board[x-1][y-2]=='N'||board[x-2][y+1]=='N'||board[x-2][y-1]=='N')
    dangerous=1;
if(!dangerous)
    for(int i=1;(i+x)<8;i++)
        if(isalpha(board[x+i][y]))
            if(board[x+i][y]=='Q'||board[x+i][y]=='R'){
                dangerous=1;    break;
               }
            else      break;
if(!dangerous)
        for(int i=1;(x-i)>=0;i++)
           if(isalpha(board[x-i][y]))
               if(board[x-i][y]=='Q'||board[x-i][y]=='R'){
                dangerous=1;     break;
               }
               else      break;
if(!dangerous)
    for(int i=1;(y+i)<8;i++)
        if(isalpha(board[x][y+i]))
            if(board[x][y+i]=='Q'||board[x][y+i]=='R'){
                dangerous=1;    break;
               }
            else      break;
if(!dangerous)
        for(int i=1;(y-i)>=0;i++)
           if(isalpha(board[x][y-i]))
               if(board[x][y-i]=='Q'||board[x][y-i]=='R'){
                dangerous=1;     break;
               }
               else      break;
if(!dangerous)
    for(int i=1;((x+i)<8||(y-i)>=0);i++)
        if(isalpha(board[x+i][y-i]))
            if(board[x+i][y-i]=='Q'||board[x+i][y-i]=='B'){
                dangerous=1;    break;
               }
            else      break;
if(!dangerous)
        for(int i=1;((y+i)<8||(x-i)>=0);i++)
           if(isalpha(board[x-i][y+i]))
               if(board[x-i][y+i]=='Q'||board[x-i][y+i]=='B'){
                dangerous=1;     break;
               }
               else      break;
if(!dangerous)
    for(int i=1;((x+i)<8||(y+i)<8);i++)
        if(isalpha(board[x+i][y+i]))
            if(board[x+i][y+i]=='Q'||board[x+i][y+i]=='B'){
                dangerous=1;    break;
               }
            else      break;
if(!dangerous)
        for(int i=1;((y-i)>=0||(x-i)>=0);i++)
           if(isalpha(board[x-i][y-i]))
               if(board[x-i][y-i]=='Q'||board[x-i][y-i]=='B'){
                dangerous=1;     break;
               }
               else      break;

board[row1][col1]=board[row2][col2];
board[row2][col2]=c;

return dangerous;
}








void stalemateblack(){
int i=0,j=0,x=0,y=0,flag=0,stop=0,k=0,n=0,m=0,counter=0,r=0,c=0,error=0,row=0,column=0,z,t;

for(z=0;z<8;z++){
    for(t=0;t<8;t++){
        if(isupper(board[z][t])&&board[z][t]!='K'&&board[z][t]!='P'){
            flag=2;row=z;column=t;
    stop=0;
    if(board[row][column]=='Q'){
        for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if((row+i)<8&&(row+i)>=0&&(column+j)>=0&&(column+j)<8){
                    if(!isupper(board[row+i][column+j])){
                        stop=1;
                        if(!checkTheKingBlack(row,column,row+i,column+j)){break;}
                        else stop=0;
                    }
                }
            }
            if(stop==1){break;}
        }
        if(stop==0){flag=0;}
    }
        stop=0;
        if(board[row][column]=='R'){
            for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if((row+i)<8&&(row+i)>=0&&(column+j)>=0&&(column+j)<8&&(i==0||j==0)){
                    if(!isupper(board[row+i][column+j])){
                        stop=1;flag=2;
                        if(!checkTheKingBlack(row,column,row+i,column+j)){break;}
                        else stop=0;
                    }
                }
            }
            if(stop==1){break;}
        }
        if(stop==0){flag=0;}

    }
        stop=0;
        if(board[row][column]=='B'){
        for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if((row+i)<8&&(row+i)>=0&&(column+j)>=0&&(column+j)<8&&i==j){
                    if(!isupper(board[row+i][column+j])){
                        stop=1;flag=2;
                        if(!checkTheKingBlack(row,column,row+i,column+j)){break;}
                        else stop=0;
                    }
                }
            }
            if(stop==1){break;}
        }
        if(stop==0){flag=0;}

  }
    stop=0;
    if(board[row][column]=='N'){
        for(i=-2;i<3;i++){
            for(j=-2;j<3;j++){
                if((row+i)<8&&(row+i)>=0&&(column+j)>=0&&(column+j)<8&&abs(i)!=abs(j)&&i!=0&&j!=0){
                    if(!isupper(board[row+i][column+j])){
                        stop=1;flag=2;
                        if(!checkTheKingBlack(row,column,row+i,column+j)){break;}
                        else stop=0;
                    }
                }
            }
            if(stop==1){break;}
        }
        if(stop==0){flag=0;}

  }


  if(flag==2) {break;}
        }
        if(z>=1&&z<7&&(t-1)>=0&&(t+1)<8){
        if(board[z][t]=='P'&&(!isalpha(board[z+1][t])||islower(board[z+1][t-1])||islower(board[z+1][t+1]))){
           stop=checkTheKingBlack(z,t,z+1,t);
           if(stop==1){
           flag=0;}
           else if(stop==0){
            flag=1;break;}
           }

           }

         if(board[z][t]=='K'){x=z;y=t;}
}
if(flag==1||flag==2){break;}
}



if(flag==0){


  for(r=x-1;r<x+2;r++){       //check each square around the king
    for(c=y-1;c<y+2;c++){
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if(board[r-i][c]=='r'||board[r-i][c]=='q'){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if(board[i][c]=='r'||board[i][c]=='q'){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if(board[r][j]=='r'||board[r][j]=='q'){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if(board[r][c-j]=='r'||board[r][c-j]=='q'){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if(board[r+i][c+j]=='b'||board[r+i][c+j]=='q'){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if(board[r-i][c-j]=='b'||board[r-i][c-j]=='q'){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if(board[r-i][c+j]=='b'||board[r-i][c+j]=='q'){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if(board[r+i][c-j]=='b'||board[r+i][c-j]=='q'){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)>=0&&(r+i)<8&&(c+j)>=0&&(c+j)<8&&i!=0&&j!=0){
    if(board[r+i][c+j]=='n'){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(board[r+1][c-1]=='p'||board[r+1][c+1]=='p'){     //check if there will be check by pawn
    error=1;
   }}
    }

    if(error==0){
    flag=0;
    for(i=-1;i<2;i++){                //check if there will be danger by the other king
       for(j=-1;j<2;j++){
        if((r+i)>=0&&(r+i)<8&&(c+j)>=0&&(c+j)<8){
        if(board[r+i][c+j]=='k'){
            flag=1;error=1;break;
        }}
        }
        if(flag==1){break;}
        }}

    if(error==1){counter++;}

    else if(isupper(board[r][c])&&board[r][c]!='K'){counter++;}
}
    }}

    if(x==0&&y!=0&&y!=7||x==7&&y!=0&&y!=7||y==0&&x!=0&&x!=7||y==7&&x!=0&&x!=7){
        if(counter==5){printf("stalemate!"); stalemate=1; Sleep(2000); }
    }
     if(x==0&&y==0||x==0&&y==7||x==7&&y==0||y==7&&x==7){
        if(counter==3){printf("stalemate!"); stalemate=1; Sleep(2000);  }
    }

    if(counter==8){printf("stalemate!"); stalemate=1; Sleep(2000);  }

}

}
















void stalematewhite(){
int i=0,j=0,x=0,y=0,flag=0,stop=0,k=0,n=0,m=0,counter=0,r=0,c=0,error=0,row=0,column=0,z,t;

for(z=0;z<8;z++){
    for(t=0;t<8;t++){
        if(islower(board[z][t])&&board[z][t]!='k'&&board[z][t]!='p'){
            flag=2;row=z;column=t;
    stop=0;
    if(board[row][column]=='q'){
        for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if((row+i)<8&&(row+i)>=0&&(column+j)>=0&&(column+j)<8){
                    if(!islower(board[row+i][column+j])){
                        stop=1;
                        if(!checkTheKingWhite(row,column,row+i,column+j)){break;}
                        else stop=0;
                    }
                }
            }
            if(stop==1){break;}
        }
        if(stop==0){flag=0;}
    }
        stop=0;
        if(board[row][column]=='r'){
            for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if((row+i)<8&&(row+i)>=0&&(column+j)>=0&&(column+j)<8&&(i==0||j==0)){
                    if(!islower(board[row+i][column+j])){
                        stop=1;flag=2;
                        if(!checkTheKingWhite(row,column,row+i,column+j)){break;}
                        else stop=0;
                    }
                }
            }
            if(stop==1){break;}
        }
        if(stop==0){flag=0;}

    }
        stop=0;
        if(board[row][column]=='b'){
        for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if((row+i)<8&&(row+i)>=0&&(column+j)>=0&&(column+j)<8&&i==j){
                    if(!islower(board[row+i][column+j])){
                        stop=1;flag=2;
                        if(!checkTheKingWhite(row,column,row+i,column+j)){break;}
                        else stop=0;
                    }
                }
            }
            if(stop==1){break;}
        }
        if(stop==0){flag=0;}

  }
    stop=0;
    if(board[row][column]=='n'){
        for(i=-2;i<3;i++){
            for(j=-2;j<3;j++){
                if((row+i)<8&&(row+i)>=0&&(column+j)>=0&&(column+j)<8&&abs(i)!=abs(j)&&i!=0&&j!=0){
                    if(!islower(board[row+i][column+j])){
                        stop=1;flag=2;
                        if(!checkTheKingWhite(row,column,row+i,column+j)){break;}
                        else stop=0;
                    }
                }
            }
            if(stop==1){break;}
        }
        if(stop==0){flag=0;}

  }


  if(flag==2) {break;}
        }
        if(z>=1&&z<7&&(t-1)>=0&&(t+1)<8){
        if(board[z][t]=='p'&&(!isalpha(board[z-1][t])||isupper(board[z-1][t-1])||isupper(board[z-1][t+1]))){
           stop=checkTheKingWhite(z,t,z-1,t);
           if(stop==1){
           flag=0;}
           else if(stop==0){
            flag=1;break;}
           }

           }

         if(board[z][t]=='k'){x=z;y=t;}
}
if(flag==1||flag==2){break;}
}



if(flag==0){


  for(r=x-1;r<x+2;r++){       //check each square around the king
    for(c=y-1;c<y+2;c++){                                                                       ////åäÇ ßÏÉ æÇÎÏ ÞíãÉ
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if(board[r-i][c]=='R'||board[r-i][c]=='Q'){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if(board[i][c]=='R'||board[i][c]=='Q'){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if(board[r][j]=='R'||board[r][j]=='Q'){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if(board[r][c-j]=='R'||board[r][c-j]=='Q'){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if(board[r+i][c+j]=='B'||board[r+i][c+j]=='Q'){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if(board[r-i][c-j]=='B'||board[r-i][c-j]=='Q'){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if(board[r-i][c+j]=='B'||board[r-i][c+j]=='Q'){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if(board[r+i][c-j]=='B'||board[r+i][c-j]=='Q'){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)>=0&&(r+i)<8&&(c+j)>=0&&(c+j)<8&&i!=0&&j!=0){
    if(board[r+i][c+j]=='N'){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((r-1)>=0&&(c-1)>=0&&(c+1)<8){
   if(board[r-1][c-1]=='P'||board[r-1][c+1]=='P'){     //check if there will be check by pawn
    error=1;
   }}
    }

    if(error==0){
    flag=0;
    for(i=-1;i<2;i++){                //check if there will be danger by the other king
       for(j=-1;j<2;j++){
        if((r+i)>=0&&(r+i)<8&&(c+j)>=0&&(c+j)<8){
        if(board[r+i][c+j]=='K'){
            flag=1;error=1;break;
        }}
        }
        if(flag==1){break;}
        }}

    if(error==1){counter++;}

    else if(islower(board[r][c])&&board[r][c]!='k'){counter++;}
}
    }}

    if(x==0&&y!=0&&y!=7||x==7&&y!=0&&y!=7||y==0&&x!=0&&x!=7||y==7&&x!=0&&x!=7){
        if(counter==5){printf("stalemate!"); Sleep(2000);   stalemate=1; }
    }
     if(x==0&&y==0||x==0&&y==7||x==7&&y==0||y==7&&x==7){
        if(counter==3){printf("stalemate!");  Sleep(2000);   stalemate=1; }
    }

    if(counter==8){printf("stalemate!");  Sleep(2000);   stalemate=1;  }

}

}

















void checkmatewhite(){
int i,j,flag=0,stop=0,k=0,n=0,m=0,counter=0,r=0,c=0,error=0;

if(piece=='R'||piece=='Q'){

    if(piecerow>x&&piececolumn==y){
    for(r=x+1;r<=piecerow;r++){       //check each square around the king
    c=y;
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if((board[r][j]=='r'||board[r][j]=='q')&&!checkTheKingWhite(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if((board[r][c-j]=='r'||board[r][c-j]=='q')&&!checkTheKingWhite(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
     if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r+1][c]=='p'&&!checkTheKingWhite(r+1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}

    }

    }



    if(piecerow<x&&piececolumn==y){
        for(r=piecerow;r<x;r++){       //check each square around the king
    c=y;
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if((board[r][j]=='r'||board[r][j]=='q')&&!checkTheKingWhite(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if((board[r][c-j]=='r'||board[r][c-j]=='q')&&!checkTheKingWhite(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r+1][c]=='p'&&!checkTheKingWhite(r+1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}

    }}





    if(piecerow==x&&piececolumn>y){
        r=x;       //check each square around the king
    for(c=y+1;c<=piececolumn;c++){
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if((board[r-i][c]=='r'||board[r-i][c]=='q')&&!checkTheKingWhite(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if((board[i][c]=='r'||board[i][c]=='q')&&!checkTheKingWhite(i,c,r,c)){
                error=1; break;}
       }}




       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r+1][c]=='p'&&!checkTheKingWhite(r+1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}

    }}




    if(piecerow==x&&piececolumn<y){
        r=x;       //check each square around the king
    for(c=piececolumn;c<y;c++){
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if((board[r-i][c]=='r'||board[r-i][c]=='q')&&!checkTheKingWhite(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if((board[i][c]=='r'||board[i][c]=='q')&&!checkTheKingWhite(i,c,r,c)){
                error=1; break;}
       }}




       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r+1][c]=='p'&&!checkTheKingWhite(r+1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}

    }}
    }




    if(piece=='B'||piece=='Q'){

       if(piecerow>x&&piececolumn>y){
        for(r=x+1;r<=piecerow;r++){       //check each square around the king
    for(c=y+1;c<=piececolumn;c++){
error=0;
if((abs(r-x)==abs(c-y))&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if((board[r-i][c]=='r'||board[r-i][c]=='q')&&!checkTheKingWhite(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if((board[i][c]=='r'||board[i][c]=='q')&&!checkTheKingWhite(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if((board[r][j]=='r'||board[r][j]=='q')&&!checkTheKingWhite(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if((board[r][c-j]=='r'||board[r][c-j]=='q')&&!checkTheKingWhite(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r+1][c]=='p'&&!checkTheKingWhite(r+1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}
    }
    if(error==1){break;}
    }

       }



     if(piecerow>x&&piececolumn<y){
        for(r=x+1;r<=piecerow;r++){       //check each square around the king
    for(c=y-1;c>=piececolumn;c--){
error=0;
if((abs(r-x)==abs(c-y))&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if((board[r-i][c]=='r'||board[r-i][c]=='q')&&!checkTheKingWhite(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if((board[i][c]=='r'||board[i][c]=='q')&&!checkTheKingWhite(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if((board[r][j]=='r'||board[r][j]=='q')&&!checkTheKingWhite(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if((board[r][c-j]=='r'||board[r][c-j]=='q')&&!checkTheKingWhite(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r+1][c]=='p'&&!checkTheKingWhite(r+1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}
    }
    if(error==1){break;}
    }

     }



    if(piecerow<x&&piececolumn>y){
        for(r=piecerow;r<x;r++){       //check each square around the king
    for(c=piececolumn;c>=y+1;c--){
error=0;
if((abs(r-x)==abs(c-y))&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if((board[r-i][c]=='r'||board[r-i][c]=='q')&&!checkTheKingWhite(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if((board[i][c]=='r'||board[i][c]=='q')&&!checkTheKingWhite(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if((board[r][j]=='r'||board[r][j]=='q')&&!checkTheKingWhite(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if((board[r][c-j]=='r'||board[r][c-j]=='q')&&!checkTheKingWhite(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r+1][c]=='p'&&!checkTheKingWhite(r+1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}
    }
    if(error==1){break;}
    }

    }



    if(piecerow<x&&piececolumn<y){
        for(r=piecerow;r<x;r++){
    for(c=piececolumn;c<y;c++){
error=0;
if((abs(r-x)==abs(c-y))&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if((board[r-i][c]=='r'||board[r-i][c]=='q')&&!checkTheKingWhite(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if((board[i][c]=='r'||board[i][c]=='q')&&!checkTheKingWhite(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if((board[r][j]=='r'||board[r][j]=='q')&&!checkTheKingWhite(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if((board[r][c-j]=='r'||board[r][c-j]=='q')&&!checkTheKingWhite(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r+1][c]=='p'&&!checkTheKingWhite(r+1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}
    }
    if(error==1){break;}
    }

    }
    }



    if(piece=='N'||piece=='P'){
        r=piecerow;       //check each square around the king
        c=piececolumn;
error=0;
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if((board[r-i][c]=='r'||board[r-i][c]=='q')&&!checkTheKingWhite(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if((board[i][c]=='r'||board[i][c]=='q')&&!checkTheKingWhite(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if((board[r][j]=='r'||board[r][j]=='q')&&!checkTheKingWhite(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if((board[r][c-j]=='r'||board[r][c-j]=='q')&&!checkTheKingWhite(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='b'||board[r+i][c+j]=='q')&&!checkTheKingWhite(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='b'||board[r-i][c-j]=='q')&&!checkTheKingWhite(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='b'||board[r-i][c+j]=='q')&&!checkTheKingWhite(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
         if((board[r+i][c-j]=='b'||board[r+i][c-j]=='q')&&!checkTheKingWhite(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='n'&&!checkTheKingWhite(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((r+1)<8&&(c+1)<8&&(c-1)>=0)
   if((board[r+1][c-1]=='p'&&!checkTheKingWhite(r+1,c-1,r,c))||(board[r+1][c+1]=='p'&&!checkTheKingWhite(r+1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    }




   if(error==0){
    counter=0;
   for(r=x-1;r<x+2;r++){       //check each square around the king
    for(c=y-1;c<y+2;c++){                                                                       ////åäÇ ßÏÉ æÇÎÏ ÞíãÉ
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if(board[r-i][c]=='R'||board[r-i][c]=='Q'){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if(board[i][c]=='R'||board[i][c]=='Q'){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if(board[r][j]=='R'||board[r][j]=='Q'){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if(board[r][c-j]=='R'||board[r][c-j]=='Q'){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if(board[r+i][c+j]=='B'||board[r+i][c+j]=='Q'){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if(board[r-i][c-j]=='B'||board[r-i][c-j]=='Q'){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if(board[r-i][c+j]=='B'||board[r-i][c+j]=='Q'){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if(board[r+i][c-j]=='B'||board[r+i][c-j]=='Q'){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if(board[r+i][c+j]=='N'){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((r-1)>=0&&(c+1)<8&&(c-1)>=0)
   if(board[r-1][c-1]=='P'||board[r-1][c+1]=='P'){     //check if there will be check by pawn
    error=1;
   }
    }

    if(error==0){
    flag=0;
    for(i=-1;i<2;i++){                //check if there will be danger by the other king
       for(j=-1;j<2;j++){
        if((r+i)>=0&&(r+i)<8&&(c+j)>=0&&(c+j)<8){
        if(board[r+i][c+j]=='K'){
            flag=1;error=1;break;
        }}
        }
        if(flag==1){break;}
        }}

    if(error==1){counter++;}

    else if(islower(board[r][c])&&board[r][c]!='k'){counter++;}
}
    }}

    if(x==0&&y!=0&&y!=7||x==7&&y!=0&&y!=7||y==0&&x!=0&&x!=7||y==7&&x!=0&&x!=7){
        if(counter==5){printf("checkmate!"); checkmate=1; Sleep(2000);  }
    }
     if(x==0&&y==0||x==0&&y==7||x==7&&y==0||y==7&&x==7){
        if(counter==3){printf("checkmate!"); checkmate=1; Sleep(2000); }
    }

    if(counter==8){printf("checkmate!");  checkmate=1; Sleep(2000); }

   }


}










void checkmateblack(){

int i,j,flag=0,stop=0,k=0,n=0,m=0,counter=0,r=0,c=0,error=0;

if(piece=='r'||piece=='q'){

    if(piecerow>x&&piececolumn==y){
    for(r=x+1;r<=piecerow;r++){       //check each square around the king
    c=y;
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if((board[r][j]=='R'||board[r][j]=='Q')&&!checkTheKingBlack(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if((board[r][c-j]=='R'||board[r][c-j]=='Q')&&!checkTheKingBlack(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
     if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P'&&!checkTheKingBlack(r-1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r-1][c]=='P'&&!checkTheKingBlack(r-1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}

    }

    }



    if(piecerow<x&&piececolumn==y){
        for(r=piecerow;r<x;r++){       //check each square around the king
    c=y;
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if((board[r][j]=='R'||board[r][j]=='Q')&&!checkTheKingBlack(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if((board[r][c-j]=='R'||board[r][c-j]=='Q')&&!checkTheKingBlack(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P'&&!checkTheKingBlack(r-1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if((board[r-1][c]=='P')&&!checkTheKingBlack(r-1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}

    }}





    if(piecerow==x&&piececolumn>y){
        r=x;       //check each square around the king
    for(c=y+1;c<=piececolumn;c++){
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if((board[r-i][c]=='R'||board[r-i][c]=='Q')&&!checkTheKingBlack(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if((board[i][c]=='R'||board[i][c]=='Q')&&!checkTheKingBlack(i,c,r,c)){
                error=1; break;}
       }}




       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P')&&!checkTheKingBlack(r-1,c+1,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r-1][c]=='P'&&!checkTheKingBlack(r-1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}

    }}




    if(piecerow==x&&piececolumn<y){
        r=x;       //check each square around the king
    for(c=piececolumn;c<y;c++){
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if((board[r-i][c]=='R'||board[r-i][c]=='Q')&&!checkTheKingBlack(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if((board[i][c]=='R'||board[i][c]=='Q')&&!checkTheKingBlack(i,c,r,c)){
                error=1; break;}
       }}




       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P'&&!checkTheKingBlack(r-1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r-1][c]=='P'&&!checkTheKingBlack(r-1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}

    }}
    }




    if(piece=='b'||piece=='q'){

       if(piecerow>x&&piececolumn>y){
        for(r=x+1;r<=piecerow;r++){       //check each square around the king
    for(c=y+1;c<=piececolumn;c++){
error=0;
if((abs(r-x)==abs(c-y))&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if((board[r-i][c]=='R'||board[r-i][c]=='Q')&&!checkTheKingBlack(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if((board[i][c]=='R'||board[i][c]=='Q')&&!checkTheKingBlack(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if((board[r][j]=='R'||board[r][j]=='Q')&&!checkTheKingBlack(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if((board[r][c-j]=='R'||board[r][c-j]=='Q')&&!checkTheKingBlack(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P'&&!checkTheKingBlack(r-1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r-1][c]=='P'&&!checkTheKingBlack(r-1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}
    }
    if(error==1){break;}
    }

       }



     if(piecerow>x&&piececolumn<y){
        for(r=x+1;r<=piecerow;r++){       //check each square around the king
    for(c=y-1;c>=piececolumn;c--){
error=0;
if((abs(r-x)==abs(c-y))&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if((board[r-i][c]=='R'||board[r-i][c]=='Q')&&!checkTheKingBlack(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if((board[i][c]=='R'||board[i][c]=='Q')&&!checkTheKingBlack(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if((board[r][j]=='R'||board[r][j]=='Q')&&!checkTheKingBlack(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if((board[r][c-j]=='R'||board[r][c-j]=='Q')&&!checkTheKingBlack(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P'&&!checkTheKingBlack(r-1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r-1][c]=='P'&&!checkTheKingBlack(r-1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}
    }
    if(error==1){break;}
    }
     }



    if(piecerow<x&&piececolumn>y){
        for(r=piecerow;r<x;r++){       //check each square around the king
    for(c=piececolumn;c>=y+1;c--){
error=0;
if((abs(r-x)==abs(c-y))&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if((board[r-i][c]=='R'||board[r-i][c]=='Q')&&!checkTheKingBlack(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if((board[i][c]=='R'||board[i][c]=='Q')&&!checkTheKingBlack(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if((board[r][j]=='R'||board[r][j]=='Q')&&!checkTheKingBlack(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if((board[r][c-j]=='R'||board[r][c-j]=='Q')&&!checkTheKingBlack(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P'&&!checkTheKingBlack(r-1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r-1][c]=='P'&&!checkTheKingBlack(r-1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}
    }
    if(error==1){break;}
    }
    }



    if(piecerow<x&&piececolumn<y){
        for(r=piecerow;r<x;r++){
    for(c=piececolumn;c<y;c++){
error=0;
if((abs(r-x)==abs(c-y))&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if((board[r-i][c]=='R'||board[r-i][c]=='Q')&&!checkTheKingBlack(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if((board[i][c]=='R'||board[i][c]=='Q')&&!checkTheKingBlack(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if((board[r][j]=='R'||board[r][j]=='Q')&&!checkTheKingBlack(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if((board[r][c-j]=='R'||board[r][c-j]=='Q')&&!checkTheKingBlack(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
        if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
    if((r+1)<8&&(c+1)<8&&(c-1)>=0){
   if(r==piecerow&&c==piececolumn){
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P'&&!checkTheKingBlack(r-1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    if(r!=piecerow||c!=piececolumn){
       if(board[r-1][c]=='P'&&!checkTheKingBlack(r-1,c,r,c)){     //check if there will be check by pawn
    error=1;
   }
    }}
    }
    }
    if(error==1){break;}
    }
    if(error==1){break;}
    }

    }
    }



    if(piece=='n'||piece=='p'){
        r=piecerow;       //check each square around the king
        c=piececolumn;
error=0;
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='R'&&board[r-i][c]!='Q'){break;}
        if((board[r-i][c]=='R'||board[r-i][c]=='Q')&&!checkTheKingBlack(r-i,c,r,c)){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='R'&&board[i][c]!='Q'){
              break;
        }
        if((board[i][c]=='R'||board[i][c]=='Q')&&!checkTheKingBlack(i,c,r,c)){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='R'&&board[r][j]!='Q'){
              break;
        }
        if((board[r][j]=='R'||board[r][j]=='Q')&&!checkTheKingBlack(r,j,r,c)){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='R'&&board[r][c-j]!='Q'){
             break;
        }
        if((board[r][c-j]=='R'||board[r][c-j]=='Q')&&!checkTheKingBlack(r,c-j,r,c)){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='B'&&board[r+i][c+j]!='Q'){flag=1;}
       if(flag==0){
       if((board[r+i][c+j]=='B'||board[r+i][c+j]=='Q')&&!checkTheKingBlack(r+i,c+j,r,c)){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='B'&&board[r-i][c-j]!='Q'){k=1;}
       if(k==0){
       if((board[r-i][c-j]=='B'||board[r-i][c-j]=='Q')&&!checkTheKingBlack(r-i,c-j,r,c)){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='B'&&board[r-i][c+j]!='Q'){n=1;}
        if(n==0){
        if((board[r-i][c+j]=='B'||board[r-i][c+j]=='Q')&&!checkTheKingBlack(r-i,c+j,r,c)){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='B'&&board[r+i][c-j]!='Q'){m=1;}
        if(m==0){
         if((board[r+i][c-j]=='B'||board[r+i][c-j]=='Q')&&!checkTheKingBlack(r+i,c-j,r,c)){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if((board[r+i][c+j]=='N'&&!checkTheKingBlack(r+i,c+j,r,c))){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((r+1)<8&&(c+1)<8&&(c-1)>=0)
   if((board[r-1][c-1]=='P'&&!checkTheKingBlack(r-1,c-1,r,c))||(board[r-1][c+1]=='P'&&!checkTheKingBlack(r-1,c+1,r,c))){     //check if there will be check by pawn
    error=1;
   }
    }
    }




   if(error==0){
    counter=0;
   for(r=x-1;r<x+2;r++){       //check each square around the king
    for(c=y-1;c<y+2;c++){                                                                       ////åäÇ ßÏÉ æÇÎÏ ÞíãÉ
error=0;
if(!(r==x&&c==y)&&r<8&&r>=0&&c<8&&c>=0){
for(i=1;i<=r;i++){               //check if there will be check by rook or queen
        if(isalpha(board[r-i][c])&&board[r-i][c]!='r'&&board[r-i][c]!='q'){break;}
        if(board[r-i][c]=='r'||board[r-i][c]=='q'){
            error=1; break;
        }
    }

    if(error==0){
    for(i=r+1;i<8;i++){
        if(isalpha(board[i][c])&&board[i][c]!='r'&&board[i][c]!='q'){
              break;
        }
        if(board[i][c]=='r'||board[i][c]=='q'){
                error=1; break;}
       }}

    if(error==0){
    for(j=c+1;j<8;j++){
        if(isalpha(board[r][j])&&board[r][j]!='r'&&board[r][j]!='q'){
              break;
        }
        if(board[r][j]=='r'||board[r][j]=='q'){
               error=1; break;}
       }}

    if(error==0){
    for(j=1;j<=c;j++){
        if(isalpha(board[r][c-j])&&board[r][c-j]!='r'&&board[r][c-j]!='q'){
             break;
        }
        if(board[r][c-j]=='r'||board[r][c-j]=='q'){
                error=1; break;}
        }}

       if(error==0){
       stop=0; flag=0; k=0; n=0; m=0;     //check if there will be check by bishop or queen

       for(i=1;i<8;i++){
       for(j=1;j<8;j++){

       if(i==j){

       if(flag==0){
       if(r+i>7||c+j>7){flag=1;}
       if(isalpha(board[r+i][c+j])&&board[r+i][c+j]!='b'&&board[r+i][c+j]!='q'){flag=1;}
       if(flag==0){
       if(board[r+i][c+j]=='b'||board[r+i][c+j]=='q'){
         error=1;
               stop=1; break;}
       }}

       if(k==0){
       if(r-i<0||c-j<0){k=1;}
       if(isalpha(board[r-i][c-j])&&board[r-i][c-j]!='b'&&board[r-i][c-j]!='q'){k=1;}
       if(k==0){
       if(board[r-i][c-j]=='b'||board[r-i][c-j]=='q'){
         error=1;
               stop=1; break;}
       }}

        if(n==0){
        if(r-i<0||c+j>7){n=1;}
        if(isalpha(board[r-i][c+j])&&board[r-i][c+j]!='b'&&board[r-i][c+j]!='q'){n=1;}
        if(n==0){
        if(board[r-i][c+j]=='b'||board[r-i][c+j]=='q'){
         error=1;
               stop=1; break;}
        }}

        if(m==0){
        if(r+i>7||c-j<0){m=1;}
        if(isalpha(board[r+i][c-j])&&board[r+i][c-j]!='b'&&board[r+i][c-j]!='q'){m=1;}
        if(m==0){
        if(board[r+i][c-j]=='b'||board[r+i][c-j]=='q'){
                error=1;
               stop=1; break;}
       }}}
       }
       if(stop==1){break;}
       }
       }

         if(error==0){
        stop=0;
        for(i=-2;i<3;i++){          //check if there will be check by knight
        for(j=-2;j<3;j++){
    if(abs(i)!=abs(j)&&(r+i)<8&&(r+i)>=0&&(c+j)<8&&(c+j)>=0&&i!=0&&j!=0){
    if(board[r+i][c+j]=='n'){
        error=1;
       stop=1; break;
    }

        }}
      if(stop==1){break;}

   }}

    if(error==0){
   if((r+1)<8&&(c+1)<8&&(c-1)>=0)
   if(board[r+1][c-1]=='p'||board[r+1][c+1]=='p'){     //check if there will be check by pawn
    error=1;
   }
    }

    if(error==0){
    flag=0;
    for(i=-1;i<2;i++){                //check if there will be danger by the other king
       for(j=-1;j<2;j++){
        if((r+i)>=0&&(r+i)<8&&(c+j)>=0&&(c+j)<8){
        if(board[r+i][c+j]=='k'){
            flag=1;error=1;break;
        }}
        }
        if(flag==1){break;}
        }}

    if(error==1){counter++;}

    else if(isupper(board[r][c])&&board[r][c]!='K'){counter++;}
}
    }}

    if(x==0&&y!=0&&y!=7||x==7&&y!=0&&y!=7||y==0&&x!=0&&x!=7||y==7&&x!=0&&x!=7){
        if(counter==5){printf("checkmate!"); checkmate=1; Sleep(2000);  }
    }
     if(x==0&&y==0||x==0&&y==7||x==7&&y==0||y==7&&x==7){
        if(counter==3){printf("checkmate!"); checkmate=1; Sleep(2000); }
    }

    if(counter==8){printf("checkmate!");  checkmate=1; Sleep(2000); }

   }


}


void checkTheKingBlack2(){

for(x=0;x<8;x++){
    for(y=0;y<8;y++)
       if(board[x][y]=='K'&&x<8&&y<8)
        break;
if(board[x][y]=='K'&&x<8&&y<8)
break;
}

    for(int i=1;(i+x)<8;i++)
        if(isalpha(board[x+i][y]))
            if(board[x+i][y]=='q'||board[x+i][y]=='r'){
                    printf("check!\n");     checkMateBlack=1;
                if(board[x+i][y]=='q'){
                    piece='q';   piecerow=x+i;   piececolumn=y;   break;
                }else{
                piece='r';   piecerow=x+i;    piececolumn=y;  break;
                }
               }
            else      break;

        for(int i=1;(x-i)>=0;i++)
           if(isalpha(board[x-i][y]))
               if(board[x-i][y]=='q'||board[x-i][y]=='r'){
                     printf("check!\n");     checkMateBlack=1;
                if(board[x-i][y]=='q'){
                    piece='q';   piecerow=x-i;   piececolumn=y;   break;
                }else{
                piece='r';   piecerow=x-i;    piececolumn=y;  break;
                }
               }
               else      break;

    for(int i=1;(y+i)<8;i++)
        if(isalpha(board[x][y+i]))
            if(board[x][y+i]=='q'||board[x][y+i]=='r'){
                    printf("check!\n");     checkMateBlack=1;
                if(board[x][y+i]=='q'){
                    piece='q';   piecerow=x;   piececolumn=y+i;   break;
                }else{
                piece='r';   piecerow=x;    piececolumn=y+i;  break;
                }
               }
            else      break;

        for(int i=1;(y-i)>=0;i++)
           if(isalpha(board[x][y-i]))
               if(board[x][y-i]=='q'||board[x][y-i]=='r'){
                    printf("check!\n");     checkMateBlack=1;
                if(board[x][y-i]=='q'){
                    piece='q';   piecerow=x;   piececolumn=y-i;   break;
                }else{
                piece='r';   piecerow=x;    piececolumn=y-i;  break;
                }
               }
               else      break;

    for(int i=1;((x+i)<8||(y-i)>=0);i++)
        if(isalpha(board[x+i][y-i]))
            if(board[x+i][y-i]=='q'||board[x+i][y-i]=='b'){
                     printf("check!\n");    checkMateBlack=1;
                if(board[x+i][y-i]=='q'){
                    piece='q';   piecerow=x+i;   piececolumn=y-i;   break;
                }else{
                piece='b';   piecerow=x+i;    piececolumn=y-i;  break;
                }
               }
            else      break;

        for(int i=1;((y+i)<8||(x-i)>=0);i++)
           if(isalpha(board[x-i][y+i]))
               if(board[x-i][y+i]=='q'||board[x-i][y+i]=='b'){
                      printf("check!\n");      checkMateBlack=1;
                if(board[x-i][y+i]=='q'){
                    piece='q';   piecerow=x-i;   piececolumn=y+i;   break;
                }else{
                piece='b';   piecerow=x-i;    piececolumn=y+i;  break;
                }
               }
               else      break;

    for(int i=1;((x+i)<8||(y+i)<8);i++)
        if(isalpha(board[x+i][y+i]))
            if(board[x+i][y+i]=='q'||board[x+i][y+i]=='b'){
                      printf("check!\n");     checkMateBlack=1;
                if(board[x+i][y+i]=='q'){
                    piece='q';   piecerow=x+i;   piececolumn=y+i;   break;
                }else{
                piece='b';   piecerow=x+i;    piececolumn=y+i;  break;
                }
               }
            else      break;

        for(int i=1;((y-i)>=0||(x-i)>=0);i++)
           if(isalpha(board[x-i][y-i]))
               if(board[x-i][y-i]=='q'||board[x-i][y-i]=='b'){
                      printf("check!\n");   checkMateBlack=1;
                if(board[x-i][y-i]=='q'){
                    piece='q';   piecerow=x-i;   piececolumn=y-i;   break;
                }else{
                piece='b';   piecerow=x-i;    piececolumn=y-i;  break;
                }
               }
               else      break;



}


















void checkTheKingWhite2(){

for(x=0;x<8;x++){
    for(y=0;y<8;y++)
       if(board[x][y]=='k'&&x<8&&y<8)
        break;
if(board[x][y]=='k'&&x<8&&y<8)
break;
}


    for(int i=1;(i+x)<8;i++)
        if(isalpha(board[x+i][y]))
            if(board[x+i][y]=='Q'||board[x+i][y]=='R'){
                    printf("check!\n");   checkMateWhite=1;
                if(board[x+i][y]=='Q'){
                    piece='Q';   piecerow=x+i;   piececolumn=y;   break;
                }else{
                piece='R';   piecerow=x+i;    piececolumn=y;  break;
                }
               }
            else      break;

        for(int i=1;(x-i)>=0;i++)
           if(isalpha(board[x-i][y]))
               if(board[x-i][y]=='Q'||board[x-i][y]=='R'){
                     printf("check!\n");    checkMateWhite=1;
                if(board[x-i][y]=='Q'){
                    piece='Q';   piecerow=x-i;   piececolumn=y;   break;
                }else{
                piece='R';   piecerow=x-i;    piececolumn=y;  break;
                }
               }
               else      break;

    for(int i=1;(y+i)<8;i++)
        if(isalpha(board[x][y+i]))
            if(board[x][y+i]=='Q'||board[x][y+i]=='R'){
                    printf("check!\n");   checkMateWhite=1;
                if(board[x][y+i]=='Q'){
                    piece='Q';   piecerow=x;   piececolumn=y+i;   break;
                }else{
                piece='R';   piecerow=x;    piececolumn=y+i;  break;
                }
               }
            else      break;

        for(int i=1;(y-i)>=0;i++)
           if(isalpha(board[x][y-i]))
               if(board[x][y-i]=='Q'||board[x][y-i]=='R'){
                    printf("check!\n");   checkMateWhite=1;
                if(board[x][y-i]=='Q'){
                    piece='Q';   piecerow=x;   piececolumn=y-i;   break;
                }else{
                piece='R';   piecerow=x;    piececolumn=y-i;  break;
                }
               }
               else      break;

    for(int i=1;((x+i)<8||(y-i)>=0);i++)
        if(isalpha(board[x+i][y-i]))
            if(board[x+i][y-i]=='Q'||board[x+i][y-i]=='B'){
                     printf("check!\n");    checkMateWhite=1;
                if(board[x+i][y-i]=='Q'){
                    piece='Q';   piecerow=x+i;   piececolumn=y-i;   break;
                }else{
                piece='B';   piecerow=x+i;    piececolumn=y-i;  break;
                }
               }
            else      break;

        for(int i=1;((y+i)<8||(x-i)>=0);i++)
           if(isalpha(board[x-i][y+i]))
               if(board[x-i][y+i]=='Q'||board[x-i][y+i]=='B'){
                      printf("check!\n");    checkMateWhite=1;
                if(board[x-i][y+i]=='Q'){
                    piece='Q';   piecerow=x-i;   piececolumn=y+i;   break;
                }else{
                piece='B';   piecerow=x-i;    piececolumn=y+i;  break;
                }
               }
               else      break;

    for(int i=1;((x+i)<8||(y+i)<8);i++)
        if(isalpha(board[x+i][y+i]))
            if(board[x+i][y+i]=='Q'||board[x+i][y+i]=='B'){
                      printf("check!\n");   checkMateWhite=1;
                if(board[x+i][y+i]=='Q'){
                    piece='Q';   piecerow=x+i;   piececolumn=y+i;   break;
                }else{
                piece='B';   piecerow=x+i;    piececolumn=y+i;  break;
                }
               }
            else      break;

        for(int i=1;((y-i)>=0||(x-i)>=0);i++)
           if(isalpha(board[x-i][y-i]))
               if(board[x-i][y-i]=='Q'||board[x-i][y-i]=='B'){
                      printf("check!\n");   checkMateWhite=1;
                if(board[x-i][y-i]=='Q'){
                    piece='Q';   piecerow=x-i;   piececolumn=y-i;   break;
                }else{
                piece='B';   piecerow=x-i;    piececolumn=y-i;  break;
                }
               }
               else      break;


}


