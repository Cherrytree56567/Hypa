#include "Rendering3D.h"

namespace Hypa {
	Rendering3D::~Rendering3D() {

	}

	Rendering3D::Rendering3D(std::shared_ptr<Window> window, std::shared_ptr<RenderingAPISystem> rAPIsys) : name("3DLayer"), pWindow(window), rAPISystem(rAPIsys), show(true) {

	}

	void Rendering3D::OnAttach() {
	}

	void Rendering3D::OnDetach() {

	}

	void Rendering3D::Render() {
		rAPISystem->GetCurrentRenderingAPI()->Render();
	}

	bool Rendering3D::IsShown() const {
		return show;
	}

	const std::string& Rendering3D::GetName() const {
		return name;
	}

	void Rendering3D::SetShow(bool value) {
		show = value;
	}
}