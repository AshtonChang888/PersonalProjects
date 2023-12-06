#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class rhythm {
    public:
        rhythm();
        ~rhythm();
        void startMenu();
        void randomize();
        void parse(std::string filename);
        void play();
        void reset();
        
    private:
        void printNote(std::vector<int>& bar);
        std::string convertToBeats(std::vector<int>& bar);
        void clean(std::string& input);
        double getFinalScore();
        std::vector<std::vector<int>> noteSeq;
        int score;
        int timeSig = 4;
        int duration = 5;
};

rhythm::rhythm() : score(0) {}

rhythm::~rhythm() {}

void rhythm::startMenu() {
    std::string userInput = "1";
    std::cout << "Welcome to the Rhythm Game!" << std::endl;
    std::cout << "Based on the notes that you see, you should add \'+\' for eigthnotes, \'e+a\' for sixteenth notes, and \'R\' for rests." << std::endl;
    std::cout << "For example, you would enter \'1+ 2e+a R\' for: " << " |￣|   |〓|〓|〓|    " << std::endl;
    std::cout << "                                              @  @   @  @  @  @    𝄽 " << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;

    //std::cout << "Would you like to play with a random assortment of notes, or with a premade text file?" << std::endl;
    //std::cout << "1 for randomized, 2 for premade file" << std::endl;
    //getline(std::cin, userInput);
    if(userInput == "1") {
        randomize();
    }
    if(userInput == "2") {
        std::cout << "Provide a textfile: ";
        getline(std::cin, userInput);
        parse(userInput);
    }
}

void rhythm::randomize() {
    srand(time(0));
    for(int i = 0; i < duration; i++) {
        std::vector<int> bar;
        double counter = 0;
        while(counter < timeSig) {
            int note = rand() % 4;
            counter++;
            if(counter > timeSig) {
                break;
            }
            bar.push_back(note);
        }
        noteSeq.push_back(bar);
    }
}

void rhythm::parse(std::string filename) {
    std::ifstream ifile(filename);
    if(ifile.fail()) {
        std::cout << "Unable to open file" << std::endl;
    }
    ifile.close();
    //TODO
}

void rhythm::printNote(std::vector<int>& bar) {
    std::string upperHalf[4] = {"   | ", " |￣| ", " |〓|〓|〓|", "    "};
    std::string lowerHalf[4] = {"  @ ", "@  @ ", "@  @  @  @", " 𝄽 "};
    for(unsigned i = 0; i < bar.size(); i++) {
        std::cout << upperHalf[bar[i]] << " ";
    } 
    std::cout << std::endl;
    for(unsigned j = 0; j < bar.size(); j++) {
        std::cout << lowerHalf[bar[j]] << "  ";
    }
    std::cout << std::endl;
}

std::string rhythm::convertToBeats(std::vector<int>& bar) {
    std::string fullString = "";
    for(unsigned i = 0; i < bar.size(); i++) {
        int num = bar[i];
        if(num == 3) {
            fullString += "R";
        }
        else {
            fullString += std::to_string(i + 1);
            if(num == 1) {
                fullString += "+";
            }
            if(num == 2) {
                fullString += "e+a";
            }
        }
        if(i != bar.size() - 1) {
            fullString += " ";
        }
    }
    return fullString;
}

void rhythm::clean(std::string& input) {
    std::stringstream ss(input);
    std::string updated = "";
    char oneChar;
    while(ss >> oneChar) {
        updated += oneChar;
        ss >> std::ws;
    }
    input = updated;
}

void rhythm::play() {
    srand(time(0));
    for(int i = 0; i < duration; i++) {
        printNote(noteSeq[i]);
        std::string correct = convertToBeats(noteSeq[i]);
        std::string copyCorrect = correct;
        std::string userInput;
        std::cout << "Enter rhythm: ";
        getline(std::cin, userInput);
        clean(userInput);
        clean(copyCorrect);
        if(userInput == copyCorrect) {
            std::cout << "Correct!" << std::endl << std::endl;
            score++;
        }
        else {
            std::cout << "Incorrect, correct answer: " << correct << std::endl <<std::endl;
        }
    }
    std::cout << "Final score: " << getFinalScore() * 100 << "%" << std::endl;
}

double rhythm::getFinalScore() {
    return score / double(duration);
}

void rhythm::reset() {
    noteSeq.clear();
    randomize();
}