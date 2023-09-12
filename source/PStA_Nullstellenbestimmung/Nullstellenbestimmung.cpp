/**********************************************************************************************************************

***********************************************************************************************************************
*                                                                                                                     *
*  Copyright (c) 2017, Simon Böhmisch . All rights reserved!                                                          *
*                                                                                                                     *
*    All rights exclusively reserved for xxx, unless expressly otherwise agreed.                                      *
*                                                                                                                     *
*    Redistribution in source or any other form, with or without modification, is not permitted.                      *
*                                                                                                                     *
*    You may use this code under the according license terms of Simon Böhmisch. Please contact Simon Böhmisch         *
*    to get the appropriate terms and conditions.                                                                     *
*                                                                                                                     *
***********************************************************************************************************************

Component   ModuleTemplate

Filename    Nullstellenbestimmung.cpp

brief       In diesem Modul sind das Bisektions- und Sekantenverfahren zur nummerischen Bestimmung von Nullstellen implementiert

author      Simon Böhmisch

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign			   Description
--------  ----------  ----			   -----------
01.00.00  2021-01-21  Simon Böhmisch   Initial check in

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES
**********************************************************************************************************************/
#include "stdafx.h" /* ohne Bedeutung, rein windowsspezifisch */
#include "Nullstellenbestimmung.h"
#include "Nullstellenbestimmung_cfg.h"
#include "math.h"

/**********************************************************************************************************************
MACROS
**********************************************************************************************************************/
#define MAJOR_VERSION  01
#define MINOR_VERSION  00
#define PATCH_VERSION  00

/**********************************************************************************************************************
FUNCTIONS
**********************************************************************************************************************/

/*********************************************************************************************************************/
/*  brief        Brief information about the function below.
*
*   Here might be added an optional detailed description which is mandatory for complex functions]
*
*   param[in]    Var1  BriefVarDescription [keyword:param]
*   param[out]   Var2  ...
*   param[in]    Var3  ...  MANDATORY if function has parameters]
*
*   return       xx
*
*   retval       E_OK         Calling function is allowed.
*   retval       E_NOT_OK     Calling function is not allowed.
*
*   author       Simon Böhmisch
**********************************************************************************************************************/
int Verfahren_GetVersion(uint8 *uiMajorVersion, uint8 *uiMinorVersion, uint8 *uiPatchVersion)
{
	int iErr = E_OK;

	*uiMajorVersion = MAJOR_VERSION;  /* Major */
	*uiMinorVersion = MINOR_VERSION;  /* Minor */
	*uiPatchVersion = PATCH_VERSION;  /* Patch */

	return(iErr);
}

/*********************************************************************************************************************/
/*  brief        Nullstellenbestimmung mittels Bisektionsverfahren
*
*   Das Verfahren wird beendet, falls eine Loesung mit der Genauigkeit "Epsilon" gefunden oder nach einer Maximalen Anzahl "Max_Iter" 
*	Iterationen keine Loesung gefunden wurde
*
*   param[in]    x1				 Parameter 1 gibt linke Intervallgrenze für die Suche der Nullstelle an
*   param[in]    x2				 Parameter 2 gibt rechte Intervallgrenze für die Suche der Nullstelle an
*   param[in]    funktion		 Zeiger auf Funktion deren Nullstelle bestimmt werden soll
*   param[in]    Debug_Mode		 Bool der die Approximative Ausgabe der Zwischenergebnisse aktiviert
*   param[in]	 Nullstelle		 Zeiger um die gefundene Nullstelle zu übergeben
*								 
*   return       iErr			 Hier wird  ein Fehlercode zurueckgegeben
*
*   retval       E_OK		     Funktion wurde erfolgreich beendet, es wurde eine Nullstelle gefunden
*   retval       E_NAN		     Bei der Berechnung ist ein Überlauf aufgetreten
*   retval       E_PARAMETER	 Für die Übergebene Funktion kann die Bisektion in dem Intervall [x1,x2] keine Nullstelle bestimmen
*   retval       E_BERECHNUNG    Die maximale Iterationzahl wurde überschritten, es wurde keine Nullstelle gefunden
*
*   author       Simon Böhmisch
*********************************************************************************************************************/
int Bisektion(double x1, double x2, double* Nullstelle, double(*m_funktion)(double), bool Debug_Mode)
{
	int iErr = E_OK;
	uint8 Counter = 1;
	double Vorzeichen, fx1, fx2, fx3, x3;
	
#ifdef NEW_METHOD
	fx1 = m_funktion(x1);
	fx2 = m_funktion(x2);
	Vorzeichen = fx1 * fx2;

	/* Hier wird geprueft ob ein Ueberlauf stattfindet bzw eine ungueltige Rechenoperation erfolgt ist */
	/* Ist dies der Fall wird die Funktion beendet */
	if (isnan(fx1) || isnan(fx2))
	{
		iErr = E_NAN;
	}
	/* Hier wird geprueft ob einer der beiden übergebenen Intervallgrenzen die Nullstelle ist */
	/* Ist dies der Fall wird die Funktion beendet */
	else if (fabs(fx1) <= Epsilon || fabs(fx2) <= Epsilon)
	{
		if (fabs(fx1) <= Epsilon)			 /* Nullstelle ist x1 */
		{
			*Nullstelle = x1;
		}
		if (fabs(fx2) <= Epsilon)			 /* Nullstelle ist x2 */
		{
			*Nullstelle = x2;
		}
	}
	/* Hier wird geprueft ob die Funktionswerte fx1 und fx2 ein gleiches Vorzeichen besitzen -> keine Nullstelle */
	/* Ist dies der Fall wird die Funktion beendet */
	else if (Vorzeichen > 0)
	{
		iErr = E_PARAMETER;
	}
	else
	{
		/* Berechnung der Bisektion */
		while (Counter <= Max_Iter)
		{
			x3 = ((x1 + x2) / 2.0);
			fx3 = m_funktion(x3);
			/* Hier wird geprueft ob ein Ueberlauf stattfindet bzw eine ungueltige Rechenoperation erfolgt ist */
			/* Ist dies der Fall wird die Funktion beendet */
			if (isnan(fx3))
			{
				iErr = E_NAN;
				break;
			}
			/* Hier wird geprüft ob der erechnete Parameter die Nullstelle ist */
			else if (fabs(fx3) <= Epsilon)
			{
				*Nullstelle = x3;
				break;
			}
			/* Eingraenzen des Suchintervalls */
			else
			{
				Vorzeichen = fx1 * fx3;
				/* Nullstelle befindet sich im Bereich zwischen x1 und x3 */
				if (Vorzeichen < 0)
				{
					x2 = x3;
					fx2 = fx3;
				}
				/* Nullstelle befindet sich im Bereich zwischen x3 und x2 */
				else
				{
					x1 = x3;
					fx1 = fx3;
				}
				/* Ausgabe der Durchgaenge und Zischenergebnisse bei aktiviertem Debug Modus */
				if (Debug_Mode)
				{
					printf("n: %d, x1 = %.3f, x2 = %.3f\n", Counter, x1, x2);
				}
				Counter++;
			}
		}
	}
	/* Die maximale Iterationsanzahl wurde ueberschritten / Keine Nullstelle gefunden */
	if (Counter > Max_Iter)
	{
		iErr = E_BERECHNUNG;
	}
#else 

#endif
	return(iErr);
}

