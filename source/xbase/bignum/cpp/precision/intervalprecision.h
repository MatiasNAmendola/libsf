#ifndef INC_INTERVAL
#define INC_INTERVAL

/*
 *******************************************************************************
 *
 *
 *                       Copyright (c) 2002-2012
 *                       Future Team Aps 
 *                       Denmark
 *
 *                       All Rights Reserved
 *
 *   This source file is subject to the terms and conditions of the
 *   Future Team Software License Agreement which restricts the manner
 *   in which it may be used.
 *   Mail: hve@hvks.com
 *
 *******************************************************************************
*/

/*
 *******************************************************************************
 *
 *
 * Module name     :   intervalprecision.h
 * Module ID Nbr   :   
 * Description     :   Interval Precision arithmetic template class
 *                     Works with the int_precision and float_precision classes
 * --------------------------------------------------------------------------
 * Change Record   :   
 *
 * Version	Author/Date		Description of changes
 * -------  -----------		----------------------
 * 01.01	HVE/020209		Initial release
 * 01.02    HVE/030421		Optimized the * operator to reduce the 8 multiplications
 *							to 2.
 *
 * End of Change Record
 * --------------------------------------------------------------------------
*/


/* define version string */
static char _VinterP_[] = "@(#)intervalprecision.h 01.02 -- Copyright (C) Future Team Aps";

#include <float.h>

// 
// Interval class
// Realisticly the class Type can be float, double, int_precision, & float_precision
// Since float and double are done unsing the Intel cpu (H/W) and using "specilization" 
// the int_precision and float_precision is done using the arbitrary precision packages
// Since their is no way to specific portable ROUND_DOWN and ROUND_UP mode the template class 
// heavily use specilization. For any other type besides float, double, int_precision and float_precision
// the operations is not defined
//
template<class _IT> class interval {
   _IT low, high;
   public:
      typedef _IT value_type;

      // constructor
      interval( const _IT& l, const _IT& h) { if( l < h ) { low =l; high = h; } else { low = h; high = l; } }
      interval( const _IT& d = 0 ) { low=d; high=d; }
	  //interval() : low(_IT(0)), high(_IT(0)) {}

      // constructor for any other type to _IT
      template<class X> interval( const interval<X>& a ) : low(a.lower()), high( a.upper())  { if( a.lower() < a.upper() ) { low =(_IT)a.lower(); high = (_IT)a.upper(); } else { low = (_IT)a.upper(); high = (_IT)a.lower(); } }
      
      // Coordinate functions
      _IT upper() const        { return high; }
      _IT lower() const        { return low; }
      _IT upper( const _IT& u ) { return ( high = u ); }
      _IT lower( const _IT& l ) { return ( low = l ); }

      _IT center() const { return ( high + low ) / (_IT)2; }
      _IT radius() const { _IT r; r =( high - low ) / (_IT)2; if( r < (_IT)0 ) r = -r; return r; }
      operator double() const { return (double)( ( high + low ) / (_IT)2 ); }  // Conversion to Double 
      operator int() const { return (int)( ( high + low ) / (_IT)2 ); }  // Conversion to int 
      _IT *ref_lower()   { return &low; }
      _IT *ref_upper()   { return &high; }

      // Essential operators
      interval<_IT>& operator= ( const interval<_IT>& );
      interval<_IT>& operator+=( const interval<_IT>& );
      interval<_IT>& operator-=( const interval<_IT>& );
      interval<_IT>& operator*=( const interval<_IT>& );
      interval<_IT>& operator/=( const interval<_IT>& );
   };


// Unary and Binary arithmetic
template<class _IT> interval<_IT> operator+( const interval<_IT>&, const interval<_IT>& );
template<class _IT> interval<_IT> operator+( const interval<_IT>& );  // Unary 
template<class _IT> interval<_IT> operator-( const interval<_IT>&, const interval<_IT>& );
template<class _IT> interval<_IT> operator-( const interval<_IT>& );                 // Unary
template<class _IT> interval<_IT> operator*( const interval<_IT>&, const interval<_IT>& );
template<class _IT> interval<_IT> operator/( const interval<_IT>&, const interval<_IT>& );

