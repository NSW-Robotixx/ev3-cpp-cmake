# Robot Pathfinder

This project is to simplify the process of navigating the field in the FLL through primitives. These should use coordinates to specify the desired destination and then use Pathfinding algorithms to calculate the path there.

## Namespaces

### [finder::physical](./physical/physical.md)

Everything that has to to with something on the outside of the Robot is located here. For example:

- Motors
- Sensors
- Screen
- Buttons

### [finder::console](./console/console.md)

The classes interfacing with the console belong here. Currently the list is very short:

- Logger

### [finder::robot](./robot/robot.md)

This namespace is designed to be used by the enduser to interface with the robot. This is the most user-friendy class. 

> This class is mostly still in development and not ready yet