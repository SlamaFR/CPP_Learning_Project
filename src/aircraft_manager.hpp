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

        std::sort(aircrafts.begin(), aircrafts.end(),
                  [](const std::unique_ptr<Aircraft>& a, const std::unique_ptr<Aircraft>& b)
                  {
                      if (a->has_terminal())
                          return true;
                      if (b->has_terminal())
                          return false;
                      return a->fuel_level() < b->fuel_level();
                  });

        auto toDelete =
            std::remove_if(aircrafts.begin(), aircrafts.end(), [](const auto& item) { return item->move(); });
        aircrafts.erase(toDelete, aircrafts.end());
        return true;
    }

    int get_required_fuel() const
    {
        return std::reduce(aircrafts.begin(), aircrafts.end(), 0,
                           [](int acc, const std::unique_ptr<Aircraft>& cur)
                           {
                               if (!cur->is_low_on_fuel() || cur->has_served())
                                   return acc;
                               return acc + 3000 - cur->fuel_level();
                           });
    }

private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
};
