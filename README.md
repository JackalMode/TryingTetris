# M4OEP-msteenbe
### Mitchell Steenbergen
### Installation
To run this program you will need:
* SFML: Download SFML from here https://www.sfml-dev.org/download/sfml/2.6.2/ specifically the GCC 13.1.0 64-bit. Then in the CMakeLists.txt set the SFML root director to: set(SFML_ROOT "Folder location of SFML"). Replace "Folder loaction of SFML" with the path where you extracted/downloaded the SFML folder. 
### Program Summary
This is Tetris. It includes classic Tetris gameplay, allowing for user movement such as, moving side to side, rotating, and dropping it down. The pieces fall automatically, rows will clear when full. It includes multiple game screens including a start, pause, and game over screen.
### Known Bugs
No known bugs at time of submission
### Future Work
With more time, the following features could be added:
* Score tracking: Displaying points gained during the game
* High Score tracking: Display and store the highest scores achieved
* Difficulty Levels: Add different difficulty settings that increase the game's speed
* Upcoming blocks: Have a screen off to the side that will show the next block in rotation.
* Sounds effects and music: this could enhance the experience by adding some sound and music. 
### Citations
* SFML Documentation and Community: Used for guidance of this project. 
### Grade
* Main Program Complexity and Usability (40 points):
  * The program demonstrates complexity through features such as tetromino spawning, movement, rotation, collision handling, row clearing, multiple screens, and wall kicks. It also includes various Module 4 concepts including, Keyboard inputs, non-input-based events (constant falling), multiple screens (start, Play, Pause, GameOver), a graphics framework(SFML), and drawing (The tetrominos).
* Interactivity of Program (20 points):
  * The program responds smoothly to keyboard inputs for moving, rotating, and dropping pieces. It includes functionality to pause, play, and exit the game. Providing a fully interactive and responsive experience for the user. 
* User Experience (20 points):
  * The program includes multiple screens that are consistent and user-friendly (start, pause, play, and game over). They transition smoothly between each state and on-screen instructions explain the controls. The gameplay is smooth, responsive, and doesn't feel sluggish to play. 
* Code Organization (20 points):
  * The code is well organized into multiple files each dedication to a specific part of the game, such as, Engine, Tetromino, Rotation, and Screens. The code is also divided into folders, making the structure easier to navigate and extend in the future. 