#include "RhythmGame.h"

using namespace std;

int main(int argc, char* argv[]) {
    rhythm RGame;
    string userInput;
    RGame.startMenu();
    while(true) {
        cout << endl;
        RGame.play();
        cout << "Would you like to play again? [yes/no]: ";
        getline(cin, userInput);
        if(userInput == "yes") {
            RGame.reset();
        }
        else {
            std::cout << "Play again sometime!" << std::endl;
            break;
        }
    }
    return 0;
}
