<<--------------------------------------------------------------------------------Artificial_Intelligence_Project_03------------------------------------------------------------------------------------------>>

# Developers :
	- This project was done by Max Sherwin

# About Project :
	- The project reads the scene contents( i.e the model properties, light properties, etc) from the json file located in "Artificial_Intelligence_Project_03->GameWorldConstruct->SceneDescription.json".

	- In the scene I have placed 30 Beholders and 1 free flying camera(controlled by the user). Controls are given below.
 
	- The 30 beholders will go through flocking behaviour(considering separation force, alignment force and cohesion force).

	- I have also set a boundary of 100 units(i.e. -100 to 100). The beholders will move within this boundary box.

	- Note : The Spiderman model in the middle of the scene has nothing to do with the project, it is just to pinpoint the middle of the game scene.
	
	- I've also added a video demo explaining the simulation and code part.

## How to build and run : 
	- The solution "Artificial_Intelligence_Project_03.sln" has to be built(either in debug or release platform mode) and then once succeeded(probably will!), make the "GameWorldConstruct" project as the startup project and now it'll be able to run for some visual treat.
	- When building the solution, the "MaxGameEngine" project should be run first since it is a static project without which the project with contents(GameWorldConstruct) cannot be run.
	
### Controls :
	- W,A,S,D,Q,E for camera movement(Front, Left, Back, Right, Up and Down respectively)
	- Mouse movement for camera rotation
	- Spacebar to pause and resume mouse mouvement(by default it is set to pause, so click on Spacebar when the scene starts to rotate camera with mouse)
	- 1, 2, 3, 4, 5 buttons are default camera showcase angles.
