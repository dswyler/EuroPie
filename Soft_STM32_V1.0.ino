#include <libmaple/usart.h>

#define C9 PB8
#define C8 PB7
#define C7 PB6
#define C6 PB5
#define C5 PB4

#define C4 PA8
#define C3 PB15
#define C2 PB14
#define C1 PB13
#define C0 PB12

#define F9 PA0
#define F8 PA1
#define F7 PA2
#define F6 PA3
#define F5 PA4
#define F4 PA5
#define F3 PA6
#define F2 PA7
#define F1 PB0
#define F0 PB1

#define B1 PB9
#define B2 PB11
#define B3 PB10
#define B4 PA12
#define B5 PA11

#define LED PC13

#define RS485_TX_DRV PA15
//#define RS485_RX_DRV PB3

#define SERIAL_USE  Serial1

int bitVal;
String stringBit;
String stringBinary;
long binaryNumber;
int decimalNumber;


// ---------------------------------------------------------------------------------
// SETUP
// ---------------------------------------------------------------------------------
void setup() {
  SERIAL_USE.begin(962100);
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  // RS485 TX Deshabilitado
  pinMode(RS485_TX_DRV, OUTPUT);
  digitalWrite(RS485_TX_DRV, LOW);
    
  // RS485 RX Habilitado
  //pinMode(RS485_RX_DRV, OUTPUT);
  //digitalWrite(RS485_RX_DRV, LOW);

  // Setear columnas
  pinMode(C0, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(C5, OUTPUT);
  pinMode(C6, OUTPUT);
  pinMode(C7, OUTPUT);
  pinMode(C8, OUTPUT);
  pinMode(C9, OUTPUT);

  pinMode(B0, INPUT);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);

  digitalWrite(C0, LOW);
  digitalWrite(C1, LOW);
  digitalWrite(C2, LOW);
  digitalWrite(C3, LOW);
  digitalWrite(C4, LOW);
  digitalWrite(C5, LOW);
  digitalWrite(C6, LOW);
  digitalWrite(C7, LOW);
  digitalWrite(C8, LOW);
  digitalWrite(C9, LOW);

    bitVal = digitalRead(B1);
  stringBit = String(bitVal);
  stringBinary = stringBinary + stringBit;
  binaryNumber = stringBinary.toInt();
    bitVal = digitalRead(B2);
  stringBit = String(bitVal);
  stringBinary = stringBinary + stringBit;
  binaryNumber = stringBinary.toInt();
    bitVal = digitalRead(B3);
  stringBit = String(bitVal);
  stringBinary = stringBinary + stringBit;
  binaryNumber = stringBinary.toInt();
    bitVal = digitalRead(B4);
  stringBit = String(bitVal);
  stringBinary = stringBinary + stringBit;
  binaryNumber = stringBinary.toInt();
    /*bitVal = digitalRead(B5);
  stringBit = String(bitVal);
  stringBinary = stringBinary + stringBit;
  binaryNumber = stringBinary.toInt();*/

  decimalNumber = convertBinaryToDecimal(binaryNumber);

}
// ---------------------------------------------------------------------------------

/*
void printN(int i){
  if( i < 1000 )
    SERIAL_USE.print(' ');
  if( i < 100 )
    SERIAL_USE.print(' ');
  if( i < 10 )
    SERIAL_USE.print(' ');
  SERIAL_USE.print(i);
}
*/
/*
void printRow(int *arrayRow){
  int i;
  int n;
  for(i=0; i<10; i++){
    n = arrayRow[i];
    if( n < 1000 )
      SERIAL_USE.print('0');
    if( n < 100 )
      SERIAL_USE.print('0');
    if( n < 10 )
      SERIAL_USE.print('0');
    SERIAL_USE.print(n);
    SERIAL_USE.print(' ');   
  }
  SERIAL_USE.println();
}
*/

