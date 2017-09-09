#include "header.h"

Node *makeNode(Record passedRecord) {

	//making a doubly linked node
	Node *newNode;

	//allocate memory for the Node
	newNode = (Node *)malloc(sizeof(Node));

	//check if node created successfully
	if (newNode != NULL) {

		//set the data fields
		strcpy(newNode->data.artist, passedRecord.artist);
		strcpy(newNode->data.albumTitle, passedRecord.albumTitle);
		strcpy(newNode->data.songTitle, passedRecord.songTitle);
		strcpy(newNode->data.genre, passedRecord.genre);
		newNode->data.songLength = passedRecord.songLength;
		newNode->data.numberOfPlays = passedRecord.numberOfPlays;
		newNode->data.rating = passedRecord.rating;


		//initialize the next and previous pointers before returning
		newNode->next = NULL;
		newNode->previous = NULL;

	}


	return newNode;
}

Record processLine(char line[]) {

	char *currentValue, *currentDuration;
	char lineCopy[100] = "";
	Record tempRecord;
	char fullName[25];

	char *ptr; //needed for strtod

	//int needed for comparison for artist and line length
	int lineLength = strlen(line);

	//preserve the original line by copying the passed line to our local currentLine variable
	strcpy(lineCopy, line);






	//Artist
	//check must be made for artists with FIrst and Last name VS. Single moniker
	//get (or attempt to get) a token with quotation marks
	currentValue = strtok(lineCopy, "\"");

	//Artist goes by a single Moniker
	if (strlen(currentValue) == lineLength) {
		//single moniker name
	
		//testing
		//Resetting the line for use with strtok
		strcpy(lineCopy, line);

		//grab the single name
		currentValue = strtok(lineCopy, ",");

		//set the artist name

		strcpy(tempRecord.artist, currentValue);
		//tempRecord.artist = currentValue;

	}
	else {
		//Artist goes by a first and last name
		//set the artist name
		strcpy(tempRecord.artist, currentValue);
		//tempRecord.artist = currentValue;
	}





	//Album Title
	//get the album title
	currentValue = strtok(NULL, ",");

	//set the value in the record
	//tempRecord.albumTitle = currentValue;
	strcpy(tempRecord.albumTitle, currentValue);



	
	//Song Title
	//get the song title
	currentValue = strtok(NULL, ",");

	//set the value in the record
	//tempRecord.songTitle = currentValue;
	strcpy(tempRecord.songTitle, currentValue);



	//Genre
	//get the genre
	currentValue = strtok(NULL, ",");

	//set the value in the record
	//tempRecord.genre = currentValue;
	strcpy(tempRecord.genre, currentValue);



	//Song Length
	//get the song duration
	//different variable being used here so as not to currupt the values
	//Setting the variable here but will not set the value into the record until after plays and rating
	currentDuration = strtok(NULL, ",");




	//Number of Plays
	currentValue = strtok(NULL, ",");

	//set the value in the record after casting (int <--- double)
	tempRecord.numberOfPlays = (int)strtod(currentValue, &ptr);




	//Rating
	//get the rating
	currentValue = strtok(NULL, ",");

	//set the value in the record after casting (int <--- double)
	tempRecord.rating = (int)strtod(currentValue, &ptr);
	



	//Duration part 2
	//send currentDuration to our processor function
	//set our tempRecord.duration values by setting it's value to 'Duration' type struct that will be returned*/
	tempRecord.songLength = processDuration(currentDuration);



	//return the Record struct
	return tempRecord;
}

Duration processDuration(char* stringDuration) {

	Duration tempDuration;
	int tempMinutes = 0, tempSeconds = 0;
	char *ptr, *stringDurationCOPY;

	char minutes[10];

	strcpy(minutes, stringDuration);

	stringDurationCOPY = minutes;

	//add a ":" to the end of the string. This will make tokenizing easier
	strcat(stringDurationCOPY, ":");

	//grab the minutes by casting (int <-- double) the token from stringDuration
	tempMinutes = (int)strtod(strtok(stringDurationCOPY, ":"), &ptr);

	//do the same for setting the seconds
	tempSeconds = (int)strtod(strtok(NULL, ":"), &ptr);

	//set the minutes and seconds values into the tempDuration that will be returned
	tempDuration.minutes = tempMinutes;
	tempDuration.seconds = tempSeconds;

	//return the Duration struct
	return tempDuration;

}

void insertSong(Node **list, Record songRecord) {

	//Node worker variable
	Node *tempNode = NULL;

	//Pointers to be used for insertion
	Node *pExisting = NULL, *pNew = NULL;

	//Create node for insertion
	tempNode = makeNode(songRecord);


	//Inserting into an empty list
	if (*list == NULL) {

		(*list) = tempNode;
	}
	//Inserting into non-empty list
	else {

		//Set my current pointer to the node in the list
		pExisting = *list;

		//Set my previous pointer to the node we just created
		pNew = tempNode;

		//Update the new pointer's 'next' to the existing node
		pNew->next = pExisting;

		//Update the existing item in the list's 'previous' pointer to the new node
		pExisting->previous = pNew;

		//Update the new pointer's "previous" to NULL (should be already set by default, but just being extra careful
		pNew->previous = NULL;

		//Set the list to point to the newest node in the list
		*list = pNew;

	}
	
}

void printList(Node *list) {

	printf("--> ");
	while (list != NULL)
	{
		printf("%s --> ", list->data.songTitle);
		list = list->next;
	}
	putchar('\n');


}