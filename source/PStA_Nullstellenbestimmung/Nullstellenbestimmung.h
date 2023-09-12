/**********************************************************************************************************************

***********************************************************************************************************************
*                                                                                                                     *
*  Copyright (c) 2017, Simon Böhmisch. All rights reserved!                                                           *
*                                                                                                                     *
*    All rights exclusively reserved for Simon Böhmisch, unless expressly otherwise agreed.                           *
*                                                                                                                     *
*    Redistribution in source or any other form, with or without modification, is not permitted.                      *
*                                                                                                                     *
*    You may use this code under the according license terms of Simon Böhmisch. Please contact Simon Böhmisch		  *
*    to get the appropriate terms and conditions.                                                                     *
*                                                                                                                     *
***********************************************************************************************************************

Component   ModuleTemplate

Filename    Verfahren.h

brief       What will I find in this file?

author      Simon Böhmisch

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign				Description
--------  ----------  ----				-----------
01.00.00  2021-01-21  Simon Böhmisch	Initial check in

**********************************************************************************************************************/
#ifndef NULLSTELLENBESTIMMUNG_H /* Include Guard */
#define NULLSTELLENBESTIMMUNG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	/**********************************************************************************************************************
	INCLUDES
	**********************************************************************************************************************/
#include "Nullstellenbestimmung_cfg.h"

	/**********************************************************************************************************************
	MACROS
	**********************************************************************************************************************/
#define E_OK			(0)	
#define E_NAN			(-1)
#define E_PARAMETER		(-2)
#define E_BERECHNUNG	(-3)

	/**********************************************************************************************************************
	TYPEDEFS
	**********************************************************************************************************************/

	typedef unsigned char  uint8;
	typedef unsigned short uint16;
	typedef unsigned long  uint32;


	/**********************************************************************************************************************
	EXTERNAL FUNCTIONS
	**********************************************************************************************************************/
	extern int Bisektion(double x1, double x2, double* Nullstelle, double(*m_funktion)(double), bool Debug_Mode);
	extern int Sekante(double x1, double x2, double* Nullstelle, double(*m_funktion)(double), bool Debug_Mode);
	extern int Verfahren_GetVersion(uint8 *uiMajorVersion, uint8 *uiMinorVersion, uint8 *uiPatchVersion);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NULLSTELLENBESTIMMUNG_H */
/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
