// Binary Space Partitioned tree transformer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include<Scene/BSPTransformer.h>

namespace OpenEngine {
namespace Scene {

BSPTransformer::BSPTransformer() {
    findStrategy = new BSPDefaultFindDivider();
    partitionStrategy = new BSPSplitStrategy();
}

BSPTransformer::~BSPTransformer() {
    delete findStrategy;
    delete partitionStrategy;
}

/**
 * Transforms the geometry nodes of a tree into BSP trees.
 *
 * @pre The root of the scene to transform may not be of type GeometryNode.
 * @param node Root node of a scene to build from.
 */
void BSPTransformer::Transform(ISceneNode& node) {
    node.Accept(*this);
}

/**
 * Get the current diving strategy.
 * @return dividing strategy object.
 * @see BSPFindDividerStrategy
 */
BSPFindDividerStrategy* BSPTransformer::GetFindDividerStrategy() {
    return findStrategy;
}

/**
 * Set a new current diving strategy.
 * The old current diving strategy object will be deleted.
 * @return new dividing strategy object.
 * @see BSPFindDividerStrategy
 */
void BSPTransformer::SetFindDividerStrategy(BSPFindDividerStrategy* strategy) {
    delete findStrategy;
    findStrategy = strategy;
}

/**
 * Get the current partition strategy.
 * @return partition strategy object.
 * @see BSPPartitionStrategy
 */
BSPPartitionStrategy* BSPTransformer::GetPartitionStrategy() {
    return partitionStrategy;
}

/**
 * Set a new current partition strategy.
 * The old current partition strategy object will be deleted.
 * @return new partition strategy object.
 * @see BSPPartitionStrategy
 */
void BSPTransformer::SetPartitionStrategy(BSPPartitionStrategy* strategy) {
    delete partitionStrategy;
    partitionStrategy = strategy;
}

void BSPTransformer::VisitGeometryNode(GeometryNode* node) {
    if (node->GetFaceSet()->Size() != 0)
        node->GetParent()->ReplaceNode(node, new BSPNode(*this, node->GetFaceSet()));
    else
        node->GetParent()->RemoveNode(node);
}

} // NS Scene
} // NS OpenEngine
