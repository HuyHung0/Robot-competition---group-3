# I. Robot setup and installation
All installation guide and examples are provide in the course link
[https://perso.telecom-paristech.fr/apvrille/OS/projects_fall2022.html](https://perso.telecom-paristech.fr/apvrille/OS/projects_fall2022.html)

This part is a recap.

1. Cross compilation
- Install docker
- 
```bash
sudo apt-get install docker-ce
sudo groupadd docker
sudo gpasswd -a ${USER} docker
sudo service docker start
sudo docker pull ev3dev/debian-jessie-armel-cross:latest
```
Some remarks:
 - We need to install docker-ce instead of docker-engine.
 - It seem that we can not run docker even if we create a group for docker and add us to the group.
 ![](screenshots/screenshot_06-01-2023_12h05m26.png)
 The last command need to run with sudo
 ![](screenshots/screenshot_06-01-2023_12h08m47.png)

 