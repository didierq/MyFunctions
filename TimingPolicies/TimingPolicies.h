#ifndef __TimingPolicies_H__
#define __TimingPolicies_H__

#include "HWTiming.h"

namespace Upp {
namespace TimingPolicies_ns
{
	// =======================================================================
	//       BasicTiming
	//
	// Timing policy that saves only current timing value
	// =======================================================================
	class BasicTiming : protected HWTiming
	{
		public:
			typedef struct TimingsDataStruct
			{
				Upp::String ToString() const
				{
					Upp::String str;
					str << "Duree="<< duree << "ms";
					return str;
				}
				double duree;
			} TimingsDataStruct;

		protected:
			BasicTiming(void);

		public:
			~BasicTiming(void);

			inline void beginTiming(void)
			{
				m_Startcount = getTime();
			};

			inline void endTiming(void)
			{
				m_Stopcount = getTime();
				m_timings.duree = diff_ms(m_Startcount, m_Stopcount);
			};

			void reset(void) { m_timings.duree = 0; };

			inline double getDuration(void) const { return m_timings.duree; }
			inline const TimingsDataStruct& getTimings(void) const { return m_timings; }
			template <class STREAM> STREAM& printStats(STREAM& str) const { str << m_timings << "\n"; return str; }
		private:
			timeType m_Startcount;
			timeType m_Stopcount;
			TimingsDataStruct m_timings;
	};


	// =======================================================================
	//       MinMaxTiming
	//
	// Timing policy that saves Min, Max and current timing value
	// =======================================================================
	class MinMaxTiming : protected HWTiming
	{
		public:
			typedef struct TimingsDataStruct
			{
				Upp::String ToString() const
				{
					Upp::String str;
					str << "Max="<< max << "ms   Min=" << min << "ms   Current=" << duree << "ms";
					return str;
				}
				double duree;
				double max;
				double min;
			} TimingsDataStruct;

		protected:
			MinMaxTiming(void);
			~MinMaxTiming(void);

		public:
			inline void beginTiming(void) {	m_Startcount = getTime(); };

			inline void endTiming(void)	{
				m_Stopcount = getTime();
				m_timings.duree = diff_ms(m_Startcount, m_Stopcount);
				if( m_timings.duree > m_timings.max)       m_timings.max = m_timings.duree;
				else if( m_timings.duree < m_timings.min ) m_timings.min = m_timings.duree;
			};

			void reset(void);

			inline double getDuration(void) const { return m_timings.duree; }
			inline const TimingsDataStruct& getTimings(void) const { return m_timings; }
			template <class STREAM> STREAM& printStats(STREAM& str) const { str << m_timings << "\n"; return str; }

		private:
			timeType m_Startcount;
			timeType m_Stopcount;
			TimingsDataStruct m_timings;
	};



	// =======================================================================
	//       AverageTiming
	//
	// Timing policy that saves Average (with nbr values count) and current timing value
	// =======================================================================
	class AverageTiming : protected HWTiming
	{
		public:
			typedef struct TimingsDataStruct {
				Upp::String ToString() const
				{
					Upp::String str;
					str << "Average=" << somme / double(count) << "ms   ( count:" << count << " )    Current=" << duree << "ms";
					return str;
				}
				

				unsigned int count;
				double somme;
				double duree;
			} TimingsDataStruct;


		protected:
			AverageTiming(void);
			~AverageTiming(void);

		public:
			inline void beginTiming(void) {
				m_Startcount = getTime();
				m_timings.count++;
			};

			inline void endTiming(void) {
				m_Stopcount = getTime();
				m_timings.somme += (m_timings.duree = diff_ms(m_Startcount, m_Stopcount));
			};

			void reset(void);

			inline double getDuration(void) const { return m_timings.duree; }
			inline const TimingsDataStruct& getTimings(void) const { return m_timings; }
			template <class STREAM> STREAM& printStats(STREAM& str) const { str << m_timings << "\n"; return str; }
		private:
			timeType m_Startcount;
			timeType m_Stopcount;
			TimingsDataStruct m_timings;
	};


	// =======================================================================
	//       MinMaxAverageTiming
	//
	// Timing policy that saves Average (with nbr values count), Min, Max and current timing value
	// =======================================================================
	class MinMaxAverageTiming : protected HWTiming
	{
		public:
			typedef struct TimingsDataStruct
			{
				Upp::String ToString() const
				{
					Upp::String str;
					str << "( count:" << count << " )  \tAverage=" << somme / double(count) << "ms  \tMax="<< max << "ms  \tMin=" << min << "ms  \tCurrent="<< duree << "ms";
					return str;
				}
				double max;
				double min;
				unsigned int count;
				double somme;
				double duree;
			} TimingsDataStruct;

		protected:
			MinMaxAverageTiming(void);
			~MinMaxAverageTiming(void);

		public:
			inline void beginTiming(void) {
				m_Startcount = getTime();
				m_timings.count++;
			};

			inline void endTiming(void) {
				m_Stopcount = getTime();
				m_timings.duree  = diff_ms(m_Startcount, m_Stopcount);
				m_timings.somme += m_timings.duree;

				if( m_timings.duree  > m_timings.max)       m_timings.max = m_timings.duree;
				else if( m_timings.duree  < m_timings.min ) m_timings.min = m_timings.duree;
			};

			void reset(void);

			inline double getDuration(void) const { return m_timings.duree; }
			inline const TimingsDataStruct& getTimings(void) const { return m_timings; }
			template <class STREAM> STREAM& printStats(STREAM& str) const { str << m_timings << "\n"; return str; }
			
			
		private:
			timeType m_Startcount;
			timeType m_Stopcount;
			TimingsDataStruct m_timings;
	};


