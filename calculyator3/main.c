#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>


int main(void) {
    char exit;
    do {
        puts("\n Chtobi zapustit operaciyu nazhmite Enter!");
        scanf("%c",&exit);
        char operacia, file_data;
        FILE *in_file; // дескриптор входного файла (откуда возьмем данные, с которыми будем работать)
        FILE *out_file; // дескриптор выходного файла (куда запишем результат)

        in_file = fopen("infile.txt","r"); // открываем файл для чтения
        out_file = fopen("outfile.txt", "w"); // открываем файл для записи
        fscanf(in_file, "%c", &operacia);
        fscanf(in_file, " %c", &file_data);

        switch (file_data) {





            case 'v': {          // начинаем работу с векторами
                float *vector_1; // указатель на первый вектор. В этой переменной хранится адрес начала массива
                float *vector_2; // указатель на второй вектор. В этой переменной хранится адрес начала массива
                float *vector_result; // указатель на вектор, содержащий результат. В этой переменной хранится адрес начала массива
                int size = 0; // размер всех векторов. Считывается из файла

                // выделим память под векторы
                vector_1 = calloc(size,sizeof(int)); // функция calloc выделяет память для вектора. size - количество элементов, sizeof(int) - размер одного элемента
                vector_2 = calloc(size,sizeof(int)); // функция calloc выделяет память для вектора. size - количество элементов, sizeof(int) - размер одного элемента
                vector_result = calloc(size,sizeof(float)); // функция calloc выделяет память для вектора. size - количество элементов, sizeof(int) - размер одного элемента
                fscanf(in_file, " %d", &size);


                switch (operacia) {
                    case '+': {   // сложение векторов
                        fprintf(out_file,"(");    // выводим первую скобку
                        for (int i = 0; i < size; i++) {
                            fscanf(in_file, "%f", &vector_1[i]);
                            fprintf(out_file," %.2f ", vector_1[i]);
                        }
                        fprintf(out_file,")");
                        fprintf(out_file," + ");

                        fprintf(out_file,"(");    // выводим вторую скобку
                        for (int i = 0; i < size; i++) {
                            fscanf(in_file, "%f", &vector_2[i]);
                            fprintf(out_file," %.2f ", vector_2[i]);
                        }
                        fprintf(out_file,")");
                        fprintf(out_file," = ");

                        fprintf(out_file,"(");    // выводим результат
                        for (int i = 0; i < size; i++) {
                            vector_result[i] = vector_1[i] + vector_2[i];
                            fprintf(out_file,"%.2f", vector_result[i]);
                            if (i != size - 1) fprintf(out_file," ");
                        }
                        fprintf(out_file,")");
                        break;
                    }
                    case '-': {         // вычитание векторов
                        fprintf(out_file,"(");    // выводим первую скобку
                        for (int i = 0; i < size; i++) {
                            fscanf(in_file, "%f", &vector_1[i]);
                            fprintf(out_file," %.2f ", vector_1[i]);
                        }
                        fprintf(out_file,")");
                        fprintf(out_file," - ");

                        fprintf(out_file,"(");    // выводим вторую скобку
                        for (int i = 0; i < size; i++) {
                            fscanf(in_file, "%f", &vector_2[i]);
                            fprintf(out_file," %.2f ", vector_2[i]);
                        }
                        fprintf(out_file,")");
                        fprintf(out_file," = ");

                        fprintf(out_file,"(");    // выводим результат
                        for (int i = 0; i < size; i++) {
                            vector_result[i] = vector_1[i] - vector_2[i];
                            fprintf(out_file,"%.2f", vector_result[i]);
                            if (i != size - 1) fprintf(out_file," ");
                        }
                        fprintf(out_file,")");
                        break;
                    }




                    case '*': {     // умножение векторов
                        fprintf(out_file,"(");    // выводим первую скобку
                        for (int i = 0; i < size; i++) {
                            fscanf(in_file, "%f", &vector_1[i]);
                            fprintf(out_file," %.2f ", vector_1[i]);
                        }
                        fprintf(out_file,")");
                        fprintf(out_file," * ");

                        fprintf(out_file,"(");    // выводим вторую скобку
                        for (int i = 0; i < size; i++) {
                            fscanf(in_file, "%f", &vector_2[i]);
                            fprintf(out_file," %.2f ", vector_2[i]);
                        }
                        fprintf(out_file,")");
                        fprintf(out_file," = ");

                        fprintf(out_file,"(");    // выводим результат
                        for (int i = 0; i < size; i++) {
                            vector_result[i] = vector_1[i] * vector_2[i];
                            fprintf(out_file,"%.2f", vector_result[i]);
                            if (i != size - 1) fprintf(out_file," ");
                        }
                        fprintf(out_file,")");
                        break;
                    }


                    default:
                        puts("Oshibka. Nepravilnyj simvol operacii. Ispravte fajl i poprobujte zanovo.");
                        break;
                }

                free(vector_1); // освобождаем память
                free(vector_2);
                free(vector_result);
                break;
            }


            case 's': {
                int num1, num2, i;
                float result;

                fscanf(in_file, " %d", &num1);
                fscanf(in_file, " %d", &num2);

                switch (operacia) {
                    case '+':
                        result = num1 + num2;
                        fprintf(out_file, "%d + %d = %.2f", num1, num2, result);
                        break;

                    case '-':
                        result = num1 - num2;
                        fprintf(out_file, "%d - %d = %.2f", num1, num2, result);
                        break;

                    case '*':
                        result = num1 * num2;
                        fprintf(out_file, "%d * %d = %.2f", num1, num2, result);
                        break;

                    case '/':
                        result = num1 / num2;
                        fprintf(out_file, "%d / %d = %.2f", num1, num2, result);
                        break;

                    case '^':
                        result = 1; // нужно задать значение result, чтобы не испортить первый шаг цикла

                        for (i = 0; i < num2; i++) {
                            result = result * num1;
                        }
                        fprintf(out_file, "результат: %d ^ %d = %.2f \n", num1, num2,
                                result);
                        break;

                    case '!':
                        if (num1 == 0) // если num == 0, то факториал считать не нужно, ответ 1
                        {
                            result = 1;
                        } else // если num != 0
                        {
                            result = 1;
                            for (i = 1; i <= num1; i++) {
                                result = result * i;
                            }
                        }
                        fprintf(out_file, "результат: %d! = %.2f \n", num1, result);
                        break;

                    default:
                        puts("Oshibka. Nepravilnyj simvol operacii. Ispravte fajl i poprobujte zanovo.");
                        break;
                }
                break;
            }

            default:
                puts("Oshibka. Nepravilnyj tip dannyh .");
                break;
        }
        fclose(in_file);
        fclose(out_file);

        puts("Operaciya zavershena. Prover'te fajl outfile.txt v papke.\n Nazhmite 'e' dlya zaversheniya");

    }while(exit != 'e');
}