#include "Entidades.h"
#include "Timer.h"
#include "GameFunctionality.h"

// Inicializa as portas ligas ao lcd
uint8_t const rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);   

// Define os botoeos usados para mover e atirar
#define switch0 3
#define switch1 2

void setup() {
  // Define os botoes de entrada para que quando pressionados ativem uma interrupcao
  attachInterrupt(digitalPinToInterrupt(switch0), InputGame1, FALLING);
  attachInterrupt(digitalPinToInterrupt(switch1), InputGame2, FALLING);

  // Inicia lcd 16x2
  InicLcd();  
  
  // Define o sprite do jogador
  Player.setEntity(0, true);
  
  // Define o sprite dos tiros
  for(int i = 0; i < numShots; i++) {
    Shots[i].setEntity(1, false); 
  } 
  
  // Define o sprite dos inimigos
  for(int i = 0; i < numEnemys; i++) {
    Enemys[i].setEntity(2, false); 
  }
  
  randomSeed(analogRead(A0));
}

void loop() {
  PrintGame();
  
  if(!Player.getLive()) {
    EndGame();
  }

  noInterrupts();

  RulesGame();
  
  interrupts();

  delay(400);
}
