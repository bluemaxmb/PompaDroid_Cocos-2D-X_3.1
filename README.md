This project is a port of the finished tutorial found at 

http://www.raywenderlich.com/24155/how-to-make-a-side-scrolling-beat-em-up-game-like-scott-pilgrim-with-cocos2d-part-1 and http://www.raywenderlich.com/24452/how-to-make-a-side-scrolling-beat-em-up-game-like-scott-pilgrim-with-cocos2d-part-2

from Cocos-2D version 2.0 to Cocos-2D-X version 3.1 rc1.

I have attempt to retain the majority of the structure of the original tutorial (with some name changes to variables because of coding standard habits I can't let go of). If you read the original tutorial most of the logic in this tutorial should still make sense. The current biggest departure is with the way the D-Pad works. CCTargetedTouchDelegate has been deprecated and as I have yet to find a sufficient replacement I had to make some work arounds. The original tutorial put the delegate callbacks in the GameLayer. While I probably could've done something similar I decided to remove a level of indirection by passing a pointer to the Player to the D-Pad, the D-Pad then makes direct calls on the Player. In all honesty this isn't the best and isn't something that would go over well in professional code (although I have seen similar approaches in games that did ship), but I think for a learning example like this it is kind of okay.

The original tutorial makes heavy use of the Cocos macro CCARRAY_FOREACH, this macro still exists, however the Cocos array class has changed and doesn't seem to be compatible with this macro in the way the original author used it. It is possible my C++ is rusty and I'm just missing something here. I've replaced all instances of this macro with Vector iterators. Its the same idea and probably a little clearer what is happening.

CACurrentMediaTime is an Apple specific API call, I've replaced it with the function CURTIME which makes use of the standard time function.

For the moment Defines.h is only included where needed, not in the PCH.

There seems to be some issues with the collision detection. It seems to arise from the difference in how Cocos rectangles work vs how CGRects work. I will attempt to have it fixed in the next few days. I checked the code in with Robots set to 1 and the first Robot spawning near the player to work on this. If you want to enable more robots with random spawn locations look at the code in initTheRobots.

I also need to figure out why the art only takes up half the screen. The original uses:

	if( ! [director_ enableRetinaDisplay:NO] )
		CCLOG(@"Retina Display Not supported");
		
And this has been deprecated out of existence with no replacement that I've identified.
