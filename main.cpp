#include "klient.h"
#include <fstream>
#include <iomanip>

//using namespace std;
using std::cout;
using std::cin;
using std::cerr;

// Funkcja do zapisywania danych do pliku
void saveToFile(const string& filename, const string& data) {
    ofstream file(filename);
    if (file.is_open()) {
        file << data;
        file.close();
    }
    else {
        cerr << "Blad przy zapisie do pliku.\n";
    }
}

// Funkcja do odczytywania danych z pliku
string readFromFile(const string& filename) {
    string data;
    ifstream file(filename);
    if (file.good()) {      //sprawdzenie czy plik istnieje
        getline(file, data);
        file.close();
    }
    else {
        cerr << "Blad przy odczycie z pliku.\n";
    }
    return data;
}

enum class Kategoria { danie_glowne, zupa, napoje };

struct Dish {
    string name;
    double price;
    Kategoria kategoria;
    Dish* next;
};

// Funkcja do dodawania dania do menu
void addDish(Dish*& menu) {
    Dish* newDish = new Dish;
    cout << "Podaj nazwê dania: ";
    cin >> newDish->name;
    cout << "Podaj cenê dania: ";
    cin >> newDish->price;
    cout << "Podaj kategorie dania (0 - Danie glowne, 1 - Zupa, 2 - Napoj): ";
    int category;
    cin >> category;
    newDish->kategoria = static_cast<Kategoria>(category);
    newDish->next = menu;
    menu = newDish;
    cout << "Danie dodane do menu.\n";
}

// Funkcja do przegl¹dania menu
void viewMenu(const Dish* menu) {
    cout << "Menu:\n";
    cout << setw(20) << "Nazwa dania" << setw(10) << "Cena" << setw(15) << "Kategoria" << endl;
    while (menu != nullptr) {
        string kategoria;
        switch (menu->kategoria) {
        case Kategoria::danie_glowne:
            kategoria = "Danie glowne";
            break;
        case Kategoria::zupa:
            kategoria = "Zupa";
            break;
        case Kategoria::napoje:
            kategoria = "Napoj";
            break;
        default:
            kategoria = "Nieznana";
        }
        cout << setw(20) << menu->name << setw(10) << menu->price << setw(15) << kategoria << endl;
        menu = menu->next;
    }
    }

// Funkcja do zmiany ceny dania w menu
void changePrice(Dish* menu) {
    string dishName;
    cout << "Podaj nazwe dania, ktorego cene chcesz zmienic: ";
    cin >> dishName;

    while (menu != nullptr) {
        if (menu->name == dishName) {
            cout << "Aktualna cena dania " << menu->name << ": " << menu->price << endl;
            cout << "Podaj now¹ cene: ";
            cin >> menu->price;
            cout << "Cena dania zmieniona.\n";
            return;
        }
        menu = menu->next;
    }

    cout << "Danie o nazwie " << dishName << " nie zostalo znalezione w menu.\n";
}

// Funkcja do zapisywania menu do pliku
void saveMenuToFile(const Dish* menu, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        while (menu != nullptr) {
            file << menu->name << " " << menu->price << " " << static_cast<int>(menu->kategoria) << "\n";
            menu = menu->next;
        }
        file.close();
        cout << "Menu zapisane do pliku: " << filename << ".\n";
    }
    else {
        cerr << "B³¹d przy zapisie do pliku.\n";
    }
}

// Funkcja do wczytywania menu z pliku
void loadMenuFromFile(Dish*& menu, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        while (!file.eof()) {
            Dish* newDish = new Dish;
            file >> newDish->name >> newDish->price;
            int category;
            file >> category;
            newDish->kategoria = static_cast<Kategoria>(category);
            newDish->next = menu;
            menu = newDish;
        }
        file.close();
        cout << "Menu wczytane z pliku: " << filename << ".\n";
    }
    else {
        cerr << "Blad przy wczytywaniu z pliku.\n";
    }
}
void saveMenuToFiles(const Dish* menu) {
    saveMenuToFile(menu, "danie_glowne.txt");
    saveMenuToFile(menu, "zupa.txt");
    saveMenuToFile(menu, "napoje.txt");
}

void loadMenuFromFiles(Dish*& menu) {
    loadMenuFromFile(menu, "danie_glowne.txt");
    loadMenuFromFile(menu, "zupa.txt");
    loadMenuFromFile(menu, "napoje.txt");
}

