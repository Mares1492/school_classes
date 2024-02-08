#include <iostream>
#include <fstream>
#include <vector>

struct Note {
    int voice;
    int pitch;
};

// Failinimed konstantidena
const std::string input_file_path = "../input/hargsis.txt";
const std::string output_file_path = "hargval.txt";

// Funktsioon avab sisendfaili ja kontrollib et oleks avatud
bool open_input_file(std::ifstream& input_file) {
    input_file.open(input_file_path);
    return input_file.is_open();
}

// Funktsioon avab väljundfaili ja kontrollib
bool open_output_file(std::ofstream& output_file) {
    output_file.open(output_file_path);
    return output_file.is_open();
}

// Funktsioon otsib ja kirjutab paralleelsed kvindid
void find_and_write_parallel_fifths(const std::vector<std::vector<Note>>& notes, std::ostream& output) {
    bool has_parallel_fifths = false;

    for (size_t i = 0; i < notes.size() - 1; i++) {
        for (size_t s = 0; s < notes[i].size(); s++) {
            for (size_t t = s + 1; t < notes[i].size(); t++) {
                if ((notes[i][s].pitch - notes[i][t].pitch) % 12 == 7 &&
                    (notes[i + 1][s].pitch - notes[i + 1][t].pitch) % 12 == 7) {
                    has_parallel_fifths = true;
                    output << i + 1 << " " << s + 1 << " " << t + 1 << "\n";
                    std::cout << i + 1 << " " << s + 1 << " " << t + 1 << "\n";
                }
            }
        }
    }

    if (!has_parallel_fifths) {
        output << "POLE\n";
    }
}

int main() {
    std::ifstream input_file;
    std::ofstream output_file;

    // Kontrollime, kas sisendfaili avamine õnnestus
    if (!open_input_file(input_file)) {
        std::cerr << "Error opening input file: " << input_file_path << "\n";
        return 1;
    }

    // Kontrollime, kas valjundfaili avamine õnnestus, ja loome uue, kui vajalik
    if (!open_output_file(output_file)) {
        std::cout << "Output file not found. Creating a new one: " << output_file_path << "\n";
        output_file.open(output_file_path);
    }

    int N, K;
    if (!(input_file >> N >> K) || N <= 0 || K <= 0) {
        std::cerr << "Invalid or missing N or K values in input file.\n";
        return 1;
    }

    std::vector<std::vector<Note>> notes(N, std::vector<Note>(K));

    // Loeme noodid sisendfailist
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            input_file >> notes[i][j].pitch;
            notes[i][j].voice = j;
        }
    }
    
    // Leiame ja kirjutame paralleelsed kvindid valjundfaili
    find_and_write_parallel_fifths(notes, output_file);

    input_file.close();
    output_file.close();

    return 0;
}
