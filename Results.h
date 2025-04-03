#ifndef  __RESULTS_H
#define __RESULTS_H

#include <list>
#include <string>
#include <tuple>


class Results
{
public:
	enum ResultValue { MarioLostLive, finished, noResult};

private:
	std::list<std::tuple<size_t, ResultValue,int>> results; 
public:

	static Results loadResults(const std::string& filename);

	void saveResults(const std::string& filename) const;

	void addResult(size_t iteration, ResultValue result, int extraValue = 0) {
		results.emplace_back(iteration, result, extraValue);
	}


	std::tuple<size_t, ResultValue, int> popResult() {
		if (results.empty()) return { 0, Results::noResult, 0 };
		auto result = results.front();
		results.pop_front();
		return result;
	}


	bool isFinishedBy(size_t iteration) const {
		return results.empty() || std::get<0>(results.back())+1 <= iteration;
	}

	size_t getNextBombIteration() const;

	const std::list<std::tuple<size_t, Results::ResultValue, int>>&getResults() const 
	{
		return results;
	}


	
};

#endif
