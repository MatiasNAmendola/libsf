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
	void iObjectLoad(SObject* obj, cu8* bmpRawFileData)
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
	SObject* iObjectCreate(u32 tnType, void* obj_data)
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
// Copy the indicated object
//
//////
	SObject* iObjectCopy(SObject* template_obj, SObject* next, SObject* parent, bool tlCopyChildren, bool tlCopySubobjects, bool tlCreateSeparateBitmapBuffers)
	{
		SObject* obj;


		// Create the object
		obj = (SObject*)malloc(sizeof(SObject));
		if (obj)
		{
			//////////
			// Initialize the object
			//////
				memset(obj, 0, sizeof(SObject));


			//////////
			// Populate the object
			//////
				if (template_obj)
					memcpy(obj, template_obj, sizeof(SObject));		// Copy the existing object contents


			//////////
			// Update the next and parent, and clear out any bmpScaled
			//////
				obj->next		= next;
				obj->parent		= parent;
				obj->bmpScaled	= NULL;


			//////////
			// Copy the bitmap, subojects, and/or children (if need be)
			//////
				if (template_obj)
				{
					// Duplicate the bitmap buffer if need be
					if (tlCreateSeparateBitmapBuffers)
						obj->bmp = iBmpCopy(template_obj->bmp);

					// Copy subobject data
					if (tlCopySubobjects)
						obj->obj_data = iSubobjectCopy(template_obj);

					// Copy children if need be
					if (tlCopyChildren && template_obj->firstChild)
						obj->firstChild = iObjectCopy(template_obj->firstChild, NULL, obj, true, true, tlCreateSeparateBitmapBuffers);
				}
		}

		// Indicate our success or failure
		return(obj);
	}




