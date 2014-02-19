//////////
//
// cbignum.cpp
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

int CBignum::Cmp(CBignum& bn)
{
	if (fp < bn.fp)			return(-1);		// fp is less than
	else if (fp == bn.fp)	return(0);		// fp is equal
	else					return(1);		// fp is greater than
}

int CBignum::CmpDelta(CBignum& t, CBignum& bn, CBignum& d)
{
	t.fp = fp - bn.fp;
	if (fabs(t.fp) <= d.fp)
		return(0);	// fp is equal

	// If we get here, it's not within the delta, so do a literal repair
	return(Cmp(bn));
}

void CBignum::Set(CBignum& bn)					{	fp = bn.fp;	}
void CBignum::Set(f64 d)						{	fp = d;	}
void CBignum::Set(s8* s)						{	fp = s; }

// Common constants
void CBignum::Set0(void)						{	fp = 0.0;	}
void CBignum::Set1(void)						{	fp = 1.0;	}
void CBignum::Set2(void)						{	fp = 2.0;	}
void CBignum::Set3(void)						{	fp = 3.0;	}
void CBignum::Set4(void)						{	fp = 4.0;	}
void CBignum::Setpi(void)						{	fp = getPi();	}
void CBignum::Set2pi(void)						{	fp = getPi(); fp *= 2.0;	}
void CBignum::Setpi2(void)						{	fp = getPi(); fp /= 2.0;	}
void CBignum::Setpi4(void)						{	fp = getPi(); fp /= 4.0;	}
void CBignum::Set3pi2(void)						{	fp = getPi(); fp *= 3.0; fp /= 2.0;	}
// golden ratio = (1 + sqrt(5)) / 2
void CBignum::Setgr(void)						{	fp = 5.0; fp = sqrt(fp); fp += 1.0; fp /= 2.0;	}
void CBignum::SetLn2(void)						{	fp = _LN2; }
void CBignum::SetLn10(void)						{	fp = _LN10; }

void CBignum::Abs(void)							{	fp = fabs(fp);	}
void CBignum::Min(CBignum& bn1)					{	fp = min(fp, bn1.fp);	}
void CBignum::Min2(CBignum& bn1, CBignum& bn2)	{	fp = min(bn1.fp, bn2.fp);	}
void CBignum::Min3(CBignum& bn1, CBignum& bn2, CBignum& bn3)	{	fp = min(min(bn1.fp, bn2.fp), bn3.fp);	}

void CBignum::Max(CBignum& bn1)					{	fp = max(fp, bn1.fp);	}
void CBignum::Max2(CBignum& bn1, CBignum& bn2)	{	fp = max(bn1.fp, bn2.fp);	}
void CBignum::Max3(CBignum& bn1, CBignum& bn2, CBignum& bn3)	{	fp = max(max(bn1.fp, bn2.fp), bn3.fp);	}

void CBignum::Sqrt(void)						{	fp = sqrt(fp);	}
void CBignum::Sqrt(CBignum& bn1)				{	fp = sqrt(bn1.fp);	}

s32 CBignum::tos32(void)						{	return((s32)fp);	}
f32 CBignum::tof32(void)						{	return((f32)fp);	}
f64 CBignum::tof64(void)						{	return((f64)fp);	}

u32 CBignum::toText(s8* tcValue, u32 tnLength)
{
	std::string s;

	s = fp.toString();
	memset(tcValue, 32, tnLength);
	memcpy(tcValue, s.c_str(), min(tnLength, s.size()));
	return(s.size());
}

void CBignum::Neg(void)							{	fp = -fp;	}
void CBignum::Neg(CBignum& bn1)					{	fp = -bn1.fp;	}

void CBignum::Mod(CBignum& bn1)					{	fp = fmod(fp, bn1.fp);	}

void CBignum::Mul(f64 d)						{	fp *= d;	}
void CBignum::Mul(CBignum& bn1)					{	fp *= bn1.fp;	}
void CBignum::Mul2(CBignum& bn1, CBignum& bn2)	{	fp = bn1.fp * bn2.fp;	}
void CBignum::Mul3(CBignum& bn1, CBignum& bn2, CBignum& bn3)	{	fp = bn1.fp * bn2.fp * bn3.fp;	}
void CBignum::Mul4(CBignum& bn1, CBignum& bn2, CBignum& bn3, CBignum& bn4)	{	fp = bn1.fp * bn2.fp * bn3.fp * bn4.fp;	}

void CBignum::Div(f64 d)						{	fp /= d;	}
void CBignum::Div(CBignum& bn1)					{	fp /= bn1.fp;	}
void CBignum::Div2(CBignum& bn1, CBignum& bn2)	{	fp = bn1.fp / bn2.fp;	}
void CBignum::Div3(CBignum& bn1, CBignum& bn2, CBignum& bn3)	{	fp = (bn1.fp / bn2.fp) / bn3.fp;	}
void CBignum::Div4(CBignum& bn1, CBignum& bn2, CBignum& bn3, CBignum& bn4)	{	fp = ((bn1.fp / bn2.fp) / bn3.fp) / bn4.fp;	}

void CBignum::Add(f64 d)						{	fp += d;	}
void CBignum::Add(CBignum& bn1)					{	fp += bn1.fp;	}
void CBignum::Add2(CBignum& bn1, CBignum& bn2)	{	fp = bn1.fp + bn2.fp;	}
void CBignum::Add3(CBignum& bn1, CBignum& bn2, CBignum& bn3)	{	fp = bn1.fp + bn2.fp + bn3.fp;	}
void CBignum::Add4(CBignum& bn1, CBignum& bn2, CBignum& bn3, CBignum& bn4)	{	fp = bn1.fp + bn2.fp + bn3.fp + bn4.fp;	}

