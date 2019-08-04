#ifndef __JSON_IO_H__
#define __JSON_IO_H__

#include <nlohmann/json.hpp>
#include "../simple_histogram.h"

namespace histogrammer {
	template<typename T>
	nlohmann::json to_json(const simple_histogram<T> &h, bool include_overflow_bins = false) {
		nlohmann::json json;
		auto data = h.full_data(include_overflow_bins);
		for (auto &d : data) {
			nlohmann::json bin;
			bin["lower"] = d.bin_lower;
			bin["upper"] = d.bin_upper;
			json["bins"].push_back(bin);
			json["values"].push_back(d.value);
		}
		return json;
	}
} //histogrammer

#endif /*__JSON_IO_H__*/
