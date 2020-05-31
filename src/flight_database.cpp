#include <flight_database.h>

FlightDatabase::FlightDatabase()
{
    flight_info_map_ = std::make_unique<FlightInfoMap>();
    list_of_flights_reduce_fire_ = std::make_unique<ListOfReducedPricePercentage>();
}

FlightDatabase::FlightDatabase(FlightDatabase&& flight_database)noexcept
{
    flight_info_map_ = std::move(flight_database.flight_info_map_);
    list_of_flights_reduce_fire_ = std::move(flight_database.list_of_flights_reduce_fire_);
    number_of_trips_ = flight_database.number_of_trips_;
}

FlightDatabase &FlightDatabase::operator=(FlightDatabase&& flight_database)noexcept
{
    if(this == &flight_database)
        return *this;

    this->flight_info_map_ = std::move(flight_database.flight_info_map_);
    this->list_of_flights_reduce_fire_ = std::move(flight_database.list_of_flights_reduce_fire_);
    this->number_of_trips_ = flight_database.number_of_trips_;

    return *this;
}

bool FlightDatabase::AddTrip(const FlightInfo& flight_info)
{
    std::lock_guard<std::mutex> lk(lock_data_base_);
    bool success = false;
    success = InsertFlightInfoMap(flight_info);
    if(success)
    {
        EntryReducedPricePercentage(flight_info.flight_number);
        ++number_of_trips_;
    }
    return success;
}

bool FlightDatabase::UpdateTrip(const FlightInfo& flight_info)
{
    std::lock_guard<std::mutex> lk(lock_data_base_);
    UpdateReducedPricePercentage(flight_info.flight_number,flight_info.air_fare);
    return  UpdateFlightInfoMap(flight_info);
}
bool FlightDatabase::RemoveTrip(const FlightNumberType flight_number)
{
    std::lock_guard<std::mutex> lk(lock_data_base_);
    bool sucess =  RemoveFlightInfoMap(flight_number);
    if(sucess)
    {
        RemoveFlightFromReducedPrice(flight_number);
        --number_of_trips_;
    }
    return sucess;
}
std::shared_ptr<FlightInfoMap> FlightDatabase::GetFlightInfo()const
{
    return std::make_shared<FlightInfoMap>(*flight_info_map_);
}

std::shared_ptr<ListOfReducedPricePercentage> FlightDatabase::GetFlightDiscountInfo()const
{
    return std::make_shared<ListOfReducedPricePercentage>(*list_of_flights_reduce_fire_);
}
uint32_t FlightDatabase::GetNumberofTrips()const
{
    return number_of_trips_;
}
bool FlightDatabase::InsertFlightInfoMap(const FlightInfo& flight_info)
{
    auto retun_value = flight_info_map_->insert({flight_info.flight_number,flight_info});
    return retun_value.second;
}

bool FlightDatabase::UpdateFlightInfoMap(const FlightInfo& flight_info)
{
    bool return_value = false;

    auto flight_index = flight_info_map_->find(flight_info.flight_number);
    if(flight_index != cend(*flight_info_map_))
    {
        return_value = true;
        flight_info_map_->at(flight_info.flight_number) = flight_info;
    }
    return return_value;
}

bool FlightDatabase::RemoveFlightInfoMap(const FlightNumberType& flight_number)
{
    bool sucess = false;
    if(flight_info_map_->find(flight_number)!=cend(*flight_info_map_))
    {
        sucess =  true;
        flight_info_map_->erase(flight_number);
    }
    return sucess;
}

void FlightDatabase::EntryReducedPricePercentage(const FlightNumberType& flight_number)
{
    ReducedPricePercentage flight_price{flight_number,0};
    list_of_flights_reduce_fire_->push_back(flight_price);
}

void FlightDatabase::UpdateReducedPricePercentage(const FlightNumberType& flight_number,
                                       const AirFareType& new_air_fare)
{
    auto flight_index = std::find_if(begin(*list_of_flights_reduce_fire_),end(*list_of_flights_reduce_fire_),
                                     [&](const auto& price_info){
                                         return flight_number == price_info.first;
                                     });
    if(flight_index != cend(*list_of_flights_reduce_fire_))
    {
        auto old_air_fare = flight_info_map_->at(flight_number).air_fare;
        if((new_air_fare > 0.0) && (new_air_fare < old_air_fare))
        {
            auto discount = static_cast<int32_t >(((old_air_fare - new_air_fare)/old_air_fare)*100);
            ReducedPricePercentage discount_flight{flight_number,discount};
            *flight_index = discount_flight;
        }
    }
}
void FlightDatabase::RemoveFlightFromReducedPrice(const FlightNumberType& flight_number)
{
    auto find_index = std::find_if(cbegin(*list_of_flights_reduce_fire_),cend(*list_of_flights_reduce_fire_),
                                   [&](const auto& flight_price)
    {
        return flight_price.first == flight_number;
    });
    if(find_index != cend(*list_of_flights_reduce_fire_))
    {
        list_of_flights_reduce_fire_->erase(find_index);
    }
}
