#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <windows.h> //графический режим
#include <math.h> // математические функции

#define PI 3.14159

struct complex
{
	double	real; 
	double	imag;
};


void write_result(double* res_data, int argc, const char* s) {
	int i;

	std::ofstream file_res(s);//каждый раз будет создаваться и перезаписываться
	for (i = 1; i < argc; i++)
		file_res << res_data[i] << " " << std::endl;
	file_res.close();
}

void count_dft(double* Seq, int argc) {
	double*	Amplitude;
	struct complex* one;       // Отдельные данные
	struct complex sum;        // суммированный результат
	int i;

	Amplitude = new double[argc];
	one = new complex[argc];

	for (i = 0; i < argc; i++) {
		sum.real = 0;
		sum.imag = 0;
		for (int j = 0; j < argc; j++) {
			one[j].real = cos(2 * PI / argc * i * j) * Seq[j];
			one[j].imag = -sin(2 * PI / argc * i * j) * Seq[j];

			sum.real += one[j].real;
			sum.imag += one[j].imag;
		}
		Amplitude[i] = sqrt(sum.real * sum.real + sum.imag * sum.imag);
	}

	write_result(Amplitude, argc, "result.txt");
	write_result(Seq, argc, "adddata.txt");
	delete[] Amplitude;
	delete[] one;
}


// главная программа
#pragma comment(lib,"graphics.lib")
int main(void)
{
	setlocale(LC_ALL, "Russian");
	int count = 0; 
	int i = 0;
	double sum_arg = 0;
	double* user_data;

	std::cout << "Введите приблизительное количество данных: ";
	std::cin >> count;
	std::cout << "Введите основные данные" << std::endl;
	user_data = new double[count + 1];
	for (i = 0; i < count; i++)
	{
		std::cin >> user_data[i];
		sum_arg += user_data[i];
	}
	sum_arg /= i;
	for (int j = 0; j < i; j++)
	{
		user_data[j] -= sum_arg;
	}

	count_dft(user_data, i);

	delete[] user_data;
	return (0);
}