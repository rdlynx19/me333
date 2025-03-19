# ME333 Assignment 9
Author: Pushkar Dave

**Ch25 Q7: You are choosing a motor for the last joint of a new direct-drive robot arm design. (A direct-drive robot does not use gearheads on the motors, creating high speeds with lowfriction.) Since it is the last joint of the robot, and it has to be carried by all the other joints, you want it to be as light as possible. From the line of motors you are considering from your favorite motor manufacturer, you know that the mass increases with the motor’s power rating. Therefore you are looking for the lowest power motor that works for your specifications. Your specifications are that the motor should have a stall torque of at least 0.1 Nm, should be able to rotate at least 5 revolutions per second when providing 0.01 Nm, and the motor should be able to operate continuously while providing 0.02 Nm. Which motor do you choose from Table 25.1? Give a justification for your answer.**

Ans: Based on the conditions specified, the stall torque must be atleast $100mNm$. The 3W motor fails this requirement, and so it cannot be used for our application. The second requirement is the speed should be alteast $300rpm$ at $10mNm$. The speed at a given torque is estimated by $$\omega = \omega_{no-load} - (\tau/\tau_{stall}) * \omega_{no-load}$$
For each remaining motor at $10mNm$, is greater than 300rpm, and so all of them can be used. And for the final requirement, the continous torque requirement is greater than $20mNm$. All of the remaining motors satisfy this requirement as well. Since, we want the lowest power rated motor (which will also be the lightest), we can choose the 10W motor for our task.

**Ch26 Q4(a): You are working for a startup robotics company designing a small differential-drive mobile robot, and your job is to choose the motors and gearing. A diff-drive robot has two wheels, each driven directly by its own motor, as well as a caster wheel or two for balance. Your design specifications say that the robot should be capable of continuously climbing a 20◦ slope at 20 cm/s. To simplify the problem, assume that the mass of the whole robot, including motor amplifiers, motors, and gearing, will be 2 kg, regardless of the motors and gearing you choose. Further assume that the robot must overcome a viscous damping force of (10 Ns/m)×v when it moves forward at a constant velocity v, regardless of the slope. The radius of the wheels has already been chosen to be 4 cm, and you can assume they never slip. If you need to make other assumptions to complete the problem, clearly state them.**

**You will choose among the 15 V motors in Table 25.1, as well as gearheads with G = 1, 10, 20, 50, or 100. Assume the gearing efficiency η for G = 1 is 100%, and for the others, 75%. (Do not combine gearheads! You get to use only one.)**

**Provide a list of all combinations of motor and gearhead that satisfy the specifications, and explain your reasoning. (There are 20 possible combinations: four motors and five gearheads.) “Satisfy the specifications” means that the motor and gearhead can provide at least what is required by the specifications. Remember that each motor only needs to provide half of the total force needed, since there are two wheels.**

Ans: Given, the angle of the slope and the mass of the robot, we can calculate the gravitational force acting on the robot using $mg\sin(\theta) = 6.71N$. Adding the force due to viscous damping to this, we have an additional force of $2N$. Therefore total force required to be exerted is $6.71 + 2 = 8.71N$

Now using, the equation $\tau = F * r$, each wheel has to provide only half the force, so the torque required comes out to be $0.1742 Nm$. Given the linear speed of motion and the radius, the angular velocity of each wheel is $5 rad/s$

Torque and velocity equations with the gear head are $\tau_{wheel} = \eta G \tau_{motor}$ and $\omega_{wheel} = \omega_{no-load}/G$

From the data sheet, for each motor we can obtain, it's no load speed and stall torque.
Using the given gear heads, and their efficiencies, when worked out, the following combinations are suitable to use:
- 10 W motor with G = 1
- 10 W motor with G = 10
- 10 W motor with G = 20
- 10 W motor with G = 50
- 10 W motor with G = 100
- 20 W motor with G = 20
- 20 W motor with G = 50
- 20 W motor with G = 100
- 90 W motor with G = 10
- 90 W motor with G = 20
- 90 W motor with G = 50
- 90 W motor with G = 100