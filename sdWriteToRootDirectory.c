// Write to Root Directory of SD Card

void writeValuesToSDCard(float activePower, float reactivePower){
	uint32_t dataOld[128] = mmcSDRead();
	char dataOldBytes[512];
	int arrayCounter;
	for(arrayCounter = 0; arrayCounter < sizeof(dataOld); arrayCounter += 4){
		dataOldBytes[arrayCounter] = ((dataOld[arrayCounter] & 0xFF000000) >> 24);
		dataOldBytes[arrayCounter + 1] = ((dataOld[arrayCounter] & 0x00FF0000) >> 16);
		dataOldBytes[arrayCounter + 2] = ((dataOld[arrayCounter] & 0x0000FF00) >> 8);
		dataOldBytes[arrayCounter + 3] = ((dataOld[arrayCounter] & 0x000000FF));
	}

	// Iterate to find the next available memory
	int appendToIndex = 0;
	for(arrayCounter = 0; arrayCounter < sizeof(dataOldBytes); arrayCounter++){
		if(dataOldBytes[arrayCounter] == 0){
			appendToIndex = arrayCounter;
			break;
		}
	}
	// Convert data floats to ascii
	char activePowerAscii[30], reactivePowerAscii[30];
	sprintf(activePowerAscii, "%f", activePower);
	sprintf(reactivePowerAscii , "%f", reactivePower);

	// Locate where bytes begin in active power ascii array
	int indexBeginActive = 0;
	for(arrayCounter = 0; arrayCounter < sizeof(activePowerAscii); arrayCounter++){
		indexBeginActive = arrayCounter;
		if(activePowerAscii[arrayCounter] != 0){
			break;
		}
	}

	// Locate where bytes begin in reactive power ascii array
	int indexBeginReactive = 0;
        for(arrayCounter = 0; arrayCounter < sizeof(reactivePowerAscii); arrayCounter++){
                indexBeginReactive = arrayCounter;
                if(reactivePowerAscii[arrayCounter] != 0){
                        break;
                }
        }

	// Append Active Power value to data array
	for(arrayCounter = indexBeginActive; arrayCounter < sizeof(activePowerAscii); arrayCounter++){
		dataArrayBytes[appendToIndex + arrayCounter - indexBeginActive] = activePowerAscii[arrayCounter];
		appendToIndex++;
	}

	// Write a space to data array
	dataArrayBytes[appendToIndex] = 0x20;
	appendToIndex++;

	// Append Reactive Power value to data array
	for(arrayCounter = indexBeginReactive; arrayCounter < sizeof(reactivePowerAscii); arrayCounter++){
                dataArrayBytes[appendToIndex + arrayCounter - indexBeginReactive] = activePowerAscii[arrayCounter];
		appendToIndex++;
        }
	// Write a new line to the data array
	dataArrayBytes[appendToIndex] = 0x0D;
	appendToIndex++
	dataArrayBytes[appendToIndex] = 0x0A;
	appendToIndex++

	// Convert back to grouped form


