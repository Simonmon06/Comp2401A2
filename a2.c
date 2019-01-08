#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char name[32];
  int  strength;
  int  armour;
  int  health;

} HeroType;

typedef struct {
  int  strength;
  int  health;

} PirateType;

typedef struct {
  PirateType **arr;
  int  pNumber;
  int top;
} ArrayType;

//-------------------------------------------------------------------

int  randomInt(int);
PirateType initPirate();
void initArr(ArrayType *arr);

void heroRespawn(HeroType* timmy, HeroType* harold);
void pop(ArrayType * pirArray);
void fight(HeroType* hero, ArrayType* pirArray);
void printStat(int* timmyWin,int* haroldWin,int* bothWin, int* pirateWin);
void oneRound(int* timmyWin,int* haroldWin,int* bothWin, int* pirateWin, HeroType *timmy, HeroType *harold, ArrayType* pirArray);
//-------------------------------------------------------------------
int main()
{
srand(time(NULL));//pick seed by current time
HeroType *timmy, *harold;
timmy=calloc(1,sizeof(HeroType));
harold=calloc(1,sizeof(HeroType));

strcpy(timmy->name, "Timmy");
strcpy(harold->name, "Harold");

timmy->strength = 5;
timmy->armour = 5;
timmy->health = 30;

harold->strength= 7;
harold->armour = 3;
harold->health = 30;
//printf("\n%s  strength: %d Hp: %d  armour: %d\n", timmy->name,timmy->strength,timmy->health,timmy->armour);
//printf("%s  strength: %d Hp: %d  armour: %d\n", harold->name,harold->strength,harold->health,harold->armour);

  int timmyWin=0;
  int haroldWin=0;
  int bothWin=0;
  int pirateWin=0;
for(int k=0; k<100; ++k){
  heroRespawn(timmy,harold);

  ArrayType *enemyArray;
  enemyArray=calloc(1,sizeof(ArrayType));
  initArr(enemyArray);


  while((timmy->health>0 || harold->health>0)&& enemyArray->pNumber>0){

    oneRound(&timmyWin,&haroldWin,&bothWin,&pirateWin,timmy,harold,enemyArray);
    printf("\n%s  strength: %d Hp: %d  armour: %d\n", timmy->name,timmy->strength,timmy->health,timmy->armour);
    printf("%s  strength: %d Hp: %d  armour: %d\n", harold->name,harold->strength,harold->health,harold->armour);
  }
  printf("over");

  printf("\nPnumber%d\n", enemyArray->pNumber);
  printStat(&timmyWin,&haroldWin,&bothWin,&pirateWin);
  while(enemyArray->top!=-1){
  pop(enemyArray);
  }
  free(enemyArray->arr);
  free(enemyArray);
  }
  free(timmy);
  free(harold);

}


void initArr(ArrayType *pirArray){

pirArray->top=9;
pirArray->arr = (PirateType **) calloc(10,sizeof(PirateType *));

for(int i=0; i<10;++i){

  PirateType *pirate;
  pirate =calloc(1,sizeof(PirateType));
  pirate->health=20;
  pirate->strength=randomInt(4)+3;
  pirArray->arr[pirArray->pNumber]=pirate;
  pirArray->pNumber++;
  }
}



void fight(HeroType* hero, ArrayType* pirArray){

  while(hero->health>0 && pirArray->top!=-1&&pirArray->arr[pirArray->top]->health>0){
    pirArray->arr[pirArray->top]->health -= hero->strength;
    if(pirArray->arr[pirArray->top]->health>0){
      int tem = pirArray->arr[pirArray->top]->strength + randomInt(1+(pirArray->arr[pirArray->top]->strength));
      int damage= tem-hero->armour;
      if(damage<=0){damage=0;}
      hero->health-=damage;
      printf("Pirate's Health: %d\n", pirArray->arr[pirArray->top]->health);
      printf("Pirate's Strength: %d\n", pirArray->arr[pirArray->top]->strength);
      printf("Pirate's tempoary Strength: %d\n",tem);
      printf("%s's Health: %d\n",hero->name, hero->health);
      printf("%s's Strength: %d\n\n",hero->name, hero->strength);
    }
    else {
      pop(pirArray);
      hero->health+=3;
      printf("hero level up!\n");
    }


        printf("///////%s's Health: %d\n",hero->name, hero->health);
        printf("pri->top%d",pirArray->top);

  }
}


void pop(ArrayType * pirArray){
  free( pirArray->arr[pirArray->top--]);
   pirArray->pNumber--;
}


void heroRespawn(HeroType *timmy, HeroType *harold){
  timmy->health=30;
  harold->health=30;
  //printf("%s strength: %d health:%d", timmy->name,timmy->strength,timmy->health);
}

void printStat(int* timmyWin,int* haroldWin,int* bothWin, int* pirateWin){
  printf("Timmy Win: %d\n",*timmyWin);
  printf("Harold Win: %d\n",*haroldWin);
  printf("Both Timmy and Harold Win: %d\n",*bothWin);
  printf("Pirate Win: %d\n",*pirateWin);
}

void oneRound(int* timmyWin,int* haroldWin,int* bothWin, int* pirateWin, HeroType *timmy, HeroType *harold, ArrayType* pirArray){
  int fateCoin=randomInt(2);
  int battleContinue=1;
  while(battleContinue==1){
    if(fateCoin==1){
      if(timmy->health>0){
        fight(timmy, pirArray);
        fateCoin=0;
      }
      if(timmy->health<=0){
        fight(harold, pirArray);
        fateCoin=1;
      }
    }

    if(fateCoin==0){
      if(harold->health>0){
        fight(harold, pirArray);
        fateCoin=1;
      }
      if(harold->health<=0){
        fight(timmy, pirArray);
        fateCoin=0;
      }
    }
    if(timmy->health<=0 &&harold->health>0&&pirArray->pNumber==0){
      *timmyWin+=1;
      battleContinue=0;
    }
    else if(timmy->health>0 &&harold->health<=0&&pirArray->pNumber==0){
      *haroldWin+=1;
      battleContinue=0;
    }
    else if(timmy->health<=0 &&harold->health<=0&&pirArray->pNumber>0){
      *pirateWin+=1;
      battleContinue=0;
    }
    else if(timmy->health>0 &&harold->health>0&&pirArray->pNumber==0){
      *bothWin+=1;
      battleContinue=0;
    }
  }
}
//-----------------------------------------------------
/*

  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
  Parameters:
    in:      maximum of range
    return:  randomly generated number
*/

int randomInt(int max)
{
  return(rand() % max);
}
