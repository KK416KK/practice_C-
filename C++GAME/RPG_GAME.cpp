#include<iostream>
#include<string>
#include<random>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;

class Player{
    public:
    string name;
    double hitpoint;
    double magicpoint;
    double attackpoint;
    double protectingpoint;
    int level;
    int money;
    int point;

    //コンストラクタ
    Player(string a,double b,double c,double d,double e,int f,int g,int h) : 
    name(a),hitpoint(b),magicpoint(c),attackpoint(d),protectingpoint(e),level(f),money(g),point(h){};
};

class Enemy_data{
    public:
    string name;
    double hitpoint;
    double attackpoint;
    double protectingpoint;
    int cp;

    //コンストラクタ
    Enemy_data(string a,double b,double c,double d,int e) :
     name(a),hitpoint(b),attackpoint(c),protectingpoint(d),cp(e){};
};

class dungeon{

};

class items{
    public:
    string item;
    //アイテムの種類:武器、回復など 1~9 武器、10~19 戦闘中・フィールドで使う、20~30フィールドで使う,31~40使えない
    int itemcode;
    int itemsuu;
    int valuees;

    items(string a,int b ,int c ,int d):
    item(a),itemcode(b),itemsuu(c),valuees(d){};

};



string Field[] = {"town","field","dungeon" };
int division;
//モンスターの全データ
std::vector<Enemy_data> enemyes;
//特定の区域に出るモンスター
std::vector<Enemy_data> en;
//戦闘時の敵パーティ
std::vector<Enemy_data> enemy_party;
std::vector<Player> player;
Player Myplayer;
std::vector<items> allitem;
std::vector<items> buyitem;
int dungeons = 0;

//主人公のステータス
void statce(int a){
    Myplayer.level = a;
    Myplayer.hitpoint = 100 + 2 * Myplayer.level;
    Myplayer.magicpoint = 80 + 2 * Myplayer.level;
    Myplayer.attackpoint = 60 + 3 * Myplayer.level;
    Myplayer.protectingpoint = 50 + 2 * Myplayer.level;
    Myplayer.money = 100;
    Myplayer.point = 0;
}

int main(){
    int start;
    enemy();
    item();

    while(true){
        std::cout << "RPG for C++" << "\n" << std::endl;
        std::cout << "ゲームを開始しますか" << std::endl;
        std::cout << "1:はじめから" << std::endl;
        std::cout << "2:続きから" << std::endl;
        std::cout << "3:終了" << std::endl;
        std::cin >> start;

        switch (start)
        {
        case 1:
            std::cout << "名前を入力してください" << endl;
            std::cin >> Myplayer.name;
            statce(1);
            game_start(start -1);
            break;
        case 2:
            //load();
            break;
        case 3:
            /*終了*/
            break;
        default:
            break;
        }
    }
} // namespace GAME

int game_start(int y){
    int move;
    while(true){
        std::cout << "現在:" << Field[y] << endl;
        std::cout << "何をしますか？>>" << endl;
        std::cout << "1:探索にでかける" << endl;
        std::cout << "2:町を探索" << endl;
        std::cout << "3:ステータスを見る" << endl;
        std::cin >> move;

        switch (move){
        case 1:
            serch();
            break;
        case 2:
            town();
            break;
        case 3:
            std::cout << "レベル:" << Myplayer.level << endl;
            std::cout << "HP:" << Myplayer.hitpoint << "/" <<  100 + 2 * Myplayer.level << endl;
            std::cout << "MP:" << Myplayer.magicpoint << "/" << 80 + 2 * Myplayer.level << endl;
            std::cout << "攻撃力:" << Myplayer.attackpoint << endl;
            std::cout << "防御力:" << Myplayer.protectingpoint << endl;
            std::cout << "所持金:" << Myplayer.money << endl;
            break;  
        default:
            break;
        }
    }  
}

