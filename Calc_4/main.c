/*
============================================================================
 Name        :  Kalkulyator
 Author      :  Daria Rudchenko
 Version     :
 Copyright   :  free
 Description :  Kalkulyator 4 in c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Структура, где хранятся исходные данные из файла
typedef struct list_data {
	char operation;
	char calculator;
	int size;
	float *value_1;
	float *value_2;
	struct list_data *next;
} list_data;

// Структура, где хранится результат выполнения калькулятора
typedef struct list_result {
	float* result;
	struct list_result *next;
} list_result;


// Функция получения последнего элемента списка
list_data* get_last_data(list_data* element){
	if(element == NULL){
		return NULL;
	}
	while(element->next){
		element = element->next;
	}
	return element;
}

list_result* get_last_result(list_result* element){
	if(element == NULL){
		return NULL;
	}
	while(element->next){
		element = element->next;
	}
	return element;
}

// Функция добавления первого элемента
void add_head_data(list_data** head, FILE* read_file){
	// Выделяем память для временного елемента списка
	list_data* tmp = (list_data*)malloc(sizeof(list_data));
	// Читаем первые два символа из файла и записываем их в элемент списока
	fscanf(read_file, "%c %c", &tmp->operation, &tmp->calculator);
	// Если "v", то читаем размерность векторов
	if(tmp->calculator == 'v'){
		fscanf(read_file, "%d", &tmp->size);
	} else {  // Иначе размерность векторов = 1 => обычные числа
		tmp->size = 1;
	}
	// Выделяем память для двух переменных, хранящие наши числа
	tmp->value_1 = malloc(tmp->size * sizeof(float));
	tmp->value_2 = malloc(tmp->size * sizeof(float));
	// Считываем сначала все числа в первую переменную...
	for(int i = 0; i < tmp->size; i++){
		fscanf(read_file, "%f", &tmp->value_1[i]);
	}
	// ...затем во вторую
	for(int i = 0; i < tmp->size; i++){
		fscanf(read_file, "%f", &tmp->value_2[i]);
	}
	// Кидаем указатель в NULL
	tmp->next = (*head);
	(*head) = tmp;
}

void number_calculator(list_data* data, list_result* result);
void vector_calculator(list_data* data, list_result* result);

//Функция добавления первого результата в другой присок
void add_head_result(list_data* data, list_result** head){
	// Выделяем память для временного елемента списка с результатами
	list_result* tmp = (list_result*)malloc(sizeof(list_result));
	if(data->calculator == 'v')
		vector_calculator(data, tmp);
	else
		number_calculator(data, tmp);
	tmp->next = (*head);
	(*head) = tmp;
}

// Функция добавления элемента в конец списка
void add_data(list_data* head, FILE* read_file){
	// Получаем последний элемент списка с данными
	list_data* last = get_last_data(head);
	// Создаём временный элемент
	list_data* tmp = (list_data*)malloc(sizeof(list_data));
	// Читаем первые два символа из файла и записываем их в элемент списока
	fscanf(read_file, " %c %c", &tmp->operation, &tmp->calculator);
	// Если "v", то читаем размерность векторов
	if(tmp->calculator == 'v'){
		fscanf(read_file, "%d", &tmp->size);
	} else {  // Иначе размерность векторов = 1 => обычные числа
		tmp->size = 1;
	}
	// Выделяем память для двух переменных, хранящие наши числа
	tmp->value_1 = malloc(tmp->size * sizeof(float));
	tmp->value_2 = malloc(tmp->size * sizeof(float));
	// Считываем сначала все числа в первую переменную...
	for(int i = 0; i < tmp->size; i++){
		fscanf(read_file, "%f", &tmp->value_1[i]);
	}
	// ...затем во вторую
	for(int i = 0; i < tmp->size; i++){
		fscanf(read_file, "%f", &tmp->value_2[i]);
	}
	tmp->next = NULL;
	last->next = tmp;
}

// Функция добавления результата в другой список
void add_result(list_data* data, list_result* head){
	// Получаем последний элемент списка с результатами
	list_result* last = get_last_result(head);
	// Создаём временный элемент
	list_result* tmp = (list_result*)malloc(sizeof(list_result));
	if(data->calculator == 'v')
		vector_calculator(data, tmp);
	else
		number_calculator(data, tmp);
	tmp->next = NULL;
	last->next = tmp;
}

void number_calculator (list_data* data, list_result* result) {
	result->result = malloc(sizeof(float));
	switch(data->operation){
	case '+':
		result->result[0] = data->value_1[0] + data->value_2[0];
		break;
	case '-':
		result->result[0] = data->value_1[0] - data->value_2[0];
		break;
	case '*':
		result->result[0] = data->value_1[0] * data->value_2[0];
		break;
	case '/':
		result->result[0] = data->value_1[0] / data->value_2[0];
		break;
	case '^':
		result->result[0] = data->value_1[0];
		if (data->value_2[0] != 0) {
			for (int i = 1;i < data->value_2[0]; i++) {
				result->result[0] = result->result[0] * data->value_1[0];
			}
		} else
		result->result[0] = 1;
		break;
	case '!':
		result->result[0] = 1;
		for (int i = 1; i <= data->value_1[0]; i++) {
			result->result[0] = result->result[0] * i;
		}
		break;
	}
}

void vector_calculator (list_data* data, list_result* result) {
	result->result = malloc(data->size * sizeof(float));
	switch(data->operation){
	case '+':
		for(int i = 0; i < data->size; i++){
			result->result[i] = data->value_1[i] + data->value_2[i];
		}
		break;
	case '-':
		for(int i = 0; i < data->size; i++){
			result->result[i] = data->value_1[i] - data->value_2[i];
		}
		break;
	case '*':
		for(int i = 0; i < data->size; i++){
			result->result[i] = data->value_1[i] * data->value_2[i];
		}
		break;
	}
}

// Функция записи результата в файл
void write_in_file(list_data* data, list_result* result, FILE* write_file){
	if(data->calculator == 'v' && data->operation != '*'){
		fprintf(write_file, "(");
		for (int i = 0; i < data->size; i++) {
			fprintf(write_file, "%.0f", data->value_1[i]);
			if (i != data->size - 1) fprintf(write_file, " ");
		}
		fprintf(write_file, ") %c (", data->operation);
		for (int i = 0; i < data->size; i++) {
			fprintf(write_file, "%.0f", data->value_2[i]);
			if (i != data->size - 1) fprintf(write_file, " ");
		}
		fprintf(write_file, ") = (");
		for (int i = 0; i < data->size; i++) {
			fprintf(write_file, "%.0f", result->result[i]);
			if (i != data->size - 1) fprintf(write_file, " ");
		}
		fprintf(write_file, ")");
	} else {
		if (data->calculator == 'v') {
			fprintf(write_file, "(a, b) = ");
		} else if (data->operation != '!') {
			fprintf(write_file, "%.0f %c %.0f = ", data->value_1[0], data->operation, data->value_2[0]);
		} else {
			fprintf(write_file, "%.0f! = ", data->value_1[0]);
		}
		fprintf(write_file, "%.0f", result->result[0]);
	}
	fprintf(write_file, "\n");
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	FILE *data_file, *result_file;
	// Открываем файлы на чтение
	data_file = fopen("data_file.txt", "r");

	// Создаём начало списка с данными из файла
	list_data* head_data = NULL;

	// Записываем данные первого калькулятора в начало списка
	add_head_data(&head_data, data_file);

	// Читаем все остальные калькуляторы, если они есть в файле
	do{
		add_data(head_data, data_file);
	}while(!feof(data_file));

	// Закрываем файл
	fclose(data_file);

	// Создаём current_data, чтобы не потерять начало списка
	list_data* current_data = head_data;
	list_result* head_result = NULL;

	// Записываем первый результат в другой список
	add_head_result(current_data, &head_result);

	current_data = current_data->next;
	// Записываем оставшиеся результаты в другой список, если они имеются
	while(current_data){
		add_result(current_data, head_result);
		current_data = current_data->next;
	}

	list_result* current_result = head_result;
	current_data = head_data;

	// Открываем файл на запись
	result_file = fopen("result_file.txt", "w");

	// Записываем всё в файл
	while(current_data){
		write_in_file(current_data , current_result, result_file);
		current_data = current_data->next;
		current_result = current_result->next;
	}

	// Закрываем файл
	fclose(result_file);

	return EXIT_SUCCESS;
}
