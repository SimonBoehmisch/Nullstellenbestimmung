// PStA_Nullstellenbestimmung.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

/**********************************************************************************************************************
INCLUDES
**********************************************************************************************************************/
#include <iostream>
#include "stdafx.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "Nullstellenbestimmung.h"
#include "Polynom.h"

/**********************************************************************************************************************
GLOBAL VARIABLES
**********************************************************************************************************************/
double X_left, X_right, Nullstelle;

/**********************************************************************************************************************
PROTOTYPES
**********************************************************************************************************************/
double Testfunktion_f1(double x_value);
double Testfunktion_f2(double x_value);
int Eingabe_Startwert(double* x1, double* x2);
void Auswertung_Fehlercode(int Err_Code);

/**********************************************************************************************************************
FUNCTIONS
**********************************************************************************************************************/

/*********************************************************************************************************************/
/*  brief       Das Demo Programm erlaubt es dem Nutzer das Bisektions- und Sekantenverfahrens für die 
*				Bestimmung der Nullstelle einer stetigen Funktion zu verwenden
*				Der Nutzer hat folgende Möglichkeiten:
*				1. Nutzer kann für eine vorgegebenen Funktion 1, die Nullstelle mittels Bisektions- und Sekantenverfahren berechnen lassen
*				1. Nutzer kann für eine vorgegebenen Funktion 2, die Nullstelle mittels Bisektions- und Sekantenverfahren berechnen lassen
*				3. Nutzer kann selbst ein Polynom, dessen Nullstelle mithilfe der beiden Verfahren bestimmt werden soll, eingeben 
*               4. Aktivieren/Deaktivieren des Debug Modus, hier werden die Approximativen Schritte der beiden Verfahren mit ausgegeben
*               5. Programm beenden
*
*   return      int     0
**********************************************************************************************************************/
int main()
{
	int iRet = E_OK;						/* int fuer Fehlercodes */
	char Auswahl_Menu = 0;					/* int um die vom Nutzer gewählte Menu Option zu speichern */
	bool Debug_Mode = false;				/* Boolean um die Approximative Ausgabe der beiden Verfahren zu aktivieren/deaktivieren */
	double* pX_left = &X_left;				/* Zeiger auf die linke Intervallgrenze*/
	double* pX_right = &X_right;			/* Zeiger auf die rechte Intervallgrenze*/
	double* pNullstelle = &Nullstelle;		/* Zeiger auf die vom Bisektions/Sekantenverfahren errechnete Nullstelle */

	while (Auswahl_Menu != 5)
	{
		printf("1) Testfunktion f(x)=2x^2-2x-2\n2) Testfunktion f(x)=e^x-1\n3) Eigenes Polynom \n4) Debug Modus \n5) Beenden\n");
		printf("Auswahl: ");
		scanf_s("%hhd", &Auswahl_Menu);
		printf("\n");
		/* Switch fuer die Menuoptionen */
		switch (Auswahl_Menu)
		{
		/* Nutzer kann zwischen zwei vorgegebenen Funktion, deren Nullstelle bestimmt werden soll, wählen */
		case 1:
			printf("Folgende Funktion wurde ausgewaehlt: f(x)=2x^2-2x-2\n\n");
			iRet = Eingabe_Startwert(pX_left, pX_right);									/* Nutzer wird aufgefordert die Intervallgrenzen einzugeben */
			printf("**********BISEKTION**********\n");
			iRet = Bisektion(X_left, X_right, pNullstelle, Testfunktion_f1, Debug_Mode);	/* Hier wird das Bisektionsverfahren aufgerufen */
			Auswertung_Fehlercode(iRet);	
			printf("**********SEKANTE**********\n");
			iRet = Sekante(X_left, X_right, pNullstelle, Testfunktion_f1, Debug_Mode);		/* Hier wird das Sekantenverfahren aufgerufen */
			Auswertung_Fehlercode(iRet);
			break;
		/* Nutzer kann zwischen zwei vorgegebenen Funktion, deren Nullstelle bestimmt werden soll, wählen */
		case 2:
			printf("Folgende Funktion wurde ausgewaehlt: f(x)=e^x-1\n\n");
			iRet = Eingabe_Startwert(pX_left, pX_right);									/* Nutzer wird aufgefordert die Intervallgrenzen einzugeben */
			printf("**********BISEKTION**********\n");
			iRet = Bisektion(X_left, X_right, pNullstelle, Testfunktion_f2, Debug_Mode);	/* Hier wird das Bisektionsverfahren aufgerufen */
			Auswertung_Fehlercode(iRet);
			printf("**********SEKANTE**********\n");
			iRet = Sekante(X_left, X_right, pNullstelle, Testfunktion_f2, Debug_Mode);		/* Hier wird das Sekantenverfahren aufgerufen */
			Auswertung_Fehlercode(iRet);
			break;
		/* Hier kann der Nutzer selbst ein Polynom eingeben, dessen Nullstelle bestimmt werden soll */
		case 3:
			printf("Geben Sie ein Polynom der Form: f(x) = a*x^n ... + a*x^2 + a*x + a an\n");
			iRet = Eingabe_Polynom();
			if (iRet == E_OK)
			{
				iRet = Ausgabe_Polynom();
				iRet = Eingabe_Startwert(pX_left, pX_right);								/* Nutzer wird aufgefordert die Intervallgrenzen einzugeben */
				printf("**********BISEKTION**********\n");
				iRet = Bisektion(X_left, X_right, pNullstelle, fx_Polynom, Debug_Mode);		/* Hier wird das Bisektionsverfahren aufgerufen */
				Auswertung_Fehlercode(iRet);
				printf("**********SEKANTE**********\n");
				iRet = Sekante(X_left, X_right, pNullstelle, fx_Polynom, Debug_Mode);		/* Hier wird das Sekantenverfahren aufgerufen */
				Auswertung_Fehlercode(iRet);
			}
			else
			{
				printf("Ungueltige Eingabe!\n");
			}
			break;
		/* Aktivieren / Deaktivieren des Debug Modus, hier werden die Approximativen Schritte der beiden Verfahren mit ausgegeben */
		case 4:
			if (Debug_Mode == false)
			{
				Debug_Mode = true;
				printf("Debug Modus = ein\n");
			}
			else
			{
				Debug_Mode = false;
				printf("Debug Modus = aus\n");
			}
			printf("\n");
			break;
		/* Programm beenden */
		case 5:
			Auswahl_Menu = 5;	/* Bedingung der while schleife is nicht mehr erfüllt*/
			printf("Das Programm wird beendet\n");
			break;
		default:
			printf("Ungueltige Eingabe!\n");
			break;
		}		
	}
	return 0;
}

