#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<limits>

//構造体を定義
struct Transaction{
    /* data */
    std::string data;
    std::string item;
    std::vector<std::string> tagIn;
    //int number; 
    double amount;
    bool isIncome;
};

void addTransaction(std::vector<Transaction>& transactions){
    Transaction newTransactin;
    std::string taginput;
    bool tag = true;

    std::cout << "日付を入力してください";
    std::cin >> newTransactin.data;

    std::cout << "項目を入力してください";
    std::cin >> newTransactin.item;

    std::cout << "金額を入力してください";
    std::cin >> newTransactin.amount;

    std::cout << "収入の場合:1 支出の場合:0 を入力してください";
    std::cin >> newTransactin.isIncome;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     
    while(tag){
        std::cout << "タグを入力してください。不要な場合空白のままEnterを押してください";
        std::getline(std::cin, taginput);

        if(taginput.empty()){
            tag = false;
        }else{
            newTransactin.tagIn.push_back(taginput);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    transactions.push_back(newTransactin);
}

void saveTransaction(const std::vector<Transaction>& transactions, const std::string& filename){
    std::ofstream file(filename);

    for(const auto& t : transactions){
        file << t.data << "," << t.item << "," << t.amount << "," << (t.isIncome ? "1" : "0") << std::endl;
        for (const auto& tagout : t.tagIn){
            
        }
    }
    file.close();
}

void loadTransaction(std::vector<Transaction>& transactoins,const std::vector<std::string>& tagIn,const std::string& filename){
    std::ifstream file(filename);
    std::string line;

    //fileに保存した内容をロードする
    //","まで
    while(std::getline(file, line)){
        Transaction t;
        size_t pos = 0;

        pos = line.find(",");
        t.data = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        t.item = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(",");
        t.amount = std::stod(line.substr(0, pos));
        line.erase(0, pos + 1);

        t.isIncome = (line == "1");

        //タグの数を取得しておいてその数だけ
        pos = line.find(",");
        t.tagIn.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);

        transactoins.push_back(t);
    }
    file.close();
}

//レポートを表示する
void showReport(const std::vector<Transaction>& transactoins){
    double totalIncome = 0;
    double totalExpenses = 0;

    for (const auto& t : transactoins){
        if(t.isIncome){
            totalIncome += t.amount;
        }else{
            totalExpenses += t.amount;
        }
    }

    std::cout << "総収入" << totalIncome << "円\n";
    std::cout << "総支出" << totalExpenses << "円\n";
    std::cout << "収支" << (totalIncome - totalExpenses) << "円\n";
}

//リストを表示する
void showRist(const std::vector<Transaction>& transactoins){
    //std::string kensaku;
    for (const auto& t : transactoins){
        std::cout << t.data << "\n" << t.item << "\n" << t.amount << "\n";
        for (const auto& tagout : t.tagIn){
            std::cout << tagout << std::endl;
        }
        std::cout << "\n";
    }
    //１度表示して、ここからタグごとのリスト
    // int num[];
    // std::cout << "検索>>";
    // std::cin >> kensaku;
    // for (const auto& t : transactoins){        
    //     for (const auto& tagout : t.tagIn){
    //         if(kensaku == tagout){
    //              num << ;
    //              探索
    //         }else{}
    //     }
    // }
}

int main(){
    std::vector<Transaction> transactions;
    std::vector<std::string> tagIn;
    std::string filename = "kakeibo.csv";

    //ファイルからデータをロードする
    loadTransaction(transactions,tagIn, filename);

    //操作の選択
    while(true){
        std::cout << "アプリメニュー\n";

        std::cout << "1: 追加\n";
        std::cout << "2: レポートを表示\n";
        std::cout << "3: 保存して終了\n";
        std::cout << "4: リストを表示\n";

        std::cout << "選択:";

        int choice;
        std::cin >> choice;
    
        if(choice == 1){
            addTransaction(transactions);
        }else if (choice == 2){
            showReport(transactions);
        }else if (choice == 3){
            saveTransaction(transactions, filename);
            break;
        }else if(choice == 4){
            showRist(transactions);
        }else{
            std::cout << "無効な操作\n";
        }
    }
    return 0;
}
//日にちを数字
//日にち事のデータ
//タグの機能をつけて勘重科目ごとや趣向品と必需品を別で表示できるようにする