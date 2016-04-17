// unboost_sample.cpp --- Unboost sample
// This file is public domain software (PDS).
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_ALL
#include "unboost.hpp"

#include <iostream>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

#ifdef UNBOOST_USE_STATIC_ASSERT
    static_assert(1, "OK");
    //static_assert(0, "NG");
#endif

//////////////////////////////////////////////////////////////////////////////

void thread_proc(void) {
    std::cout << "in thread_proc" << std::endl;
}

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    #ifdef UNBOOST_USE_SMART_PTR
        std::cout << "smart ptr" << std::endl;
        unboost::shared_ptr<int> spi = unboost::make_shared<int>(2);
        std::cout << *spi << std::endl;
    #endif

    #ifdef UNBOOST_USE_THREAD
        std::cout << "thread" << std::endl;
        unboost::thread t(thread_proc);
        t.join();
    #endif

    #ifdef UNBOOST_USE_ARRAY
        std::cout << "array" << std::endl;
        unboost::array<int,2> a = {2, 3};
        std::cout << a[0] << std::endl;
        std::cout << a[1] << std::endl;
    #endif

    #ifdef UNBOOST_USE_REGEX
        std::cout << "regex" << std::endl;
        std::vector<std::string> fnames;
        fnames.push_back("foo.txt");
        fnames.push_back("bar.txt");
        fnames.push_back("baz.dat");
        fnames.push_back("zoidberg");
        using unboost::regex;
        regex txt_regex("[a-z]+\\.txt");
     
        for (size_t i = 0; i < fnames.size(); ++i) {
            using namespace unboost;
            std::string& fname = fnames[i];
            std::cout << fname << ": " << regex_match(fname, txt_regex) << '\n';
        }
    #endif

    #ifdef UNBOOST_USE_CONVERSION
        std::cout << "conversion" << std::endl;
        std::cout << unboost::to_string(unboost::stoi("2016")) << std::endl;
        std::cout << unboost::lexical_cast<int>("123") << std::endl;
        std::cout << unboost::lexical_cast<std::string>(123) << std::endl;
        std::cout << unboost::stod("123") << std::endl;
    #endif

    #ifdef UNBOOST_USE_COMPLEX_FUNCTIONS
        std::cout << "complex functions" << std::endl;
        std::cout << unboost::math::asin(std::complex<double>(2, 3)).real() << std::endl;
    #endif

    #ifdef UNBOOST_USE_RANDOM
        std::cout << "random" << std::endl;
        {
            using namespace unboost::random;
            mt19937 engine;
            uniform_int_distribution<int> distribution(1, 6);
            for (int i = 0; i < 5; ++i) {
                std::cout << distribution(engine) << std::endl;
            }
        }
    #endif

    #ifdef UNBOOST_USE_CHRONO
        std::cout << "chrono" << std::endl;
        {
            using namespace unboost::chrono;
            seconds sec(1);
            std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
            std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
            std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
            std::cout << duration_cast<hours>(sec).count() << " hours" << std::endl;
        }
    #endif

    #ifdef UNBOOST_USE_UNORDERED_SET
        std::cout << "unorderd set" << std::endl;
        unboost::unordered_set<int> us;
        us.insert(1);
        us.insert(2);
        {
            unboost::unordered_set<int>::iterator it, end = us.end();
            for (it = us.begin(); it != end; ++it) {
                std::cout << *it << std::endl;
            }
        }
    #endif

    #ifdef UNBOOST_USE_UNORDERED_MAP
        std::cout << "unorderd map" << std::endl;
        unboost::unordered_map<int, int> um;
        um.insert(std::make_pair(2, 3));
        um.insert(std::make_pair(4, 5));
        {
            unboost::unordered_map<int, int>::iterator it, end = um.end();
            for (it = um.begin(); it != end; ++it) {
                std::cout << it->first << "," << it->second << std::endl;
            }
        }
    #endif

    #ifdef UNBOOST_USE_FOREACH
        std::cout << "foreach" << std::endl;
        {
            std::vector<int> v;
            v.push_back(2);
            v.push_back(3);
            v.push_back(4);
            UNBOOST_FOREACH(int& i, v) {
                i -= 1;
            }
            UNBOOST_FOREACH(int i, v) {
                std::cout << i << std::endl;
            }
        }
    #endif

    return 0;
} // main

//////////////////////////////////////////////////////////////////////////////
