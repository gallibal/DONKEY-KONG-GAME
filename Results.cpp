#include "Results.h"
#include <limits>
#include <fstream>


Results Results::loadResults(const std::string& filename) {
	std::ifstream results_file(filename);
	Results results;
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		int score;
		results_file >> iteration >> result >> score;
		results.addResult(iteration, static_cast<ResultValue>(result),score);
	}
	return results;
}

void Results::saveResults(const std::string& filename) const {
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << std::get<0>(result) << ' ' << std::get<1>(result) << ' ' << std::get<2>(result);
	}
	results_file.close();
}

size_t Results::getNextBombIteration() const {
	if (!results.empty() && std::get<1>(results.front()) == MarioLostLive) {
		return std::get<0>(results.front());
	}

	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}
