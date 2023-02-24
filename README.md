# Assignment2COP4520 Minotaur part 1
It is important to know that part 1 and part 2 have been separated into two files they have to be run separately for part 1.
Compile using
g++ assignment2problem1.cpp
To see output to terminal do command
.\a.exe    
If using visual studio codes just do those commands into the terminal after having c++ extensions and only have 1 file in there at a time.

# Description of part 1 
The Minotaur invited N guests to his birthday party. When the guests arrived, he made the following announcement.

The guests may enter his labyrinth, one at a time and only when he invites them to do so. At the end of the labyrinth, the Minotaur placed a birthday cupcake on a plate. When a guest finds a way out of the labyrinth, he or she may decide to eat the birthday cupcake or leave it. If the cupcake is eaten by the previous guest, the next guest will find the cupcake plate empty and may request another cupcake by asking the Minotaur's servants. When the servants bring a new cupcake the guest may decide to eat it or leave it on the plate.

The Minotaur's only request for each guest is to not talk to the other guests about her or his visit to the labyrinth after the game has started. The guests are allowed to come up with a strategy prior to the beginning of the game. There are many birthday cupcakes, so the Minotaur may pick the same guests multiple times and ask them to enter the labyrinth. Before the party is over, the Minotaur wants to know if all of his guests have had the chance to enter his labyrinth. To do so, the guests must announce that they have all visited the labyrinth at least once.

Now the guests must come up with a strategy to let the Minotaur know that every guest entered the Minotaur's labyrinth. It is known that there is already a birthday cupcake left at the labyrinth's exit at the start of the game. How would the guests do this and not disappoint his generous and a bit temperamental host?

Create a program to simulate the winning strategy (protocol) where each guest is represented by one running thread. In your program you can choose a concrete number for N or ask the user to specify N at the start.
# Approach and solution
First i made sure to only have 10 guests it is a concrete number however if user wants to change they would have to edit the code and switch N=10 to whatever number they desire and code will still work. N in this case represents guests, I have this in a thread array and then have them all run a function to enter labyrinth in a for loop. Once they all activate it is random which one goes first as they all run parallel and once one makes it the thread is lock and once its unlock they all race again to execute. Have ityt to make it so that each guests only eats cupcake once and leaves plate empty so others can request and once they they all eat the cupcake once it will check if they all ate cupcake by the end of runtime.There is a counter for who eats the cupcake so that they dont communicate with each other and are able to know when they all entered at least once.

# Minotaur part 2 
To compile this problem its same process as above but for compiling use 
g++ assignment2problem2.cpp
and to run it use
.\a.exe same as above
# Description 
The Minotaur decided to show his favorite crystal vase to his guests in a dedicated showroom with a single door. He did not want many guests to gather around the vase and accidentally break it. For this reason, he would allow only one guest at a time into the showroom. He asked his guests to choose from one of three possible strategies for viewing the Minotaur's favorite crystal vase:

Any guest could stop by and check whether the showroom's door is open at any time and try to enter the room. While this would allow the guests to roam around the castle and enjoy the party, this strategy may also cause large crowds of eager guests to gather around the door. A particular guest wanting to see the vase would also have no guarantee that she or he will be able to do so and when.

The Minotaur's second strategy allowed the guests to place a sign on the door indicating when the showroom is available. The sign would read "AVAILABLE" or "BUSY." Every guest is responsible to set the sign to "BUSY" when entering the showroom and back to "AVAILABLE" upon exit. That way guests would not bother trying to go to the showroom if it is not available.

The third strategy would allow the quests to line in a queue. Every guest exiting the room was responsible to notify the guest standing in front of the queue that the showroom is available. Guests were allowed to queue multiple times.

Which of these three strategies should the guests choose? Please discuss the advantages and disadvantages.

Implement the strategy/protocol of your choice where each guest is represented by 1 running thread. You can choose a concrete number for the number of guests or ask the user to specify it at the start.
# Approach and solution
Use method two for these problem as it goes hand in hand with problem one without needing a counter. For this i just had it make threads based on guest then after this have a set where it checks which guests have seen the vase and they arent allowed to look at the vase more than once.
Advantage of this is that it is very easy to implement and easy to understand.
Disadvantages are that we really cant tell the runtime as it will randomly have threads go into the room.
