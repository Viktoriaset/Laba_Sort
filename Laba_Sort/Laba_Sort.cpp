#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>
#include <fstream>
#include <thread>


void BubbleSortClassic(std::vector<long long>& mas);

void PrintMas(std::vector<double> mas);
double CountTime(void (*sortFunction)(std::vector<long long>& mas), std::vector<long long> mas);
std::vector<std::vector<double>> Expirement(void (*sortFunction)(std::vector<long long>& mas));
std::vector<long long> CreateMas(long long n);

void BubbleSortClassic(std::vector<long long>& mas) {
    for (long long i = mas.size() - 1; i >= 0; i--) {
        for (long long j = 0; j < i; j++) {
            if (mas[j] > mas[j + 1]) {
                std::swap(mas[j], mas[j + 1]);
            }
        }
    }
}


void PrintMas(std::vector<double> mas) {
    std::ofstream out("output.txt", std::ios_base::app);
    for (int i = 0; i < mas.size(); i++) {
        out << mas[i] << ' ';
    }
    out << std::endl;
    out << "________________________________________" << std::endl;
}

double CountTime(void (*sortFunction)(std::vector<long long> &mas), std::vector<long long> mas) {
    // return time for need function for sort massive mas(second)
    clock_t startTimer = std::clock();
    sortFunction(mas);
    clock_t finalTimer = std::clock();
    return ((double)(finalTimer - startTimer)) / CLOCKS_PER_SEC;

}

void UseSort(void (*sortFunction)(std::vector<long long>& mas), std::vector<std::vector<double>> &timeSorting, int i) {

    std::vector<long long> mas = CreateMas(((long long)std::pow(10, i)));
    timeSorting[i - 1].push_back(CountTime(sortFunction, mas));

}

std::vector<std::vector<double>> Expirement(void (*sortFunction)(std::vector<long long>& mas)) {
    std::ofstream out("output.txt", std::ios_base::app);
    std::vector<std::vector<double>> timeSorting;
    for (int i = 1; i < 10; i++) {
        timeSorting.push_back(std::vector<double>());

        out << "================================" << std::endl;
        out << "Start expirements, where" << " N = 10^" << i << std::endl;

        std::vector<std::thread> Potoki;

        for (int j = 1; j < 10; j++) {
            Potoki.push_back(std::thread(UseSort, std::ref(sortFunction), std::ref(timeSorting), i));
        }
        for (int j = 0; j < Potoki.size(); j++) {
            Potoki[j].join();
        }

        out << "Finish expirements, where" << " N = 10^" << i << std::endl;
        out << "Results expirements:";
        PrintMas(timeSorting[i - 1]);
        out << std::endl;
        out << "================================" << std::endl;
    }
    return timeSorting;
}

std::vector<long long> CreateMas(long long n) {
    std::vector<long long> mas;
    for (int i = 0; i < n; i++) {
        mas.push_back(rand() * rand());
    }

    return mas;
}

int main()
{
    std::vector<long long> mas;
    for (int i = 0; i < 200; i++) {
        mas.push_back(rand());
    }

    std::vector<std::vector<double>> BSCTime = Expirement(BubbleSortClassic);
    for (int i = 0; i < BSCTime.size(); i++) {
        PrintMas(BSCTime[i]);
    }

    return 0;
}