//interval<double> log( const interval<double>& );
//interval<double> log10( const interval<double>& );
//interval<double> sqrt( const interval<double>& );
//interval<double> pow( const interval<double>&, const double );
//interval<double> exp( const interval<double>& );

// Output Operator <<
//
template<class _Ty> std::ostream& operator<<( std::ostream& strm, interval<_Ty>& a ) { return strm << "[" << a.lower() << "," << a.upper() << "]"; }

// Input operator >>
//
template<class _Ty> std::istream& operator>>( std::istream& strm, interval<_Ty>& c ) 
   {
   _Ty l, u; char ch;
   if( strm >> ch && ch != '[')
      strm.putback(ch), strm >> l, h = (_Ty)0;
	else
      if( strm >> h >> ch && ch != ',')
	      if( ch == ']')
	         h = (_Ty)0;
	      else 
            strm.putback( ch ); // strm.setstate(std::ios::failbit);
	   else
         if( strm >> im >> ch && ch != ']')
	         strm.putback( ch ); //, strm.setstate(ios_base::failbit);
	
   if(!strm.fail())
	   c = interval<_Ty>( l, h );

   return strm;
   }
 

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//    Essential Operators =,+=,-=,*=,/=
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////


// Works for all class types
//
template<class _IT> interval<_IT>& interval<_IT>::operator=( const interval<_IT>& a )
   {
   low = a.lower();
   high = a.upper();

   return *this;
   }


// Works all other classes. 
// Please note that this is for all interger classes. interval<int>, interval<long>, interval<int_precision>
//
template<class _IT> interval<_IT>& interval<_IT>::operator+=( const interval<_IT>& a )
   {
   low += a.lower();
   high += a.upper();
   
   return *this;
   }


// Specilization for float_precision and +=
//
interval<float_precision>& interval<float_precision>::operator+=( const interval<float_precision>& a )
   {
   low.mode( ROUND_DOWN );
   low += a.lower();
   
   high.mode( ROUND_UP );
   high += a.upper();
   
   return *this;
   }

// Specilization for float and +=
// That dont used fpcontrol and therefore can be used in managed application
//
interval<float>& interval<float>::operator+=( const interval<float>& a )
   {
	interval<float_precision> rhs(*this), lhs(a);

	rhs += lhs;

	low=rhs.lower();
	high=rhs.upper();

   return *this;
   }


// Specilization for double and +=
// That dont used fpcontrol and therefore can be used in managed application
//
interval<double>& interval<double>::operator+=( const interval<double>& a )
   {
	interval<float_precision> rhs(*this), lhs(a);

	rhs += lhs;

	low=rhs.lower();
	high=rhs.upper();

   return *this;
   }

// Works all other classes. 
// Please note that this is for all interger classes. interval<int>, interval<long>, interval<int_precision>
//
template<class _IT> interval<_IT>& interval<_IT>::operator-=( const interval<_IT>& a )
   {
   low -= a.high;
   high -= a.low;
   
   return *this;
   }

// Specilization for float_precision and -=
//
interval<float_precision>& interval<float_precision>::operator-=( const interval<float_precision>& a )
   {
   low.mode( ROUND_DOWN );
   low -= a.lower();
   
   high.mode( ROUND_UP );
   high -= a.upper();
   
   return *this;
   }

// Specilization for float and -=
// That dont used fpcontrol and therefore can be used in managed application
//
interval<float>& interval<float>::operator-=( const interval<float>& a )
   {
	interval<float_precision> rhs(*this), lhs(a);

	rhs -= lhs;

	low=rhs.lower();
	high=rhs.upper();

   return *this;
   }

