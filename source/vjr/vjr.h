//////////
//
// /libsf/source/vjr/vjr.h
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Shobjidl.h>
#include "resource.h"

#include "vjr_const.h"

#include "builder.cpp"

#include "vjr_structs0.h"

#include "compiler_const.h"
#include "compiler_structs.h"
#include "compiler_defs.h"
#include "compiler_globals.h"

#include "vjr_structs.h"
#include "vjr_defs.h"
#include "vjr_globals.h"

#include "graphics\h\app_icon.h"
#include "graphics\h\move.h"
#include "graphics\h\minimize.h"
#include "graphics\h\maximize.h"
#include "graphics\h\close.h"
#include "graphics\h\arrow_ul.h"
#include "graphics\h\arrow_ur.h"
#include "graphics\h\arrow_lr.h"
#include "graphics\h\arrow_ll.h"

#include "graphics\h\checkbox_multi.h"
#include "graphics\h\checkbox_off.h"
#include "graphics\h\checkbox_on.h"

#include "graphics\h\textbox_2d.h"
#include "graphics\h\textbox_3d.h"

#include "graphics\h\radio_off.h"
#include "graphics\h\radio_on.h"

#include "graphics\h\jdebi_app_icon.h"

#include "vjr_sup.cpp"
#include "objects.cpp"
#include "callbacks.cpp"
#include "bitmaps.cpp"
#include "compiler.cpp"
