//////////
//
// bignum.cpp
//
//////
//
//




#include "bignum.h"
#include "cbignum.h"
#include "cbignum.cpp"

//////////
// Allocate for up to 2048 bignums
//////
	struct SSlotCmpfr
	{
		bool	used;		// Is this slot used?
		CBignum	bn;			// The cmpfr entry
	};
	SSlotCmpfr bf[2048];



BOOL APIENTRY DllMain(	HMODULE	hModule,
						DWORD	ul_reason_for_call,
						LPVOID	lpReserved	)
{
	u32 lnI;


	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
			// Initialize our slots for bignums
			for (lnI = 0; lnI < sizeof(bf) / sizeof(CBignum); lnI++)
			{
				// Initialize
				bf[lnI].used = false;
				bf[lnI].bn.Init();
			}
			break;

		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

bool isValid(s32 tnId)
{
	return(tnId < sizeof(bf) / sizeof(SSlotCmpfr) && bf[tnId].used);
}

s32 bn_init(s32 tnId, u32 tnBits)
{
	u32 lnI;

	if (tnId < 0)
	{
		// They're request a new slot
		for (lnI = 0; lnI < sizeof(bf) / sizeof(SSlotCmpfr); lnI++)
		{
			if (!bf[lnI].used)
			{
				// We've found an empty slot
				bf[lnI].used	= true;
				bf[lnI].bn.Init();
// TODO:  We need to indicate the precision here (and below)
//				bf[lnI].bn.p	= tnBits;
				return(lnI);
			}
		}
		// If we get here, failure
		return(-1);

	} else if (isValid(tnId)) {
		// Re-initializing the indicated slot
		bf[tnId].bn.Init();
//		bf[tnId].bn.p = tnBits;
		return(tnId);

	} else {
		// Failure
		return(-1);
	}
}

s32 bn_new(s32 tnBits)
{
	return(bn_init(-1, tnBits));
}

s32 bn_free(s32 tnId)
{
	if (isValid(tnId))
	{
		// Free the slot and mark it not used
		bf[tnId].used = false;
		return(1);
	}
	return(0);
}

s32 bn_cmp(s32 tnIdLeft, s32 tnIdRight)
{
	if (isValid(tnIdLeft) && isValid(tnIdRight))
	{
		return(bf[tnIdLeft].bn.Cmp(bf[tnIdRight].bn));
	}
	return(-1);
}

s32 bn_cmp_delta(s32 tnIdTmp, s32 tnIdLeft, s32 tnIdRight, f64 delta)
{
	if (isValid(tnIdTmp) && isValid(tnIdLeft) && isValid(tnIdRight))
	{
		return(bf[tnIdLeft].bn.CmpDelta(bf[tnIdTmp].bn, bf[tnIdRight].bn, delta));
	}
	return(-1);
}

s32 bn_is_nan(s32 tnId)
{
	if (isValid(tnId))
	{
		return(bf[tnId].bn.IsNan());
	}
	return(true);
}

s32 bn_is_inf(s32 tnId)
{
	if (isValid(tnId))
	{
		return(bf[tnId].bn.IsInf());
	}
	return(true);
}

s32 bn_random(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Random();
		return(1);
	}
	return(0);
}

u32 bn_set(s32 tnId, s32 tnIdValue)
{
	if (isValid(tnId) && isValid(tnIdValue))
	{
		bf[tnId].bn.Set(bf[tnIdValue].bn);
		return(1);
	}
	return(0);
}

u32 bn_set_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_set_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_set_text(s32 tnId, s8* tcValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set(tcValue);
		return(1);
	}
	return(0);
}

u32 bn_set0(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set0();
		return(1);
	}
	return(0);
}

u32 bn_set1(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set1();
		return(1);
	}
	return(0);
}

u32 bn_set2(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set2();
		return(1);
	}
	return(0);
}

u32 bn_set3(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set3();
		return(1);
	}
	return(0);
}

u32 bn_set4(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set4();
		return(1);
	}
	return(0);
}

u32 bn_setpi(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Setpi();
		return(1);
	}
	return(0);
}

