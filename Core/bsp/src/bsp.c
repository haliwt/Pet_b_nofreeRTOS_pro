#include "bsp.h"

main_prcess_t pro_t;

uint8_t relay_id_led;

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- 喂狗 */
    if(pro_t.gTimer_pro_feed_dog > 2){
	   pro_t.gTimer_pro_feed_dog=0;
	   Feed_Dog();

    }
		
	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */
	
    /* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();
	
	/* 例如 uIP 协议，可以插入uip轮询函数 */
	//TOUCH_CapScan();
	


}
/*
*********************************************************************************************************
*	函 数 名: Key_Handler(uint8_t key_value)
*	功能说明: 中间层 
*			 
*	形    参: 输入按键的键值
*	返 回 值: 无
*********************************************************************************************************
*/
void Key_Handler(uint8_t key_value)
{
  switch(key_value){

     case fun_key:  //fun key 
         pro_t.key_fun++;
         switch(pro_t.key_fun){

		    case relay_a:

		       relay_id_led = relay_fan_led_on;
		       tpd_t.gTimer_select_fun=0;
			   

		    break;
		 
		    case relay_b:
				relay_id_led = relay_tape_led_on;
				tpd_t.gTimer_select_fun=0;
				

		    break;

			case relay_c:
				relay_id_led = relay_kill_led_on;
				tpd_t.gTimer_select_fun=0;
				
		    break;

			case relay_d: //keep temperature value
			 relay_id_led = relay_keep_temp_led_on;
			 tpd_t.gTimer_select_fun=0;
			

			pro_t.key_fun =0;

		    break;

			default:

			break;

			
		 

		 }
    
     break;

	 case confirm_short_key: // confirm key
	    pro_t.key_short_confirm_flag =1;

	 break;

	 case confirm_long_key: //confirm long by pressed 

	    pro_t.key_long_confirm_flag =1;

	 break;
  
  }


}
/*
*********************************************************************************************************
*	函 数 名: void Main_Process(void)
*	功能说明: App 层 
*			 
*	形    参: 输入按键的键值
*	返 回 值: 无
*********************************************************************************************************
*/
void Main_Process(void)
{

 
   switch(relay_id_led){

    case relay_fan_led_on:

       if(tpd_t.gTimer_select_fun < 6 &&  pro_t.key_short_confirm_flag ==0){
        	Fan_Led_Flicker();
			fan_led_on=0;
       }
       else{
	   	  tpd_t.gTimer_select_fun =10;
	
		 
           if(tpd_t.read_key_flag ==0 &&  pro_t.key_short_confirm_flag ==1){
				tpd_t.relay_fan_flag =1;
				pro_t.key_short_confirm_flag =0;
			    
			}
			else if(pro_t.key_short_confirm_flag ==1){

				tpd_t.relay_fan_flag =0;
				pro_t.key_short_confirm_flag =0;
	
			}
			else{
		  	   if(tpd_t.relay_fan_flag ==1){
					FAN_LED_ON();
					RELAY_FAN_SetHigh()	 ;
			   }
			   else{
                  FAN_LED_OFF();
		          RELAY_FAN_SetLow()	;

			   }
	         
	        }

		}

     

		 if(tpd_t.relay_tape_flag ==1){
		 	 TAPE_LED_ON();
			 RELAY_TAPE_SetHigh();
			 
		 }
		 else{
		 	TAPE_LED_OFF();
            RELAY_TAPE_SetLow();

		 }

		 
	     if(tpd_t.relay_kill_flag ==1){
		 	 KILL_LED_ON();
			 RELAY_KILL_SetHigh();
	        
		 }
		 else{
		 	 KILL_LED_OFF();
			 RELAY_KILL_SetLow();
	
	
		 }

		 
	    if(tpd_t.relay_keep_temp_flag ==1){
			KEEP_HEAT_LED_ON();
	        RELAY_KEEP_TEMP_SetHigh();
		}
		else{
	        KEEP_HEAT_LED_OFF();
	        RELAY_KEEP_TEMP_SetLow();
	
		}


    break;

	case relay_tape_led_on:

		if(tpd_t.gTimer_select_fun < 6 && pro_t.key_short_confirm_flag ==0){
			Tape_Led_Flicker();
		}
		else{

             tpd_t.gTimer_select_fun =10;
	
             if(tpd_t.read_key_flag ==0 &&  pro_t.key_short_confirm_flag ==1){
			   		tpd_t.relay_tape_flag =1;
					pro_t.key_short_confirm_flag =0;
			   }
			   else if(pro_t.key_short_confirm_flag ==1){

				   tpd_t.relay_tape_flag =0;
				   pro_t.key_short_confirm_flag =0;


			   }
			   else{

					if(tpd_t.relay_tape_flag ==1){
						TAPE_LED_ON();
			 			RELAY_TAPE_SetHigh();

					}
					else{
					TAPE_LED_OFF();
            		RELAY_TAPE_SetLow();


					}


			   }
			
		}
		



	    //

         if(tpd_t.relay_fan_flag == 1){

			 FAN_LED_ON();//FAN_LED_ON();
					 
		     RELAY_FAN_SetHigh()	 ;

         }
         else{
		   FAN_LED_OFF();//FAN_LED_OFF();
		   RELAY_FAN_SetLow()	;


		 }
	
//         if(tpd_t.relay_tape_flag ==1){
//		 	 TAPE_LED_ON();
//			 RELAY_TAPE_SetHigh();
//			 
//		 }
//		 else{
//		 	TAPE_LED_OFF();
//            RELAY_TAPE_SetLow();
//
//		 }

		 
	     if(tpd_t.relay_kill_flag ==1){
		 	 KILL_LED_ON();
			 RELAY_KILL_SetHigh();
	        
		 }
		 else{
		 	 KILL_LED_OFF();
			 RELAY_KILL_SetLow();
	
	
		 }

		 
	    if(tpd_t.relay_keep_temp_flag ==1){
			KEEP_HEAT_LED_ON();
	        RELAY_KEEP_TEMP_SetHigh();
		}
		else{
	        KEEP_HEAT_LED_OFF();
	        RELAY_KEEP_TEMP_SetLow();
	
		}


    break;

	case relay_kill_led_on:

		//STERILIZATION
		if(tpd_t.gTimer_select_fun < 6 && pro_t.key_short_confirm_flag ==0 ){
			Sterilization_Led_Filcker();
		}
		else{
			 tpd_t.gTimer_select_fun =10;
			 
			if(tpd_t.read_key_flag ==0 &&  pro_t.key_short_confirm_flag ==1){
				tpd_t.relay_kill_flag =1;
				pro_t.key_short_confirm_flag =0;
			}
			else if(pro_t.key_short_confirm_flag ==1){

				tpd_t.relay_kill_flag =0;
				pro_t.key_short_confirm_flag =0;

           }
		   else{

				if(tpd_t.relay_kill_flag ==1){
				KILL_LED_ON();
				RELAY_KILL_SetHigh();

				}
				else{
				KILL_LED_OFF();
				RELAY_KILL_SetLow();


				}
			}

		}
  
		 
        if(tpd_t.relay_fan_flag == 1){

			 FAN_LED_ON();//FAN_LED_ON();
					 
		     RELAY_FAN_SetHigh()	 ;

         }
         else{
		   FAN_LED_OFF();//FAN_LED_OFF();
		   RELAY_FAN_SetLow()	;


		 }
	
         if(tpd_t.relay_tape_flag ==1){
		 	 TAPE_LED_ON();
			 RELAY_TAPE_SetHigh();
			 
		 }
		 else{
		 	TAPE_LED_OFF();
            RELAY_TAPE_SetLow();

		 }

		 
//	     if(tpd_t.relay_kill_flag ==1){
//		 	 KILL_LED_ON();
//			 RELAY_KILL_SetHigh();
//	        
//		 }
//		 else{
//		 	 KILL_LED_OFF();
//			 RELAY_KILL_SetLow();
//	
//	
//		 }

		 
	    if(tpd_t.relay_keep_temp_flag ==1){
			KEEP_HEAT_LED_ON();
	        RELAY_KEEP_TEMP_SetHigh();
		}
		else{
	        KEEP_HEAT_LED_OFF();
	        RELAY_KEEP_TEMP_SetLow();
	
		}


    break;

	case relay_keep_temp_led_on:

	    //KEEP HEAT Display of LED 
       if(tpd_t.gTimer_select_fun < 6 && pro_t.key_long_confirm_flag ==1){
	   	   Keep_Heat_Led_Filcker();
		   tpd_t.keep_heat_run_flag= 1;
	       led_t.gTimer_keey_heat_flicker=0;
		   tpd_t.gTimer_keep_heat_fun=0;
		
       	}
        else{
			tpd_t.gTimer_select_fun=10;


			if(tpd_t.read_key_flag ==0 &&  pro_t.pro_t.key_long_confirm_flag ==1){
				tpd_t.relay_keep_temp_flag =1;
				pro_t.key_short_confirm_flag =0;
			}
			else if(pro_t.pro_t.key_long_confirm_flag ==1){

				tpd_t.relay_keep_temp_flag =0;
				pro_t.key_short_confirm_flag =0;


			}
			else{

				if(tpd_t.relay_keep_temp_flag ==1){
					KEEP_HEAT_LED_ON();
			        RELAY_KEEP_TEMP_SetHigh();
			    }
			    else{
			        KEEP_HEAT_LED_OFF();
			        RELAY_KEEP_TEMP_SetLow();
		
			    }

           }
          

        }

		//
	     if(tpd_t.relay_fan_flag == 1){

			 FAN_LED_ON();//FAN_LED_ON();
					 
		     RELAY_FAN_SetHigh()	 ;

         }
         else{
		   FAN_LED_OFF();//FAN_LED_OFF();
		   RELAY_FAN_SetLow()	;


		 }
	
         if(tpd_t.relay_tape_flag ==1){
		 	 TAPE_LED_ON();
			 RELAY_TAPE_SetHigh();
			 
		 }
		 else{
		 	TAPE_LED_OFF();
            RELAY_TAPE_SetLow();

		 }

		 
	     if(tpd_t.relay_kill_flag ==1){
		 	 KILL_LED_ON();
			 RELAY_KILL_SetHigh();
	        
		 }
		 else{
		 	 KILL_LED_OFF();
			 RELAY_KILL_SetLow();
	
	
		 }

		 
//	    if(tpd_t.relay_keep_temp_flag ==1){
//			KEEP_HEAT_LED_ON();
//	        RELAY_KEEP_TEMP_SetHigh();
//		}
//		else{
//	        KEEP_HEAT_LED_OFF();
//	        RELAY_KEEP_TEMP_SetLow();
//	
//		}


    break;

    }




}


