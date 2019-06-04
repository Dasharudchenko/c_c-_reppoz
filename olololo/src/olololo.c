/*
 ============================================================================
 Name        : kalkulyator2.c
 Author      : Daria Rudchenko
 Version     :
 Copyright   : free
 Description : Vectornii kalkulyator
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main() {
   printf("S chem proizvodit rabotu: 1) 4isla 2) vectori\n") ;
   int logic;
   scanf("%d", &logic);
   switch (logic){

       case 1: {
           float a, b, c = 1, otvet;                         //объявляем переменные для хранения введённых чисел
               int uslovie;


               int e = 1;
               while (e == 1) {                                      //объявляем цикл работы для возможности рестарта
                   printf("vvedite 2 chisla\n");
                   scanf("%f%f", &a, &b);
                   printf("slojenie 1\n");
                   printf("raznost 2\n");
                   printf("umnojenie 3\n");
                   printf("delenie 4\n");
                   printf("vozvedenie v stepen(a^b) 5\n");
                   printf("faktorial ot 1 chisla 6\n");
                   printf("vvedite nomer operacii\n");
                   scanf("%d", &uslovie);
                   if (uslovie==1) {
                       printf("otvet %f\n", a + b);
                   }
                   if (uslovie==2) {
                       printf("otvet %f\n", a - b);
                   }
                   if (uslovie==3) {
                       printf("otvet %f\n", a * b);
                   }
                   if (uslovie==4) {
                       printf("otvet %f\n", a / b);
                   }
                   if (uslovie==5) {
                       otvet = pow(a, b);                                                   //функция возведения числа в степень
                       printf("otvet %f\n", otvet);
                   }
                   if (uslovie==6) {
                       while (a != 0)
                       {
                           c = c * a;
                           a = a - 1;
                           if (a==0)
                           {
                               printf("otvet %f\n", c);
                           }
                       }
                   }
                   printf("dlya restarta vvedite 1, dlya vihoda luboe drugoe chislo");
                   scanf("%d", &e);
       }
   }

   case 2: {

       float *vector1, *vector2;           //объявляем переменные для хранения векторов
       int size, f;

       printf("vvedite razmernost vectora: ");
       scanf("%d", &size);

       vector1 = calloc(size,sizeof(float));  //выделяем память для заранее неизвестной размерности
       for (int i = 0; i < size; i++) {
           printf("Enter cords first vector (a): ");
           scanf("%f", &vector1[i]);
       }

       vector2 = calloc(size,sizeof(float));

       for (int i = 0; i < size; i++) {
           printf("Enter cords second vector (b): ");
           scanf("%f", &vector2[i]);
       }

       int k;
       puts("\n select operation:    1) \"+\" - summ\n    2) \"-\" - razn\n    3) \"*\" - skalyar *");
       printf("select command: ");
       scanf("%d", &k);

       f = 0;
       while(f == 0) {
           if(k > 0 && k < 4){
               f = 1;
           }
           else {
               printf("Not have this cammand! Select command from list: ");
               scanf("%d", &k);
           }
       }

       float result = 0;
       switch(k) {
           case 1:
               printf("\n Result: (");
               for (int i = 0; i < size; i++) {              //программа циклично проводит операции с каждым элементом вектора
                   printf("%.2f", vector1[i] + vector2[i]);
                   if (i != size-1) printf(" ");
               }
               printf(")\n\n");
               break;
           case 2:
               printf("\n Result: (");
               for (int i = 0; i < size; i++) {
                   printf("%.2f", vector1[i] - vector2[i]);
                   if (i != size-1) printf(" ");
               }
               printf(")\n\n");
               break;
           case 3:
               for (int i = 0; i < size; i++) {
                   result += vector1[i] * vector2[i];
               }
               printf("\n Result: %.2f\n\n", result);
               break;
       }
       free(vector1);  // освобождаем память
       free(vector2);

        }
    }
}

