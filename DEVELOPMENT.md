##Development Log

####November 14, 2020

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
    - Table maintains a collection of balls as well as its own walls
    . Currently, those walls are just a simple rectangle and don't have
     pockets, so the collision logic is fairly simple. 
     
- Implemented basic SnookerApp to display moving balls and collisions.
    - Tweaked a time scale factor to slow down all balls by a factor, which
      both allows the visualization to move at a more natural speed and
      prevents tunneling issues.