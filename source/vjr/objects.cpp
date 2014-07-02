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
// Creates the object structure
//
//////
	SObject* iObj_create(u32 tnBaseType, void* obj_data)
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
				obj->baseType	= tnBaseType;
				obj->sub_obj	= obj_data;
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
	SObject* iObj_copy(SObject* template_obj, SObject* next, SObject* parent, bool tlCopyChildren, bool tlCopySubobjects, bool tlCreateSeparateBitmapBuffers)
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
						obj->bmp = iBmp_copy(template_obj->bmp);

					// Copy subobject data
					if (tlCopySubobjects)
						obj->sub_obj = iSubobj_copy(template_obj);

					// Copy children if need be
					if (tlCopyChildren && template_obj->firstChild)
						obj->firstChild = iObj_copy(template_obj->firstChild, NULL, obj, true, true, tlCreateSeparateBitmapBuffers);
				}
		}

		// Indicate our success or failure
		return(obj);
	}




//////////
//
// Delete the indicated object.
//
//////
	void iObj_delete(SObject* obj, bool tlDeleteSelf)
	{
		// Make sure our environment is sane
		if (obj)
		{
// TODO:  write this code
		}
	}




//////////
//
// Called to render the indicated object
//
//////
	u32 iObj_render(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		u32 lnPixelsRendered;


		// Make sure our environment is sane
		lnPixelsRendered = 0;
		if (obj)
		{
			switch (obj->baseType)
			{
				case _OBJECT_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
					lnPixelsRendered += iSubobj_renderEmpty(obj, (SSubObjEmpty*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_FORM:			// Form class, the main outer window the OS sees
					lnPixelsRendered += iSubobj_renderForm(obj, (SSubObjForm*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
					lnPixelsRendered += iSubobj_renderSubform(obj, (SSubObjSubform*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_LABEL:		// A label
					lnPixelsRendered += iSubobj_renderLabel(obj, (SSubObjLabel*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_TEXTBOX:		// An input textbox
					lnPixelsRendered += iSubobj_renderTextbox(obj, (SSubObjTextbox*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_BUTTON:		// A push button
					lnPixelsRendered += iSubobj_renderButton(obj, (SSubObjButton*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_EDITBOX:		// An input multi-line editbox
					lnPixelsRendered += iSubobj_renderEditbox(obj, (SSubObjEditbox*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_IMAGE:		// A graphical image
					lnPixelsRendered += iSubobj_renderImage(obj, (SSubObjImage*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_CHECKBOX:		// A checkbox
					lnPixelsRendered += iSubobj_renderCheckbox(obj, (SSubObjCheckbox*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_OPTION:		// A combination selection
					lnPixelsRendered += iSubobj_renderOption(obj, (SSubObjOption*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
					break;

				case _OBJECT_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
					lnPixelsRendered += iSubobj_renderRadio(obj, (SSubObjRadio*)obj->sub_obj, tlRenderChildren, tlRenderSiblings);
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
// Called from subobjects to render any object children and sibling they may have based on flags
//
//////
	void iObj_renderChildrenAndSiblings(SObject* obj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		SObject* objSib;


		//////////
		// Render any children
		//////
			if (tlRenderChildren && obj->firstChild)
				iObj_render(obj->firstChild, true, true);


		//////////
		// Render any siblings
		//////
			if (tlRenderSiblings && obj->next)
			{
				objSib = obj->next;
				while (objSib)
				{
					// Render this sibling
					iObj_render(objSib, true, true);

					// Move to next sibling
					objSib = objSib->next;
				}
			}
	}





//////////
//
// Called to publish the indicated object, which takes the rendered bitmaps of all child objects
// and overlays them where they should be
//
//////
	u32 iObj_publish(SBitmap* bmpDst, RECT* trc, SObject* obj, bool tlPublishChildren, bool tlPublishSiblings)
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
				lnPixelsRendered += iObj_publish(bmpDst, &lrc, obj->firstChild, true, true);


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
					iBmp_delete(obj->bmpScaled, true, true);

					// Create the new one
					obj->bmpScaled = iBmp_allocate();
					iBmp_createBySize(obj->bmpScaled, lnWidth, lnHeight, 32);
					// Now when we scale into it, it will be the right size
				}

				// Perform the scale
				iBmp_scale(obj->bmpScaled, obj->bmp);

				// Perform the bitblt
				lnPixelsRendered += iBmp_bitBlt(bmpDst, &lrc, obj->bmpScaled);

			} else {
				// We can just copy
				lnPixelsRendered += iBmp_bitBlt(bmpDst, &lrc, obj->bmp);
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
					lnPixelsRendered += iObj_publish(bmpDst, trc, objSib, tlPublishChildren, false);

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
// Duplicate the chain of ObjectLabels, so the destination has a copy of each.
//
//////
	void iObj_duplicateChain(SObject** root, SObject* chain)
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
				obj = iObj_copy(chain, NULL, chain, true, true, true);
				if (obj)
				{
					// Update the duplicate object's forward pointer in the chain
					*oPrevPtr = obj;

					// Setup the next forward pointer
					oPrevPtr = &obj->next;

					// Get the location of our sub-object update pointer
					objDataPtr = &obj->sub_obj;

					// Copy the sub-object
					obj->sub_obj = iSubobj_copy(chain);
				}

				// Move to next item in the chain
				chain = chain->next;
			}
		}
	}




//////////
//
// Called to set the object size
//
//////
	void iObj_setSize(SObject* obj, s32 tnLeft, s32 tnTop, s32 tnWidth, s32 tnHeight)
	{
		// Resize if need be
		obj->bmp = iBmp_verifySizeOrResize(obj->bmp, tnWidth, tnHeight);

		// Position and size its rectangle
		SetRect(&obj->rc, tnLeft, tnTop, tnLeft + tnWidth, tnTop + tnHeight);

		// Mark it dirty for a full re-render
		obj->isDirty = true;
	}




//////////
//
// Called to create the Windows-side window for the form.  The normal bit buffer is
// rendered regardless of whether or not the form is presented outwardly.  It can be
// used as an off-screen buffer in that way.
//
//////
	SWindow* iObj_createWindowForForm(SObject* obj_form)
	{
		SWindow* win;


		// Make sure our environment is sane
		win = NULL;
		if (obj_form)
			win = iWindow_createForObject(obj_form);

		// Indicate our status
		return(win);
	}




//////////
//
// Called to set the visible status of the indicated object.
// Returns the previous visible status.
//
//////
	bool iObj_setVisible(SObject* obj, bool tlNewVisible)
	{
		bool llOldVisible;


		// Make sure our environment is sane
		llOldVisible = false;
		if (obj)
		{
			llOldVisible	= obj->isVisible;
			obj->isVisible	= tlNewVisible;
		}

		// Indicate our status
		return(false);
	}




//////////
//
// Called to copy the sub-object based on type
//
//////
	void* iSubobj_copy(SObject* template_obj)
	{
		void* ptr;


		ptr = NULL;
		if (template_obj)
		{
			// Update the sub-object data
			switch (template_obj->baseType)
			{
				case _OBJECT_TYPE_EMPTY:		// Empty, used as a placeholder object that is not drawn
					ptr = (void*)iSubobj_createEmpty((SSubObjEmpty*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_FORM:			// Form class, the main outer window the OS sees
					ptr = (void*)iSubobj_createForm((SSubObjForm*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_SUBFORM:		// A new class which has its own drawing content and can be moved about using UI features
					ptr = (void*)iSubobj_createSubform((SSubObjSubform*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_LABEL:		// A label
					ptr = (void*)iSubobj_createLabel((SSubObjLabel*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_TEXTBOX:		// An input textbox
					ptr = (void*)iSubobj_createTextbox((SSubObjTextbox*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_BUTTON:		// A push button
					ptr = (void*)iSubobj_createButton((SSubObjButton*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_EDITBOX:		// An input multi-line editbox
					ptr = (void*)iSubobj_createEditbox((SSubObjEditbox*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_IMAGE:		// A graphical image
					ptr = (void*)iSubobj_createImage((SSubObjImage*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_CHECKBOX:		// A checkbox
					ptr = (void*)iSubobj_createCheckbox((SSubObjCheckbox*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_OPTION:		// A combination selection
					ptr = (void*)iSubobj_createOption((SSubObjOption*)template_obj->sub_obj, template_obj);
					break;

				case _OBJECT_TYPE_RADIO:		// A radio dial, which can also present as a slider or spinner
					ptr = (void*)iSubobj_createRadio((SSubObjRadio*)template_obj->sub_obj, template_obj);
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
	SSubObjEmpty* iSubobj_createEmpty(SSubObjEmpty* template_subobj, SObject* parent)
	{
		SSubObjEmpty* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjEmpty*)malloc(sizeof(SSubObjEmpty));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjEmpty));

				// Initially populate
				subobj->parent	= parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Note:  None are currently defined

				} else {
					// Use VJr defaults
				}

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
	SSubObjForm* iSubobj_createForm(SSubObjForm* template_subobj, SObject* parent)
	{
		SSubObjForm* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjForm*)malloc(sizeof(SSubObjForm));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjForm));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->font				= iFont_duplicate(template_subobj->font);
					subobj->nwRgba.color		= template_subobj->nwRgba.color;
					subobj->neRgba.color		= template_subobj->neRgba.color;
					subobj->swRgba.color		= template_subobj->swRgba.color;
					subobj->seRgba.color		= template_subobj->seRgba.color;
					subobj->backColor.color		= template_subobj->backColor.color;
					subobj->foreColor.color		= template_subobj->foreColor.color;
					subobj->captionColor.color	= template_subobj->captionColor.color;

					subobj->bmpIcon				= iBmp_copy(template_subobj->bmpIcon);
					iDatum_duplicate(&subobj->comment, &template_subobj->comment);
					iDatum_duplicate(&subobj->caption, &template_subobj->caption);
					iDatum_duplicate(&subobj->toolTip, &template_subobj->toolTip);

					*(u32*)&subobj->activate	= *(u32*)&template_subobj->activate;
					*(u32*)&subobj->deactivate	= *(u32*)&template_subobj->deactivate;

				} else {
					// Use VJr defaults
					subobj->font				= iFont_duplicate(gsFont);
					subobj->nwRgba.color		= NwColor.color;
					subobj->neRgba.color		= NeColor.color;
					subobj->swRgba.color		= SwColor.color;
					subobj->seRgba.color		= SeColor.color;
					subobj->backColor.color		= white.color;
					subobj->foreColor.color		= black.color;
					subobj->captionColor.color	= black.color;

					subobj->bmpIcon				= iBmp_copy(bmpVjrIcon);
					iDatum_duplicate(&subobj->caption, "Form", 4);

					*(u32*)&subobj->activate	= (u32)&iDefaultCallback_activate;
					*(u32*)&subobj->deactivate	= (u32)&iDefaultCallback_deactivate;
				}
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
	SSubObjSubform* iSubobj_createSubform(SSubObjSubform* template_subobj, SObject* parent)
	{
		SSubObjSubform* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjSubform*)malloc(sizeof(SSubObjSubform));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjSubform));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->font				= iFont_duplicate(template_subobj->font);
					subobj->borderNwColor.color	= template_subobj->borderNwColor.color;
					subobj->borderNeColor.color	= template_subobj->borderNeColor.color;
					subobj->borderSwColor.color	= template_subobj->borderSwColor.color;
					subobj->borderSeColor.color	= template_subobj->borderSeColor.color;
					subobj->backColor.color		= template_subobj->backColor.color;
					subobj->foreColor.color		= template_subobj->foreColor.color;
					subobj->captionColor.color	= template_subobj->captionColor.color;

					subobj->bmpIcon				= iBmp_copy(template_subobj->bmpIcon);
					iDatum_duplicate(&subobj->comment, &template_subobj->comment);
					iDatum_duplicate(&subobj->caption, &template_subobj->caption);
					iDatum_duplicate(&subobj->toolTip, &template_subobj->toolTip);

					*(u32*)&subobj->activate	= *(u32*)&template_subobj->activate;
					*(u32*)&subobj->deactivate	= *(u32*)&template_subobj->deactivate;

				} else {
					// Use VJr defaults
					// Copy from indicated template
					subobj->font				= iFont_duplicate(gsFont);
					subobj->borderNwColor.color	= NwColor.color;
					subobj->borderNeColor.color	= NeColor.color;
					subobj->borderSwColor.color	= SwColor.color;
					subobj->borderSeColor.color	= SeColor.color;
					subobj->backColor.color		= white.color;
					subobj->foreColor.color		= black.color;
					subobj->captionColor.color	= black.color;

					subobj->bmpIcon				= iBmp_copy(bmpVjrIcon);
					iDatum_duplicate(&subobj->caption, "Subform", 7);

					*(u32*)&subobj->activate	= *(u32*)&iDefaultCallback_activate;
					*(u32*)&subobj->deactivate	= *(u32*)&iDefaultCallback_deactivate;
				}
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
	SSubObjLabel* iSubobj_createLabel(SSubObjLabel* template_subobj, SObject* parent)
	{
		SSubObjLabel* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjLabel*)malloc(sizeof(SSubObjLabel));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjLabel));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->font						= iFont_duplicate(template_subobj->font);
					subobj->backColor.color				= template_subobj->backColor.color;
					subobj->foreColor.color				= template_subobj->foreColor.color;

					subobj->alignment					= template_subobj->alignment;
					iDatum_duplicate(&subobj->comment,	&template_subobj->comment);
					iDatum_duplicate(&subobj->caption,	&template_subobj->caption);
					iDatum_duplicate(&subobj->toolTip,	&template_subobj->toolTip);

					subobj->isOpaque					= template_subobj->isOpaque;
					subobj->isBorder					= template_subobj->isBorder;
					subobj->borderColor.color			= template_subobj->borderColor.color;
					subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
					subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

				} else {
					// Use VJr defaults
					subobj->font						= iFont_duplicate(gsFont);
					subobj->backColor.color				= white.color;
					subobj->foreColor.color				= black.color;

					subobj->alignment					= _ALIGNMENT_LEFT;
					iDatum_duplicate(&subobj->caption, "Label", 5);

					subobj->isOpaque					= true;
					subobj->isBorder					= false;
					subobj->borderColor.color			= black.color;
					subobj->disabledBackColor.color		= disabledBackColor.color;
					subobj->disabledForeColor.color		= disabledForeColor.color;
				}
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
	SSubObjTextbox* iSubobj_createTextbox(SSubObjTextbox* template_subobj, SObject* parent)
	{
		SSubObjTextbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjTextbox*)malloc(sizeof(SSubObjTextbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjTextbox));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->font						= iFont_duplicate(template_subobj->font);
					subobj->backColor.color				= template_subobj->backColor.color;
					subobj->foreColor.color				= template_subobj->foreColor.color;

					subobj->style						= template_subobj->style;
					subobj->alignment					= template_subobj->alignment;
					iDatum_duplicate(&subobj->value,		&template_subobj->value);
					subobj->valueLength					= template_subobj->valueLength;
					iDatum_duplicate(&subobj->picture,	&template_subobj->picture);
					iDatum_duplicate(&subobj->mask,		&template_subobj->mask);
					iDatum_duplicate(&subobj->comment,	&template_subobj->comment);
					iDatum_duplicate(&subobj->toolTip,	&template_subobj->toolTip);

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

				} else {
					// Use VJr defaults
					subobj->font						= iFont_duplicate(gsFont);
					subobj->backColor.color				= white.color;
					subobj->foreColor.color				= black.color;

					subobj->style						= _STYLE_3D;
					subobj->alignment					= _ALIGNMENT_LEFT;
					subobj->valueLength					= 0;

					subobj->cursor						= 0;
					subobj->selectStart					= -1;
					subobj->selectEnd					= -1;

					subobj->isOpaque					= true;
					subobj->isBorder					= false;
					subobj->borderColor.color			= black.color;
					subobj->selectedBackColor.color		= selectedBackColor.color;
					subobj->selectedForeColor.color		= selectedForeColor.color;
					subobj->disabledBackColor.color		= disabledBackColor.color;
					subobj->disabledForeColor.color		= disabledForeColor.color;

					*(u32*)&subobj->interactiveChange	= *(u32*)&iDefaultCallback_interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&iDefaultCallback_programmaticChange;
				}
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
	SSubObjButton* iSubobj_createButton(SSubObjButton* template_subobj, SObject* parent)
	{
		SSubObjButton* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjButton*)malloc(sizeof(SSubObjButton));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjButton));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->font						= iFont_duplicate(template_subobj->font);
					subobj->backColor.color				= template_subobj->backColor.color;
					subobj->foreColor.color				= template_subobj->foreColor.color;

					subobj->style						= template_subobj->style;
					subobj->alignment					= template_subobj->alignment;
					iDatum_duplicate(&subobj->caption,	&template_subobj->caption);
					iDatum_duplicate(&subobj->comment,	&template_subobj->comment);
					iDatum_duplicate(&subobj->toolTip,	&template_subobj->toolTip);

					subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
					subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

					*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;

				} else {
					// Use VJr defaults
					subobj->font						= iFont_duplicate(gsFont);
					subobj->backColor.color				= white.color;
					subobj->foreColor.color				= black.color;

					subobj->style						= _STYLE_3D;
					subobj->alignment					= _ALIGNMENT_LEFT;
					iDatum_duplicate(&subobj->caption,	"Button", 6);

					subobj->disabledBackColor.color		= disabledBackColor.color;
					subobj->disabledForeColor.color		= disabledForeColor.color;

					*(u32*)&subobj->interactiveChange	= *(u32*)&iDefaultCallback_interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&iDefaultCallback_programmaticChange;
				}
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
	SSubObjEditbox* iSubobj_createEditbox(SSubObjEditbox* template_subobj, SObject* parent)
	{
		SSubObjEditbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjEditbox*)malloc(sizeof(SSubObjEditbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjEditbox));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->font						= iFont_duplicate(template_subobj->font);
					subobj->backColor.color				= template_subobj->backColor.color;
					subobj->foreColor.color				= template_subobj->foreColor.color;

					subobj->style						= template_subobj->style;
					subobj->alignment					= template_subobj->alignment;
					iEditChainManager_duplicate(&subobj->codeBlock, template_subobj->codeBlock, true);
					iDatum_duplicate(&subobj->comment,	&template_subobj->comment);
					iDatum_duplicate(&subobj->toolTip,	&template_subobj->toolTip);

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

				} else {
					// Use VJr defaults
					subobj->font						= iFont_duplicate(gsFont);
					subobj->backColor.color				= white.color;
					subobj->foreColor.color				= black.color;

					subobj->style						= _STYLE_3D;
					subobj->alignment					= _ALIGNMENT_LEFT;

					subobj->cursor						= 0;
					subobj->selectStart					= -1;
					subobj->selectEnd					= -1;

					subobj->isOpaque					= true;
					subobj->isBorder					= false;
					subobj->borderColor.color			= black.color;
					subobj->selectedBackColor.color		= selectedBackColor.color;
					subobj->selectedForeColor.color		= selectedForeColor.color;
					subobj->disabledBackColor.color		= disabledBackColor.color;
					subobj->disabledForeColor.color		= disabledForeColor.color;

					*(u32*)&subobj->interactiveChange	= *(u32*)&iDefaultCallback_interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&iDefaultCallback_programmaticChange;
				}
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
	SSubObjImage* iSubobj_createImage(SSubObjImage* template_subobj, SObject* parent)
	{
		SSubObjImage* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjImage*)malloc(sizeof(SSubObjImage));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjImage));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->style						= template_subobj->style;
					iDatum_duplicate(&subobj->comment,	&template_subobj->comment);
					iDatum_duplicate(&subobj->toolTip,	&template_subobj->toolTip);
					subobj->image						= iBmp_copy(template_subobj->image);
					subobj->imageOver					= iBmp_copy(template_subobj->imageOver);

					*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;

				} else {
					// Use VJr defaults
					subobj->style						= _IMAGE_STYLE_OPAQUE;
					subobj->image						= iBmp_copy(bmpNoImage);

					*(u32*)&subobj->programmaticChange	= *(u32*)&iDefaultCallback_programmaticChange;
				}
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
	SSubObjCheckbox* iSubobj_createCheckbox(SSubObjCheckbox* template_subobj, SObject* parent)
	{
		SSubObjCheckbox* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjCheckbox*)malloc(sizeof(SSubObjCheckbox));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjCheckbox));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->font						= iFont_duplicate(template_subobj->font);
					subobj->backColor.color				= template_subobj->backColor.color;
					subobj->foreColor.color				= template_subobj->foreColor.color;

					subobj->alignment					= template_subobj->alignment;
					subobj->style						= template_subobj->style;
					subobj->value						= template_subobj->value;
					iDatum_duplicate(&subobj->comment,	&template_subobj->comment);
					iDatum_duplicate(&subobj->caption,	&template_subobj->caption);
					iDatum_duplicate(&subobj->toolTip,	&template_subobj->toolTip);

					subobj->isOpaque					= template_subobj->isOpaque;
					subobj->isBorder					= template_subobj->isBorder;
					subobj->borderColor.color			= template_subobj->borderColor.color;
					subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
					subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

					*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;

				} else {
					// Use VJr defaults
					subobj->font						= iFont_duplicate(gsFont);
					subobj->backColor.color				= white.color;
					subobj->foreColor.color				= black.color;

					subobj->alignment					= _ALIGNMENT_LEFT;
					subobj->style						= _STYLE_3D;
					subobj->value						= 0;
					iDatum_duplicate(&subobj->caption, "Checkbox", 8);

					subobj->isOpaque					= true;
					subobj->isBorder					= false;
					subobj->borderColor.color			= black.color;
					subobj->disabledBackColor.color		= disabledBackColor.color;
					subobj->disabledForeColor.color		= disabledForeColor.color;

					*(u32*)&subobj->interactiveChange	= *(u32*)&iDefaultCallback_interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&iDefaultCallback_programmaticChange;
				}
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
	SSubObjOption* iSubobj_createOption(SSubObjOption* template_subobj, SObject* parent)
	{
		SSubObjOption* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjOption*)malloc(sizeof(SSubObjOption));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjOption));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->backColor.color				= template_subobj->backColor.color;
					subobj->foreColor.color				= template_subobj->foreColor.color;

					subobj->alignment					= template_subobj->alignment;
					subobj->style						= template_subobj->style;
					iDatum_duplicate(&subobj->comment,	&template_subobj->comment);
					iDatum_duplicate(&subobj->toolTip,	&template_subobj->toolTip);

					subobj->optionCount					= template_subobj->optionCount;		// How many options are there?
					subobj->multiSelect					= template_subobj->multiSelect;		// Can multiple items be selected?

					// Copy the label objects
					iObj_duplicateChain(&subobj->firstOption, template_subobj->firstOption);	// Each option has its own set of properties, and each is of _OBJECT_TYPE_LABEL

					// Copy the events
					*(u32*)&subobj->onSelect			= *(u32*)&template_subobj->onSelect;
					*(u32*)&subobj->onDeselect			= *(u32*)&template_subobj->onDeselect;
					*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;

				} else {
					// Use VJr defaults
					subobj->backColor.color				= white.color;
					subobj->foreColor.color				= black.color;

					subobj->alignment					= _ALIGNMENT_LEFT;
					subobj->style						= _STYLE_3D;

					subobj->optionCount					= 2;
					subobj->multiSelect					= false;

					// Create the two objects
					subobj->firstOption					= iObj_create(_OBJECT_TYPE_LABEL, NULL);
					if (subobj->firstOption)
						subobj->firstOption->next		= iObj_create(_OBJECT_TYPE_LABEL, NULL);

					// Copy the events
					*(u32*)&subobj->onSelect			= *(u32*)&iDefaultCallback_onSelect;
					*(u32*)&subobj->onDeselect			= *(u32*)&iDefaultCallback_onDeselect;
					*(u32*)&subobj->interactiveChange	= *(u32*)&iDefaultCallback_interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&iDefaultCallback_programmaticChange;
				}
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
	SSubObjRadio* iSubobj_createRadio(SSubObjRadio* template_subobj, SObject* parent)
	{
		SSubObjRadio* subobj;


		//////////
		// Create the indicated item
		//////
			subobj = (SSubObjRadio*)malloc(sizeof(SSubObjRadio));


		//////////
		// If successful, initialize it
		//////
			if (subobj)
			{
				// Initialize
				memset(subobj, 0, sizeof(SSubObjRadio));

				// Initially populate
				subobj->parent = parent;

				// Initialize based on template
				if (template_subobj)
				{
					// Copy from indicated template
					subobj->font						= iFont_duplicate(template_subobj->font);
					subobj->backColor.color				= template_subobj->backColor.color;
					subobj->foreColor.color				= template_subobj->foreColor.color;

					subobj->alignment					= template_subobj->alignment;
					subobj->style						= template_subobj->style;
					subobj->value						= template_subobj->value;
					subobj->minValue					= template_subobj->minValue;
					subobj->maxValue					= template_subobj->maxValue;
					subobj->roundTo						= template_subobj->roundTo;
					iDatum_duplicate(&subobj->comment,	&template_subobj->comment);
					iDatum_duplicate(&subobj->toolTip,	&template_subobj->toolTip);

					subobj->isOpaque					= template_subobj->isOpaque;
					subobj->isBorder					= template_subobj->isBorder;
					subobj->borderColor.color			= template_subobj->borderColor.color;
					subobj->disabledBackColor.color		= template_subobj->disabledBackColor.color;
					subobj->disabledForeColor.color		= template_subobj->disabledForeColor.color;

					*(u32*)&subobj->interactiveChange	= *(u32*)&template_subobj->interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&template_subobj->programmaticChange;

				} else {
					// Use VJr defaults
					subobj->font						= iFont_duplicate(gsFont);
					subobj->backColor.color				= white.color;
					subobj->foreColor.color				= white.color;

					subobj->alignment					= _ALIGNMENT_LEFT;
					subobj->style						= _STYLE_3D;
					subobj->value						= 0;
					subobj->minValue					= 0;
					subobj->maxValue					= 100;
					subobj->roundTo						= 1.0f;

					subobj->isOpaque					= true;
					subobj->isBorder					= false;
					subobj->borderColor.color			= black.color;
					subobj->disabledBackColor.color		= disabledBackColor.color;
					subobj->disabledForeColor.color		= disabledForeColor.color;

					*(u32*)&subobj->interactiveChange	= *(u32*)&iDefaultCallback_interactiveChange;
					*(u32*)&subobj->programmaticChange	= *(u32*)&iDefaultCallback_programmaticChange;
				}
			}


		//////////
		// Indicate our success or failure
		//////
			return(subobj);
	}




//////////
//
// Called to set the form's icon
//
//////
	void iSubobj_form_setIcon(SObject* obj, SBitmap* bmp)
	{
		SSubObjForm* subobj;


		// Make sure our environment is sane
		if (obj && bmp && obj->baseType == _OBJECT_TYPE_FORM)
		{
			// Grab the form data
			subobj = (SSubObjForm*)obj->sub_obj;

			// Delete the old icon if any
			if (subobj->bmpIcon)
				iBmp_delete(subobj->bmpIcon, true, true);

			// Create a new icon that is 24x24
			subobj->bmpIcon = iBmp_allocate();
			iBmp_createBySize(subobj->bmpIcon, 24, 24, 32);

			// Scale the indicated icon into this one
			iBmp_scale(subobj->bmpIcon, bmp);
		}
	}




//////////
//
// Called to set the caption for the form
//
//////
	void iSubobj_form_setCaption(SObject* obj, s8* tcCaption, u32 tnCaptionLength)
	{
		SSubObjForm* subobj;


		// Make sure our environment is sane
		if (obj && obj->baseType == _OBJECT_TYPE_FORM)
		{
			// Grab the form data
			subobj = (SSubObjForm*)obj->sub_obj;

			// Set the caption
			iDatum_duplicate(&subobj->caption, tcCaption, tnCaptionLength);
		}
	}




//////////
//
// Called to set the border colors for the indicated form
//
//////
	void iSubobj_form_setBorderRgba(SObject* obj, u32 tnNwRgba, u32 tnNeRgba, u32 tnSwRgba, u32 tnSeRgba)
	{
		SSubObjForm* subobj;


		// Make sure our environment is sane
		if (obj && obj->baseType == _OBJECT_TYPE_FORM)
		{
			// Grab the form data
			subobj = (SSubObjForm*)obj->sub_obj;

			// Set the colors
			subobj->nwRgba.color	= tnNwRgba;
			subobj->neRgba.color	= tnNeRgba;
			subobj->swRgba.color	= tnSwRgba;
			subobj->seRgba.color	= tnSeRgba;
		}
	}




//////////
//
// Called to set the back color for the indicated form
//
//////
	u32 iSubobj_form_setBackColor(SObject* obj, u32 tnRgba)
	{
		u32				lnOldColor;
		SSubObjForm*	subobj;


		// Make sure our environment is sane
		lnOldColor = 0;
		if (obj && obj->baseType == _OBJECT_TYPE_FORM)
		{
			// Grab the form data
			subobj = (SSubObjForm*)obj->sub_obj;

			// SEt the color
			lnOldColor				= subobj->backColor.color;
			subobj->backColor.color	= tnRgba;
		}

		// Indicate the old color
		return(lnOldColor);
	}




//////////
//
// Called to set the fore color for the indicated form
//
//////
	u32 iSubobj_form_setForeColor(SObject* obj, u32 tnRgba)
	{
		u32				lnOldColor;
		SSubObjForm*	subobj;


		// Make sure our environment is sane
		lnOldColor = 0;
		if (obj && obj->baseType == _OBJECT_TYPE_FORM)
		{
			// Grab the form data
			subobj = (SSubObjForm*)obj->sub_obj;

			// SEt the color
			lnOldColor				= subobj->foreColor.color;
			subobj->foreColor.color	= tnRgba;
		}

		// Indicate the old color
		return(lnOldColor);
	}




//////////
//
// Called to set the form's caption color
//
//////
	u32 iSubobj_form_setCaptionColor(SObject* obj, u32 tnRgba)
	{
		u32				lnOldColor;
		SSubObjForm*	subobj;


		// Make sure our environment is sane
		lnOldColor = 0;
		if (obj && obj->baseType == _OBJECT_TYPE_FORM)
		{
			// Grab the form data
			subobj = (SSubObjForm*)obj->sub_obj;

			// SEt the color
			lnOldColor					= subobj->captionColor.color;
			subobj->captionColor.color	= tnRgba;
		}

		// Indicate the old color
		return(lnOldColor);
	}




//////////
//
// Called to delete the empty.
//
//////
	void iSubobj_deleteEmpty(SSubObjEmpty* subobj, bool tlFreeSelf)
	{
		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the form.
//
//////
	void iSubobj_deleteForm(SSubObjForm* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_free(subobj->font, true);
			iBmp_delete(subobj->bmpIcon, true, true);
			iDatum_free(&subobj->comment, false);
			iDatum_free(&subobj->caption, false);
			iDatum_free(&subobj->toolTip, false);


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the subform.
//
//////
	void iSubobj_deleteSubform(SSubObjSubform* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_free(subobj->font, true);
			iBmp_delete(subobj->bmpIcon, true, true);
			iDatum_free(&subobj->comment, false);
			iDatum_free(&subobj->caption, false);
			iDatum_free(&subobj->toolTip, false);


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the label.
//
//////
	void iSubobj_deleteLabel(SSubObjLabel* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_free(subobj->font, true);
			iDatum_free(&subobj->comment, false);
			iDatum_free(&subobj->caption, false);
			iDatum_free(&subobj->toolTip, false);


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the textbox.
//
//////
	void iSubobj_deleteTextbox(SSubObjTextbox* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_free(subobj->font, true);
			iDatum_free(&subobj->value, false);
			iDatum_free(&subobj->picture, false);
			iDatum_free(&subobj->mask, false);
			iDatum_free(&subobj->comment, false);
			iDatum_free(&subobj->toolTip, false);


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the button.
//
//////
	void iSubobj_deleteButton(SSubObjButton* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_free(subobj->font, true);
			iDatum_free(&subobj->caption, false);
			iDatum_free(&subobj->comment, false);
			iDatum_free(&subobj->toolTip, false);


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the editbox.
//
//////
	void iSubobj_deleteEditbox(SSubObjEditbox* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////
			iFont_free(subobj->font, true);
			iEditChainManager_free(&subobj->codeBlock, true);
			iDatum_free(&subobj->comment, false);
			iDatum_free(&subobj->toolTip, false);


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the image.
//
//////
	void iSubobj_deleteImage(SSubObjImage* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the checkbox.
//
//////
	void iSubobj_deleteCheckbox(SSubObjCheckbox* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the option.
//
//////
	void iSubobj_deleteOption(SSubObjOption* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Called to delete the radio.
//
//////
	void iSubobj_deleteRadio(SSubObjRadio* subobj, bool tlFreeSelf)
	{
		//////////
		// Free subobject components
		//////


		//////////
		// Free self
		//////
			if (tlFreeSelf)
				free(subobj);
	}




//////////
//
// Renders an empty.  Note, empty objects are not rendered.  This control, however,
// can have controls within which are rendered to off-screen buffers, used for whatever
// non-visual purposes exist.  As such, render calls are still made to it.
//
//////
	u32 iSubobj_renderEmpty(SObject* obj, SSubObjEmpty* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		//////////
		// Do any requisite processing
		//////
			iObj_renderChildrenAndSiblings(obj, tlRenderChildren, tlRenderSiblings);


		//////////
		// Success!
		//////
			obj->isDirty = false;
			return(0);		// Indicate that nothing was rendered which will affect the screen
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
	u32 iSubobj_renderForm(SObject* obj, SSubObjForm* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{
		u32				lnPixelsRendered;
		SObject*		objSib;
		RECT			lrc, lrc2, lrc3, lrc4;
		HFONT			lhfontOld;


		// Make sure our environment is sane
		lnPixelsRendered = 0;
		if (obj && subobj)
		{
			//////////
			// Traverse and render any children
			//////
				if (tlRenderChildren && obj->firstChild)
					lnPixelsRendered += iObj_render(obj->firstChild, true, tlRenderSiblings);


			//////////
			// If we need re-rendering, re-render
			//////
				// The entire bmp
				SetRect(&lrc, 0, 0, obj->bmp->bi.biWidth, obj->bmp->bi.biHeight);

				// Do we need to redraw?  Or can we just copy?
				if (obj->isDirty)
				{
					//////////
					// Frame it
					//////
						// Draw the window border
						iBmp_fillRect(obj->bmp, &lrc, subobj->nwRgba, subobj->neRgba, subobj->swRgba, subobj->seRgba, true);

						// Frame it
						iBmp_frameRect(obj->bmp, &lrc, black, black, black, black, false);

						// Draw the client area
						SetRect(&lrc2, 8, subobj->bmpIcon->bi.biHeight + 2, lrc.right - subobj->bmpIcon->bi.biHeight - 2, lrc.bottom - subobj->bmpIcon->bi.biHeight - 1);
						iBmp_fillRect(obj->bmp, &lrc2, white, white, white, white, false);

						// Put a border around the client area
						InflateRect(&lrc2, 1, 1);
						iBmp_frameRect(obj->bmp, &lrc2, black, black, black, black, false);


					//////////
					// Form icon and standard controls
					//////
						// Form icon
						SetRect(&lrc3,	bmpArrowUl->bi.biWidth + 8, 1, bmpArrowUl->bi.biWidth + 8 + subobj->bmpIcon->bi.biWidth, 1 + subobj->bmpIcon->bi.biHeight);
						iBmp_bitBlt(obj->bmp, &lrc3, subobj->bmpIcon);
						// Close
						SetRect(&lrc2,	lrc.right - bmpArrowUr->bi.biWidth - 8 - bmpClose->bi.biWidth, lrc.top + 1, lrc.right - bmpArrowUr->bi.biWidth - 8, lrc.bottom - 1);
						iBmp_bitBlt(obj->bmp, &lrc2, bmpClose);
						// Maximize
						SetRect(&lrc2,	lrc2.left - bmpMaximize->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
						iBmp_bitBlt(obj->bmp, &lrc2, bmpMaximize);
						// Minimize
						SetRect(&lrc2,	lrc2.left - bmpMinimize->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
						iBmp_bitBlt(obj->bmp, &lrc2, bmpMinimize);
						// Move
						SetRect(&lrc4,	lrc2.left - bmpMove->bi.biWidth - 1, lrc2.top, lrc2.left - 1, lrc2.bottom);
						iBmp_bitBlt(obj->bmp, &lrc4, bmpMove);


					//////////
					// Resizing arrows
					//////
						// Upper left arrow
						SetRect(&lrc2, lrc.left, lrc.top, lrc.left + bmpArrowUl->bi.biWidth, lrc.top + bmpArrowUl->bi.biHeight);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpArrowUl);
						// Upper right arrow
						SetRect(&lrc2, lrc.right - bmpArrowUr->bi.biWidth, lrc.top, lrc.right, lrc.top + bmpArrowUr->bi.biHeight);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpArrowUr);
						// Lower left arrow
						SetRect(&lrc2, lrc.right - bmpArrowLr->bi.biWidth, lrc.bottom - bmpArrowLr->bi.biHeight, lrc.right, lrc.bottom);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpArrowLr);
						// Lower right arrow
						SetRect(&lrc2, lrc.left, lrc.bottom - bmpArrowLl->bi.biHeight, lrc.left + bmpArrowLl->bi.biWidth, lrc.bottom);
						iBmp_bitBltMask(obj->bmp, &lrc2, bmpArrowLl);


					//////////
					// Form caption
					//////
						SetRect(&lrc2, lrc3.right + 8, lrc3.top + 2, lrc4.right - 8, lrc3.bottom);
						lhfontOld = (HFONT)SelectObject(obj->bmp->hdc, subobj->font->hfont);
						SetTextColor(obj->bmp->hdc, (COLORREF)RGB(subobj->captionColor.red, subobj->captionColor.grn, subobj->captionColor.blu));
						SetBkMode(obj->bmp->hdc, TRANSPARENT);
						DrawTextA(obj->bmp->hdc, subobj->caption.data, subobj->caption.length, &lrc2, DT_VCENTER | DT_END_ELLIPSIS);
						SelectObject(obj->bmp->hdc, lhfontOld);


					//////////
					// Copy to prior rendered bitmap
					//////
						// Make sure our bmpPriorRendered exists
						obj->bmpPriorRendered = iBmp_verifyCopyIsSameSize(obj->bmpPriorRendered, obj->bmp);

						// Copy to the prior rendered version
						lnPixelsRendered += iBmp_bitBlt(obj->bmpPriorRendered, &lrc, obj->bmp);
						// Right now, we can use the bmpPriorRendered for a fast copy rather than 

				} else {
					// Render from its prior rendered version
					lnPixelsRendered += iBmp_bitBlt(obj->bmp, &lrc, obj->bmpPriorRendered);
				}


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;


			//////////
			// Render any siblings
			//////
				if (tlRenderSiblings && obj->next)
				{
					objSib = obj->next;
					while (objSib)
					{
						// Render this sibling
						lnPixelsRendered += iObj_render(objSib, tlRenderChildren, false);

						// Move to next sibling
						objSib = objSib->next;
					}
				}
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
	u32 iSubobj_renderSubform(SObject* obj, SSubObjSubform* subobj, bool tlRenderChildren, bool tlRenderSiblings)
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
	u32 iSubobj_renderLabel(SObject* obj, SSubObjLabel* subobj, bool tlRenderChildren, bool tlRenderSiblings)
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
	u32 iSubobj_renderTextbox(SObject* obj, SSubObjTextbox* subobj, bool tlRenderChildren, bool tlRenderSiblings)
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
	u32 iSubobj_renderButton(SObject* obj, SSubObjButton* subobj, bool tlRenderChildren, bool tlRenderSiblings)
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
	u32 iSubobj_renderEditbox(SObject* obj, SSubObjEditbox* subobj, bool tlRenderChildren, bool tlRenderSiblings)
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
	u32 iSubobj_renderImage(SObject* obj, SSubObjImage* subobj, bool tlRenderChildren, bool tlRenderSiblings)
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
	u32 iSubobj_renderCheckbox(SObject* obj, SSubObjCheckbox* subobj, bool tlRenderChildren, bool tlRenderSiblings)
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
	u32 iSubobj_renderOption(SObject* obj, SSubObjOption* subobj, bool tlRenderChildren, bool tlRenderSiblings)
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
	u32 iSubobj_renderRadio(SObject* obj, SSubObjRadio* subobj, bool tlRenderChildren, bool tlRenderSiblings)
	{


			//////////
			// Indicate we're no longer dirty, that we have everything
			//////
				obj->isDirty = false;
		return(0);
	}
