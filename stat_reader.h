#pragma once

#include <iosfwd>
#include <string_view>

#include "transport_catalogue.h"

struct RequestDescription {
    std::string command;
    std::string id;
};

void ParseAndPrintStat(const TransportCatalogue& transport_catalogue, std::string_view request,
                       std::ostream& output);