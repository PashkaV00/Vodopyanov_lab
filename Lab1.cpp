#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
using namespace std;

// Данные о трубе
struct Pipe {
    string km_mark = "";        // Километровая отметка
    double length = 0.0;         // Длина
    int diameter = 0;            // Диаметр 
    bool under_repair = false;   // В ремонте или нет

    void input() {
        cout << "Введите километровую отметку: ";
        cin >> km_mark;

        cout << "Введите длину (км): ";
        while (!(cin >> length) || length <= 0) {
            cout << "Ошибка! Введите положительное число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Введите диаметр (мм): ";
        while (!(cin >> diameter) || diameter <= 0) {
            cout << "Ошибка! Введите положительное число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        string repair_input;
        while (true) {
            cout << "Труба в ремонте? (да/нет): ";
            cin >> repair_input;

            if (repair_input == "да") {
                under_repair = true;
                break;
            }
            else if (repair_input == "нет") {
                under_repair = false;
                break;
            }
            else {
                cout << "Ошибка! Введите только 'да' или 'нет'" << endl;
            }
        }
    }

    void display() const {
        cout << "Труба: " << km_mark << ", " << length << "км, "
            << diameter << "мм, статус: " << (under_repair ? "в ремонте" : "работает") << endl;
    }
};

// Данные кс
struct CompressorStation {
    string name = "";                // Название станции
    int total_workshops = 0;         // Общее количество цехов
    int working_workshops = 0;       // Количество цехов в работе
    int efficiency_class = 0;        // Класс эффективности станции

    void input() {
        cout << "Введите название: ";
        cin >> name;

        cout << "Введите общее количество цехов: ";
        while (!(cin >> total_workshops) || total_workshops <= 0) {
            cout << "Ошибка! Введите положительное число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        do {
            cout << "Введите количество работающих цехов: ";
            // Проверка что введено число и оно неотрицательное
            while (!(cin >> working_workshops) || working_workshops < 0) {
                cout << "Ошибка! Введите неотрицательное число: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            // Проверка что работающих цехов не больше общего количества
            if (working_workshops > total_workshops) {
                cout << "Ошибка: работающих цехов не может быть больше общего количества!" << endl;
            }
        } while (working_workshops > total_workshops);

        cout << "Введите класс эффективности: ";
        while (!(cin >> efficiency_class) || efficiency_class <= 0) {
            cout << "Ошибка! Введите положительное число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    void display() const {
        cout << "КС: " << name << ", цехи: " << working_workshops
            << "/" << total_workshops << ", класс: " << efficiency_class << endl;
    }
};

// Функция для сохранения всех данных в файл
void saveToFile(const vector<Pipe>& pipes, const vector<CompressorStation>& stations) {
    ofstream file("data.txt");
    if (file.is_open()) {
        // Сохраняем количество труб
        file << pipes.size() << endl;
        // Сохраняем данные каждой трубы
        for (const auto& pipe : pipes) {
            file << pipe.km_mark << endl << pipe.length << endl << pipe.diameter
                << endl << pipe.under_repair << endl;
        }

        // Сохраняем количество КС
        file << stations.size() << endl;
        // Сохраняем данные каждой КС
        for (const auto& station : stations) {
            file << station.name << endl << station.total_workshops << endl
                << station.working_workshops << endl << station.efficiency_class << endl;
        }
        file.close();
        cout << "Данные успешно сохранены!" << endl;
    }
    else {
        cout << "Ошибка сохранения файла!" << endl;
    }
}

// Функция для загрузки всех данных из файла
void loadFromFile(vector<Pipe>& pipes, vector<CompressorStation>& stations) {
    ifstream file("data.txt");
    if (file.is_open()) {
        // Загружаем количество труб
        int pipeCount;
        file >> pipeCount;
        pipes.resize(pipeCount);
        // Загружаем данные каждой трубы
        for (int i = 0; i < pipeCount; i++) {
            file >> pipes[i].km_mark >> pipes[i].length >> pipes[i].diameter >> pipes[i].under_repair;
        }

        // Загружаем количество КС
        int stationCount;
        file >> stationCount;
        stations.resize(stationCount);
        // Загружаем данные каждой КС
        for (int i = 0; i < stationCount; i++) {
            file >> stations[i].name >> stations[i].total_workshops
                >> stations[i].working_workshops >> stations[i].efficiency_class;
        }
        file.close();
        cout << "Данные успешно загружены!" << endl;
    }
    else {
        cout << "Ошибка загрузки файла!" << endl;
    }
}

// Функция для выбора трубы из списка
int selectPipe(const vector<Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "Нет доступных труб!" << endl;
        return -1;
    }

    cout << "Список труб:" << endl;
    for (int i = 0; i < pipes.size(); i++) {
        cout << i + 1 << ". ";
        pipes[i].display();
    }

    int choice;
    cout << "Выберите трубу для редактирования (1-" << pipes.size() << "): ";
    while (!(cin >> choice) || choice < 1 || choice > pipes.size()) {
        cout << "Неверный выбор! Введите число от 1 до " << pipes.size() << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return choice - 1;  // Возвращаем индекс выбранной трубы
}

// Функция для выбора КС из списка
int selectStation(const vector<CompressorStation>& stations) {
    if (stations.empty()) {
        cout << "Нет доступных КС!" << endl;
        return -1;
    }

    cout << "Список КС:" << endl;
    for (int i = 0; i < stations.size(); i++) {
        cout << i + 1 << ". ";
        stations[i].display();
    }

    int choice;
    cout << "Выберите КС для редактирования (1-" << stations.size() << "): ";
    while (!(cin >> choice) || choice < 1 || choice > stations.size()) {
        cout << "Неверный выбор! Введите число от 1 до " << stations.size() << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return choice - 1;  // Возвращаем индекс выбранной КС
}

// Главная функция программы
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Pipe> pipes;                    // Вектор для хранения всех труб
    vector<CompressorStation> stations;    // Вектор для хранения всех КС
    int choice;                            // Переменная для выбора пункта меню

    // Главный цикл программы
    while (true) {
        cout << "\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход\nВыберите: ";
        cin >> choice;

        // Обработка выбора пользователя
        switch (choice) {
        case 1: {
            // Добавление новой трубы
            Pipe newPipe;
            newPipe.input();
            pipes.push_back(newPipe);
            break;
        }
        case 2: {
            // Добавление новой КС
            CompressorStation newStation;
            newStation.input();
            stations.push_back(newStation);
            break;
        }
        case 3: {
            // Все трубы
            cout << "\n--- Трубы ---" << endl;
            if (pipes.empty()) {
                cout << "Трубы отсутствуют" << endl;
            }
            else {
                // Вывод всех труб
                for (int i = 0; i < pipes.size(); i++) {
                    cout << i + 1 << ". ";
                    pipes[i].display();
                }
            }

            cout << "\n--- КС ---" << endl;
            if (stations.empty()) {
                cout << "КС отсутствуют" << endl;
            }
            else {
                // Вывод всех КС
                for (int i = 0; i < stations.size(); i++) {
                    cout << i + 1 << ". ";
                    stations[i].display();
                }
            }
            break;
        }
        case 4: {
            // Редактирование существующей трубы
            int pipeIndex = selectPipe(pipes);
            if (pipeIndex != -1) {
                cout << "Редактирование трубы:" << endl;
                pipes[pipeIndex].input();
                cout << "Труба успешно отредактирована!" << endl;
            }
            break;
        }
        case 5: {
            // Редактирование существующей КС
            int stationIndex = selectStation(stations);
            if (stationIndex != -1) {
                cout << "Редактирование КС:" << endl;
                stations[stationIndex].input();
                cout << "КС успешно отредактирована!" << endl;
            }
            break;
        }
        case 6:
            // Сохранение данных в файл
            saveToFile(pipes, stations);
            break;
        case 7:
            // Загрузка данных из файла
            loadFromFile(pipes, stations);
            break;
        case 0:
            // Выход из программы
            return 0;
        default:
            // Обработка неверного выбора в меню
            cout << "Неверный выбор!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}