u32 bn_set2pi(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set2pi();
		return(1);
	}
	return(0);
}

u32 bn_setpi2(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Setpi2();
		return(1);
	}
	return(0);
}

u32 bn_setpi4(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Setpi4();
		return(1);
	}
	return(0);
}

u32 bn_set3pi2(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Set3pi2();
		return(1);
	}
	return(0);
}

u32 bn_set_golden_ratio(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Setgr();
		return(1);
	}
	return(0);
}

u32 bn_abs(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Abs();
		return(1);
	}
	return(0);
}

u32 bn_min(s32 tnIdDst, s32 tnIdSrc1, s32 tnIdSrc2)
{
	if (isValid(tnIdDst) && isValid(tnIdSrc1) && isValid(tnIdSrc2))
	{
		bf[tnIdDst].bn.Min2(bf[tnIdSrc1].bn, bf[tnIdSrc2].bn);
		return(1);
	}
	return(0);
}

u32 bn_max(s32 tnIdDst, s32 tnIdSrc1, s32 tnIdSrc2)
{
	if (isValid(tnIdDst) && isValid(tnIdSrc1) && isValid(tnIdSrc2))
	{
		bf[tnIdDst].bn.Max2(bf[tnIdSrc1].bn, bf[tnIdSrc2].bn);
		return(1);
	}
	return(0);
}

u32 bn_sqrt(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Sqrt();
		return(1);
	}
	return(0);
}

u32 bn_square(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Square();
		return(1);
	}
	return(0);
}

s32 bn_to_s32(s32 tnId)
{
	if (isValid(tnId))
	{
		return(bf[tnId].bn.tos32());
		return(1);
	}
	return(0);
}

f64 bn_to_f64(s32 tnId)
{
	if (isValid(tnId))
	{
		return(bf[tnId].bn.tof64());
		return(1);
	}
	return(0);
}

u32 bn_to_text(s32 tnId, s8* tcValue, u32 tnLength)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.toText(tcValue, tnLength);
		return(1);
	}
	return(0);
}

u32 bn_neg(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Neg();
		return(1);
	}
	return(0);
}

u32 bn_mod(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bf[tnId1].bn.Mod2(bf[tnId2].bn);
		return(1);
	}
	return(0);
}

u32 bn_mul(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bf[tnId1].bn.Mul(bf[tnId2].bn);
		return(1);
	}
	return(0);
}

u32 bn_mul_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Mul(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_mul_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Mul(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_div(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bf[tnId1].bn.Div(bf[tnId2].bn);
		return(1);
	}
	return(0);
}

u32 bn_div_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Div(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_div_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Div(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_add(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bf[tnId1].bn.Add(bf[tnId2].bn);
		return(1);
	}
	return(0);
}

u32 bn_add_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Add(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_add_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Add(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_sub(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bf[tnId1].bn.Sub(bf[tnId2].bn);
	}
	return(0);
}

u32 bn_sub_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Sub(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_sub_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Sub(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_cos(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Cos();
		return(1);
	}
	return(0);
}

u32 bn_sin(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Sin();
		return(1);
	}
	return(0);
}

u32 bn_tan(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Tan();
		return(1);
	}
	return(0);
}

u32 bn_acos(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Acos();
		return(1);
	}
	return(0);
}

u32 bn_asin(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Asin();
		return(1);
	}
	return(0);
}

u32 bn_atan(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Atan();
		return(1);
	}
	return(0);
}

u32 bn_atan2(s32 tnIdDst, s32 tnIdY, s32 tnIdX)
{
	if (isValid(tnIdDst) && isValid(tnIdY) && isValid(tnIdX))
	{
		bf[tnIdDst].bn.Atan2(bf[tnIdY].bn, bf[tnIdX].bn);
		return(1);
	}
	return(0);
}

u32 bn_cot(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Cot();
		return(1);
	}
	return(0);
}

u32 bn_csc(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Csc();
		return(1);
	}
	return(0);
}

u32 bn_sec(s32 tnId)
{
	if (isValid(tnId))
	{
		bf[tnId].bn.Sec();
		return(1);
	}
	return(0);
}
