February 21, 2014
Bignum Arbitrary Precision Floating Point Library
-------------------------------------------------

Files:		bignum.pjx/pjt		-- Project
			bignum.vcx/vct		-- Bignum class (drop onto form to use, rename "bn",
									access using "thisForm.bn")
			frmTest.scx/sct		-- Main form (examine the form's Init(), Click() events
									on buttons, and LostFocus() on Number 1, 2.

			bp.prg, go.prg		-- Helpers.  Use "do bp" to build the project, and "do go" to run it.
			main.prg			-- Top level program.  Only launches frmTest.

			bignum.exe			-- The VFP9 executable.
			bignum.dll			-- The DLL created by cpp\bignum.sln in Release mode.

-----

Sample usage:

SET CLASSLIB TO bignum.vcx ADDITIVE
bn = CREATEOBJECT("bignum")
n1 = bn.new()				&& Defaults to 256-bit precision, about 35 significant digits in base-10.
n2 = bn.new(500.0)			&& Defaults to 256-bit precision, and sets the initial value to 500.0.
n3 = bn.new(0, 512)			&& Overrides to 512-bit precision, and sets the initial value to 0.0.
n4 = bn.new(3, 1024, .T.)	&& Overrides to 1024-bit precision, sets the new default to 1024-bit
							&&   precision, and sets the initial value to 3.0.

bn.set(n1, 20.0)			&& Set the n1 value to 20.0
bn.set(n2. 4)				&& Set the n2 value to 4.0

* To set to a very large number, use text:
bn.set(n3, "1234567890123456789012345678901234567890.0987654321098765432109876543210987654321")

* To conduct operations, think of the formula as "a = a OP b", where "OP" is the operation.
* For Multiply, consider:  "a = a * b"
bn.mul(n1, n2)		&& n1 = n1 * n2
* Note:  At this ponit, the value is still stored in the memory slot of n1.
* Note:  n1 is not the actual number, but just an id to access it.
* Note:  To get the real number, use:

? bn.to_text(n1)

* In general, examine the frmTest.scx command buttons to see the parameters, or look at the bignum vcx:
MODIFY FORM frmTest.scx
MODIFY CLASS bignum OF bignum.vcx

-----
Please report any bugs if you'd like:
rick.c.hodgin@mykolab.com