// Specilization for double and -=
// That dont used fpcontrol and therefore can be used in managed application
//
interval<double>& interval<double>::operator-=( const interval<double>& a )
   {
	interval<float_precision> rhs(*this), lhs(a);

	rhs -= lhs;

	low=rhs.lower();
	high=rhs.upper();

   return *this;
   }

// Works all other classes. 
// Please note that this is for all interger classes. interval<int>, interval<long>, interval<int_precision>
// Instead of doing the mindless low = MIN(low*a.high, low*a.low,high*a.low,high*a.high) and
// high = MAX(low*a.high, low*a.low,high*a.low,high*a.high) requiring a total of 8 multiplication
//
//   low, high, a.low, a.high    result
//    +     +     +     +        +  +  [ low*a.low, high*a.high ]
//    +     +     -     +        -  +  [ high*a.low, high*a.high ]
//    +     +     -     -        -  -  [ high*a.low, low*a.high ]
//    -     +     +     +        -  +  [ low*a.high, high*a.high ]  
//    -     +     -     +        -  +  [ MIN(low*a.high,high*a.low), MAX(low*a.low,high*a.high) ]
//    -     +     -     -        -  -  [ high*a.low, low*a.low ]
//    -     -     +     +        -  -  [ low*a.high, high,a.low ]
//    -     -     -     +        -  -  [ low*a.high, low*a.low ]
//    -     -     -     -        +  +  [ high*a.high, low * a.low ]
//
template<class _IT> interval<_IT>& interval<_IT>::operator*=( const interval<_IT>& a )
   {
   _IT l, h, t;

   if( low >= (_IT)0 ) // 
      { // both low and high >= 0
      if( a.lower() >= (_IT)0 )
         { // a.low >=0, a.high >= 0
         l = low * a.lower();
         h = high * a.upper();
         }
      else
         if( a.upper() >= (_IT)0 )
            {  //  a.low < 0, a.high >= 0
            l = high * a.lower();
            h = high * a.upper();
            }
         else
            { // a.low and a.high < 0 
            l = high * a.lower();
            h = low * a.upper();
            }
      }
   else
      if( high >= (_IT)0 )
         {  // low < 0, high >= 0
         if( a.lower() >= (_IT)0 )
            { // a.low >=0, a.high >= 0
            l = low * a.upper();
            h = high * a.upper();
            }
         else
            if( a.upper() >= (_IT)0 )
               {  //  a.low < 0, a.high >= 0
               l = low * a.upper(); if ( l > ( t = high * a.lower() ) ) l = t;
               h = high * a.upper(); if ( h < ( t = low * a.lower() ) ) h = t;
               }
            else
               { // a.low and a.high < 0 
               l = high * a.lower();
               h = low * a.lower();
               }
         }
      else
         { // low and high are < 0 
         if( a.lower() >= (_IT)0 )
            { // a.low >=0, a.high >= 0
            l = low * a.upper();
            h = high * a.lower();
            }
         else
            if( a.upper() >= (_IT)0 )
               {  //  a.low < 0, a.high >= 0
               l = low * a.upper(); 
               h = low * a.lower();
               }
            else
               { // a.low and a.high < 0 
               l = high * a.upper();
               h = low * a.lower();
               }
        }

   low = l;
   high = h;

   return *this;
   }


