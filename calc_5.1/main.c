#include <stdio.h>
#include <stdlib.h>

//очередь для хранения всех цисел и символов операции
typedef struct turn {
    int size;
    char *element;
    struct turn *next;
} turn;

//список, коротый хранит каждую цифру числа
typedef struct value {
    char value;
    struct value *next;
} value;

//стек для хранения всех результатов
typedef struct stack {
    float result;
    struct stack *next;
} stack;

//функция добавления последнего эклемента в очереди
turn* add_element_turn(FILE* file, char symbol) {
    // объявили первый элемент списка с цифрами
    value* head_value;
    // чтобы не потерять первый элемент
    value* last_value;
    //выделение памяти под голову и конец списка
    head_value = (value*) malloc(sizeof(value));
    last_value = (value*) malloc(sizeof(value));
    //чтобы не потерять начало
    last_value = head_value;

    //инициализируем и выделяем память для временного элемента очереди
    turn* tmp = (turn*) malloc(sizeof(turn));

    //размер массива с числами или операциями
    int size = 0;
    //читаем символы пока не пробел => это или число или операция
    while (symbol != ' ') {
        size = size + 1;
        //если size = 1, то начало списка символами
        if (size == 1) {
            head_value->value = symbol;
            head_value->next = NULL;
            last_value = head_value;
        } else {
            value* tmp_value = (value*) malloc(sizeof(value));
            tmp_value->value = symbol;
            tmp->next = NULL;
            last_value->next = tmp_value;
            last_value = last_value->next;
        }
        //если конец файла, то выходим из цикла
        if (feof(file) != 0)
            break;
        else
            //иначе продолжаем читать символы
        if(symbol != '$')
            fscanf(file, "%c", &symbol);
        else
            break;
    }
    //возвражаемся в начало списка с числами или операциями
    last_value = head_value;
    tmp->size = size;
    tmp->element = malloc(size * sizeof(char));
    //заполняем очередь с массивами
    for (int i = 0; i < size; i++) {
        tmp->element[i] = last_value->value;
        if (last_value->next)
            last_value = last_value->next;
    }
    return tmp;
}

//добавление чисел в стэк
stack* add_element_stack(char *value, stack* head_stack) {
    stack* tmp_stack = (stack*) malloc(sizeof(stack));
    tmp_stack->next = head_stack;
    tmp_stack->result = atof(value);
    return tmp_stack;
}

//ф-я, которая выполняет операции
stack* operation(char operation, stack* element) {
    switch (operation) {
        case '+':
            element->next->result = element->next->result + element->result;
            break;
        case '-':
            element->next->result = element->next->result - element->result;
            break;
        case '*':
            element->next->result = element->next->result * element->result;
            break;
        case '/':
            element->next->result = element->next->result / element->result;
            break;
    }
    free(element);
    return element->next;
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    FILE *data_file, *result_file;
    data_file = fopen("data_file.txt", "r");
    char symbol;

    // создаём первый элемент очереди
    turn* head_turn;
    head_turn = (turn*) malloc(sizeof(turn));
    fscanf(data_file, "%c", &symbol);
    head_turn = add_element_turn(data_file, symbol);

    //инициализируем еткущий элемент очереди с числами или операциями
    turn* current_turn;
    current_turn = (turn*) malloc(sizeof(turn));
    //чтобы не потерять начало
    current_turn = head_turn;

    //читаем числа и операции пока не конец файла
    while (!feof(data_file)) {
        fscanf(data_file, "%c", &symbol);
        current_turn->next = add_element_turn(data_file, symbol);
        current_turn = current_turn->next;
    }
    fclose(data_file);

    //возвращаемся в начало очереди
    current_turn = head_turn;

    result_file = fopen("result_file.txt", "w");

    stack* head_stack = (stack*)malloc(sizeof(stack));
    head_stack = add_element_stack(current_turn->element, head_stack);

    current_turn = current_turn->next;

    while (current_turn->next) {
        if (current_turn->element[0] != '$') {
            if (current_turn->element[0] == '+'
                || (current_turn->element[0] == '-' && current_turn->size == 1)
                || current_turn->element[0] == '*' || current_turn->element[0] == '/') {
                head_stack = operation(current_turn->element[0], head_stack);
            } else {
                head_stack = add_element_stack(current_turn->element, head_stack);
            }
            current_turn = current_turn->next;
        } else {
            fprintf(result_file, "%.0f\n", head_stack->result);
            head_stack = head_stack->next;
            current_turn = current_turn->next;
        }
    }

    fclose(result_file);

    return EXIT_SUCCESS;
}