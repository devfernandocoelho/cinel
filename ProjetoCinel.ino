//#include <usiTwiSlave.h>
//#include <TinyWireS.h>
//#include <USI_TWI_Master.h>
//#include <TinyWireM.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define inv 2 //pino para a inversao de marcha
#define semaf1verd 53//Pinos Sinais
#define semaf1verm 52
#define semaf1amar 51
#define semaf2verd 50
#define semaf2verm 49
#define semaf2amar 48
#define semaf3verd 47
#define semaf3verm 46
#define semaf3amar 45
#define semaf4verd 44
#define semaf4verm 43
#define semaf4amar 42

#define Segm1 31
#define Segm2 30
#define Segm3 29
#define Segm4 28

#define reed A0//Sensors
#define reedPn A1//SensorsPn
#define reedLdr A2//Sensor LDR
#define reedIr A3//SensorIR

#define PN_Led1 3//LEDS Passagem  Nivel
#define PN_Led2 4

#define ldrOut 7//LDR Iluminação

#define PN_Buzz 8

#define agulha11 94
#define agulha12 40
#define agulha21 94
#define agulha22  134

//LCD
LiquidCrystal_I2C lcd(0x3F, 20, 4);  // set the LCD address to 0x3f for a 20 chars and 4 line display

//Passagem de nivel
bool PnStatus = 0;

int pnled1Status = HIGH;
int pnled2Status = HIGH;
int pnbuzzStatus = LOW;





unsigned long OldMillisLed1 = 325;//Memórias temporarias
unsigned long OldMillisLed2 = 0;
unsigned long OldMillisBuzz = 0;
unsigned long OldMillisInv = 1000;

const long Led1interval = 650;//blink rate
const long Led2interval = 650;//blink rate
const long Buzzinterval = 325;//buzzer rate
const long Invinterval = 1000;//duracao impulso inversao de marcha



//Servos
Servo servoPn1;
Servo servoPn2;
Servo servoAgulha1;
Servo servoAgulha2;

//Sensors
boolean Sensor1 = 0;//Pos1
boolean Sensor2 = 0;//Sinal1_FreePn
boolean Sensor3 = 0;//Pos2
boolean Sensor4 = 0;//Sinal2
boolean Sensor5 = 0;//Pos3
boolean Sensor6 = 0;//Sinal3
boolean Sensor7 = 0;//Pos4
boolean Sensor8 = 0;//Sinal4
boolean Sensor9 = 0;//Pn fechada
boolean Sensor10 = 0;//IR sem obstáculos
int reedVal = 0;//Recebe a leitura dos sensores(A0)
int reedPnVal = 0;//Recebe a leitura dos sensores/barreiras PN
int reedIrVal = 0;//recebe a leitura dos sensores IR



int estado = 0;
int time = 0;
int ciclo1 = 0;//1º ciclo do programa
int ldr = 0;

byte x = 0;//AttinyMaster 


void setup()
	{
	Serial.begin(9600);
	Wire.begin(); // join i2c bus (address optional for master)

	pinMode(inv, OUTPUT);
	pinMode(PN_Led1, OUTPUT);
	pinMode(PN_Led2, OUTPUT);
	pinMode(PN_Buzz, OUTPUT);
	pinMode(semaf1verd, OUTPUT);
	pinMode(semaf1verm, OUTPUT);
	pinMode(semaf1amar, OUTPUT);
	pinMode(semaf2verd, OUTPUT);
	pinMode(semaf2verm, OUTPUT);
	pinMode(semaf2amar, OUTPUT);
	pinMode(semaf3verd, OUTPUT);
	pinMode(semaf3verm, OUTPUT);
	pinMode(semaf3amar, OUTPUT);
	pinMode(semaf4verd, OUTPUT);
	pinMode(semaf4verm, OUTPUT);
	pinMode(semaf4amar, OUTPUT);
	pinMode(Segm1, OUTPUT);
	pinMode(Segm2, OUTPUT);
	pinMode(Segm3, OUTPUT);
	pinMode(Segm4, OUTPUT);
	pinMode(ldrOut, OUTPUT);

	pinMode(reed, INPUT);
	pinMode(reedPn, INPUT);
	pinMode(reedIr, INPUT);
	pinMode(reedLdr, INPUT);


	//attachServos	
	servoPn1.attach(10);
	servoPn2.attach(11);
	servoAgulha1.attach(12);
	servoAgulha2.attach(13);


	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 5;
	TIMSK1 = 1;
	TCNT1 = 65535 - 15625;
	interrupts();

	time = 3;

	}


ISR(TIMER1_OVF_vect)
	{
	TCNT1 = 65535 - 15625;
	if (time > 0) time--;
	Serial.println(estado);
	}

