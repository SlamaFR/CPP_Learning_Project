#pragma once

#include "aircraft.hpp"

#include <algorithm>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
public:
    void add_aircraft(std::unique_ptr<Aircraft> aircraft) { aircrafts.emplace_back(std::move(aircraft)); }

    bool move() override
    {
        auto toDelete = std::remove_if(aircrafts.begin(), aircrafts.end(), [](const auto& item) { return item->move(); });
        aircrafts.erase(toDelete, aircrafts.end());
        return true;
    }

private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
};
