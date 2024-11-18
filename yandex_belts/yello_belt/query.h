#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace query {
    enum class QueryType {
        NewBus,
        BusesForStop,
        StopsForBus,
        AllBuses
    };

    struct Query {
        QueryType                type;
        string              bus;
        string              stop;
        string              stop_count;
        vector<string> stops;
    };

    istream& operator>>(istream& is, Query& q);
}