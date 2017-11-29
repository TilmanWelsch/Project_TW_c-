/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Labor Software Engineering --- Abschlussprojekt
//					Dozent:		Prof. Harig
//					Autor:		Tilman Welsch
//					Matr.-Nr.:	754042	
//----------------------------------------------------------------------------------------------
//			Aenderungen:
//					Datum:		16.05.2017					- Projektbeginn (Klassen und 
//															  Konstruktoren erstellt)
//								17.05.2017					- BasisStruktur für alle Menuepunkte
//								20.05.2017					- Menuepunkte fertiggestellt
//								23.05.2017					- Fehler behoben

#include "stdafx.h"
using namespace std;
#include <iostream>
#include <string.h>
#include <iomanip>

class CPerson //SuperClass for Technician and Client - no instances needed
{
public:
	//Constructors and Deconstructors
	CPerson(){}
	~CPerson(){}
	CPerson(char*, unsigned long int);

	virtual char* GetPersonName() = 0;
	virtual unsigned long int GetPersonNmbr() = 0;
	virtual void PrintPerson() = 0;
protected:
	char namePerson[50];
	unsigned long int personNmbr;
};
CPerson::CPerson(char* pNamePerson, unsigned long int hPersonNmbr)
{
	strcpy_s(namePerson, pNamePerson);
	personNmbr = hPersonNmbr;
}

class CTechnician : public CPerson		//SubClass of CPerson
{
public:
	//Constructors and Deconstructors
	CTechnician(){}
	~CTechnician(){}
	CTechnician(char*, unsigned long int, float);		//Constructor with usage of SuperClass' Const.

	char* GetPersonName(){ return namePerson; }
	unsigned long int GetPersonNmbr(){ return personNmbr; }
	float GetWage(){ return techWage; }

	void PrintPerson();
protected:
	float techWage;
};
CTechnician::CTechnician(char* pNamePerson, unsigned long int hPersonNmbr, float hTechWage) : CPerson(pNamePerson, hPersonNmbr)
{
	techWage = hTechWage;
}
void CTechnician::PrintPerson()
{
	cout << GetPersonNmbr() << "\t" << GetPersonName() << "\t";
	cout << fixed << setprecision(2) << GetWage();
	cout << " EUR\n";
}

class CClient : public CPerson			//SubClass of CPerson
{
public:
	//Constructors and Deconstructors
	CClient(){}
	~CClient(){}
	CClient(char*, unsigned long int, float);		//Constructor with usage of SuperClass' Const.

	char* GetPersonName(){ return namePerson; }
	unsigned long int GetPersonNmbr(){ return personNmbr; };
	float GetDistance(){ return distance; }

	void PrintPerson();
protected:
	float distance;
};
CClient::CClient(char* pNamePerson, unsigned long int hPersonNmbr, float hDistance) :CPerson(pNamePerson, hPersonNmbr)
{
	distance = hDistance;
}
void CClient::PrintPerson()
{
	cout << GetPersonNmbr() << "\t" << GetPersonName() << "\t";
	cout << fixed << setprecision(2) << GetDistance();
	cout << " km\n";
}

class COperation						//SuperClass of Special Operations
{
public:
	//Constructors and Deconstructors
	COperation(){}
	~COperation(){}
	COperation(unsigned long int, unsigned long int, unsigned long int, float);
	//Methods
	void PrintOp();
	unsigned long int GetOperationNmbr(){ return operationNmbr; }
	unsigned long int GetClientNmbr(){ return clientNmbr; }
	unsigned long int GetTechnicianNmbr(){ return technicianNmbr; }
	float GetWorkHours(){ return workHours; }
protected:
	unsigned long int operationNmbr, clientNmbr, technicianNmbr;
	float workHours;
};
COperation::COperation(unsigned long int hOpNmbr, unsigned long int hClientNmbr, unsigned long int hTechNmbr, float hWorkHours)
{
	operationNmbr = hOpNmbr;
	clientNmbr = hClientNmbr;
	technicianNmbr = hTechNmbr;
	workHours = hWorkHours;
}
void COperation::PrintOp()
{
	cout << GetOperationNmbr() << "\t" << GetClientNmbr() << "\t" << GetTechnicianNmbr() << "\t" << GetWorkHours() << "\n\n";
}