void displayUserMenu(const Dish* menu) {
    cout << "Twoje menu:\n";
    cout << setw(20) << "Nazwa dania" << setw(10) << "Cena" << setw(15) << "Kategoria" << endl;
    while (menu != nullptr) {
        string kategoria;
        switch (menu->kategoria) {
        case Kategoria::danie_glowne:
            kategoria = "Danie glowne";
            break;
        case Kategoria::zupa:
            kategoria = "Zupa";
            break;
        case Kategoria::napoje:
            kategoria = "Napoj";
            break;
        default:
            kategoria = "Nieznana";
        }
        cout << setw(20) << menu->name << setw(10) << menu->price << setw(15) << kategoria << endl;
        menu = menu->next;
    }
}
int main()
{   
    Dish* menu = nullptr;
    int choice;
    string userLogin, userPassword;
    string adminLoginFilename = "admin_login.txt";  //zmienna do podawania nazwy pliku loginu
    string adminPasswordFilename = "admin_password.txt";    //zmienna do podawania nazwy pliku hasla

    int loginAttempts = 0;

    cout << "Wybierz opcje:\n";
    cout << "1. Uzytkownik\n";
    cout << "2. Administrator\n";
    cin >> choice;

    if (choice == 1)
    {
        // Kod dla u¿ytkownika
        cout << "Witaj, uzytkowniku!\n";
        displayUserMenu(menu);
        // Tu mo¿esz dodaæ kod dla u¿ytkownika
    }

    if (choice != 1 && choice != 2)
    {
        cout << "Nieprawidlowy wybor. Koniec programu.\n";
    }

    if (loginAttempts == 3)
    {
        cout << "Przekroczono limit blednych prob. Wracam do wyboru uzytkownika.\n";
    }

    if (choice == 2)
    {
        // Kod dla administratora
        int admin_choice;   //przeniesione tutaj przez bledy w petli do while
        while (loginAttempts < 3)
        {
            cout << "Podaj login: ";
            cin >> userLogin;
            cout << "Podaj haslo: ";
            cin >> userPassword;
                
            {
                if (userLogin == readFromFile(adminLoginFilename) && userPassword == readFromFile(adminPasswordFilename))
                {
                        Dish* menu = nullptr; // Inicjalizacja menu
                        loadMenuFromFiles(menu); // Wczytanie menu z pliku
                        cout << "Zalogowano jako administrator.\n";
                    do
                    {
                        cout << " =====================" << endl;
                        cout << "||  1. Edytuj ceny  ||" << endl;
                        cout << "||  2. Edytuj menu  ||" << endl;
                        cout << "||  3. Zmien haslo  ||" << endl;
                        cout << "||  4. Zmien login  ||" << endl;
                        cout << "||  5. Wyjdz        ||" << endl;
                        cout << " =====================" << endl;
                        cin >> admin_choice;
                        {
                            switch (admin_choice)
                            {
                            case (1):   //Edycja cen
                            {
                                changePrice(menu);
                                saveMenuToFile(menu, "menu.txt");
                                break;
                            }
                            case(2):
                            {
                                addDish(menu);
                                break;
                            }
                            case(3):    // zmiana has³a dla administratora
                            {
                                cout << "Podaj nowe haslo: ";
                                cin >> userPassword;
                                saveToFile(adminPasswordFilename, userPassword);
                                cout << "Zmieniono haslo administratora.\n";

                            }
                            break;
                            case(4):       //zmiana loginu administratora
                            {
                                cout << "Podaj nowy login: ";
                                cin >> userLogin;
                                saveToFile(adminLoginFilename, userLogin);
                                cout << "Zmieniono login administratora.\n";
                                break;
                            }
                            case(5):
                            {
                                break;
                            }
                            break;
                            default:
                            {
                                cout << "Wybrano nieistniejaca opcje!" << endl;
                                break;
                            }
                            }
                        }
                    } while (admin_choice != 5);
                   
                        break;
                }
              
                else {
                    cout << "Bledny login lub haslo. Sprobuj ponownie.\n";
                    loginAttempts++;
                }
            }


        }
        //Koniec czêœci odpowiedzialnej za logowanie jako administrator



        return 0;
    }
}