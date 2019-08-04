#include <simple_histogram/simple_histogram.h>
#include <simple_histogram/utilities/json_io.h>

#include <iostream>
#include <fmt/format.h>

using namespace histogrammer;
using namespace std;

int main(int argc, char *argv[]) {
	simple_histogram<double> histo(6, -1.0, 1.0);

	histo.sample(-2);
	histo.sample(0.0);
	histo.sample(0.5, 3.14159);

	cout << "Get out just the bin values (w/o overflow bins)\n";
	for (auto &v : histo.data()) {
		cout << fmt::format("{}\n", v);
	}

	cout << "Get out just the bin values (including overflow bins)\n";
	for (auto &v : histo.data(true)) {
		cout << fmt::format("{}\n", v);
	}

	cout << "\nFull Data (w/o overflow bins)\n";
	for (auto &v : histo.full_data()) {
		cout << fmt::format("index {: d}\t({: .1f},{: .1f})\t->{}\n", v.bin_index, v.bin_lower, v.bin_upper, v.value);
	}

	cout << "\nFull Data (w/ overflow bins)\n";
	for (auto &v : histo.full_data(true)) {
		cout << fmt::format("index {: d}\t({: .1f},{: .1f})\t->{}\n", v.bin_index, v.bin_lower, v.bin_upper, v.value);
	}

	cout << "Export everything to JSON ... because everyone loves JSON\n";
	cout << to_json(histo, true).dump(4) << endl;
	return 0;
}