/*Процент размер поля и процент мины запрашивать у 
пользователя, и размещать мины на поля в соответсвии
с этим коэффициентом(x = rand; if (rand < 20) mines[0] = True;)*/

// ? - unknown
// # - excharged
// * - mine



#include "iostream"
#include "lib.h"
using namespace std;
int main(){
    Coords input; 
    Field pole;
    int height,width;
    float procentage;
    cout<<"Welcom to mines\n ? - unknown\n\
 # - excharged\n 0..8 - mine quantity\n * - mine"<< endl;
    cout << "Height: "; cin >> height; 
    cout << "Width: "; cin >> width;
    pole.set_size(width, height);
    cout << "Percent mines: "; cin >> procentage;
    pole.set_mine_prtg(procentage);
    pole.make_pole(height, width, procentage);
    while (pole.game_running()){
        pole.print_pole();
        cout<<"coords: "; cin >> input.x >> input.y; cout << endl;


    }
    return 0;
}

