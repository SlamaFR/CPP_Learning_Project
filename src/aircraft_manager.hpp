#pragma once

#include "aircraft.hpp"

#include <vector>

class AircraftManager : public GL::DynamicObject
{
public:
    void add_aircraft(std::unique_ptr<Aircraft> aircraft) { aircrafts.emplace_back(std::move(aircraft)); }

    bool move() override
    {
        for (auto it = aircrafts.begin(); it != aircrafts.end();)
        {
            if ((*it)->move())
            {
                it = aircrafts.erase(it);
            }
            else
            {
                ++it;
            }
        }
        return true;
    }

private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
};
