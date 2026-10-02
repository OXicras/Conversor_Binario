#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Botao.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int pinBotao [3] = {11, 12, 13};
const int pinLed[4] = {4, 5, 6, 7};
Botao botaoCima;
Botao botaoBaixo;
Botao botaoEnter;
int contador = 0;

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
  botaoCima.atualizar();
  botaoBaixo.atualizar();
  botaoEnter.atualizar();
  

  lcd.setCursor(10, 1);
  lcd.print(contador);

  if(botaoCima.pressionou())
  {
    if (contador < 15)
      contador++;
  }
  if(botaoBaixo.pressionou())
  {
    if (contador > 0)
      contador--;
  }
  if(botaoEnter.pressionou())
  {
    binarioLed();
  }
}

void binarioLed()
{
  if (contador%2 == 0)
  {
    digitalWrite(pinLed[3], HIGH);
  }
  else
  {
    digitalWrite(pinLed[3], LOW);
  }

}