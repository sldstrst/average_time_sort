#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <ctime>
#include <iomanip>

using namespace std;
using std::time;

//сортировка Шейкером
void shekerSort(unsigned int* mas, unsigned int col)
{
	int left = 0, right = col - 1; // левая и правая границы сортируемой области массива
	bool flag = true;  // флаг наличия перемещений
					   // Выполнение цикла пока левая граница не сомкнётся с правой
					   // или пока в массиве имеются перемещения
	while ((left < right) && flag)
	{
		flag = false;
		for (int i = left; i < right; i++)  //двигаемся слева направо
		{
			if (mas[i] > mas[i + 1]) // если следующий элемент меньше текущего,
			{             // меняем их местами
				int t = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = t;
				flag = true;      // перемещения в этом цикле были
			}
		}
		right -= 1; // сдвигаем правую границу на предыдущий элемент
		for (int i = right; i > left; i--)  //двигаемся справа налево
		{
			if (mas[i - 1] > mas[i]) // если предыдущий элемент больше текущего,
			{            // меняем их местами
				int t = mas[i];
				mas[i] = mas[i - 1];
				mas[i - 1] = t;
				flag = true;    // перемещения в этом цикле были
			}
		}
		left++; // сдвигаем левую границу на следующий элемент
	}
}

//сортировка пузырьком
void sortPuz(unsigned int* mas, unsigned int col)
{
	unsigned int per = 0;
	for (int j = 0; j < col; j++)
	{
		for (int g = 0; g < col - 1; g++)
		{
			if (mas[g] > mas[g + 1])
			{
				per = mas[g];   //       1 = 2
				mas[g] = mas[g + 1]; //  2 = 3
				mas[g + 1] = per;//      3 = 1
			}
		}
	}
}

//вывод на экран
void inp(unsigned int* mas, unsigned int col)
{
	for (int k = 0; k < col; k++)
	{
		cout << mas[k] << " ";
	}
	cout << endl;
}

// заполнение массива случайными числами
void rand(unsigned int* mas, unsigned int col, int m)
{
	for (int i = 0; i < col; i++)
	{
		mas[i] = rand() % 10 + m;
	}
}

//сортировка включением (вставки)
void sortInsert(unsigned int* mas, unsigned int col) // сортировка вставками
{
	unsigned int temp;// temp - временная переменная для хранения значения элемента сортируемого массива
	for (int i = 1; i < col; i++)
	{
		temp = mas[i]; // инициализируем временную переменную текущим значением элемента массива
		while (i >= 1 && mas[i - 1] > temp) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
		{
			mas[i] = mas[i - 1]; // перестановка элементов массива
			mas[i - 1] = temp;
			i--;
		}
	}
}

//сортировка расчёска
void sortRascheska(unsigned int* mas, unsigned int col)
{
	double fakt = 1.2;
	unsigned int help = col;
	unsigned int step = col;
	int n = 0;
	while (step > 1)
	{
		for (int i = 0; i + step < col; ++i)
		{
			if (mas[i] > mas[i + step])
			{
				swap(mas[i], mas[i + step]);
				n++;
			}
		}
		help /= (fakt);
		step = static_cast<int>(help);
	}
}

//сортировка Гномья
void sortGnom(unsigned int* mas, unsigned int col)
{
	unsigned int in = 0, per = 0;
	while (in < col)
	{
		if (in == 0 || mas[in - 1] <= mas[in])
			++in;
		else
		{
			per = mas[in];
			mas[in] = mas[in - 1];
			mas[in - 1] = per;
			--in;
		}
	}
}

//сортировка Шилла
void sortShell(unsigned int* mas, unsigned int col)
{
	unsigned int step = col / 2;
	while (step > 0)
	{
		int i, j;
		for (i = step; i < col; i++)
		{
			int value = mas[i];
			for (j = i - step; (j >= 0) && (mas[j] > value); j -= step)
				mas[j + step] = mas[j];
			mas[j + step] = value;
		}
		step /= 2;
	}
}

//удаление выделенной памяти под массив
void fre(unsigned int* mas)
{
	delete[]mas;
}

//функция вызова функций сртировки для подсчёта времени выполнения этих функций
float coffee(unsigned int* mas, unsigned int col, int menu)
{
	unsigned int so = 10;
	float name = 0.0f;
	void(*ukMas[7])(unsigned int*, unsigned int) = { inp, sortPuz, sortInsert, sortRascheska, shekerSort, sortGnom,sortShell };
	clock_t start, finish;
	for (int i = 1; i <= 6; i++)
	{
		unsigned int* mas = new unsigned int[col];
		rand(mas, col, so);
		start = clock();
		ukMas[menu](mas, col);
		finish = clock();
		name = (float)(finish - start) / CLOCKS_PER_SEC;
		free(mas);
	}
	return name / 6;
}

void graf(unsigned int* mas, unsigned int col, int so, float tabl)
{
	unsigned int* arr = new unsigned int[5];
	float* time = new float[5];
	for (int i = 0; i < 5; i++)
	{
		tabl = coffee(mas, col, so);
		col = col * 10;
		arr[i] = col;
		time[i] = tabl;
	}
	cout << "Количество элементов в массиве" << setw(4) << "|" << "Cреднее время обработки" << endl;
	cout << "/--------------------------------------------------------\\" << endl;
	for (int k = 0; k < 5; k++)
	{
		cout << "|" << left << setw(32) << arr[k] << "|" << setw(23) << fixed << setprecision(6) << time[k] << "|" << endl;
	}
	cout << "\\--------------------------------------------------------/" << endl;
	delete[]arr;
	delete[]time;
}



//главная функция
int main()
{
	setlocale(0, "");
	clock_t start, finish;
	bool bMenu = true;
	float tabl = 0.0;
	unsigned int col = 1, m = 0;
	//выделение динамической памяти под массив, в котором количество элементов равно col 
	unsigned int* mas = new unsigned int[col];
	int menu = 0;

	//массив указателей на функции
	void(*ukMas[7])(unsigned int*, unsigned int) = { inp, sortPuz, sortInsert, sortRascheska, shekerSort, sortGnom,sortShell };
	while (bMenu)
	{
		//cout << "\nВведите размерность массива:";
		//cin >> col;
		//меню
		cout << "Меню" << endl;
		cout << "1 - Метод Пузырька" << endl;
		cout << "2 - Метод Вставки" << endl;
		cout << "3 - Метод Расчёски" << endl;
		cout << "4 - Метод Шейкера" << endl;
		cout << "5 - Метод Гномья" << endl;
		cout << "6 - Метод Шелла" << endl;
		cout << "7 - Выход" << endl;
		//выбор пункта меню
		cout << "Выберите пункт меню:";
		cin >> menu;
		int so = menu;
		switch (menu)
		{
		case 1:
		{
			graf(mas, col, so, tabl);

		}break;
		case 2:
		{
			graf(mas, col, so, tabl);
		}break;
		case 3:
		{
			graf(mas, col, so, tabl);
		}break;
		case 4:
		{
			graf(mas, col, so, tabl);
		}break;
		case 5:
		{
			graf(mas, col, so, tabl);
		}break;
		case 6:
		{
			graf(mas, col, so, tabl);
		}break;
		case 7:
		{
			fre(mas);
			bMenu = false;
		}break;
		}

	}
	cin.get();
	return 0;
}