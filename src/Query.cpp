/*
 * Copyright 2017 Raefaldhi Amartya Junior <raefaldhiamartya@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Query.h"

#include <NodeMonitor.h>
#include <Query.h>
#include <Volume.h>
#include <VolumeRoster.h>
#include "Playlist.h"

Query* Query::instance = NULL;

Query::Query() 
	  : BQuery() {	
	BVolume volume;
	BVolumeRoster volRoster;
	volRoster.GetBootVolume(&volume);
	
	SetVolume(&volume);

	PushAttr("name");
	PushString("*");
	PushOp(B_CONTAINS);

	PushAttr("BEOS:TYPE");
	PushString("audio/");
	PushOp(B_BEGINS_WITH);
	PushOp(B_AND);

	Fetch();
	
	entry_ref ref;
	while (GetNextRef(&ref) == B_OK) {
		Playlist::library.push_back(ref);
	}
}

void Query::Init() {
	instance = new Query();
}
/*
		case B_QUERY_UPDATE: {
			int32 opcode = 0;
			if (message->FindInt32("opcode", &opcode) != B_OK) {
				return;
			}
			entry_ref ref;
			switch (opcode) {
				case B_ENTRY_CREATED: {			
				}break;
				case B_ENTRY_REMOVED: {
					
				}break;
			}
		}break;
*/
