// если игрок нажимает на поле у которой MINED=yes
// идет вызов Field::game_running(0)

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
    int env{0};
public:
    Cell() = default;
    explicit Cell(STATUS status, MINED mined):condition{status, mined}{}
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
    bool loos();
};

