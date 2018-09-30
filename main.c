#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

int wheelCount[4] = {0, 0, 0, 0},
wheelValue[4] = {0, 0, 0 ,0},
check = 0,
subi[4] = {0, 0, 0, 0},
maxWheelCount = 0;

int main(void){
	DDRD=0x00;//колеса
	PORTD=0xff;
	DDRC=0xff;//лампы о неисправностях
	PORTC=0xff;
	_delay_ms(1000);
	PORTC=0x00;

	while(1){
		//определение количества вращений 1 колеса
		if ((PIND &= 0x04) == (1 << PORTD2)){
			wheelValue[0] = 1;
			_delay_ms(10);
		}
		if ( (wheelValue[0] == 1) && ((PIND &= 0x04) != (1 << PORTD2)) ){
			wheelCount[0]++;
			wheelValue[0] = 0;
			_delay_ms(30);
		}
		//определение количества вращений 2 колеса
		if ((PIND &= 0x08) == (1 << PORTD3)){
			wheelValue[1] = 1;
			_delay_ms(10);
		}
		if ( (wheelValue[1] == 1) && ((PIND &= 0x08) != (1 << PORTD3)) ){
			wheelCount[1]++;
			wheelValue[1] = 0;
			_delay_ms(30);
		}
		//определение количества вращений 3 колеса
		if ((PIND &= 0x10) == (1 << PORTD4)){
			wheelValue[2] = 1;
			_delay_ms(10);
		}
		if ( (wheelValue[2] == 1) && ((PIND &= 0x10) != (1 << PORTD4)) ){
			wheelCount[2]++;
			wheelValue[2] = 0;
			_delay_ms(30);
		}
		//определение количества вращений 4 колеса
		if ((PIND &= 0x20) == (1 << PORTD5)){
			wheelValue[3] = 1;
			_delay_ms(10);
		}
		if ( (wheelValue[3] == 1) && ((PIND &= 0x20) != (1 << PORTD5)) ){
			wheelCount[3]++;
			wheelValue[3] = 0;
			_delay_ms(30);
		}
		for(int i = 0; i < 4; i++){
			if(wheelCount[i] >= 4){
				check = 1;
			}
		}
		if(check == 1){
			for(int i = 0; i < 4; i++){
				subi[i] = 4 - wheelCount[i];
				if(subi[i] > 2){
					PORTC |= (1 << i);
					} else {
					PORTC &=~ (1 << i);
				}
			}
			check = 0;
			for(int i = 0; i < 4; i++){
				wheelCount[i] = 0;
				wheelValue[i] = 0;
			}
		}
		
		
	}
}

