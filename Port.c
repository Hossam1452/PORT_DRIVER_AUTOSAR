/*
 * Module : Port
 *
 * File Name : Port.c
 *
 * Description : Source File for Port Module
 *
 * Created on: Oct 31, 2019
 *
 * Author: Hossam Eldien Mahmoud
 */

#include "Port.h"
#include "Dio_Regs.h"

#if(PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"

/* AUTOSAR Version checking between Det and PortModules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif

//static Port_ConfigChannel* Port_Channel = NULL_PTR;
static uint8 Port_Status = PORT_NOT_INITIALIZED;

/*
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port Driver.
*/
void Port_Init(const Port_ConfigType* ConfigPtr){
#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_INIT_ID, PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
		uint8* DDR_Ptr = NULL_PTR;//pointer to capture direction REG
		uint8* PORT_Ptr = NULL_PTR;//pointer to capture Port REG
		uint8 pins;	//to loop on all pins

		/* Loop on all pins and initialize it */
		for(pins=PIN_0; pins < PINS_NUM; pins++){
			/* Pin 0-7 PortA */
			if( (ConfigPtr->Channels[pins].Pin_Num >=PORT_A_START) &&
					(ConfigPtr->Channels[pins].Pin_Num <= PORT_A_FINISH ) )
			{
				DDR_Ptr = &DDRA_REG;	//Set direction REG as DDRA
				PORT_Ptr = &PORTA_REG;	//Set Port REG as PORTA
			}
			/* Pin 8-15 PortB */
			/**/
			else if( (ConfigPtr->Channels[pins].Pin_Num >=PORT_B_START)  &&
					(ConfigPtr->Channels[pins].Pin_Num <= PORT_B_FINISH ) )
			{
				DDR_Ptr = &DDRB_REG;	//Set direction REG as DDRB
				PORT_Ptr = &PORTB_REG;	//Set Port REG as PORTB
			}
			/* Pin 16-23 PortC */
			else if( (ConfigPtr->Channels[pins].Pin_Num >= PORT_C_START ) &&
					(ConfigPtr->Channels[pins].Pin_Num <= PORT_C_FINISH ) )
			{
				DDR_Ptr = &DDRC_REG;	//Set direction REG as DDRC
				PORT_Ptr = &PORTC_REG;	//Set Port REG as PORTC
			}
			/* Pin 24-31PortD */
			else if( (ConfigPtr->Channels[pins].Pin_Num >= PORT_D_START ) &&
					(ConfigPtr->Channels[pins].Pin_Num <= PORT_D_FINISH ) )
			{
				DDR_Ptr = &DDRD_REG;	//Set direction REG as DDRD
				PORT_Ptr = &PORTD_REG;	//Set Port REG as PORTD
			}
			/* Out of Range */
			else
			{
				#if(PORT_DEV_ERROR_DETECT == STD_ON)
					Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							PORT_INIT_ID, PORT_E_PARAM_CONFIG);
				#endif
			}
			/* Setting Pin direction */
			//if Pin_Dir is OUTPUT
			if(ConfigPtr->Channels[pins].Pin_Dir == OUTPUT)
			{
				SET_BIT(*DDR_Ptr, (ConfigPtr->Channels[pins].Pin_Num % PINS_PER_PORT));	//Pin_Num % 8 = Pin_Num in Port
				/* Setting initial value */
				//High
				if(ConfigPtr->Channels[pins].Pin_mode == High)
				{
					SET_BIT(*PORT_Ptr, (ConfigPtr->Channels[pins].Pin_Num % PINS_PER_PORT));
				}
				//Low
				else
				{
					CLEAR_BIT(*PORT_Ptr, (ConfigPtr->Channels[pins].Pin_Num % PINS_PER_PORT));
				}
			}
			//if Pin_Dir not OUTPUT -> Input or unchangeable by Input default
			else
			{
				CLEAR_BIT(*DDR_Ptr, (ConfigPtr->Channels[pins].Pin_Num % PINS_PER_PORT));
				/* Setting internal mode */
				//Pull up
				if(ConfigPtr->Channels[pins].Pin_mode == Pull_up)
				{
					SET_BIT(*PORT_Ptr, (ConfigPtr->Channels[pins].Pin_Num % PINS_PER_PORT));
				}
				//Disable
				else
				{
					CLEAR_BIT(*PORT_Ptr, (ConfigPtr->Channels[pins].Pin_Num % PINS_PER_PORT));
				}
			}
		}
		Port_Status = PORT_INITIALIZED; //Change port status as initialized
	}
}

