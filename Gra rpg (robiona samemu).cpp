#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

//////// ZMIENNE GLOBALNE /////////////////////
//
int hp = 100;
int obrona = 10;
int atak = 10;
//
///////////////////////////////////////////////


// klasa reprezentująca przedmiot
class Item
{
public:
    string name;
    string type;
    int value;

    Item(string name, string type, int value) : name(name), type(type), value(value){}

    void showItem() const
    {
        cout << "Name: " << name << ", Type: " << type << ", value: " << value << endl;
    }
};


// klasa reprezentująca plecak
class Backpack
{
private:
    vector<Item> items;

public:
    // metoda dodawania przedmiotu do plecaka
    void addItem(const Item& item)
    {
        items.push_back(item);
        cout << "- Dodano " << item.name << " do plecaka." << endl; /////
    }

    // metoda wyświetlająca zawartości plecaka
    void showContents()
    {
        cout << "Zawartosc plecaka:" << endl;
        for (size_t i = 0; i < items.size(); ++i)
        {
            cout << i << ". ";
            items[i].showItem();
        }
    }

    // metoda użycia przedmiotu z plecaka
    void useItem(size_t index)
    {
        if (index < items.size())
        {
            cout << "\nUzywasz przedmiotu: " << items[index].name << endl;

            if (items[index].type == "hpBoost") {
                hp += items[index].value;
                cout << "Twoje HP wzroslo o " << items[index].value << " punktow." << endl;
            }
            else if (items[index].type == "obronaBoost") {
                obrona += items[index].value;
                cout << "Twoja obrona wzrosla o " << items[index].value << " punktow." << endl;
            }
            else if (items[index].type == "atakBoost") {
                atak += items[index].value;
                cout << "Twoj atak wzrosl o " << items[index].value << " punktow." << endl;
            }
            items.erase(items.begin() + index);
        }
        else
        {
            cout << "Nieprawidłowy indeks przedmiotu." << endl;
        }
    }

    // metoda inicjalizująca przykladowe przedmioty w plecaku
    void initializeItems()
    {
        // dodawanie przedmiotów na podstawie przekazanych argumentów
            addItem(Item("Jagody Lesne", "hpBoost", 5));
            addItem(Item("Magiczny Kamien", "atakBoost", 2));
            addItem(Item("Złota Zbroja", "obronaBoost", 6));  
    }
};


// struktura przechowująca dane o wyniku losowania
struct WynikPrzeciwnicy
{
    int ilosc;
    int hp;
    int obrona;
    int atak;
};


// Funkcja szablonowa losująca szanse przeciwnikow na podstawie podanych parametrów
template<typename T>
WynikPrzeciwnicy SzansaPrzeciwnicy(const vector<pair<int, T>>& szanse, int hp_na1, int obrona_na1, int atak_na1)
{
    int losowa_szansa = rand() % 100 + 1;
    int ilosc = 0;

    int akumulowana_szansa = 0;
    for (const auto& szansa : szanse)
    {
        akumulowana_szansa += szansa.first;
        if (losowa_szansa <= akumulowana_szansa)
        {
            ilosc = szansa.second;
            break;
        }
    }
    WynikPrzeciwnicy wynik;
    wynik.ilosc = ilosc;
    wynik.hp = ilosc * hp_na1;
    wynik.obrona = ilosc * obrona_na1;
    wynik.atak = ilosc * atak_na1;

    return wynik;
}

// funkcja definiująca szansę dla wilków
vector<pair<int, int>> szansaWilkow()
{
    return
    {
        {5,2},{15, 3},{25, 4},{25, 5},{15, 6},{5, 7},{5, 8},{3, 9},{2, 10}
    };
}


// funkcja wyświetlająca informacje o postaci
void showInfo()
{
    cout << "------------------------------------" << endl;
    cout << "HP: " << hp << "\nOBRONA: " << obrona << "\nATAK: " << atak << endl;
    cout << "------------------------------------" << endl;
}


