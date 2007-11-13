// BSP tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/BSPTreeBuilder.h>
#include <Scene/BSPTransformer.h>
#include <Scene/CollectedGeometryTransformer.h>

namespace OpenEngine {
namespace Scene {

/**
 * Construct builder.
 */
BSPTreeBuilder::BSPTreeBuilder() {

}

/**
 * Destructor.
 */
BSPTreeBuilder::~BSPTreeBuilder() {

}

/**
 * Build a BSP tree from a scene structure.
 *
 * @param node Root node of a scene to build from.
 * @return BSP tree or NULL if no tree could be built.
 */
BSPNode* BSPTreeBuilder::Build(ISceneNode& node) {

    // create transformers
    CollectedGeometryTransformer collect;
    BSPTransformer bsp;

    // clone the scene in a new clone container
    // (needed in case build was called on a geometry node).
    SceneNode clone;
    clone.AddNode(node.Clone());

    // transform
    collect.Transform(clone);
    bsp.Transform(clone);

    // validate
    BSPNode* bspnode = NULL;
    if (clone.GetNumberOfNodes() == 1) {
        bspnode = dynamic_cast<BSPNode*>(*(clone.subNodes.begin()));
        clone.RemoveNode(bspnode);
    }

    // clone is deleted when we leave scope so we have nothing to delete.

    return bspnode;
}

} // NS Scene
} // NS OpenEngine
