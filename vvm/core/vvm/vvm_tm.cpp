//////////
//
// /libsf/vvm/vvm/vvm_tm.cpp
//
//////
// Version 0.60
// Copyright (c) 2012, 2013 by Rick C. Hodgin
//////
// Last update:
//     November 10, 2012
//////
// Change log:
//     November 10, 2012 - Initial creation
//////
// See devhelp.txt.
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
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//









//////////
//
// Initializes the VVM to its power-on state.
// Processes any load commands found on the command line.
//
//////
	bool ivvmtm_initialize(void)
	{
		bool			llResult;
		u32				lnI;
		SThreadMizer*	ltm;


		//////////
		// Find out how many cores we're dealing with
		//////
			oss_getSystemInfo(&gsVvmSysInfo);
			gsVvmSysInfo.cores = min(max(gsVvmSysInfo.cores, 256), 1);			// Range must be 1..256


		//////////
		// For each core, create a thread control structure slot
		//////
			llResult = oss_allocateAdditionalStartEndMasterSlots(&gsVvm.gseRootThreadMizer, gsVvmSysInfo.cores);


		// Enter a loop (for breaking out of)
		while (llResult)
		{
			// For each core, spawn a worker thread and have it waiting
			for (lnI = 0; lnI < (u32)gsVvmSysInfo.cores; lnI++)
			{
				//////////
				// Create its entry in the next free slot
				//////
					ltm = (SThreadMizer*)oss_SEChain_append(&gsVvm.gseRootThreadMizer, oss_getNextUniqueId(), oss_getNextUniqueId(), sizeof(SThreadMizer), 1, NULL);
					if (!ltm)
					{
						// Should not happen, but it did
						llResult = false;
						break;
					}

				//////////
				// Tag it as indicated
				//////
					ltm->threadNum = lnI;

				//////////
				// Spawn it as a viable thread, but paused
				//////
					ltm->ossInfo = oss_threadCreate((u64)&ivvmtm_mainLoop, (void*)ltm, true);
					if (!ltm->ossInfo)
					{
						// Failure spawning
						llResult = false;
						break;
					}

				//////////
				// Start it up, get it going, time to move along, move along, nothing to see here
				//////
					oss_threadResume(ltm->ossInfo);

			}
			// When we get here, we're good, every slot's been filled.  There is peace and fullness.
			llResult = true;
			break;
		}

		// Indicate success or failure (Note:  We are praying for success, but will accept failure if need be)
		return(llResult);
	}




//////////
//
// Spawned from oss_createThread, the parameter is that which we passed above ((void*)ltm)
//
//////
	void ivvmtm_mainLoop(void* ttm)
	{
		_ivvmtm_SMainLoop	lml;


		// Make sure the environment is sane
		lml.ltm = (SThreadMizer*)ttm;

		// Initialize our counters.
		// These are not set each pass because we search top-down until we find something
		// to do, then we do it, then we politely release our timeslice and continue on again
		// immediately thereafter.  We want to pick back up from exactly where we were.
		lml.lnI	= 0;
		lml.lnJ	= 0;
		while (lml.ltm)
		{
			// Try to find something to do
			// Lock the semaphore
			oss_lockSemaphore(gsVvm.gsemProgramsAccess);
			lml.llProgramsGeneralAccessLocked = true;

			// Iterate for an empty thread, and then take it
			if (lml.lnI >= gsVvm.gseRootPrograms.masterCount)
				lml.lnI = 0;


			//////////
			// We continue from where we left off last time
			// BEGIN
			//////
				//////
					ivvmtm_mainLoopPrograms(&lml);
				//////
			//////
			// END
			//////////


			// Unlock if we need to
			if (lml.llProgramsGeneralAccessLocked)
			{
				// Unlock this semaphore
				oss_unlockSemaphore(gsVvm.gsemProgramsAccess);
				lml.llProgramsGeneralAccessLocked = false;
			}

			// Release this thread's timeslice to any other threads of equal value
			if (!lml.llProcessedSomething)		oss_sleep(1);			// We didn't find anything to do, so pause 1 millisecond
			else								oss_sleep(0);			// We did find something to do, and we did it by gum! ... So continue on immediately hereafter as there is still work to be done (we don't want to be burning daylight)
		}
		// Control will never reach here, as this thread must/will be terminated externally
	}




