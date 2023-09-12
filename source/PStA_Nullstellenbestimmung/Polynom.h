/**********************************************************************************************************************

***********************************************************************************************************************
*                                                                                                                     *
*  Copyright (c) 2017, Simon Böhmisch. All rights reserved!                                                           *
*                                                                                                                     *
*    All rights exclusively reserved for Simon Böhmisch, unless expressly otherwise agreed.                           *
*                                                                                                                     *
*    Redistribution in source or any other form, with or without modification, is not permitted.                      *
*                                                                                                                     *
*    You may use this code under the according license terms of Simon Böhmisch. Please contact Simon Böhmisch         *
*    to get the appropriate terms and conditions.                                                                     *
*                                                                                                                     *
***********************************************************************************************************************

Component   ModuleTemplate

Filename    Polynom.h

brief       What will I find in this file?

author		Simon Böhmisch

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign				Description
--------  ----------  ----				-----------
01.00.00  2016-01-07  Simon Böhmisch	Initial check in

**********************************************************************************************************************/
#ifndef POLYNOM_H /* Include Guard */
#define POLYNOM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	/**********************************************************************************************************************
	INCLUDES
	**********************************************************************************************************************/
#include "Polynom_cfg.h"

	/**********************************************************************************************************************
	MACROS
	**********************************************************************************************************************/
#define E_OK    (0)	
#define E_Err	(-1)

	/**********************************************************************************************************************
	TYPEDEFS
	**********************************************************************************************************************/

	typedef unsigned char  uint8;
	typedef unsigned short uint16;
	typedef unsigned long  uint32;


	/**********************************************************************************************************************
	EXTERNAL FUNCTIONS
	**********************************************************************************************************************/
	extern int Eingabe_Polynom(void);
	extern int Ausgabe_Polynom(void);
	extern double fx_Polynom(double x_value);
	extern double Testfunktion_f1(double x_value);
	extern double Testfunktion_f2(double x_value);
	extern int Funktion_GetVersion(uint8 *uiMajorVersion, uint8 *uiMinorVersion, uint8 *uiPatchVersion);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* POLYNOM_H */
/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