class CSpecialOperation : public COperation	//SubClass of COperation
{
public:
	//Constructors and Deconstructors
	CSpecialOperation(){}
	~CSpecialOperation(){}
	CSpecialOperation(unsigned long int, unsigned long int, unsigned long int, float,
		unsigned int d, unsigned int m, unsigned int y, float);
	//Methods
	unsigned int GetDay(){ return day; }
	unsigned int GetMonth(){ return month; }
	unsigned int GetYear(){ return year; }
	float GetAddFactor(){ return addFactor; }
	void SetSpecialOperation();
protected:
	unsigned int day, month, year;
	float addFactor;
};
CSpecialOperation::CSpecialOperation(unsigned long int hOpNmbr, unsigned long int hClientNmbr, unsigned long int hTechNmbr,
	float hWorkHours, unsigned int hDay, unsigned int hMonth, unsigned int hYear, float hAddFactor) : COperation(hOpNmbr, hClientNmbr, hTechNmbr, hWorkHours)
{
	day = hDay;
	month = hMonth;
	year = hYear;
	addFactor = hAddFactor;
}


class CPlanning
{
public:
	//Constructors and Deconstructors
	CPlanning();
	~CPlanning(){}
	//Menue - Methoden
	void StartProject();
	void NewOperation();
	void DeleteOperation();
	void OverView();
	void Bill();
	void PrintTechsAndClients();
	//Calls and operations
	void CallPrintPerson(CPerson &x){ x.PrintPerson(); }		//Aufruf virtuelle Methode zur Ausgabe Personen
	bool TechExisting(unsigned long int hTechNmbr);
	bool ClientExisting(unsigned long int hClientNmbr);
	bool OperationExisting(unsigned long int hOpNmbr); //Hier Unterscheidung mit Operations und SOps einbauen
	unsigned int GetTechPosByNmbr(unsigned long int);
	unsigned int GetClientPosByNmbr(unsigned long int);
	unsigned int GetNextFreeOpPos();
	unsigned int GetNextFreeSOpPos();
protected:
	CTechnician tech[4];
	CClient		client[8];
	COperation operation[50];
	CSpecialOperation sOperation[50];
};

CPlanning::CPlanning()
{
	tech[0] = CTechnician("Mueller", 111UL, 21.30f);
	tech[1] = CTechnician("Maier", 113UL, 19.10f);
	tech[2] = CTechnician("Krause", 119UL, 25.80f);
	tech[3] = CTechnician("Koenig", 123UL, 21.30f);

	client[0] = CClient("KALOGA", 11UL, 68.00f);
	client[1] = CClient("KELS", 13UL, 158.00f);
	client[2] = CClient("MUKKI", 17UL, 230.00f);
	client[3] = CClient("ARENA", 19UL, 108.00f);
	client[4] = CClient("BALLA", 23UL, 17.00f);
	client[5] = CClient("SANSI", 29UL, 74.00f);
	client[6] = CClient("DRUM", 31UL, 358.00f);
	client[7] = CClient("HELLA", 37UL, 45.00f);

	//Operations und SpecialOperations mit Nullen vorbelegen
	for (int i = 0; i < 50; i++)
	{
		operation[i] = COperation(0UL, 0UL, 0UL, 0.0f);
	}
	for (int i = 0; i < 50; i++)
	{
		sOperation[i] = CSpecialOperation(0UL, 0UL, 0UL, 0.0f, 0U, 0U, 0U, 0.0f);
	}
};

