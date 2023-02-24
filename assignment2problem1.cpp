#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#define N 10

// Keeps track of which guests in the labyrinth have eaten the cupcake at least once
std::array<bool, N> guestThatEntered;
//for lock and unlock
std::mutex mutex;
//variable to let us know if we have cupcake or not
bool Cupcake = true;
//counter to run until size of guests
int counter = 0;

//Checks whether cupcake is available or not
void CupOrNoCup()
{
    while (counter < N)
    {
        mutex.lock();

        // In this case, the cupcake will only be unavailable if someone
        // has eaten it, so we need to update the count and replace the cupcake
        if (!Cupcake)
        {
            std::cout << "cupcake requested\n";
            counter++;
            Cupcake = true;
        }

        // Need to make sure this thread eats the cupcake once
        if (Cupcake && !guestThatEntered[0])
        {
            counter++;
            Cupcake = true;
            guestThatEntered[0] = true;
        }

        mutex.unlock();
    }
}

void enterLabyrinth(unsigned int threadIndex)
{
    while (counter < N)
    {
        mutex.lock();
        //if cupcake and guest that entered didnt eat cupcake yet
        if (Cupcake && !guestThatEntered[threadIndex])
        {
            //if they havent eaten cupcake they eat and cupcake not available
            Cupcake = false;
            //set it so that we know that guest entered
            guestThatEntered[threadIndex] = true;
            std::cout << "Guest #" << threadIndex << " ate the cupcake" << std::endl;
        }

        mutex.unlock();
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::array<std::thread, N> threads{};

    // Designate the first thread as the counter. This thread will keep track
    // of whether the cupcake has been eaten and update the count accordingly
    threads[0] = std::thread(CupOrNoCup);

    //make parallel threads
    //keep in mind rng not needed since the lock will stop other threads from going then once unlock
    //all threads will race to see which one goes first
    for (size_t i = 1; i < threads.size(); i++)
    {
        threads[i] = std::thread(enterLabyrinth, i);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start);
    std::cout << "Checking if all guests entered\n";
    for (size_t i = 0; i <= threads.size(); i++)
    {
        if (guestThatEntered[i])
        {
            std::cout << "Guest " << i + 1 << " entered\n";
        }
    }

    std::cout << "All have entered the labyrinth." << std::endl;
    std::cout << "Finished in " << duration.count() << "ms" << std::endl;
}
