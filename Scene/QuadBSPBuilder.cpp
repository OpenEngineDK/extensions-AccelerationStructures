// Hybrid Quad and BSP tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/QuadBSPBuilder.h>
#include <Scene/QuadNode.h>
#include <Scene/CollectedGeometryTransformer.h>
#include <Scene/QuadTransformer.h>
#include <Scene/BSPTransformer.h>

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
    // create transformers
    CollectedGeometryTransformer collect;
    QuadTransformer quad;
    BSPTransformer bsp;

    // clone the scene in a new clone container
    // (needed in case build was called on a geometry node).
    SceneNode clone;
    clone.AddNode(node.Clone());

    // transform
    collect.Transform(clone);
    quad.Transform(clone);
    bsp.Transform(clone);

    // validate
    QuadNode* qnode = NULL;
    if (clone.GetNumberOfNodes() == 1) {
        qnode = dynamic_cast<QuadNode*>(*(clone.subNodes.begin()));
        clone.RemoveNode(qnode);
    }

    // clone is deleted when we leave scope so we have nothing to delete.

    return qnode;
}

} // NS Scene
} // NS OpenEngine
