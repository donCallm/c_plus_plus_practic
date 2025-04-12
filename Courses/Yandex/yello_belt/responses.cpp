#include "responses.h"

namespace bus_response {
    template<typename T>
    void print_vector(const vector<T>& v) {
        if (v.size() == 0) {
            cout << "empty" << endl;
            return;
        }
        for (size_t i = 0; i < v.size(); ++i) {
            cout << v[i];
            if (i != v.size() - 1) cout << ' ';
        }
    }

    ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
        if (r.stop_name == "")
            os << "No stop";
        else if (r.buses.size() == 1) 
            os << "No interchange";
        else
            print_vector<string>(r.buses);
        return os;
    }

    ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
        if (r.bus_name == "") {
            os << "No bus";
            return os;
        }
        for (size_t i = 0; i < r.stops.size(); ++i) {
            os << "Stop " << r.stops[i].stop_name << ": ";
            if (r.stops[i].buses.size() == 1) {
                os << "No interchange";
            }
            else {
                for (size_t j = 0; j < r.stops[i].buses.size(); ++j) {
                    if (r.stops[i].buses[j] != r.bus_name)
                        os << r.stops[i].buses[j];
                    if (j != r.stops[i].buses.size() - 1)
                        os << ' ';
                }
            }
            if (i != r.stops.size() - 1) cout << endl;
        }
        return os;
    }

    ostream& operator<<(ostream& os, const AllBusesResponse& r) {
        if (r.buses.size() == 0) {
            os << "No buses";
            return os;
        }
        for (const auto& item : r.buses) {
            os << "Bus: " << item.first << ' ';
            print_vector<string>(item.second);
            os << endl;
        }
        return os;
    }

    bool operator<(const StopsForBusResponse& f, const StopsForBusResponse& s) {
        return (f.bus_name < s.bus_name) ? true : false;
    }
}