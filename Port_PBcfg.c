/*
 * Module : PORT
 *
 * File Name : PORT_PBcfg.c
 *
 * Description : Post Build compile configuration source file for PORT Module
 *
 * Created on: Oct 31, 2019
 *
 * Author: Hossam Eldien Mahmoud
 */

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* Array of changable ports */
const Port_PinType Port_Changable[Port_CONFIGURED_CHANNLES] ={PIN_0,PIN_26}; //array of changable pins depends on configuration

const Port_ConfigType Port_Configurations = {
		PIN_0,PORT_PIN_OUT,STD_HIGH,//0	A
		PIN_1,DEFUALT_DIR,Disable,//1
		PIN_2,DEFUALT_DIR,Disable,//2
		PIN_3,DEFUALT_DIR,Disable,//3
		PIN_4,DEFUALT_DIR,Disable,//4
		PIN_5,DEFUALT_DIR,Disable,//5
		PIN_6,DEFUALT_DIR,Disable,//6
		PIN_7,DEFUALT_DIR,Disable,//7
		PIN_8,DEFUALT_DIR,Disable,//8	B
		PIN_9,DEFUALT_DIR,Disable,//9
		PIN_10,DEFUALT_DIR,Disable,//10
		PIN_11,DEFUALT_DIR,Disable,//11
		PIN_12,DEFUALT_DIR,Disable,//12
		PIN_13,DEFUALT_DIR,Disable,//13
		PIN_14,DEFUALT_DIR,Disable,//14
		PIN_15,DEFUALT_DIR,Disable,//15
		PIN_16,DEFUALT_DIR,Disable,//16	C
		PIN_17,DEFUALT_DIR,Disable,//17
		PIN_18,DEFUALT_DIR,Disable,//18
		PIN_19,DEFUALT_DIR,Disable,//19
		PIN_20,DEFUALT_DIR,Disable,//20
		PIN_21,DEFUALT_DIR,Disable,//21
		PIN_22,DEFUALT_DIR,Disable,//22
		PIN_23,DEFUALT_DIR,Disable,//23
		PIN_24,DEFUALT_DIR,Disable,//24	D
		PIN_25,DEFUALT_DIR,Disable,//25
		PIN_26,PORT_PIN_IN,Disable,//26
		PIN_27,DEFUALT_DIR,Disable,//27
		PIN_28,DEFUALT_DIR,Disable,//28
		PIN_29,DEFUALT_DIR,Disable,//29
		PIN_30,DEFUALT_DIR,Disable,//30
		PIN_31,DEFUALT_DIR,Disable,//31
};
