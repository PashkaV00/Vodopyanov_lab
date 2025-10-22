#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// Структура для хранения данных о трубе
struct Pipe {
    string name;
    double length;
    int diameter;
    bool inRepair;

    Pipe() : name(""), length(0.0), diameter(0), inRepair(false) {}
};

// Хранения данных о компрессорной станции
struct CompressorStation {
    string name;
    int numberWorkshop;
    int workingWorkshop;
    int classWorkshop;

    CompressorStation() : name(""), numberWorkshop(0), workingWorkshop(0), classWorkshop(0) {}
};

// Функция для ввода данных о трубе
void input_pipe(Pipe& pipe) {
    cout << "Название трубы: ";
    getline(cin >> ws, pipe.name);
    while (pipe.name.empty()) {
        cout << "Ошибка: название не может быть пустым: ";
        getline(cin, pipe.name);
    }

    cout << "Длина: ";
    // Проверка корректности ввода длины
    while (!(cin >> pipe.length) || (pipe.length < 0) || (cin.peek() != '\n')) {
        cout << "Ошибка: введите положительное число: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Диаметр: ";
    // Проверка корректности ввода диаметра
    while (!(cin >> pipe.diameter) || (pipe.diameter < 0) || (cin.peek() != '\n')) {
        cout << "Ошибка: введите положительное число: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Статус (0 - в ремонте, 1 - работает): ";
    // Проверка корректности ввода статуса
    while (!(cin >> pipe.inRepair) || (cin.peek() != '\n')) {
        cout << "Ошибка: введите 0 или 1: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
}

// Функция для изменения статуса ремонта трубы
void edit_Repair_Pipe(Pipe& pipe) {
    cout << "Статус (0 - в ремонте, 1 - работает): ";
    while (!(cin >> pipe.inRepair)) {
        cout << "Ошибка: введите 0 или 1: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
}

// Функция проверки, создана ли труба (проверяет не пустое ли имя)
bool Pipe_created(const Pipe& pipe) {
    return !pipe.name.empty();
}

// Функция для ввода данных о компрессорной станции
void input_CS(CompressorStation& CS) {
    cout << "Название КС: ";
    getline(cin >> ws, CS.name);
    while (CS.name.empty()) {
        cout << "Ошибка: название не может быть пустым: ";
        getline(cin, CS.name);
    }

    cout << "Количество цехов: ";
    // Проверка что количество цехов положительное
    while (!(cin >> CS.numberWorkshop) || (CS.numberWorkshop <= 0) || (cin.peek() != '\n')) {
        cout << "Ошибка: введите положительное число: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Количество рабочих цехов: ";
    // Проверка что рабочих цехов не больше общего количества
    while (!(cin >> CS.workingWorkshop) || (CS.workingWorkshop < 0) || (CS.workingWorkshop > CS.numberWorkshop) || (cin.peek() != '\n')) {
        cout << "Ошибка: должно быть от 0 до " << CS.numberWorkshop << ": ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Класс станции (1-5): ";
    // Проверка что класс в диапазоне от 1 до 5
    while (!(cin >> CS.classWorkshop) || (CS.classWorkshop < 1) || (CS.classWorkshop > 5) || (cin.peek() != '\n')) {
        cout << "Ошибка: введите число от 1 до 5: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
}

// Функция для редактирования компрессорной станци
void edit_CS(CompressorStation& CS) {
    int n;

    while (true) {
        cout << "Запуск цеха (1), остановка цеха (-1): ";
        while (!(cin >> n) || (n != 1 && n != -1)) {
            cout << "Ошибка: введите 1 или -1: ";
            cin.clear();
            cin.ignore(100, '\n');
        }

        if ((CS.workingWorkshop + n >= 0) && (CS.workingWorkshop + n) <= CS.numberWorkshop) {
            CS.workingWorkshop += n;  // Изменение количества рабочих цехов
            break;
        }

        cout << "Ошибка: невозможно выполнить операцию\n";
    }

    cout << "Количество рабочих цехов: " << CS.workingWorkshop << endl;
}

// Функция проверки, создана ли компрессорная станция
bool StationCreated(const CompressorStation& CS) {
    return !CS.name.empty();
}

// Функция для просмотра информации о трубе
void view_Object_1(Pipe& pipe) {
    if (Pipe_created(pipe)) {
        cout << "\n === Труба === \n";
        cout << "Название: " << pipe.name << ", Длина: " << pipe.length
            << ", Диаметр: " << pipe.diameter << ", В ремонте?: " << (pipe.inRepair ? "Нет" : "Да") << endl;
    }
    else cout << "\n Труба не создана \n";
}

// Функция для просмотра информации о компрессорной станции
void view_Object_2(CompressorStation& CS) {
    if (StationCreated(CS)) {
        cout << "\n == Компрессорная станция == \n";
        cout << "Название: " << CS.name << ", Всего цехов: " << CS.numberWorkshop
            << ", Рабочих цехов: " << CS.workingWorkshop << ", Класс станции: " << CS.classWorkshop << endl;
    }
    else cout << "\n КС не создана \n";
}

// Функция отображения главного меню программы
void display_Menu() {
    cout << "\n=== Меню управления трубопроводом ===\n";
    cout << "1. Добавить трубу\n";
    cout << "2. Добавить компрессорную станцию\n";
    cout << "3. Просмотр всех объектов\n";
    cout << "4. Редактировать трубу\n";
    cout << "5. Редактировать компрессорную станцию\n";
    cout << "6. Сохранить данные\n";
    cout << "7. Загрузить данные\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

// Функция сохранения данных о трубе в файл
void save_Pipe_to_File(const Pipe& pipe, ofstream& file) {
    if (Pipe_created(pipe)) {
        file << "== Труба ==\n";
        file << pipe.name << "\n";
        file << pipe.length << "\n";
        file << pipe.diameter << "\n";
        file << pipe.inRepair << "\n";
    }
}

// Функция сохранения данных о компрессорной станции в файл
void save_CS_to_File(const CompressorStation& CS, ofstream& file) {
    if (StationCreated(CS)) {
        file << "== КС ==\n";
        file << CS.name << "\n";
        file << CS.numberWorkshop << "\n";
        file << CS.workingWorkshop << "\n";
        file << CS.classWorkshop << "\n";
    }
}

// Функция загрузки данных о трубе из файла
void load_Pipe_from_File(Pipe& pipe, ifstream& file) {
    getline(file >> ws, pipe.name);
    file >> pipe.length;
    file >> pipe.diameter;
    file >> pipe.inRepair;
}

// Функция загрузки данных о компрессорной станции из файла
void load_CS_from_File(CompressorStation& CS, ifstream& file) {
    getline(file >> ws, CS.name);
    file >> CS.numberWorkshop;
    file >> CS.workingWorkshop;
    file >> CS.classWorkshop;
}

int main() {
    // Установка русской кодировки для консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Pipe pipe;  // Создание трубы
    CompressorStation CS;  // Создание компрессорной станции
    int choice;  // Выбора пункта меню

    do {
        display_Menu();  // Показ меню

        // Проверка корректности ввода для меню
        while (!(cin >> choice) || (choice < 0 || choice > 7) || (cin.peek() != '\n')) {
            cout << "Ошибка: введите число от 0 до 7: ";
            cin.clear();
            cin.ignore(100, '\n');
        }

        // Обработка выбора
        switch (choice) {
        case 1:
            input_pipe(pipe);
            cout << "Труба успешно добавлена \n";
            break;

        case 2:
            input_CS(CS);
            cout << "Компрессорная станция успешно добавлена \n";
            break;

        case 3:
            view_Object_1(pipe);
            view_Object_2(CS);
            break;

        case 4:
            if (Pipe_created(pipe))
                edit_Repair_Pipe(pipe);
            else
                cout << "== Сначала создайте трубу ===\n";
            break;

        case 5:
            if (StationCreated(CS))
                edit_CS(CS);
            else
                cout << " == Сначала создайте компрессорную станцию ==\n";
            break;

        case 6: {  // Сохранение данных в файл
            ofstream file("data.txt");
            if (file.is_open()) {
                save_Pipe_to_File(pipe, file);
                save_CS_to_File(CS, file);
                file.close();
                cout << "\nДанные сохранены в файл 'data.txt'\n";
            }
            else {
                cout << "Ошибка: не удалось создать файл\n";
            }
            break;
        }

        case 7: {  // Загрузка данных из файла
            ifstream file("data.txt");
            if (file.is_open()) {
                string line;
                // Чтение файла построчно
                while (getline(file, line)) {
                    if (line == "== Труба ==") {
                        load_Pipe_from_File(pipe, file);
                    }
                    else if (line == "== КС ==") {
                        load_CS_from_File(CS, file);
                    }
                }
                file.close();
                cout << "\nДанные загружены из файла\n";
            }
            else {
                cout << "Ошибка: не удалось открыть файл для чтения\n";
            }
            break;
        }

        case 0:
            cout << "Выход из программы\n";
            break;
        }

    } while (choice != 0);

    return 0;
}
