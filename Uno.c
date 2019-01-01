/* *****************************
   Adam Rideout-Arkell 105153544
   
   ***************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 30
#define NOCARD -99
#define CLEAR 100

int showInstructions(void);
void showMyHand(int a[][3]);
int genCardNum(void);
int genCardColour(void);
int dealCards(int a[][3], int howMany);//returns row number of last card dealt
void initHand(int a[][3]);
void playTurn(int a[][3], char name[]);
void genDiscard(void);
_Bool checkDiscard(int a[][3]);
void confirmation(char name[]);
int safeScan(void);
int searchHand(int a[][3], int clr, int nmbr);
int toString(char a[]);
_Bool playableOrNot(int hand[][3], int index);
_Bool winner(int a[][3]);
int genCardNumRand(void);

int discard[1][3];
int colours[] = {114, 121, 103, 98};//r, y, g, b
int cardNumbers[] = {0,1,2,3,4,5,6,7,8,9,-10,-2,-4,-11,-11};
int uniqueId = 0;
int uniqueIdCheck = 99;


int main( void ){
	srand(time(NULL));

	if(showInstructions() == 0) goto exit;//show instructions
	
	printf("%s", "Player 1, please enter your name: ");
	char player1name[20];
	scanf("%19s", player1name);
	printf("%s", "Player 2, please enter your name: ");
	char player2name[20];
	scanf("%19s", player2name);
	puts("");
	
	int player1[SIZE][3] = {0};
	int player2[SIZE][3] = {0};

	initHand(player1);
	initHand(player2);
	
	genDiscard();
	
	printf("%s", "How many cards would you like to deal per player? (Up to 7): ");
	unsigned int perPlayer;
	scanf("%d", &perPlayer);
	if(perPlayer > 7) perPlayer = 7;
	puts("");
	
	dealCards(player1, perPlayer);
	dealCards(player2, perPlayer);	
	int turn = 1;
	
	while (1){//loop broken by "if winner" statement at the end

		if(turn%2 == 1) playTurn(player1, player1name);
		else playTurn(player2, player2name);
		
		if(winner(player1)) {//winner?
			printf("%s wins! Congrats!!\n", player1name);
			break;
		}else if(winner(player2)){
			printf("%s wins! Congrats!!\n", player2name);
			break;
		}
		++turn;
	}
	
	printf("%s","Thanks for playing! ");
	exit: puts("Goodbye.");
}

int showInstructions(void){
	// write the instructions
	for(int i = 0; i <=CLEAR; ++i){
		puts("");
	}
	char instructions[] = "Welcome to Uno for two players. All of the rules are the same as real-life Uno...\n*don't forget to type 'uno' when you have one card remaining...\n| -11 = WILDCARD | -10 = SKIP | -2 = PICKUP 2 | -4 = PICKUP 4.\n\nHave fun!\n";
	int n = sizeof(instructions);
	int j = 0; //line length counter
	for(size_t i = 0; i < n; ++i){
		printf("%c", instructions[i]);
		if(instructions[i] == '\n') j = 0;
		++j;
		if (j >= 100) {
			if (instructions[i] == ' '){
				puts("");
				j = 0;
			}
		}
	} puts("");
	
	unsigned int answer;	
	int inputGood;
	do {//give the user time to read the instructions
		printf("%s", "Type 1 to play, 0 to quit: ");
		inputGood = scanf("%d", &answer);
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
	} while (inputGood != 1 || answer > 1);
	return answer;
}

void showMyHand(int a[][3]){
	int t = 0;
	
	for(int n = 0; n<SIZE; ++n){
		if (a[n][0] != NOCARD){
			printf("|%c%3d|  ", a[n][0], a[n][1]);
			++t;
			if(t%7 == 0) printf("%s", "\n\n           ");	
		}
	}
	puts("");
}

int genCardNum(void){
	int x = rand()%15;
	if (x>9) {
		if(rand()%3 == 1) x = rand()%10;	
	}
	return cardNumbers[x];
}

int genCardNumRand(void){
	int x;
	do{
		x = rand()%15-4;
		if(x == 10) x = -10;
	} while (x == -3 || x == -1 || (x < 0 && (rand()%3) != 0));
	return x;
}

int genCardColour(void){
	return colours[rand()%4];
}

int dealCards(int a[][3], int howMany){
	int x = 1;
	int row = 0;
	for(; x<=howMany; ++row){
		if(a[row][0] == NOCARD){
			++x;
			a[row][0] = genCardColour();
			a[row][1] = genCardNum();
			a[row][2] = uniqueId;
			++uniqueId;
		}	
	}
	return row-1;
}

void initHand(int a[][3]){
	for(int i = 0; i<SIZE; ++i){//initialize players
		for(int j = 0; j<3; ++j){
			a[i][j] = NOCARD;
		}
	}
}

void playTurn(int a[][3], char name[]){

	confirmation(name);
	printf("current discard: |%c%2d| ", discard[0][0], discard[0][1]);
	if (checkDiscard(a) == 1) goto endOfTurn; //return of 1 means it's a skip card.
	printf("-- %s's hand: ", name);
	showMyHand(a);
	puts("");
	
	
	
	while (1){
		printf("%s", "Choose from the following options:\n1 = See Your Hand\n2 = Pick Up a Card\n3 = Play a Card\n4 = End Your Turn: ");
		int choice = safeScan();

		switch(choice){
			case 1: 
				printf("\ncurrent discard: |%c%2d| ", discard[0][0], discard[0][1]);
				printf("-- %s's hand: ", name);
				showMyHand(a);
				break;
				
			case 2://pickup
				{int lastCard = dealCards(a, 1);
				printf("\nYou picked up a |%c%2d|\n\n", a[lastCard][0], a[lastCard][1]);
				//add fuction to play picked up card
				uniqueIdCheck = discard[0][2];}
				break;
			
			case 3://play
				printf("%s", "Type the card that you want to play (like y3, or r-10): ");
				char cardPlayed[5];
				scanf("%s", cardPlayed);
				int numberPlayed = toString(cardPlayed);
				int play = searchHand(a, cardPlayed[0], numberPlayed);
				
				if(numberPlayed == -11){//wildcard
					char cl;
					do{
						printf("%s", "A wild card! Please type the colour you want to change to (r, y, g, or b): ");
						scanf(" %c", &cl);
						int c;
						while ((c = getchar()) != '\n' && c != EOF);
					} while(cl !='r' && cl !='y' && cl !='g' && cl !='b');
					
					puts("");
					discard[0][0] = cl;
					discard[0][1] = -11;
					a[play][0] = NOCARD;
					break;
				}
				
				if(play == -1){
					printf("\nYou do not have %s in your hand.\n\n", cardPlayed);
				}else if(playableOrNot(a, play) == 0){
					printf("%s is not playable right now.\n\n", cardPlayed);
				}else{
					puts("\nNice move!\n");
				}
				
				
				
				break;
			
			case 4://end turn. add UNO check.
				for(int i = 0; i <=CLEAR; ++i){
				puts("");
				}
				goto endOfTurn;
			
		}
			
	}
	endOfTurn: puts("\n");		
}

int searchHand(int a[][3], int clr, int nmbr){//return row number if card present, -1 if not present
	for(int i = 0; i<SIZE; ++i){
		if(a[i][0] == clr){
			if(a[i][1] == nmbr){
				return i;
			}
		}
	}
	return -1;
}

void genDiscard(void){
	discard[0][0] = genCardColour();
	discard[0][1] = genCardNum();
	discard[0][2] = uniqueId;
	++uniqueId;

}

_Bool checkDiscard(int a[][3]){
	int x = 0;
	if(discard[0][2] != uniqueIdCheck){
		if(-2 == discard[0][1]) {
			puts("PICKUP 2! 2 new cards have been added to your hand.");
			dealCards(a, 2);
			uniqueIdCheck = discard[0][2];
		}else if (-4 == discard[0][1]){
			puts("PICKUP 4! 4 new cards have been added to your hand.");
			dealCards(a, 4);
			uniqueIdCheck = discard[0][2];
		}else if (-10 == discard[0][1]) {
			puts("YOU HAVE BEEN SKIPPED, and your turn is over!");
			x = 1;
			uniqueIdCheck = discard[0][2];
		}else if (-11 == discard[0][1]){
			printf("%s", 	"-- your hand: ");
			showMyHand(a);
			char cl;
			do{
				printf("%s", "Discard is wild! Please type the colour you want to change to (r, y, g, or b): ");
				scanf(" %c", &cl);
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
			} while(cl !='r' && cl !='y' && cl !='g' && cl!='b');
			
			puts("");
			discard[0][0] = cl;
			uniqueIdCheck = discard[0][2];
		}
	}
	return x;
}

void confirmation(char name[]){
	int y;//confirmation
	do{
	printf("%s, type \"1\" to play your turn: ", name);
	if((scanf("%d", &y)) != 1){
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		}
	} while(y != 1);
}

int safeScan(void){
	int y;
	if((scanf("%d", &y)) != 1){
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		}
	
	return y;
}

int toString(char a[]) {
  int c, sign, offset, n;
 
  if (a[1] == '-') {  // Handle negative integers
    sign = -1;
  }
 
  if (sign == -1) {  // Set starting position to convert
    offset = 2;
  }
  else {
    offset = 1;
  }
 
  n = 0;
 
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }
 
  if (sign == -1) {
    n = -n;
  }
 
  return n;
}

_Bool playableOrNot(int hand[][3], int index){//makes the play and returns 1, or if not allowed returns 0
	if (hand[index][1] == -11){
		return 1;
	}
	for(int either = 0; either<2; ++either){
		if(hand[index][either] == discard [0][either]){
			for(int both = 0; both<3; ++both){
				discard[0][both] = hand[index][both];
				hand[index][0] = NOCARD;
			}
			return 1;
		}
	}
	return 0;
}

_Bool winner(int a[][3]){
	int sum = 0;
	for(int j = 0; j<SIZE; ++j){
		sum += a[j][0];
	}
	if (sum == SIZE * NOCARD) return 1;
	else return 0;
}