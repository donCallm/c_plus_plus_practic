#include "query.h"

namespace query {
    istream& operator>>(istream& is, Query& q) {
        if (q.stops.size() != 0)
            q.stops.clear();
        size_t i = 0;
        string type;
        is >> type;
        if (type == "NEW_BUS") {
            q.type = QueryType::NewBus;
            is.ignore(1);
            is >> q.bus;
            is.ignore(1);
            is >> q.stop_count;
            is.ignore(1);
            string buf;
            while (is) {
                is >> buf;
                is.ignore(1);
                q.stops.push_back(move(buf));
            }
        } 
        else if (type == "BUSES_FOR_STOP") {
            q.type = QueryType::BusesForStop;
            is.ignore(1);
            is >> q.stop;
        }
        else if (type == "STOPS_FOR_BUS") {
            q.type = QueryType::StopsForBus;
            is.ignore(1);
            is >> q.bus;
        }
        else if (type == "ALL_BUSES") {
            q.type = QueryType::AllBuses;
        }
        else throw runtime_error("unknown query");
        
        return is;
    }
}