// Specilization for float_precision and *= operator
//
interval<float_precision>& interval<float_precision>::operator*=( const interval<float_precision>& a )
   {
   float_precision l, h, t;

   l.precision( low.precision() );
   h.precision( low.precision() );   
   t.precision( low.precision() );

   l.mode( ROUND_DOWN );
   h.mode( ROUND_UP );

   if( low.sign() > 0 ) // 
      { // both low and high >= 0
      if( a.lower().sign() > 0 )
         { // a.low >=0, a.high >= 0
         l = low;  l *= a.lower();
         h = high; h *= a.upper();
         }
      else
         if( a.upper().sign() > 0 )
            {  //  a.low < 0, a.high >= 0
            l = high;  l *= a.lower();
            h = high; h *= a.upper();
            }
         else
            { // a.low and a.high < 0 
            l = high; l *= a.lower();
            h = low;  h *= a.upper();
            }
      }
   else
      if( high.sign() > 0 )
         {  // low < 0, high >= 0
         if( a.lower().sign() > 0 )
            { // a.low >=0, a.high >= 0
            l = low;  l *= a.upper();
            h = high; h *= a.upper();
            }
         else
            if( a.upper().sign() > 0 )
               {  //  a.low < 0, a.high >= 0
               t.mode( ROUND_DOWN );
               l = low;  l *= a.upper(); if( l > ( t = high, t *= a.lower() ) ) l = t;
               t.mode( ROUND_UP );
               h = high; h *= a.upper(); if( h < ( t = low, t *= a.lower() ) ) h = t;
               }
            else
               { // a.low and a.high < 0 
               l = high; l *= a.lower();
               h = low;  h *= a.lower();
               }
         }
      else
         { // low and high are < 0 
         if( a.lower().sign() > 0 )
            { // a.low >=0, a.high >= 0
            l = low;  l *= a.upper();
            h = high; h *= a.lower();
            }
         else
            if( a.upper().sign() > 0 )
               {  //  a.low < 0, a.high >= 0
               l = low; l *= a.upper(); 
               h = low; h *= a.lower();
               }
            else
               { // a.low and a.high < 0 
               l = high; l *= a.upper();
               h = low; h *= a.lower();
               }
        }

   low = l;
   high = h;

   return *this;
   }

// Specilization for float and *=
// That dont used fpcontrol and therefore can be used in managed application
//
interval<float>& interval<float>::operator*=( const interval<float>& a )
   {
	interval<float_precision> rhs(*this), lhs(a);

	rhs *= lhs;

	low=rhs.lower();
	high=rhs.upper();

   return *this;
   }

// Specilization for double and *=
// That dont used fpcontrol and therefore can be used in managed application
//
interval<double>& interval<double>::operator*=( const interval<double>& a )
   {
	interval<float_precision> rhs(*this), lhs(a);

	rhs *= lhs;

	low=rhs.lower();
	high=rhs.upper();

   return *this;
   }

// Works for all other classes
// Please note that this is for all interger classes. interval<int>, interval<long>
//
template<class _IT> interval<_IT>& interval<_IT>::operator/=( const interval<_IT>& b )
   {
   interval<_IT> a, c;

   c.low = (_IT)1 / b.upper();
   c.high = (_IT)1 / b.lower();

   a = interval( low, high );
   c *= a;

   low = c.lower();
   high = c.upper();

   return *this; 
   }

// Specilization for float_precision and /=
//
interval<float_precision>& interval<float_precision>::operator/=( const interval<float_precision>& b )
   {
   float_precision l = b.upper(), h = b.lower();
   interval<float_precision> c(b);

   l.mode( ROUND_DOWN );
   l = _float_precision_inverse( l );

   h.mode( ROUND_UP );
   h = _float_precision_inverse( h );

   c = interval<float_precision>( l , h );
   *this *= c;

   return *this;
   }

// Specilization for float and /=
// That dont used fpcontrol and therefore can be used in managed application
//
interval<float>& interval<float>::operator/=( const interval<float>& a )
   {
	interval<float_precision> rhs(*this), lhs(a);

	rhs /= lhs;

	low=rhs.lower();
	high=rhs.upper();

   return *this;
   }

// Specilization for double and /=
// That dont used fpcontrol and therefore can be used in managed application
//
interval<double>& interval<double>::operator/=( const interval<double>& a )
   {
	interval<float_precision> rhs(*this), lhs(a);

	rhs /= lhs;

	low=rhs.lower();
	high=rhs.upper();

   return *this;
   }


