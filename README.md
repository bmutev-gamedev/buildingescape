# Building Escape
---
This repository houses my game project for a puzzle type game Building Escape. This game was started during my course at Udemy - "The Unreal Engine Developer Course - Learn C++ & Make Games", found [here](https://www.udemy.com/unrealcourse?couponCode=GitHubDiscount), led by Ben Tristem and Sam Pattuzzi. Later I have built upon it a bit and as of now this is not yet a full fledget game. It is missing quite a bit of things such as a game menu, an options menu, more levels, atleast a basic multiplayer and so on.

## The Game
The game is played from a first person perspective. The goal is for the player to find a way to reach and interact with a console found in a chamber room. To do that, the player has to move and place objects at certain places, interact with objects in certain sequence so that the door between rooms can be opened. In the end of the level the player has to deactivate a sphere field around the console to reach it.

## General classes overview
#### Grabber and Toucher 
Thsese two are component classes used by the player pawn to interact with the objects found in game. 
The Grabber class, as its name sates, is used to make a check if the object has any physics active and if so to continuously simulate a grab by changing the position of the grabbed object to the end of the tracing line of the pawn.
The Toucher in simmilar way checks for objects that are of certain type and are marked with specific tag. But for this component to work it also implements an interface class - ReactsOnTouch. This interface is used to communicate private states to other classes.

#### DoorOpen and ChamberDoorOpen
These two component classes are responsible for monitoring the triggers asociated with them and sending event messages to the door blueprint to which they are attached, thus controlling the door opening or closing actions.

#### LighUpLamp
This component class is used by lamps so that they can be controlled. This component also uses an interface(LampState) for state sharing later when needed.

#### ChamberConsole
This is the base class for the chamber console. It is responsible for monitoring the states of the lamps found in the chamber room and to interact with the sphere field around the console.
