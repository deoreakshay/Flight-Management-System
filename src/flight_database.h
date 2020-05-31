#ifndef _FLIGHT_DATABASE_
#define _FLIGHT_DATABASE_

#include <iostream>
#include <set>
#include <string>
#include <functional>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <mutex>

using FlightNumberType = std::int32_t;
using NameType = std::string;
using AirFareType = double;
using FlightNumberListType = std::vector<FlightNumberType>;
using CityNameUpdate = std::function<void(const NameType& , const NameType& ,const AirFareType&)>;
using OperatorNameUpdate = std::function<void(const NameType& ,const AirFareType&)>;
using AirfarePriceUpdate = std::function<void(const NameType& , const FlightNumberType fight_number, const std::int32_t)>;

struct FlightInfo
{
    FlightNumberType flight_number{0};
    NameType origin_city;
    NameType destination_city;
    NameType flight_operator;
    AirFareType air_fare;

    FlightInfo() {}
    FlightInfo(FlightNumberType num, NameType &&origin, NameType &&destination, NameType &&oname, AirFareType fare)
        : flight_number(num), origin_city(std::move(origin)), destination_city(std::move(destination)), 
          flight_operator(std::move(oname)), air_fare(fare) {}
};

using FlightInfoMap = std::map<FlightNumberType, FlightInfo>;
using ReducedPricePercentage = std::pair<FlightNumberType,int32_t>;
using ListOfReducedPricePercentage = std::vector<ReducedPricePercentage>;

class FlightDatabase
{
 public:
     FlightDatabase();
     FlightDatabase(const FlightDatabase& flight_database)=delete;
     FlightDatabase(FlightDatabase&& flight_database)noexcept;
     FlightDatabase operator=(const FlightDatabase& flight_database)=delete;
     FlightDatabase &operator=(FlightDatabase&& flight_database)noexcept;

     bool AddTrip(const FlightInfo& flight_info);
     bool UpdateTrip(const FlightInfo& flight_info);
     bool RemoveTrip(const FlightNumberType flight_number);

     std::shared_ptr<FlightInfoMap> GetFlightInfo()const;
     std::shared_ptr<ListOfReducedPricePercentage> GetFlightDiscountInfo()const;
     uint32_t GetNumberofTrips()const;

 private:
     bool InsertFlightInfoMap(const FlightInfo& flight_info);
     bool UpdateFlightInfoMap(const FlightInfo& flight_info);
     bool RemoveFlightInfoMap(const FlightNumberType& flight_number);

     void EntryReducedPricePercentage(const FlightNumberType& flight_number);
     void UpdateReducedPricePercentage(const FlightNumberType& flight_number,
                                       const AirFareType& new_air_fare);
     void RemoveFlightFromReducedPrice(const FlightNumberType& flight_number);

     std::unique_ptr<FlightInfoMap> flight_info_map_;
     std::unique_ptr<ListOfReducedPricePercentage> list_of_flights_reduce_fire_;
     
     uint32_t  number_of_trips_{0};
     std::mutex lock_data_base_;
};
#endif //_FLIGHT_DATABASE_
