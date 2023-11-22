This was a procedural simulation I developed after being inspired by Dwarf Fortress. 
It procedurally generates a world, populates the world with settlements and creates markets for those settlements based on the availability of resources. 
It was developed in C++. As of this moment, it generates a world as described. 
I finished at this point because continuing would involve developing an AI for around 1200 agents.


World generation

The map is procedurally generated in Map.cpp using Perlin noise to create height maps. Rivers are generated in random locations use random walk until they hit a body of water.


Settlements 

In the figure above the brown patches represent human settlements, with the red dot in the centre representing the city. 
After the map has been generated, cities are then placed. 
Each city is place in the highest resource spot available if there are no other cities nearby. 
The settlement is then placed within one days travel of the city. 
This is why you see settlements place nearby water sources as they are quicker to travel along.

Markets and price predictions
When it comes to price predictions the model I use predicts what the value of each resource through the following algorithm

1.	List out the required resources (food, water, etc)
2.	Start by setting all prices equal and sort the available jobs by the highest producers
3.	It then iterates through adjusting prices until an equilibrium is met where supply matches demand

The project also handles some future market simulations.

Misc.

The graphics were written using an SMFL library to display.
