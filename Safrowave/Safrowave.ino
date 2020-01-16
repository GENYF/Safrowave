#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>

#define NOTE_AS3 233

const int flame = 4;
const int buzzer = 5;

LiquidCrystal_I2C lcd(0x3F, 16, 2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
	Serial.begin(9600);

	mlx.begin();
	lcd.begin();
}

void loop()
{
	SetTone();
	SetLCD();
	delay(1000);
}

void SetTone() {
	int flamedata = digitalRead(flame);     
	int AmbTemp = mlx.readAmbientTempC();
	int ObjTemp = mlx.readObjectTempC();

	noTone(buzzer);               

	if (flamedata == 0 || AmbTemp > 40 || ObjTemp > 40) {                  
		tone(buzzer, 956, 3000);
	}
	else {                            
		noTone(buzzer);             
	}
}

void SetLCD() {
	double AmbTemp = mlx.readAmbientTempC();
	double ObjTemp = mlx.readObjectTempC();

	lcd.clear();
	lcd.backlight();

	lcd.setCursor(0, 0);
	lcd.print("Ambient = ");
	lcd.print(AmbTemp);
	lcd.println("C");

	lcd.setCursor(0, 1);
	lcd.print("Object = ");
	lcd.print(ObjTemp);
	lcd.print("C");
}