bool tour(int S, int F, Queue* itinerary)
{
    // Declare variables
    ver[S]->visited = 1; //the declaration should have ver as a pointer to a vertex
    int i;
    int k=0;

    if (S == F)
    {
        return true;
    }

    // Find the nodes adj to S
    for (i=0; i<NUMNODES; i++)
    {
        if (adj[S][i] == 1)
        {
            if (ver[i]->visited == 0)
            {
                if (ver[i]->isPOI == 1)
                {
                    k = tour(i, F, itinerary);
                    if (k == 1)
                    {
                        return true;
                    }
                }
            }
        }
    }
    for (i=0; i<NUMNODES; i++)
    {
        if (adj[S][i] == 1)
        {
            if (ver[i]->visited == 0)
            {
                k = tour(i, F, itinerary);
                if (k == 1)
                {
                    return true;
                }
            }
        }
    }




    // Return bool indidcating whether you found F yet
    return false; // I decided to return true values higher in the program to prevent the loop from running unnecessarily
}