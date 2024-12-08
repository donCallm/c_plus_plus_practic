#include "bus_manager.h"

namespace bmanager {
    void BusManager::AddBus(const string& new_bus, const vector<string>& new_stops) {
        if (buses.find(new_bus) != buses.end())
            return;
        
        for (const auto& item : new_stops) {
            if (stops[item].stop_name == "")
                stops[item].stop_name = item;
            stops[item].buses.emplace_back(new_bus);

            if (buses[new_bus].bus_name == "")
                buses[new_bus].bus_name = new_bus;
            buses[new_bus].stops.emplace_back(stops[item]);
        }

        all_buses.buses[new_bus] = new_stops;
    }

    BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
        if (stops.find(stop) != stops.end())
            return stops.at(stop);
        return {};
    } 

    StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
        if (buses.find(bus) != buses.end())
            return buses.at(bus);
        return {};
    }

    AllBusesResponse BusManager::GetAllBuses() const {
        return all_buses;
    }
}