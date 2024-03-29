#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int const MAX = 100;
int stack[MAX];
int tos = 0;

void push(int i) {
	if (tos >= MAX) {
		cout << "stack is full";
		return;
	}
	stack[tos] = i;
	tos++;
}

int pop() {
	tos--;
	if (tos < 0) {
		cout << "stack is empty";
		return 0;
	}
	return stack[tos];
}
int priority(char pr) {
	switch (pr) {
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	case '^':
		return 3;
	case '&':
		return 4;
	case '|':
		return 4;
	case '!':
		return 5;
	default:
		return 0;
	}
}
string RPE(const string& strok) {
    string OPZ;

    for (char i : strok) {
        if (i == ' ') {
            continue;
        }
        if (isalnum(i) || i == ' ') { // Если символ - операнд или пробел
            if (i != ' ') {
                OPZ += i;
            }
        }
        else if (i == '(') { // Если символ - открывающая скобка
            push(i);
        }
        else if (i == ')') { // Если символ - закрывающая скобка
            while (tos != -1  && stack[tos] != '(') {
                OPZ += stack[tos];
                pop();
            }
            pop(); // Удаляем открывающую скобку из стека
            tos += 1;
        }
        else { // Если символ - оператор
            if (isalnum(i) || i == ' ') { // Если символ - операнд или пробел
                if (i != ' ') {
                    OPZ += i;
                    OPZ += ' '; // Добавляем пробел после операнда
                }
            }
            else { // Если символ - оператор
                if (tos == 0 || stack[tos - 1] == '(' || priority(stack[tos - 1]) < priority(i)) {
                    push(i);
                }
                else {
                    while (tos != 0 && priority(stack[tos - 1]) >= priority(i)) {
                        OPZ += stack[tos - 1]; // Добавляем оператор из стека в ОПЗ
                        OPZ += ' '; // Добавляем пробел после оператора
                        pop(); // Удаляем его из стека
                    }
                    push(i); // Помещаем текущий оператор в стек
                }
            }

        }
    }

    while (tos != 0) {
        OPZ += " "; // Добавляем пробел
        OPZ += stack[tos - 1]; // Добавляем оператор или операнд
        pop(); // Удаляем его из стека
    }

    return OPZ;
}

int main()
{
    ifstream fin;
    fin.open("inputData.txt");
    ofstream fout;
    fout.open("outputData.txt");
    if (!fin.is_open()) {
        cout << "unfind file!";
    }
    else {
        string strok;
        getline(fin, strok);
        string opz = RPE(strok);
        fout << opz << '\n';
        return 0;

    }

    fout.close();
    fin.close();
}
