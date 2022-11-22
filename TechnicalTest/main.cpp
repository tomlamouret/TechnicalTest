//
//  main.cpp
//  TechnicalTest
//
//  Created by Tom Lamouret on 2022-11-20.
//

#include "SegmentPeriod_c.hpp"
#include "SegmentMgr_c.hpp"
#include <iostream>

int main(int argc, const char * argv[])
{
    std::vector<SegmentPeriod_c> SegmentPeriodVector;
    SegmentPeriodVector.insert(SegmentPeriodVector.end(), {SegmentPeriod_c("A", 0, 12), SegmentPeriod_c("A", 12, 24), SegmentPeriod_c("B", 0, 8), SegmentPeriod_c("B", 8, 12), SegmentPeriod_c("B", 12, 24), SegmentPeriod_c("C", 0, 10), SegmentPeriod_c("C", 10, 20), SegmentPeriod_c("C", 20, 24)});

    SegmentPeriodMgr_c SegmentPeriodMgr = SegmentPeriodMgr_c(SegmentPeriodVector);
    
    // Objets SegmentPeriod_c présents dans SegmentPeriodMgr :
    // (A, 0h – 12h), (A, 12h – 24h),
    // (B, 0h – 8h), (B, 8h – 12h), (B, 12h – 24h),
    // (C, 0h – 10h), (C, 10h – 20h), (C, 20h – 24h)
    
    std::set<std::string> SegmentSet = {"A", "B"};
    std::vector<std::pair<int, int>> CommonIntervalVector = SegmentPeriodMgr.FindCommonIntervals(SegmentPeriodMgr, SegmentSet);
    
    // CommonIntervalVector = <0h, 8h>, <8h, 12h>, <12h, 24h>
    
    for (const auto& pair : CommonIntervalVector)
    {
        std::cout << "<" << pair.first << ", " << pair.second << "h>" << std::endl;
    }
}
