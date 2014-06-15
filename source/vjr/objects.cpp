//////////
//
// /libsf/source/vjr/objects.cpp
//
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jun.14.2014
//////
// Change log:
//     Jun.14.2014 - Initial creation
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




//////////
//
// Called to load a bitmap file that was loaded from disk, or simulated loaded from disk.
//
//////
	void iLoadObject(SObject* obj, cu8* bmpRawFileData)
	{
		BITMAPFILEHEADER*	bh;
		BITMAPINFOHEADER*	bi;


		//////////
		// Grab the headers
		//////
			bh = (BITMAPFILEHEADER*)bmpRawFileData;
			bi = (BITMAPINFOHEADER*)(bh + 1);


		//////////
		// Initialize the bitmap, and populate
		//////
			obj->bmp = iBmpAllocate();
			memcpy(&obj->bmp->bh, bh, sizeof(obj->bmp->bh));
			memcpy(&obj->bmp->bi, bi, sizeof(obj->bmp->bi));
			obj->bmp->bd			= (s8*)(bmpRawFileData + bh->bfOffBits);
			obj->bmp->rowWidth	= iBmpComputeRowWidth(obj->bmp);
			if (obj->bmp->bi.biBitCount == 24)
				iConvertBitmapTo32Bits(obj->bmp);
	}




//////////
//
// Creates the object structure
//
//////
	SObject* iCreateObject(u32 tnType, void* obj_data)
	{
		SObject* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObject*)malloc(sizeof(SObject));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObject));

				// Initially populate
				obj->type		= tnType;
				obj->obj_data	= obj_data;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the empty object structure
//
//////
	SObjectEmpty* iCreateObjectEmpty(SObjectEmpty* template_obj, SObject* parent)
	{
		SObjectEmpty* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectEmpty*)malloc(sizeof(SObjectEmpty));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectEmpty));

				// Initially populate
				obj->parent	= parent;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the form object structure
//
//////
	SObjectForm* iCreateObjectForm(SObjectForm* template_obj, SObject* parent)
	{
		SObjectForm* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectForm*)malloc(sizeof(SObjectForm));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectForm));

				// Initially populate
				obj->parent				= parent;
				obj->font				= iFontDuplicate(template_obj->font);
				obj->backColor.color	= template_obj->backColor.color;
				obj->foreColor.color	= template_obj->foreColor.color;
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->caption, &template_obj->caption);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the subform object structure
//
//////
	SObjectSubform* iCreateObjectSubform(SObjectSubform* template_obj, SObject* parent)
	{
		SObjectSubform* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectSubform*)malloc(sizeof(SObjectSubform));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectSubform));

				// Initially populate
				obj->parent				= parent;
				obj->font				= iFontDuplicate(template_obj->font);
				obj->backColor.color	= template_obj->backColor.color;
				obj->foreColor.color	= template_obj->foreColor.color;
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->caption, &template_obj->caption);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the label object structure
//
//////
	SObjectLabel* iCreateObjectLabel(SObjectLabel* template_obj, SObject* parent)
	{
		SObjectLabel* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectLabel*)malloc(sizeof(SObjectLabel));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectLabel));

				// Initially populate
				obj->parent						= parent;
				obj->font						= iFontDuplicate(template_obj->font);
				obj->backColor.color			= template_obj->backColor.color;
				obj->foreColor.color			= template_obj->foreColor.color;

				obj->alignment					= template_obj->alignment;
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->caption, &template_obj->caption);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);

				obj->isOpaque					= template_obj->isOpaque;
				obj->isBorder					= template_obj->isBorder;
				obj->borderColor.color			= template_obj->borderColor.color;
				obj->disabledBackColor.color	= template_obj->disabledBackColor.color;
				obj->disabledForeColor.color	= template_obj->disabledForeColor.color;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the textbox object structure
