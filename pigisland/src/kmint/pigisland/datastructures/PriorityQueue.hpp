#pragma once
#include <queue>

namespace searchStrategy {
	template<typename T, typename priority_t>
	struct PriorityQueue {
		using element = std::pair<priority_t, T>;

		std::priority_queue<element, std::vector<element>, std::greater<>> elements;

		bool empty() const { return elements.empty(); }
		void insert(T item, priority_t priority) { elements.emplace(priority, item); }

		T pop() {
			T best_item = elements.top().second;
			elements.pop();
			return best_item;
		}
	};
}