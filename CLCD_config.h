/*******************************************************************************/
// Layer : HAL 
// Author : OMAR Sayed 
// Version : 01
// Date : 21/8/2023
//                              *Component CLCD*
/*******************************************************************************/
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/* Port Options
 * 1- PORTA_REG
 * 2- PORTB_REG
 * 3- PORTC_REG
 * 4- PORTD_REG
 */

/* Pin Options
 * 1- PIN0
 * 2- PIN1
 * 3- PIN2
 * 4- PIN3
 * 5- PIN4
 * 6- PIN5
 * 7- PIN6
 * 8- PIN7
 */

#define CLCD_DATA_PORT     PORTA_REG

#define CLCD_CTRL_PORT     PORTC_REG

#define RS     PIN0
#define RW     PIN1
#define EN     PIN2









#endif
