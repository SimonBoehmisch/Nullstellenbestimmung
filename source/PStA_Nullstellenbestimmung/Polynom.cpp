/**********************************************************************************************************************

***********************************************************************************************************************
*                                                                                                                     *
*  Copyright (c) 2017, Simon Böhmisch . All rights reserved!                                                          *
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

Filename    Polynom.cpp

brief       Dieses Modul beinhaltet Funktionen für die Ein und Ausgabe eines Polynoms sowie die Berechnung 
			dessen Funktionswertes und Zwei Exemplarisch gewaehlte Testfunktionen

author      Simon Böhmisch

***********************************************************************************************************************
* Changes                                                                                                             *
***********************************************************************************************************************

Version   Date        Sign				Description
--------  ----------  ----				-----------
01.00.00  2017-01-07  Simon Böhmisch	Initial check in

**********************************************************************************************************************/

/**********************************************************************************************************************
INCLUDES
**********************************************************************************************************************/
#include "stdafx.h" /* ohne Bedeutung, rein windowsspezifisch */
#include "Polynom.h"
#include "Polynom_cfg.h"
#include "math.h"

/**********************************************************************************************************************
MACROS
**********************************************************************************************************************/
#define MAJOR_VERSION  01
#define MINOR_VERSION  00
#define PATCH_VERSION  00


/**********************************************************************************************************************
GLOBAL VARIABLES
**********************************************************************************************************************/

double Vielfache_a[Max_Grad] = { 0 };	/* Array um die jeweiligen Vielfachen a der unbekannten x des Polynoms zu Speichern */ 
int Grad_n;								/* Integer um den Grad n des Polynoms zu speichern*/


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
*   return       iErr
*
*   retval       E_OK         Calling function is allowed.
*   retval       E_NOT_OK     Calling function is not allowed.
*
*   author       Name of the developer
**********************************************************************************************************************/
int Funktion_GetVersion(uint8 *uiMajorVersion, uint8 *uiMinorVersion, uint8 *uiPatchVersion)
{
	int iErr = E_OK;

	*uiMajorVersion = MAJOR_VERSION;  /* Major */
	*uiMinorVersion = MINOR_VERSION;  /* Minor */
	*uiPatchVersion = PATCH_VERSION;  /* Patch */

	return(iErr);
}

/*********************************************************************************************************************/
/*  brief        Funktion für die Abfrage des Polynoms dessen Nullstelle berechnet werden soll
*
*   Der Nutzer wird aufgefordert den Grad des Polynoms einzugeben, anschließend wird er aufgefordert die jeweiligen 
*	Vielfachen a einzugeben
*
*   param[in]    void  
*
*   return       iErr		  Fehlercode
*
*   retval       E_OK         Calling function is allowed
*   retval       E_NOT_OK     Calling function is not allowed
*
*   author       Simon Böhmisch
**********************************************************************************************************************/
int Eingabe_Polynom(void)
{
	int iErr = E_OK;
	int i;

#ifdef NEW_METHOD
	/* Array für die Speicherung der jwewiligen Vielfachen a wird mit Null ueberschrieben */
	for (i = 0; i < Max_Grad; i++)
	{
		Vielfache_a[i] = 0;
	}
	printf("Geben Sie den Grad n des Polynoms ein (1 ~ 4 ): ");
	scanf_s("%d", &Grad_n);
	/* Abfrage der Vielfachen a */
	if ((Grad_n >= 1) && (Grad_n <= Max_Grad))
	{
		printf("Geben Sie das jeweilige Vielfache a ein\n");
		/* Beginnend mit der unbestimmten x mit dem höchsten Grad n werden die jeweiligen Vielfachen a abgefragt */
		/* f(x) = a*x^n ... + a*x^2 + a*x + a*/
		for (i = 0; i <= Grad_n; i++)
		{
			printf("a*x^%d:", Grad_n - i);
			scanf_s("%lf", &Vielfache_a[Grad_n - i]);
		}
	}
	/* Ungueltige Eingabe */
	else 
	{
		iErr = E_Err;
	}
	printf("\n");
#else 

#endif

	return(iErr);
}

