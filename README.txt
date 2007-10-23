Author: OpenEngine Team

Homepage: http://www.openengine.dk/wiki/Extensions/AccelerationStructures

Get the latest version with:
  darcs get http://daimi.au.dk/~cgd/extensions/AccelerationStructures

This is a bundle extension for scene graph transformations and thereby 
optimizing the scene graph structure for different purposes.
With this extension you can easily build a quad tree structure representing
the entire scene. Combined with frustum clipping you can indeed accelerate the 
rendering process. You can also build a BSP (Binary Space Partitioning) tree
which has a lot of advantages eg. rendering back-to-front or locating the
intersection face for collision detection or physics calculations.
The quad and BSP tree can both be used in a hybrid approach.

If you plan on adding new node types checkout this wiki to see how you
easily can auto generate boilerplate code in the visitor. It's for your own
convenience: 

http://www.openengine.dk/wiki/CreatingExtensions#VisitorExpansion.txt 
