# project2-part2-asimak4
project2-part2-asimak4 created by GitHub Classroom

For this project, I worked very hard on the development of correctly moving the chess pieces, making sure that the user moves are valid, checking for mate and check, cpu moves are valid, and making sure that the user formatted the input correctly. 

I did not have time to continue working with the extra credit of this assigment, due to the weight of my other classes, but I completed everything to the full potential during this project. I also did not add any other commands other than the 00 - 04 which are described in the rubric.

I have layed out exactly how i developed and implemented the chess program in my design.pdf in this repository but i basically just went with the rubric step by step implementing the 00 - 04 in order and making sure i validated each move and the input coming in from the user. 

For the CPU's random movement, I chose to implement it like this: Chooseing a random piece to move, make then pick a random number out of that number of pieces, then randomely pick a destination of that piece, so i have the original location and where i am trying to move it. Then i put those values into a function called validmoves where it tells me if it is a valid more or not and if it is not a valid move, i then continue the loop and have it repeat those steps until a valid move is found. This works well and i also make sure to check for the "check" and if it is putting its pieces into the check position, and if so i restart the loop aswell.  

Also, i want to give a big shoutout and thank you to John the TA for making the server/viewer for the chess modoule because it helped with the visualization and made playing the game much more fun during develpment. 

