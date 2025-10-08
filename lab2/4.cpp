// Дана строка name и целое число K (> 0). Записать в текстовый файл с именем name K символов
// «*». Использовать алгоритм fill_n.
#include <iostream>
#include <fstream>
#include <algorithm> // Для fill_n
using namespace std;

int main() {
    string name;  // Имя файла
    int K;        // Количество символов "*"
    
    // Ввод данных
    cout << "Введите имя файла: ";
    cin >> name;
    cout << "Введите количество символов '*': ";
    cin >> K;
    
    // Открываем файл для записи
    ofstream outFile(name);
    
    // Проверяем, удалось ли открыть файл
    if (!outFile) {
        cout << "Ошибка при открытии файла!" << endl;
        return 1;
    }

    // Используем fill_n для записи K символов "*" в файл
    fill_n(ostream_iterator<char>(outFile), K, '*');

    cout << "Файл " << name << " успешно записан!" << endl;

    // Закрываем файл
    outFile.close();

    return 0;
}
