#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef enum {
    OP_INCREMENT,
    OP_DECREMENT,
    OP_MOVE_HEAD_LEFT,
    OP_MOVE_HEAD_RIGHT,
    OP_INPUT,
    OP_OUTPUT,
    OP_FORW_JUMP,
    OP_BACK_JUMP
} operation_type;

typedef struct {
    operation_type op_type;
    size_t operand;
} operation;

struct operations {
    vector <operation> operations;
    size_t op_count;
    size_t tape_capacity;
};

vector <char> read_code(char* file) {
    vector <string> program;
    ifstream code(file);
    string instruction;
    while (getline(code, instruction)) {
        program.push_back(instruction);
    }
    code.close();
    vector <char> program_instructions;
    return program_instructions;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "No File Provided! correct usage : ./jit <file to compile>" << endl;
        return 1;
    }
    vector <char> program = read_code(argv[1]);
    return 0;
}