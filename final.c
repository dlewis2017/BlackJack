#include <stdio.h>
#include <math.h>
#include "gfx3.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define HAND 10
void initializeHands(int player[HAND], int dealer[HAND]);
void startHand(int player[HAND], int dealer_hand[HAND]);
void beginPrompt();
void dispRules();

void drawDesign(int xpos, int ypos);//draws a design on each card, called within draw functions

void p_drawNum(int player[HAND], int num_cards); //draws the number of the card value on each card
void d_drawNum(int dealer[HAND], int num_cards);

void draw_deck(int xpos, int ypos, int width, int height); //recursive function to draw deck

void drawPlayer(int player[HAND], int dx);	//draws the cards as well as calls the design function
void drawDealer(int dealer[HAND], int dx);

void p_dispTotal(int player[HAND], int num_cards);	//displays the total on the screen
void d_dispTotal(int dealer[HAND], int num_cards);

void hitPlayer(int player[HAND], int num_cards);

void deal(int dealer[HAND], int player[HAND], int pcards);	//a function that runs until the hand ends, either the dealer will win or bust (or tie)

void playerBust();
void blackjack();

int totalHand(int player[HAND], int num_cards);
int totalDealer(int dealer[HAND], int num_cards);

char * itoa (int value, char *result, int base);

int main(){
	srand(time(NULL));
	size_t player_count = 0;	//count of player total points, dealer total points
	size_t dealer_count = 0;
	char choice;
	char hitstay;
	int player_hand[10], dealer_hand[10];	//assuming max hand size will be 10, although nearly impossible
	size_t pCards = 2;	//starts with 2 cards in each hand, one for dealer (number of cards in hand)
	size_t dCards = 1;
	initializeHands(player_hand, dealer_hand); //initialize the arrays to zero
	int xsize = 1000;
	int ysize = 1000;
	int xpos = 50;
	int ypos = 400;
	int width = 100;
	int height = 130;

	beginPrompt();
	scanf("%c",&choice);
	if (choice == 'r'){
		dispRules();
		printf("\nType 'b' to begin: ");
		scanf("%c ", &choice);
		if (choice == 'b') return 0;
	}
	gfx_open(xsize, ysize, "Blackjack");
	startHand(player_hand, dealer_hand);
	while(1){
		draw_deck(xpos,ypos,width,height);
		drawPlayer(player_hand, pCards);
                drawDealer(dealer_hand, dCards);
                p_drawNum(player_hand, pCards);
                d_drawNum(dealer_hand, dCards);
                p_dispTotal(player_hand, pCards);
                d_dispTotal(dealer_hand, dCards);
		if (totalHand(player_hand, pCards) > 21){
			p_dispTotal(player_hand, pCards);
			playerBust();
			initializeHands(player_hand, dealer_hand);
			startHand(player_hand, dealer_hand);
			pCards = 2;
			dCards = 1;
			gfx_flush();
			usleep(3000000);
			gfx_clear();
			continue;
		}
		if ((totalHand(player_hand, pCards) == 21) && pCards == 2){
			blackjack();
			initializeHands(player_hand, dealer_hand);
                        startHand(player_hand, dealer_hand);
                        pCards = 2;
                        dCards = 1;
                        gfx_flush();
                        usleep(3000000);
                        gfx_clear();
			continue;
		}
		gfx_flush();
		hitstay = gfx_wait();
		if (hitstay == 'q') return 0;
		if (hitstay == 'h') {
			pCards++;
			hitPlayer(player_hand, pCards);
			drawPlayer(player_hand, pCards);
			p_dispTotal(player_hand, pCards);
		}
		if (hitstay == 's') {
			deal(dealer_hand, player_hand, pCards);
			initializeHands(player_hand, dealer_hand);
			startHand(player_hand, dealer_hand);
			pCards = 2;
			dCards = 1;
			gfx_flush();
			usleep(3000000);
			gfx_clear();
			continue;
		}
		gfx_clear();
	}
}

void initializeHands(int player[HAND], int dealer[HAND]){
	size_t i;
	for (i=0;i<HAND;i++){
		player[i]=0;
		dealer[i]=0;
	}
}

void beginPrompt(){
	printf("Hello, and welcome to the Blackjack table.\nPress 'r' to hear the rules or type 'b' to begin: ");
}

