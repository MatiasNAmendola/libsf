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
	struct SBignumSlot
	{
		bool	used;		// Is this slot used?
		CBignum	bn;			// The bignum entry
	};
	SBignumSlot bnArray[2048];



BOOL APIENTRY DllMain(	HMODULE	hModule,
						DWORD	ul_reason_for_call,
						LPVOID	lpReserved	)
{
	u32 lnI;


	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			// Initialize our slots for bignums
			for (lnI = 0; lnI < sizeof(bnArray) / sizeof(CBignum); lnI++)
			{
				// Initialize
				bnArray[lnI].used = false;
				bnArray[lnI].bn.Init();
			}
			break;

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

bool isValid(s32 tnId)
{
	return(tnId < sizeof(bnArray) / sizeof(SBignumSlot) && bnArray[tnId].used);
}

s32 bn_init(s32 tnId, u32 tnBits)
{
	u32 lnI, lnDigits;

	// Determine the number of significant digits
	lnDigits = (s32)((f64)tnBits / 3.33333333333333) + 2;

	// See what we're adding
	if (tnId < 0)
	{
		// They're request a new slot
		for (lnI = 0; lnI < sizeof(bnArray) / sizeof(SBignumSlot); lnI++)
		{
			if (!bnArray[lnI].used)
			{
				// We've found an empty slot
				bnArray[lnI].used	= true;
				bnArray[lnI].bn.Init();
				bnArray[lnI].bn.fp.precision(lnDigits);
				return(lnI);
			}
		}
		// If we get here, failure
		return(-1);

	} else if (isValid(tnId)) {
		// Re-initializing the indicated slot
		bnArray[tnId].bn.Init();
		bnArray[tnId].bn.fp.precision(lnDigits);
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
		bnArray[tnId].used = false;
		return(1);
	}
	return(0);
}

s32 bn_cmp(s32 tnIdLeft, s32 tnIdRight)
{
	if (isValid(tnIdLeft) && isValid(tnIdRight))
	{
		return(bnArray[tnIdLeft].bn.Cmp(bnArray[tnIdRight].bn));
	}
	return(-1);
}

s32 bn_cmp_delta(s32 tnIdTmp, s32 tnIdLeft, s32 tnIdRight, s32 tnIdDelta)
{
	if (isValid(tnIdTmp) && isValid(tnIdLeft) && isValid(tnIdRight) && isValid(tnIdDelta))
	{
		return(bnArray[tnIdLeft].bn.CmpDelta(bnArray[tnIdTmp].bn, bnArray[tnIdRight].bn, bnArray[tnIdDelta].bn));
	}
	return(-1);
}

u32 bn_set(s32 tnId, s32 tnIdValue)
{
	if (isValid(tnId) && isValid(tnIdValue))
	{
		bnArray[tnId].bn.Set(bnArray[tnIdValue].bn);
		return(1);
	}
	return(0);
}

u32 bn_set_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_set_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_set_text(s32 tnId, s8* tcValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set(tcValue);
		return(1);
	}
	return(0);
}

u32 bn_set0(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set0();
		return(1);
	}
	return(0);
}

u32 bn_set1(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set1();
		return(1);
	}
	return(0);
}

u32 bn_set2(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set2();
		return(1);
	}
	return(0);
}

u32 bn_set3(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set3();
		return(1);
	}
	return(0);
}

u32 bn_set4(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set4();
		return(1);
	}
	return(0);
}

u32 bn_setpi(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Setpi();
		return(1);
	}
	return(0);
}

u32 bn_set2pi(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set2pi();
		return(1);
	}
	return(0);
}

u32 bn_setpi2(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Setpi2();
		return(1);
	}
	return(0);
}

u32 bn_setpi4(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Setpi4();
		return(1);
	}
	return(0);
}

u32 bn_set3pi2(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Set3pi2();
		return(1);
	}
	return(0);
}

u32 bn_set_golden_ratio(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Setgr();
		return(1);
	}
	return(0);
}

u32 bn_set_ln2(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.SetLn2();
		return(1);
	}
	return(0);
}

u32 bn_set_ln10(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.SetLn10();
		return(1);
	}
	return(0);
}

u32 bn_abs(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Abs();
		return(1);
	}
	return(0);
}

u32 bn_min(s32 tnIdDst, s32 tnIdSrc1, s32 tnIdSrc2)
{
	if (isValid(tnIdDst) && isValid(tnIdSrc1) && isValid(tnIdSrc2))
	{
		bnArray[tnIdDst].bn.Min2(bnArray[tnIdSrc1].bn, bnArray[tnIdSrc2].bn);
		return(1);
	}
	return(0);
}

