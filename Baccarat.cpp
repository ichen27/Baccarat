#include <iostream>
#include <cassert>
#include <cstdlib>
#include <time.h>

using namespace std;

void menu(int&);
int dealcards(void);
int playerhand(int);
int dealerhand(int, int);
int winner(int, int);
void settlewager(int&, int, int);


int main() {
  int balance = 100;
  int enter;
  while(balance > 0){
    cout<<"Current Balance: $" <<balance<<endl;
    cout<<endl;
    srand(time(0));
    menu(balance);
  }
}
//function for the menu where user can choose who to bet on and how much they want to wager
void menu(int& balance){
    int choice, wager, won;
    int exit = 1;
    cout<<"Menu: "<<endl;
    cout<<"1. Bet on yourself (Payout: 1:1)"<<endl;
    cout<<"2. Bet on the dealer (Payout: 1:1 with 5% commission)"<<endl;
    cout<<"3. Bet on the tie (Payout: 8:1)"<<endl;
    cout<<"4. End the game"<<endl;
    while (choice != 1 && choice != 2 && choice != 3 && choice != 4){
    cout<<"Your choice: ";
    cin>>choice;
   }
    switch(choice){
      case 1:
        while(wager < 0 || wager > balance){
        cout<<"Wager amount: $";
        cin>>wager;
          }
        won = dealcards();
        if (won == 1){
          won = 1;
        }else if(won == 2){
          won = 2;
        }else if(won == 3){
          won = 3;
        }
        settlewager(balance, won, wager);
        
      break;
      case 2:
        while(wager < 0 || wager > balance){
        cout<<"Wager amount: $";
        cin>>wager;
          }
        won = dealcards();
        if (won == 1){
          won = 2;
        }else if(won == 2){
          won = 1;
        }else if(won == 3){
          won = 3;
        }
        settlewager(balance, won, wager);
    
      break;
      case 3:
        while(wager < 0 || wager > balance){
        cout<<"Wager amount: $";
        cin>>wager;
          }
        won = dealcards();
        if (won == 1){
          won = 3;
        }else if(won == 2){
          won = 3;
        }else if(won == 3){
          won = 4;
        }
        settlewager(balance, won, wager);
        
      break;
      case 4:
        exit = 0;
        cout<<"Thanks for playing!"<<endl;
        cout<<"You're leaving with $"<<balance<<endl;
        balance = 0;
      
    }
}

//function to deal cards and output the total
int dealcards(void){
  int player1, player2, banker1, banker2, p_total, b_total;

  player1 = rand() % 9;
  player2 = rand() % 9;
  banker1 = rand() % 9;
  banker2 = rand() % 9;
  p_total = player1 + player2;
  b_total = banker1 + banker2;
  if (p_total >= 10){
    p_total = p_total - 10;
  }
  if (b_total >= 10){
    b_total = b_total - 10;
  }
  cout<<endl;
  cout<<"Cards dealt: "<<endl;
  cout<<"Player Hand: "<<player1<<" "<<player2<<"          "<<"Banker Hand: "<<banker1<<" "<<banker2<<endl;
  cout<<"Total: "<<p_total<<"                   "<<"Total: "<<b_total<<endl;
  cout<<endl;

  srand(time(0));
  int player3 = playerhand(p_total);
  int banker3 = dealerhand(b_total, player3);

  if(player3 >= 0 || banker3 >= 0){
  if (player3 >= 0 ){
    p_total = p_total + player3;
    if (p_total >= 10){
    p_total = p_total - 10;
  }
    cout<<"Third card for player is drawn: "<<player3<<endl;
  }
  if(banker3 >= 0){
    b_total = b_total + banker3;
    if (b_total >= 10){
    b_total = b_total - 10;
  }     
    cout<<"Third card for banker is drawn: "<<banker3<<endl;
  }
    cout<<endl;
    cout<<"Player Total: "<<p_total<<endl;
    cout<<"Banker Total: "<<b_total<<endl;
    cout<<endl;
 }
  int win = winner(p_total, b_total);
  
  return win;
}

//functionthat will deal the 3rd card for player
int playerhand(int total){
  int card3;
  if (total <= 5){
    card3 = rand() % 9;
  }else{
    cout<<"No third card for the player is drawn"<<endl;
    card3 = -1;
  }
  return card3;
}

//function that will deal the 3rd card for banker
int dealerhand(int b_total, int player3){
  int card3;
  if (b_total <= 2){
    card3 = rand() % 9;
  }
  else if(b_total == 3){
    if (player3 != 8){
      card3 = rand() % 9;
    }else {
      card3 = -1;
      cout<<"No third card for the banker is drawn"<<endl;
      }
  }
  else if(b_total == 4){
    if(player3 != 0 && player3 != 1 && player3 != 8 && player3 != 9){
      card3 = rand() % 9;
    }else {
      card3 = -1;
      cout<<"No third card for the banker is drawn"<<endl;
      }
  }
  else if(b_total == 5){
    if(player3 != 0 && player3 == 1 && player3 != 2 && player3 != 3 && player3 != 8 && player3 != 9){
      card3 = rand() % 9;
    }else{
      card3 = -1;
      cout<<"No third card for the banker is drawn"<<endl;
    }
  }
  else if(b_total == 6){
    if(player3 == 6 || player3 == 7){
      card3 = rand() % 9;
    }else{
      card3 = -1;
      cout<<"No third card for the banker is drawn"<<endl;
    }
  }
  else{
    card3 = -1;
    cout<<"No third card for the banker is drawn"<<endl;
  }

  return card3;
  }

//function that will decide the winner
int winner(int p_total, int b_total){
  int win;
  if (p_total > b_total){
    win = 1;
    cout<<"The player hand has won"<<endl;
  }
  else if(b_total > p_total){
    win = 2;
    cout<<"The banker hand has won"<<endl;
  }
  else if (p_total == b_total){
    cout<<"There was a tie"<<endl;
    win = 3;
  }
  return win;
}

//function that will decide if the user won or loss money and how much
void settlewager(int& balance, int won, int wager){
  if (won == 1){
    balance = balance + wager;
    cout<<"Congrats You have Won $"<<wager<<"!"<<endl;
  }else if(won == 2){
    balance = balance - wager;
    cout<<"Unfortunately you lost $"<<wager<<endl;
  }else if(won == 3){
    balance = balance;
    cout<<"You Will Receive Your $"<<wager<<" Bet Back"<<endl;
  }else if(won == 4){
    balance = balance + (wager*8);
    cout<<"Congrats You Bet on the Tie and Won $"<<(wager*8)<<"!"<<endl;
  }
  cout<<endl;
  return;
}