//探索する
int serch(){
    int move;
    int number;
    division = 0;
    //フィールドに出現するモンスターを取得
    party_of_enemy(division);

    std::cout << "現在:" << Field[division + 1] << endl;
    std::cout << "何をしますか？>>" << endl;
    std::cout << "1:周辺を探索" << endl;
    std::cout << "2:町へ帰る" << endl;
    std::cout << "3:ステータスを見る" << endl;
    std::cout << "4:アイテムを使う" << endl;
    std::cout << "5:ダンジョンに入る" << endl;
    std::cin >> move;

    switch (move)
    {
    case 1:
        number = random_few(100);
        //20%の確立で敵と戦うもしくはダンジョンを見つける
        if(number <= 20){
            battle();
            enemy_party.clear();
        }else if(number >= 80){
            discovery();
        }
        break;
    case 2:
        //町へ戻る
        game_start(0);
        break;
    case 3:
        std::cout << "レベル:" << Myplayer.level << endl;
        std::cout << "HP:" << Myplayer.hitpoint << "/" <<  100 + 2 * Myplayer.level << endl;
        std::cout << "MP:" << Myplayer.magicpoint << "/" << 80 + 2 * Myplayer.level << endl;
        std::cout << "攻撃力:" << Myplayer.attackpoint << endl;
        std::cout << "防御力:" << Myplayer.protectingpoint << endl;
        std::cout << "所持金:" << Myplayer.money << endl;
        break;
    case 5:
        if(dungeons == 0){
            std::cout << "ダンジョンがありません" << endl;
        }else{}
        break;
    default:
        break;
    }

}

int battle(){
    int moves;
    //敵の数
    int enem1 = random_few(3);
    bool turn = true;

    for (int c = 1; c <= enem1;c++){
        //敵の種類
        int enem2 = random_few(en.size());
        enemy_party.push_back(en[enem2]);
    }
    for(const auto& object : enemy_party){
        string ename = object.name;
        std::cout << ename << "があらわれた" << endl;       
    }

    while(turn){
        std::cout << "ステータス:" << endl;
        std::cout << Myplayer.hitpoint << "/" << 100 + 2 * Myplayer.level << endl;
        int de = 1;
        for(const auto& object : enemy_party){
            string ename = object.name;
            int hp = object.hitpoint;
            std::cout << de << ":" << ename << endl;
            std::cout << "HP:" << hp << endl;
            de++;       
        }
        std::cout << "行動を選択:" << endl;  
        std::cout << "1:攻撃" << endl;
        std::cout << "2:防御" << endl;
        std::cout << "3:技" << endl;
        std::cout << "4:逃げる" << endl;
        std::cin >>  moves;
        switch (moves)
        {
        case 1:
        int i = 1;
        int j;
        std::cout << "誰を攻撃しますか" << endl;
        for(const auto& object : enemy_party){
            string ename = object.name;
            std::cout << i << ":" << ename << endl;
            i++;       
        }
        std::cout << i << ":" << "戻る" << endl;
        std::cin >> j;
        if(enemy_party.size() < j){
            break;
        }else{
            turn_battle(j);
        }
        break;

        case 2:
            
            break;
        case 3:
            break;
        case 4:
            std::cout << "戦闘を放棄した" << endl;
            return 0;
            break;
        default:
            break;
        }
    }
}

int turn_battle(int a){
    int c;
    int damage;
    if (enemy_party.size() < a){
        std::cout << "PLAYERは" << enemy_party[a].name << "に攻撃" << endl;
        c = a * 100;
        damage = attack(c);
        enemy_party[a].hitpoint -= damage; 
        std::cout <<  enemy_party[a].name << "は" << damage << "ダメージを受けた" << endl;
        if(enemy_party[a].hitpoint < 0){
            std::cout <<  enemy_party[a].name << "を倒した" << endl;
            enemy_party.erase(enemy_party.begin() + a);
            if(enemy_party.size() == 0){
                std::cout << "戦いに勝利した" << endl;
                return 0;
            }
        }
    }
    
    for (int y = 1;y <= enemy_party.size(); y++){
        int g = 0;
        if(enemy_party[y].hitpoint > 0){
            std::cout << enemy_party[y].name << "の攻撃" << endl;
            g = y * 1000;
            damage = attack(g);
            if (Myplayer.hitpoint < 0){
                std::cout << "GAME OVER" << endl;
                main();
            }
        }
    }  
}

