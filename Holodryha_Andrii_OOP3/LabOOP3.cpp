#include <iostream>
#define N 3
using namespace std;

const int monthDays[12]
= { 31, 28, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31 };

class Data {
private:
	int n, * chysl;
public:
	Data()
	{
		n = N; chysl = new int[n];
		for (int i = 0; i < n; i++)
		{
			chysl[i] = 1;
			if ((i + 1) % 3 == 0) chysl[i] = 2020;
		}
		//Конструктор
	}
	Data(int n, int* chysl)
	{
		this->n = n; this->chysl = new int[this->n];
		for (int i = 0; i < this->n; i++)
			this->chysl[i] = chysl[i];
		//Конструктор з параметрами
	}
	Data(const Data& obj)
	{
		this->n = obj.n; this->chysl = new int[this->n];
		for (int i = 0; i < this->n; i++)
			this->chysl[i] = obj.chysl[i];
		//Копія конструктора
	}
	~Data()
	{
		delete[]chysl;
	}
	//Деструктор

	int GetN()
	{
		return n;
	}
	void GetChysl(int* arr) 
	{
		for (int i = 0; i < this->n; i++)
			arr[i] = chysl[i];
	}

	void SetChysl(int n, int* chysl) 
	{
		this->n = n; this->chysl = new int[this->n];
		for (int i = 0, j = 0; i < this->n; i++, j++) 
		{
			if (j == 0 && (chysl[i] > 31 || chysl[i] < 0)) 
			{ 
				puts("Неправильний день"); this->chysl[i] = 0;
			}
			else if (j == 1)
			{
				if (chysl[i] > 12 || chysl[i] < 0)
				{ puts("Неправильний місяць"); this->chysl[i] = 0;
				}
				else if (chysl[i - 1] > monthDays[chysl[i]])
				{
					puts("Неправильний день"); this->chysl[i] = 0;
				}
				else this->chysl[i] = chysl[i];
			}
			else this->chysl[i] = chysl[i];

			if ((i + 1) % 3 == 0) j = -1;
		}
	}

	void Print1() 
	{
		const char* months[] = 
		{ "січня", "лютого", "березня", "квітня", "травня", "червня",
		  "липня", "серпня", "вересня", "жовтня", "листопада", "грудня" 
		};
		for (int i = 0, j = 0; i < this->n; i++, j++)
		{
			if (j == 1) 
			{
				if (chysl[i] == 0) cout << "неправильно ";
				else cout << months[this->chysl[i] - 1] << ' ';
			}
			else cout << this->chysl[i] << ' ';
			if ((i + 1) % 3 == 0) 
			{ 
				j = -1; putchar('\b'); cout << ((i + 1) == N ? '\0' : ',') << ' ';
			}
		}
		cout << '\n';
	}
	void Print2() 
	{
		for (int i = 0; i < this->n; i++)
			cout << ((i + 1) % 3 != 0 && chysl[i] < 10 ? '0' : '\0') << this->chysl[i] << ((i + 1) % 3 != 0 ? '.' : ' ');
		cout << '\n';
	}

	friend ostream& operator<<(ostream& os, const Data& day) {
		for (int i = 0; i < N; i++)
			os << day.chysl[i] << " ";
		os << "\n";
		return os;
	}

	friend istream& operator>>(istream& is, Data& day) {
		for (int i = 0; i < N; i++)
			is >> day.chysl[i];
		return is;
	}

	int operator -(const Data& other) {
		long int n1 = this->chysl[2] * 365 + this->chysl[0];
		for (int i = 0; i < this->chysl[1] - 1; i++)
			n1 += monthDays[i];
		if (this->chysl[1] >= 2 && (this->chysl[2] % 4 == 0)) n1++;
		n1 += (this->chysl[2] / 4 - this->chysl[2] / 100 + this->chysl[2] / 400);

		long int n2 = other.chysl[2] * 365 + other.chysl[0];
		for (int i = 0; i < other.chysl[1] - 1; i++)
			n2 += monthDays[i];
		if (other.chysl[1] >= 2 && (other.chysl[2] % 4 == 0)) n2++;
		n2 += (other.chysl[2] / 4 - other.chysl[2] / 100 + other.chysl[2] / 400);

		return (n1 - n2);
	}

	bool operator >(const Data& other) {
		long int n1 = this->chysl[2] * 365 + this->chysl[0];
		for (int i = 0; i < this->chysl[1] - 1; i++)
			n1 += monthDays[i];
		n1 += (this->chysl[2] / 4 - this->chysl[2] / 100 + this->chysl[2] / 400);

		long int n2 = other.chysl[2] * 365 + other.chysl[0];
		for (int i = 0; i < other.chysl[1] - 1; i++)
			n2 += monthDays[i];
		n2 += (other.chysl[2] / 4 - other.chysl[2] / 100 + other.chysl[2] / 400);

		if (n1 > n2) return true;
		else return false;
		cout << "\n";
	}

	void operator =(const Data& other) {
		this->n = other.n;
		if (this->chysl != NULL) {
			delete[]this->chysl;
		}
		this->chysl = new int[other.n];
		for (int i = 0; i < other.n; i++) {
			this->chysl[i] = other.chysl[i];
		}
	}
};

int main() {
	system("chcp 1251");
	const int Length = 4; int max, min;
	int arr[N] = { 15, 2, 2020 };
	int arr2[N] = { 11, 2, 2020 };
	int arr3[N] = { 12, 3, 2020 };

	Data days[Length] = {
		 Data(3, arr),
		 Data(3, arr2),
		 Data(),
		 Data(3, arr3)
	};
	Data temp;

	for (int j = 0; j < (Length - 1); j++) {
		for (int i = 0; i < (Length - 1); i++) {
			if (days[i + 1] > days[i]) {
				temp = days[i];
				days[i] = days[i + 1];
				days[i + 1] = temp;
			}
		}
	}

	max = min = days[0] - days[1];
	for (int k = 0; k < (Length - 1); k++) {
		for (int i = k + 1; i < Length; i++) {
			if ((days[k] - days[i]) > max) max = days[k] - days[i];
			if ((days[k] - days[i]) < min) min = days[k] - days[i];
		}
	}

	for (int i = 0; i < Length; i++) {
		cout << days[i] << "\n";
	}
	cout << "Максимальна рiзниця: " << max << ", мiнiмальна рiзниця: " << min << "\n";

}