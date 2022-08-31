#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PlaylistNode.h"

void PrintMenu(char playlistTitle[]) {
   printf("%s PLAYLIST MENU\na - Add song\nr - Remove song\nc - Change position of song\ns - Output songs by specific artist\nt - Output total time of playlist (in seconds)\no - Output full playlist\nq - Quit\n\n", playlistTitle);
}

PlaylistNode* ExecuteMenu(char option, char playlistTitle[], PlaylistNode* headNode) {
    /* Type your code here */
    if (option == 'a')
    {
        printf("ADD SONG\nEnter song's unique ID:");
        char uniqueID[101];
        fgets(uniqueID, 101, stdin);
        uniqueID[strlen(uniqueID) - 1] = '\0';

        printf("\nEnter song's name:");
        char songName[101];
        fgets(songName, 100, stdin);
        songName[strlen(songName) - 1] = '\0';

        printf("\nEnter artist's name:");
        char artistName[101];
        fgets(artistName, 100, stdin);
        artistName[strlen(artistName) - 1] = '\0';

        printf("\nEnter song's length (in seconds):");
        int songLength;
        scanf("%d", &songLength);
        printf("\n\n");
        PlaylistNode* newNode = (PlaylistNode*)malloc(sizeof(PlaylistNode));
        CreatePlaylistNode(newNode, uniqueID, songName, artistName, songLength, NULL);
        PlaylistNode* currentNode = headNode;
        if (currentNode == NULL)
        {
            headNode = newNode;
        }
        else
        {
            while (currentNode->nextNodePtr != NULL)
            {
                currentNode = GetNextPlaylistNode(currentNode);
            }
            InsertPlaylistNodeAfter(currentNode, newNode);
        }
        char tmp[101];
        fgets(tmp, 100, stdin);
    }
    else if (option == 'r')
    {
        printf("REMOVE SONG\nEnter song's unique ID:");
        char uniqueID[100];
        scanf("%s", uniqueID);
        PlaylistNode* currentNode = headNode;
        PlaylistNode* previousNode = NULL;
        while (strcmp(currentNode->uniqueID, uniqueID) != 0)
        {
            previousNode = currentNode;
            currentNode = GetNextPlaylistNode(currentNode);
        }
        printf("\n");
        printf("\"%s\" removed.\n\n", currentNode->songName);
        SetNextPlaylistNode(previousNode, GetNextPlaylistNode(currentNode));
        free(currentNode);
        char tmp[101];
        fgets(tmp, 100, stdin);
    }
    else if (option == 'c')
    {
        printf("CHANGE POSITION OF SONG\nEnter song's current position:");
        int currentPosition;
        scanf("%d", &currentPosition);
        printf("\nEnter new position for song:");
        int newPosition;
        scanf("%d", &newPosition);
        PlaylistNode* currentNode = headNode;
        PlaylistNode* previousNode = NULL;
        PlaylistNode* prevNode = NULL;
        PlaylistNode* nodeAtPosition = headNode;
        for (int i = 0; i < newPosition - 1; i++)
        {
            prevNode = nodeAtPosition;
            nodeAtPosition = GetNextPlaylistNode(nodeAtPosition);
        }
        for (int i = 0; i < currentPosition - 1; i++)
        {
            previousNode = currentNode;
            currentNode = GetNextPlaylistNode(currentNode);
        }
        if (newPosition != currentPosition)
        {
            if (currentPosition == 1)
            {
                headNode = currentNode->nextNodePtr;
                currentNode->nextNodePtr = nodeAtPosition->nextNodePtr;
                nodeAtPosition->nextNodePtr = currentNode;
            }
            else
            {
                // if (currentNode->nextNodePtr == NULL)
                // {
                    
                // }
                // else
                // {
                    if (newPosition > currentPosition)
                    {
                        prevNode = nodeAtPosition;
                        nodeAtPosition = GetNextPlaylistNode(nodeAtPosition);
                    }
                    if (newPosition == 1)
                    {
                        previousNode->nextNodePtr = currentNode->nextNodePtr;
                        currentNode->nextNodePtr = headNode;
                        headNode = currentNode;
                    }
                    // else if (nodeAtPosition->nextNodePtr == NULL)
                    // {
                    //     previousNode->nextNodePtr = currentNode->nextNodePtr;
                    //     currentNode->nextNodePtr = nodeAtPosition->nextNodePtr;
                    //     nodeAtPosition->nextNodePtr = currentNode;
                    // }
                    else
                    {
                        previousNode->nextNodePtr = currentNode->nextNodePtr;
                        currentNode->nextNodePtr = nodeAtPosition;
                        prevNode->nextNodePtr = currentNode;
                    }
                // }
            }
        }
        printf("\n\"%s\" moved to position %d\n\n", currentNode->songName, newPosition);
        char tmp[101];
        fgets(tmp, 100, stdin);
    }
    else if (option == 's')
    {
        printf("OUTPUT SONGS BY SPECIFIC ARTIST\nEnter artist's name:");
        char artistName[100];
        fgets(artistName, 100, stdin);
        artistName[strlen(artistName) - 1] = '\0';
        printf("\n");
        PlaylistNode* currentNode = headNode;
        int count = 1;
        while (currentNode != NULL)
        {
            if (strcmp(currentNode->artistName, artistName) == 0)
            {
                printf("%d.\n",count);
                PrintPlaylistNode(currentNode);
                printf("\n");
            }
            currentNode = GetNextPlaylistNode(currentNode);
            ++count;
        }
        // printf("\n");
    }
    else if (option == 't')
    {
        printf("OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");
        PlaylistNode* currentNode = headNode;
        int totalTime = 0;
        while (currentNode != NULL)
        {
            totalTime += currentNode->songLength;
            currentNode = GetNextPlaylistNode(currentNode);
        }
        printf("Total time: %d seconds\n\n", totalTime);
    }
    else if (option == 'o')
    {
        printf("%s - OUTPUT FULL PLAYLIST", playlistTitle);
        if (headNode == NULL)
        {
            printf("\nPlaylist is empty\n\n");
        }
        else
        {
            PlaylistNode* currentNode = headNode;
            int count = 0;
            while (currentNode != NULL)
            {
                printf("\n%d.\n", ++count);
                PrintPlaylistNode(currentNode);
                currentNode = GetNextPlaylistNode(currentNode);
            }
            printf("\n");
        }
    }
    // }
    // else if (option == 'q')
    // {
    //     return NULL;
    // }
    return headNode;
}

int main(void) {
    /* Type your code here */
    PlaylistNode* headNode = NULL;
    // PlaylistNode* tail = NULL;
    char playlistTitle[100];
    printf("Enter playlist's title:");
    fgets(playlistTitle, 100, stdin);
    playlistTitle[strlen(playlistTitle) - 1] = '\0';
    char option = 'X';
    char tmp[100];
    printf("\n\n");
    while (option != 'q')
    {
        PrintMenu(playlistTitle);
        printf("Choose an option:\n");
        fgets(tmp, 100, stdin);
        option = tmp[0];
        headNode = ExecuteMenu(option, playlistTitle, headNode);
    }
    return 0;
}