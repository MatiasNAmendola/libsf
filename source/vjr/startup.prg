**********
*
* /libsf/source/vjr/startup.prg
*
*****
* Version 0.20
* Copyright (c) 2014 by Rick C. Hodgin
*****
* Last update:
*     Jun.17.2014
*****
* Change log:
*     Jun.17.2014 - Initial creation
*****
*
* This software is released as Liberty Software under a Repeat License, as governed
* by the Public Benefit License v1.0 or later (PBL).
*
* You are free to use, copy, modify and share this software.  However, it can only
* be released under the PBL version indicated, and every project must include a copy
* of the pbl.txt document for its version as is at http:*www.libsf.org/licenses/.
*
* For additional information about this project, or to view the license, see:
*
*     http:*www.libsf.org/
*     http:*www.libsf.org/licenses/
*     http:*www.visual-freepro.org/vjr/indexmain.html
*     http:*www.visual-freepro.org/wiki/index.php/PBL
*     http:*www.visual-freepro.org/wiki/index.php/Repeat_License
*
* Thank you.  And may The Lord bless you richly as you lift up your life, your
* talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
*
*




**********
* Create _screen
*****
	PUBLIC _screen
	_screen			= CREATEOBJECT("Form")
	_screen.name	= "frmScreen"
	IF NOT _screen.protected.LoadLastFromVjrUserDbf()
		defaultScreenSetup()
	ENDIF


**********
* Create _jdebi
*****
	PUBLIC _jdebi
	_jdebi		= CREATEOBJECT("Form")
	_jdebi.name	= "frmJDebi"
	IF NOT _jdebi.protected.LoadLastFromVjrUserDbf()
		defaultJDebiSetup()
	ENDIF


**********
* Enter main system loop
*****
	_vjr.protected.Main()




**********
* Called to set the main screen to its defaults
*****
	FUNCTION defaultScreenSetup
	LOCAL lnMin
		**********
		* Set colors
		*****
			_screen.BackColor	= RGB(255,255,255)
			_screen.ForeColor	= RGB(0,0,0)
			_screen.NwColor		= RGB(222, 230, 255)
			_screen.NeColor		= RGB(157, 194, 214)
			_screen.SwColor		= RGB(255, 255, 255)
			_screen.SeColor		= RGB(192, 212, 255)
			_screen.Caption		= "Visual FreePro, Jr. -- " + VERSION(4)
		
		
		**********
		* Position screen
		*****
			lnMin				= MIN(SYSMETRIC(1) / 8, SYSMETRIC(2) / 8)
			_screen.Left		= lnMin
			_screen.Top			= lnMin
			_screen.Width		= (SYSMETRIC(1) / 2) - lnMin
			_screen.Height		= SYSMETRIC(2) - (2 * lnMin)
		
		
		**********
		* Make it visible.
		* Note:  Until it is visible, it's just a rendered buffer of bits.
		*        Once visible, it gets an OS-visible window for presentation.
		*****
			_screen.Visible		= .T.




