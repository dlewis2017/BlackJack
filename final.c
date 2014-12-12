//David Lewis and Jack Ryan
//Final Project CSE 20211
//Blackjack
//final.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gfx3.h"
#include <time.h>

void initialize_hands(int *dealer, int *player);
void beginPrompt();
void dispRules();
void display_player(int player_count, int *player);
void display_dealer(int dealer_count, int *dealer);
char hit_or_stay(char choice3);
int draw_dealer(int *dealer);
int draw_player(int *player);
int player_hit(int player_count, int *player);
int dealer_hit(int dealer_count, int *dealer);
int player_total(int i, int total, int player_count, int *player);
int dealer_total(int i, int total2, int dealer_count, int *dealer);
void decide_winner(int total, int total2);

int main()
{
	while(1)
	{
        srand(time(NULL));
        int xsize = 1000;        //changed this to make it a larger screen
        int ysize = 1000;
        int dealer[10];         //array to hold dealer hand
        int player[10];
        char choice, choice2, choice3, choice4;
        int i = 0;
	int dealer_count = 0;   //running counts of total dealer/player points
        int player_count = 0;
        int total = 0;
        int total2 = 0;
	initialize_hands(dealer,player);

	gfx_open(xsize,ysize,"BLACKJACK");
	beginPrompt();
        scanf(" %c",&choice);
	//runs through the program for you after this point 2nd time around
	//please try the get char thing that you were talking about
        while(choice != 'Q' && choice != 'q' && choice != 'P' && choice != 'p' && choice != 'R' && choice != 'r')
        {
                printf("Choose a valid letter:\nP:Play,R:Rules,Q:quit)\n");
                scanf(" %c", &choice);
        }
	if(choice == 'q' || choice == 'Q')
        {
                return 0;
        }
	if(choice == 'r' || choice == 'R')
	{
		dispRules();
		printf("\nAre you ready to play? (P:Play,Q:Quit)");
		scanf(" %c", choice2);
        	while(choice2 != 'Q' && choice2 != 'q' && choice2 != 'P' && choice2 != 'p')
        	{
            	 	printf("Choose a valid letter:\nP:Play,Q:quit)\n");
    		        scanf(" %c", &choice2);
        	}
		if(choice2 == 'q' || choice2 == 'Q')
        	{
        	        return 0;
       	 	}
	
	}
	printf("----------------B-L-A-C-K-J-A-C-K-------------------\n\n");

//open gfx window and start with gfx_wait and gfx_event waiting

	dealer_count = draw_dealer(dealer); 
        display_dealer(dealer_count,dealer);//from this function there could be another function to draw initial cards
        total2 = dealer_total(i,total2,dealer_count,dealer);
        printf("dealertotal = %d\n",total2); //can get rid of most printf statements in code this was just for the programmer to have a visual of the running totals

        player_count = draw_player(player);
        display_player(player_count,player);//from this function there could be another fucntion to draw initial cards
        total = player_total(i,total,player_count,player);
        printf("playertotal = %d\n",total);

	if(total == 21)
	{
		printf("21! YOU WIN!!!\n");
		main(); //clear screen after every call back to the int main maybe
	}
	//wait for mouse click
        while(choice3 != 'S' && choice3 != 's')//every time mouse click does not click on certain area "STAY BUTTON" continue waiting
        {
		choice3 = hit_or_stay(choice3);
               if(choice3 == 'H' || choice3 == 'h') //if mouse clicks in area of "HIT" button continue
                {
			i = player_count;
                        player_count = player_hit(player_count,player);
                        total = player_total(i,total,player_count,player);
			display_player(player_count,player);//in this function could be another function to add a card to player hand
			printf("playertotal = %d\n",total);
                        if(total > 21)
                        {
                                printf("BUST!!! Sorry you lose...\nThank you for playing BLACKJACK!!\n");
                                main();
                        }
                        if(total == 21)
                        {
                                printf("21! YOU WIN!!!! CONGRATULATIONS!!!!\nThank you for playing BLACKJACK!!\n");
                                main();
                        }
                }
        }
	printf("\n");
        printf("Dealer's turn to hit\n\n"); //move into automatic gfx that is not affected by user clicking or doing anything

        if(total2 >= 17 )
        {
                printf("Dealer Stays\n\n");
        }
	while(total2<17 && total2 < total)
        {
	i = dealer_count;
	dealer_count = dealer_hit(dealer_count,dealer);

        total2 = dealer_total(i,total2,dealer_count,dealer);
        printf("player total = %d\n",total);
        printf("dealer total = %d\n",total2);
        display_dealer(dealer_count,dealer);//another function within that makes new card
	}
	decide_winner(total,total2);
	}
        return 0;
}
void initialize_hands(int *dealer, int *player)
{
	int i;
        for (i=0;i<10;i++){     //initialize dealer and player hands to zero
                dealer[i]=0;
                player[i]=0;
        }
}
void beginPrompt()
{
        printf("Hello, and welcome to the Blackjack table. Are you ready to play or would you like to read the rules first? (P:Play,R:Rules,Q:quit) \n");

}
void dispRules()
{
	printf("Rules:You are competing against the dealer to get as close to 21 points total without going over.\nIf you hit exactly 21 points, you get 'Blackjack' but if you go over you lose.\n");
        printf("Aces can count for either one point or eleven, depending on the situation. Face cards all count for ten points.\n");
        printf("When prompted for a decision, you may either type 's' to STAY or 'h' to HIT.\n");
	printf("House Rules:Dealer will hit with anything below a 17. On a soft 17, the dealer will stay.\n");
}
void display_player(int player_count, int *player)
{
	printf("Your Hand:\n");
	int i;

	for(i = 0;i<=player_count;i++)
	{
		if(player[i] == 1)
		{
			printf("Ace, ");
		}
		if(player[i] == 2)
		{
			printf("Two, ");
		}
		if(player[i] == 3)
		{
			printf("Three, ");
		}
		if(player[i] == 4)
		{
			printf("Four, ");
		}
		if(player[i] == 5)
		{
			printf("Five, ");
		}
		if(player[i] == 6)
		{
			printf("Six, ");
		}
		if(player[i] == 7)
		{
			printf("Seven, ");
		}
		if(player[i] == 8)
		{
			printf("Eight, ");
		}
		if(player[i] == 9)
		{
			printf("Nine, ");
		}
		if(player[i] == 10)
		{
			printf("Ten, ");
		}
		if(player[i] == 11)
		{
			printf("Jack, ");
		}
		if(player[i] == 12)
		{
			printf("Queen, ");
		}
		if(player[i] == 13)
		{
			printf("King, ");
		}
	}
	printf("\n");
}
void display_dealer(int dealer_count, int *dealer)
{
	printf("Dealer's Hand:\n");
	int i;

	for(i=0;i<=dealer_count;i++)
	{
		if(dealer[i] == 1)
		{
			printf("Ace, ");
		}
		if(dealer[i] == 2)
		{
			printf("Two, ");
		}
		if(dealer[i] == 3)
		{
			printf("Three, ");
		}
		if(dealer[i] == 4)
		{
			printf("Four, ");
		}
		if(dealer[i] == 5)
		{
			printf("Five, ");
		}
		if(dealer[i] == 6)
		{
			printf("Six, ");
		}
		if(dealer[i] == 7)
		{
			printf("Seven, ");
		}
		if(dealer[i] == 8)
		{
			printf("Eight, ");
		}
		if(dealer[i] == 9)
		{
			printf("Nine, ");
		}
		if(dealer[i] == 10)
		{
			printf("Ten, ");
		}
		if(dealer[i] == 11)
		{
			printf("Jack, ");
		}
		if(dealer[i] == 12)
		{
			printf("Queen, ");
		}
		if(dealer[i] == 13)
		{
			printf("King, ");
		}
	}
	printf("\n");
}
char hit_or_stay(char choice3)
{
	printf("HIT (H) STAY (S)\n");
        scanf(" %c",  &choice3);
        while(choice3 != 'H' && choice3 != 'S' && choice3 != 'h' && choice3 != 's')
        {
		printf("Choose valid letter:\nHIT (H) STAY (S)\n");
                scanf(" %c", &choice3);
        }
	return choice3;
}
int draw_dealer(int *dealer)
{
	int dealer_count;
	for(dealer_count = 0; dealer_count<1; dealer_count++)
	{
		dealer[dealer_count] = rand()%13+1;
	}
	return dealer_count;

}
int draw_player(int *player)
{
	int player_count;
	for(player_count = 0;player_count<2;player_count++)
	{
		player[player_count] = rand()%13+1;
	}
	return player_count;

}
int player_hit(int player_count, int *player)
{
	player_count++;
	player[player_count] = rand()%13+1;
	//printf("%d Player count", player_count);//
	return player_count;

}
int dealer_hit(int dealer_count, int *dealer)
{
	dealer_count++;
	dealer[dealer_count] = rand()%13+1;
	//printf("%d Dealer count",dealer_count);
	return dealer_count;

}
int player_total(int i, int total, int player_count, int *player)
{
	for(i;i<player_count+1;i++)
	{
		if(player[i] == 1)
		{
			if(total < 11)
			{
				total = total + 11;
			}
			else
			{
				total = total + 1;
			}
		}
		if(player[i] > 9)
		{
			total = total + 10;
		}
		else
		{
			total = total + player[i];
		}
	}
	return total;
}
int dealer_total(int i, int total2, int dealer_count, int *dealer)
{
	for(i;i<dealer_count;i++)
	{
		if(dealer[i] == 1)
		{
			if(total2 < 11)
			{
				total2 = total2 + 11;
			}
			else
			{
				total2 = total2 + 1;
			}
		}
		if(dealer[i] > 9)
		{
			total2 = total2 + 10;
		}
		else
		{
			total2 = total2 + dealer[i];
		}
	}
	return total2;
}
void decide_winner(int total, int total2)
{
	if(total2> 21)
        {
                printf("Dealer BUST!!! You win!!!\nThank you for playing BLACKJACK!!\n");
		main();
        }
	if(total2 == 21)
        {
                printf("21! Dealer wins!!! Sorry...\nThank you for playing BLACKJACK!!\n");
		main();
        }

	if(total > total2)
        {
                printf("Your hand was better, you win!!\n");
        }
	if(total2 > total)
        {
                printf("Sorry, the dealer's hand was better than yours. You lose.\n");
        }
	if(total2 == total)
	{
		printf("Tie!\n");
	}
	printf("Thank you for playing BLACKJACK!!\n\n");
	main();
}