void dispRules(){
	printf("Rules:You are competing against the dealer to get as close to 21 points total without going over.\nIf you hit exactly 21 points, you get 'Blackjack' but if you go over you lose.\n");
	printf("Aces can count for either one point or eleven, depending on the situation. Face cards all count for ten points.\n");
	printf("When prompted for a decision, you may either type 's' to STAY or 'h' to HIT.\n");
	printf("You may press any other key or the click with the mouse to change the colors on the cards.");
	printf("At any point in the program, you may type 'q' to exit Blackjack.");
}

void startHand(int player_hand[HAND], int dealer_hand[HAND]){	//gives the player and the dealer 2 starting cards
	player_hand[0] = (rand() % 13) + 1;
	dealer_hand[0] = (rand() % 13) + 1;
	player_hand[1] = (rand() % 13) + 1;
}

void draw_deck(int xpos, int ypos, int width, int height){ //recursive function to draw deck
	int i;
	gfx_color(250,250,250);
	//base case
	if(xpos > 60){
		gfx_fill_rectangle(xpos,ypos,width,height);
		gfx_color(0,0,0);
		gfx_rectangle(xpos, ypos, width, height);
		drawDesign(xpos+width/2,ypos+height/2);
		return;
	}
	
	//draw rectangle
	if(xpos%2 == 0){
	gfx_color(0,0,0);
	}
	gfx_rectangle(xpos,ypos,width,height);
	
	//recursive calls
	draw_deck(xpos+1,ypos+1,width+1,height+1);

}
void drawPlayer(int player[HAND], int dx){
	gfx_color(255,255,255);
	int i;
	for (i=0;i<dx;i++){
		gfx_fill_rectangle(100 + i*120, 700, 100, 130);
	}
	for (i=0;i<dx;i++){
		drawDesign(150 + i*120, 765);
	}
}

void drawDealer(int dealer[HAND], int dx){
        gfx_color(255,255,255);
        int i;
        for (i=0;i<dx;i++){
                gfx_fill_rectangle(100 + i*120, 100, 100, 130);
        }
	for (i=0;i<dx;i++){
		drawDesign(150 + i*120, 165);
	}
}

void hitPlayer(int player[HAND], int num_cards){
	player[num_cards - 1] = rand() % 13 + 1;
}

void deal(int dealer[HAND], int player[HAND], int p_num_cards){
	int dCards = 1;
	while (totalHand(dealer, dCards) < 17){
		hitPlayer(dealer, dCards);
		gfx_flush();
		gfx_clear();
		draw_deck(50,400,100,130);
		drawDealer(dealer, dCards);
		drawPlayer(player, p_num_cards);
                p_drawNum(player, p_num_cards);
                d_drawNum(dealer, dCards);
                d_dispTotal(dealer, dCards);
		p_dispTotal(player, p_num_cards);
		dCards++;
	}
	if (totalHand(dealer, dCards) > 21){
		gfx_color(0,255,0);
		gfx_text(500, 500, "Congratulations, the dealer bust! You win!");
		usleep(500000);
	}
	else if (totalHand(dealer, dCards) > totalHand(player,p_num_cards)){
		gfx_color(255,0,0);
		gfx_text(500, 500,"Uh oh, you have lost to the dealer. We'll take your money now.");
		usleep(500000);
	}
	else if (totalHand(dealer, dCards) == totalHand(player, p_num_cards)){
		gfx_color(0,255,0);
		gfx_text(500, 500, "You have tied! If this were Vegas you'd get your money back!");
		usleep(500000);
	}
	else{
		gfx_color(0,255,0);
		gfx_text(500, 500, "Congratulations, you have beaten the dealer!");
		usleep(500000);
	}
}

void playerBust(){
	gfx_color(255, 0, 0);
	gfx_text(500, 500, "You bust! We will take your money now.");
	usleep(50000);
}

void blackjack(){
	gfx_color(0,255,0);
	gfx_text(500, 500, "Blackjack! Your money is instantly doubled!");
}
void p_dispTotal(int player[HAND], int num_cards){
	gfx_color(255,255,255);
	int total = totalHand(player, num_cards);
	char buffer[5];
	itoa(total, buffer, 10);
	gfx_text(100, 600, "Player total: ");
	gfx_text(185, 600, buffer);
}

