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
    //partitionStrategy = new BSPDivideStrategy();
}

BSPTransformer::~BSPTransformer() {
    delete findStrategy;
}

void BSPTransformer::Transform(ISceneNode& node) {
    node.Accept(*this);
}

BSPFindDividerStrategy* BSPTransformer::GetFindDividerStrategy() {
    return findStrategy;
}

void BSPTransformer::SetFindDividerStrategy(BSPFindDividerStrategy* strategy) {
    delete findStrategy;
    findStrategy = strategy;
}

BSPPartitionStrategy* BSPTransformer::GetPartitionStrategy() {
    return partitionStrategy;
}

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
