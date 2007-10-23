// Hybrid Quad and BSP tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/QuadBSPBuilder.h>
#include <Scene/BSPTreeBuilder.h>
#include <Scene/QuadNode.h>
#include <Scene/QuadTreeBuilder.h>

namespace OpenEngine {
namespace Scene {

QuadBSPBuilder::QuadBSPBuilder() {}

QuadBSPBuilder::~QuadBSPBuilder() {}

/**
 * Build a hybrid quad-bsp tree.
 *
 * @see QuadTreeBuilder::Build
 * @see BSPTreeBuilder::Build
 *
 * @param node Tree to build from.
 */
QuadNode* QuadBSPBuilder::Build(ISceneNode& node) {
    // build the quad tree
    QuadTreeBuilder builder;
    QuadNode* quad = builder.Build(node);
    // accept on quad to boot strap bsp building
    if (quad!=NULL)
    quad->Accept(*this);
    // return the tree
    return quad;
}

void QuadBSPBuilder::VisitQuadNode(QuadNode* node) {
    // find quad leafs with geometry
    if (node->subNodes.size() == 1) {
        // create and add a BSP tree
        BSPTreeBuilder builder;
        node->AddNode(builder.Build(*node));
        // remove the geometry node
        node->RemoveNode(*(node->subNodes.begin()));
        return;
    }
    node->VisitSubNodes(*this);
}

} // NS Scene
} // NS OpenEngine