	// =======================================================================
	//       HistogramTiming
	//
	// Timing policy that saves an array[HISTO_SIZE] values.
	// Each array value represents the nbr of timing values that included between two thresholds
	// It counts the number of times the timing value was included between two threshold values
	// Very useful to eliminate out of bound measurements that are du to external factors and get the get real performance
	// =======================================================================
	template <int HISTO_SIZE=20, bool AUTO_ADJUST=false>
	class HistogramTiming : protected HWTiming
	{
		public:
			typedef struct TimingsDataStruct
			{
				
				inline Upp::String CountToString(unsigned int count) const {
					Upp::String r;
					if (count!=0) r << count;
					else r << " ";
					return r;
				}
				
				
				Upp::String ToString() const
				{
					Upp::String str;
					str << HISTO_SIZE << " pos    Range: [ " << rangeMin_ms << " , " << rangeMax_ms << " ]  (count:" << count << ")   sum: " << somme << "ms";
					str << " \t[" << thresholds[0] << "] ";
					for (int c=0; c<HISTO_SIZE; ++c) {
						str << CountToString(histogram[c]) << " \t[" << thresholds[c+1] << "] ";
					}
					return str;
				}
			    unsigned int count;
			    unsigned int histogram[HISTO_SIZE];
			    double thresholds[HISTO_SIZE+1];
			    double rangeMax_ms;
			    double rangeMin_ms;
			    double duree;
			    double somme;
    		} TimingsDataStruct;

		protected:
			HistogramTiming(void) { setRange(0,50); };
			~HistogramTiming(void)  {};

		public:
			inline void beginTiming(void) {
				m_Startcount = getTime();
			}

			inline void endTiming(void) {
				m_timings.count++;
				m_Stopcount = getTime();
				m_timings.duree = diff_ms(m_Startcount, m_Stopcount );
				m_timings.somme += m_timings.duree;
				addToHisto( m_timings.duree, AUTO_ADJUST );
			}
			
			void autoRange() {
				double min = m_timings.thresholds[0];
				double max = m_timings.thresholds[HISTO_SIZE];
				double inc = (max-min)/HISTO_SIZE;
				if (m_timings.histogram[0]!=0) {
					// If first cell Is not null ==> enlarge Histogram
					min -= inc;
					if (min<0) min=0;
				}
				if (m_timings.histogram[HISTO_SIZE-1]!=0) {
					// If last cell Is not null ==> enlarge Histogram
					max += inc;
				}
				setRange(min, max);
			}
			
			void setRange( double min, double max ) {
				reset();
				m_timings.rangeMin_ms = min;
				m_timings.rangeMax_ms = max;
				double inc = (max-min)/HISTO_SIZE;
				for (int c=0; c<HISTO_SIZE; ++c) {
					m_timings.thresholds[c] = min;
					m_timings.histogram[c] = 0;
					min += inc;
				}
				m_timings.thresholds[HISTO_SIZE] = min;
			}

			void reset(void) {
				m_timings.somme = 0;
				m_timings.duree = 0;
				m_timings.count = 0;
				for (int c=0; c<HISTO_SIZE; ++c) {
					m_timings.histogram[c] = 0;
				}
			}

			inline double getDuration(void) const { return m_timings.duree; }
			inline const TimingsDataStruct& getTimings(void) const { return m_timings; }
			template <class STREAM> STREAM& printStats(STREAM& str) const { str << m_timings << "\n"; return str; }
			
			void addToHisto( double val, bool autoAdjustRange=false )
			{
				int min = 0;
				int max = HISTO_SIZE;
			
				if (val < m_timings.thresholds[0]) {
					m_timings.thresholds[0] = val;
					++(m_timings.histogram[0]);
					if (autoAdjustRange) autoRange();
				}
				else if (m_timings.thresholds[HISTO_SIZE] < val) {
					m_timings.thresholds[HISTO_SIZE] = val;
					++(m_timings.histogram[HISTO_SIZE-1]);
					if (autoAdjustRange) autoRange();
				}
				else {
					while(min < max)
					{
						int mid = (max + min) / 2;
						if( m_timings.thresholds[mid] <= val )
							min = mid + 1;
						else
							max = mid;
					}
					++(m_timings.histogram[min-1]);
				}
				
			}
		
			
		private:
			timeType m_Startcount;
			timeType m_Stopcount;
			TimingsDataStruct m_timings;
	};

	// =======================================================================
	//       MinMaxTiming
	//
	// Timing policy that does no timing (Compiler will optimise out all the useless calls)
	// =======================================================================
	class NoTiming : protected HWTiming
	{
		protected:
			NoTiming(void) {};
			~NoTiming(void) {};

		public:
			inline void beginTiming(void) {};
			inline void endTiming(void)  {};
			inline void reset(void) {};

			template <class STREAM>
			inline STREAM& printStats(STREAM& str) const { return str; }
			inline double getDuration(void) const { return 0; }
	};

};// fin namespace : TimingPolicies_ns




// =======================================================================
//       NamedTimings<Timing_policy>
//
// Main timing class. It takes timing policy as template parameter
// =======================================================================
template <class POLICY_TYPE = TimingPolicies_ns::BasicTiming>
class NamedTimings : public POLICY_TYPE
{
	public:
		NamedTimings(const char* prefix)
		: m_prefix( prefix )
		{}
		Upp::String ToString() const {
			Upp::String str;
			typename POLICY_TYPE::TimingsDataStruct timings = POLICY_TYPE::getTimings();
			str << m_prefix << " > " << timings;
			return str;
		}

		template <class STREAM>
		STREAM& printStats(STREAM& str)	const {
			str << ToString().Begin() << "\n";
			return str;
		}

	private:
		const char* m_prefix;
};

}
#endif /*__TimingPolicies_H__*/
