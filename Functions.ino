


void invmarcha()
	{


	for (int i = 0; i < 5000; i++)
		{
		digitalWrite(Segm1, HIGH);
		digitalWrite(Segm2, HIGH);
		digitalWrite(Segm3, HIGH);
		digitalWrite(Segm4, HIGH);
		digitalWrite(inv, 1);
		}

	digitalWrite(inv, 0);
	delay(1000);
	digitalWrite(Segm1, LOW);
	digitalWrite(Segm2, LOW);
	digitalWrite(Segm3, LOW);
	digitalWrite(Segm4, LOW);


	}
void BarreiraPnOn()
	{
	int pnOn = 8;
	servoPn1.write(pnOn);
	servoPn2.write(pnOn);

	}
void BarreiraPnOff()
	{
	int pnOff = 93;
	servoPn1.write(pnOff);
	servoPn2.write(pnOff);

	analogWrite(PN_Buzz, LOW);
	digitalWrite(PN_Led1, LOW);
	digitalWrite(PN_Led2, LOW);
	}
void Agulha1Via1()
	{
	sendTiny1(1);
	servoAgulha1.write(agulha11);
	}
void Agulha1Via2()
	{
	sendTiny1(2);
	servoAgulha1.write(agulha12);
	}
void Agulha2Via1()
	{
	sendTiny2(1);
	servoAgulha2.write(agulha21);
	}
void Agulha2Via2()
	{
	sendTiny2(2);
	servoAgulha2.write(agulha22);
	}
void Sinaliz_A()
	{
	digitalWrite(semaf1verd, 1);
	digitalWrite(semaf1verm, 0);
	digitalWrite(semaf1amar, 0);
	digitalWrite(semaf2verd, 0);
	digitalWrite(semaf2verm, 1);
	digitalWrite(semaf2amar, 0);
	digitalWrite(semaf3verd, 0);
	digitalWrite(semaf3verm, 1);
	digitalWrite(semaf3amar, 0);
	digitalWrite(semaf4verd, 0);
	digitalWrite(semaf4verm, 1);
	digitalWrite(semaf4amar, 0);



	}
void Sinaliz_B()
	{
	digitalWrite(semaf1verd, 0);
	digitalWrite(semaf1verm, 1);
	digitalWrite(semaf1amar, 0);
	digitalWrite(semaf2verd, 1);
	digitalWrite(semaf2verm, 0);
	digitalWrite(semaf2amar, 0);
	digitalWrite(semaf3verd, 0);
	digitalWrite(semaf3verm, 1);
	digitalWrite(semaf3amar, 0);
	digitalWrite(semaf4verd, 0);
	digitalWrite(semaf4verm, 1);
	digitalWrite(semaf4amar, 0);
	}
void Sinaliz_C()
	{
	digitalWrite(semaf1verd, 0);
	digitalWrite(semaf1verm, 1);
	digitalWrite(semaf1amar, 0);
	digitalWrite(semaf2verd, 0);
	digitalWrite(semaf2verm, 1);
	digitalWrite(semaf2amar, 0);
	digitalWrite(semaf3verd, 1);
	digitalWrite(semaf3verm, 0);
	digitalWrite(semaf3amar, 0);
	digitalWrite(semaf4verd, 0);
	digitalWrite(semaf4verm, 1);
	digitalWrite(semaf4amar, 0);
	}
void Sinaliz_D()
	{
	digitalWrite(semaf1verd, 0);
	digitalWrite(semaf1verm, 1);
	digitalWrite(semaf1amar, 0);
	digitalWrite(semaf2verd, 0);
	digitalWrite(semaf2verm, 1);
	digitalWrite(semaf2amar, 0);
	digitalWrite(semaf3verd, 0);
	digitalWrite(semaf3verm, 1);
	digitalWrite(semaf3amar, 0);
	digitalWrite(semaf4verd, 1);
	digitalWrite(semaf4verm, 0);
	digitalWrite(semaf4amar, 0);
	}
void Sinaliz_E()

	{
	digitalWrite(semaf1verd, 0);
	digitalWrite(semaf1verm, 0);
	digitalWrite(semaf1amar, 1);
	digitalWrite(semaf2verd, 0);
	digitalWrite(semaf2verm, 1);
	digitalWrite(semaf2amar, 0);
	digitalWrite(semaf3verd, 0);
	digitalWrite(semaf3verm, 1);
	digitalWrite(semaf3amar, 0);
	digitalWrite(semaf4verd, 0);
	digitalWrite(semaf4verm, 1);
	digitalWrite(semaf4amar, 0);
	}
void Sinaliz_F()
	{

	digitalWrite(semaf1verd, 0);
	digitalWrite(semaf1verm, 1);
	digitalWrite(semaf1amar, 0);
	digitalWrite(semaf2verd, 1);
	digitalWrite(semaf2verm, 0);
	digitalWrite(semaf2amar, 0);
	digitalWrite(semaf3verd, 0);
	digitalWrite(semaf3verm, 0);
	digitalWrite(semaf3amar, 1);
	digitalWrite(semaf4verd, 0);
	digitalWrite(semaf4verm, 1);
	digitalWrite(semaf4amar, 0);
	}