void CPlanning::StartProject()
{
	int input = 50;	//Koennte auch weggelassen werden
	do
	{
		cout << "\nMENUE\n1. Neuen Einsatz festlegen\n2. Einsatz loeschen\n3. Uebersicht\n4. Rechnung\n"
			<< "5. Liste aller Techniker und Kunden\n0. Programmende" << "\n\n(Stellen der Ident Nummern: Techniker 3, "
			<< "Kunden 2, Einsaetze 1\nIdentnummern immer nur einmal vergeben!)\n";
		cin >> input;

		if (input == 1)
		{
			NewOperation();
		}
		else if (input == 2)
		{
			DeleteOperation();
		}
		else if (input == 3)
		{
			OverView();
		}
		else if (input == 4)
		{
			Bill();
		}
		else if (input == 5)
		{
			PrintTechsAndClients();
		}
		else if (input == 0)
		{
			break;
		}
		else
		{
			cout << "\n\n Dieser Programmpunkt existiert nicht. Bitte einen vorhandenen waehlen!";
		}
	} while (input != 0);
}

void CPlanning::NewOperation()
{
	unsigned long int opNmbr, clNmbr, techNmbr;
	unsigned int whichOperation, hDay, hMonth, hYear, position;
	float hours;
	cout << "\nGewaehlter Menuepunkt: 1\n"
		<< "\nBitte Einsatznummer vergeben:\t";
	cin >> opNmbr;
	cout << "\n\nBitte Art des Einsatzes waehlen:"
		<< "\n1. Normaler Einsatz\n2. Spezialeinsatz\n";
	cin >> whichOperation;
	// Zeige Alle Kunden
	for (int i = 0; i < 8; i++)
	{
		CallPrintPerson(client[i]);
	}
	if (whichOperation == 1) //Normaler Einsatz
	{
		cout << "\nKundennummer: ";
		cin >> clNmbr;
		for (int i = 0; i < 4; i++)
		{
			CallPrintPerson(tech[i]);
		}
		cout << "\nTechnikernummer: ";
		cin >> techNmbr;
		cout << "\nStundenzahl: ";
		cin >> hours;
		position = GetNextFreeOpPos();
		operation[position] = COperation(opNmbr, clNmbr, techNmbr, hours);
	}
	else if (whichOperation == 2) //Spezialeinsatz
	{
		cout << "\nKundennummer: ";
		cin >> clNmbr;
		for (int i = 0; i < 4; i++)
		{
			CallPrintPerson(tech[i]);
		}
		cout << "\nTechnikernummer: ";
		cin >> techNmbr;
		cout << "\nStundenzahl: ";
		cin >> hours;
		cout << "\nBitte Tag, Monat und Jahr eingeben (TT *Enter* MM *Enter* JJJJ *Enter*): ";
		cin >> hDay >> hMonth >> hYear;
		float hAddFactor;
		cout << "\nBitte den Zuschlagsfaktor eingeben: ";
		cin >> hAddFactor;
		position = GetNextFreeSOpPos();
		sOperation[position] = CSpecialOperation(opNmbr, clNmbr, techNmbr, hours, hDay, hMonth, hYear, hAddFactor);
	}
	else
	{
		cout << "\n\nDer gewaehlte Einsatz existiert nicht.";
	}
}

void CPlanning::DeleteOperation()
{
	unsigned long int opNmbr;
	cout << "\nGewaehlter Menuepunkt: 2\n";
	//Alle Einsaetze anzeigen (wie menue3)
	cout << "\nNummer des Einsatzes:\t";
	cin >> opNmbr;
	for (int i = 0; i < 50; i++)
	{
		if (operation[i].GetOperationNmbr() == opNmbr)
		{
			cout << "\nStandardeinsatz (1) mit der Nummer " << operation[i].GetOperationNmbr() << " wurde geloescht.\n";
			operation[i] = COperation(0UL, 0UL, 0UL, 0.0f);
			break;
		}
		else if (sOperation[i].GetOperationNmbr() == opNmbr)
		{
			cout << "\nSpezialeinsatz (2) mit der Nummer " << sOperation[i].GetOperationNmbr() << " wurde geloescht.\n";
			sOperation[i] = CSpecialOperation(0UL, 0UL, 0UL, 0.0f, 0U, 0U, 0U, 0.0f);
			break;
		}
	}
}

