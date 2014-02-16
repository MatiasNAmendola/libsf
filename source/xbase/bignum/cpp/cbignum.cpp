//////////
//
// cmpfr.cpp
//
/////
//
//




// This class encapsulates the functions above in a very straight-forward form
CBignum::CBignum()
{
}

CBignum::~CBignum()
{
}

void CBignum::operator=(CBignum& right)			{	fp	= right.fp;	}

void CBignum::Init(void)						{	fp = 0.0;	}

int CBignum::Cmp(CBignum& bn)					{	return(0);	}
int CBignum::Cmp(f64 d)							{	return(0);	}
int CBignum::Cmp(long int i)					{	return(0);	}

int CBignum::CmpDelta(CBignum& t, CBignum& bn, f64 delta)	{	return(0);	}
int CBignum::CmpDelta(CBignum& t, f64 d, f64 delta)			{	return(0);	}

bool CBignum::IsNan(void)						{	return(false);	}
bool CBignum::IsNan(CBignum& bn1)				{	return(false);	}

bool CBignum::IsInf(void)						{	return(false);	}
bool CBignum::IsInf(CBignum& bn1)				{	return(false);	}

void CBignum::Random(void)						{}

void CBignum::Set(CBignum& bn)					{}
void CBignum::Set(f64 d)						{}
void CBignum::Set(s8* s)						{}
// Common constants by member function
void CBignum::Set0(void)						{}
void CBignum::Set1(void)						{}
void CBignum::Set2(void)						{}
void CBignum::Set3(void)						{}
void CBignum::Set4(void)						{}
void CBignum::Setpi(void)						{}
void CBignum::Set2pi(void)						{}
void CBignum::Setpi2(void)						{}
void CBignum::Setpi4(void)						{}
void CBignum::Set3pi2(void)						{}
void CBignum::Setgr(void)						{}

void CBignum::Abs(void)							{}
void CBignum::Min(CBignum& bn1)					{}
void CBignum::Min2(CBignum& bn1, CBignum& bn2)	{}
void CBignum::Min3(CBignum& bn1, CBignum& bn2, CBignum& bn3)		{}

void CBignum::Max(CBignum& bn1)					{}
void CBignum::Max2(CBignum& bn1, CBignum& bn2)	{}
void CBignum::Max3(CBignum& bn1, CBignum& bn2, CBignum& bn3)		{}

void CBignum::Sqrt(void)						{}
void CBignum::Sqrt(CBignum& bn1)					{}

s32 CBignum::tos32(void)						{	return(0);	}
f32 CBignum::tof32(void)						{	return(0.0f);	}
f64 CBignum::tof64(void)						{	return(0.0);	}

u32 CBignum::toText(s8* tcValue, u32 tnLength)
{
	std::string s;
	s8 format[32];

	s = fp.toString();
// TODO:  Test how long s is, and if long enough copy, if not copy what we can and return the length
	return(0);
}

void CBignum::Neg(void)							{}
void CBignum::Neg(CBignum& bn1)					{}

void CBignum::Mod2(CBignum& bn1)				{}
void CBignum::Mod2(CBignum& bn1, CBignum& bn2)	{}

void CBignum::Mul(f64 d)						{}
void CBignum::Mul(CBignum& bn1)					{}
void CBignum::Mul2(f64 d1, CBignum& bn2)		{}
void CBignum::Mul2(CBignum& bn1, f64 d2)		{}
void CBignum::Mul2(CBignum& bn1, CBignum& bn2)	{}
void CBignum::Mul3(CBignum& bn1, CBignum& bn2, CBignum& bn3)		{}
void CBignum::Mul4(CBignum& bn1, CBignum& bn2, CBignum& bn3, CBignum& c4)		{}

void CBignum::Div(f64 d1)						{}
void CBignum::Div(CBignum& bn1)					{}
void CBignum::Div2(f64 d1, CBignum& bn2)		{}
void CBignum::Div2(CBignum& bn1, f64 d2)		{}
void CBignum::Div2(CBignum& bn1, CBignum& bn2)	{}
void CBignum::Div3(CBignum& bn1, CBignum& bn2, CBignum& bn3)		{}

void CBignum::Add(f64 d1)						{}
void CBignum::Add(CBignum& bn1)					{}
void CBignum::Add2(f64 d1, CBignum& bn2)		{}
void CBignum::Add2(CBignum& bn1, f64 d2)		{}
void CBignum::Add2(CBignum& bn1, CBignum& bn2)	{}
void CBignum::Add3(CBignum& bn1, CBignum& bn2, CBignum& bn3)		{}

void CBignum::Sub(f64 d1)						{}
void CBignum::Sub(CBignum& bn1)					{}
void CBignum::Sub2(f64 d1, CBignum& bn2)		{}
void CBignum::Sub2(CBignum& bn1, f64 d2)			{}
void CBignum::Sub2(CBignum& bn1, CBignum& bn2)	{}
void CBignum::Sub3(CBignum& bn1, CBignum& bn2, CBignum& bn3)		{}

void CBignum::Cos(void)							{}
void CBignum::Cos(CBignum& bn1)					{}

void CBignum::Sin(void)							{}
void CBignum::Sin(CBignum& bn1)					{}

void CBignum::Tan(void)							{}
void CBignum::Tan(CBignum& bn1)					{}

void CBignum::Acos(void)						{}
void CBignum::Acos(CBignum& bn1)				{}

void CBignum::Asin(void)						{}
void CBignum::Asin(CBignum& bn1)				{}

void CBignum::Atan(void)						{}
void CBignum::Atan(CBignum& bn1)				{}

void CBignum::Atan2(CBignum& y, CBignum& x)		{}

void CBignum::Cot(void)							{}
void CBignum::Cot(CBignum& bn1)					{}

void CBignum::Csc(void)							{}
void CBignum::Csc(CBignum& bn1)					{}

void CBignum::Sec(void)							{}
void CBignum::Sec(CBignum& bn1)					{}

void CBignum::Square(void)						{ fp = fp * fp;	}
void CBignum::Square(f64 d1)					{ fp = d1 * d1;	}
void CBignum::Square(CBignum& bn1)				{ fp = bn1.fp * bn1.fp; }

void CBignum::Cos(f64 d1)						{ fp = cos(d1);	}
void CBignum::Sin(f64 d1)						{ fp = sin(d1);	}
void CBignum::Tan(f64 d1)						{ fp = tan(d1);	}
void CBignum::Acos(f64 d1)						{ fp = acos(d1);	}
void CBignum::Asin(f64 d1)						{ fp = asin(d1);	}
void CBignum::Atan(f64 d1)						{ fp = atan(d1);	}
void CBignum::Atan2(f64 y, f64 x)				{ fp = atan2(y, x);	}
