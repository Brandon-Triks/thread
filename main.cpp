//вариант2

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <future>

void mult(const std::vector<double>& arr1,const std::vector<double>& arr2, const std::string& ThreadName) {
    for (size_t i = 0; i < arr1.size(); i++) {
        std::cout<<ThreadName<<'\t';
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout<<i<<'\t'<<arr1[i] << "*" << arr2[i] << "=" << arr1[i]*arr2[i]<<'\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void add(const std::vector<double>& arr1,const std::vector<double>& arr2,const std::string& ThreadName) {
    for (size_t i = 0; i < arr1.size(); i++) {
        std::cout<<ThreadName<<'\t';
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout<<i<<'\t'<<arr1[i] << "+" << arr2[i] << "=" << arr1[i]+arr2[i]<<'\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void print(size_t n3,const std::string& ThreadName) {
    for (size_t i = 0; i < n3; i++) {
        std::cout<<ThreadName<<'\t';
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout<<i<<'\t'<<std::rand()<<'\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

int main() {
    std::srand(std::time(NULL));
    size_t n1 = 20, n2 = 20, n3 = 25;
    std::vector<double> arr1(n1);
    std::vector<double> arr2(n2);
    for (size_t i = 0; i < n1; i++) {
        arr1[i] = std::rand();
    }
    for (size_t i = 0; i < n2; i++) {
        arr2[i] = std::rand();
    }
    //                  реализация thread
    // std::thread thread1(mult,arr1,arr2,"thread1");
    // std::thread thread2(add,arr1,arr2,"thread2");
    // std::thread thread3(print,n3,"thread3");
    //
    // thread1.join();
    // thread2.join();
    // thread3.join();
    //
    // std::cout << "Главный поток\t";
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // std::cout << "Работа окончена.";
    //                  реализация async
    std::future<void> f1 = std::async(std::launch::async, mult, std::ref(arr1), std::ref(arr2), "thread1");
    std::future<void> f2 = std::async(std::launch::async, add, std::ref(arr1), std::ref(arr2), "thread2");
    std::future<void> f3 = std::async(std::launch::async, print, n3, "thread3");
    f1.get();
    f2.get();
    f3.get();
    std::cout << "Главный поток\t";
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Работа окончена.";
}