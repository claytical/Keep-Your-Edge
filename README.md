Keep-Your-Edge-OSX
==================

A simple game of avoiding circles and collecting squares.

# Playing

Click the mouse in to the area you want to move. Avoid the circles :)

# Making Levels

Using the level editor, you can create a pattern.xml file. This pattern contains coordinates for collectables and enemies. You can group these into sets which are then put into a level file.

## Level File
The level file is pretty self explanatory.
The complete number is the amount of edges you need to collect to get to the end of the level. Speed is negative because everything comes from the top down. The multiplier increments the speed each time the set of files has been ran through.

<name>Name of Level</name>
<author>You</author>
<complete>20</complete>
<speed>-1</speed>
<multiplier>1.01</multiplier>
<file>small.xml</file>
<file>triangle.xml</file>
<file>pattern.xml</file>
