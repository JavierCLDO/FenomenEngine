#pragma once

#include "Utils/vector.h"
#include "Components/component.h"
#include <memory>

namespace fenomen::render {
	class RenderObject;
}

namespace fenomen::logic {

class RenderComponent : public Component {
public:
	RenderComponent(Entity* owner);
	virtual ~RenderComponent();

	virtual void Init();
	virtual void Sync();
	virtual void OnDestroy() override;

	void SetVisible(bool b);
	void SetStatic();
	void SetDynamic();

	virtual void Create(const std::string&) = 0;

protected:
	bool bStatic, bVisible;
	std::unique_ptr<render::RenderObject> renderObject;
};

}
