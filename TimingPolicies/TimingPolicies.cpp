#include <Core/Core.h>
#include "TimingPolicies.h"

namespace Upp {
namespace TimingPolicies_ns
{
	/////////////////////////////////////////////
	///////////////// BasicTiming ////////////////
	/////////////////////////////////////////////	
	BasicTiming::BasicTiming(void)
	{
		m_timings.duree = 0;
	};
	BasicTiming::~BasicTiming(void) {};

	/////////////////////////////////////////////
	///////////////// MinMaxCalc ////////////////
	/////////////////////////////////////////////	
	MinMaxTiming::MinMaxTiming(void)
	{
		reset();
	}

	MinMaxTiming::~MinMaxTiming(void)
	{
	}

	void MinMaxTiming::reset(void) 
	{
		m_timings.max = 0; // ms
		m_timings.min = 10E20; // ms
		m_timings.duree = 0;
	}
	
	/////////////////////////////////////////////
	///////////////// AverageTiming ////////////////
	/////////////////////////////////////////////
	AverageTiming::AverageTiming(void)
	{
		reset();
	}
	
	AverageTiming::~AverageTiming()
	{
	}

	void AverageTiming::reset(void) 
	{
		m_timings.count = 0;
		m_timings.somme = 0.;
		m_timings.duree = 0;
	}
	
	/////////////////////////////////////////////
	///////////////// AverageTiming ////////////////
	/////////////////////////////////////////////	
	MinMaxAverageTiming::MinMaxAverageTiming(void)
	{
		reset();
	}
	
	MinMaxAverageTiming::~MinMaxAverageTiming()
	{
	}

	void MinMaxAverageTiming::reset(void)
	{
		m_timings.max = 0; // ms
		m_timings.min = 10E20; // ms
		m_timings.count = 0;
		m_timings.somme = 0.;
		m_timings.duree = 0;
	}
}
}
