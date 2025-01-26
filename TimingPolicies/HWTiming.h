#ifndef HWTIMING_H_
#define HWTIMING_H_


// ==============================================================================================================
// ==============================================================================================================


/**
   * @brief Classe qui encapsule les fonctions de mesures temporelles pour windows
   */

#ifdef WIN32
	#include <Windows.h>
	class windowsHWTiming
	{
		protected:
		windowsHWTiming(void)
		{
			QueryPerformanceFrequency((LARGE_INTEGER*)&m_TickPerSecond);
		};
		
		public:
			typedef struct 
			{
			  signed __int64 nTicksCnt;
			} timeType;
		
			inline double diff_ms(timeType& p_start, timeType& p_end)
			{
				return (double(p_end.nTicksCnt-p_start.nTicksCnt)/double(m_TickPerSecond)*1000.);
			};
			
			inline timeType getTime(void)
			{
				timeType res;
				QueryPerformanceCounter((LARGE_INTEGER*)&res.nTicksCnt);
				return res;
			};
	
		private:
			signed __int64 m_TickPerSecond;
	};

	typedef windowsHWTiming HWTiming;

#else
	#include <time.h>
	class LinuxHWTiming {
		protected:
			LinuxHWTiming() {};
			
		public:
			typedef timespec timeType;
			
			static inline timeType getTime()
			{
				timeType t;
				clock_gettime(CLOCK_BOOTTIME, &t);
				return t;
			}
			
			// renvoie la difference en ms (milli-secondes)
			static inline double diff_ms(timeType& t1, timeType& t2)
			{
				return ((t2.tv_sec-t1.tv_sec)*1000.0 + (t2.tv_nsec-t1.tv_nsec)/1000000.0); 
			}
	};

	typedef LinuxHWTiming HWTiming;
#endif


#endif /*HWTIMING_H_*/