// Specilization for int_precision and /=
//
interval<int_precision>& interval<int_precision>::operator/=( const interval<int_precision>& b )
   {
   float_precision l = b.upper(), h = b.lower();
   interval<float_precision> c(b), a(*this);

   l.mode( ROUND_DOWN );
   l = _float_precision_inverse( l );

   h.mode( ROUND_UP );
   h = _float_precision_inverse( h );

   c = interval<float_precision>( l , h );
   a *= c;

   low = (int_precision)floor( a.lower() );
   high = (int_precision)ceil( a.upper() );

   return *this;
   }


// Specialization for int and /=
//
interval<int>& interval<int>::operator/=( const interval<int>& b )
   {
   double tlow, thigh;
   interval<int> a;
   interval<double> c;

   tlow = 1 / (double)b.upper();
   thigh = 1 / (double)b.lower();

   a = interval( low, high );
   c = interval<double>( tlow, thigh );
   c *= a;

   low = (int)floor( c.lower() );
   high = (int)ceil( c.upper() );

   return *this; 
   }

//////////////////////////////////////////////////////////////////////////////////////
///
/// END Essential Operators
///
//////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//    Binary and Unary Operators +,-,*,/
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Binary + operator
// Works for all classes
//
template<class _IT> interval<_IT> operator+( const interval<_IT>& a, const interval<_IT>& b )
   {
   interval<_IT> c(a);

   c += b; 
   
   return c;
   }


// Unary + operator
// Works for all classes
//
template<class _IT> interval<_IT> operator+( const interval<_IT>& a )
   {
   return a;
   }

// Binary - operator
// Works for all classes
//
template<class _IT> interval<_IT> operator-( const interval<_IT>& a, const interval<_IT>& b )
   {
   interval<_IT> c(a);

   c -= b;

   return c;
   }


// Unary - operator
// Works for all classes
//
template<class _IT> interval<_IT> operator-( const interval<_IT>& a )
   {
   interval<_IT> c(a);

   c = interval();
   c -= a;

   return c;
   }

// Binary * operator
// Works for all classes
//
template<class _IT> interval<_IT> operator*( const interval<_IT>& a, const interval<_IT>& b )
   {
   interval<_IT> c(a);

   c *= b;

   return c;
   }

// Binary / operator
// Works for all classes
//
template<class _IT> interval<_IT> operator/( const interval<_IT>& a, const interval<_IT>& b )
   {
   interval<_IT> c(a);

   if( c.lower() == b.lower() && c.upper() == b.upper() )
      c = interval<_IT>(1,1);
   else
      c /= b;
   
   return c;
   }

//////////////////////////////////////////////////////////////////////////////////////
///
/// END Binary and Unary Operators
///
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
///
/// Interval sqrt(), log10(), log(), exp() and pow()
///
//////////////////////////////////////////////////////////////////////////////////////


// Specilization for sqrt(float_precision)
// 
interval<float_precision> sqrt( const interval<float_precision>& x )
   {
   float_precision l, u;
   
   l.assign( x.lower() );  // Assign value, precision and mode
   l.mode( ROUND_DOWN );
   l = sqrt( l );

   u.assign( x.upper() );  // Assign value, precision and mode
   u.mode( ROUND_UP );
   u = sqrt( u );

   return interval<float_precision>( l, u );
   }

// sqrt for float using manged code.
//
interval<float> sqrt( const interval<float>& x )
   {
	interval<float_precision> fx(x);
   float lower, upper;
   
   fx=sqrt(fx);
   lower=fx.lower();
   upper=fx.upper();
   return interval<float>( lower, upper );
   }

// sqrt for double using managed code.
//
interval<double> sqrt( const interval<double>& x )
   {
	interval<float_precision> fx(x);
   double lower, upper;
   
   fx=sqrt(fx);
   lower=fx.lower();
   upper=fx.upper();
   return interval<double>( lower, upper );
   }