**********
* Called to set the JDebi Debugger to its defaults
*****
	FUNCTION defaultJDebiSetup
	LOCAL lnMin
	
		**********
		* Set colors
		*****
			_jdebi.BackColor	= RGB(255,255,255)
			_jdebi.ForeColor	= RGB(0,0,0)
			_jdebi.NwColor		= RGB(222, 230, 255)
			_jdebi.NeColor		= RGB(157, 194, 214)
			_jdebi.SwColor		= RGB(255, 255, 255)
			_jdebi.SeColor		= RGB(192, 212, 255)
			_jdebi.Caption		= "JDebi Debugger -- " + VERSION(4) FLAGS JDebi
		
		
		**********
		* Position screen
		*****
			lnMin				= MIN(SYSMETRIC(1) / 8, SYSMETRIC(2) / 8)
			_jdebi.Left			= SYSMETRIC(1) / 2
			_jdebi.Top			= lnMin
			_jdebi.Width		= (SYSMETRIC(1) / 2) - lnMin
			_jdebi.Height		= SYSMETRIC(2) - (2 * lnMin)
		
		
		**********
		* Add its subforms
		*****
			_jdebi.AddObject("sourceCode",		"subform")		FLAGS inherit
			_jdebi.AddObject("sourceLight",		"subform")		FLAGS inherit
			_jdebi.AddObject("locals",			"subform")		FLAGS inherit
			_jdebi.AddObject("watchWindow",		"subform")		FLAGS inherit
			_jdebi.AddObject("debugging",		"subform")		FLAGS inherit
			_jdebi.AddObject("commandWindow",	"subform")		FLAGS inherit
			_jdebi.AddObject("output",			"subform")		FLAGS inherit
		
		
		**********
		* Position and size sourceCode
		*****
			WITH _jdebi.sourceCode
				* Standard positioning
				.Left		= 0
				.Top		= 0
				.Width		= INT(0.8 * _jdebi.width)
				.Height		= INT(0.6 * _jdebi.height)
				
				* Make it visible
				.Visible	= .T.
			ENDWITH
		
		
		**********
		* Position and size sourceLight
		*****
			WITH _jdebi.sourceLight
				* Standard positioning
				.Left		= _jdebi.sourceCode.Width
				.Top		= 0
				.Width		= _jdebi.Width - _jdebi.sourceCode.Width
				.Height		= _jdebi.sourceCode.Height
				
				**********
				* Add the index portion
				*****
					.AddObject("index", "subform")	FLAGS inherit
					.index.Top		= INT(0.8 * .Height)
					.index.Width	= .Width
					.index.Height	= .Height - .index.Top
					.index.Visible	= .T.
				
				* Make it visible within the JDebi form
				.Visible	= .T.
			ENDWITH
		
		
		**********
		* Position and size locals
		*****
			WITH _jdebi.locals
				* Standard positioning
				.Left		= 0
				.Top		= _jdebi.sourceCode.Height
				.Width		= _jdebi.sourceCode.Width
				.Height		= (_jdebi.Height - _jdebi.sourceCode.Height) / 2
				
				* Make it visible
				.Visible	= .T.
			ENDWITH
		
		
		**********
		* Position and size watchWindow
		*****
			WITH _jdebi.watchWindow
				* Standard positioning
				.Left		= 0
				.Top		= _jdebi.locals.Top + _jdebi.locals.Height
				.Width		= _jdebi.sourceCode.Width
				.Height		= (_jdebi.Height - _jdebi.sourceCode.Height) / 2
				
				* Make it visible
				.Visible	= .T.
			ENDWITH
		
		
		**********
		* Position and size debugging
		*****
			WITH _jdebi.debugging
				* Standard positioning
				.Left		= _jDebi.sourceCode.Width
				.Top		= _jDebi.watchWindow.Top
				.Width		= _jdebi.sourceLight.Width
				.Height		= INT(0.3 * (_jdebi.Height - _jdebi.sourceCode.Height))
				
				* Make it visible
				.Visible	= .T.
			ENDWITH
		
		
		**********
		* Position and size commandWindow
		*****
			WITH _jdebi.commandWindow
				* Standard positioning
				.Left		= 0
				.Top		= _jdebi.watchWindow.Top + _jdebi.watchWindow.Height
				.Width		= _jdebi.watchWindow.Width
				.Height		= _jdebi.Height - .Top
				
				* Make it visible
				.Visible	= .T.
			ENDWITH
		
		
		**********
		* Position and size output
		*****
			WITH _jdebi.output
				* Standard positioning
				.Left		= _jDebi.sourceCode.Width
				.Top		= _jDebi.debugging.Top + _jDebi.debugging.Height
				.Width		= _jdebi.debugging.Width
				.Height		= _jdebi.Height - .Top
				
				* Make it visible
				.Visible	= .T.
			ENDWITH
		
		
		**********
		* Make it visible.
		* Note:  Until it is visible, it's just a rendered buffer of bits.
		*        Once visible, it gets an OS-visible window for presentation.
		*****
			_jdebi.Visible		= .T.
