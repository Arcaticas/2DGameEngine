#pragma once

namespace Physics
{
	inline void TwoDPhysicsObj::SetDragCoefficient(float i_fluidDensity, float i_fluidDrag, float i_size)
	{
		m_dragCoef = .5f * i_fluidDensity * i_fluidDrag * i_size;
	}
}