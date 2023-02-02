# Project of Fall 2022: "Attack/Defense basket-ball game" - Group number 3 (SEAL)

## Getting started

To make it easy for you to get started with GitLab, here's a list of recommended next steps.

Already a pro? Just edit this README.md and make it your own. Want to make it easy? [Use the template at the bottom](#editing-this-readme)!

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://gitlab.eurecom.fr/nguyenk/osrobot.git
git branch -M main
git push -uf origin main
```
![SEAL LOGO](images/seal.jpeg "SEAL")


### This project is created for OS course in EURECOM. The project is to design and code an EV3 Mindstorm Lego robot to play basketball as an attacker and also a defender. For more information, you can click on this link [OS PROJECT 2022](https://perso.telecom-paristech.fr/apvrille/OS/projects_fall2022.html)


## Our Robot design
![FRONT VIEW](images/front_view.jpeg "FRONT VIEW")
![SIDE VIEW](images/side_view.jpeg "SIDE VIEW")
![REAR VIEW](images/rear_view.jpeg "REAR VIEW")
![TOP VIEW](images/top_view.jpeg "TOP VIEW")

The robot complies to the specifications given which are:

- The robot must be contained in width=30cm, length=30cm, height=35cm maximum at start-up
- The robot must contain a flag, on which the number of your group is clearly readable from at least two sides of your robot. The flag dimension is at most 10x10cm. It may also contain a logo, a drawing, and the name of the robot
- The program you run should have been totally written in C.

## Robot Components

We utilise 4 motors and 3 sensors as follows :

1. 1st Motor : Right Wheel
2. 2nd Motor : Left Wheel
3. 3rd Motor : Kicker
   - Used to kick the ball and try to score into the basket
4. 4th Motor : Grappler
   - Used as a claw which will move downwards to grab the ball and upwards to hold the ball before it is kicked by the Kicker

5. 1st Sensor : Sonar Sensor
   - We use the sonar sensor to detect the distance between the robot and the ball, hence making the robot stops in a precise distance from the ball letting the grappler hand to be able to pickup the ball and keep it 
6. 2nd Sensor : Color Sensor
   - We use the color sensor to detect the colored line in front of the defensive area. This is used both in attacking and defending. For attacking, the color sensor prevents the robot from entering the defensive area which will make it loses points while in defending the color sensor prevents the robot from leaving the defensive area. This is to let the robot navigate and circulate in the area as an act of defending the goal
7. 3rd Sensor : Gyro Sensor
   - We use the gyro sensor to help the robot moves, navigates and making turns with precise calculations and data

## Our Strategy

### Attacking
- For attacking, our strategy is to score the ball that we already have in the grappler by going straight to the colored line using the color sensor.
- After reaching the colored line, the robot will kick the ball into the basket and making a right turn facing the ball on its right
- Robot will move slowly towards the ball until the sonar sensor detects the suitable distance, making the robot stops
- Robot will then pickup the ball in front of it and turns left facing the goal once again. It will kick the ball into the basketball
- Robot turns left facing the leftside of the arena, and move slowly towards the ball on its left until the sonar sensor detects the precised distance
- Robot will pickup the ball and make a right turn facing the goal and kick the ball into it

### Defending
- For defending, we use sonar sensor and color sensor for the navigation. If the robot detects the colored line or a wall in front of it, it will turn and avoid them
- Hence, making the robot navigates and roams in the defensive area