//
//////
	SObjectTextbox* iCreateObjectTextbox(SObjectTextbox* template_obj, SObject* parent)
	{
		SObjectTextbox* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectTextbox*)malloc(sizeof(SObjectTextbox));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectTextbox));

				// Initially populate
				obj->parent						= parent;
				obj->font						= iFontDuplicate(template_obj->font);
				obj->backColor.color			= template_obj->backColor.color;
				obj->foreColor.color			= template_obj->foreColor.color;

				obj->style						= template_obj->style;
				obj->alignment					= template_obj->alignment;
				iDatumDuplicate(&obj->value,	&template_obj->value);
				obj->valueLength				= template_obj->valueLength;
				iDatumDuplicate(&obj->picture,	&template_obj->picture);
				iDatumDuplicate(&obj->mask,		&template_obj->mask);
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);

				obj->cursor						= template_obj->cursor;
				obj->selectStart				= template_obj->selectStart;
				obj->selectEnd					= template_obj->selectEnd;

				obj->isOpaque					= template_obj->isOpaque;
				obj->isBorder					= template_obj->isBorder;
				obj->borderColor.color			= template_obj->borderColor.color;
				obj->selectedBackColor.color	= template_obj->selectedBackColor.color;
				obj->selectedForeColor.color	= template_obj->selectedForeColor.color;
				obj->disabledBackColor.color	= template_obj->disabledBackColor.color;
				obj->disabledForeColor.color	= template_obj->disabledForeColor.color;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the button object structure
//
//////
	SObjectButton* iCreateObjectButton(SObjectButton* template_obj, SObject* parent)
	{
		SObjectButton* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectButton*)malloc(sizeof(SObjectButton));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectButton));

				// Initially populate
				obj->parent						= parent;
				obj->font						= iFontDuplicate(template_obj->font);
				obj->backColor.color			= template_obj->backColor.color;
				obj->foreColor.color			= template_obj->foreColor.color;

				obj->style						= template_obj->style;
				obj->alignment					= template_obj->alignment;
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);

				obj->disabledBackColor.color	= template_obj->disabledBackColor.color;
				obj->disabledForeColor.color	= template_obj->disabledForeColor.color;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the editbox object structure
//
//////
	SObjectEditbox* iCreateObjectEditbox(SObjectEditbox* template_obj, SObject* parent)
	{
		SObjectEditbox* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectEditbox*)malloc(sizeof(SObjectEditbox));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectEditbox));

				// Initially populate
				obj->parent						= parent;
				obj->font						= iFontDuplicate(template_obj->font);
				obj->backColor.color			= template_obj->backColor.color;
				obj->foreColor.color			= template_obj->foreColor.color;

				obj->style						= template_obj->style;
				obj->alignment					= template_obj->alignment;
				iEditChainManagerDuplicate(&obj->value, template_obj->value);
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);

				obj->cursor						= template_obj->cursor;
				obj->selectStart				= template_obj->selectStart;
				obj->selectEnd					= template_obj->selectEnd;

				obj->isOpaque					= template_obj->isOpaque;
				obj->isBorder					= template_obj->isBorder;
				obj->borderColor.color			= template_obj->borderColor.color;
				obj->selectedBackColor.color	= template_obj->selectedBackColor.color;
				obj->selectedForeColor.color	= template_obj->selectedForeColor.color;
				obj->disabledBackColor.color	= template_obj->disabledBackColor.color;
				obj->disabledForeColor.color	= template_obj->disabledForeColor.color;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the image object structure
//
//////
	SObjectImage* iCreateObjectImage(SObjectImage* template_obj, SObject* parent)
	{
		SObjectImage* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectImage*)malloc(sizeof(SObjectImage));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectImage));

				// Initially populate
				obj->parent		= parent;
				obj->style		= template_obj->style;
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);
				obj->image		= iBmpCopy(template_obj->image);
				obj->imageOver	= iBmpCopy(template_obj->imageOver);
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the checkbox object structure
//
//////
	SObjectCheckbox* iCreateObjectCheckbox(SObjectCheckbox* template_obj, SObject* parent)
	{
		SObjectCheckbox* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectCheckbox*)malloc(sizeof(SObjectCheckbox));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectCheckbox));

				// Initially populate
				obj->parent						= parent;
				obj->font						= iFontDuplicate(template_obj->font);
				obj->backColor.color			= template_obj->backColor.color;
				obj->foreColor.color			= template_obj->foreColor.color;

				obj->alignment					= template_obj->alignment;
				obj->style						= template_obj->style;
				obj->value						= template_obj->value;
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->caption, &template_obj->caption);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);

				obj->isOpaque					= template_obj->isOpaque;
				obj->isBorder					= template_obj->isBorder;
				obj->borderColor.color			= template_obj->borderColor.color;
				obj->disabledBackColor.color	= template_obj->disabledBackColor.color;
				obj->disabledForeColor.color	= template_obj->disabledForeColor.color;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the combo object structure
