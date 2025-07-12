#include "Records.h"

namespace ApplesGame {
	void InitRecords(Records& record, int recordIndex, int* selectedFakeNameIndices) {
		const int recordValue = (int)(10.f + rand() / (float)RAND_MAX * (140.f - 10.f));
		const float recordTime = 30.f + rand() / (float)RAND_MAX * (80.f - 30.f);
		record.userScore = recordValue;
		record.userTime = recordTime;
		int userNameIndex = (int)(rand() / (float)RAND_MAX * 40.f);
		while (std::any_of(selectedFakeNameIndices, selectedFakeNameIndices + NUM_RECORDS, [userNameIndex](int idx) { return idx == userNameIndex; })) {
			userNameIndex = (int)(rand() / (float)RAND_MAX * 40.f);
		}
		selectedFakeNameIndices[recordIndex] = userNameIndex;
		record.userName = FAKE_USERS_NAME[userNameIndex];
	}
	void WriteMyRecord(Records* RecordsList, int myScore, float myPlayTime, SortByValue sortBy) {
		Records* myRecord = std::find_if(RecordsList, RecordsList + NUM_RECORDS, [](Records item) -> bool { return item.isMe; });
		myRecord->userScore = myScore;
		myRecord->userTime = myPlayTime;
		SortList(RecordsList, sortBy);
	}
	void SortList(Records* RecordsList, SortByValue sortBy) {
		std::sort(
			RecordsList,
			RecordsList + NUM_RECORDS,
			[sortBy](Records a, Records b) {
				if (sortBy == SortByValue::Score) return  a.userScore > b.userScore;
				else return a.userTime < b.userTime;
			});
	}
}