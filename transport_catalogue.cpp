#include "transport_catalogue.h"

void TransportCatalogue::AddStop(std::string_view name, Coordinates coordinates) {
    stops_.emplace_back(Stop{std::string(name), coordinates});
    //stops_.push_back({move(std::string(name.data(), name.size())), coordinates});
    stopname_to_stop_[name] = &stops_.back();
}

void TransportCatalogue::AddBus(std::string_view name, std::vector<std::string_view> route) {
    // route_length
    double route_length = 0;
    for (auto it = route.begin() + 1; it != route.end(); ++it) {
        auto prev_stop = stopname_to_stop_.find(*(it - 1));
        auto stop = stopname_to_stop_.find(*it);
        route_length += ComputeDistance(stop->second->coordinates, (prev_stop)->second->coordinates);
    }

    buses_.emplace_back(Bus{std::string(name), {}, route_length});
    for (const auto& stop_name : route) {
        // Добавляем указатели на остановки в маршрут
        buses_.back().route.push_back(stopname_to_stop_.at(std::string(stop_name)));
    }
    busname_to_bus_[buses_.back().name] = &buses_.back();
}

Bus TransportCatalogue::GetBusInfo(std::string_view name) const {
    return busname_to_bus_.count(name) ? *busname_to_bus_.at(name) : Bus{};
}