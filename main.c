#include <avr/io.h>
#include <avr/iom16.h>
#include <stdbool.h> //библиотека дл€ bool
#define F_CPU 8000000UL //частота задержки
#include <util/delay.h> //библиотека задержки
int lose(void),
	check(void);//объ€вление глобальных переменных
//------------------------------------
//массив рандома
//------------------------------------
int lamps[3][8] = {0x01 ,0x08, 0x02, 0x80, 0x04, 0x40, 0x10, 0x20,
				   0x02, 0x80, 0x20, 0x04, 0x01, 0x40, 0x10, 0x08,
				   0x10, 0x40, 0x08, 0x01, 0x80, 0x02, 0x20, 0x04};
int j = 0; //строка lamps
bool win = false;
//------------------------------------
//главна€ функци€
//------------------------------------
int main(void){	
	DDRA = 0x00;  //кнопки
	DDRB = 0xff;  //лампы
	PORTB = 0x00; //отключаем все лампы
//------------------------------------
//проверка во врем€ горени€ светодиода
//------------------------------------
	while(1){
		check();
		PORTB = 0x00;
		_delay_ms(1000);
		if(win){
			continue;
			} else {
			break;
		}
	}
	lose();
	return 0;
}
//------------------------------------
//проверка нажати€ (ту ли нажал)
//------------------------------------
int check(void){
	int timer = 100;
	for(int i = 0; i < 7; i++){
		PORTB = lamps[j][i];
		while(timer){
			_delay_ms(10);
			if(PINA){
				if(PINA != lamps[j][i]){
					win = false;
					break;
					} else {
					win = true;
					break;
				}
			}
			timer--;
		}
		j++;
		if (j==3){
			j=0;
		}
	}
	return 0;
}
//------------------------------------
//проигрыш
//------------------------------------
int lose(void){
	while(1){
		PORTB = 0xff;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
	}
}