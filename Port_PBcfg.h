/*
 * Module : Port
 *
 * File Name : Port_PBcfg.h
 *
 * Description : Post Build compile Header file for Port Module
 *
 * Created on: Oct 31, 2019
 *
 * Author: Hossam Eldien Mahmoud
 */

#ifndef PORT_PBCFG_H_
#define PORT_PBCFG_H_

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

extern const Port_ConfigType Port_Configurations; //extern configuration structure from Port_PBcfg.c
extern const Port_PinType Port_Changable[Port_CONFIGURED_CHANNLES]; //extern array of changeable pins

#endif /* PORT_PBCFG_H_ */
