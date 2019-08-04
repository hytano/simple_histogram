#include <boost/histogram.hpp>

#include <vector>

namespace histogrammer {
	template<typename T>
	class simple_histogram {
	public:
		template<typename DT>
		struct bin_data_t {
			int bin_index;
			DT bin_lower;
			DT bin_upper;
			int value;
		};

		simple_histogram(int bins, T start, T stop) {
			boost::histogram::axis::regular<> axis(bins, start, stop);
			_histo = boost::histogram::make_histogram(axis);
		}

		void sample(T data, double weight = 1.0) {
			_histo(data, boost::histogram::weight(weight));
		}

		auto samples(bool include_overlow_bins = false) const {
			size_t smpls = 0;
			for (const auto &s : boost::histogram::indexed(_histo, include_overlow_bins ? boost::histogram::coverage::all : boost::histogram::coverage::inner))
			{
				smpls += *s;
			}
			return smpls;
		}

		auto data(bool include_overlow_bins = false) const {
			std::vector<T> rslt;
			rslt.reserve(_histo.size() + (include_overlow_bins ? 0 : -2));

			for (const auto &s : boost::histogram::indexed(_histo, include_overlow_bins ? boost::histogram::coverage::all : boost::histogram::coverage::inner))
			{
				rslt.push_back(*s);
			}
			return rslt;
		}

		auto full_data(bool include_overlow_bins = false) const {
			std::vector<bin_data_t<T>> rslt(std::max<size_t>(0, _histo.size() + (include_overlow_bins ? 0 : -2))); // crazy people will call this for 0-bin axis

			auto iter = rslt.begin();
			for (const auto &s : boost::histogram::indexed(_histo, include_overlow_bins ? boost::histogram::coverage::all : boost::histogram::coverage::inner))
			{
				iter->bin_index = s.index();
				iter->bin_lower = s.bin().lower();
				iter->bin_upper = s.bin().upper();
				iter->value = *s;
				++iter;
			}
			return rslt;
		}

		auto &histogram() { return _histo; }

	protected:
		boost::histogram::histogram<std::vector<boost::histogram::axis::regular<T>>> _histo;
	};
}; // namespace histrogrammer