//
//////
	SObjectOption* iCreateObjectOption(SObjectOption* template_obj, SObject* parent)
	{
		SObjectOption* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectOption*)malloc(sizeof(SObjectOption));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectOption));

				// Initially populate
				obj->parent	= parent;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Creates the radio object structure
//
//////
	SObjectRadio* iCreateObjectRadio(SObjectRadio* template_obj, SObject* parent)
	{
		SObjectRadio* obj;


		//////////
		// Create the indicated item
		//////
			obj = (SObjectRadio*)malloc(sizeof(SObjectRadio));


		//////////
		// If successful, initialize it
		//////
			if (obj)
			{
				// Initialize
				memset(obj, 0, sizeof(SObjectRadio));

				// Initially populate
				obj->parent						= parent;
				obj->font						= iFontDuplicate(template_obj->font);
				obj->backColor.color			= template_obj->backColor.color;
				obj->foreColor.color			= template_obj->foreColor.color;

				obj->alignment					= template_obj->alignment;
				obj->style						= template_obj->style;
				obj->value						= template_obj->value;
				obj->minValue					= template_obj->minValue;
				obj->maxValue					= template_obj->maxValue;
				obj->roundTo					= template_obj->roundTo;
				iDatumDuplicate(&obj->comment, &template_obj->comment);
				iDatumDuplicate(&obj->toolTip, &template_obj->toolTip);

				obj->isOpaque					= template_obj->isOpaque;
				obj->isBorder					= template_obj->isBorder;
				obj->borderColor.color			= template_obj->borderColor.color;
				obj->disabledBackColor.color	= template_obj->disabledBackColor.color;
				obj->disabledForeColor.color	= template_obj->disabledForeColor.color;
			}


		//////////
		// Indicate our success or failure
		//////
			return(obj);
	}




//////////
//
// Renders an empty.  Note, empty objects are not rendered.  This control, however,
// can be subclassed or can be used as a trigger object for the operation.  As such,
// calls are made to it.
//
//////
	u32 iRenderEmpty(SObjectEmpty* obj)
	{
		return(0);
	}




//////////
//
// Renders the form, which traverses through all child objects and renders to the
// furthest extent before rendering itself.
//
// Note:  The object rendering is independent of the publication of the constructed
//        bitmap.  The render operation only populates the bit buffer.  It will be
//        published at a later time, if indeed it is visible, however, it can after
//        rendering be re-directed to some other source, a disk file, or over a
//        network resource.
//
//////
	u32 iRenderForm(SObjectForm* obj)
	{
		return(0);
	}




//////////
//
// Renders the subform, which traverses through all child objects and renders to the
// furthest extent before rendering itself.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderSubform(SObjectSubform* obj)
	{
		return(0);
	}




//////////
//
// Renders the label, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderLabel(SObjectLabel* obj)
	{
		return(0);
	}




//////////
//
// Renders the textbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderTextbox(SObjectTextbox* obj)
	{
		return(0);
	}




//////////
//
// Renders the button, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderButton(SObjectButton* obj)
	{
		return(0);
	}




//////////
//
// Renders the editbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderEditbox(SObjectEditbox* obj)
	{
		return(0);
	}




//////////
//
// Renders the image, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderImage(SObjectImage* obj)
	{
		return(0);
	}




//////////
//
// Renders the checkbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderCheckbox(SObjectCheckbox* obj)
	{
		return(0);
	}




//////////
//
// Renders the option, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderOption(SObjectOption* obj)
	{
		return(0);
	}




//////////
//
// Renders the radio, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iRenderRadio(SObjectRadio* obj)
	{
		return(0);
	}
