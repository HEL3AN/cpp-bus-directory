#include "transport_catalogue.h"

void TransportCatalogue::AddStop(std::string_view name, Coordinates coordinates) {
    stops_.push_back({move(name), coordinates}); //изменить name
    stopname_to_stop_[name] = &stops_.back();
}

void TransportCatalogue::AddBus(std::string_view name, std::vector<std::string_view> route) {
    // route
    std::vector<Stop*> route_stops;
    for (auto stop_name : route) {
        auto stop = stopname_to_stop_.find(stop_name);
        if (stop == stopname_to_stop_.end()) {
            stopname_to_stop_[stop_name] = &stops_.back();
            route_stops.push_back(&stops_.back());
        } else {
            route_stops.push_back(stop->second);
        }
    }

    // route_length
    double route_length = 0;
    for (auto it = route.begin() + 1; it != route.end(); ++it) {
        auto prev_stop = stopname_to_stop_.find(*(it - 1));
        auto stop = stopname_to_stop_.find(*it);
        route_length += ComputeDistance(stop->second->coordinates, (prev_stop)->second->coordinates);
    }

    buses_.push_back({move(name), move(route_stops), route_length}); //изменить name
    busname_to_bus_[name] = &buses_.back();
}

Bus TransportCatalogue::GetBusInfo(std::string_view name) const {
    return busname_to_bus_.count(name) ? *busname_to_bus_.at(name) : Bus{};
}