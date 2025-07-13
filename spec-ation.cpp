/***********************************************************************************************************************************
 
  The game implementation consists of two core classes: the  base  Cell class and its derived Field class.
  All cell operations must be performed exclusively through the Field class interface. 
  
  Each Cell object contains two fundamental components: coordinate data (x,y) and state information.
  The state includes two properties: a status field (which can be CLOSED, OPEN, or EXCHARGED) and a mined flag (no/yes).

  During initialization, the make_pole() method sets all cells to CLOSED status and randomly distributes mines across the field.

  When opening a cell, the system changes its status to OPEN and reveals its contents.
  When flagging a cell (if they provide 1 as the third argument), the cell status toggles to EXCHARGED. 

  The game achieves victory when all cells satisfy one of two conditions:
    1. condition_mined = yes && condition_status = excharged
    2. condition_mined = no && condition_status = open

  This state verification occurs automatically after each move, with the Field class checking the entire 
  game state according to these termination conditions.
  
  The implementation enforces strong encapsulation, with the Field class serving as the only interface for all cell manipulations.

************************************************************************************************************************************/

struct Coords{ 
    int x;
    int y;
};

class Cell{
public:
    enum STATUS {open, close, excharged};
    enum MINED {no, yes};
    struct Status{
        STATUS status;
        MINED mined;
    };
 protected:
    Status condition{close, no};
    Coords coords;
    int env{0}; // количество мин вокруг
public:
    Cell() = default;
    explicit Cell(STATUS status, MINED mined) : condition{status, mined}{}
    void set_condition_status(STATUS status){
        this->condition.status = status;
    }
    void set_condition_mined(MINED mined){
        this->condition.mined = mined;
    }
    void set_coords(int x, int y){
        coords.x = x;
        coords.y = y;
    }
    STATUS get_condition_status(){return condition.status;}
    MINED get_condition_mined(){return condition.mined;}
    Coords get_coords(){return coords;}
    void print_cell(int);
};


class Field : public Cell{
    bool game_run{1};
    int width{0};
    int height{0};
    float mine_prtg{0.0};
    Cell pole[50][50];
public:
    Field() = default;
    void set_difficulty(int h, int w, float pr){
        height = h;
        width = w;
        mine_prtg = pr;
    }
    int get_width(){return width;}
    int get_height(){return height;}

    void make_pole();
    void print_pole();
    int count_env(int i, int j);
    void set_status(int i, int j, int flag);

    bool game_running(int);
    bool win();
    bool lose();
};

