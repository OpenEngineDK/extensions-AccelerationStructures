// BSP tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_BSP_NODE_H_
#define _OE_BSP_NODE_H_

#include <Scene/ISceneNode.h>
#include <Geometry/FaceSet.h>

namespace OpenEngine {
namespace Scene {

// forward declarations
class BSPTransformer;
class GeometryNode;

using namespace OpenEngine::Geometry;

// Epsilon value defining when a point is in the span of a plane
static const float epsilon = 0.1f;

/**
 * BSP tree node.
 *
 * @class BSPNode BSPNode.h SceneBSPTree/BSPNode.h
 */
class BSPNode : public ISceneNode {
    OE_SCENE_NODE(BSPNode, ISceneNode)

protected:

    FacePtr divider;  //!< dividing plane
    BSPNode* front;             //!< link to front node
    BSPNode* back;              //!< link to back node
    FaceSet* span;    //!< faces in dividing plane
    GeometryNode* sub;          //!< sub node wrapping the divided faces

public:
    BSPNode() : front(NULL),back(NULL),span(NULL) {};
    BSPNode(const BSPNode& node);
    explicit BSPNode(BSPTransformer& trans, FaceSet* faces);
    virtual ~BSPNode();

    void VisitSubNodes(ISceneNodeVisitor& visitor);

    FacePtr  GetDivider();
    BSPNode* GetFront();
    BSPNode* GetBack();
    FaceSet* GetSpan();

    int ComparePoint(Vector<3,float> point);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<ISceneNode>(*this);
        ar & divider;
        ar & front;
        ar & back;
        ar & span;
        ar & sub;
    }

};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::BSPNode)

#endif // _OE_BSP_NODE_H_
