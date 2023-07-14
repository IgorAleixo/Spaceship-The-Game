#include "Dados.h"

// Define o numero maximo de tiros e inimigos em tela
#define numShots 2
#define numEnemys 6


// Variaveis globais das entidades
entity Player;	           
entity Shots[numShots];	   
entity Enemys[numEnemys]; 

// Estados das variaveis
bool volatile flagInput[2] = {false, false};

// Inicia o ldc
void InicLcd() {
  lcd.begin(16, 2);
  
  // Limpa a tela
  lcd.clear();
  
  // Armazena os sprites dos objetos 
  lcd.createChar(0, playerSprite);     
  lcd.createChar(1, shotSprite);  
  lcd.createChar(2, enemySprite);   
  
  lcd.setCursor(3, 0);
  lcd.print("Spaceship:");
  lcd.setCursor(4, 1);
  lcd.print("The Game");

  while(1){
    if(flagInput[0] || flagInput[1]) {
      flagInput[0] = 0;
      flagInput[1] = 0;
      break;
    }
  } 
}

// Imprime a tela de fim de game
void EndGame() {
  interrupts();

  lcd.clear();
  
  lcd.setCursor(3, 0);
  lcd.print("Game Over!");
  
  lcd.setCursor(3, 1);
  lcd.print("Restart? ");
  
  for(int i = 9; ; i--) {
    lcd.setCursor(12, 1);
    lcd.print(i);
    delay(1000);
  }
}

// Recebe os inputs dos botoes
void InputGame1() {
  flagInput[0] = 1;
}

void InputGame2() {
  flagInput[1] = 1;
}

// Estabelece as regras de negocios do jogo
void RulesGame() {
  timer static t_EnemySpawn(random(1, 3) * 500);
  timer static t_ShotSpawn(500);
  
  // Gera inimigos em um dado intervalo
  if(t_EnemySpawn.TestTimer()) {
    for(int i = 0; i < numEnemys; i++) {
      if(!Enemys[i].getLive()){
        Enemys[i].SpawnEntity(30 + random(2));
        break;
      }
    }
  }
  
  // Gera tiros em um dado intervalo, se o botao estver pressionado
  if(flagInput[1]) {
    if(t_ShotSpawn.TestTimer()) {
      flagInput[1] = 0;

      for(int i = 0; i < numShots; i++) {
        if(Shots[i].getLive() == false){
          Shots[i].SpawnEntity(Player.getPos() + 2);
          break;
        }
      }
    }
  }
  
  // Avanca todos os inimigos
  for(int i = 0; i < numEnemys; i++) {
    if(Enemys[i].getLive() == true){
      Enemys[i].UpdatePosX();
    }
  }
  
  // Testa colicao dos objetos
  for(int i = 0; i < numEnemys; i++) {
    for(int j = 0; j < numShots; j++) {
      if(!Enemys[i].getLive() || !Shots[j].getLive()) continue;
      
      byte posEnemy = Enemys[i].getPos();
      byte posShot = Shots[j].getPos();
      
      // Testa se o tiro e inimigo estão na mesma casa ou uma casa a frente do outro
      if(posShot == posEnemy || posShot + 2 == posEnemy) {
        Enemys[i].KillEntity();
        Shots[j].KillEntity();
        break;
      }  
  	}
    
    if(Enemys[i].getLive() && Player.getPos() == Enemys[i].getPos()) {
      Player.KillEntity();
    }
  }
  
  // Testa switch de posição
  if(flagInput[0]) {
    flagInput[0] = 0;
  	Player.UpdatePosY();
  }
  
  // Avanca todos os tiros de posicao
  for(int i = 0; i < numShots; i++) {
    if(Shots[i].getLive()){
      Shots[i].UpdatePosX();
    }
  }
}

// Imprime a situação do jogo
void PrintGame() {
  // Limpa a tela do lcd
  lcd.clear();
    
  // Imprime o jogador
  Player.WriteEntity();
    
  // Imprime os inimigos se existirem
  for(int i = 0; i < numShots; i++) {
    if(Shots[i].getLive()){
      Shots[i].WriteEntity();
    }
  }

  // Imprime os tiros se existirem
  for(int i = 0; i < numEnemys; i++) {
    if(Enemys[i].getLive()){
      Enemys[i].WriteEntity();
    }
  }
}
