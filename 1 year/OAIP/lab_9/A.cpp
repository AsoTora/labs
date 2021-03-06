//
// Created by aso on 1/27/19.
//

#include "A.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sys/stat.h>


/*
 Создать бинарный файл, записать в него десять действительных чи-
сел и закрыть файл. Открыть файл для чтения, прочитать записанные дан-
ные и выполнить задание. Результат вывести на экран и в текстовый файл.
Закрыть все открытые файлы.

*/


using namespace std;
long file_length(const char *f);

void A_1() {
    /* Найти сумму четных и количество отрицательных чисел. */
    int count=0, sum=0;
    string path = "/home/aso/CLionProjects/lab_9/info.txt";
    string path1 = "/home/aso/CLionProjects/lab_9/res.txt";

    ofstream fout; // write
    fout.open("/home/aso/CLionProjects/lab_9/info.txt", ifstream::out);
    if (!fout.is_open()){
        cout << "Error!" << endl;
    }else{
        for (int i = 0; i < 10; i++) {
            cout << "enter " << i << " number: ";
            int a;
            cin >> a;
            fout << a << '\n';
        }
    }
    fout.close();


    ifstream file;
    ofstream results;

    file.open(path);
    results.open(path1);

    if(!file.is_open()){
        cout << "Error!" << endl;
    }else{
        cout << "Opened" << endl;

        while(!file.eof()){
            int i=0;
            file >> i;

            if (i < 0) count++;
            if (i%2 == 0) sum += i;
        }
    }

    results << "Summa: " << sum << '\n';
    results << "Ammount: " << count;

    cout << "Summa: " << sum << endl;
    cout << "Ammount: " << count << endl;

    file.close();
    results.close();
}

void A_1_1(){
    /* Найти сумму четных и количество отрицательных чисел. */

    const char *path = "/home/aso/CLionProjects/lab_9/info1.txt";
    const char *path1 = "/home/aso/CLionProjects/lab_9/res1.txt";
    FILE *f;
    int count=0, sum=0;

    f = fopen(path, "w");
    if (f==nullptr){
        cout << "Error" << endl;
    }else{
        for (int i=0; i<10; i++){
            int a;
            cout << "Enter " << i << " number: ";
            cin >> a;
            fwrite(&a, sizeof(a), 1, f); // запись числа в файл
        }
    }
    fclose(f);

    f = fopen(path, "r");
    FILE *f2 = fopen(path1, "w");
    if (f == nullptr){
        cout << "Error" << endl;
    }else{
        long int size = file_length(path);
        int l = size/sizeof(int);
        int *arr = new int [l];

        fread(arr, sizeof(int), l, f); // чтение числа из файла
        for (int i=0; i<l; i++){
            if (arr[i] < 0) count++;
            if (arr[i]%2 == 0) sum += arr[i];
        }
        cout << "Summa: " << sum << endl;
        cout << "Ammount: " << count << endl;

        if (f2 == nullptr){
            cout << "Error" << endl;
        }else{  // запись результата в файл res1.txt
            fprintf(f2,"Summa: %d\n",sum);
            fprintf(f2,"Ammount: %d\n",count);
        }
    }
    fclose(f);
    fclose(f2);
}


long file_length(const char *f){
    /* https://www.tutorialspoint.com/unix_system_calls/stat.htm */
    struct stat st{}; // объявление структуры вида stat these functions return information about a file.
    stat(f, &st);  // запись в нее содержимого файла
    return st.st_size; // вернет размер содержимого в байтах
}
