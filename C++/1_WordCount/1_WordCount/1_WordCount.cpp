#include <iostream>
#include <fstream>
#include <string>

class WordCounter {
private:

    int line_counter_ = 0;
    int word_counter_ = 0;
    int char_counter_ = 0;
    int byte_counter_ = 0;

    std::ifstream reading_file;

public:

    WordCounter(char* file_name) {

        reading_file.open(file_name);

        if(!reading_file.is_open()) std::cout<<"file is not openned";   

    }

    void parse() {

        if (!reading_file.is_open()) return;

        reading_file.seekg(0, std::ios::end);

        byte_counter_ = reading_file.tellg();

        reading_file.seekg(0, std::ios::beg);

        while (!reading_file.eof()) {

            bool on_word = false;
            std::string file_string;
            std::getline(reading_file, file_string, '\n');
            line_counter_++;

            for (int i = 0; i < file_string.size(); ++i) {
                

                if (on_word && file_string[i] != ' ') {
                    char_counter_++;
                } else if (!on_word && file_string[i] != ' ') {
                    char_counter_++;
                    word_counter_++;
                    on_word = true;
                } else if (on_word && file_string[i] == ' ') {
                    on_word = false;
                }
                
            }


        }

    }

    void print(char* argv_[], int argc_) {

        if(!reading_file.is_open()) return; 

        for (int i = 1; i < argc_; i++) {

            std::string commands = argv_[i];

            if (commands[0] == '-') {

                if (commands[1] == '-') {

                    if (commands == "--lines") {

                        std::cout << line_counter_ << " ";

                    } else if (commands == "--bytes") {
                        
                        std::cout << byte_counter_ << " ";

                    } else if (commands == "--words") {

                        std::cout << word_counter_ << " ";

                    } else if (commands == "--chars") {

                        std::cout<< char_counter_ << " ";

                    }

                } else {

                    if (commands.find("l") != std::string::npos) {

                        std::cout << line_counter_ << " ";

                    }

                    if (commands.find("w") != std::string::npos) {

                        std::cout << word_counter_ << " ";

                    }

                    if (commands.find("c") != std::string::npos) {

                        std::cout << byte_counter_ << " ";

                    }

                    if (commands.find("m") != std::string::npos) {

                        std::cout << char_counter_ << " ";

                    }
                }

            }
        }
        if (argc_ == 2) {
            
            std::cout << line_counter_ << " " << word_counter_ << " " << byte_counter_ << " " << char_counter_;

        }

    }

};

int main(int argc, char* argv[]) {
    
    for (int i = 1; i < argc; ++i) {

        if (argv[i][0] != '-') {

            WordCounter w(argv[i]);

            w.parse();

            w.print(argv, argc);
        }
    }

    

}
