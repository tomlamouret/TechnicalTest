#include <string>
#include "SegmentPeriod_c.hpp"

SegmentPeriod_c::SegmentPeriod_c(std::string SegmentId, int StartTime, int EndTime):m_SegmentId(SegmentId), m_StartTime(StartTime), m_EndTime(EndTime)
{}

std::string SegmentPeriod_c::SegmentId() const
{
    return m_SegmentId;
}

int SegmentPeriod_c::StartTime() const
{
    return m_StartTime;
}

int SegmentPeriod_c::EndTime() const
{
    return m_EndTime;
}

bool SegmentPeriod_c::operator<(const SegmentPeriod_c& rhs) const
{
    return (m_StartTime < rhs.m_EndTime);
}
