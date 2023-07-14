// Classe responsavel por temporizar em um intervalo constante
class timer {
  private:
  long updateInterval;  // Define o intervalo padrao de ocilacao
  long lastInterval;    // Valor da ultima chamada do intervalo do temporizador
  
  public:
  timer(long Interval);
  
  // Determina se ja passou o tempo do intervalo
  // Se sim, returna verdadeiro e reinicia o temporizador
  // Se não, returna falso
  bool TestTimer();
};

timer::timer(long Interval) {
  updateInterval = Interval;
  lastInterval = millis();
}

bool timer::TestTimer() {
  if(millis() - lastInterval > updateInterval) {
    lastInterval = millis();
    return true;
  }

  return false;
}
