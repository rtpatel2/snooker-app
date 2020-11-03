## Final project proposal
I would like to create an interactive game of snooker.

### Background

Snooker is a cue sport, a category including games like 8-ball pool; however, the rules of snooker are fairly unique from those of 8-ball pool. While there are a handful of fairly popular 8-ball pool emulators online, there are fewer for snooker. I've developed an interest for cue sports over the last few years, and would enjoy implementing the complex pieces of physics (at least, complex relative to the Ideal Gas MP) that go into governing the collisions/ball movement of the game, as well as implementing the core game rules.

### Timeline

Week 1:
- Implement physics governing ball movement (e.g., friction with table, slightly inelastic collisions)
- Implement the table, and the physics governing collisions with the sides of the table (e.g., straight edges, curved sections near pockets, pockets)
- Implement a cue, and allow it to exert force upon a cue ball depending on some sort of changeable "strength".

Week 2:
- Implement game rules (e.g., order in which balls must be pocketed, replacing balls, points, scratching)
- Implement basic AI player, perhaps one that just tries to pocket the nearest correct-colored ball.

Week 3:
- Design a GUI in Cinder to display game components (e.g., drawing a table, cue, colored balls)
- Design win/loss screens
- Maintain game/score history for the player

Stretch goals:
- Implement game rules/AI player for other cue sports, since most of the logic will already exist from the snooker piece.
- Some sort of web-hosting to allow for multiplayer, or simply local multiplayer (i.e., on one computer).
