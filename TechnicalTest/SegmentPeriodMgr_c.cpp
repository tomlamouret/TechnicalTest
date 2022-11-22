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
    // SetsToSearch will contain all the intervals to compare separated in different vectors representing the different sets.
    std::vector<std::vector<SegmentPeriod_c>> SetsToSearch;
    
    // Indexes will allow to keep track of which interval is to be compared within the vector of different intervals of a set.
    std::vector<int> Indexes;
    
    std::set<std::string>::iterator SetItr;
    
    for (SetItr = SegmentSet.begin(); SetItr != SegmentSet.end(); ++SetItr)
    {
        std::vector<SegmentPeriod_c> SpecificSet = SegmentPeriodMgr.GetById(*SetItr);
        
        // Sort the vector so that the intervals are in chronological order. Overrode the less than operator function of SegmentPeriod_c to make std::sort() work.
        sort(SpecificSet.begin(), SpecificSet.end());
        
        // Adds the sorted intervals from one of the specified sets to SetsToSearch.
        SetsToSearch.push_back(SpecificSet);
        
        // Initializes the indexes to 0.
        Indexes.push_back(0);
    }
    
    std::vector<std::pair<int, int>> CommonIntervals;
    bool NotLastLoop = true;
    int StartTime = 0, EndTime = 0;
    
    while (NotLastLoop)
    {
        int i = 0;
        bool AddCommonInterval = true;
        
        while (i < SetsToSearch.size()) {
            if (i == 0)
            {
                // Current interval of the first set
                StartTime = SetsToSearch[i][Indexes[i]].StartTime();
                EndTime = SetsToSearch[i][Indexes[i]].EndTime();
            }
            
            // No intersection found.
            else if (SetsToSearch[i][Indexes[i]].StartTime() >= EndTime || SetsToSearch[i][Indexes[i]].EndTime() <= StartTime) {
                
                // This is to avoid an out-of-bounds exception.
                if (Indexes[i] == SetsToSearch[i].size() - 1)
                {
                    
                    // This if-else statement ensures that Indexes[0] can be incremented.
                    if (Indexes[i - 1] == SetsToSearch[i - 1].size() - 1)
                    {
                        
                        // No more intervals to compare.
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
            
            // Updates the intersection.
            else {
                StartTime = std::max(StartTime, SetsToSearch[i][Indexes[i]].StartTime());
                EndTime = std::min(EndTime, SetsToSearch[i][Indexes[i]].EndTime());
            }
            ++i;
        }
        
        if (AddCommonInterval)
        {
            CommonIntervals.push_back(std::make_pair(StartTime, EndTime));
            
            // The extra decrementation of i cancels out the final incrementation of i in the preceding while loop.
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
