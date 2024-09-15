#pragma once
#include <deque>
#include <unordered_map>
#include <vector>
#include <string>
#include "geo.h"

struct Stop {
	std::string_view name;
	Coordinates coordinates;
};

struct Bus {
	std::string_view name;
	std::vector<Stop*> route;
	double route_length;
};

class TransportCatalogue {
public:
	void AddStop(std::string_view name, Coordinates coordinates);
	void AddBus(std::string_view name, std::vector<std::string_view> route);
	Bus GetBusInfo(std::string_view name) const;
private:
	std::unordered_map<std::string_view, Stop*> stopname_to_stop_;
	std::unordered_map<std::string_view, Bus*> busname_to_bus_;
	std::deque<Stop> stops_;
	std::deque<Bus> buses_;
};