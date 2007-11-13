// BSP tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _BSP_TREE_BUILDER_H_
#define _BSP_TREE_BUILDER_H_

#include <Scene/BSPNode.h>

namespace OpenEngine {
namespace Scene {

// forward declarations of node types
class GeometryNode;
class ISceneNode;

/**
 * BSP tree builder.
 *
 * @class BSPTreeBuilder BSPTreeBuilder.h Scene/BSPTreeBuilder.h
 */
class BSPTreeBuilder {
public:
    BSPTreeBuilder();
    ~BSPTreeBuilder();
    BSPNode* Build(ISceneNode& node);
};

} // NS Scene
} // NS OpenEngine

#endif // _BSP_BUILDER_H_
