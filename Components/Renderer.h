#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/glm.hpp>
#include <glm/common.hpp>

#include "../Managers/ShaderManager.h"
#include "../Managers/ModelManager.h"
#include "../Components/Component.h"
#include "../Engine/Material.h"

class IRenderer : public IComponent
{
public:
	enum FLAGS {
		COLOR = 1 << 0,		// 1
		CAMERA = 1 << 1,	// 2
		SPECULAR = 1 << 2,  // 4
		AMBIENT = 1 << 3,	// 8
		DIFFUSE = 1 << 4,	// 16
		SHININESS = 1 << 5, // 32
		LIGHTS = 1 << 6,	// 64
		TEXTURE = 1 << 7	// 128
	};

	void SetFlag(FLAGS _flag);
	void RemoveFlag(FLAGS _flag);
	bool IsFlagSet(FLAGS _flag);

protected:
	ShaderManager& shaderManager = ShaderManager::GetInstance();
	int flags = 0;
};