u32 bn_max(s32 tnIdDst, s32 tnIdSrc1, s32 tnIdSrc2)
{
	if (isValid(tnIdDst) && isValid(tnIdSrc1) && isValid(tnIdSrc2))
	{
		bnArray[tnIdDst].bn.Max2(bnArray[tnIdSrc1].bn, bnArray[tnIdSrc2].bn);
		return(1);
	}
	return(0);
}

u32 bn_sqrt(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Sqrt();
		return(1);
	}
	return(0);
}

u32 bn_square(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Square();
		return(1);
	}
	return(0);
}

u32 bn_ytox(s32 tnIdY, s32 tnIdX)
{
	if (isValid(tnIdY) && isValid(tnIdX))
	{
		bnArray[tnIdY].bn.YToX(bnArray[tnIdX].bn);
		return(1);
	}
	return(0);
}

s32 bn_to_s32(s32 tnId)
{
	if (isValid(tnId))
	{
		return(bnArray[tnId].bn.tos32());
		return(1);
	}
	return(0);
}

f64 bn_to_f64(s32 tnId)
{
	if (isValid(tnId))
	{
		return(bnArray[tnId].bn.tof64());
		return(1);
	}
	return(0);
}

u32 bn_to_text(s32 tnId, s8* tcValue, u32 tnLength)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.toText(tcValue, tnLength);
		return(1);
	}
	return(0);
}

u32 bn_neg(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Neg();
		return(1);
	}
	return(0);
}

u32 bn_mod(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bnArray[tnId1].bn.Mod(bnArray[tnId2].bn);
		return(1);
	}
	return(0);
}

u32 bn_mul(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bnArray[tnId1].bn.Mul(bnArray[tnId2].bn);
		return(1);
	}
	return(0);
}

u32 bn_mul_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Mul(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_mul_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Mul(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_div(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bnArray[tnId1].bn.Div(bnArray[tnId2].bn);
		return(1);
	}
	return(0);
}

u32 bn_div_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Div(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_div_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Div(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_add(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bnArray[tnId1].bn.Add(bnArray[tnId2].bn);
		return(1);
	}
	return(0);
}

u32 bn_add_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Add(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_add_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Add(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_sub(s32 tnId1, s32 tnId2)
{
	if (isValid(tnId1) && isValid(tnId2))
	{
		bnArray[tnId1].bn.Sub(bnArray[tnId2].bn);
	}
	return(0);
}

u32 bn_sub_s32(s32 tnId, s32 tnValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Sub(tnValue);
		return(1);
	}
	return(0);
}

u32 bn_sub_f64(s32 tnId, f64 tfValue)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Sub(tfValue);
		return(1);
	}
	return(0);
}

u32 bn_cos(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Cos();
		return(1);
	}
	return(0);
}

u32 bn_sin(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Sin();
		return(1);
	}
	return(0);
}

u32 bn_tan(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Tan();
		return(1);
	}
	return(0);
}

u32 bn_acos(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Acos();
		return(1);
	}
	return(0);
}

u32 bn_asin(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Asin();
		return(1);
	}
	return(0);
}

u32 bn_atan(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Atan();
		return(1);
	}
	return(0);
}

u32 bn_atan2(s32 tnIdDst, s32 tnIdY, s32 tnIdX)
{
	if (isValid(tnIdDst) && isValid(tnIdY) && isValid(tnIdX))
	{
		bnArray[tnIdDst].bn.Atan2(bnArray[tnIdY].bn, bnArray[tnIdX].bn);
		return(1);
	}
	return(0);
}

u32 bn_cot(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Cot();
		return(1);
	}
	return(0);
}

u32 bn_csc(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Csc();
		return(1);
	}
	return(0);
}

u32 bn_sec(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Sec();
		return(1);
	}
	return(0);
}

u32 bn_log(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Log();
		return(1);
	}
	return(0);
}

u32 bn_log2(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Log2();
		return(1);
	}
	return(0);
}

u32 bn_log10(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Log10();
		return(1);
	}
	return(0);
}

u32 bn_cosh(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Cosh();
		return(1);
	}
	return(0);
}

u32 bn_sinh(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Sinh();
		return(1);
	}
	return(0);
}

u32 bn_tanh(s32 tnId)
{
	if (isValid(tnId))
	{
		bnArray[tnId].bn.Tanh();
		return(1);
	}
	return(0);
}
