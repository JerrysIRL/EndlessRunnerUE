# **Endless Runner**
_Endless Runner_ is a local multiplayer 3D game made in Unreal Engine 5.1 using C++. The goal of the game is to run and avoid obstacles for as long as possible while collecting coins. As the game progresses, the difficulty increases, making it more challenging to survive.

## Mechanics
Endless Runner features several game mechanics, including:

- **Object Pooling**: The game uses object pooling to efficiently spawn and move platforms. A pool of pre-allocated platform objects is created at the start of the game, and these objects are reused as needed instead of creating new ones. This helps to reduce memory allocation and improve performance. The system is controlled by the custom GameMode class, which stores the last platform and a BoxTrigger behind the player. When the player collides with the trigger, the platform moves to the end line.
- **Basic Movement**: The player can move left and right as well as crouch and jump. The movement is handled by a custom character movement system implemented in a Pawn C++ class.
- **Increasing difficulty**: As the game progresses, the speed of the game increases, making it more difficult and exciting to play.
- **Obstacles / Projectiles** : The game includes three different types of obstacles: obstacles, coins, and medpacks. The obstacles are randomized using a shuffle algorithm. Obstacles are implemented as a subclass of the BaseMover class, which handles movement towards the player for both platforms and obstacles. 
- **Score Counter and Player Health**: A score counter and player health system are be implemented to add more depth to the gameplay.

# Object-Oriented Design
  Endless Runner was designed using an object-oriented approach, which helped to make the code more modular and reusable. Each game mechanic is implemented as a separate class, with clear interfaces and responsibilities. This approach ensures that each class has only one responsibility and minimizes the risk of code duplication and coupling. Additionally, data is sealed off from other classes to prevent unintended modification.
 
  The game loop functionality is sealed off in the custom GameMode class (Game Manager), which manages the spawning of platforms, obstacles, and power-ups, as well as the increasing difficulty. This design decision makes it easy to iterate on the game in the future, as it centralizes the game logic in one place and allows for easy modification and extension.

 Overall, the object-oriented design of Endless Runner helps to keep the code organized, maintainable, and scalable.


## Usage
Use the following controls to play the game:
| Controls Player 1 | Explanation |
| ------ | ------ |
| A and D |  moving left and right | 
| W |  jumping | 
| S |  crouching | 


- Each coin adds 15 points to the score

## Installation
To install and play Endless Runner, simply download the latest release from the "Release" section on the GitHub repository page and launch the executable.
