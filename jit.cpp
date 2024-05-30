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
    size_t tape_capacity = 0;
};

operations ops;


vector <char> read_and_tokenize_code(char* file) {
    vector <string> program;
    ifstream code(file);
    string instruction;
    while (getline(code, instruction)) {
        program.push_back(instruction);
    }
    code.close();
    vector <char> program_instructions;
    for (size_t i = 0; i < program.size(); i++) {
        for (size_t j = 0; j < program[i].size(); j++) {
            if (program[i][j] == '+' || program[i][j] == '-' || program[i][j] == '>' || program[i][j] == '<'
            || program[i][j] == '.' || program[i][j] == ',' || program[i][j] == '[' || program[i][j] == ']') {
                program_instructions.push_back(program[i][j]);
            }
        }
    }
    return program_instructions;
}

void init_ops(vector <char> program) {
    ops.operations.clear();
    ops.op_count = 0;
    ops.tape_capacity = 0;
    for (size_t i = 0; i < program.size(); i++) {
        operation op;
        size_t count = 1;
        while (i + 1 < program.size() && program[i] == program[i + 1]) {
            count++;
            i++;
        }
        switch (program[i]) {
            case '+':
                op.op_type = OP_INCREMENT;
                break;
            case '-':
                op.op_type = OP_DECREMENT;
                break;
            case '>':
                op.op_type = OP_MOVE_HEAD_RIGHT;
                ops.tape_capacity += count;
                break;
            case '<':
                op.op_type = OP_MOVE_HEAD_LEFT;
                ops.tape_capacity -= count;
                break;
            case '.':
                op.op_type = OP_OUTPUT;
                break;
            case ',':
                op.op_type = OP_INPUT;
                break;
            // these two operations (forward jump and backward jump) do not work like this
            // change them later
            case '[':
                op.op_type = OP_FORW_JUMP;
                break;
            case ']':
                op.op_type = OP_BACK_JUMP;
                break;
            default:
                continue;
        }
        op.operand = count;
        ops.operations.push_back(op);
        ops.op_count++;
    }
}


int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "No File Provided! correct usage : ./jit <file to compile>" << endl;
        return 1;
    }
    vector <char> program = read_and_tokenize_code(argv[1]);
    init_ops(program);

    return 0;
}