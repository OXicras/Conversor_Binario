#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int pinBotao [3] = {11, 12, 13};
const int pinLed[4] = {4, 5, 6, 7};
int contador = 0;
int valor;

void binarioLed();

void setup() 
{
  lcd.init();
  lcd.backlight();
  pinMode(pinLed[0], OUTPUT);
  pinMode(pinLed[1], OUTPUT);
  pinMode(pinLed[2], OUTPUT);
  pinMode(pinLed[3], OUTPUT);
  pinMode(pinBotao[0], INPUT_PULLUP);
  pinMode(pinBotao[1], INPUT_PULLUP);
  pinMode(pinBotao[2], INPUT_PULLUP);
}

void loop() 
{
  bool estadoAtualBotao[3] = {digitalRead(pinBotao[0]), digitalRead(pinBotao[1]), digitalRead(pinBotao[2])};
  static bool estadoAnteriorBotao[3] = {1, 1, 1};
  
  lcd.setCursor(9, 1);
  lcd.print(contador);

//! BOTAO CIMA
  if (estadoAtualBotao[0] != estadoAnteriorBotao[0])
  {
    if (!estadoAtualBotao[0])
    {
      if(contador < 15)
      {
        contador++;
      }
        
    }
  }
  estadoAnteriorBotao[0] = estadoAtualBotao[0];

  //! BOTAO BAIXO
  if (estadoAtualBotao[1] != estadoAnteriorBotao[1])
  {
    if (!estadoAtualBotao[1])
    {
      if (contador > 0)
      {
        contador--;
      }
    }
  }
  estadoAnteriorBotao[1] = estadoAtualBotao[1];


  //! BOTAO ENTER
  if (estadoAtualBotao[2] != estadoAnteriorBotao[2])
  {
    if (!estadoAtualBotao[2])
    {
      binarioLed();
      valor = contador;
      digitalWrite(pinLed[3], LOW);
      digitalWrite(pinLed[2], LOW);
      digitalWrite(pinLed[1], LOW);
      digitalWrite(pinLed[0], LOW);
    }
  }
  estadoAnteriorBotao[2] = estadoAtualBotao[2];

  
}

void binarioLed()
{
  bool binario[4] = {};
  for (int i = 3; i > 0; i--)
  {
    binario[i] = valor % 2;
    valor /= 2;
  }
  binario[3] = valor;
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(pinLed[i], binario[i]);
  }
}