/*********************************************************************************************************************/
/*  brief        Funktion für die Abfrage der für das Bisektions- und Sekantenverfahren erforderlichen Intervallgrenzen
*
*   param[out]    x1  Zeiger auf den ersten Parameter der Intervallgrenzen
*   param[out]    x2  Zeiger auf den ersten Parameter der Intervallgrenzen
*
*   return       iErr
*
*   retval       E_OK         Calling function is allowed.
*   retval       E_NOT_OK     Calling function is not allowed.
*
*   author       Simon Böhmisch
**********************************************************************************************************************/
int Eingabe_Startwert(double* x1, double* x2)
{
	int iErr = E_OK;

	printf("Suchbereich fuer die Nullstelle eingeben [x1,x2]: \n");
	printf("x1: ");
	scanf_s("%lf", x1);
	printf("x2: ");
	scanf_s("%lf", x2);
	printf("\n");
	printf("Startwerte: x1 = %.3f, x2 = %.3f\n", *x1, *x2);
	printf("\n");
	return(iErr);
}

/*********************************************************************************************************************/
/*  brief       Funktion die den vom Bisektions- und Sekantenverfahren zurueckgegeben Fehlercode auswertet
*
*   param[in]    Err-Code		
*
*   author       Simon Böhmisch
*********************************************************************************************************************/
void Auswertung_Fehlercode(int Err_Code)
{
	/* Ausgabe der Nullstelle */
	if (Err_Code == E_OK)
	{
		printf("x = %.3f ist die Nullstelle\n", Nullstelle);
	}
	/* Fehler bei der Berechnung */
	if (Err_Code == E_NAN)
	{
		printf("UEBERLAUF\n");
	}
	/* Bisektionsverfahren kann im angegeben Bereich keine Nullstelle berechnen*/
	if (Err_Code == E_PARAMETER)
	{
		printf("Für die uebergebene Funktion kann die Bisektion in dem Intervall zwischen %.3f und %.5f keine Nullstelle bestimmen\n", X_left, X_right);
	}
	/* Maximale Anzahl der Berechnungen wurde ueberschritten */
	if (Err_Code == E_BERECHNUNG)
	{
		printf("Maximale Iterationszahl wurde ueberschritten, es wurde keine Nullstelle gefunden\n");
	}
	printf("\n");
}

/**********************************************************************************************************************
EOF
**********************************************************************************************************************/