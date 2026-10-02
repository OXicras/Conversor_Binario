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
  Serial.begin(9600);
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
      Serial.println ("APERTOU CIMA");
      if(contador < 15)
      {
        contador++;
        lcd.clear();
      }
        
    }
  }
  estadoAnteriorBotao[0] = estadoAtualBotao[0];

  //! BOTAO BAIXO
  if (estadoAtualBotao[1] != estadoAnteriorBotao[1])
  {
    if (!estadoAtualBotao[1])
    {
      Serial.println ("APERTOU BAIXO");
      if (contador > 0)
      {
        contador--;
        lcd.clear();
      }
    }
  }
  estadoAnteriorBotao[1] = estadoAtualBotao[1];


  //! BOTAO ENTER
  if (estadoAtualBotao[2] != estadoAnteriorBotao[2])
  {
    if (!estadoAtualBotao[2])
    {
      Serial.println ("APERTOU ENTER");
      binarioLed();
      valor = contador;
    }
  }
  estadoAnteriorBotao[2] = estadoAtualBotao[2];

  
}

void binarioLed()
{
  Serial.println ("COMECOU BINARIO");
  bool binario[4] = {0, 0, 0, 0};
  for (int i = 3; i > 0; i--)
  {
    Serial.println ("CONVERTENDO BINARIO");
    Serial.print (binario[i]);
    binario[i] = valor % 2;
    valor /= 2;
  }
  binario[0] = valor;

  for (int i = 0; i < 4; i++)
  {
    Serial.println ("MUDANDO PRO LED");
    Serial.print (binario[i]);
    digitalWrite(pinLed[i], binario[i]);
  }
}