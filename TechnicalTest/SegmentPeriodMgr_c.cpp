#include "SegmentMgr_c.hpp"
#include <algorithm>

constexpr int TIME_START = 0;
constexpr int TIME_END = 24 * 60 * 60;

SegmentPeriodMgr_c::SegmentPeriodMgr_c(std::vector<SegmentPeriod_c> SegmentPeriodVector) : m_SegmentPeriodVector(SegmentPeriodVector)
{
}

std::vector<SegmentPeriod_c> SegmentPeriodMgr_c::GetAll() const
{
    return m_SegmentPeriodVector;
}

std::vector<SegmentPeriod_c> SegmentPeriodMgr_c::GetById(const std::string &SegmentId) const
{
    std::vector<SegmentPeriod_c> w_ToReturn;
    for (SegmentPeriod_c SegmentPeriod : m_SegmentPeriodVector)
    {
        if (SegmentPeriod.SegmentId() == SegmentId)
        {
            w_ToReturn.push_back(SegmentPeriod);
        }
    }
    return w_ToReturn;
}

std::vector<std::pair<int, int>> SegmentPeriodMgr_c::FindCommonIntervals(const SegmentPeriodMgr_c& SegmentPeriodMgr, const std::set<std::string>& SegmentSet)
{
    std::vector<std::vector<SegmentPeriod_c>> SetsToSearch;
    std::vector<int> Indexes;
    std::set<std::string>::iterator SetItr;
    for (SetItr = SegmentSet.begin(); SetItr != SegmentSet.end(); ++SetItr)
    {
        std::vector<SegmentPeriod_c> SpecificSet = SegmentPeriodMgr.GetById(*SetItr);
        // Sort the vector so that the intervals are in chronological order. I could override the sort() function to be able to sort vectors of SegmentPeriod_c objects.
        sort(SpecificSet.begin(), SpecificSet.end());
        // Adds the sorted intervals from one of the specified sets to SetsToSearch.
        SetsToSearch.push_back(SpecificSet);
        // Initializes the indexes to 0.
        Indexes.push_back(0);
    }
    
    // This block would allow to find the first common interval; the actual solution should only contain one nested loop
    //    int MinEndTime = SetsToSearch[0][0].EndTime();
    //    int SmallestFirstIntervalIndex = 0;
    //    for (int i = 0; 0 < SetsToSearch.size(); ++i)
    //    {
    //        if (SetsToSearch[i][0].EndTime() < MinEndTime)
    //        {
    //            MinEndTime = SetsToSearch[i][0].EndTime();
    //            SmallestFirstIntervalIndex = i;
    //        }
    //    }
    //    CommonIntervals.push_back(std::make_pair(SetsToSearch[SmallestFirstIntervalIndex][0].StartTime(), SetsToSearch[SmallestFirstIntervalIndex][0].EndTime()));
    //    Indexes[SmallestFirstIntervalIndex]++;
    //    while (true)
    //    {
    //        // First interval of the first set
    //        int StartTime = SetsToSearch[0][Indexes[0]].StartTime();
    //        int EndTime = SetsToSearch[0][Indexes[0]].EndTime();
    //
    //        bool AddCommonInterval = true;
    //
    //        // Check rest of the intervals and find the intersection
    //        for (int i = 1; i < SetsToSearch.size(); i++) {
    //
    //            // If no intersection exists
    //            if (SetsToSearch[i][Indexes[i]].StartTime() > EndTime || SetsToSearch[i][Indexes[i]].EndTime() < StartTime) {
    //                Indexes[i]++;
    //                AddCommonInterval = false;
    //                break;
    //            }
    //
    //            // Else update the intersection
    //            else {
    //                StartTime = std::max(StartTime, SetsToSearch[i][Indexes[i]].StartTime());
    //                EndTime = std::min(EndTime, SetsToSearch[i][Indexes[i]].EndTime());
    //            }
    //        }
    //
    //        if (AddCommonInterval)
    //        {
    //            CommonIntervals.push_back(std::make_pair(SetsToSearch[][].StartTime(), SetsToSearch[][].EndTime()));
    //        }
    //    }
    
    std::vector<std::pair<int, int>> CommonIntervals;
    bool NotLastLoop = true;
    int StartTime = 0, EndTime = 0;
    
    while (NotLastLoop)
    {
        int i = 0;
        bool AddCommonInterval = true;
        
        // Check rest of the intervals and find the intersection
        while (i < SetsToSearch.size()) {
            if (i == 0)
            {
                // First interval of the first set
                StartTime = SetsToSearch[i][Indexes[i]].StartTime();
                EndTime = SetsToSearch[i][Indexes[i]].EndTime();
            }
            
            // If no intersection exists
            else if (SetsToSearch[i][Indexes[i]].StartTime() >= EndTime || SetsToSearch[i][Indexes[i]].EndTime() <= StartTime) {
                if (Indexes[i] == SetsToSearch[i].size() - 1)
                {
                    if (Indexes[i - 1] == SetsToSearch[i - 1].size() - 1)
                    {
                        NotLastLoop = false;
                    }
                    else
                    {
                        Indexes[i - 1]++;
                    }
                }
                else
                {
                    Indexes[i]++;
                }
                AddCommonInterval = false;
                break;
            }
            
            // Else update the intersection
            else {
                StartTime = std::max(StartTime, SetsToSearch[i][Indexes[i]].StartTime());
                EndTime = std::min(EndTime, SetsToSearch[i][Indexes[i]].EndTime());
            }
            ++i;
        }
        
        if (AddCommonInterval)
        {
            CommonIntervals.push_back(std::make_pair(StartTime, EndTime));
            if (Indexes[i - 1] == SetsToSearch[i - 1].size() - 1)
            {
                if (Indexes[i - 2] == SetsToSearch[i - 2].size() - 1)
                {
                    NotLastLoop = false;
                }
                else
                {
                    Indexes[i - 2]++;
                }
            }
            else
            {
                Indexes[i - 1]++;
            }
        }
    }
    
    return CommonIntervals;
}
