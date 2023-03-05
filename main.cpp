#include "vector.h"
#include "matrix.h"
#include "Complex.h"
#include "MathVector.h"
#include "MathMatrix.h"
#include <string>
#include <iostream>

using namespace std;
//	******************************************************************************************
//	Declaration of used functions
MathVector create_vector(int opt);
MathMatrix create_matrix(int opt);
void error(exception& e);
char save_question();
//	******************************************************************************************

int main()
{
	//	******************************************************************************************
	//	Question to user which operation he wants to choose and inputing his choice.
	int option1;
	do{
		cout << "Wybierz opcje: " << endl;
		cout << "1 - Liczenie normy wektora" << endl;
		cout << "2 - Liczenie normy macierzy" << endl;
		cout << "3 - Mnozenie macierz x macierz" << endl;
		cout << "4 - Mnozenie macierz x wektor" << endl;
		cout << "5 - Liczenie macierzy trojkatnej dolnej L" << endl;
		cout << "6 - Liczenie macierzy trojkatnej Gornej U" << endl;
		cout << "7 - Liczenie macierzy odwrotnej" << endl;
		cout << "8 - Licznie wyznacznika macierzy" << endl;
		cout << "9 - Podanie rozmiaru macierzy" << endl;
		cout << "10 - Exit " << endl;
		cin >> option1;

		//	******************************************************************************************

		//	******************************************************************************************
		//	Loop which checking if inputed choice is possible or not.
		if (option1 < 1 || option1 >= 10 || cin.fail())
		{
			if (option1 == 10)
			{
				break;
			}
			cout << "Invalid argument";
			break;
		}
		//	******************************************************************************************

		//	******************************************************************************************
		//	Question about source of data.
		int option2;
		cout << "\nW jaki sposob chcesz wprowadzic dane ?: " << endl;
		cout << "1 - z klawiatury" << endl;
		cout << "2 - z pliku" << endl;
		cin >> option2;
		system("cls");
		//	******************************************************************************************

		//	******************************************************************************************
		//	Loop which checking inputed choice about source of data and craeting appropriate objects.
		MathVector V;
		MathMatrix M1, M2;
		if (option1 == 1 || option1 == 4)
		{
			if (option1 == 4)
			{
				MathMatrix m = create_matrix(option2);
				M1 = m;
			}
			MathVector v = create_vector(option2);
			V = v;
		}
		else
		{
			MathMatrix m = create_matrix(option2);
			M1 = m;
			if (option1 == 3)
			{
				MathMatrix m = create_matrix(option2);
				M2 = m;
			}
		}

		char option3;
		ofstream ofs("Result.dat");
		//	******************************************************************************************

		//	******************************************************************************************
		//	Function switch - fulfil choosen option
		switch (option1)
		{
		case 1:
			cout << "Normy wynosza:" << endl;
			try
			{
				cout << "Pierwsza norma: " << V.one_norm() << endl;
				cout << "Druga norma: " << V.two_norm() << endl;
				cout << "Trzecia norma: " << V.uniform_norm() << endl;
			}
			catch (exception& e) { error(e); }
			
				option3 = save_question();
				
				if (option3 == 't' || option3 == 'T')
				{
					ofs << "Normy wynosza:" << endl;
					ofs << "Pierwsza norma: " << V.one_norm() << endl;
					ofs << "Druga norma: " << V.two_norm() << endl;
					ofs << "Trzecia norma: " << V.uniform_norm() << endl;
				}
			break;
		case 2:
			cout << "Normy macierzowe wynosza: " << endl;
				cout << "Pierwsza norma: " << M1.one_norm() << endl;
				cout << "Druga norma: " << M1.two_norm() << endl;
				cout << "Trzecia norma: " << M1.uniform_norm() << endl;
				option3 = save_question();
				if (option3 == 't' || option3 == 'T')
				{
					ofs << "Normy macierzowe wynosza: " << endl;
					ofs << "Pierwsza norma: " << M1.one_norm() << endl;
					ofs << "Druga norma: " << M1.two_norm() << endl;
					ofs << "Trzecia norma: " << M1.uniform_norm() << endl;
				}
			break;
		case 3:
			cout << "Wynik mnozenia macierz x macierz: " << endl;
			try
			{
				cout << M1*M2 << endl;
			}
			catch (exception& e) { error(e); }
			option3 = save_question();
			if (option3 == 't' || option3 == 'T')
			{
				ofs << "Wynik mnozenia macierz x macierz: " << endl;
				ofs << M1*M2 << endl;
			}
			break;
		case 4:
			cout << "Wynik mnozenia macierz x wektor: " << endl;
			try
			{
				cout << M1*V << endl;
			}
			catch (exception& e) { error(e); }
			option3 = save_question();
			if (option3 == 't' || option3 == 'T')
			{
				ofs << "Wynik mnozenia macierz x wektor: " << endl;
				ofs << M1*V << endl;
			}
			break;
		case 5:
			cout << "Macierz trojkatna dolna L: " << endl;
			try
			{
				cout << M1.compute_lower() << endl;

			}
			catch (exception& e) { error(e); }
			option3 = save_question();
			if (option3 == 't' || option3 == 'T')
			{
				ofs << "Macierz trojkatna dolna L: " << endl;
				ofs << M1.compute_lower() << endl;
			}
			break;
		case 6:
			cout << "Macierz trojkatna gorna U: " << endl;
			try
			{
				cout << M1.compute_upper() << endl;
				
			}
			catch (exception& e) { error(e); }
			option3 = save_question();
			if (option3 == 't' || option3 == 'T')
			{
				ofs << "Macierz trojkatna gorna U" << endl;
				ofs << M1.compute_upper() << endl;
			}
			break;
		case 7:
			cout << "Macierz odwrotna: " << endl;
			try
			{
				cout << M1.inverse() << endl;
			}
			catch (exception& e) { error(e); }
			option3 = save_question();
			if (option3 == 't' || option3 == 'T')
			{
				ofs << "Macierz odwrotna: " << endl;
				ofs << M1.inverse() << endl;
			}
			break;
		case 8:
			cout << "Wyznacznik macierzy:" << endl;
			try
			{
				cout << M1.condition_num() << endl;
			}
			catch (exception& e) { error(e); }
			option3 = save_question();
			if (option3 == 't' || option3 == 'T')
			{
				ofs << "Wyznacznik macierzy: " << endl;
				ofs << M1.condition_num() << endl;
			}
			break;
		case 9:
			cout << "Rozmiar macierzy wynosi: " << endl;
			try
			{
				cout << M1.get_size() << endl;
			}
			catch (exception& e) { error(e); }
			option3 = save_question();
			if (option3 == 't' || option3 == 'T')
			{
				ofs << "Rozmiar macierzy wynosi: " << endl;
				ofs << M1.get_size() << endl;
			}
			break;
		default:
			break;
		}
		cout << "\nNacisniej dowolny przycisk aby powrocic do menu" << endl;
		system("Pause");
		system("cls");
	} while (!(option1 == 10));
	return 0;
}//	******************************************************************************************
//	*****************************************	END OF MAIN PART OF PROGRAM		*****************************************	//

