## Development Log

#### November 14, 2020

- Implemented basic functionality of Ball class.
    - Ball maintains its position, velocity, color, mass, and radius. Mass
      and radius likely aren't to be directly used in this project, as all
      snooker balls have the same mass and radius; however, the class becomes
      more flexible by taking these values as parameters. It might be
      worthwhile to make them take default constant values.
    - Ball updates its own position under the influence of slight
      translational friction, proportional to some rolling resistance between
      the table cloth and the ball.
    - Ball has a coefficient of restitution of 0.95 for collisions with the
     wall, making the ball lose velocity when it collides with the wall.
    - Currently, the collisions between balls are perfectly elastic, but
      perhaps I'll work on a computation for inelastic collisions.

- Implemented basic functionality of Table class.
    - Table maintains a collection of balls as well as its own walls.
      Currently, those walls are just a simple rectangle and don't have
      pockets, so the collision logic is fairly simple. 
     
- Implemented basic SnookerApp to display moving balls and collisions.
    - Tweaked a time scale factor to slow down all balls by a factor, which
      both allows the visualization to move at a more natural speed and
      prevents tunneling issues.
      
#### November 15, 2020

- Designed TableCushion abstract class with StraightCushion and CurvedCushion
 subclasses, representing the different types of cushions on a snooker table.
    - StraightCushion uses rectangular collision logic, while CurvedCushion
     uses circular collision logic. Both apply the coefficient of restitution
      of 0.95.
    - Because Cinder does not implement a CircleT analogue to RectT, the
     CurvedCushion data members must be maintained directly (i.e., a position
      and radius).
- Implemented basic UI elements of TableCushion subclasses to SnookerApp.

#### November 17, 2020

- Modified application of friction on Ball.
    - Previously, friction would decrease the magnitude of both components of
     velocity by a constant deceleration due to friction. In reality, 
     however, the friction on a single component of the velocity is proportional to
      the relevant magnitude of that component. Using sines and cosines of
       the angle between the components allows for this.
  
- Implemented unit tests to validate functionality of each class.

#### November 18, 2020

- Modified pointer usage to smart pointers.
    - Smart pointers handle memory management for their respective objects
    , simplifying the design and improving the flexibility (i.e., fewer snags
     to fall into for someone extending this project.)
     
- Moved logic to set up standard snooker table into Table class.
    - Reducing the amount of code in the SnookerApp class allows for more
     comprehensive testing and better separation of front-end and back-end.
     
 - Added additional unit tests to tackle some edge cases not covered in the
  initial batches of unit tests.
  
#### November 19, 2020

- Implemented code to initially spot all standard snooker balls onto the
  table at the beginning of the game.
    - Currently, all balls are stationary except the cue ball, which moves
      towards the pyramid of reds upon running the SnookerApp for
      demonstration purposes.
    - In games of snooker, the player to break has the ability to move the
      cue ball so long as it stays behind the baulk line. The cue ball
      in the SnookerApp currently cannot be moved (or stroked with varying
      strength/angle), but these are features slated for week 2. 
      
      
#### November 27, 2020

- Implemented elementary cue movement functionality.
    - Player can interact with the cue by pressing down the left mouse button
      and dragging, and then releasing the LMB to stroke the cue.

    - Cue applies velocity to cue ball proportional to the amount it is
      pulled back.
      
#### November 28, 2020
 
- Integrated cue functionality with front-end visualizer.
    - Cue follows player's mouse on visualizer, allowing the user to modify
       the angle of his/her shot.
    - Imposed maximum cue pull back to prevent unrealistically powerful shots.
      
#### November 29, 2020

- Designed GameEngine class to maintain snooker rules.
    - Governs game flow and imposes rules of snooker upon the Players.
    
- Designed Player class to maintain any player-specific fields to be used in
  a game of snooker.
    - Player can determine if the next ball to strike/pocket is red or
      colored, can determine whether or not a shot is legal, and handles the
      implementation of either passing the cue to the other player or
      stroking again.
      
- Designed Pocket class to handle functionality of snooker pockets.
    - A Ball will be pocketed in a given pocket if the Ball's center of mass
      is within the pocket. The GameEngine and Table handle the logic behind
      removing a Ball from the Table, and respotting it when necessary.
      
- Integrated new back-end functionality with front-end visualization.
    - Implemented drawing of Pockets onto visualizer.
    - Implemented deletion/redrawing of Balls as they are pocketed/respotted
      , respectively.
      
#### November 30, 2020

- Resolved bugs relating to pocketing and respotting Balls by modifying
  risky use of pointers.

- Rearranged code to improve modularity and OOP design.

#### December 1, 2020

- Refactored code to delete obsolete code artifacts.

- Wrote formal unit tests to rigorously validate functionality implemented in
  GameEngine, Player, and Pocket classes, as well as any new functionality in
  existing classes.
  
#### December 2 & 3, 2020

- Wrote additional edge case unit tests for GameEngine, Player, and Pocket
  classes.

#### December 5, 2020

- Implemented elementary CPU strategy, in which the CPU attempts to pocket
  the nearest legal Ball in the Pocket nearest the object Ball.
    - CPU determines the position to strike on the object Ball such that the
      object Ball will follow a path from its current position to the center
      of the chosen Pocket. This specific shot-making technique allows the
      CPU to make relatively straight shots, while still keeping an element
      of randomness in its handling of difficult/non-obvious shots. 
      
#### December 6, 2020

- Modified Player classes to maintain their scores, which are updated by the
  GameEngine as appropriate.
 
- Modified visualizer to display Player scores and the Player whose turn it
  currently is.
  
#### December 7, 2020

- Designed endscreen to be displayed on the visualizer once a game has ended.

- Resolved issue in determining if a stroke is legal.
    - When determining the legality of a stroke, certain Table parameters (i
      .e., number of red Balls on the Table, least value color on the Table
      ) must be taken before the stroke is performed, not after. Doing so after
      the stroke will produce invalid results.
      
- Wrote elementary unit tests to validate CPU functionality in
  GameEngine class.
  
#### December 8, 2020

- Wrote unit tests to validate score-keeping in Player class.

- Wrote edge case tests and added rigor to previously written tests.