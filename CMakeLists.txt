
ADD_LIBRARY(Extensions_AccelerationStructures
  Renderers/AcceleratedRenderingView.cpp
  Scene/QuadNode.cpp
  Scene/QuadTreeBuilder.cpp
  Scene/BSPNode.cpp
  Scene/BSPTreeBuilder.cpp
  Scene/QuadBSPBuilder.cpp
)

TARGET_LINK_LIBRARIES(Extensions_AccelerationStructures
  OpenEngine_Renderers
  OpenEngine_Scene
)
