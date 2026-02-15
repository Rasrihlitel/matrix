#include <iostream>
#include <stdlib.h>

using namespace std;
void hello(int& code) {
	cout << "0. Выход" << endl;
	cout << "1. Создать матрицу" << endl;
	cout << "2. Вывести на экран матрицу" << endl;
	cout << "3. Создать вектор" << endl;
	cout << "4. Вывести на экран вектор" << endl;
	cout << "5. Умножение матрицы на вектор" << endl;
	cout << "6. Транспонирование матрицы" << endl;
	cout << "7. Нахождение седловых элементов матрицы" << endl;
	cout << "Ваш выбор: ";
	cin >> code;
}

void outmatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		cout << "| ";
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << "|" << endl;
	}
}

void outvector(int* vector, int n) {
	for (int i = 0; i < n; i++) {
		cout << "| " << vector[i] << " |" << endl;
	}
}

int** create_matrix(int** matrix, int n) {
	matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
	}
	return matrix;
}

int* create_vector(int* vector, int n) {
	vector = new int[n];
	return vector;
}

void insertmatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 1 + rand() % 100;
		}
	}
}

void insertvector(int* vector, int n) {
	for (int i = 0; i < n; i++) {
		vector[i] = 1 + rand() % 100;
	}
}

int* multiplication(int** matrix, int* vector, int n) {
	int* res = new int[n];
	for (int i = 0; i < n; i++) {
		res[i] = 0;
		for (int j = 0; j < n; j++) {
			res[i] += matrix[i][j] * vector[j];
		}
	}
	return res;
}

void transposition(int** matrix, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			int buff = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = buff;
		}
	}
}

void saddlery(int** matrix, int n) {
	int f = 0;
	for (int i = 0; i < n; i++) {
		int min = matrix[i][0];
		for (int j = 1; j < n; j++) {
			if (min > matrix[i][j]) {
				min = matrix[i][j];
			}
		}
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == min) {
				int max = matrix[i][j];
				for (int l = 0; l < n; l++) {
					if (max < matrix[l][j]) {
						max = matrix[l][j];
					}
				}
				if (max == matrix[i][j]) {
					f = 1;
					cout << "Седловой элемент находится в " << i + 1 << " строке и в " << j + 1 << " столбце" << endl;
				}
			}
		}

	}
	if (f == 0) {
		cout << "Седловых элементов нет" << endl;
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RUS");
	srand(time(0));
	int* vector = nullptr;
	int* result = nullptr;
	int** matrix = nullptr;
	int code, n = 0, flag = 0, f = 0;
	do {
		hello(code);
		switch (code) {
			case 0: break; // Конец

			case 1: // Создание матрицы
				if (matrix != nullptr) {
					for (int i = 0; i < n; i++) {
						delete[] matrix[i];
					}
					delete[] matrix;
				}
				cout << "Введите размер квадратной матрицы: ";
				cin >> n;
				if (n < 1) {
					cout << "Можно вводить размер не меньше 1" << endl;
					break;
				}
				matrix = create_matrix(matrix, n);
				insertmatrix(matrix, n);
				flag = 1;
				break;

			case 2: // Вывод матрицы
				if (flag == 0) {
					cout << "Для начала надо создать матрицу" << endl;
					break;
				}
				outmatrix(matrix, n);
				break;

			case 3: // Создание вектора
				if (vector != nullptr) {
					delete[] vector;
				}
				if (flag == 0) {
					cout << "Для начала надо создать матрицу" << endl;
					break;
				}
				vector = create_vector(vector, n);
				insertvector(vector, n);
				f = 1;
				break;

			case 4: // Вывод вектора
				if (flag == 0) {
					cout << "Для начала надо создать матрицу" << endl;
					break;
				}			
				if (f == 0) {
					cout << "Для начала надо создать вектор" << endl;
					break;
				}
				outvector(vector, n);
				break;

			case 5: // Произведение
				if (result != nullptr) {
					delete[] result;
				}
				if (flag == 0) {
					cout << "Для начала надо создать матрицу" << endl;
					break;
				}
				if (f == 0) {
					cout << "Для начала надо создать вектор" << endl;
					break;
				}
				result = multiplication(matrix, vector, n);
				outvector(result, n);
				break;

			case 6: // Транспонирование
				if (flag == 0) {
					cout << "Для начала надо создать матрицу" << endl;
					break;
				}
				transposition(matrix, n);
				outmatrix(matrix, n);
				break;

			case 7: // Седловой элемент
				if (flag == 0) {
					cout << "Для начала надо создать матрицу" << endl;
					break;
				}
				saddlery(matrix, n);
				break;

			default:
				if (abs(code) > 8) {
					cout << "Можно вводить числа только от 0 до 7" << endl;
					break;
				}
				break;
		}
	} while (code != 0);

	if (vector != nullptr) {
		delete[] vector;
	}
	if (result != nullptr) {
		delete[] result;
	}
	if (matrix != nullptr) {
		for (int i = 0; i < n; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	return 0;
}