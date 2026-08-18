// *******************************************************************************************
// LABORATORIO 3 - UART
// Camila Aristizabal 24367
// *******************************************************************************************

#include <Arduino.h>
// LCD

// *******************************************************************************************
// DEFINICIÓN DE PINES
// *******************************************************************************************

// Potenciómetro para intensidad ROJA
#define POT_ROJO 34

// Potenciómetro para intensidad VERDE
#define POT_VERDE 35

// *******************************************************************************************
// CONFIGURACIÓN PWM
// *******************************************************************************************

#define LED_ROJO   25
#define LED_VERDE  26
#define LED_AZUL   27

#define CANAL_ROJO   0
#define CANAL_VERDE  1
#define CANAL_AZUL   2

#define FRECUENCIA_PWM 5000
#define RESOLUCION_PWM 8


// *******************************************************************************************
// VARIABLES GLOBALES
// *******************************************************************************************

int lecturaADC_Rojo = 0;
int lecturaADC_Verde = 0;

int valorRojo = 0;
int valorVerde = 0;


// *******************************************************************************************
// CONFIGURACIÓN
// *******************************************************************************************

void setup()
{
  // Inicializar comunicación UART
  Serial.begin(115200);

  // Configurar entradas
  pinMode(POT_ROJO, INPUT);
  pinMode(POT_VERDE, INPUT);

  
  // CONFIGURACIÓN DE PWM
  

  ledcSetup(CANAL_ROJO, FRECUENCIA_PWM, RESOLUCION_PWM);
  ledcSetup(CANAL_VERDE, FRECUENCIA_PWM, RESOLUCION_PWM);
  ledcSetup(CANAL_AZUL, FRECUENCIA_PWM, RESOLUCION_PWM);

  ledcAttachPin(LED_ROJO, CANAL_ROJO);
  ledcAttachPin(LED_VERDE, CANAL_VERDE);
  ledcAttachPin(LED_AZUL, CANAL_AZUL);

 
}


// *******************************************************************************************
// LOOP PRINCIPAL
// *******************************************************************************************
void loop()
{
  // -------------------------------------------------------------------
  // Leer los dos potenciómetros
  // -------------------------------------------------------------------

  lecturaADC_Rojo = analogRead(POT_ROJO);
  lecturaADC_Verde = analogRead(POT_VERDE);


  // -------------------------------------------------------------------
  //  Convertir de 12 bits a 8 bits
  // -------------------------------------------------------------------
  // ADC ESP32:
  // 0 - 4095
  //
  // Valor de 8 bits:
  // 0 - 255
  // -------------------------------------------------------------------

  valorRojo = lecturaADC_Rojo * 255 / 4095;
  valorVerde = lecturaADC_Verde * 255 / 4095;
  
  
  // actualizar las leds del RGB  luego de hacer la lectura 
  

  ledcWrite(CANAL_ROJO, valorRojo);
  ledcWrite(CANAL_VERDE, valorVerde);

  // Azul apagado
  ledcWrite(CANAL_AZUL, 255);

  // -------------------------------------------------------------------
  //  Enviar los valores por  UART
  // -------------------------------------------------------------------

  Serial.print("Rojo: ");
  Serial.print(valorRojo);

  Serial.print(" | Verde: ");
  Serial.println(valorVerde);


  // -------------------------------------------------------------------
  // Pequeña espera 
  // -------------------------------------------------------------------

  delay(200);


  
}


