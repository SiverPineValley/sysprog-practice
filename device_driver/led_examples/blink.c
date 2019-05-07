#include <wiringPi.h>

#define GPIO18       1

int main(void)
{
    wiringPiSetup();
    pinMode(GPIO18, OUTPUT);
    for(;;)
    {
        digitalWrite(GPIO18, HIGH);  delay(500);
        digitalWrite(GPIO18, LOW);   delay(500);
        return 0;
    }

}
