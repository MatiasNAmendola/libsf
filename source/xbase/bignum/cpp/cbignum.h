//////////
//
// cbignum.h
//
/////
//
//




//////////
// Global variables
//////
	// This class encapsulates the functions above in a very straight-forward form
	class CBignum
	{
	public:
		CBignum();
		~CBignum();
		void operator=(CBignum& r);
		
		void Init(void);

		int Cmp(CBignum& c);
		int Cmp(f64 d);
		int Cmp(long int i);

		int CmpDelta(CBignum& t,	CBignum& c,	f64 delta);
		int CmpDelta(CBignum& t,	f64 d,		f64 delta);

		bool IsNan(void);
		bool IsNan(CBignum& c1);

		bool IsInf(void);
		bool IsInf(CBignum& c1);

		void Random(void);

		void Set(CBignum& c);
		void Set(f64 d);
		void Set(s8* s);
		// Common constants by member function
		void Set0(void);
		void Set1(void);
		void Set2(void);
		void Set3(void);
		void Set4(void);
		void Setpi(void);
		void Set2pi(void);
		void Setpi2(void);
		void Setpi4(void);
		void Set3pi2(void);
		void Setgr(void);
		void SetLn2(void);
		void SetLn10(void);

		void Abs(void);
		void Min(CBignum& c1);
		void Min2(CBignum& c1, CBignum& c2);
		void Min3(CBignum& c1, CBignum& c2, CBignum& c3);

		void Max(CBignum& c1);
		void Max2(CBignum& c1, CBignum& c2);
		void Max3(CBignum& c1, CBignum& c2, CBignum& c3);

		void Sqrt(void);
		void Sqrt(CBignum& c1);

		void Square(void);
		void Square(f64 d1);
		void Square(CBignum& c1);

		void YToX(CBignum& bnX);

		void Log(void);
		void Log(CBignum& bn1);

		void Log2(void);
		void Log2(CBignum& bn1);

		void Log10(void);
		void Log10(CBignum& bn1);

		s32 tos32(void);
		f32 tof32(void);
		f64 tof64(void);
		u32 toText(s8* tcValue, u32 tnLength);

		void Neg(void);
		void Neg(CBignum& c1);

		void Mod(CBignum& c1);

		void Mul(f64 d);
		void Mul(CBignum& c1);
		void Mul2(CBignum& c1, f64 d2);
		void Mul2(CBignum& c1, CBignum& c2);
		void Mul3(CBignum& c1, CBignum& c2, CBignum& c3);
		void Mul4(CBignum& c1, CBignum& c2, CBignum& c3, CBignum& c4);

		void Div(f64 d1);
		void Div(CBignum& c1);
		void Div2(CBignum& c1, CBignum& c2);
		void Div3(CBignum& c1, CBignum& c2, CBignum& c3);
		void Div4(CBignum& c1, CBignum& c2, CBignum& c3, CBignum& c4);

		void Add(f64 d1);
		void Add(CBignum& c1);
		void Add2(CBignum& c1, f64 d2);
		void Add2(CBignum& c1, CBignum& c2);
		void Add3(CBignum& c1, CBignum& c2, CBignum& c3);
		void Add4(CBignum& c1, CBignum& c2, CBignum& c3, CBignum& c4);

		void Sub(f64 d1);
		void Sub(CBignum& c1);
		void Sub2(CBignum& c1, f64 d2);
		void Sub2(CBignum& c1, CBignum& c2);
		void Sub3(CBignum& c1, CBignum& c2, CBignum& c3);
		void Sub4(CBignum& c1, CBignum& c2, CBignum& c3, CBignum& c4);

		void Cos(void);
		void Cos(CBignum& c1);

		void Sin(void);
		void Sin(CBignum& c1);

		void Tan(void);
		void Tan(CBignum& c1);

		void Acos(void);
		void Acos(CBignum& c1);

		void Asin(void);
		void Asin(CBignum& c1);

		void Atan(void);
		void Atan(CBignum& c1);

		void Atan2(CBignum& y, CBignum& x);

		void Cot(void);
		void Cot(CBignum& c1);

		void Csc(void);
		void Csc(CBignum& c1);

		void Sec(void);
		void Sec(CBignum& c1);

		void Cosh(void);
		void Cosh(CBignum& c1);

		void Sinh(void);
		void Sinh(CBignum& c1);

		void Tanh(void);
		void Tanh(CBignum& c1);

		void Cos(f64 d1);
		void Sin(f64 d1);
		void Tan(f64 d1);
		void Acos(f64 d1);
		void Asin(f64 d1);
		void Atan(f64 d1);
		void Atan2(f64 y, f64 x);

		void CopyOut(s8* bf);

	public:
		float_precision	fp;
	};