void d_dispTotal(int dealer[HAND], int num_cards){
	gfx_color(255,255,255);
        int total = totalHand(dealer, num_cards);
        char buffer[5];
        itoa(total, buffer, 10);
        gfx_text(100, 300, "Dealer total: ");
        gfx_text(185, 300, buffer);
}

int totalHand(int player[HAND], int num_cards){
	int total = 0;
	int i;
        for (i=0;i<num_cards;i++){
		if (player[i] > 10){
			total += 10;
			continue;
		}
		if (total <= 10 && player[i] == 1){
			total += 11;
			continue;
		}
		total += player[i];
        }
        return total;
}


int totalDealer(int dealer[HAND], int num_cards){
        int total = 0;
        int i;
        for (i=0;i<num_cards;i++){
                if (dealer[i] > 10) total += 10;
                else total += dealer[i];
        }
        return total;
}

char * itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void p_drawNum(int player[HAND], int num_cards){
	gfx_color(0,0,0);
	int i = 0;
	for (i;i<num_cards;i++){
		if(player[i] == 1)
		{
                        gfx_text(105 + i*120, 710, "Ace");
                }
                if(player[i] == 2)
                {
                        gfx_text(105 + i*120, 710, "Two");
                }
                if(player[i] == 3)
                {
                        gfx_text(105 + i*120, 710, "Three");
                }
                if(player[i] == 4)
                {
                        gfx_text(105 + i*120, 710, "Four");
                }
                if(player[i] == 5)
                {
			gfx_text(105 + i*120, 710, "Five");
                }
                if(player[i] == 6)
                {
                        gfx_text(105 + i*120, 710, "Six");
                }
                if(player[i] == 7)
                {
                        gfx_text(105 + i*120, 710, "Seven");
                }
                if(player[i] == 8)
                {
                        gfx_text(105 + i*120, 710, "Eight");
                }
                if(player[i] == 9)
                {
                        gfx_text(105 + i*120, 710, "Nine");
                }
                if(player[i] == 10)
                {
                        gfx_text(105 + i*120, 710, "Ten");
                }
                if(player[i] == 11)
                {
                        gfx_text(105 + i*120, 710, "Jack");
                }
                if(player[i] == 12)
                {
                        gfx_text(105 + i*120, 710, "Queen");
                }
                if(player[i] == 13)
                {
                        gfx_text(105 + i*120, 710, "King");
                }
	}
}

void d_drawNum(int dealer[HAND], int num_cards){
        gfx_color(0,0,0);
        int i = 0;
        for (i;i<num_cards;i++){
                if(dealer[i] == 1)
                {
                        gfx_text(105 + i*120, 110, "Ace");
                }
                if(dealer[i] == 2)
                {
                        gfx_text(105 + i*120, 110, "Two");
                }
                if(dealer[i] == 3)
                {
                        gfx_text(105 + i*120, 110, "Three");
                }
                if(dealer[i] == 4)
                {
                        gfx_text(105 + i*120, 110, "Four");
                }
                if(dealer[i] == 5)
                {
                        gfx_text(105 + i*120, 110, "Five");
                }
                if(dealer[i] == 6)
                {
                        gfx_text(105 + i*120, 110, "Six");
                }
                if(dealer[i] == 7)
                {
                        gfx_text(105 + i*120, 110, "Seven");
                }
                if(dealer[i] == 8)
                {
                        gfx_text(105 + i*120, 110, "Eight");
                }
                if(dealer[i] == 9)
                {
                        gfx_text(105 + i*120, 110, "Nine");
                }
                if(dealer[i] == 10)
                {
                        gfx_text(105 + i*120, 110, "Ten");
                }
                if(dealer[i] == 11)
                {
                        gfx_text(105 + i*120, 110, "Jack");
                }
                if(dealer[i] == 12)
                {
                        gfx_text(105 + i*120, 110, "Queen");
                }
                if(dealer[i] == 13)
                {
                        gfx_text(105 + i*120, 110, "King");
                }
        }
}

void drawDesign(int xpos, int ypos){
	int i = 0;
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	for (i;i<25;i++){
		int r = rand() % 255;
	        int g = rand() % 255;
        	int b = rand() % 255;
		gfx_color(r,g,b);
		gfx_circle(xpos, ypos, i);
	}
}