void loop()
	{
	unsigned long CurrentMillis = millis();
	sensores(reedVal, reedPnVal, reedIrVal);//faz a leitura dos sensores


	ldr = analogRead(reedLdr);

	reedVal = analogRead(reed);
	reedPnVal = analogRead(reedPn);
	reedIrVal = analogRead(reedIr);




	if (ldr <= 480)
		{
		digitalWrite(ldrOut, HIGH);

		}
	else digitalWrite(ldrOut, LOW);

	pnled1Status = !pnled2Status;

	if ((Sensor9 == 1) && (Sensor10 == 0))
		{
		PnStatus = 1;
		}
	else PnStatus = 0;

	if (PnStatus == 1 && ciclo1 == 1)
		{

		if (CurrentMillis - OldMillisLed1 >= Led1interval)
			{
			OldMillisLed1 = CurrentMillis;
			pnled1Status = (pnled1Status == HIGH) ? LOW : HIGH;
			digitalWrite(PN_Led1, pnled1Status);
			}

		if (CurrentMillis - OldMillisLed2 >= Led2interval)
			{
			OldMillisLed2 = CurrentMillis;
			pnled2Status = (pnled2Status == HIGH) ? LOW : HIGH;
			digitalWrite(PN_Led2, pnled2Status);
			}

		if (CurrentMillis - OldMillisBuzz >= Buzzinterval)
			{
			OldMillisBuzz = CurrentMillis;
			pnbuzzStatus = (pnbuzzStatus == HIGH) ? LOW : HIGH;
			analogWrite(PN_Buzz, pnbuzzStatus);
			}
		}




	if (time == 0)
		{
		if (estado == 0 && time == 0)
			{
			segmentoOff(1);
			segmentoOff(2);
			segmentoOff(3);
			segmentoOff(4);
			lcd.clear();
			Sinaliz_G();
			time = 3;
			estado = 1;
			}
		else if (estado == 1 && time == 0)
			{
			BarreiraPnOn();


			if (PnStatus == 1)
				{
				lcdInf(1);
				Agulha1Via1();
				
				Agulha2Via1();
				invmarcha();

				Sinaliz_A();
				segmentoOn(1);
				segmentoOn(2);
				segmentoOn(3);
				segmentoOn(4);
				estado = 2;

				}

			}
		else if (estado == 2)
			{
			if (Sensor2 == 1)
				{
				BarreiraPnOff();
				Sinaliz_D();
				}
			if (Sensor3 == 1 && estado == 2)
				{

				segmentoOn(1);
				segmentoOff(2);
				segmentoOn(3);
				segmentoOn(4);
				lcdInf(2);
				time = 5;
				//Sinaliz_B();
				estado = 3;
				}
			}
		else if (estado == 3)
			{
			delay(1000);
			Sinaliz_B();
			segmentoOn(1);
			segmentoOn(2);
			segmentoOn(3);
			segmentoOn(4);

			estado = 4;



			}
		else if (estado == 4)
			{
			if (Sensor4 == 1)
				{
				Sinaliz_E();
				
				}

			if (Sensor6 == 1)
				{

				segmentoOff(1);
				segmentoOff(2);
				segmentoOff(3);
				segmentoOff(4);
				lcdInf(3);
				Agulha2Via2();
				
				invmarcha();
				Sinaliz_C();
				estado = 5;
				
				}
			}
		else if (estado == 5)
			{
			
			delay(1000);
			estado = 6;
			}
		else if (estado == 6)
			{
			
			segmentoOn(1);
			segmentoOn(2);
			segmentoOn(3);
			segmentoOn(4);


			estado = 7;

			}
		else if (estado == 7)
			{
			if (Sensor5 == 1)
				{
				Sinaliz_G();
				}
			if (Sensor7 == 1)
				{
				lcdInf(4);
				segmentoOff(1);
				segmentoOff(2);
				segmentoOff(3);
				segmentoOff(4);
				estado = 8;
				}
			}
		else if (estado == 8)
			{
			BarreiraPnOn();


			if (PnStatus == 1)
				{
				Agulha1Via2();
				//Sinaliz_D();
				time = 4;
				estado = 9;

				}
			}
		else if (estado == 9 && time == 0)
			{
			delay(1000);
			Sinaliz_D();
			segmentoOn(1);
			segmentoOff(2);
			segmentoOn(3);
			segmentoOn(4);
			estado = 10;
			}
		else if (estado == 10)
			{
			if (Sensor8 == 1)
				{
				Sinaliz_F();
				}
			if (Sensor1 == 1)
				{
				estado = 20;
				}
			}
		else if (estado == 20)
			{
			if (Sensor1 == 1)
				{
				BarreiraPnOff();
				estado = 0;
				time = 0;
				}
			}
		}

	ciclo1 = 1;

	}