void CPlanning::OverView()
{
	cout << "\nGewaehlter Menuepunkt: 3\n";
	cout << "\nEinsaetze"
		<< "\nNummer \tTechniker \tKunde \tStunden \tDatum\n\n";

	int hTNmbr, hCNmbr;
	if (operation[0].GetOperationNmbr() == 0 && sOperation[0].GetOperationNmbr() == 0)
		cout << "Keine Einsaetze und keine Spezialeinsaetze vorhanden.\n";
	else
	{
		for (int i = 0; i < 50; i++)
		{
			if (operation[i].GetOperationNmbr() != 0)
			{
				hTNmbr = operation[i].GetTechnicianNmbr();
				hCNmbr = operation[i].GetClientNmbr();
				cout << operation[i].GetOperationNmbr() << "\t"
					<< tech[GetTechPosByNmbr(hTNmbr)].GetPersonName() << "\t\t"
					<< client[GetClientPosByNmbr(hCNmbr)].GetPersonName() << "\t"
					<< operation[i].GetWorkHours() << "\n";
			}
			else
				break;
		}

		for (int i = 0; i < 50; i++)
		{
			if (sOperation[i].GetOperationNmbr() != 0)
			{
				hTNmbr = sOperation[i].GetTechnicianNmbr();
				hCNmbr = sOperation[i].GetClientNmbr();
				cout << sOperation[i].GetOperationNmbr() << "\t"
					<< tech[GetTechPosByNmbr(hTNmbr)].GetPersonName() << "\t\t"
					<< client[GetClientPosByNmbr(hCNmbr)].GetPersonName() << "\t"
					<< sOperation[i].GetWorkHours() << "\t\t" << sOperation[i].GetDay() << "."
					<< sOperation[i].GetMonth() << "." << sOperation[i].GetYear() << "\n";
			}
			else
				break;
		}
	}
}

void CPlanning::Bill()
{
	unsigned long int opNmbr;
	unsigned int whichOp = 0;	//1 for operation, 2 for sOperation
	int opPos = 51, hCNmbr, hTNmbr;
	float distancePrice, workPrice, addPrice, allPrice;

	cout << "\nGewaehlter Menuepunkt: 4\n"
		<< "\nBitte Einsatznummer eingeben:\t";

	cin >> opNmbr;

	for (int i = 0; i < 50; i++)
	{
		if (opNmbr == 0)
		{
			cout << "\nEs gibt weder Einsatz noch Spezialeinsatz mit der Nummer 0.\n";
			break;
		}
		else
		{
			if (operation[i].GetOperationNmbr() == opNmbr)
			{
				whichOp = 1;
				opPos = i;
				break;
			}
			else if (sOperation[i].GetOperationNmbr() == opNmbr)
			{
				whichOp = 2;
				opPos = i;
				break;
			}
		}
	}

	//Print
	if (whichOp == 1)
	{
		hTNmbr = operation[opPos].GetTechnicianNmbr();
		hCNmbr = operation[opPos].GetClientNmbr();
		distancePrice = client[GetClientPosByNmbr(hCNmbr)].GetDistance() * 0.25f;
		workPrice = tech[GetTechPosByNmbr(hTNmbr)].GetWage() * operation[opPos].GetWorkHours();
		allPrice = distancePrice + workPrice;
		cout << "Einsatznummer:\t" << operation[opPos].GetOperationNmbr() << "\n"
			<< "Kunde:\t\t" << client[GetClientPosByNmbr(hCNmbr)].GetPersonName() << "\n"
			<< "Techniker:\t" << tech[GetTechPosByNmbr(hTNmbr)].GetPersonName() << "\n"
			<< "Stunden:\t" << operation[opPos].GetWorkHours() << "\n"
			<< "Lohn:\t\t" << workPrice << "\n"
			<< "Fahrtkosten:\t" << distancePrice << "\n"
			<< "Gesamtkosten:\t" << allPrice << "\n";
	}
	else if (whichOp == 2)
	{
		hTNmbr = sOperation[opPos].GetTechnicianNmbr();
		hCNmbr = sOperation[opPos].GetClientNmbr();
		distancePrice = client[GetClientPosByNmbr(hCNmbr)].GetDistance() * 0.25f;
		workPrice = tech[GetTechPosByNmbr(hTNmbr)].GetWage() * sOperation[opPos].GetWorkHours();

		addPrice = distancePrice + workPrice;
		allPrice = sOperation[opPos].GetAddFactor() * addPrice + addPrice;

		cout << "Einsatznummer:\t" << operation[opPos].GetOperationNmbr() << "\n"
			<< "Kunde:\t\t" << client[GetClientPosByNmbr(hCNmbr)].GetPersonName() << "\n"
			<< "Techniker:\t" << tech[GetTechPosByNmbr(hTNmbr)].GetPersonName() << "\n"
			<< "Stunden:\t" << operation[opPos].GetWorkHours() << "\n"
			<< "Lohn:\t\t" << workPrice << "\n"
			<< "Fahrtkosten:\t" << distancePrice << "\n"
			<< "Gesamtkosten:\t" << addPrice << "\n"
			<< "Mit Zuschlag:\t" << allPrice << "\n";
	}
	else
		cout << "\nDer gewaehlte Einsatz existiert nicht.\n";
}

