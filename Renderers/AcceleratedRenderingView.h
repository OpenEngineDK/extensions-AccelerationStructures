// Accelerated rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _ACCELERATED_RENDERING_VIEW_H_
#define _ACCELERATED_RENDERING_VIEW_H_

#include <Scene/ISceneNodeVisitor.h>

namespace OpenEngine {
    namespace Scene {
        class BSPNode;
        class QuadNode;
    }
    namespace Display{
        class IViewingVolume;
    }
namespace Renderers {
    using Display::IViewingVolume;
    using Scene::BSPNode;
    using Scene::QuadNode;
    using Scene::ISceneNodeVisitor;

/**
 * Accelerated rendering view.
 */
class AcceleratedRenderingView : virtual public ISceneNodeVisitor {
private:
    IViewingVolume* vv;
public:
    AcceleratedRenderingView();
    virtual ~AcceleratedRenderingView();

    void SetViewingVolume(IViewingVolume* vv);

    void VisitQuadNode(QuadNode* node);
    void VisitBSPNode(BSPNode* node);
};

} // NS Renderers
} // NS OpenEngine

#endif // _ACCELERATED_RENDERING_VIEW_H_
