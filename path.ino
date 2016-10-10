
void followPath(float path[][3], int pathLength) {
  
  //Set starting node
  updateMarker();
  float xPrev = marker.x;
  float yPrev = marker.y;
  
  //Repeat process to travel to each node
  for (int node = 0; node < pathLength; node++) {
    
    //Repeat turn/drive proces MAX_DRIVE times
    sendf(&rf, "Now traveling to Node ", node, "...");
    for (int i = 0; i < MAX_DRIVE; i++) {
      
      //Repeat turn MAX_TURN times
      for (int j = 0; j < MAX_TURNS; j++) {
        //Exexute turn
        sendf(&rf, "--Starting Turn ", j, "...");
        turnToNode(path[node][X], path[node][Y], xPrev, yPrev, E_ROT);
      }

      //Execute drive
      sendf(&rf, "-Starting Drive ", i, "...");
      driveToNode(path[node][X], path[node][Y], xPrev, yPrev, path[node][E]);

      //Reset starting node
      updateMarker();
      xPrev = marker.x;
      yPrev = marker.y;
    }
  }

  sendf(&rf, "OSV has reached its final destination!");
}
