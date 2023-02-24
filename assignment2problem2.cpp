#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_set> 
#include <chrono>
#include <array>
#include <atomic>
//10 guests
#define N 10
// Keeps track of what guests have already seen the vase
std::unordered_set<std::thread::id> sawVase{};
std::mutex mutex;
// Available or busy variable, 0 will represent available and 1 will represent busy.
std::atomic<long long int> AorB = 0;

void enterRoom(int i) {
    std::thread::id Id = std::this_thread::get_id();
    //will run based on how many guests there are
    while (sawVase.size() < N) {
        //lock
        mutex.lock();
        //if room is available and rng number isn't already inserted in sawVase
        if (AorB == 0 && sawVase.find(Id) == sawVase.end()) {
            //room busy
            AorB=1;
            //starts at guest 0 so added +1 to make it go from 1-10
            std::cout << "Guest #" << i+1 << " is admiring the vase" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            //Guest is done admiring so room is available
            AorB=0;
            //Insert rng from 1-10 into sawVase so guest cant come again.
            sawVase.insert(Id);
        }
        //unlock
        mutex.unlock();
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();//starting tiMer
    //making an array of the threads
    std::array<std::thread, N> threads{};  

    //runs threads
    for (size_t i = 0; i < threads.size(); i++) {
        //will make thread/person go to admire vase
        threads[i] = std::thread(enterRoom, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }
    //end clock
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);

    std::cout << "All guests have viewed the vase." << std::endl;
    std::cout << "Duration: " << duration.count() << "ms" << std::endl;
}