/*********************************************************************************************************************/
/*  brief        Funktion für die Ausgabe des vom Nutzer eingegebenen Polynoms
*
*   Ausgabe erfolgt in dieser Form: f(x) = a*x^n... + a*x^2 + a*x + a
*
*   return       iErr
*
*   retval       E_OK         Calling function is allowed.
*   retval       E_NOT_OK     Calling function is not allowed.
*
*   author       Simon Böhmisch
**********************************************************************************************************************/
int Ausgabe_Polynom(void)
{
	int iErr = E_OK;
	int i;

#ifdef NEW_METHOD
	printf("Folgendes Polynom wurde eingegeben: f(x)=");
	for (i = 0; i <= Grad_n; i++)
	{
		/* Ausgabe für unbestimmte x mit Grad > 1 und deren Vielfache a */
		/* Ausgabe: a*x^n */
		if (Grad_n - i > 1)
		{
			printf("%.2lfx^%d", Vielfache_a[Grad_n - i], Grad_n - i);
			if (Vielfache_a[Grad_n - i - 1] >= 0)
			{
				printf("+");
			}
		}
		/*Ausgabe für unbestimmte x mit Grad = 1 und deren Vielfache a */
		/* Ausgabe: a*x */
		else if (Grad_n - i > 0)
		{
			printf("%.2lfx", Vielfache_a[Grad_n - i]);
			if (Vielfache_a[Grad_n - i - 1] >= 0)
			{
				printf("+");
			}
		}
		/*Ausgabe für unbestimmte x mit Grad = 0 und deren Vielfache a */
		/* Ausgabe: a */
		else
		{
			printf("%.2lf", Vielfache_a[Grad_n - i]);
		}
	}
	printf("\n\n");
#else 

#endif

	return(iErr);
}

/*********************************************************************************************************************/
/*  brief        Berechnet den Funktionswert f(x) für das vom Nutzer eingegebene Polynom
*
*   param[in]    x_value	Variable x der Funktion / wird vom Bisektions- oder Sekantenverfahren berechnet und übergeben
*
*   return       y_value	Errechneter Funktionswert f(x_value)
*
*   author       Simon Böhmisch
**********************************************************************************************************************/
double fx_Polynom(double x_value)
{
	int i = 0;
	double y_value = 0;

#ifdef NEW_METHOD
	for (i = 0; i <= Grad_n; i++)
	{
		/* Hier wird folgendes berechnet: y_value = a*x^n für alle unbekannten des Polynoms */
		y_value += (Vielfache_a[Grad_n-i] * pow(x_value, Grad_n - i));
	}
#else 

#endif
	return(y_value);
}

/*********************************************************************************************************************/
/*  brief        Berechnet den Funktionswert f(x) für die exemplarisch gewaehlte Testfunktion 1
*
*   param[in]    x_value	Variable x der Funktion / wird vom Bisektions- oder Sekantenverfahren berechnet und übergeben
*
*   return       y_value	Errechneter Funktionswert f(x_value)
*
*   author       Simon Böhmisch
**********************************************************************************************************************/
double Testfunktion_f1(double x_value)
{
	/* f(x) = x^2 - 2x - 1*/
	double y_value = 0;
	y_value = ((2 * (x_value * x_value)) - (2 * x_value) - 2);
	return y_value;
}

/*********************************************************************************************************************/
/*  brief        Berechnet den Funktionswert f(x) für die exemplarisch gewaehlte Testfunktion 2
*
*   param[in]    x_value	Variable x der Funktion / wird vom Bisektions- oder Sekantenverfahren berechnet und übergeben
*
*   return       y_value	Errechneter Funktionswert f(x_value)
*
*   author       Simon Böhmisch
**********************************************************************************************************************/
double Testfunktion_f2(double x_value)
{
	/* f(x) = e^x - 8 */
	double y_value = 0;
	y_value = (exp(x_value) - 8);
	return y_value;
}

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/
