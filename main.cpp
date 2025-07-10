/*Процент размер поля и процент мины запрашивать у 
пользователя, и размещать мины на поля в соответсвии
с этим коэффициентом(x = rand; if (rand < 20) mines[0] = True;)*/





#include "iostream"
#include "lib.h"
using namespace std;
int main(){
    Coords input; 
    Field pole;
    int height,width;
    float procentage;
    cout<<"Welcom to mines"<< endl;
    cout << "Height: \n"; cin >> height; 
    cout << "Width: \n"; cin >> width;
    pole.set_size(width, height);
    cout << "Percent mines: \n"; cin >> procentage;
    pole.set_mine_prtg(procentage);
    while (pole.game_running()){
        cout<<"coords: "; cin >> input.x >> input.y; cout << endl;    

    }
    return 0;
}