// Specilization for log float_precision
// 
interval<float_precision> log( const interval<float_precision>& x )
   {
   float_precision l, u;
   
   l.assign( x.lower() );  // Assign value, precision and mode
   l.mode( ROUND_DOWN );
   l = log( l );

   u.assign( x.upper() );  // Assign value, precision and mode
   u.mode( ROUND_UP );
   u = log( u );

   return interval<float_precision>( l, u );
   }

// log for float using manged code.
//
interval<float> log( const interval<float>& x )
   {
	interval<float_precision> fx(x);
   float lower, upper;
   
   fx=log(fx);
   lower=fx.lower();
   upper=fx.upper();
   return interval<float>( lower, upper );
   }

// log for double using managed code.
//
interval<double> log( const interval<double>& x )
   {
	interval<float_precision> fx(x);
   double lower, upper;
   
   fx=log(fx);
   lower=fx.lower();
   upper=fx.upper();
   return interval<double>( lower, upper );
   }



// Specilization for log float_precision
// 
interval<float_precision> log10( const interval<float_precision>& x )
   {
   float_precision l, u;
   
   l.assign( x.lower() );  // Assign value, precision and mode
   l.mode( ROUND_DOWN );
   l = log10( l );

   u.assign( x.upper() );  // Assign value, precision and mode
   u.mode( ROUND_UP );
   u = log10( u );

   return interval<float_precision>( l, u );
   }

// log10 for float using manged code.
//
interval<float> log10( const interval<float>& x )
   {
	interval<float_precision> fx(x);
   float lower, upper;
   
   fx=log10(fx);
   lower=fx.lower();
   upper=fx.upper();
   return interval<float>( lower, upper );
   }

// log10 for double using managed code.
//
interval<double> log10( const interval<double>& x )
   {
	interval<float_precision> fx(x);
   double lower, upper;
   
   fx=log10(fx);
   lower=fx.lower();
   upper=fx.upper();
   return interval<double>( lower, upper );
   }

   
// Specilization for exp float_precision
// 
interval<float_precision> exp( const interval<float_precision>& x )
   {
   float_precision l, u;
   
   l.assign( x.lower() );  // Assign value, precision and mode
   l.mode( ROUND_DOWN );
   l = exp( l );

   u.assign( x.upper() );  // Assign value, precision and mode
   u.mode( ROUND_UP );
   u = exp( u );

   return interval<float_precision>( l, u );
   }

// exp for float using manged code.
//
interval<float> exp( const interval<float>& x )
   {
	interval<float_precision> fx(x);
   float lower, upper;
   
   fx=exp(fx);
   lower=fx.lower();
   upper=fx.upper();
   return interval<float>( lower, upper );
   }

// exp for double using managed code.
//
interval<double> exp( const interval<double>& x )
   {
	interval<float_precision> fx(x);
   double lower, upper;
   
   fx=exp(fx);
   lower=fx.lower();
   upper=fx.upper();
   return interval<double>( lower, upper );
   }


// Specilization for pow float_precision
// 
interval<float_precision> pow( const interval<float_precision>& x, const float_precision& y )
   {
   interval<float_precision> c(x);

   c = log( x );
   c *= interval<float_precision>( y );
   c = exp( c );

   return c;
   }

// pow for float using manged code.
//
interval<float> pow( const interval<float>& x, const double y  )
   {
	interval<float_precision> fx(x);
	float_precision yy(y);
   float lower, upper;
   
   fx=pow(fx,yy);
   lower=fx.lower();
   upper=fx.upper();
   return interval<float>( lower, upper );
   }

// pow for double using managed code.
//
interval<double> pow( const interval<double>& x, const double y )
   {
	interval<float_precision> fx(x);
	float_precision yy(y);
   double lower, upper;
   
   fx=pow(fx,yy);
   lower=fx.lower();
   upper=fx.upper();
   return interval<double>( lower, upper );
   }

//////////////////////////////////////////////////////////////////////////////////////
///
/// END Interval sqrt(), log10(), log(), exp(), pow()
///
//////////////////////////////////////////////////////////////////////////////////////


#endif