void Sinaliz_G()
	{
	digitalWrite(semaf1verd, 0);
	digitalWrite(semaf1verm, 1);
	digitalWrite(semaf1amar, 0);
	digitalWrite(semaf2verd, 0);
	digitalWrite(semaf2verm, 1);
	digitalWrite(semaf2amar, 0);
	digitalWrite(semaf3verd, 0);
	digitalWrite(semaf3verm, 1);
	digitalWrite(semaf3amar, 0);
	digitalWrite(semaf4verd, 0);
	digitalWrite(semaf4verm, 1);
	digitalWrite(semaf4amar, 0);
	}
void segmentoOn(int nr1)
	{
	switch (nr1)
		{
		case 1: digitalWrite(Segm1, LOW);
		case 2: digitalWrite(Segm2, LOW);
		case 3: digitalWrite(Segm3, LOW);
		case 4: digitalWrite(Segm4, LOW);
		}
	}
void segmentoOff(int nr2)
	{
	switch (nr2)
		{
		case 1: digitalWrite(Segm1, HIGH);
		case 2: digitalWrite(Segm2, HIGH);
		case 3: digitalWrite(Segm3, HIGH);
		case 4: digitalWrite(Segm4, HIGH);
		}
	}
void sensores(int _reedVal, int _reedPnVal, int _reedIrVal)
	{
	if (_reedVal > 75 && _reedVal < 125) Sensor1 = 1;
	else Sensor1 = 0;
	if (_reedVal > 150 && _reedVal < 230) Sensor2 = 1;
	else Sensor2 = 0;
	if (_reedVal > 430 && _reedVal < 500) Sensor3 = 1;
	else Sensor3 = 0;
	if (_reedVal > 530 && _reedVal < 600) Sensor4 = 1;
	else Sensor4 = 0;
	if (_reedVal > 630 && _reedVal < 750) Sensor5 = 1;
	else Sensor5 = 0;
	if (_reedVal > 790 && _reedVal < 900) Sensor6 = 1;
	else Sensor6 = 0;
	if (_reedVal > 320 && _reedVal < 400) Sensor7 = 1;
	else Sensor7 = 0;
	if (_reedVal > 250 && _reedVal < 300) Sensor8 = 1;
	else Sensor8 = 0;
	if (_reedPnVal > 975 && _reedPnVal < 1100) Sensor9 = 1;
	else Sensor9 = 0;
	if (_reedIrVal > 400) Sensor10 = 1;
	else Sensor10 = 0;
	}
void lcdInf(int _msg)
	{
	if (_msg == 1)
		{
		//colocar codigo a limpar o display no inicio de cada segmento
		lcd.init();
		lcd.clear();
		lcd.backlight();


		lcd.setCursor(0, 0);

		lcd.print("Vai entrar na linha1");
		lcd.setCursor(0, 1);

		lcd.print("o comboio destinado");
		lcd.setCursor(1, 2);

		lcd.print("a Braga as 20:30h");
		lcd.setCursor(0, 3);

		lcd.print("atrasado 20 minutos");

		}
	else if (_msg == 2)
		{
		lcd.clear();
		lcd.backlight();
		lcd.setCursor(0, 0);

		lcd.print("O comboio destinado");
		lcd.setCursor(1, 1);

		lcd.print("a Braga vai partir");
		lcd.setCursor(0, 2);

		lcd.print("dentro de 2 minutos");
		lcd.setCursor(0, 3);
		lcd.print("");

		}
	else if (_msg == 3)
		{
		lcd.clear();
		lcd.backlight();
		lcd.setCursor(0, 0);

		lcd.print("Vai entrar na linha2");
		lcd.setCursor(0, 1);

		lcd.print("o comboio destinado");
		lcd.setCursor(2, 2);

		lcd.print("a Porto-Campanha");
		lcd.setCursor(4, 3);

		lcd.print("pelas 23:00h");

		}
	else if (_msg == 4)
		{
		lcd.clear();
		lcd.backlight();
		lcd.setCursor(0, 0);

		lcd.print("O comboio destinado");
		lcd.setCursor(2, 1);

		lcd.print("a Porto-Campanha");
		lcd.setCursor(3, 2);

		lcd.print("vai partir as");
		lcd.setCursor(7, 3);

		lcd.print("23:10h");

		}

	}
void sendTiny1(byte valor)
	{
	Wire.beginTransmission(0x70); // transmit to device
	Wire.write(valor);        // sends byte
	Wire.endTransmission();    // stop transmitting
	}
void sendTiny2(byte valor)
	{
	Wire.beginTransmission(0x72); // transmit to device
	Wire.write(valor);        // sends byte
	Wire.endTransmission();    // stop transmitting
	}
