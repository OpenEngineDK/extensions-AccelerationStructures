// Accelerated rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/AcceleratedRenderingView.h>

#include <Scene/BSPNode.h>
#include <Scene/QuadNode.h>

namespace OpenEngine {
namespace Renderers {

using namespace OpenEngine::Scene;

//! Rendering view constructor.
AcceleratedRenderingView::AcceleratedRenderingView(Viewport& viewport)
    : IRenderingView(viewport) {

}

AcceleratedRenderingView::~AcceleratedRenderingView() {

}

void AcceleratedRenderingView::VisitQuadNode(QuadNode* node) {
    if (viewport.GetViewingVolume()->IsVisible(node->GetBoundingBox()))
        node->VisitSubNodes(*this);
}

void AcceleratedRenderingView::VisitBSPNode(BSPNode* node) {
    node->VisitSubNodes(*this);
}

} // NS Renderers
} // NS OpenEngine