//	******************************************************************************************
//	Function which create appropriate MathVector object dependent of inputed source of data
MathVector create_vector(int opt)
{
	MathVector v1;
	try
	{
		if (opt == 1)
		{
			cin >> v1;
		}
		else if (opt == 2)
		{
			string name;
			cout << "Stworz plik z rozmiarem wektora i danymi i podaj jego nazwe w formacie: MyVector.dat " << endl;
			cin >> name;
			ifstream ifs(name);
			ifs >> v1;
		}
	}
	catch (exception& e) { error(e); }
	return v1;
}
//	******************************************************************************************

//	******************************************************************************************
//	Function which create appropriate MathMatrix object dependent of inputed source of data
MathMatrix create_matrix(int opt)
{
	MathMatrix m1;
	try
	{
		if (opt == 1)
		{
			cin >> m1;
		}
		else if (opt == 2)
		{
			string name;
			cout << "Stworz plik z rozmiarem macierzy i danymi i podaj jego nazwe w formacie: MyMatrix.dat " << endl;
			cin >> name;
			ifstream ifs(name);
			ifs >> m1;
		}
	}
	catch (exception& e) { error(e); }
	return m1;
}
//	******************************************************************************************

//	******************************************************************************************
//	Function which is called when exception is catched
void error(exception& e)
{
	cerr << "\nException caught" << endl;
	cerr << "Type: " << typeid(e).name() << endl;
	cerr << "What: " << e.what() << endl;
	system("pause");
	exit(1);
}
//	******************************************************************************************

//	******************************************************************************************
//	Function which ask user if he wants to save his results, taking his choice and gives it to program
char save_question()
{
	char k;
	do{
		cout << "Czy chcesz zapisac wyniki do pliku ? <T/N>";
		cin >> k; 
		if (k == 't' || k == 'T' || k == 'n' || k == 'N')
		{
			return k;
		}
	} while (!(k == 't' || k == 'T' || k == 'n' || k == 'N'));
}
//	******************************************************************************************