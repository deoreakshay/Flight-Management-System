#include <flight_info_read_operations.h>

FlightInfoReadOperation::FlightInfoReadOperation(const std::shared_ptr<FlightDatabase> data_base):
                                                flight_data_base_{data_base}
{

}
std::pair<FlightInfo,bool> FlightInfoReadOperation::GetFlightDetail(const FlightNumberType& flight_number)
{
    auto flight_info_map = flight_data_base_->GetFlightInfo();
    FlightInfo flight_info;
    bool sucess = false;

    if(flight_info_map->find(flight_number) != cend(*flight_info_map))
    {
        sucess = true;
        flight_info = flight_info_map->at(flight_number);
    }
    return std::make_pair(flight_info,sucess);
}

std::vector<FlightNumberType> FlightInfoReadOperation::GetListOfFlightFromTheCity(const std::string& source_city_name)
{
    std::vector<FlightNumberType> list_of_flight;
    auto flight_info_map = flight_data_base_->GetFlightInfo();

    std::for_each(cbegin(*flight_info_map),cend(*flight_info_map),[&](const auto& flight_info)
    {
       if(flight_info.second.origin_city == source_city_name)
       {
           list_of_flight.push_back(flight_info.first);
       }
    });
    return list_of_flight;
}

std::vector<FlightNumberType> FlightInfoReadOperation::GetListOfFlightFromOperator(const std::string& operator_name)
{
    std::vector<FlightNumberType> list_of_flight;
    auto flight_info_map = flight_data_base_->GetFlightInfo();

    std::for_each(cbegin(*flight_info_map),cend(*flight_info_map),[&](const auto& flight_info)
    {
        if(flight_info.second.flight_operator == operator_name)
        {
            list_of_flight.push_back(flight_info.first);
        }
    });
    return list_of_flight;
}

AirFareType FlightInfoReadOperation::AverageAirFare()
{
    AirFareType total_air_fare{0.0};
    AirFareType average{0.0};
    auto flight_info_map = flight_data_base_->GetFlightInfo();

    for(const auto& flight_info: *flight_info_map)
    {
        total_air_fare += flight_info.second.air_fare;
    }
    if(!flight_info_map->empty())
        average  = total_air_fare/flight_data_base_->GetNumberofTrips();
    return average;
}

void FlightInfoReadOperation::UpdateMaximumAirFareOperatorname(const OperatorNameUpdate operator_name)
{
    std::vector<NameType> flight_operator_name_list;
    std::int32_t number_of_max_fare{0};
    AirFareType max_air_fare{0.0};

    auto flight_info_map = flight_data_base_->GetFlightInfo();

    for(const auto& flight_info: *flight_info_map)
    {
        if(!number_of_max_fare)
        {
            number_of_max_fare++;
            max_air_fare = flight_info.second.air_fare;
            flight_operator_name_list.push_back(flight_info.second.flight_operator);
        }
        else
        {
            if(flight_info.second.air_fare > max_air_fare)
            {
                flight_operator_name_list.clear();
                max_air_fare = flight_info.second.air_fare;
                flight_operator_name_list.push_back(flight_info.second.flight_operator);
            }
            else if(flight_info.second.air_fare == max_air_fare)
            {
                flight_operator_name_list.push_back(flight_info.second.flight_operator);
            }
        }
    }

    for(auto& index : flight_operator_name_list)
    {
        operator_name(index,max_air_fare);
    }
}

AirFareType FlightInfoReadOperation::GetAirFare(const FlightNumberType& flight_number)
{
    auto flight_info_map = flight_data_base_->GetFlightInfo();
    AirFareType air_fare{0.0};

    auto index = flight_info_map->find(flight_number);
    if(index != cend(*flight_info_map))
    {
        air_fare = index->second.air_fare;
    }
    return air_fare;
}