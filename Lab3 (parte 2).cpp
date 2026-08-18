// *******************************************************************************************
// LABORATORIO 3 - UART
// Camila Aristizabal 24367
// *******************************************************************************************


#include <Arduino.h>

// LiquidCrystal para LCD

#include <LiquidCrystal.h>



// *******************************************************************************************
// DEFINICIÓN DE PINES
// *******************************************************************************************

// -------------------------------
// Potenciómetros
// -------------------------------

#define POT_ROJO   34
#define POT_VERDE  35


// -------------------------------
// LED RGB
// -------------------------------

#define LED_ROJO   25
#define LED_VERDE  26
#define LED_AZUL   27


// -------------------------------
// LCD 16x2 - Modo 8 bits
// -------------------------------

// RS y E
#define LCD_RS 32
#define LCD_E  33

// Líneas de datos
#define LCD_D0 4
#define LCD_D1 16
#define LCD_D2 17
#define LCD_D3 18
#define LCD_D4 19
#define LCD_D5 21
#define LCD_D6 22
#define LCD_D7 23
// *******************************************************************************************
// CONFIGURACIÓN PWM
// *******************************************************************************************

#define CANAL_ROJO  0
#define CANAL_VERDE 1
#define CANAL_AZUL  3

#define FRECUENCIA_PWM 5000
#define RESOLUCION_PWM 8

// *******************************************************************************************
// CONFIGURACIÓN DEL LCD
// *******************************************************************************************

LiquidCrystal lcd(
  LCD_RS,
  LCD_E,
  LCD_D0,
  LCD_D1,
  LCD_D2,
  LCD_D3,
  LCD_D4,
  LCD_D5,
  LCD_D6,
  LCD_D7
);

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
  // -------------------------------
  // Comunicación UART
  // -------------------------------

  Serial.begin(115200);


  // -------------------------------
  // Potenciómetros
  // -------------------------------

  pinMode(POT_ROJO, INPUT);
  pinMode(POT_VERDE, INPUT);


  // -------------------------------
  // Configuración PWM
  // -------------------------------

  ledcSetup(CANAL_ROJO, FRECUENCIA_PWM, RESOLUCION_PWM);
  ledcSetup(CANAL_VERDE, FRECUENCIA_PWM, RESOLUCION_PWM);
  ledcSetup(CANAL_AZUL, FRECUENCIA_PWM, RESOLUCION_PWM);

  ledcAttachPin(LED_ROJO, CANAL_ROJO);
  ledcAttachPin(LED_VERDE, CANAL_VERDE);
  ledcAttachPin(LED_AZUL, CANAL_AZUL);


  // -------------------------------
  // Inicializar LCD
  // -------------------------------

  lcd.begin(16, 2);

  lcd.clear();


  // -------------------------------
  // Texto inicial
  // -------------------------------

  lcd.setCursor(0, 0);
  lcd.print("Rojo: ");

  lcd.setCursor(0, 1);
  lcd.print("Verde: ");


  // -------------------------------
  // Azul apagado por ahora
  // -------------------------------

  ledcWrite(CANAL_AZUL, 255);
}

//LOOP PRINCIPAL 

void loop()
{
// *******************************************************************************************
// LECTURA DE POTENCIÓMETROS
// *******************************************************************************************

lecturaADC_Rojo = analogRead(POT_ROJO);

lecturaADC_Verde = analogRead(POT_VERDE);

// *******************************************************************************************
// CONVERSIÓN DE 12 BITS A 8 BITS
// *******************************************************************************************

valorRojo = lecturaADC_Rojo * 255 / 4095;

valorVerde = lecturaADC_Verde * 255 / 4095;

// *******************************************************************************************
// ACTUALIZACIÓN DEL LED RGB
// *******************************************************************************************

ledcWrite(CANAL_ROJO, valorRojo);

ledcWrite(CANAL_VERDE, valorVerde);

// Azul todavía no se controla
ledcWrite(CANAL_AZUL, 0);

// *******************************************************************************************
// ENVÍO DE DATOS MEDIANTE UART
// *******************************************************************************************

Serial.print("Rojo: ");
Serial.print(valorRojo);

Serial.print(" | Verde: ");
Serial.println(valorVerde);

// *******************************************************************************************
// ACTUALIZAR LCD CON LOS ESTADOS
// *******************************************************************************************

// Mostrar Rojo
lcd.setCursor(6, 0);
lcd.print("   ");

lcd.setCursor(6, 0);
lcd.print(valorRojo);


// Mostrar Verde
lcd.setCursor(7, 1);
lcd.print("   ");

lcd.setCursor(7, 1);
lcd.print(valorVerde);

delay(200);
}