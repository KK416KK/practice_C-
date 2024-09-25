#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

void displayCurrentState(const std::string& guessedWord, int remainingGuesses)
{
    std::cout << "Current word: " << guessedWord << "\n";
    std::cout << "Remaining guesses: " << remainingGuesses << "\n";
}

//単語が完成したかを確認
bool isWordGuessed(const std::string& word, std::string& guessedWord){
    return word == guessedWord;
}

//文字があってた時表示する
void updateGuessedWord(const std::string& word, std::string& guessedword, char guess){
    for (size_t i = 0; i < word.length(); ++i){
        if (word [i] == guess){
            guessedword[i] = guess;
        }
    }
}

int main(){
    const std::string wordToGuess = "programing"; //単語
    std::string guessedWord(wordToGuess.length(),'_'); //単語の文字数と同じ長さのアンダーバー
    std::vector<char> incorrectGuesses;
    int remainingGuesses = 6; //試行回数
    std::cout << "Welcome to humgman \n";
    while (remainingGuesses > 0 && ! isWordGuessed(wordToGuess, guessedWord)){
        displayCurrentState(guessedWord, remainingGuesses);
        std::cout << "Enter your guess: ";
        char guess;
        std::cin >> guess; //文字を入力
        //同じ文字を入力したとき
        if(std::find(incorrectGuesses.begin(),incorrectGuesses.end(),guess) != incorrectGuesses.end() || std::find(guessedWord.begin(), guessedWord.end(), guess) != guessedWord.end()){
            std::cout << "You already guessedWord that letter. Try again.\n";
            continue;
        }

        //入力した文字が入っているか
        if (wordToGuess.find(guess) != std::string::npos){
            updateGuessedWord(wordToGuess, guessedWord, guess);
        }else{
            incorrectGuesses.push_back(guess); --remainingGuesses;
        }
    }

    //終了時
    if(isWordGuessed(wordToGuess, guessedWord)){
        std::cout << "Congratulations! You guessed the word: " << wordToGuess << "\n";
    }else{
        std::cout << "Sorry, You ran out og guesses. the word was: " << wordToGuess << "\n";
    }

}