void CBignum::Sub(f64 d)						{	fp -= d;	}
void CBignum::Sub(CBignum& bn1)					{	fp -= bn1.fp;	}
void CBignum::Sub2(CBignum& bn1, CBignum& bn2)	{	fp = bn1.fp - bn2.fp;	}
void CBignum::Sub3(CBignum& bn1, CBignum& bn2, CBignum& bn3)	{	fp = bn1.fp - bn2.fp - bn3.fp;	}
void CBignum::Sub4(CBignum& bn1, CBignum& bn2, CBignum& bn3, CBignum& bn4)	{	fp = bn1.fp - bn2.fp - bn3.fp - bn4.fp;	}

void CBignum::Cos(void)							{	fp = cos(fp);	}
void CBignum::Cos(CBignum& bn1)					{	fp = cos(bn1.fp);	}

void CBignum::Sin(void)							{	fp = sin(fp);	}
void CBignum::Sin(CBignum& bn1)					{	fp = sin(bn1.fp);	}

void CBignum::Tan(void)							{	fp = tan(fp);	}
void CBignum::Tan(CBignum& bn1)					{	fp = tan(bn1.fp);	}

void CBignum::Acos(void)						{	fp = acos(fp);	}
void CBignum::Acos(CBignum& bn1)				{	fp = acos(bn1.fp);	}

void CBignum::Asin(void)						{	fp = asin(fp);	}
void CBignum::Asin(CBignum& bn1)				{	fp = asin(bn1.fp);	}

void CBignum::Atan(void)						{	fp = atan(fp);	}
void CBignum::Atan(CBignum& bn1)				{	fp = atan(bn1.fp);	}

void CBignum::Atan2(CBignum& y, CBignum& x)		{	fp = atan2(y.fp, x.fp);	}

void CBignum::Cot(void)							{	float_precision t;	t.precision(fp.precision()); t = 1.0; fp = t / tan(fp);	}
void CBignum::Cot(CBignum& bn1)					{	float_precision t;	t.precision(fp.precision()); t = 1.0; fp = t / tan(bn1.fp);	}

void CBignum::Csc(void)							{	float_precision t;	t.precision(fp.precision()); t = 1.0; fp = t / sin(fp);	}
void CBignum::Csc(CBignum& bn1)					{	float_precision t;	t.precision(fp.precision()); t = 1.0; fp = t / sin(bn1.fp);	}

void CBignum::Sec(void)							{	float_precision t;	t.precision(fp.precision()); t = 1.0; fp = t / cos(fp);	}
void CBignum::Sec(CBignum& bn1)					{	float_precision t;	t.precision(fp.precision()); t = 1.0; fp = t / cos(bn1.fp);	}

void CBignum::Cosh(void)						{	fp = cosh(fp);	}
void CBignum::Cosh(CBignum& bn1)				{	fp = cosh(bn1.fp);	}

void CBignum::Sinh(void)						{	fp = sinh(fp);	}
void CBignum::Sinh(CBignum& bn1)				{	fp = sinh(bn1.fp);	}

void CBignum::Tanh(void)						{	fp = tanh(fp);	}
void CBignum::Tanh(CBignum& bn1)				{	fp = tanh(bn1.fp);	}

void CBignum::Acosh(void)						{	fp = acosh(fp);	}
void CBignum::Acosh(CBignum& bn1)				{	fp = acosh(bn1.fp);	}

void CBignum::Asinh(void)						{	fp = asinh(fp);	}
void CBignum::Asinh(CBignum& bn1)				{	fp = asinh(bn1.fp);	}

void CBignum::Atanh(void)						{	fp = atanh(fp);	}
void CBignum::Atanh(CBignum& bn1)				{	fp = atanh(bn1.fp);	}

void CBignum::Square(void)						{ fp = fp * fp;	}
void CBignum::Square(f64 d1)					{ fp = d1 * d1;	}
void CBignum::Square(CBignum& bn1)				{ fp = bn1.fp * bn1.fp; }

void CBignum::Log(void)							{ fp = log(fp);	}
void CBignum::Log(CBignum& bn1)					{ fp = log(bn1.fp);	}

void CBignum::Log2(void)						{ fp = log2(fp);	}
void CBignum::Log2(CBignum& bn1)				{ fp = log2(bn1.fp);	}

void CBignum::Log10(void)						{ fp = log10(fp);	}
void CBignum::Log10(CBignum& bn1)				{ fp = log10(bn1.fp);	}

void CBignum::YToX(CBignum& bnX)				{ fp = pow(fp, bnX.fp);	}

void CBignum::Cos(f64 d1)						{ fp = cos(d1);	}
void CBignum::Sin(f64 d1)						{ fp = sin(d1);	}
void CBignum::Tan(f64 d1)						{ fp = tan(d1);	}
void CBignum::Acos(f64 d1)						{ fp = acos(d1);	}
void CBignum::Asin(f64 d1)						{ fp = asin(d1);	}
void CBignum::Atan(f64 d1)						{ fp = atan(d1);	}
void CBignum::Atan2(f64 y, f64 x)				{ fp = atan2(y, x);	}
