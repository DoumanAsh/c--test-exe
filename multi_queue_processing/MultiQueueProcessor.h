#pragma once
#include <map>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

template<typename Key, typename Value>
struct IConsumer {
    virtual void Consume(Key id, const Value &value) {
        std::cout << "Consume id=" << id << " value=" << value << "\n";
    }
};

const size_t MAX_CAPACITY = 1000;

template<typename Key, typename Value>
class MultiQueueProcessor {
public:
    MultiQueueProcessor() :
        worker(std::bind(&MultiQueueProcessor::Process, this)) {}

    ~MultiQueueProcessor() {
        StopProcessing();
        cond.notify_all();
        worker.join();
    }

    void StopProcessing() {
        running = false;
    }

    void Subscribe(Key id, IConsumer<Key, Value> * consumer) {
        Lock lock{ mtx };

        auto iter = consumers.find(id);
        if (iter == consumers.end()) {
            consumers.emplace(id, consumer);
            cond.notify_all();
        }
    }

    void Unsubscribe(Key id) {
        Lock lock{ mtx };

        auto iter = consumers.find(id);
        if (iter != consumers.end()) consumers.erase(id);
    }

    void Enqueue(Key id, Value& value)
    {
        {
            Lock lock{ mtx };
            auto iter = this->find_queue_or_create(id);
            if (iter->second.size() < MAX_CAPACITY) iter->second.push_back(value);
        }
        cond.notify_all();
    }

    void Enqueue(Key id, Value&& value)
    {
        {
            Lock lock{ mtx };
            auto iter = this->find_queue_or_create(id);
            if (iter->second.size() < MAX_CAPACITY) iter->second.push_back(std::move(value));
        }
        cond.notify_all();
    }

    Value Dequeue(Key id)
    {
        Lock lock{ mtx };
        auto iter = queues.find(id);
        if (iter != queues.end()) {
            auto front = std::move(iter->second.front());

            iter->second.pop_front();
            if (iter->second.size() == 0) queues.erase(iter);

            return front;
        }
        return Value{};
    }

private:
    typedef std::unique_lock<std::mutex> Lock;
    typedef std::deque<Value> Values;
    ///Finds queue by id.
    ///If no such queue, then creates it.
    ///
    ///@note Doesn't perform lock
    auto find_queue_or_create(Key id) {
        //Insertion happens only if element is not present.
        //Otherwise it returns existing element.
        return queues.emplace(id, Values()).first;
    }

protected:
    void Process() {
        while (running) {
            Lock lock(mtx);
            while (queues.empty() || consumers.empty()) {
                //Skip if either consumers or queues are missing.
                cond.wait(lock);
                if (!running) break;
            }

            for (auto const &consumer : consumers) {
                auto queue_elem = queues.find(consumer.first);
                if (queue_elem != queues.end()) {
                    for (auto const &value : queue_elem->second) {
                        consumer.second->Consume(queue_elem->first, value);
                    }

                    queues.erase(queue_elem);
                }
            }
        }
    }

    std::map<Key, IConsumer<Key, Value> *> consumers;
    std::map<Key, Values> queues;

    std::mutex mtx;
    std::condition_variable cond;
    bool running = true;
    std::thread worker;
};
