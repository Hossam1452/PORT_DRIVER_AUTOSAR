/*
 * Module : Port
 *
 * File Name : Port.h
 *
 * Description : Header file for Port Module
 *
 * Created on: Oct 31, 2019
 *
 * Author: Hossam Eldien Mahmoud
 */

#ifndef PORT_H_
#define PORT_H_

/* Id for the company in the AUTOSAR*/
#define PORT_VENDOR_ID    (1197U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port status
 */
#define PORT_INITIALIZED				(1U)
#define PORT_NOT_INITIALIZED			(0U)

/* Macros for number of Ports */
#define PORT_NUM						(4U)
#define PORT_A							(0U)
#define PORT_A_START					(0U)
#define PORT_A_FINISH					(7U)

#define PORT_B							(1U)
#define PORT_B_START					(8U)
#define PORT_B_FINISH					(15U)

#define PORT_C							(2U)
#define PORT_C_START					(16U)
#define PORT_C_FINISH					(23U)

#define PORT_D							(3U)
#define PORT_D_START					(24U)
#define PORT_D_FINISH					(31U)

/* Macros for number of pins */
#define PINS_NUM						(32U)
#define PINS_PER_PORT					(8U)
#define PIN_0							(0U)
#define PIN_1							(1U)
#define PIN_2							(2U)
#define PIN_3							(3U)
#define PIN_4							(4U)
#define PIN_5							(5U)
#define PIN_6							(6U)
#define PIN_7							(7U)
#define PIN_8							(8U)
#define PIN_9							(9U)
#define PIN_10							(10U)
#define PIN_11							(11U)
#define PIN_12							(12U)
#define PIN_13							(13U)
#define PIN_14							(14U)
#define PIN_15							(15U)
#define PIN_16							(16U)
#define PIN_17							(17U)
#define PIN_18							(18U)
#define PIN_19							(19U)
#define PIN_20							(20U)
#define PIN_21							(21U)
#define PIN_22							(22U)
#define PIN_23							(23U)
#define PIN_24							(24U)
#define PIN_25							(25U)
#define PIN_26							(26U)
#define PIN_27							(27U)
#define PIN_28							(28U)
#define PIN_29							(29U)
#define PIN_30							(30U)
#define PIN_31							(31U)


#define INPUT 								 (0U)
#define OUTPUT								 (1U)
#define DEFUALT_DIR							 (0U)
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR check between standard types and port module */
#if((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif


/* Non AUTOSAR files */
#include "Common_Macros.h"

/************************************ API Service Id Macros ***********************************/
/* Service ID for Port_init */
#define PORT_INIT_ID				    (uint8)0x00

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIRECTION_ID 		(uint8)0x01

/* Service Id for Port_RefreshPortDirection */
#define PORT_REFRESH_PIN_DIRECTION_ID	(uint8)0x02

/* Service ID for PORT_GetVersionInfo */
#define PORT_GET_VERSION_INFO_ID		(uint8)0x03

/* Service ID for PORT_SetPinMode */
#define PORT_SET_PIN_MODE_ID			(uint8)0x04

/*************************************** DET Error Codes **************************************/
/* DET code to report invalid channel */
#define PORT_E_PARAM_PIN				(uint8)0x0A

/* DET code to report unconfigurable pin */
#define PORT_E_DIRECTION_UNCHANGABLE	(uint8)0x0B

/* DET code to report init wrong parameter */
#define PORT_E_PARAM_CONFIG				(uint8)0x0C

/* DET code to report set pin mode unchangable */
#define PORT_E_PARAM__INVALID_MODE		(uint8)0x0D
#define PORT_E_MODE_UNCHANGABLE			(uint8)0x0E

/* API service used without module initialization is reported using following */
#define PORT_E_UNINIT					(uint8)0x0F

/* API called with a NULL PTR */
#define PORT_E_PARAM_POINTER			(uint8)0x10

/************************************** Module Data types *************************************/

/* Type definition for Port_pinType used by the Port APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinDirectionType used by the Port APIs */
typedef enum{
	PORT_PIN_IN,
	PORT_PIN_OUT
}Port_PinDirectionType;

/* Type definition for Port_PinInternalMode */
typedef enum{
	Disable=0, //if pin set as input
	Pull_up=1,
	Low=0, //if pin set as output
	High=1
}Port_PinInternalMode;

/* Type definition for Port_PinModeType used by Port APIs */
typedef uint8 Port_PinModeType; //dosn't used in AVR

typedef struct{
	Port_PinType Pin_Num;
	Port_PinDirectionType Pin_Dir;
	Port_PinInternalMode Pin_mode;
}Port_ConfigChannel;

typedef struct{
	Port_ConfigChannel Channels[PINS_NUM];
}Port_ConfigType;

/* Configuration structure file */
#include "Port_PBcfg.h"

/* AUTOSAR Version checking between Port_PBcfg.h and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBCfg.h does not match the expected version"
#endif

/* Software Version checking between Port_PBCfg.h and port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_PBCfg.h does not match the expected version"
#endif

/**************************************** Functions Prototype ***********************************************/

/* Function for Port initialization API */
void Port_Init(const Port_ConfigType* ConfigPtr);

/* Function for setting pin direction API */
void Port_SetPinDirection(const Port_PinType Pin,const Port_PinDirectionType Direction);

/* Function for refresh port direction */
void Port_RefreshPortDirection(void);

/* Function for get version information */
void Port_GetVersionInfo(Std_VersionInfoType* VersionInfo);

/* Function for setting pin mode */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode); //At AVR we don't use this function

#endif /* PORT_H_ */