//////////
//
// Called to render the indicated object
//
//////
	u32 iObjectRender(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		u32 lnPixelsRendered;


		// Make sure our environment is sane
		lnPixelsRendered = 0;
		if (obj)
		{
			switch (obj->type)
			{
				case _OBJECT_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
					lnPixelsRendered += iSubobject_renderEmpty(obj, (SObjectEmpty*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_FORM:			// Form class, the main outer window the OS sees
					lnPixelsRendered += iSubobject_renderForm(obj, (SObjectForm*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
					lnPixelsRendered += iSubobject_renderSubform(obj, (SObjectSubform*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_LABEL:		// A label
					lnPixelsRendered += iSubobject_renderLabel(obj, (SObjectLabel*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_TEXTBOX:		// An input textbox
					lnPixelsRendered += iSubobject_renderTextbox(obj, (SObjectTextbox*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_BUTTON:		// A push button
					lnPixelsRendered += iSubobject_renderButton(obj, (SObjectButton*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_EDITBOX:		// An input multi-line editbox
					lnPixelsRendered += iSubobject_renderEditbox(obj, (SObjectEditbox*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_IMAGE:		// A graphical image
					lnPixelsRendered += iSubobject_renderImage(obj, (SObjectImage*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_CHECKBOX:		// A checkbox
					lnPixelsRendered += iSubobject_renderCheckbox(obj, (SObjectCheckbox*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_OPTION:		// A combination selection
					lnPixelsRendered += iSubobject_renderOption(obj, (SObjectOption*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
					lnPixelsRendered += iSubobject_renderRadio(obj, (SObjectRadio*)obj->obj_data, tlRenderChildren, tlRenderSiblings);
					break;

				default:
// TODO:  We should never get here... we should fire off an internal consistency error
					break;
			}
		}

		// Indicate how many pixels were rendered
		return(lnPixelsRendered);
	}




//////////
//
// Called to publish the indicated object, which takes the rendered bitmaps of all child objects
// and overlays them where they should be
//
//////
	u32 iObjectPublish(SBitmap* bmpDst, RECT* trc, SObject* obj, bool tlPublishChildren, bool tlPublishSiblings)
	{
		u32			lnWidth, lnHeight, lnPixelsRendered;
		RECT		lrc;
		SObject*	objSib;


		//////////
		// Determine the position within the parent's rectangle where this object will go
		//////
			lnPixelsRendered = 0;
			SetRect(&lrc, trc->left + obj->rc.left, trc->top + obj->rc.top, trc->left + obj->rc.right, trc->top + obj->rc.bottom);


		//////////
		// Publish any children
		//////
			if (tlPublishChildren && obj->firstChild)
				lnPixelsRendered += iObjectPublish(bmpDst, &lrc, obj->firstChild, true, true);


		//////////
		// Publish this item
		//////
			// The size of the bitmap should equal the size of the rectangle on the parent.
			lnWidth		= obj->rc.right - obj->rc.left;
			lnHeight	= obj->rc.bottom - obj->rc.top;
			// If it's different, then we need to scale the content
			if (lnWidth != obj->bmp->bi.biWidth || lnHeight != obj->bmp->bi.biHeight)
			{
				// Need to scale, but do we need to create or alter our scaled target bitmap?
				if (!obj->bmpScaled || lnWidth != obj->bmpScaled->bi.biWidth || lnHeight != obj->bmpScaled->bi.biHeight)
				{
					// Delete any existing bitmap
					iBmpDelete(obj->bmpScaled, true);

					// Create the new one
					obj->bmpScaled = iBmpAllocate();
					iBmpCreateBySize(obj->bmpScaled, lnWidth, lnHeight, 32);
					// Now when we scale into it, it will be the right size
				}

				// Perform the scale
				iBmpScale(obj->bmpScaled, obj->bmp);

				// Perform the bitblt
				lnPixelsRendered += iBmpBitBlt(bmpDst, &lrc, obj->bmpScaled);

			} else {
				// We can just copy
				lnPixelsRendered += iBmpBitBlt(bmpDst, &lrc, obj->bmp);
			}


		//////////
		// Publish any siblings
		//////
			if (tlPublishSiblings && obj->next)
			{
				// Begin at the next sibling
				objSib = obj->next;
				while (objSib)
				{
					// Render this sibling
					lnPixelsRendered += iObjectPublish(bmpDst, trc, objSib, tlPublishChildren, false);

					// Move to next sibling
					objSib = objSib->next;
				}
			}


		//////////
		// Indicate how many pixels were painted
		//////
			return(lnPixelsRendered);
	}




//////////
//
// Called to copy the sub-object based on type
//
//////
	void* iSubobjectCopy(SObject* template_obj)
	{
		void* ptr;


		ptr = NULL;
		if (template_obj)
		{
			// Update the sub-object data
			switch (template_obj->type)
			{
				case _OBJECT_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
					ptr = (void*)iSubobject_createEmpty((SObjectEmpty*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_FORM:			// Form class, the main outer window the OS sees
					ptr = (void*)iSubobject_createForm((SObjectForm*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
					ptr = (void*)iSubobject_createSubform((SObjectSubform*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_LABEL:		// A label
					ptr = (void*)iSubobject_createLabel((SObjectLabel*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_TEXTBOX:		// An input textbox
					ptr = (void*)iSubobject_createTextbox((SObjectTextbox*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_BUTTON:		// A push button
					ptr = (void*)iSubobject_createButton((SObjectButton*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_EDITBOX:		// An input multi-line editbox
					ptr = (void*)iSubobject_createEditbox((SObjectEditbox*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_IMAGE:		// A graphical image
					ptr = (void*)iSubobject_createImage((SObjectImage*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_CHECKBOX:		// A checkbox
					ptr = (void*)iSubobject_createCheckbox((SObjectCheckbox*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_OPTION:		// A combination selection
					ptr = (void*)iSubobject_createOption((SObjectOption*)template_obj->obj_data, template_obj);
					break;

				case _OBJECT_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
					ptr = (void*)iSubobject_createRadio((SObjectRadio*)template_obj->obj_data, template_obj);
					break;

				default:
// TODO:  We should never get here... we should fire off an internal consistency error
					break;
			}
		}

		// Indicate our success or failure
		return(ptr);
	}




//////////
//
// Creates the empty object structure
//
//////
	SObjectEmpty* iSubobject_createEmpty(SObjectEmpty* template_subobj, SObject* parent)
	{
		SObjectEmpty* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectEmpty*)malloc(sizeof(SObjectEmpty));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectEmpty));

				// Initially populate
				subobj->parent	= parent;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the form object structure
//
//////
	SObjectForm* iSubobject_createForm(SObjectForm* template_subobj, SObject* parent)
	{
		SObjectForm* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectForm*)malloc(sizeof(SObjectForm));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectForm));

				// Initially populate
				subobj->parent				= parent;
				subobj->font				= iFontDuplicate(template_subobj->font);
				subobj->backColor.color		= template_subobj->backColor.color;
				subobj->foreColor.color		= template_subobj->foreColor.color;

				iDatumDuplicate(&subobj->comment, &template_subobj->comment);
				iDatumDuplicate(&subobj->caption, &template_subobj->caption);
				iDatumDuplicate(&subobj->toolTip, &template_subobj->toolTip);

				*(u32*)&subobj->activate	= *(u32*)&template_subobj->activate;
				*(u32*)&subobj->deactivate	= *(u32*)&template_subobj->deactivate;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the subform object structure
//
//////
	SObjectSubform* iSubobject_createSubform(SObjectSubform* template_subobj, SObject* parent)
	{
		SObjectSubform* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectSubform*)malloc(sizeof(SObjectSubform));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectSubform));

				// Initially populate
				subobj->parent				= parent;
				subobj->font				= iFontDuplicate(template_subobj->font);
				subobj->backColor.color		= template_subobj->backColor.color;
				subobj->foreColor.color		= template_subobj->foreColor.color;

				iDatumDuplicate(&subobj->comment, &template_subobj->comment);
				iDatumDuplicate(&subobj->caption, &template_subobj->caption);
				iDatumDuplicate(&subobj->toolTip, &template_subobj->toolTip);

				*(u32*)&subobj->activate	= *(u32*)&template_subobj->activate;
				*(u32*)&subobj->deactivate	= *(u32*)&template_subobj->deactivate;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the label object structure
//
//////
	SObjectLabel* iSubobject_createLabel(SObjectLabel* template_subobj, SObject* parent)
	{
		SObjectLabel* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectLabel*)malloc(sizeof(SObjectLabel));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectLabel));

				// Initially populate
				subobj->parent						= parent;
				subobj->font						= iFontDuplicate(template_subobj->font);
				subobj->backColor.color				= template_subobj->backColor.color;
				subobj->foreColor.color				= template_subobj->foreColor.color;

				subobj->alignment					= template_subobj->alignment;
				iDatumDuplicate(&subobj->comment,	&template_subobj->comment);
				iDatumDuplicate(&subobj->caption,	&template_subobj->caption);
				iDatumDuplicate(&subobj->toolTip,	&template_subobj->toolTip);

				subobj->isOpaque					= template_subobj->isOpaque;
				subobj->isBorder					= template_subobj->isBorder;
				subobj->borderColor.color			= template_subobj->borderColor.color;
				subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
				subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the textbox object structure
//
//////
	SObjectTextbox* iSubobject_createTextbox(SObjectTextbox* template_subobj, SObject* parent)
	{
		SObjectTextbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectTextbox*)malloc(sizeof(SObjectTextbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectTextbox));

				// Initially populate
				subobj->parent						= parent;
				subobj->font						= iFontDuplicate(template_subobj->font);
				subobj->backColor.color				= template_subobj->backColor.color;
				subobj->foreColor.color				= template_subobj->foreColor.color;

				subobj->style						= template_subobj->style;
				subobj->alignment					= template_subobj->alignment;
				iDatumDuplicate(&subobj->value,		&template_subobj->value);
				subobj->valueLength					= template_subobj->valueLength;
				iDatumDuplicate(&subobj->picture,	&template_subobj->picture);
				iDatumDuplicate(&subobj->mask,		&template_subobj->mask);
				iDatumDuplicate(&subobj->comment,	&template_subobj->comment);
				iDatumDuplicate(&subobj->toolTip,	&template_subobj->toolTip);

				subobj->cursor						= template_subobj->cursor;
				subobj->selectStart					= template_subobj->selectStart;
				subobj->selectEnd					= template_subobj->selectEnd;

				subobj->isOpaque					= template_subobj->isOpaque;
				subobj->isBorder					= template_subobj->isBorder;
				subobj->borderColor.color			= template_subobj->borderColor.color;
				subobj->selectedBackColor.color		= template_subobj->selectedBackColor.color;
				subobj->selectedForeColor.color		= template_subobj->selectedForeColor.color;
				subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
				subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

				*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
				*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the button object structure
//
//////
	SObjectButton* iSubobject_createButton(SObjectButton* template_subobj, SObject* parent)
	{
		SObjectButton* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectButton*)malloc(sizeof(SObjectButton));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectButton));

				// Initially populate
				subobj->parent						= parent;
				subobj->font						= iFontDuplicate(template_subobj->font);
				subobj->backColor.color				= template_subobj->backColor.color;
				subobj->foreColor.color				= template_subobj->foreColor.color;

				subobj->style						= template_subobj->style;
				subobj->alignment					= template_subobj->alignment;
				iDatumDuplicate(&subobj->comment,	&template_subobj->comment);
				iDatumDuplicate(&subobj->toolTip,	&template_subobj->toolTip);

				subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
				subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

				*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
				*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the editbox object structure
//
//////
	SObjectEditbox* iSubobject_createEditbox(SObjectEditbox* template_subobj, SObject* parent)
	{
		SObjectEditbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectEditbox*)malloc(sizeof(SObjectEditbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectEditbox));

				// Initially populate
				subobj->parent						= parent;
				subobj->font						= iFontDuplicate(template_subobj->font);
				subobj->backColor.color				= template_subobj->backColor.color;
				subobj->foreColor.color				= template_subobj->foreColor.color;

				subobj->style						= template_subobj->style;
				subobj->alignment					= template_subobj->alignment;
				iEditChainManagerDuplicate(&subobj->value, template_subobj->value);
				iDatumDuplicate(&subobj->comment,	&template_subobj->comment);
				iDatumDuplicate(&subobj->toolTip,	&template_subobj->toolTip);

				subobj->cursor						= template_subobj->cursor;
				subobj->selectStart					= template_subobj->selectStart;
				subobj->selectEnd					= template_subobj->selectEnd;

				subobj->isOpaque					= template_subobj->isOpaque;
				subobj->isBorder					= template_subobj->isBorder;
				subobj->borderColor.color			= template_subobj->borderColor.color;
				subobj->selectedBackColor.color		= template_subobj->selectedBackColor.color;
				subobj->selectedForeColor.color		= template_subobj->selectedForeColor.color;
				subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
				subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

				*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
				*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the image object structure
//
//////
	SObjectImage* iSubobject_createImage(SObjectImage* template_subobj, SObject* parent)
	{
		SObjectImage* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectImage*)malloc(sizeof(SObjectImage));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectImage));

				// Initially populate
				subobj->parent						= parent;
				subobj->style						= template_subobj->style;
				iDatumDuplicate(&subobj->comment,	&template_subobj->comment);
				iDatumDuplicate(&subobj->toolTip,	&template_subobj->toolTip);
				subobj->image						= iBmpCopy(template_subobj->image);
				subobj->imageOver					= iBmpCopy(template_subobj->imageOver);

				*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the checkbox object structure
//
//////
	SObjectCheckbox* iSubobject_createCheckbox(SObjectCheckbox* template_subobj, SObject* parent)
	{
		SObjectCheckbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectCheckbox*)malloc(sizeof(SObjectCheckbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectCheckbox));

				// Initially populate
				subobj->parent						= parent;
				subobj->font						= iFontDuplicate(template_subobj->font);
				subobj->backColor.color				= template_subobj->backColor.color;
				subobj->foreColor.color				= template_subobj->foreColor.color;

				subobj->alignment					= template_subobj->alignment;
				subobj->style						= template_subobj->style;
				subobj->value						= template_subobj->value;
				iDatumDuplicate(&subobj->comment,	&template_subobj->comment);
				iDatumDuplicate(&subobj->caption,	&template_subobj->caption);
				iDatumDuplicate(&subobj->toolTip,	&template_subobj->toolTip);

				subobj->isOpaque					= template_subobj->isOpaque;
				subobj->isBorder					= template_subobj->isBorder;
				subobj->borderColor.color			= template_subobj->borderColor.color;
				subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
				subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

				*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
				*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the combo object structure
//
//////
	SObjectOption* iSubobject_createOption(SObjectOption* template_subobj, SObject* parent)
	{
		SObjectOption* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectOption*)malloc(sizeof(SObjectOption));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectOption));

				// Initially populate
				subobj->parent						= parent;
				subobj->backColor.color				= template_subobj->backColor.color;
				subobj->foreColor.color				= template_subobj->foreColor.color;

				subobj->alignment					= template_subobj->alignment;
				subobj->style						= template_subobj->style;
				iDatumDuplicate(&subobj->comment,	&template_subobj->comment);
				iDatumDuplicate(&subobj->toolTip,	&template_subobj->toolTip);

				subobj->optionCount					= template_subobj->optionCount;		// How many options are there?
				subobj->multiSelect					= template_subobj->multiSelect;		// Can multiple items be selected?

				// Copy the label objects
				iObjectDuplicateChain(&subobj->firstOption, template_subobj->firstOption);	// Each option has its own set of properties, and each is of _OBJECT_TYPE_LABEL

				// Copy the events
				*(u32*)&subobj->onSelect			= *(u32*)&template_subobj->onSelect;
				*(u32*)&subobj->onDeselect			= *(u32*)&template_subobj->onDeselect;
				*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
				*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Creates the radio object structure
//
//////
	SObjectRadio* iSubobject_createRadio(SObjectRadio* template_subobj, SObject* parent)
	{
		SObjectRadio* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SObjectRadio*)malloc(sizeof(SObjectRadio));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SObjectRadio));

				// Initially populate
				subobj->parent						= parent;
				subobj->font						= iFontDuplicate(template_subobj->font);
				subobj->backColor.color				= template_subobj->backColor.color;
				subobj->foreColor.color				= template_subobj->foreColor.color;

				subobj->alignment					= template_subobj->alignment;
				subobj->style						= template_subobj->style;
				subobj->value						= template_subobj->value;
				subobj->minValue					= template_subobj->minValue;
				subobj->maxValue					= template_subobj->maxValue;
				subobj->roundTo						= template_subobj->roundTo;
				iDatumDuplicate(&subobj->comment,	&template_subobj->comment);
				iDatumDuplicate(&subobj->toolTip,	&template_subobj->toolTip);

				subobj->isOpaque					= template_subobj->isOpaque;
				subobj->isBorder					= template_subobj->isBorder;
				subobj->borderColor.color			= template_subobj->borderColor.color;
				subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
				subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

				*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
				*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Duplicate the chain of ObjectLabels, so the destination has a copy of each.
//
//////
	void iObjectDuplicateChain(SObject** root, SObject* chain)
	{
		SObject*		obj;
		SObject**		oPrevPtr;
		void**			objDataPtr;


		// Create the master record
		if (root)
		{
			// Repeat adding as many entries as there are
			oPrevPtr = root;
			while (chain)
			{
				// Create this object
				obj = iObjectCopy(chain, NULL, chain, true, true, true);
				if (obj)
				{
					// Update the duplicate object's forward pointer in the chain
					*oPrevPtr = obj;

					// Setup the next forward pointer
					oPrevPtr = &obj->next;

					// Get the location of our sub-object update pointer
					objDataPtr = &obj->obj_data;

					// Copy the sub-object
					obj->obj_data = iSubobjectCopy(chain);
				}

				// Move to next item in the chain
				chain = chain->next;
			}
		}
	}




//////////
//
// Renders an empty.  Note, empty objects are not rendered.  This control, however,
// can be subclassed or can be used as a trigger object for the operation.  As such,
// calls are made to it.
//
//////
	u32 iSubobject_renderEmpty(SObject* obj, SObjectEmpty* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		obj->isDirty = false;
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
	u32 iSubobject_renderForm(SObject* obj, SObjectForm* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		u32			lnPixelsRendered;
		SObject*	objSib;


		// Make sure our environment is sane
		lnPixelsRendered = 0;
		if (obj && subobj)
		{
			//////////
			// Traverse and render any children
			//////
				if (tlRenderChildren && obj->firstChild)
					lnPixelsRendered += iObjectRender(obj->firstChild, true, tlRenderSiblings);


			//////////
			// If we need re-rendering, re-render
			//////
				if (obj->isDirty)
				{
				}


			//////////
			// Render any siblings
			//////
				objSib = obj->next;
				while (objSib)
				{
					// Render this sibling
					lnPixelsRendered += iObjectRender(objSib, tlRenderChildren, false);

					// Move to next sibling
					objSib = objSib->next;
				}


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		}

		// Indicate how many pixels were drawn
		return(lnPixelsRendered);
	}




//////////
//
// Renders the subform, which traverses through all child objects and renders to the
// furthest extent before rendering itself.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderSubform(SObject* obj, SObjectSubform* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the label, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderLabel(SObject* obj, SObjectLabel* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the textbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderTextbox(SObject* obj, SObjectTextbox* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the button, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderButton(SObject* obj, SObjectButton* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the editbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderEditbox(SObject* obj, SObjectEditbox* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the image, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderImage(SObject* obj, SObjectImage* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the checkbox, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderCheckbox(SObject* obj, SObjectCheckbox* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the option, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderOption(SObject* obj, SObjectOption* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}




//////////
//
// Renders the radio, and traverses any child objects contained within to render them.
//
// Note:  See "Note" on iRenderForm().
//
//////
	u32 iSubobject_renderRadio(SObject* obj, SObjectRadio* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}
