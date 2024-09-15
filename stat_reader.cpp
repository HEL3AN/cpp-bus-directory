#include "stat_reader.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

RequestDescription ParseRequestDescription(std::string_view line) {
    auto space_pos = line.find_first_of(' ');
    if (space_pos == line.npos) {
        return {};
    }

    return {std::string(line.substr(0, space_pos)),
            std::string(line.substr(space_pos + 1))};
}

void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request,
                       std::ostream& output) {
    auto request_description = ParseRequestDescription(request);
    if (request_description.command == "Bus") {
        auto bus_info = tansport_catalogue.GetBusInfo(request_description.id);
        if (bus_info.route.empty()) {
            output << "Bus " << request_description.id << ": not found\n";
            return;
        }
        std::sort(bus_info.route.begin(), bus_info.route.end(),
                  [](const Stop* lhs, const Stop* rhs) {
                      return lhs->name < rhs->name;
                  }); // сортировка остановок для использования в unique
        output << "Bus " << bus_info.name << ": "
               << bus_info.route.size() << " stops on route, "
               << std::unique(bus_info.route.begin(), bus_info.route.end()) - bus_info.route.begin() << " unique stops, "
               << std::setprecision(6) << bus_info.route_length << " route length \n";
    }
}