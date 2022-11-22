#ifndef SEGMENTPERIODMGR_C_HPP
#define SEGMENTPERIODMGR_C_HPP

#include <set>
#include <string>
#include <utility>
#include <vector>
#include "SegmentPeriod_c.hpp"

class SegmentPeriodMgr_c
{
public: 
    SegmentPeriodMgr_c(std::vector<SegmentPeriod_c> SegmentPeriodVector);
    std::vector<SegmentPeriod_c> GetAll() const;
    std::vector<SegmentPeriod_c> GetById(const std::string &SegmentId) const;
    std::vector<std::pair<int, int>> FindCommonIntervals(const SegmentPeriodMgr_c& SegmentPeriodMgr, const std::set<std::string>& SegmentSet);

private:
    std::vector<SegmentPeriod_c> m_SegmentPeriodVector;
};

#endif
