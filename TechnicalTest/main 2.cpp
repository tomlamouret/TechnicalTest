#include <set>
#include <string>
#include "SegmentPeriod_c.hpp"
#include "SegmentMgr_c.hpp"

int main()
{
    SegmentPeriod_c SegmentPeriodA1 = SegmentPeriod_c("A", 0, 12);
    SegmentPeriod_c SegmentPeriodA2 = SegmentPeriod_c("A", 12, 24);
    SegmentPeriod_c SegmentPeriodB1 = SegmentPeriod_c("B", 0, 8);
    SegmentPeriod_c SegmentPeriodB2 = SegmentPeriod_c("B", 8, 12);
    SegmentPeriod_c SegmentPeriodB3 = SegmentPeriod_c("B", 12, 24);
    SegmentPeriod_c SegmentPeriodC1 = SegmentPeriod_c("C", 0, 10);
    SegmentPeriod_c SegmentPeriodC2 = SegmentPeriod_c("C", 10, 20);
    SegmentPeriod_c SegmentPeriodC3 = SegmentPeriod_c("C", 20, 24);
    
    std::vector<SegmentPeriod_c> SegmentPeriodVector;
    SegmentPeriodVector.push_back(SegmentPeriodA1);
    SegmentPeriodVector.push_back(SegmentPeriodA2);
    SegmentPeriodVector.push_back(SegmentPeriodB1);
    SegmentPeriodVector.push_back(SegmentPeriodB2);
    SegmentPeriodVector.push_back(SegmentPeriodB3);
    SegmentPeriodVector.push_back(SegmentPeriodC1);
    SegmentPeriodVector.push_back(SegmentPeriodC2);
    SegmentPeriodVector.push_back(SegmentPeriodC3);

    SegmentPeriodMgr_c SegmentPeriodMgr = SegmentPeriodMgr_c(SegmentPeriodVector);
    // Objets SegmentPeriod_c présents dans SegmentPeriodMgr :
    // (A, 0h – 12h), (A, 12h – 24h),
    // (B, 0h – 8h), (B, 8h – 12h), (B, 12h – 24h),
    // (C, 0h – 10h), (C, 10h – 20h), (C, 20h – 24h)
    std::set<std::string> SegmentSet = {A, B};
    std::vector<std::pair<int, int>> CommonIntervalVector = FindCommonIntervals(SegmentPeriodMgr, SegmentSet);
    // CommonIntervalVector = <0h, 8h>, <8h, 12h>, <12h, 24h>
}