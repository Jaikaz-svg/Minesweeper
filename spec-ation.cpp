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
    Status status{close, no};
    Coords coords;
    int env{0};
public:
    Cell() = default;
    explicit Cell(STATUS status, MINED mined):status{status, mined}{}
    void set_status_status(STATUS status){
        this->status.status = status;
    }
    void set_status_mined(MINED mined){
        this->status.mined = mined;
    }
    void set_coords(int x, int y){
        coords.x = x;
        coords.y = y;
    }
    Status get_status(){return status;}
    MINED get_mined(){return status.mined;}
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
    Field(int height, int width, float pr) : height(height), width(width), mine_prtg(pr){
        make_pole(height, width, pr);
    }
    void set_size(int, int); // no need
    void set_mine_prtg(float pr){mine_prtg = pr;}// no need
    int get_width(){return width;}
    int get_height(){return height;}

    void make_pole(int, int, float);
    void print_pole();
    Status cmp(Coords);
    int count_env(int i, int j);
    void set_status(int i, int j, STATUS st){
        pole[i][j].set_status_status(st);
    }

    bool game_running(int game_end = 1){
        if (game_end == 0) game_run = game_end;
        return game_run;
    }
};

