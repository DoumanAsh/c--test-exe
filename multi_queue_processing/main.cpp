#include <iostream>
#include <string>

#include <thread>
#include <chrono>

#include "MultiQueueProcessor.h"

const int MAX_ITERATION = 1000;

static const char sym_table[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

std::string get_random_string() {
    char buffer[52] = { 0 };

    for (size_t idx = 0; idx < sizeof(buffer) - 1; idx++) {
        buffer[idx] = sym_table[rand() % (sizeof(sym_table) - 1)];
    }
    return std::string(buffer);
}

void producer1(MultiQueueProcessor<int, std::string> *queue)
{
    for (int i = 0; i != MAX_ITERATION; ++i) {
        queue->Enqueue(1, get_random_string());
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
}

void producer2(MultiQueueProcessor<int, std::string> *queue) {
    for (int i = 0; i != MAX_ITERATION; ++i) {
        queue->Enqueue(2, get_random_string());
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void producer3(MultiQueueProcessor<int, std::string> *queue) {
    int keys[] = { 1, 2, 3 };
    for (int i = 0; i != MAX_ITERATION; ++i) {
        queue->Enqueue(keys[rand() % (sizeof(keys) - 1)], get_random_string());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main(int, char**) {
    std::cout << "Hellow world!" << std::endl;

    IConsumer<int, std::string> consm1;
    IConsumer<int, std::string> consm2;
    IConsumer<int, std::string> consm3;

    MultiQueueProcessor<int, std::string> queue;

    queue.Enqueue(1, std::string("first"));
    queue.Enqueue(2, std::string("seocnd"));
    queue.Enqueue(2, std::string("seocnd"));
    queue.Enqueue(3, std::string("third"));
    queue.Subscribe(1, &consm1);

    std::thread first(producer1, &queue);
    std::thread second(producer2, &queue);
    std::thread third(producer3, &queue);

    queue.Subscribe(2, &consm2);
    queue.Subscribe(3, &consm3);

    first.join();
    second.join();
    third.join();
    return 0;
}
