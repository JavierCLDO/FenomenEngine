#pragma once

#include "Components/renderComponent.h"
#include <string>

namespace fenomen::logic {

class MeshComponent : public RenderComponent {
public:
	MeshComponent(Entity* owner);
	virtual ~MeshComponent();

	void Init() override;
	//void Update(double deltaTime) override;

	void Sync() override;

	void Create(const std::string& mesh);

	void CreatePlane(double width = 2.0, double height = 2.0, uint32_t xsegments = 1, uint32_t ysegments = 1, double utile = 1.0, double vtile = 1.0);

	void Create(const std::string& mesh, const std::string& datablock);

	void SetDatablock(const std::string& name);

	const Vector& GetAABBsize();
	const Vector& GetHalfAABBSize();

protected:

	std::string dataBlock; bool bDataBlockChanged;
};

}
