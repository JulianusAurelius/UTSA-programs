#ifndef _graphPathAlg_h
#define _graphPathAlg_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"
#include "point2D.h"
#include "stackPoint2D.h"
#include "queuePoint2D.h"
#include "priorityQueuePoint2D.h"
#include "array2D.h"

typedef enum pathResult{ PATH_IMPOSSIBLE, PATH_FOUND, PATH_UNKNOWN } pathResult;

void printNames( );

pathResult hasPath( array2D *maze );
pathResult findNearestFinish( array2D *maze, int *spDist );
pathResult findTunnelRoute( array2D *maze, int k );

#endif
