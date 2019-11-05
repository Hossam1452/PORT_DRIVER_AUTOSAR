/*
 * Module : Port
 *
 * File Name : Port_Cfg.h
 *
 * Description : Pre-compile Configurations Header file for Port module
 *
 * Created on: Oct 31, 2019
 *
 * Author: Hossam Eldien Mahmoud
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)


/* Number of the configured Port Channels */
#define Port_CONFIGURED_CHANNLES             (2U)

/* DIO Configured Port ID's  */
#define PortConf_LED_PORT_NUM                (Dio_PortType)0 /* PORTA */
#define PortConf_BUTTON_PORT_NUM             (Dio_PortType)3 /* PORTD */

/* DIO Configured Channel ID's */
#define PortConf_LED_CHANNEL_NUM             (Dio_ChannelType)0 /* Pin 0 in PORTA */
#define PortConf_BUTTON_CHANNEL_NUM          (Dio_ChannelType)2 /* Pin 2 in PORTD */

#endif /* PORT_CFG_H_ */
