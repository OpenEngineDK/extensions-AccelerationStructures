// BSP tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _BSP_NODE_H_
#define _BSP_NODE_H_

#include <Scene/SceneNode.h>
#include <Geometry/FaceSet.h>

namespace OpenEngine {
namespace Scene {

using namespace OpenEngine::Scene;
using namespace OpenEngine::Geometry;

// Epsilon value defining when a point is in the span of a plane
static const float epsilon = 0.1f;

/**
 * BSP tree node.
 *
 * @class BSPNode BSPNode.h SceneBSPTree/BSPNode.h
 */
class BSPNode : public SceneNode {
protected:

    FacePtr    divider;         //!< dividing plane
    BSPNode* front;             //!< link to front node
    BSPNode* back;              //!< link to back node
    FaceSet* span;              //!< faces in dividing plane

    FacePtr FindDivider(FaceSet& faces);

public:
    BSPNode(BSPNode& node);
    explicit BSPNode(FaceSet* faces);
    ~BSPNode();
    ISceneNode* Clone();
    void Accept(ISceneNodeVisitor& visitor);
    void VisitSubNodes(ISceneNodeVisitor& visitor);

    FacePtr  GetDivider();
    BSPNode* GetFront();
    BSPNode* GetBack();
    FaceSet* GetSpan();

    int ComparePoint(Vector<3,float> point);
};

} // NS Scene
} // NS OpenEngine

#endif // _BSP_NODE_H_
