#include "intervalset.cpp"
#include <algorithm>

int IntervalSet::get_total_length() const{
    return std::accumulate(
        intervals.begin(),
        intervals.end(),
        0,
        [](int total, Interval& itvl){return total + itvl.get_length();});
}

void IntervalSet::sanitize(){

    std::vector<Interval> disjoint_intervals = []
    Interval current_interval;
    bool current_interval_valid = false;
    std::sort(intervals.begin(),intervals.end());
    for(auto& itvl: intervals){

        if(!current_interval_valid){
            current_interval = itvl;
            current_interval_valid = true;
            continue;
        }
        
        if itvl.overlaps(current_interval,true){
            current_interval = itvl.merge(current_interval);
        }
        else{
            disjoint_intervals.push_back(current_interval);
            current_interval = itvl;
        }
            
    }

    if(current_interval_valid)
        disjoint_intervals.push_back(current_interval);

    intervals = disjoint_intervals;
}

IntervalSet IntervalSet::operator&(const Inverval& other) const{

    IntervalSet ret;
    size_t i = 0;
    size_t j = 0;
    while (i<intervals.size()) and (j<other.intervals.size()){

        if(intervals[i].overlaps(other.intervals[j],false))
            ret.intervals.push_back(intervals[i].intersect(other.intervals[j]));
        
        if(intervals[i] < other.intervals[j]){
            i++;
        }
        else{
            j++;
        }
            
    }
    
    return ret;

IntervalSet IntervalSet::operator-(const InvervalSet& other) const {

        IntervalSet ret;

        size_t j = 0;
        for(auto const& itvl: intervals){

        

            // AND with -> add to ret.intervals
            // Keep doing this until you run out of other.intervals
            // or they're > and don't overlap current interval

            auto left = itvl.start;
            auto right = itvl.end;
            while( (left < right) and (j<other.intervals.size()) and (other.intervals[j].start<itvl.end) ){

            
                // If no overlap, other is too far back. Incrememt it
                if(other.intervals[j].end <= left){
                    j++;
                    continue;
                }
                    

                // There is definitely overlap here
                if(left < other.intervals[j].start){
                    ret.intervals.push_back(Interval(left,other.intervals[j].start));
                    left = other.intervals[j].end;
                }
                else{
                    left = other.intervals[j].end;
                    j++;
                }
            }       
                
                

            if(left < right)
                ret.intervals.push_back(Interval(left,right));

        }

        return ret
}         

IntervalSet IntervalSet::operator|(const InveralSet& other) const{


        IntervalSet ret;
        size_t i = 0;
        size_t j = 0;
        bool current_interval_valid = false;
        Interval current_interval;
        Interval next_interval;
        while (i < intervals.size()) or (j < other.intervals.size()):
            # Pick the next interval to be the min from the two interval sets
            # incrememnt counter for the one that was picked
            if (i == intervals.size()){
                next_interval = other.intervals[j]
                j++;
            }
            else if (j == other.intervals.size()){
                next_interval = intervals[i];
                i++;
            }
            else{
                if (intervals[i] < other.intervals[j]){
                    next_interval = intervals[i];
                    i++;
                }
                else{
                    next_interval = other.intervals[j]
                    j++;
                }
            }

            // Handle first interval
            if (!current_interval_valid){
                current_interval = next_interval;
                current_interval_valid = true;
                continue;
            }
                

            // Test if current_interval overlaps next_interval
            // then merge them and continue
            if current_interval.overlaps(next_interval){
                current_interval = current_interval.merge(next_interval);
            }
            // If no overlap, add current_interval to
            //# the running list and set current_interval to next_interval
            else{
                ret.intervals.push_back(current_interval);
                current_interval = next_interval;
            }
                

        if (current_interval_valid)
            ret.intervals.push_back(current_interval);

        return ret;
}

IntervalSet IntervalSet::operator^(const InveralSet& other) const{
    return (*this - other) | (other - *this);
}
        
IntervalSet IntervalSet::operator==(const InveralSet& other) const{
    if(intervals.size() != other.intervals.size()) return false;
    for(int i = 0; i < intervals.size(); i++){
        if(intervals[i] != other.intervals[i]) return false;
    }
    return true;
}       