/*********************************************************************************************************************/
/*  brief        Nullstellenbestimmung mittels Sekantenverfahren
*
*   Das Verfahren wird beendet, falls eine Loesung mit der Genauigkeit "Epsilon" gefunden oder nach "Max_Iter"
*	Iterationen keine Loesung gefunden wurde
*
*   param[in]    x1				 Parameter 1 in dessen Naehe die Nullstelle gesucht werden soll an
*   param[in]    x2				 Parameter 2 in dessen Naehe die Nullstelle gesucht werden soll an
*   param[in]    funktion		 Zeiger auf Funktion deren Nullstelle bestimmt werden soll
*   param[in]    Debug_Mode		 Bool der die Approximative Ausgabe der Zwischenergebnisse aktiviert
*   param[in]	 Nullstelle		 Zeiger um die gefundene Nullstelle zu übergeben
*								 
*   return       iErr			 Hier wird  ein Fehlercode zurueckgegeben
*
*   retval       E_OK		     Funktion wurde erfolgreich beendet, es wurde eine Nullstelle gefunden
*   retval       E_NAN		     bei der Berechnung ist ein Ueberlauf aufgetreten
*   retval       E_BERECHNUNG    Es wurde keine Nullstelle gefunden, die maximale Iterationzahl wurde ueberschritten
*
*   author       Simon Böhmisch
**********************************************************************************************************************/
int Sekante(double x1, double x2, double* Nullstelle, double(*m_funktion)(double), bool Debug_Mode)
{
	int iErr = E_OK;
	uint8 Counter = 1;
	double fx1, fx2, x3, fx3;
	
#ifdef NEW_METHOD
	fx1 = m_funktion(x1);
	fx2 = m_funktion(x2);

	/* Hier wird geprüft ob ein Ueberlauf stattfindet bzw eine ungueltige Rechenoperation erfolgt ist */
	/* Ist dies der fall wird die Funktion beendet */
	if (isnan(fx1) || isnan(fx2))
	{
		iErr = E_NAN;
	}
	/* Hier wird geprueft ob einer der beiden Parameter die Nullstelle ist */
	else if (fabs(fx1) <= Epsilon || fabs(fx2) <= Epsilon)
	{
		if (fabs(fx1) < Epsilon)			/* Nullstelle ist x1 */
		{
			*Nullstelle = x1;
		}
		if (fabs(fx2) < Epsilon)			/* Nullstelle ist x2 */
		{
			*Nullstelle = x2;
		}
	}
	else
	{
		/* Berechnung Sekantenverfahen */
		while (Counter <= Max_Iter)
		{
			x3 = x2 - (((x2 - x1)*fx2) / (fx2 - fx1));
			fx3 = m_funktion(x3);
			/* Hier wird geprueft ob ein Ueberlauf stattfindet bzw eine ungueltige Rechenoperation erfolgt ist */
			/* Ist dies der Fall wird die Funktion beendet */
			if (isnan(fx3))
			{
				iErr = E_NAN;
				break;
			}
			/* Hier wird geprueft ob der errechnete Parameter die Nullstelle ist */
			else if (fabs(fx3) <= Epsilon)
			{
				*Nullstelle = x3;
				break;
			}
			/* eingraenzen des Suchintervalls */
			else
			{
				x1 = x2;
				x2 = x3;
				fx1 = fx2;
				fx2 = fx3;
				/* Ausgabe der Durchgaenge und Zwischenergebnisse bei aktiviertem Debug Modus */
				if (Debug_Mode)
				{
					printf("n: %d, x1 = %.3f, x2 = %.3f\n", Counter, x1, x2);
				}
				Counter++;
			}
		}
	}
	/* Die maximale Iterationsanzahl wurde ueberschritten / keine Nullstelle gefunden */
	if (Counter > Max_Iter)
	{
		iErr = E_BERECHNUNG;
	}
#else

#endif
	return(iErr);
}

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
