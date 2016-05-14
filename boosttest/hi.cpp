#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/coroutine/all.hpp>
#include <boost/filesystem.hpp>
#include <memory>
#include <boost/thread/thread.hpp>
#include <vector>

using namespace boost::filesystem;

typedef boost::shared_ptr<int> int_ptr;


void fib(boost::coroutines::asymmetric_coroutine<int>::push_type& yield) {
    int first = 1;
    int second = 1;
    yield(first);    // Returns for the first time.
    // Entrance #2
    yield(second);   // Returns for the second time.
    // Entrance #3
    for(int i = 0; i < 8; ++i){
        int third = first + second;
        first = second;
        second = third;
        yield(third);
    }
}

void coro_test()
{
    boost::coroutines::asymmetric_coroutine<int>::pull_type source(fib);
    int answer1 = source.get();  // Retrieves the first result of yield.
    std::cout << answer1;
    source();                    // Execution goes to "Entrance #2" above.
    int answer2 = source.get();  // Retrieves the second result of yield.
    std::cout << answer2;
    source();                    // Execution goes to "Entrance #3..."
    int answer3 = source.get();  // Gets the third answer...
    std::cout << answer3;
    source();                    // Runs one more time.

    // Continously gets the last result of yield and assigns it to i in the
    // loop, then runs the coroutine again.
    for (auto i : source) {
        std::cout << i << " ";
    }
}

int main() {
    int_ptr p(new int{10});
    std::cout << "OH hai\n";

    std::vector<std::unique_ptr<boost::thread>> threads;
    for (int i = 0; i < 10; ++ i)
    {
        threads.push_back(std::make_unique<boost::thread>([] {
            std::cout << "I am on this thread:"
                      << boost::this_thread::get_id() << "!\n";
        }));
    }

    for (int i = 0; i < 10; ++ i)
    {
        threads[i]->join();
    }

    coro_test();
}
