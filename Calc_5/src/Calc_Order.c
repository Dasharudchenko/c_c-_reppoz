#include <stdio.h>
#include <stdlib.h>

//список для хранения всех цисел и символов операции
typedef struct list_main {
	int size;
	char *element;
	struct list_main *next;
} list_main;

//список, коротый храник каждую цифру числа
typedef struct list_value {
	char value;
	struct list_value *next;
} list_value;

//стек для хранения всех результатов
typedef struct stack {
	float result;
	struct stack *next;
} stack;

//ф-я, которая находит последний элемнт списка
list_main* get_last_element_list(list_main* head_list) {
	if (head_list == NULL)
		return NULL;
	//пока существует следующий элемент, переходим к следующему элементу
	while (head_list->next) {
		head_list = head_list->next;
	}
	return head_list;
}

//функция добавления последнего эклемента в список
void add_element_list(FILE* file, char symbol, list_main* head_list) {
	// объявили первый элемент списка с цифрами
	list_value* head_value;
	// чтобы не потерять первый элемент
	list_value* last_value;
	//выделение памяти под голову и конец списка
	head_value = (list_value*) malloc(sizeof(list_value));
	last_value = (list_value*) malloc(sizeof(list_value));
	//чтобы не потерять начало
	last_value = head_value;

	//инициализируем и выделяем память для временного элемента списка
	list_main* tmp = (list_main*) malloc(sizeof(list_main));

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
			list_value* tmp_number = (list_value*) malloc(sizeof(list_value));
			tmp_number->value = symbol;
			tmp->next = NULL;
			last_value->next = tmp_number;
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
	//заполняем список с массивами
	for (int i = 0; i < size; i++) {
		tmp->element[i] = last_value->value;
		if (last_value->next)
			last_value = last_value->next;
	}

	list_main* last = get_last_element_list(head_list);
	last->next = tmp;
}

//добавление чисел в стэк
stack* add_element_stack(char *number, stack* head_stack) {
	stack* tmp = (stack*) malloc(sizeof(stack));
	tmp->next = head_stack;
	tmp->result = atof(number);
	return tmp;
}

//фунцияя, которая выполняет операции
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

	// создаём первый элемент списка
	list_main* head_list;
	head_list = (list_main*) malloc(sizeof(list_main));
	fscanf(data_file, "%c", &symbol);
	add_element_list(data_file, symbol, head_list);

	//читаем числа и операции пока не конец файла
	while (!feof(data_file)) {
		fscanf(data_file, "%c", &symbol);
		add_element_list(data_file, symbol, head_list);
	}
	fclose(data_file);
	//инициализируем еткущий элемент списка с числами или операциями
	list_main* current_list;
	current_list = (list_main*) malloc(sizeof(list_main));
	//чтобы не потерять начало
	current_list = head_list->next;
	result_file = fopen("result_file.txt", "w");

	//объявляем начало стека
	stack* head_stack = (stack*)malloc(sizeof(stack));
	head_stack = add_element_stack(current_list->element, head_stack);
	current_list = current_list->next;

	while (current_list->next) {
		if (current_list->element[0] != '$') {
			if (current_list->element[0] == '+'
				|| (current_list->element[0] == '-' && current_list->size == 1)
				|| current_list->element[0] == '*' || current_list->element[0] == '/') {
				head_stack = operation(current_list->element[0], head_stack);
			} else {
				head_stack = add_element_stack(current_list->element, head_stack);
			}
			current_list = current_list->next;
		} else {
			fprintf(result_file, "%.0f\n", head_stack->result);
			head_stack = head_stack->next;
			current_list = current_list->next;
		}
	}

	fclose(result_file);

	return EXIT_SUCCESS;
}
