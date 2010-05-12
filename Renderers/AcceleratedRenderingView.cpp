// Accelerated rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/AcceleratedRenderingView.h>
#include <Display/IViewingVolume.h>

#include <Scene/BSPNode.h>
#include <Scene/QuadNode.h>

namespace OpenEngine {
namespace Renderers {

using namespace OpenEngine::Scene;
using namespace OpenEngine::Display;

//! Rendering view constructor.
AcceleratedRenderingView::AcceleratedRenderingView()
    : ISceneNodeVisitor(), 
      vv(NULL)
{
}    


AcceleratedRenderingView::~AcceleratedRenderingView() {
}

void AcceleratedRenderingView::SetViewingVolume(IViewingVolume* vv) {
    this->vv = vv;
}

void AcceleratedRenderingView::VisitQuadNode(QuadNode* node) {
    #ifdef OE_SAFE
    if (!vv) throw Exception("Accelerated visitor with NULL viewing volume.");
    #endif
    if (vv->IsVisible(node->GetBoundingBox()))
        node->VisitSubNodes(*this);
}

void AcceleratedRenderingView::VisitBSPNode(BSPNode* node) {
    node->VisitSubNodes(*this);
}

} // NS Renderers
} // NS OpenEngine
