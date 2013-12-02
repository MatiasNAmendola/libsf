**********
*
* /libsf/vvm/utils/dsf/progs/dsf_dll.prg
*
*****
* Version 0.60
* Copyright (c) 2013 by Rick C. Hodgin
*****
* Last update:
*     Nov.26.2013
*****
* Change log:
*     Nov.26.2013	- Initial creation
*****
*
* This function should be in sync with the dsf_*() functions defined in:
*		/libsf/vvm/utils/dsf/msvc++/dsf/dsf.cpp
*
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
*     http:*www.visual-freepro.org
*     http:*www.visual-freepro.org/blog/
*     http:*www.visual-freepro.org/forum/
*     http:*www.visual-freepro.org/wiki/
*     http:*www.visual-freepro.org/wiki/index.php/PBL
*     http:*www.visual-freepro.org/wiki/index.php/Repeat_License
*
* Thank you.  And may The Lord bless you richly as you lift up your life, your
* talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
*
*****




FUNCTION declare_dsf_dll

	* Obtains the bitmap for the indicated character
	DECLARE INTEGER dsf_get_character_bitmap ;
						IN exe\dsf.dll ;
						INTEGER		tnAsciiCharacter, ;		&& CHR(tnAsciiCharacter) to get
						STRING		tcBitmapFilename, ;		&& Name of the bitmap file to write to (NULL if you don't want to keep the character bitmap)
						STRING		tcFloanFilename, ;		&& Grab the floan data representing the full outline of the character
						STRING		tcFontName, ;			&& "Arial", "Ubuntu", etc.
						INTEGER		tnBitmapHeight, ;		&& Typically 400
						INTEGER		tnBitmapWidth			&& Typically 400

	* Scales the bitmap to a new size for adjusted viewing
	DECLARE INTEGER dsf_scale_and_clip_bitmap ;
						IN exe\dsf.dll ;
						STRING		tcBitmapFilenameIn, ;	&& Input bitmap of image already drawn
						STRING		tcBitmapFilenameOut, ;	&& Output bitmap of image scaled
						SINGLE		tfWidthAdjust, ;		&& 1.0 leaves it the same horizontally
						SINGLE		tfHeightAdjust, ;		&& 1.0 leaves it the same vertically
						INTEGER		tnClipLeft, ;			&& In pixels, how many to clip/crop at the left after scaling
						INTEGER		tnClipTop, ;			&& In pixels, how many to clip/crop at the top after scaling
						INTEGER		tnNewWidth, ;			&& New width after scaling, typically 400
						INTEGER		tnNewHeight				&& New height after scaling, typically 400
