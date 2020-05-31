#include <flight_info_write_operations.h>

FlightInfoWriteOperation::FlightInfoWriteOperation(const std::shared_ptr<FlightDatabase> data_base):
        flight_data_base_{data_base}
{

}

bool FlightInfoWriteOperation::AddTrip(const FlightInfo& flight_info)
{
    return flight_data_base_->AddTrip(flight_info);
}

bool FlightInfoWriteOperation::UpdateTrip(const FlightInfo& flight_info)
{
    return flight_data_base_->UpdateTrip(flight_info);
}

bool FlightInfoWriteOperation::RemoveTrip(const FlightNumberType& flight_number)
{
    return flight_data_base_->RemoveTrip(flight_number);
}