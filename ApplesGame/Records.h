#pragma once
#include <string>
#include <algorithm>
#include "Constants.h"

namespace ApplesGame {
	enum class SortByValue : int {
		Score,
		Time,
	};

	struct Records {
		bool isMe = false;
		int userScore = 0;
		float userTime = 0.f;
		std::string userName = "";
	};

	void InitRecords(Records& RecordsList, int recordIndex, int* selectedFakeNameIndices);
	void WriteMyRecord(Records* RecordsList, int myScore, float myPlayTime, SortByValue sortBy);
	void SortList(Records* RecordsList, SortByValue sortBy);
}

