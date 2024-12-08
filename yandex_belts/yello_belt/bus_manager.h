#pragma once

#include <iostream>
#include <unordered_map>
#include <ostream>
#include "responses.h"
#include "query.h"

using namespace std;
using namespace bus_response;

namespace bmanager {
    using map_stops = unordered_map<string, BusesForStopResponse>;
    using map_buses = unordered_map<string, StopsForBusResponse>;

    class BusManager {
        public:
            void AddBus(const string& bus, const vector<string>& stops);
            BusesForStopResponse GetBusesForStop(const string& stop) const;
            StopsForBusResponse GetStopsForBus(const string& bus) const;
            AllBusesResponse GetAllBuses() const;
        private:
            map_stops        stops;
            map_buses        buses;
            AllBusesResponse all_buses;
    };
}