// ---------------------------------------------------------------------------------
// Digitalizar una fila completa
// ---------------------------------------------------------------------------------
void captureRow(int *arrayRow){
  arrayRow[0] = analogRead(F0);
  arrayRow[1] = analogRead(F1);
  arrayRow[2] = analogRead(F2);
  arrayRow[3] = analogRead(F3);
  arrayRow[4] = analogRead(F4);
  arrayRow[5] = analogRead(F5);
  arrayRow[6] = analogRead(F6);
  arrayRow[7] = analogRead(F7);
  arrayRow[8] = analogRead(F8);
  arrayRow[9] = analogRead(F9);  
}
// ---------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------
void sendRow(int *arrayRow, int n){
  SERIAL_USE.write( byte((arrayRow[0] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[1] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[2] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[3] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[4] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[5] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[6] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[7] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[8] + n*100) >> 4) );
  SERIAL_USE.write( byte((arrayRow[9] + n*100) >> 4) );

  /*SERIAL_USE.write(byte(arrayRow[1] >> 4));
  SERIAL_USE.write(byte(arrayRow[2] >> 4));
  SERIAL_USE.write(byte(arrayRow[3] >> 4));
  SERIAL_USE.write(byte(arrayRow[4] >> 4));
  SERIAL_USE.write(byte(arrayRow[5] >> 4));
  SERIAL_USE.write(byte(arrayRow[6] >> 4));
  SERIAL_USE.write(byte(arrayRow[7] >> 4));
  SERIAL_USE.write(byte(arrayRow[8] >> 4));
  SERIAL_USE.write(byte(arrayRow[9] >> 4));*/
}
// ---------------------------------------------------------------------------------

int row0[10];
int row1[10];
int row2[10];
int row3[10];
int row4[10];
int row5[10];
int row6[10];
int row7[10];
int row8[10];
int row9[10];

// ---------------------------------------------------------------------------------
// LOOP
// ------------------------------------------------------------------------------
void loop() {
  unsigned long t0, t1;

  // esperar disparo
  while( SERIAL_USE.available() == 0 );   

  while(SERIAL_USE.available()){
    byte a = SERIAL_USE.read();
  }

  // digitalizar panel
  
  // Activar columna
  digitalWrite(C9, LOW);
  digitalWrite(C0, HIGH);
  // leer filas
  captureRow(row0);

  // Activar columna
  digitalWrite(C0, LOW);
  digitalWrite(C1, HIGH);
  // leer filas
  captureRow(row1);

  // Activar columna
  digitalWrite(C1, LOW);
  digitalWrite(C2, HIGH);
  // leer filas
  captureRow(row2);

  // Activar columna
  digitalWrite(C2, LOW);
  digitalWrite(C3, HIGH);
  // leer filas
  captureRow(row3);

  // Activar columna
  digitalWrite(C3, LOW);
  digitalWrite(C4, HIGH);
  // leer filas
  captureRow(row4);

  // Activar columna
  digitalWrite(C4, LOW);
  digitalWrite(C5, HIGH);
  // leer filas
  captureRow(row5);

  // Activar columna
  digitalWrite(C5, LOW);
  digitalWrite(C6, HIGH);
  // leer filas
  captureRow(row6);

  // Activar columna
  digitalWrite(C6, LOW);
  digitalWrite(C7, HIGH);
  // leer filas
  captureRow(row7);

  // Activar columna
  digitalWrite(C7, LOW);
  digitalWrite(C8, HIGH);
  // leer filas
  captureRow(row8);

  // Activar columna
  digitalWrite(C8, LOW);
  digitalWrite(C9, HIGH);
  // leer filas
  captureRow(row9);

  // timer 
  t0 = micros();

  // esperar que se cumpla el tiempo para transmitir
  while(1){
    t1 = micros();  
    if( (t1-t0) >= 1250*decimalNumber ) // (1250us de transmision para cada plataforma)
      break;
  }

  // enviar

  // RS485 RX Deshabilitado
  //digitalWrite(RS485_RX_DRV, HIGH);
  
  // RS485 TX Habilitado
  digitalWrite(RS485_TX_DRV, HIGH);
  digitalWrite(LED, LOW);
      
  for( int n=0; n<1; n++){
    sendRow(row0, n);
    sendRow(row1, n);
    sendRow(row2, n);
    sendRow(row3, n);
    sendRow(row4, n);
    sendRow(row5, n);
    sendRow(row6, n);
    sendRow(row7, n);
    sendRow(row8, n);
    sendRow(row9, n);
  }

  // Esperar finalizacion de TX
  usart_reg_map *regs = USART1->regs;
  while ( !(regs->SR & USART_SR_TC) ); // Wait for Transmission Complete to set

  //delay(1);
  delayMicroseconds(20);

  // RS485 TX Deshabilitado
  digitalWrite(RS485_TX_DRV, LOW);
  digitalWrite(LED, HIGH);

  // esperar que se cumpla el tiempo para recibir
  /*
  while(1){
    t1 = micros();  
    if( (t1-t0) >= 20000 )
      break;
  }
  */

  // RS485 RX Habilitado
  //digitalWrite(RS485_RX_DRV, LOW);

  // limpiar buffer de RX
  while(SERIAL_USE.available()){
    byte a = SERIAL_USE.read();
  }


}
