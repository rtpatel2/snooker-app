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