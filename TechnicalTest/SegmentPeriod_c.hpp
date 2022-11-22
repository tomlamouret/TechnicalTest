#ifndef SEGMENTPERIOD_C_HPP
#define SEGMENTPERIOD_C_HPP

#include <string>

class SegmentPeriod_c
{
public:
    SegmentPeriod_c(std::string SegmentId, int StartTime, int EndTime);
    std::string SegmentId() const;
    int StartTime() const;
    int EndTime() const;
    bool operator<(const SegmentPeriod_c& rhs) const;

private:
    std::string m_SegmentId; // Identificateur du segment
    int m_StartTime;         // Heure de début de l’intervalle du segment
    int m_EndTime;           // Heure de fin de l’intervalle du segment
};

#endif
