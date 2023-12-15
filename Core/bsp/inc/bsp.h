#ifndef __BSP_H_
#define __BSP_H_
#include "main.h"

//core
#include "adc.h"
#include "gpio.h"
#include "iwdg.h"
#include "tim.h"

//bsp
#include "bsp_ctl.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_ntc.h"
#include "bsp_tm1650.h"
#include "bsp_smg.h"
#include "bsp_delay.h"
#include "bsp_relay.h"


typedef enum{

    fun_key =0x01,
	confirm_short_key,
	confirm_long_key


}key_id_state;


typedef enum{

    relay_a = 0x01,
	relay_b ,
	relay_c ,
	relay_temp 

}relay_id_state;

typedef enum{

    relay_fan_led_on =0x01,
	relay_tape_led_on,
	relay_kill_led_on,
	relay_keep_temp_led_on,
	
	
}reelay_led_state;


typedef struct{

   uint8_t key_fun;
   uint8_t key_short_confirm_flag;
   uint8_t key_long_confirm_flag;
   uint8_t set_keep_temp;
   uint8_t set_keep_tmep_value;
   
   uint8_t gTimer_pro_feed_dog;
   uint8_t gTimer_pro_key;
   uint8_t gTimer_pro_disp;


}main_prcess_t;


extern main_prcess_t pro_t;


void bsp_Idle(void);
void Key_Handler(uint8_t key_value);

void Main_Process(void);



#endif 

