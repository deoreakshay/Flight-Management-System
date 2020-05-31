#ifndef _FLIGHT_INFO_WRITE_OPERATION_
#define _FLIGHT_INFO_WRITE_OPERATION_
#include <flight_database.h>

class FlightInfoWriteOperation
{
public:
    explicit FlightInfoWriteOperation(const std::shared_ptr<FlightDatabase> data_base);

    bool AddTrip(const FlightInfo& flight_info);
    bool UpdateTrip(const FlightInfo& flight_info);
    bool RemoveTrip(const FlightNumberType& flight_number);
    ~FlightInfoWriteOperation()= default;
private:
    std::shared_ptr<FlightDatabase> flight_data_base_;
};

#endif //_FLIGHT_INFO_WRITE_OPERATION_