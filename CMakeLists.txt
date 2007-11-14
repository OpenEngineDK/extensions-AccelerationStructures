
ADD_LIBRARY(Extensions_AccelerationStructures
  # quad stuff
  Scene/QuadNode.cpp
  Scene/QuadTransformer.cpp
  Scene/QuadTreeBuilder.cpp
  # bsp stuff
  Scene/BSPNode.cpp
  Scene/BSPTransformer.cpp
  Scene/BSPTreeBuilder.cpp
  #Scene/BSPFindDividerStrategy.cpp
  #Scene/BSPPartitionStrategy.cpp
  # other things
  Scene/ASDotVisitor.cpp
  Scene/QuadBSPBuilder.cpp
  Renderers/AcceleratedRenderingView.cpp
)

TARGET_LINK_LIBRARIES(Extensions_AccelerationStructures
  OpenEngine_Renderers
  OpenEngine_Scene
)
