#ifndef STATUS_H_
#define STATUS_H_

#include "common.h"
#include "Rule.h"
using namespace std;

namespace tinyYACC {
	struct Status;
	typedef shared_ptr<Status> statusPtr;

	//
	// status 其实就是一层壳而已.
	//
	struct Status {
		shared_ptr<set<Item>> items;  // 用于记录一大票的Item

		Status() :
			items(make_shared<set<Item>>())
		{}

		void insertItem(const Item& it) {
			items->insert(it);
		}
		friend wostream& operator<<(wostream&os, const Status& s);
	};

	//
	// 为了尽量减少比较,这里计算一下hash值.
	//
	struct StatusHash {
		size_t operator() (const Status & s) const {
			size_t res = 1;
			for (auto it : *s.items) {
				res = res ^ (it.hash() << 1);
			}
			return res;
		}
	};
}

#endif // !STATUS_H_