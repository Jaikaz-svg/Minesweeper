/*Процент, размер поля и процент мины запрашивать у 
пользователя, и размещать мины на поля в соответсвии
с этим коэффициентом(x = rand; if (rand < 20) mines[0] = True;)*/

// ? - unknown
// # - excharged
// * - mine



#include "iostream"
#include "lib.h"
#include <limits>
using namespace std;
int main(){
    Field pole;
    Coords input; 

    int height, width, flag;
    float procentage;

    cout<<"Welcom to mines\n ? - unknown\n\
 # - excharged\n 0..8 - mine quantity\n * - mine"<< endl;

    cout << "Height: "; cin >> height; 
    cout << "Width: "; cin >> width;
    cout << "Percent mines: "; cin >> procentage;

    pole.set_difficulty(height, width, procentage);
    pole.make_pole();
    pole.print_pole();

    while (pole.game_running()){
        cout<<"coords(x, y): ";
        if (cin >> input.x >> input.y >> flag){
            if (input.x > pole.get_width() || input.y > pole.get_height() || input.x == 0 || input.y == 0){
                cout << "Index out of range\n";
            }
            else {
                pole.set_status(input.y, input.x, flag);
                if (pole.loos())
                    pole.game_running(0);
                else if (pole.win())
                    pole.game_running(0);
                else pole.print_pole();
            }
        } 
        else {
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}

