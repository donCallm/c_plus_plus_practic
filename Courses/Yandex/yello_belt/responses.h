#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

namespace bus_response {
    struct BusesForStopResponse {
        string              stop_name;
        vector<string> buses;
    };

    struct StopsForBusResponse {
        string              bus_name;
        vector<BusesForStopResponse> stops;
    };

    struct AllBusesResponse {
        unordered_map<string, vector<string>> buses;
    };

    ostream& operator<<(ostream& os, const BusesForStopResponse& r);  
    ostream& operator<<(ostream& os, const StopsForBusResponse& r);
    ostream& operator<<(ostream& os, const AllBusesResponse& r);
    bool operator<(const StopsForBusResponse& f, const StopsForBusResponse& s);
}