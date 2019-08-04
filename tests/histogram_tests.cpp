//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <simple_histogram/simple_histogram.h>

using namespace std;
using namespace histogrammer;

SCENARIO("Sampled data can be analyzed using histograms", "[sample_count]") {
	GIVEN("a simple histogram with 5 bins") {
		simple_histogram<double> histo(5, -1.0, 1.0);
		WHEN("no data was inserted (sampled)") {
			THEN("the count of the sampled data should be 0") {
				REQUIRE(histo.samples() == 0);

				AND_WHEN("data outside the bins is sampled") {
					histo.sample(-2.0);
					THEN("the count of the sampled data should also be 0") {
						REQUIRE(histo.samples() == 0);
						
						AND_WHEN("data fitting into the bin range is sampled") {
							histo.sample(0.3);
							THEN("the count of the sampled data should be 1") {
								REQUIRE(histo.samples() == 1);
							}
						}
					}
				}
			}
		}
	}
}
