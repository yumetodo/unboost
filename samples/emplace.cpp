// emplace.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_EMPLACE
#include <unboost.hpp>
#include <cstdio>
#include <vector>
#include <list>
#include <map>
#include <string>

int main(void) {
    std::cout << "emplace" << std::endl;

    std::vector<int> v;
    unboost::emplace_back(v, 1);
    unboost::emplace_back(v, 2);
    assert(v.size() == 2);
    assert(v[0] == 1);
    assert(v[1] == 2);

    std::list<int> lis;
    unboost::emplace_back(lis, 1);
    unboost::emplace_back(lis, 2);
    std::list<int>::iterator it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);

    unboost::emplace_at(lis, lis.end(), 3);
    it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);

    std::map<int, std::string> m;
    unboost::emplace(m, 1, "one");
    unboost::emplace(m, 2, "two");
    unboost::emplace(m, 3, "three");
    assert(m[1] == "one");
    assert(m[2] == "two");
    assert(m[3] == "three");

    std::cout << "success" << std::endl;

    return 0;
}
