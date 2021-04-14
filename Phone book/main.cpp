#include <iostream>
#include <fstream>
#include "rb_tree.h"

using namespace std;

int main()
{
    rb_tree *tree = new rb_tree;
    string data[3];
    int x;
    while(true)
    {
        cout << "Menu: " << endl << "1. Wstaw nowego abonenta." << endl;
        cout << "2. Usun abonenta." << endl << "3. Wyszukaj abonenta." << endl;
        cout << "4. Zapisz do pliku." << endl << "5. Wczytaj z pliku." << endl;
        cout << "6. Wypisz listę abonentów." << endl << "7. Zamknij program." << endl << "0. Test" << endl;
        cin.clear();
        cin >> x;
        switch (x)
        {
            case 1:
            {
                cout << "Podaj imie, nazwisko oraz adres bez spacji (nazwa_ulicy_numer):" << endl;
                    for (int i = 0; i < 3; i++)
                        cin >> data[i];
                    tree->insert(data, nullptr);
                break;
            }
            case 2:
                cout << "Podaj imię, nazwisko oraz adres bez spacji, abonenta ktorego chcesz usunac:" << endl;
                for(int i = 0; i < 3; i++)
                    cin >> data[i];
                tree->remove(data);
                break;
            case 3:
                cout << "Podaj imię, nazwisko oraz adres bez spacji, abonenta ktorego chcesz wyszukac:" << endl;
                for(int i = 0; i < 3; i++)
                    cin >> data[i];
                tree->search(data);
                break;
            case 4:
            {
                tree->save();
                break;
            }
            case 5:
            {
                ifstream in("ksiunszka.bin", ios::in | ios::binary);
                size_t len;
                char *tmp;
                if(!in.is_open())
                {
                    cout << "Nie znaleziono pliku.";
                    break;
                }
                while(in.read((char *)& len, sizeof(size_t)))
                {
                    tmp = new char[len+1];
                    in.read(tmp, len);
                    tmp[len] = '\0';
                    data[0] = tmp;
                    delete tmp;

                    for(int i = 1; i < 3; i++)
                    {
                        in.read((char *)& len, sizeof(size_t));
                        tmp = new char[len+1];
                        in.read(tmp, len);
                        tmp[len] = '\0';
                        data[i] = tmp;
                        delete tmp;
                    }

                    tree->insert(data, &in);
                }
                in.close();
                break;
            }
            case 6:
                tree->printout();
                break;
            case 7:
                return 0;
            case 0:
                cout << tree->test(nullptr, 1) << endl;
                break;
            default:
                cout << "Podaj poprawna cyfre.";
                break;
        }
    }

}
