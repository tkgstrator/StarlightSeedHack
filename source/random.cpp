#include "sead/random.h"
#ifdef __unix
#include <time.h>
#endif

namespace sead
{
	void Random::init()
	{
		#ifdef WIN32
		init(GetTickCount64()); // Windows
		#else
		init(time(NULL)); // Linux
		#endif

	}

	void Random::init(u32 seed)
	{
		mSeed1 = 0x6C078965 * (seed   ^ (seed   >> 30)) + 1;
		mSeed2 = 0x6C078965 * (mSeed1 ^ (mSeed1 >> 30)) + 2;
		mSeed3 = 0x6C078965 * (mSeed2 ^ (mSeed2 >> 30)) + 3;
		mSeed4 = 0x6C078965 * (mSeed3 ^ (mSeed3 >> 30)) + 4;
	}
	
	void Random::init(u32 seed1, u32 seed2, u32 seed3, u32 seed4)
	{
		if ((seed1 | seed2 | seed3 | seed4) == 0) // seeds must not be all zero.
		{
			seed1 = 1;
			seed2 = 0x6C078967;
			seed3 = 0x714ACB41;
			seed4 = 0x48077044;
		}

		mSeed1 = seed1;
		mSeed2 = seed2;
		mSeed3 = seed3;
		mSeed4 = seed4;
	}

	u32 Random::getU32()
	{
		u32 n = mSeed1 ^ (mSeed1 << 11);

		mSeed1 = mSeed2;
		mSeed2 = mSeed3;
		mSeed3 = mSeed4;
		mSeed4 = n ^ (n >> 8) ^ mSeed4 ^ (mSeed4 >> 19);

		return mSeed4;
	}

	u64 Random::getU64()
	{
		u32 n1 = mSeed1 ^ (mSeed1 << 11);
		u32 n2 = mSeed2;
		u32 n3 = n1 ^ (n1 >> 8) ^ mSeed4;

		mSeed1 = mSeed3;
		mSeed2 = mSeed4;
		mSeed3 = n3 ^ (mSeed4 >> 19);
		mSeed4 = n2 ^ (n2 << 11) ^ ((n2 ^ (n2 << 11)) >> 8) ^ mSeed3 ^ (n3 >> 19);

		return ((u64)mSeed3 << 32) | mSeed4;
	}

	void Random::getContext(u32 *seed1, u32 *seed2, u32 *seed3, u32 *seed4) const
	{
		*seed1 = mSeed1;
		*seed2 = mSeed2;
		*seed3 = mSeed3;
		*seed4 = mSeed4;
	}
}