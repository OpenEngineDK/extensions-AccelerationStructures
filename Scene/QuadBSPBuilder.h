// Hybrid Quad and BSP tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _QUAD_BSP_TREE_BUILDER_H_
#define _QUAD_BSP_TREE_BUILDER_H_

#include <Scene/QuadNode.h>

namespace OpenEngine {
namespace Scene {

// forward declarations of node types
class ISceneNode;

/**
 * Hybrid Quad and BSP tree builder.
 *
 * @class QuadBSPBuilder QuadBSPBuilder.h Scene/QuadBSPBuilder.h
 */
class QuadBSPBuilder {
public:
    QuadBSPBuilder();
    ~QuadBSPBuilder();
    QuadNode* Build(ISceneNode& node);
};

} // NS Scene
} // NS OpenEngine

#endif // _QUAD_BSP_TREE_BUILDER_H_
