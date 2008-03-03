// Quad tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _QUAD_NODE_H_
#define _QUAD_NODE_H_

#include <Scene/SceneNode.h>
#include <Geometry/Box.h>
#include <Geometry/FaceSet.h>
#include <boost/serialization/base_object.hpp>

#include <boost/serialization/export.hpp>


// forward declarations
namespace OpenEngine {
namespace Scene {

class ISceneNodeVisitor;

using namespace OpenEngine::Scene;
using namespace OpenEngine::Geometry;

/**
 * Quad tree node.
 * To build a tree please refer to QuadTreeBuilder.
 *
 * @see QuadTreeBuilder
 *
 * @class QuadNode QuadNode.h Scene/QuadTree/QuadNode.h
 */
class QuadNode : public SceneNode {
private:

    //! bounding square
    Box bb;

    //! sub nodes
    QuadNode *tl, *tr, *bl, *br;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<SceneNode>(*this);
        ar & bb;
        ar & tl;
        ar & tr;
        ar & bl;
        ar & br;
    }


public:
    QuadNode():tl(NULL),tr(NULL),bl(NULL),br(NULL) {}; // empty constructor for serialization
    QuadNode(FaceSet* faces, const int count, const float hsize);
    QuadNode(QuadNode& node);
    ~QuadNode();

    ISceneNode* CloneSelf();
    void Accept(ISceneNodeVisitor& visitor);
    void VisitSubNodes(ISceneNodeVisitor& visitor);

    QuadNode* GetTopLeft() const;
    QuadNode* GetTopRight() const;
    QuadNode* GetBottomLeft() const;
    QuadNode* GetBottomRight() const;

    Box GetBoundingBox() const;
};

} // NS Scene
} // NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Scene::QuadNode)

#endif // _QUAD_NODE_H_
