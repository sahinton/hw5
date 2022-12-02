

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, vector<int>& shifts, int row, int col
);
bool isAvailable(const AvailabilityMatrix& avail, int row, int col);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
		int n = avail.size();
		int k = avail[0].size();
		sched.resize(n);
		vector<int> shifts;
		shifts.resize(k);
		//build sched matrix
		for(int i = 0; i < n; i++){
			sched[i].resize(dailyNeed);
			for(int j = 0; j < dailyNeed; j++){
				sched[i][j] = -1;
			}
		}
		
		
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);




}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, vector<int>& shifts, int row, int col
){
	//get n and k
	int n = avail.size();
	int k = avail[0].size();
  if(row == n){
    return true;
  }
	if(sched[row][col] == -1){
		for(int i = 0; i < k; i++){
			if(isAvailable(avail, row, i) && shifts[i] < maxShifts){
				sched[row][col] = i;
				shifts[i]++;
				if(col == dailyNeed - 1){
					if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, row + 1, 0)){
						return true;
					}
				}
				else{
					if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, row, col + 1)){
						return true;
					}
				}
			}
		}
		sched[row][col] = -1;
	}
	return false;

}

bool isAvailable(const AvailabilityMatrix& avail, int row, int col){
    if(avail[row][col] == true){
        return true;
    }
    else{
        return false;
    }
}
