#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

// Classe que engloba todas as possiveis entidades: jogador, tiro e inimigo
class entity {
  private:
  byte pos;		            // Pos % 2 == posicao no lado de tamanho 2, pos / 2 == posicao no lado de tamanho 16
  byte vel = 0;				// Velocidade
  byte sprite = 0; 			// Byte do sprite
  bool live = false;		// Inidica se o objeto existe
  
  public:
  // Set da classe entidades
  void setEntity(byte sprite, bool live);
  void setEntity(byte sprit);
  
  // Muda a posicao no eixo menor
  void UpdatePosY();
  
  // Muda a posicao no eixo maior e muda live para false se estiver fora de 1 até 16
  void UpdatePosX();
  
  // Imprime o objeto
  void WriteEntity();
  
  // Devolve o valor da variavel live
  bool getLive();
  
  // Devolve o valor da variavel pos
  byte getPos();
  
  // Muda o valor de live para true
  void SpawnEntity(byte pos);
  
  // Muda o valor de live para false
  void KillEntity();
};

void entity::setEntity(byte sprite, bool live) {
  pos = 0;
  this->sprite = sprite;
  this->live = live;
    
  if(sprite == 2) {
    this->vel = -2;
  } else {
    this->vel = 2;
  }
}

void entity::setEntity(byte sprite) {
  pos = 0;
  live = false;
  this->sprite = sprite;
  
  if(sprite == 2) {
    this->vel = -2;
  } else {
    this->vel = 2;
  }
}

void entity::UpdatePosY() {
  // Troca o ultimo digito de pos
  pos ^= 1;
}
  
void entity::UpdatePosX() {
  // Testa se objeto pode existirf
  if(pos < 2 || pos > 31) {
    live = false;
  }
  
  // Muda a posicao horizontal sem afetar a vertical
  pos += vel;
}
  
void entity::WriteEntity() {
  // pos >> 1 == pos / 2,  pos & 1 == pos % 2
  lcd.setCursor(pos >> 1, pos & 1);
  lcd.write(sprite);
}
  
bool entity::getLive() {
  return live;
}
  
byte entity::getPos() {
  return pos;
}
  
void entity::SpawnEntity(byte pos)  {
  this->pos = pos;
  live = true;
}
  
void entity::KillEntity()  {
  live = false;
}
