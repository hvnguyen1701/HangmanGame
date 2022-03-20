#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_BAD_GUESSES = 7;
const string DATA_FILE_NAME = "data.txt";
const string FIGURE[] = {
    "   -------------    \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |                \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",

    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |                \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",
    
    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |           |    \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",
    
    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|    \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",
    
    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\   \n"
    "   |                \n"
    "   |     \n"
    " -----   \n",
    
    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\  \n"
    "   |          /     \n"
    "   |     \n"
    " -----   \n",
    
    "   -------------    \n"
    "   |           |    \n"
    "   |           O    \n"
    "   |          /|\\  \n"
    "   |          / \\  \n"
    "   |     \n"
    " -----   \n"};

string chooseWord(const string &dataFileName);
char readAGuess();
bool contains(const string &word, const char &ch);
void renderGame(const string &guessedWord, const string &badGuesses);
void updateGuessedWord(string &guessedWord, const string &secretWord, const char &guess);
void removeDuplicate(string &s);
void printBadGuesses(string badGuesses);
void displayFinalResult(const bool &isVictorious, const string &secretWord, const int &badGuessCount);

int main() {
    srand(time(nullptr));
    string secretWord = chooseWord(DATA_FILE_NAME), guessedWord = string(secretWord.size(), '-'), badGuesses = "";
    // Game loop
    do {
        renderGame(guessedWord, badGuesses);
        char guess = readAGuess();
        if (contains(secretWord, guess)) updateGuessedWord(guessedWord, secretWord, guess);
        else badGuesses += guess;
    } while (badGuesses.size() < MAX_BAD_GUESSES && guessedWord != secretWord);
    renderGame(guessedWord, badGuesses);
    displayFinalResult(badGuesses.size() < MAX_BAD_GUESSES, secretWord, badGuesses.size());

    return 0;
}

string chooseWord(const string &dataFileName) {
    ifstream file(dataFileName);
    vector<string> wordList;
    string word;
    while (file >> word) wordList.push_back(word);
    file.close();

    int randomIndex = rand()%wordList.size();
    return wordList[randomIndex];
}

char readAGuess() {
    char ch;
    cout << "\nChoose a character (A-Z): ";
    cin >> ch;
    return toupper(ch);
}

bool contains(const string &word, const char &ch) {
    return (word.find_first_of(ch) != string::npos);
}

void updateGuessedWord(string &guessedWord, const string &secretWord, const char &guess) {
    for (int i = 0; i < secretWord.size(); i++)
        if (guess == secretWord[i]) guessedWord[i] = guess;
}

void removeDuplicate(string &s) {
    for (int i = 0; i < s.size(); i++)
        for (int j = i + 1; j < s.size(); j++)
            if (s[i] == s[j]) {
                s[i] = '*';
                break;
            }
    while (s.find('*') != string::npos) s.erase(s.find('*'), 1);
}

void printBadGuesses(string badGuesses) {
    if (badGuesses.size() == 0) return;
    removeDuplicate(badGuesses);
    cout << "Wrong guessed characters list: ";
    for (int i = 0; i < (int)badGuesses.size() - 1; i++) cout << badGuesses[i] << ", ";
    cout << badGuesses.back() << "\n";
}

void renderGame(const string &guessedWord, const string &badGuesses) {
    int badGuessCount = badGuesses.size();
    cout << "\n\n\n\n\n\n\n\n\n\n" << FIGURE[badGuessCount];
    cout << "\nSecret word: " << guessedWord << "\n";
    cout << "\nNumber of wrong guesses: " << badGuessCount << "\n";
    printBadGuesses(badGuesses);
}

void displayFinalResult(const bool &isVictorious, const string &secretWord, const int &badGuessCount) {
    cout << "\n\n************* GAME OVER! *************\n\n";
    if (isVictorious) cout << "       Congratulations! You win!";
    else cout << "You lost :(. The correct word is " << secretWord << ".";
    cout << "\nYou guessed " << badGuessCount << " wrong character" << ((badGuessCount != 1) ? "s" : "");
    cout << " that " << ((badGuessCount != 1) ? "are" : "is") << " not in the secret word.\n\n";
}