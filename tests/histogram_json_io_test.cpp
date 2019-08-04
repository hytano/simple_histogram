#include "catch.hpp"

#include <simple_histogram/simple_histogram.h>
#include <simple_histogram/utilities/json_io.h>

using namespace std;
using namespace histogrammer;

SCENARIO("Histograms can be serialized into JSON objects", "[json]") {
	GIVEN("a simple histogram with some bins and data") {
		const int bin_count = 4;
		simple_histogram<double> h(bin_count, -1.0, 1.0);
		h.sample(0.5);
		h.sample(0.312);
		h.sample(-0.44);

		WHEN("exporting to JSON") {
			auto j = to_json(h);
			THEN("the output shall be a json object") {
				REQUIRE(j.is_object());
			}
			THEN("the output shall have the bin config in the \"bins\" array with the same size as the bin count") {
				REQUIRE(j.find("bins") != j.end());
				REQUIRE(j["bins"].is_array());
				REQUIRE(j["bins"].size() == bin_count);
			}
			THEN("the output shall have the bins data in the \"values\" array with the same size as the bin count") {
				REQUIRE(j.find("values") != j.end());
				REQUIRE(j["values"].is_array());
				REQUIRE(j["values"].size() == bin_count);
			}
		}
	}
}