//////////
//
// Called to handle the programs loop.  Looks through gseRootPrograms one by one to find the
// next program with a serviceable thread.
//
//////
	void ivvmtm_mainLoopPrograms(_ivvmtm_SMainLoop* tml)
	{
		tml->llProcessedSomething = false;
		for ( ; !tml->llProcessedSomething && tml->lnI < gsVvm.gseRootPrograms.masterCount; tml->lnI++)
		{
			if (gsVvm.gseRootPrograms.master[tml->lnI] && gsVvm.gseRootPrograms.master[tml->lnI]->used)
			{
				// Get the pointer to this program
				tml->lp = (SProgram*)gsVvm.gseRootPrograms.master[tml->lnI]->ptr;

				// Try to lock this program's general thread-access semaphore
				if (oss_tryLockSemaphore(tml->lp->semForThreadsAccess))
				{
					// Indicate we have access to this program
					tml->llProgramsAccessLocked = true;


					//////////
					// We have access to the threads in general
					// Iterate through each trying to lock them to see if they need serviced
					// BEGIN
					//////
						//////
							ivvmtm_mainLoopThreads(tml);
						//////
					//////
					// END
					//////////


					// Did we process something?
					if (!tml->llProcessedSomething)
						tml->lnJ =0;		// Nope, reset for next look at the next program

					// If we're still locked, unlock
					if (tml->llProgramsAccessLocked)
					{
						// Unlock this semaphore
						oss_unlockSemaphore(tml->lp->semForThreadsAccess);
						tml->llProgramsAccessLocked = false;
					}
				}
			}
		}
	}




//////////
//
// Called to handle the threads loop.  Looks through the program's threads one by one to find
// the next thread that can be serviced.
//
//////
	void ivvmtm_mainLoopThreads(_ivvmtm_SMainLoop* tml)
	{
		// Repeat for every thread in this program
		for ( ; !tml->llProcessedSomething && tml->lnJ < tml->lp->_threads.masterCount; tml->lnJ++)
		{
			if (tml->lp->_threads.master[tml->lnJ] && tml->lp->_threads.master[tml->lnJ]->used)
			{
				// Get the pointer to this thread
				tml->lt = (SThread*)tml->lp->_threads.master[tml->lnJ]->ptr;

				// Try to lock this thread-specific semaphore to gain access to its parameters
				if (oss_tryLockSemaphore(tml->lt->status.semaphoreAccess))
				{
					// Indicate we have access to this thread locked
					tml->llThreadsAccessLocked = true;


					//////////
					// Try to execute it
					// BEGIN
					//////
						//////
							ivvmtm_mainLoopAttemptThreadExecution(tml);
						//////
					//////
					// END
					//////////

				}

				// Unlock the semaphore if need be
				if (tml->llThreadsAccessLocked)
				{
					// It need be :-)
					oss_unlockSemaphore(tml->lt->status.semaphoreAccess);
					tml->llThreadsAccessLocked = false;
				}
			}
		}
		// When we get here, we've processed something, or exhausted looking up this program's thread
	}




//////////
//
// Called to see if this Program.Thread is serviceable by this mainLoop algorithm.
//
//////
	void ivvmtm_mainLoopAttemptThreadExecution(_ivvmtm_SMainLoop* tml)
	{
		//////////
		// Make sure we can process this thread per the affinity setting
		//		1) in use
		//		2) not suspended
		//		3) it is set to run on this thread
		//////
		if (tml->lt->status.inUse && !tml->lt->status.isSuspended && (tml->lt->status.affinity == -1 || tml->lt->status.affinity == tml->ltm->threadNum))
		{
			// We are allowed to process this thread
			// We are going to execute this thread


			//////////
			// We're done iterating through programs to find our man.
			// This program is still locked, but we can release for other threads vying
			// Unlock the programsGeneralAccess (so other threads waiting to sett what to do can iterate)
			//////
				oss_unlockSemaphore(gsVvm.gsemProgramsAccess);
				tml->llProgramsGeneralAccessLocked = false;


			//////////
			// Physically do the processing
			// BEGIN
			//////
				//////
					ivvmtm_mainLoopThreadExecute(tml);
				//////
			//////
			// END
			//////////


		}
		// When we get here, this thread is either 1) not for us, or 2) processed
	}




//////////
//
// Called to setup and execute the thread's code.
//
//////
	void ivvmtm_mainLoopThreadExecute(_ivvmtm_SMainLoop* tml)
	{
		//////////
		//
		// Execute instructions until the timer tick changes the indicated number of times
		//
		// BEGIN
		//////
			//////
				// Indicate starting tick count
				tml->lt->status.startTick = *gsVvmSysInfo.addressOf1MsTickCount;


				//////////
				// Process for up to 2 ticks.
				// This guarantees at least 1ms access as the ticker could be very
				// close to cycling its first tick already.
				// BEGIN
				//////
					//////
						ivvme_executeThread(tml->lt, 2);
					//////
				//////
				// END
				//////////


				// Indicate we processed something
				tml->llProcessedSomething = true;
			//////
		//////
		// END
		//////////
	}