// funkcja losująca przygody
bool przygoda(Backpack& backpack, int& hp, int& obrona, int& atak)
{
    while (true)
    {
        int wydarzenie = rand() % 2 + 1; // losowanie wartości od 1 do 2

        switch (wydarzenie)
        {
        case 1:
        {
            // definiowanie szans dla wilkow za pomoca osobnej funkcji
            vector<pair<int, int>> szanse_wilkow = szansaWilkow();

            // wywołanie funkcji SzansaPrzeciwnicy
            WynikPrzeciwnicy wynik_wilkow = SzansaPrzeciwnicy(szanse_wilkow, 6, 1, 2);

            cout << "\nNatrafiasz na watache " << wynik_wilkow.ilosc << " wilkow" << endl;
            cout << "        _\n";
            cout << "       / \\      _-'\n";
            cout << "     _/|  \\-''- _ /\n";
            cout << "__-' { |          \\\n";
            cout << "    /             \\\n";
            cout << "    /       \"o.  |o}\n";
            cout << "    |            \\ ;\n";
            cout << "                  ',\n";
            cout << "       \\_         __\\\n";
            cout << "         ''-_    \\.//\n";
            cout << "           / '-____'\n";
            cout << "          /\n";
            cout << "        _'\n";
            cout << "      _-'\n";
            // info o wilkach:
            cout << "Wilki: " << wynik_wilkow.hp << "HP, " << wynik_wilkow.obrona << " OBRONA, " << wynik_wilkow.atak << " ATAK" << endl;

            // walka z watachą wilków
            int wilkiHP = wynik_wilkow.hp;
            int wilkiObrona = wynik_wilkow.obrona;
            while (wilkiHP > 0 && hp > 0)
            {
                int wyborCase1;
                cout << "walczysz czy uciekasz? 1-walka, 2-ucieczka" << endl;
                cin >> wyborCase1;

                switch (wyborCase1)
                {
                    case 1:
                    {
                        // atak bohatera 
                        int obrazenia = max(0, atak - wilkiObrona); // ?
                        wilkiHP -= obrazenia;
                        cout << "Bohater atakuje watache wilkow i zadaje " << obrazenia << " obrazen." << endl;
                        cout << "Wilki: " << wilkiHP << "HP" << endl;
                        if (wilkiHP <= 0) 
                        { 
                            cout << "\nPokonales watache wilkow!" << endl;                           
                            cout << "Zdobywasz Jagody Lesne!" << endl;
                            backpack.addItem(Item("Jagody Lesne", "hpBoost", 5));
                            break;
                        }
                        
                        // atak wilkow
                        int obrazenia_od_wilkow = max(0, wynik_wilkow.atak - obrona);
                        // if (obrazenia_od_wilkow < 0) { obrazenia_od_wilkow = 0; }
                        cout << "Watacha wilkow atakuje i zadaje " << obrazenia_od_wilkow << " obrazen." << endl;
                        hp -= obrazenia_od_wilkow;
                        cout << "bohater: " << hp << " HP" << endl;
                        if (hp <= 0) { cout << "Zginales w walce z wilkami!" << endl; break; }
                        break;
                    }
                    case 2:
                    {
                        cout << "\nUdaje ci sie uciec, ale zostajesz pogryziony przez wilki i tracisz polowe hp" << endl;
                        hp -= hp / 2;
                        cout << hp << " HP" << endl;
                        return true; // zakonczenie walki po ucieczce
                    }
                    default:
                    {
                        cout << "Nieznana opcja, spróbuj ponownie.\n" << endl;
                        break;
                    }
                }
                if (hp <= 0 || wilkiHP <= 0) break;
            }
            break;
        }
        default:
            break;
        }
        return false; // zwróć false jeśli nie ma wydarzenia
    }

}


// główna pętla gry

int main()
{
    srand(time(0)); // Inicjalizacja generatora liczb pseudolosowych

    Backpack backpack;

    while (true)
    {
        showInfo();

        int wybor;
        cout << "[WYBIERZ AKCJE]: \n" << endl;
        cout << "1. WYRUSZ NA PRZYGODE - nacisnij '1' " << endl;
        cout << "2. ZAJRZYJ DO PLECAKA - nacisnij '2' \n" << endl;
        cout << "------------------------------------" << endl;
        cout << "------------------------------------" << endl;
        cout << "------------------------------------" << endl;
        cout << "------------------------------------" << endl;
        cout << "------------------------------------" << endl;
        cout << "" << endl;


        cin >> wybor;

        switch(wybor)
        {
        case 1:
            cout << "WYRUSZASZ NA PRZYGODE! \n" << endl;
            przygoda(backpack, hp, obrona, atak);
            break;
        case 2:
            cout << "[ZAWARTOSC PLECAKA]: \n" << endl;   ;
            backpack.showContents();

            cout << "Wybierz przedmiot ktorego chcesz uzyc (wpisz nr): ";
            int itemIndex;
            cin >> itemIndex;

            switch (itemIndex)
            {
            case 0:
            case 1:
            case 2:
                backpack.useItem(itemIndex);
                break;
            default:
                cout << "Nieprawidlowy indeks, sprobuj ponownie." << endl;
                break;
            }
            break;
        default:
            cout << "nieznana opcja, sprobuj ponownie" << endl;
        }
    }
    return 0;
}







