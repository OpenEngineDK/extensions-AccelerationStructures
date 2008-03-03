// Binary Space Partitioned tree transformer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_BSP_TRANSFORMER_H_
#define _OE_BSP_TRANSFORMER_H_

#include <Scene/BSPNode.h>
#include <Scene/BSPFindDividerStrategy.h>
#include <Scene/BSPPartitionStrategy.h>
#include <Scene/GeometryNode.h>
#include <Scene/ISceneNodeVisitor.h>

namespace OpenEngine {
namespace Scene {

/**
 * BSP Transformer.
 *
 * Converts a scene structure to a one where all Geometry nodes are
 * converted to BSP trees.
 *
 * @code
 * // first some large scene structure must be available
 * SceneNode* scene;
 * // create a transformer
 * BSPTransformer bspt;
 * // transform the scene
 * bspt.Transform(*scene);
 * @endcode
 *
 * @see GeometryNode
 *
 * @class BSPTransformer BSPTransformer.h Scene/BSPTransformer.h
 */
class BSPTransformer : public ISceneNodeVisitor {
private:
    BSPFindDividerStrategy* findStrategy;
    BSPPartitionStrategy* partitionStrategy;

public:
    BSPTransformer();
    virtual ~BSPTransformer();

    virtual void Transform(ISceneNode& node);

    virtual BSPFindDividerStrategy* GetFindDividerStrategy();
    virtual void SetFindDividerStrategy(BSPFindDividerStrategy* strategy);

    virtual BSPPartitionStrategy* GetPartitionStrategy();
    virtual void SetPartitionStrategy(BSPPartitionStrategy* strategy);

    virtual void VisitGeometryNode(GeometryNode* node);
};

} // NS Scene
} // NS OpenEngine

#endif // _OE_BSP_TRANSFORMER_H_
