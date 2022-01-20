#include "Game.h"

#define MAX_LEVEL 200

const int XP_Level[MAX_LEVEL] = 
    {100,205,315,430,551,678,811,951,1098,1252,1414,1584,1763,1951,
    2148,2355,2572,2800,3040,3292,3556,3833,4124,4430,4751,5088,5442,
    5814,6204,6614,7044,7496,7970,8468,8991,9540,10117,10722,11358,12025,
    12726,13462,14235,15046,15898,16792,17731,18717,19752,20839,21980,23179,
    24437,25758,27145,28602,30132,31738,33424,35195,37054,39006,41056,43208,45468,
    47841,50333,52949,55696,58580,61609,64789,68128,71634,75315,79180,83239,87500,91975,
    96673,101606,106786,112225,117936,123932,130228,136839,143780,151069,158722,166758,175195,
    184054,193356,203123,213379,224147,235454,247326,259792,272881,286625,301056,316208,332118,348823,366364,
    384782,404121,424427,445748,468135,491641,516323,542239,569450,598022,628023,659524,692600,727330,763796,
    802085,842289,884503,928828,975369,1024237,1075548,1129425,1185996,1245395,1307764,1373252,1442014,1514214,
    1590024,1669625,1753206,1840966,1933114,2029869,2131462,2238135,2350141,2467748,2591235,2720896,2857040,2999992,
    3150091,3307695,3473179,3646937,3829383,4020952,4222099,4433303,4655068,4887921,5132417,5389137,5658693,5941727,
    6238913,6550958,6878605,7222635,7583866,7963159,8361416,8779586,9218665,9679698,10163782,10672071,11205774,11766162,
    12354570,12972398,13621117,14302272,15017485,15768459,16556981,17384930,18254276,19167089,20125542,21131919,22188616,
    23298146,24463153,25686409,26970828,28319469,29735541,31222417,32783636,34422917};

using namespace std;

class Character 
{
    protected:
        string name;
        int level;
        int HP;
        int ATK;
        int DEF;
        int DODGE;

    public:
        Character(string name, int level = 1, int HP = 50, int ATK = 5, int DEF = 5, int DODGE = 1) 
                 : name(name), level(level), HP(HP), ATK(ATK), DEF(DEF), DODGE(DODGE) {
                     cout << name << " was born" << endl;
        };

        ~Character() {cout << name << " was died" << endl;};
        
        virtual void attack(Character &enemy) {
            srand(time(NULL));
            int hit = rand() % enemy.ATK;
            int damage = hit > DODGE ? max(0, ATK - enemy.DEF) : 0;
            cout << name << " has attack " << enemy.name << endl;
            cout << enemy.name << " receive " << damage << " damage" << endl;
            enemy.HP -= damage;
        }   

};

class Inventory 
{
    private:
        int BOUND = 30;
        map<string, int> items;
    public: 
        void showInventory() { 
            for (auto item : items) {
                cout << "Name: " << item.first << ": " << item.second << endl;
            }
        }

        void addItem(string name, int quantity) {
            if (items.find(name) != items.end() || items.size() < BOUND)
                items[name] += quantity;
            else {
                cout << "Inventory is full" << endl;
            }
        }

        void removeItem(string name) {
            items[name]--;
            cout << name << " was used" << endl;
        }
};

class Player : public Character
{
    private: 
        int XP;
        int money;
        string Class;
        Inventory inventory;
    public:
        Player(string name, int level, int HP, int ATK, int DEF, int DODGE) 
            : Character(name, level, HP, ATK, DEF, DODGE) {
                XP = 0;
                money = 1000;
                inventory = {};
        }

        void levelUp() { 
            level++;
            ATK += 10;
            DEF += 10;
            DODGE += 5;
        }

        friend void Battle(Player &player, Monster &monster);

};

class Monster : public Character
{
    private:
        int wraith;
        int rate;
    public:
        Monster(string name, int level, int HP, int ATK, int DEF, int DODGE, int rate = 1) 
        : Character(name, level, HP, ATK, DEF, DODGE){
            wraith = 0;
            this->rate = rate;
        }

        friend void Battle(Player &player, Monster &monster);
};

void Battle(Player &player, Monster &monster) {
    cout << "Battle: " << player.name << " vs " << monster.name << endl;

}