#pragma once
#include <queue>

namespace searchStrategy {
	template<typename T, typename priority>
	struct PriorityQueue {
		using element = std::pair<priority, T>;

		std::priority_queue<element, std::vector<element>, std::greater<>> elements;

		bool empty() const { return elements.empty(); }
		void insert(T item, priority priority) { elements.emplace(priority, item); }

		T pop() {
			T best_item = elements.top().second;
			elements.pop();
			return best_item;
		}
	};
}