int attack(int a){
    int b;
    int ap;
    int ram = random_few(100) * 0.1;
    
    if (a > 99 && 1000 > a){
        b = a / 100;
        ap = Myplayer.attackpoint - enemy_party[b].protectingpoint + ram;
        if(ap > 0){
            return ap;
        }else{
            return 0;
        }
    }else if(a > 999 && a < 10000){
        b = a / 1000;
        ap = enemy_party[b].attackpoint;
    }
}

int random_few(int a){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> rand(1,a);
    int number = rand(mt);
    return number;
}

int discovery(){
    std::cout << "ダンジョンを見つけた" << endl;
    dungeons += 1;
}

//モンスターのデータを取得する
int enemy(){
    std::ifstream file("enemy_data.csv");
    std::string line;

    //
    std::getline(file,line);
    while(std::getline(file,line)){
        std::stringstream ss(line);
        std::string name ,hp ,ap ,pp ,cp; 

        std::getline(ss,name,',');
        std::getline(ss,hp,',');
        std::getline(ss,ap,',');
        std::getline(ss,pp,',');
        std::getline(ss,cp,',');

        double hitp = std::stod(hp);
        double attp = std::stod(ap);
        double prop = std::stod(pp);
        double codp = std::stoi(cp);


        enemyes.push_back(Enemy_data(name,hitp,attp,prop,codp));
    }
    return 0;
}

int item(){
    std::ifstream file("itemlist.csv");
    std::string line;

    //
    std::getline(file,line);
    while(std::getline(file,line)){
        std::stringstream ss(line);
        std::string name ,code ,suu ,val; 

        std::getline(ss,name,',');
        std::getline(ss,code,',');
        std::getline(ss,suu,',');
        std::getline(ss,val,',');

        int Icode = std::stod(code);
        int Ival = std::stod(val);

        allitem.push_back(items(name,Icode,0,Ival));
    }
    return 0;
}

void party_of_enemy(int a){    
    for(const auto& obj : enemyes){
        if(obj.cp == a){
            en.push_back(obj);
        }
    }
}

void town(){
    int move;

    while(true){
        std::cout << "現在:" << Field[division + 1] << endl;
        std::cout << "何をしますか？>>" << endl;
        std::cout << "1:武器屋" << endl;
        std::cout << "2:アイテム屋" << endl;
        std::cout << "3:ギルド" << endl;
        std::cout << "4:自宅" << endl;
        std::cout << "5:戻る" << endl;
        std::cin >> move;

        switch (move)
        {
        case 1:
        case 2:
        int i = 1;
        int itembuy;
            std::cout << "何を買いますか？" << endl;
            
            for(const auto& object : allitem){
                if(object.itemcode << 10 && object.itemcode >> 0 && move == 1){
                    buyitem.push_back(object);
                }else if (object.itemcode << 30 && object.itemcode >> 9 && move == 2){
                    buyitem.push_back(object);
                }else{
                    break;
                }
                std::cout << i << ":" << object.item << endl;
                i++;                      
            }
            std::cin >> itembuy;
            if(itembuy <= buyitem.size() && itembuy > 0){
                std::cout << buyitem[itembuy - 1].item << "を買った" << endl;
                int cod = 0;
                for(const auto& object : allitem){
                    if(buyitem[itembuy - 1].itemcode == cod){
                        break;
                    }else{
                        cod++;
                    }
                }
                allitem[cod].itemsuu += 1;                
            }
            break;
        case 5:
            game_start(0);
            break;
        
        default:
            break;
        }
    }
}