void CPlanning::PrintTechsAndClients()
{
	cout << "\nGewaehlter Menuepunkt: 5\n";
	cout << "\nTechniker"
		<< "\nNummer \tName \tStundenlohn\n\n";
	for (int i = 0; i < 4; i++)
	{
		CallPrintPerson(tech[i]);
	}
	cout << "\n\nKunden"
		<< "\nNummer \tName \tEntfernung\n\n";
	for (int i = 0; i < 8; i++)
	{
		CallPrintPerson(client[i]);
	}
}

unsigned int CPlanning::GetTechPosByNmbr(unsigned long int hNmbr)
{
	int position = 0;
	for (int i = 0; i < 4; i++)
	{
		if (tech[i].GetPersonNmbr() == hNmbr)
		{
			position = i;
			break;
		}
	}
	return position;
}
unsigned int CPlanning::GetClientPosByNmbr(unsigned long int hNmbr)
{
	int position = 0;
	for (int i = 0; i < 8; i++)
	{
		if (client[i].GetPersonNmbr() == hNmbr)
		{
			position = i;
			break;
		}
	}
	return position;
}

unsigned int CPlanning::GetNextFreeOpPos()
{
	int position = 0;
	for (int i = 0; i < 50; i++)
	{
		if (operation[i].GetOperationNmbr() == 0)
		{
			position = i;
			break;
		}
	}
	return position;
}
unsigned int CPlanning::GetNextFreeSOpPos()
{
	int position = 0;
	for (int i = 0; i < 50; i++)
	{
		if (sOperation[i].GetOperationNmbr() == 0)
		{
			position = i;
			break;
		}
	}
	return position;
}

//ABSICHERUNGEN GEGEN FALSCHEINGABE
// -------------------------------
//bool CPlanning::TechExisting(unsigned long int hTechNmbr)	
//{
//	bool existing;
//	if (GetTechPosByNmbr(hTechNmbr))
//		existing = true;
//	else
//		existing = false;
//	return existing;
//}
//
//bool CPlanning::ClientExisting(unsigned long int hClientNmbr)
//{
//	bool existing;
//	if (GetClientPosByNmbr(hClientNmbr))
//		existing = true;
//	else
//		existing = false;
//	return existing;
//}
//
////Fuer DeleteOperation
//bool CPlanning::OperationExisting(unsigned long int hOperation)
//{
//	bool existing;
//	if (hOperation>999 && hOperation < 1008)
//		existing = true;
//	else
//		existing = false;
//	return existing;
//}

int _tmain(int argc, _TCHAR* argv[])
{
	CPlanning daten;
	daten.StartProject();
	return 0;
}