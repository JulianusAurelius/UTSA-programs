#ifndef PLAYLISTNODE_H
#define PLAYLISTNODE_H
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct PlaylistNode {
    char uniqueID[50];
    char songName[50];
    char artistName[50];
    int songLength;
    struct PlaylistNode* nextNodePtr;
} PlaylistNode;

void CreatePlaylistNode(PlaylistNode* thisNode, char[], char[], char[], int, PlaylistNode* nextNode);
void InsertPlaylistNodeAfter(PlaylistNode* thisNode, PlaylistNode* newNode);
void SetNextPlaylistNode(PlaylistNode* thisNode, PlaylistNode* newNode);
PlaylistNode* GetNextPlaylistNode(PlaylistNode* thisNode);
void PrintPlaylistNode(PlaylistNode* thisNode);

#endif