/*
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin -Port Pin ID number.
* 				   Dir -Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Set the port pin direction.
*/
void Port_SetPinDirection(const Port_PinType Pin,const Port_PinDirectionType Direction)
{
	uint8 *DDR_Ptr = NULL_PTR;//pointer to capture direction REG
	uint8 *PORT_Ptr = NULL_PTR;//pointer to capture Port REG
	uint8 port = Pin/PINS_PER_PORT;	//to capture port id
#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(PINS_NUM <= Pin)
	{
		/* Reporting Det error */
		/* Pin is out of range */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
						PORT_SET_PIN_DIRECTION_ID, PORT_E_PARAM_PIN);
	}
	else
	{
		uint8 changeable_flag = 0;	//1 if this pin configure as changeable pin
		uint8 changeable_pins;	//iterator to for loop
		for(changeable_pins=0; changeable_pins < Port_CONFIGURED_CHANNLES; changeable_pins++)
		{
			/* Loop on the changeable pins Array if the Pin is changeable set the changeableflag */
			if(Port_Changable[changeable_pins]==Pin)
			{
				changeable_flag =1;
			}
			else
			{}
		}
		if(0 == changeable_flag)
		{
			/* Reporting Det error */
			/* Pin is configured as unchangeable */
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
							PORT_SET_PIN_DIRECTION_ID, PORT_E_DIRECTION_UNCHANGABLE);
		}
		else{/* NO ACTION NEED */}
	}
#endif
	/* Switch on the Port */
	switch(port)
	{
	/* PORT A */
	case PORT_A : DDR_Ptr = &DDRA_REG;	//Setting dir REG as DDRA
			PORT_Ptr = &PORTA_REG;	//Setting Port REG as PORTA
			break;
	/* PORT B */
	case PORT_B : DDR_Ptr = &DDRB_REG;	//Setting dir REG as DDRB
			PORT_Ptr = &PORTB_REG;	//Setting Port REG as PORTB
			break;
	/* PORT C */
	case PORT_C : DDR_Ptr = &DDRC_REG;	//Setting dir REG as DDRC
			PORT_Ptr = &PORTC_REG;	//Setting Port REG as PORTC
			break;
	/* PORT D */
	case PORT_D : DDR_Ptr = &DDRD_REG;	//Setting dir REG as DDRD
			PORT_Ptr = &PORTD_REG;	//Setting Port REG as PORTD
			break;
	}
	/* Setting the direction */
	if(Direction == OUTPUT)
	{
		SET_BIT(*DDR_Ptr, (Pin % PINS_PER_PORT));
		SET_BIT(*PORT_Ptr, STD_LOW);//By default Low
	}
	else
	{
		CLEAR_BIT(*DDR_Ptr, (Pin % PINS_PER_PORT));
	}
}

/*
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refresh Port direction
*/
void Port_RefreshPortDirection(void)
{
#if(PORT_DEV_ERROR_DETECT == STD_ON)
	if(PORT_NOT_INITIALIZED == Port_Status)
	{
		/* Report Det Error */
		//Port is not initialized
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
									PORT_REFRESH_PIN_DIRECTION_ID, PORT_E_UNINIT);
	}
	else
#endif
	{
		uint8* DDR_Ptr = NULL_PTR; //pointer to capture dir REG
		uint8 pins; //pins iterator
		uint8 changeable_pins; //changeable pins iterator
		uint8 changeable_flag=0; //flag set if the pin is changeable
		/* loop on all pins if it unchangeable refresh it's direction by set it as input "Default" */
		for(pins=PIN_0; pins <= PIN_31; pins++)
		{
			/* loop on changeable pins Array to know if this pin is changeable or not */
			for(changeable_pins=0; changeable_pins < Port_CONFIGURED_CHANNLES ; changeable_pins++)
			{
				if(pins == Port_Changable[changeable_pins])
				{
					changeable_flag =1; //set changeable flag
				}
				else{}
			}
			//if pin is configured as unchangeable
			if(0 == changeable_flag)
			{
				switch(pins/PINS_PER_PORT) //switch the port
				{
				case PORT_A : DDR_Ptr = &DDRA_REG;	//Setting dir REG as DDRA
							break;
				case PORT_B : DDR_Ptr = &DDRB_REG;	//Setting dir REG as DDRB
							break;
				case PORT_C : DDR_Ptr = &DDRC_REG;	//Setting dir REG as DDRC
							break;
				case PORT_D : DDR_Ptr = &DDRD_REG;	//Setting dir REG as DDRD
							break;
				}
				//Clear DDR to set it as input -> default direction
				CLEAR_BIT(*DDR_Ptr, (pins % PINS_PER_PORT));
			}
			else{/* NO ACTION NEED */}
		}
	}
}

/*
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - pointer to structure store the Version information
* Return value: None
* Description: Function to Initialize the Port Driver.
*/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
						PORT_GET_VERSION_INFO_ID, PORT_E_UNINIT);
	}
	else if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_ID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif
